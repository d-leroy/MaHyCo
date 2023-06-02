#include "mahyco/MahycoModule.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

namespace Mahyco {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

MahycoModule::
MahycoModule(const ModuleBuildInfo& bi)
: MahycoModuleBase<MahycoModule>(bi)
{
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

MahycoModule::
~MahycoModule()
{
}

/*---------------------------------------------------------------------------*/
/* Pour préparer les accélérateurs */
/* TODO: Modaniser? */
/*---------------------------------------------------------------------------*/
void MahycoModule::
accBuild() 
{
  m_acc_env = SingletonIAccEnv::accEnv(subDomain());
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* Vérification de la compatibilité des options */
/* TODO: Modaniser? */
/*---------------------------------------------------------------------------*/
void MahycoModule::
checkOptions()
{
  IParallelMng* m_parallel_mng = subDomain()->parallelMng();
  my_rank = m_parallel_mng->commRank();


  info() <<  "Mon rang " << my_rank << " et mon nombre de mailles " << allCells().size();
  info() <<  " Mes mailles pures : " << ownCells().size();
  info() <<  " Mes mailles frantomes : " << allCells().size() - ownCells().size();

  info() << " Check donnees ";
  if ((options()->remap()->getOrdreProjection() == 3) && (mesh()->ghostLayerMng()->nbGhostLayer() != 3) && (m_parallel_mng->isParallel() == true)) {
    info() << " mode parallele : " << m_parallel_mng->isParallel();
    info() << " nombre de couches de mailles fantomes : " << mesh()->ghostLayerMng()->nbGhostLayer();
    info() << " incompatible avec la projection d'ordre " << options()->remap()->getOrdreProjection();
    info() << " ----------------------------- fin du calcul à la fin de l'init ---------------------------------------------";
    subDomain()->timeLoopMng()->stopComputeLoop(true);
  }
  if ((options()->withProjection == true) && (mesh()->ghostLayerMng()->nbGhostLayer() < 2) && (m_parallel_mng->isParallel() == true)) {
    info() << " mode parallele : " << m_parallel_mng->isParallel();
    info() << " nombre de couches de mailles fantomes : " << mesh()->ghostLayerMng()->nbGhostLayer();
    info() << " incompatible avec la projection ";
    info() << " ----------------------------- fin du calcul à la fin de l'init ---------------------------------------------";
    subDomain()->timeLoopMng()->stopComputeLoop(true);
  }
}

/*---------------------------------------------------------------------------*/
/* Initialisation de m_cartesian_mesh et m_dimension */
/* TODO: Modaniser? */
/*---------------------------------------------------------------------------*/
void MahycoModule::
initCartesianMesh()
{
  m_cartesian_mesh = _initCartMesh();
  m_dimension = mesh()->dimension(); 
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void MahycoModule::
allocCqs(MahycoAllocCqsVars& vars)
{
  // Dimensionne les variables tableaux
  vars.m_cell_cqs.resize(4*(m_dimension-1));
  vars.m_cell_cqs_n.resize(4*(m_dimension-1));
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void MahycoModule::
initDtIni(MahycoInitDtIniVars& vars)
{
  // Initialise le delta-t
  Real deltat_init = getDeltatInit();
  m_global_deltat = deltat_init;
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void MahycoModule::
initHydroVar(MahycoInitHydroVarVars& vars)
{
  info() << " Initialisation des variables";
  // Initialises les variables (surcharge l'init d'arcane)
  getCasModel()->initVar(m_dimension);
  
  if (!getSansLagrange()) {
    for( Integer i=0,n=getEnvironment().size(); i<n; ++i ) {
        IMeshEnvironment* ienv = mm->environments()[i];
        // Initialise l'énergie et la vitesse du son
        getEnvironment()[i].eosModel()->initEOS(ienv);
    }

    CellToAllEnvCellConverter all_env_cell_converter(mm);

    // valeur moyenne
    ENUMERATE_CELL(icell, allCells()){
        Cell cell = * icell;
        AllEnvCell all_env_cell = all_env_cell_converter[cell];
        if (all_env_cell.nbEnvironment() !=1) {
            vars.m_internal_energy[cell] = 0.;
            ENUMERATE_CELL_ENVCELL(ienvcell,all_env_cell) {
                EnvCell ev = *ienvcell;        
                vars.m_internal_energy[cell] += vars.m_internal_energy[ev] * vars.m_mass_fraction[ev];
                vars.m_sound_speed[cell] = std::max(vars.m_sound_speed[ev], vars.m_sound_speed[cell]);
            }
        }
    }
  }
  // initialisation du volume Euler
  ENUMERATE_CELL(icell,allCells()){
    Cell cell = *icell;
    // initialisation du volume Euler
    vars.m_euler_volume[cell] = vars.m_cell_volume[cell];
  }
  
  Arcane::Numerics::IGeometryMng* gm = getGeometry();
  gm->init();
  auto g = gm->geometry();
  bool is_verbose = false;
  if (is_verbose){
    ENUMERATE_CELL(icell,allCells()){
      Cell c = *icell;
      // initialisation du volume Euler
      info() << "Volume = " << g->computeMeasure(c);  
      for (NodeEnumerator inode(c.nodes()); inode.hasNext(); ++inode)
        info() << c.localId() << " avec " << inode.localId();
    }
  }
  
  InitGeometricValues();
  
  // deplacé de hydrocontinueInit
  // calcul des volumes via les cqs, differents deu calcul dans computeGeometricValues ?
  {
    auto queue = m_acc_env->newQueue();
    auto command = makeCommand(queue);

    auto in_node_coord = ax::viewIn(command,vars.m_node_coord);
    auto in_cell_cqs   = ax::viewIn(command,vars.m_cell_cqs);
    auto out_cell_volume_g  = ax::viewOut(command,vars.m_cell_volume.globalVariable()); 

    auto cnc = m_acc_env->connectivityView().cellNode();

    // NOTE : on ne peut pas utiliser un membre sur accélérateur (ex : m_dimension), 
    // cela revient à utiliser this->m_dimension avec this pointeur illicite
    Real inv_dim = 1./m_dimension;

    command << RUNCOMMAND_ENUMERATE(Cell, cid, allCells()){

      // Calcule le volume de la maille
      Span<const Real3> cell_cqs = in_cell_cqs[cid];
      Real volume = 0;

      Int64 index=0;
      for( NodeLocalId nid : cnc.nodes(cid) ){
        volume += math::dot(in_node_coord[nid],  cell_cqs[index]);
        ++index;
      }
      volume *= inv_dim;
      out_cell_volume_g[cid] = volume;
    };
  }
}


/*---------------------------------------------------------------------------*/
/* Affecte le type de synchronisation des variables arcane */
/* TODO: Modaniser? */
/*---------------------------------------------------------------------------*/
void MahycoModule::
setSyncVarVers()
{
  auto* mm = IMeshMaterialMng::getReference(defaultMesh());
  mm->setSynchronizeVariableVersion(6);
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void MahycoModule::
computeCellMass(MahycoComputeCellMassVars& vars)
{
  debug() << " Entree dans computeCellMass()";
  {
    auto queue = m_acc_env->newQueue();
    auto command = makeCommand(queue);

    auto in_cell_volume_g = ax::viewIn(command, vars.m_cell_volume.globalVariable());
    auto in_density_g     = ax::viewIn(command, vars.m_density.globalVariable());
    auto out_cell_mass_g  = ax::viewOut(command, vars.m_cell_mass.globalVariable());

    command << RUNCOMMAND_ENUMERATE(Cell, cid, allCells()){
      out_cell_mass_g[cid] = in_density_g[cid] * in_cell_volume_g[cid];
    };
  }
  ENUMERATE_ENV(ienv,mm){
    IMeshEnvironment* env = *ienv;
    ENUMERATE_ENVCELL(ienvcell,env) {
      EnvCell ev = *ienvcell;
      Cell cell = ev.globalCell();
      vars.m_cell_mass[ev] = vars.m_mass_fraction[ev] * vars.m_cell_mass[cell];
    }
  }
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void MahycoModule::
computeNodeMass(MahycoComputeNodeMassVars& vars)
{
  debug() << " Entree dans computeNodeMass()";
  // Initialisation ou reinitialisation de la masse nodale
  // Le calcul sur les noeuds fantômes externes n'est pas correct
  // de toute façon (d'où m_node_mass.synchronize) autant ne calculer
  // que sur ownNodes()
  m_acc_env->vsyncMng()->computeAndSync(
    ownNodes(),
    [&](NodeGroup node_group, RunQueue* async_queue) {
      auto command = makeCommand(async_queue);

      Real one_over_nbnode = m_dimension == 2 ? .25  : .125 ;
      auto nc_cty = m_acc_env->connectivityView().nodeCell();

      auto in_cell_mass_g = ax::viewIn(command, vars.m_cell_mass.globalVariable());
      auto out_node_mass = ax::viewOut(command, vars.m_node_mass);

      command << RUNCOMMAND_ENUMERATE(Node,nid,node_group) {
        Real sum_mass = 0.;
        for( CellLocalId cid : nc_cty.cells(nid) )
          sum_mass += in_cell_mass_g[cid];
        out_node_mass[nid] = one_over_nbnode * sum_mass;
      };
    },
    vars.m_node_mass);
}

/*---------------------------------------------------------------------------*/
/* TODO: Modaniser?*/
/*---------------------------------------------------------------------------*/

void MahycoModule::
continueForMultiMat()
{
  PROF_ACC_BEGIN(__FUNCTION__);

  mm = IMeshMaterialMng::getReference(defaultMesh());

  mm->recreateFromDump();
  m_nb_env = mm->environments().size();
  m_nb_vars_to_project = 3 * m_nb_env + 3 + 1 + 1;

  PROF_ACC_END;
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void MahycoModule::
continueForIterationDt(MahycoContinueForIterationDtVars& vars)
{
  m_global_old_deltat = vars.m_old_deltat;
  // mise a jour nombre iteration 
  m_global_iteration = m_global_iteration() +1;
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void MahycoModule::
saveValuesAtN(MahycoSaveValuesAtNVars& vars)
{
  debug() << " Entree dans saveValuesAtN()";

  // le pas de temps a été mis a jour a la fin dunpas de temps precedent et arcanne met dans m_global_old_deltat ce pas de temps ?
  // donc nous ont remet le bon old pas de temps
  m_global_old_deltat = m_old_deltat;

#if 0  
  // synchronisation debut de pas de temps (avec projection nécéssaire ?)
  vars.m_pseudo_viscosity.synchronize();
  vars.m_density.synchronize();
  vars.m_internal_energy.synchronize();
  vars.m_cell_volume.synchronize();
  vars.m_pressure.synchronize();
  
   auto queue_synchronize = m_acc_env->refQueueAsync();
   MeshVariableSynchronizerList mvsl(m_acc_env->vsyncMng()->bufAddrMng());
   mvsl.add(vars.m_pseudo_viscosity);
   mvsl.add(vars.m_density);
   mvsl.add(vars.m_internal_energy);
   mvsl.add(vars.m_cell_volume);
   mvsl.add(vars.m_pressure);
   m_acc_env->vsyncMng()->multiMatSynchronize(mvsl, queue_synchronize, VS_bulksync_evqueue);
#endif
  
//   m_cell_cqs.synchronize();
//   m_velocity.synchronize();

  // Exploitation de plusieurs queues asynchrones en concurrence
  // queue_cell => recopie des valeurs pures et globales
  // menv_queue => recopies des valeurs mixtes de tous les environnements
  // queue_node => recopie des valeurs aux noeuds
  
  auto queue_cell = m_acc_env->newQueue();
  // on va recopier de façon asynchrone et concurrente les grandeurs aux mailles et aux noeuds
  queue_cell.setAsync(true); 

  {
    auto command = makeCommand(queue_cell);

    auto in_pseudo_viscosity = ax::viewIn(command,vars.m_pseudo_viscosity.globalVariable());
    auto in_pressure         = ax::viewIn(command,vars.m_pressure.globalVariable());
    auto in_cell_volume      = ax::viewIn(command,vars.m_cell_volume.globalVariable());
    auto in_density          = ax::viewIn(command,vars.m_density.globalVariable());
    auto in_internal_energy  = ax::viewIn(command,vars.m_internal_energy.globalVariable());
    auto in_cell_cqs         = ax::viewIn(command,vars.m_cell_cqs);

    auto inout_pseudo_viscosity_n = ax::viewInOut(command,vars.m_pseudo_viscosity_n.globalVariable());

    auto out_pseudo_viscosity_nmoins1 = ax::viewOut(command,vars.m_pseudo_viscosity_nmoins1.globalVariable());
    auto out_pressure_n         = ax::viewOut(command,vars.m_pressure_n.globalVariable());
    auto out_cell_volume_n      = ax::viewOut(command,vars.m_cell_volume_n.globalVariable());
    auto out_density_n          = ax::viewOut(command,vars.m_density_n.globalVariable());
    auto out_internal_energy_n  = ax::viewOut(command,vars.m_internal_energy_n.globalVariable());
    auto out_cell_cqs_n         = ax::viewInOut(command,vars.m_cell_cqs_n);

    command << RUNCOMMAND_ENUMERATE(Cell, cid, allCells()){
      out_pseudo_viscosity_nmoins1[cid] = inout_pseudo_viscosity_n[cid];
      inout_pseudo_viscosity_n[cid] = in_pseudo_viscosity[cid];
      out_pressure_n[cid] = in_pressure[cid];
      out_cell_volume_n[cid] = in_cell_volume[cid];
      out_density_n[cid] = in_density[cid];
      out_internal_energy_n[cid] = in_internal_energy[cid];

      out_cell_cqs_n[cid].copy(in_cell_cqs[cid]);
    }; // asynchrone
  }

  auto menv_queue = m_acc_env->multiEnvMng()->multiEnvQueue();
#if 0
  ENUMERATE_ENV(ienv,mm){
    IMeshEnvironment* env = *ienv;
    ENUMERATE_ENVCELL(ienvcell,env){
      EnvCell ev = *ienvcell;
      vars.m_pseudo_viscosity_nmoins1[ev] = vars.m_pseudo_viscosity_n[ev];
      vars.m_pseudo_viscosity_n[ev] = vars.m_pseudo_viscosity[ev];
      vars.m_pressure_n[ev] = vars.m_pressure[ev];
      vars.m_cell_volume_n[ev] = vars.m_cell_volume[ev];
      vars.m_density_n[ev] = vars.m_density[ev];
      vars.m_internal_energy_n[ev] = vars.m_internal_energy[ev];
    }
  }
#else
  // Les recopies par environnement dont indépendantes, on peut utiliser menv_queue
  ENUMERATE_ENV(ienv,mm){
    IMeshEnvironment* env = *ienv;

    auto command = makeCommand(menv_queue->queue(env->id()));

    // Pour les mailles impures (mixtes), liste des indices valides 
    Span<const Int32> in_imp_idx(env->impureEnvItems().valueIndexes());
    Integer nb_imp = in_imp_idx.size();

    Span<const Real> in_pseudo_viscosity(envView(vars.m_pseudo_viscosity, env));
    Span<const Real> in_pressure        (envView(vars.m_pressure, env));
    Span<const Real> in_cell_volume     (envView(vars.m_cell_volume, env));
    Span<const Real> in_density         (envView(vars.m_density, env));
    Span<const Real> in_internal_energy (envView(vars.m_internal_energy, env));

    Span<Real> inout_pseudo_viscosity_n(envView(vars.m_pseudo_viscosity_n, env));

    Span<Real> out_pseudo_viscosity_nmoins1(envView(vars.m_pseudo_viscosity_nmoins1, env));
    Span<Real> out_pressure_n         (envView(vars.m_pressure_n, env));
    Span<Real> out_cell_volume_n      (envView(vars.m_cell_volume_n, env));
    Span<Real> out_density_n          (envView(vars.m_density_n, env));
    Span<Real> out_internal_energy_n  (envView(vars.m_internal_energy_n, env));

    command << RUNCOMMAND_LOOP1(iter, nb_imp) {
      auto imix = in_imp_idx[iter()[0]]; // iter()[0] \in [0,nb_imp[

      out_pseudo_viscosity_nmoins1[imix] = inout_pseudo_viscosity_n[imix];
      inout_pseudo_viscosity_n[imix] = in_pseudo_viscosity[imix];
      out_pressure_n[imix] = in_pressure[imix];
      out_cell_volume_n[imix] = in_cell_volume[imix];
      out_density_n[imix] = in_density[imix];
      out_internal_energy_n[imix] = in_internal_energy[imix];
    }; // asynchrone par rapport au CPU
  }
#endif

  bool copy_velocity = !getSansLagrange();
  bool copy_node_coord = getWithProjection() && getRemap()->isEuler();

  auto queue_node = m_acc_env->newQueue(); // queue asynchrone, pendant ce temps exécution sur queue_cell et menv_queue[*]
  queue_node.setAsync(true);

  if (copy_velocity || copy_node_coord) {
    auto command = makeCommand(queue_node);

    // if (!getSansLagrange()) m_velocity_n.copy(m_velocity)
    auto in_velocity = ax::viewIn(command, vars.m_velocity);
    auto out_velocity_n = ax::viewOut(command, vars.m_velocity_n);

    // if (getWithProjection() && getRemap()->isEuler()) m_node_coord.copy(m_node_coord_0)
    auto in_node_coord_0 = ax::viewIn(command, vars.m_node_coord_0);
    auto out_node_coord = ax::viewOut(command, vars.m_node_coord);

    command << RUNCOMMAND_ENUMERATE(Node,nid,allNodes()) {
      if (copy_velocity)
        out_velocity_n[nid] = in_velocity[nid];
      if (copy_node_coord)
        out_node_coord[nid] = in_node_coord_0[nid];
    }; // asynchrone
  }

  queue_cell.barrier();
  menv_queue->waitAllQueues();
  queue_node.barrier();
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void MahycoModule::
computeArtificialViscosity(MahycoComputeArtificialViscosityVars& vars)
{
  if (getSansLagrange()) return;
  PROF_ACC_BEGIN(__FUNCTION__);
  debug() << " Entree dans computeArtificialViscosity()";
#if 0
  ENUMERATE_ENV(ienv,mm){
    IMeshEnvironment* env = *ienv;
    Real adiabatic_cst = getEnvironment()[env->id()].eosModel()->getAdiabaticCst(env);
    ENUMERATE_ENVCELL(ienvcell,env){
      EnvCell ev = *ienvcell;
      Cell cell = ev.globalCell();
      m_pseudo_viscosity[ev] = 0.;     
      if (m_div_u[cell] < 0.0) {
        m_pseudo_viscosity[ev] = 1. / m_tau_density[ev]
          * (-0.5 * m_caracteristic_length[cell] * m_sound_speed[cell] * m_div_u[cell]
             + (adiabatic_cst + 1) / 2.0 * m_caracteristic_length[cell] * m_caracteristic_length[cell]
             * m_div_u[cell] * m_div_u[cell]);
      }
    }
  }
  

  // maille mixte
  // moyenne sur la maille
  CellToAllEnvCellConverter all_env_cell_converter(mm);
  ENUMERATE_CELL(icell, allCells()){
    Cell cell = * icell;
    AllEnvCell all_env_cell = all_env_cell_converter[cell];
    if (all_env_cell.nbEnvironment() !=1) {
      m_pseudo_viscosity[cell] = 0.;     
      ENUMERATE_CELL_ENVCELL(ienvcell,all_env_cell) {
        EnvCell ev = *ienvcell;        
        m_pseudo_viscosity[cell] += m_pseudo_viscosity[ev] * m_fracvol[ev];
      }
    }
  }
#else
  // Traitement des mailles pures tout environnement compris
  // Pour ce faire, on boucle sur tout le maillage en initialisant à 0
  // Si la maille est pure, il faut récupérer l'env_id pour adiabatic_cst
  // A la fin de la boucle, toutes les mailles pures sont calculées 
  // et les emplacements des grandeurs globales pour les mailles mixtes sont à 0
  
  auto queue = m_acc_env->newQueue();
  queue.setAsync(true); // la queue est asynchrone par rapport à l'hôte, 
  // cependant tous les kernels lancés sur cette queue s'exécutent séquentiellement les uns après les autres
  // ici c'est primordial car le premier kernel va initialiser les grandeurs globales qui vont être mises 
  // à jour environnement par environnement par les kernels suivants

  {
    auto command = makeCommand(queue);

    auto in_env_id               = ax::viewIn(command, m_acc_env->multiEnvMng()->envId());
    auto in_div_u                = ax::viewIn(command, m_div_u);
    auto in_caracteristic_length = ax::viewIn(command, m_caracteristic_length);
    auto in_sound_speed          = ax::viewIn(command, m_sound_speed.globalVariable());
    auto in_tau_density          = ax::viewIn(command, m_tau_density.globalVariable());
    auto in_adiabatic_cst_env    = ax::viewIn(command, m_adiabatic_cst_env);

    auto out_pseudo_viscosity = ax::viewOut(command, m_pseudo_viscosity.globalVariable());

    command << RUNCOMMAND_ENUMERATE(Cell,cid,allCells()) {
      out_pseudo_viscosity[cid] = 0.;
      Integer env_id = in_env_id[cid]; // id de l'env si maille pure, <0 sinon
      if (env_id>=0 && in_div_u[cid] < 0.0) {
        CellLocalId ev_cid(cid); // exactement même valeur mais permet de distinguer ce qui relève du partiel et du global
        Real adiabatic_cst = in_adiabatic_cst_env(env_id);
        out_pseudo_viscosity[ev_cid] = 1. / in_tau_density[ev_cid]
          * (-0.5 * in_caracteristic_length[cid] * in_sound_speed[cid] * in_div_u[cid]
             + (adiabatic_cst + 1) / 2.0 * in_caracteristic_length[cid] * in_caracteristic_length[cid]
             * in_div_u[cid] * in_div_u[cid]);
      }
    };
  }
  
  // Traitement des mailles mixtes
  // Pour chaque env traité l'un après l'autre, on récupère les mailles mixtes
  // Pour chaque maille mixte, on calcule pseudo_viscosity 
  // et on accumule cette valeur *fracvol dans la grandeur globale
  ENUMERATE_ENV(ienv,mm){
    IMeshEnvironment* env = *ienv;

    auto command = makeCommand(queue);

    Real adiabatic_cst = m_adiabatic_cst_env(env->id());
    auto in_div_u                = ax::viewIn(command, m_div_u);
    auto in_caracteristic_length = ax::viewIn(command, m_caracteristic_length);
    auto in_sound_speed          = ax::viewIn(command, m_sound_speed.globalVariable());

    auto out_pseudo_viscosity = ax::viewOut(command, m_pseudo_viscosity.globalVariable());

    // Des sortes de vues sur les valeurs impures pour l'environnement env
    Span<const Real>    in_fracvol(envView(m_fracvol, env));
    Span<const Integer> in_global_cell(envView(m_acc_env->multiEnvMng()->globalCell(), env));
    Span<const Real>    in_tau_density(envView(m_tau_density, env));
    Span<Real> inout_pseudo_viscosity(envView(m_pseudo_viscosity, env));


    // Pour les mailles impures (mixtes), liste des indices valides 
    Span<const Int32> in_imp_idx(env->impureEnvItems().valueIndexes());
    Integer nb_imp = in_imp_idx.size();

    command << RUNCOMMAND_LOOP1(iter, nb_imp) {
      auto imix = in_imp_idx[iter()[0]]; // iter()[0] \in [0,nb_imp[
      CellLocalId cid(in_global_cell[imix]); // on récupère l'identifiant de la maille globale

      // On calcule la valeur partielle sur la maille mixte
      inout_pseudo_viscosity[imix] = 0.;
      if (in_div_u[cid] < 0.0) {
        inout_pseudo_viscosity[imix] = 1. / in_tau_density[imix]
          * (-0.5 * in_caracteristic_length[cid] * in_sound_speed[cid] * in_div_u[cid]
             + (adiabatic_cst + 1) / 2.0 * in_caracteristic_length[cid] * in_caracteristic_length[cid]
             * in_div_u[cid] * in_div_u[cid]);
      }

      // Contribution à la grandeur globale, 
      // out_pseudo_viscosity[cid] a été initialisée lors de la boucle sur maille pure
      out_pseudo_viscosity[cid] += inout_pseudo_viscosity[imix] * in_fracvol[imix]; 
    };
  }
  queue.barrier(); // attente de fin des exécutions sur GPU
#endif
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void MahycoModule::
updateForceAndVelocity(MahycoUpdateForceAndVelocityVars& vars, const Real dt)
{
  debug() << " Entree dans updateForceAndVelocity()";
 
#if 0 
  // Remise à zéro du vecteur des forces.
  m_force.fill(Real3::zero());

  // Calcul pour chaque noeud de chaque maille la contribution
  // des forces de pression
  ENUMERATE_CELL(icell, allCells()){
    Cell cell = * icell;
    Real pressure = vars.m_pressure[icell] + vars.m_pseudo_viscosity[icell];
    for (NodeEnumerator inode(cell.nodes()); inode.hasNext(); ++inode) {
      vars.m_force[inode] += pressure * vars.m_cell_cqs[icell] [inode.index()];
     }
  }

  VariableNodeReal3InView in_force(viewIn(vars.m_force));
  VariableNodeReal3InView in_velocity(viewIn(vars.m_velocity_in));
  VariableNodeRealInView  in_mass(viewIn(vars.m_node_mass));
  VariableNodeReal3OutView out_velocity(viewOut(vars.m_velocity_out));

  // Calcule l'impulsion aux noeuds
  PRAGMA_IVDEP
  ENUMERATE_SIMD_NODE(inode, allNodes()){
    SimdNode snode=*inode;
    out_velocity[snode] = in_velocity[snode] + ( dt / in_mass[snode]) * in_force[snode];;
  }
  vars.m_velocity_out.synchronize();
#else
  m_acc_env->vsyncMng()->computeAndSync(
    ownNodes(),
    [&](NodeGroup node_group, RunQueue* async_queue) {
  
      auto command = makeCommand(async_queue);
     
      auto in_pressure         = ax::viewIn(command, vars.m_pressure.globalVariable());
      auto in_pseudo_viscosity = ax::viewIn(command, vars.m_pseudo_viscosity.globalVariable());
      auto in_cell_cqs         = ax::viewIn(command, vars.m_cell_cqs);
      // TODO : supprimer m_force, qui ne devient qu'une variable temporaire de travail
      auto out_force           = ax::viewOut(command, vars.m_force);
     
      auto node_index_in_cells = m_acc_env->nodeIndexInCells();
      const Integer max_node_cell = m_acc_env->maxNodeCell();
     
      auto nc_cty = m_acc_env->connectivityView().nodeCell();
     
      auto in_mass      = ax::viewIn(command, vars.m_node_mass);
      auto in_velocity  = ax::viewIn(command, vars.m_velocity_in);
      auto out_velocity = ax::viewOut(command, vars.m_velocity_out);
     
      command << RUNCOMMAND_ENUMERATE(Node,nid,node_group) {
        Int32 first_pos = nid.localId() * max_node_cell;
        Integer index = 0;
        Real3 node_force = Real3::zero();
        for( CellLocalId cid : nc_cty.cells(nid) ){
          Int16 node_index = node_index_in_cells[first_pos + index];
          node_force += (in_pressure[cid]+in_pseudo_viscosity[cid]) 
            * in_cell_cqs[cid][node_index];
          ++index;
        }
        out_force[nid] = node_force;
     
        // On peut mettre la vitesse à jour dans la foulée
        out_velocity[nid] = in_velocity[nid] + ( dt / in_mass[nid]) * node_force;
      };
    },
    vars.m_velocity_out);
#endif
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void MahycoModule::
updateVelocity(MahycoUpdateVelocityVars& vars)
{
  if (getSansLagrange()) {
    updateVelocityWithoutLagrange();
    PROF_ACC_END;
    return;
  }
  
  // passage des vitesse de n à n-1/2 si projection 
  // la vitesse m_velocity_n 
  // (qui dans le cas de vnr-csts est la vitesse apres projection du pas de temps précédent donc n),
  // est replacee à n-1/2 pour vnr-csts.
  // Dans le cas de vnr (pas csts) elle est deja en n-1/2
  if (getSchemaCsts() && getWithProjection()) updateVelocityBackward();
      
      
  debug() << " Entree dans updateVelocity()";
#if 0
  // Remise à zéro du vecteur des forces.
  m_force.fill(Real3::zero());

  // Calcul pour chaque noeud de chaque maille la contribution
  // des forces de pression
  ENUMERATE_CELL(icell, allCells()){
    Cell cell = * icell;
    Real pressure = vars.m_pressure_n[icell] + vars.m_pseudo_viscosity_n[icell];
    for (NodeEnumerator inode(cell.nodes()); inode.hasNext(); ++inode) {
      vars.m_force[inode] += pressure * vars.m_cell_cqs_n[icell] [inode.index()];
     }
  }
  
  VariableNodeReal3InView in_force(viewIn(vars.m_force));
  VariableNodeReal3InView in_velocity(viewIn(vars.m_velocity_n));
  VariableNodeRealInView  in_mass(viewIn(vars.m_node_mass));
  VariableNodeReal3OutView out_velocity(viewOut(vars.m_velocity));

  const Real dt(0.5 * (m_global_old_deltat() + m_global_deltat()));
  // Calcule l'impulsion aux noeuds
  PRAGMA_IVDEP
  ENUMERATE_SIMD_NODE(inode, allNodes()){
    SimdNode snode=*inode;
    out_velocity[snode] = in_velocity[snode] + ( dt / in_mass[snode]) * in_force[snode];;
  }

  m_velocity.synchronize();
#else
  updateForceAndVelocity(0.5 * (m_global_old_deltat() + m_global_deltat()),
        /* calcul m_force : */ vars.m_pressure_n, vars.m_pseudo_viscosity_n, vars.m_cell_cqs_n,
        /* calcul m_velocity : */ vars.m_velocity_n, vars.m_velocity);
#endif
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void MahycoModule::
updateVelocityBackward(MahycoUpdateVelocityBackwardVars& vars)
{
  if (getSansLagrange()) return;
  debug() << " Entree dans updateVelocityBackward()";
  updateForceAndVelocity(-0.5 * m_global_old_deltat(),
      /* calcul m_force : */ vars.m_pressure_n, vars.m_pseudo_viscosity_n, vars.m_cell_cqs_n,
      /* calcul m_velocity_n : */ vars.m_velocity_n, vars.m_velocity_n);
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void MahycoModule::
updateVelocityForward(MahycoUpdateVelocityForwardVars& vars)
{
  if (getSansLagrange()) return;
  debug() << " Entree dans updateVelocityForward()";
  updateForceAndVelocity(0.5 * m_global_deltat(),
      /* calcul m_force : */ vars.m_pressure, vars.m_pseudo_viscosity, vars.m_cell_cqs,
      /* calcul m_velocity : */ vars.m_velocity, vars.m_velocity);
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void MahycoModule::
updateVelocityWithoutLagrange(MahycoUpdateVelocityWithoutLagrangeVars& vars)
{
  bool option(getCasModel()->hasReverseOption());
  Real factor(getCasModel()->getReverseParameter());
  
  Real option_real( (Real) option);
  
  VariableNodeReal3InView in_velocity(viewIn(vars.m_velocity_n));
  VariableNodeReal3OutView out_velocity(viewOut(vars.m_velocity));

  PRAGMA_IVDEP
  ENUMERATE_SIMD_NODE(inode, allNodes()){
    SimdNode snode=*inode;
    out_velocity[snode] = in_velocity[snode] * (1. -option_real)
          + option_real * in_velocity[snode] * cos(Pi * m_global_time() * factor);
  }

  vars.m_velocity.synchronize();
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void MahycoModule::
updatePosition(MahycoUpdatePositionVars& vars)
{
  debug() << " Entree dans updatePosition()";
  Real deltat = m_global_deltat();
#if 0
  ENUMERATE_NODE(inode, allNodes()){
    Node node = *inode;
    if (((getSansLagrange()) && (node.nbCell() == 4)) || (!getSansLagrange()))
        vars.m_node_coord[inode] += deltat * vars.m_velocity[inode];
  }
  Real one_over_nbnode = m_dimension == 2 ? .25  : .125 ;
  ENUMERATE_CELL(icell, allCells()){
    Cell cell = * icell;
    Real3 somme = {0. , 0. , 0.};
    for (NodeEnumerator inode(cell.nodes()); inode.hasNext(); ++inode)
      somme += vars.m_node_coord[inode];
    vars.m_cell_coord[cell] = one_over_nbnode * somme;
  }
#else
  auto queue = m_acc_env->newQueue();
  if (!getSansLagrange())
  {
    auto command = makeCommand(queue);

    auto in_velocity    = ax::viewIn(command,vars.m_velocity);
    auto out_node_coord = ax::viewOut(command,vars.m_node_coord);

    command << RUNCOMMAND_ENUMERATE(Node,nid,allNodes()) {
      out_node_coord[nid] += deltat * in_velocity[nid];
    };
  }
  else // getSansLagrange() == true
  {
    ENUMERATE_NODE(inode, allNodes()){
      Node node = *inode;
      if (node.nbCell() == 4) {
        vars.m_node_coord[inode] += deltat * vars.m_velocity[inode];
      }
    }
  }
  {
    Real one_over_nbnode = m_dimension == 2 ? .25  : .125 ;

    auto command = makeCommand(queue);

    auto in_node_coord  = ax::viewIn(command,vars.m_node_coord);
    auto out_cell_coord = ax::viewOut(command,vars.m_cell_coord);
    auto cnc = m_acc_env->connectivityView().cellNode();

    command << RUNCOMMAND_ENUMERATE(Cell,cid,allCells()) {
      Real3 somme = {0. , 0. , 0.};
      for( NodeLocalId nid : cnc.nodes(cid) ){
        somme += in_node_coord[nid];
      }
      out_cell_coord[cid] = one_over_nbnode * somme;
    };
  }
#endif
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void MahycoModule::
applyBoundaryCondition(MahycoApplyBoundaryConditionVars& vars)
{
  debug() << " Entree dans applyBoundaryCondition()";
#if 0
  for (Integer i = 0, nb = getBoundaryCondition().size(); i < nb; ++i){
    String NomBC = getBoundaryCondition()[i]->surface;
    FaceGroup face_group = mesh()->faceFamily()->findGroup(NomBC);
    Real value = getBoundaryCondition()[i]->value();
    TypesMahyco::eBoundaryCondition type = getBoundaryCondition()[i]->type();

    // boucle sur les faces de la surface
    ENUMERATE_FACE(j, face_group){
      Face face = * j;
      Integer nb_node = face.nbNode();

      // boucle sur les noeuds de la face
      for (Integer k = 0; k < nb_node; ++k){
        Node node = face.node(k);
        Real3& velocity = vars.m_velocity[node];

        switch (type){
        case TypesMahyco::VelocityX:
          velocity.x = value;
          break;
        case TypesMahyco::VelocityY:
          velocity.y = value;
          break;
        case TypesMahyco::VelocityZ:
          velocity.z = value;
          break;
        case TypesMahyco::Unknown:
          break;
        }
      }
    }
  }
#else
  auto queue = m_acc_env->newQueue();

  // Pour cette méthode, comme les conditions aux limites sont sur des groupes
  // indépendants (ou alors avec la même valeur si c'est sur les mêmes noeuds),
  // on peut exécuter les noyaux en asynchrone.
  queue.setAsync(true);

  for( auto bc : m_boundary_conditions ) {
    Real value = bc.value;
    TypesMahyco::eBoundaryCondition type = bc.type;

    auto command = makeCommand(queue);
    auto inout_velocity = ax::viewInOut(command,vars.m_velocity);

    command << RUNCOMMAND_ENUMERATE(Node,nid,bc.boundary_nodes) {
      Real3 velocity = inout_velocity[nid];
      switch(type) {
        case TypesMahyco::VelocityX: velocity.x = value; break;
        case TypesMahyco::VelocityY: velocity.y = value; break;
        case TypesMahyco::VelocityZ: velocity.z = value; break;
        case TypesMahyco::Unknown: break;
      }
      inout_velocity[nid] = velocity;
    }; // non-bloquant
  }

  queue.barrier();
#endif
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void MahycoModule::
initGeometricValues(MahycoInitGeometricValuesVars& vars)
{
  debug() << " Entree dans InitGeometricValues() ";
  ENUMERATE_NODE(inode, allNodes()){
      vars.m_node_coord_0[inode] = vars.m_node_coord[inode];
  }
  Real one_over_nbnode = m_dimension == 2 ? .5  : .25 ;
  if ( m_dimension == 3) {
    ENUMERATE_FACE (iFace, allFaces()) {
        Face face = *iFace;
        Real3 face_vec1 = vars.m_node_coord[face.node(2)] - vars.m_node_coord[face.node(0)]; 
        Real3 face_vec2 = vars.m_node_coord[face.node(3)] - vars.m_node_coord[face.node(1)];
        vars.m_face_normal[iFace].x = produit(face_vec1.y, face_vec2.z, face_vec1.z, face_vec2.y);
        vars.m_face_normal[iFace].y = - produit(face_vec2.x, face_vec1.z, face_vec2.z, face_vec1.x);
        vars.m_face_normal[iFace].z = produit(face_vec1.x, face_vec2.y, face_vec1.y, face_vec2.x);
        vars.m_face_normal[iFace] /= vars.m_face_normal[iFace].normL2();
    }
  } else {
    ENUMERATE_FACE (iFace, allFaces()) {
      Face face = *iFace;
      vars.m_face_normal[iFace].x = (vars.m_node_coord[face.node(1)].y - vars.m_node_coord[face.node(0)].y); 
      vars.m_face_normal[iFace].y = (vars.m_node_coord[face.node(1)].x - vars.m_node_coord[face.node(0)].x); 
      vars.m_face_normal[iFace] /= vars.m_face_normal[iFace].normL2();
    }
  }
  ENUMERATE_FACE (iFace, allFaces()) {
      Face face = *iFace;
      vars.m_face_coord[face] = 0.;
      for (Integer inode = 0; inode < face.nbNode(); ++inode) 
        vars.m_face_coord[face] +=  one_over_nbnode * vars.m_node_coord[face.node(inode)];
  }
  ENUMERATE_CELL(icell,allCells()) {
    ENUMERATE_FACE(iface, (*icell).faces()){
      const Face& face = *iface;
      Integer index = iface.index(); 
        vars.m_outer_face_normal[icell][index] = (vars.m_face_coord[face]-vars.m_cell_coord[icell]) 
            / (vars.m_face_coord[face]-vars.m_cell_coord[icell]).normL2();
    }
  }
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void MahycoModule::
computeGeometricValuesIni(MahycoComputeGeometricValuesIniVars& vars)
{
  computeGeometricValuesAux();
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void MahycoModule::
computeGeometricValues(MahycoComputeGeometricValuesVars& vars)
{
  computeGeometricValuesAux();
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void MahycoModule::
computeGeometricValuesAux(MahycoComputeGeometricValuesAuxVars& vars)
{
  debug() << my_rank << " : " << " Entree dans computeGeometricValues() ";
  
  // m_node_coord.synchronize();
  // TODO (BM) 15/03/2022 besoin de synchro meme si updatePosition met à jour m_node_coord sur les allNodes
  //                      A comprendre ...
  if ( m_dimension == 3) {

    // Dans le principe, on synchronise m_node_coord (variable aux noeuds)
    // puis on appelle la lambda sur tous les Cell de allCells()
    m_acc_env->vsyncMng()->syncAndCompute(
	vars.m_node_coord,     // ----------------------------------> variable à synchroniser avant les calculs
	allCells(),       // ----------------------------------> groupe d'items sur lequel on itère
	[&](CellGroup cell_group, RunQueue* async_queue) // ---> définition du calcul sur un CellGroup
        {
          auto command = makeCommand(async_queue);
        
          auto in_node_coord = ax::viewIn(command,vars.m_node_coord);
          auto out_cell_cqs = ax::viewInOut(command,vars.m_cell_cqs);
        
          auto cnc = m_acc_env->connectivityView().cellNode();
        
          command << RUNCOMMAND_ENUMERATE(Cell, cid, cell_group){
            // Recopie les coordonnées locales (pour le cache)
            Real3 coord[8];
            Int32 index=0;
            for( NodeLocalId nid : cnc.nodes(cid) ){
              coord[index]=in_node_coord[nid];
              ++index;
            }
            // Calcul les coordonnées des centres des faces
            Real3 face_coord[6] = {
              0.25 * (coord[0] + coord[3] + coord[2] + coord[1]),
              0.25 * (coord[0] + coord[4] + coord[7] + coord[3]),
              0.25 * (coord[0] + coord[1] + coord[5] + coord[4]),
              0.25 * (coord[4] + coord[5] + coord[6] + coord[7]),
              0.25 * (coord[1] + coord[2] + coord[6] + coord[5]),
              0.25 * (coord[2] + coord[3] + coord[7] + coord[6])
            };
        
            // Calcule les résultantes aux sommets
            computeCQs(coord, face_coord, out_cell_cqs[cid]);
          };
        }
	);

  } else {
    auto queue_synchronize = m_acc_env->refQueueAsync();
    m_acc_env->vsyncMng()->globalSynchronize(queue_synchronize, vars.m_node_coord);

    Real3 npc[5];
    ENUMERATE_CELL(icell, allCells()){
      Cell cell = * icell;
      // Recopie les coordonnées locales (pour le cache)
      Real3 coord[8];
      for (NodeEnumerator inode(cell.nodes()); inode.index() < cell.nbNode(); ++inode) {
        coord[inode.index()] = vars.m_node_coord[inode];
      }
      coord[4] = coord[0];
      for (NodeEnumerator inode(cell.nodes()); inode.index() < cell.nbNode(); ++inode) {
        npc[inode.index()+1].x = 0.5 * (coord[inode.index()+1].y -  coord[inode.index()].y);
        npc[inode.index()+1].y = 0.5 * (coord[inode.index()].x -  coord[inode.index()+1].x);
        // npc[inode.index()+1] = npc[inode.index()+1] / npc[inode.index()+1].normL2();
      }
      npc[0] = npc[4];
      for (Integer ii = 0; ii < 4; ++ii) {
        vars.m_cell_cqs[icell][ii] = npc[ii+1] + npc[ii]; 
      }
    }  
 }
//   m_cell_cqs.synchronize(); // TODO : pourquoi synchronize ?
 
  if (getLongueurCaracteristique() == "faces-opposees")
  {
#if 0
    ENUMERATE_CELL(icell, allCells()){
      Cell cell = * icell;    
      // Calcule le volume de la maille
      {
        Real volume = 0.;

        for (Integer inode = 0; inode < cell.nbNode(); ++inode) {
          volume += math::dot(vars.m_node_coord[cell.node(inode)], vars.m_cell_cqs[icell] [inode]);
          // pinfo() << cell.localId() << " coor " << m_node_coord[cell.node(inode)] << " et " << m_cell_cqs[icell] [inode];
           
          // TODO : bien s'assurer que m_node_volume ne sert à rien
          // m_node_volume[cell.node(inode)] += volume;
        }
        volume /= m_dimension;

        vars.m_cell_volume[cell] = volume;
      }
      // Calcule la longueur caractéristique de la maille.
      {
        // Recopie les coordonnées locales (pour le cache)
        Real3 coord[8];
        for (NodeEnumerator inode(cell.nodes()); inode.index() < 8; ++inode) {
          coord[inode.index()] = vars.m_node_coord[inode];
        }
        // Calcul les coordonnées des centres des faces
        Real3 face_coord[6];
        face_coord[0] = 0.25 * (coord[0] + coord[3] + coord[2] + coord[1]);
        face_coord[1] = 0.25 * (coord[0] + coord[4] + coord[7] + coord[3]);
        face_coord[2] = 0.25 * (coord[0] + coord[1] + coord[5] + coord[4]);
        face_coord[3] = 0.25 * (coord[4] + coord[5] + coord[6] + coord[7]);
        face_coord[4] = 0.25 * (coord[1] + coord[2] + coord[6] + coord[5]);
        face_coord[5] = 0.25 * (coord[2] + coord[3] + coord[7] + coord[6]);

        Real3 median1 = face_coord[0] - face_coord[3];
        Real3 median2 = face_coord[2] - face_coord[5];
        Real3 median3 = face_coord[1] - face_coord[4];
        Real d1 = median1.normL2();
        Real d2 = median2.normL2();
        Real d3 = median3.normL2();

        Real dx_numerator = d1 * d2 * d3;
        Real dx_denominator = d1 * d2 + d1 * d3 + d2 * d3;
        vars.m_caracteristic_length[icell] = dx_numerator / dx_denominator;
      }
    } 
#else
    {
      auto queue = m_acc_env->newQueue();
      auto command = makeCommand(queue);

      auto in_node_coord = ax::viewIn(command,vars.m_node_coord);
      auto in_cell_cqs   = ax::viewIn(command,vars.m_cell_cqs);
      auto out_cell_volume_g        = ax::viewOut(command,vars.m_cell_volume.globalVariable()); 
      auto out_caracteristic_length = ax::viewOut(command,vars.m_caracteristic_length);
      
      auto cnc = m_acc_env->connectivityView().cellNode();

      // NOTE : on ne peut pas utiliser un membre sur accélérateur (ex : m_dimension), 
      // cela revient à utiliser this->m_dimension avec this pointeur illicite
      Real inv_dim = 1./m_dimension;

      command << RUNCOMMAND_ENUMERATE(Cell, cid, allCells()){

        // Calcule le volume de la maille
        Span<const Real3> cell_cqs = in_cell_cqs[cid];
        Real volume = 0;
        
	// Recopie les coordonnées locales (pour le cache)
        Real3 coord[8];

        Int64 index=0;
        for( NodeLocalId nid : cnc.nodes(cid) ){
          volume += math::dot(in_node_coord[nid],  cell_cqs[index]);
          coord[index]=in_node_coord[nid];
          ++index;
        }
        volume *= inv_dim;
        out_cell_volume_g[cid] = volume;

        // Calcule la longueur caractéristique de la maille.
        {
          // Calcul les coordonnées des centres des faces
          Real3 face_coord[6];
          face_coord[0] = 0.25 * (coord[0] + coord[3] + coord[2] + coord[1]);
          face_coord[1] = 0.25 * (coord[0] + coord[4] + coord[7] + coord[3]);
          face_coord[2] = 0.25 * (coord[0] + coord[1] + coord[5] + coord[4]);
          face_coord[3] = 0.25 * (coord[4] + coord[5] + coord[6] + coord[7]);
          face_coord[4] = 0.25 * (coord[1] + coord[2] + coord[6] + coord[5]);
          face_coord[5] = 0.25 * (coord[2] + coord[3] + coord[7] + coord[6]);

          Real3 median1 = face_coord[0] - face_coord[3];
          Real3 median2 = face_coord[2] - face_coord[5];
          Real3 median3 = face_coord[1] - face_coord[4];
          Real d1 = median1.normL2();
          Real d2 = median2.normL2();
          Real d3 = median3.normL2();

          Real dx_numerator = d1 * d2 * d3;
          Real dx_denominator = d1 * d2 + d1 * d3 + d2 * d3;
          out_caracteristic_length[cid] = dx_numerator / dx_denominator;
        }
      };
    }
#endif
  }
  else if (getLongueurCaracteristique() == "racine-cubique-volume")
  {
    Real racine = m_dimension == 2 ? .5  : 1./3. ;
    // Calcul des volumes aux mailles puis longueur caractéristique
    // Attention, m_node_volume n'est plus calculé car n'est pas utilisé
    {
      auto queue = m_acc_env->newQueue();
      auto command = makeCommand(queue);

      auto in_node_coord = ax::viewIn(command,vars.m_node_coord);
      auto in_cell_cqs   = ax::viewIn(command,vars.m_cell_cqs);
      auto out_cell_volume_g        = ax::viewOut(command,vars.m_cell_volume.globalVariable()); 
      auto out_caracteristic_length = ax::viewOut(command,vars.m_caracteristic_length);
      
      auto cnc = m_acc_env->connectivityView().cellNode();

      // NOTE : on ne peut pas utiliser un membre sur accélérateur (ex : m_dimension), 
      // cela revient à utiliser this->m_dimension avec this pointeur illicite
      Real inv_dim = 1./m_dimension;

      command << RUNCOMMAND_ENUMERATE(Cell, cid, allCells()){

        // Calcule le volume de la maille
        Span<const Real3> cell_cqs = in_cell_cqs[cid];
        Real volume = 0;

        Int64 index=0;
        for( NodeLocalId nid : cnc.nodes(cid) ){
          volume += math::dot(in_node_coord[nid],  cell_cqs[index]);
          ++index;
        }
        volume *= inv_dim;
        out_cell_volume_g[cid] = volume;

        // Calcule la longueur caractéristique de la maille.
        out_caracteristic_length[cid] = math::pow(volume, racine);
      };
    }
  }
  else
  {
    info() << " pas de longeur caractéritique definie dans le .arc " << getLongueurCaracteristique();
    subDomain()->timeLoopMng()->stopComputeLoop(true);
  }

  m_acc_env->multiEnvMng()->checkMultiEnvGlobalCellId(); // Vérifie que m_acc_env->multiEnvMng()->globalCell() est correct

  // maille mixte
  // moyenne sur la maille
  auto menv_queue = m_acc_env->multiEnvMng()->multiEnvQueue();
  ENUMERATE_ENV(ienv, mm) {
    IMeshEnvironment* env = *ienv;

    // Pour les mailles impures (mixtes), liste des indices valides 
    Span<const Int32> in_imp_idx(env->impureEnvItems().valueIndexes());
    Integer nb_imp = in_imp_idx.size();

    // Des sortes de vues sur les valeurs impures pour l'environnement env
    Span<Real> out_cell_volume(envView(m_cell_volume, env));
    Span<const Real> in_fracvol(envView(m_fracvol, env));
    Span<const Integer> in_global_cell(envView(m_acc_env->multiEnvMng()->globalCell(), env));

    // Les kernels sont lancés de manière asynchrone environnement par environnement
    auto command = makeCommand(menv_queue->queue(env->id()));

    auto in_cell_volume_g  = ax::viewIn(command,vars.m_cell_volume.globalVariable()); 

    command << RUNCOMMAND_LOOP1(iter,nb_imp) {
      auto imix = in_imp_idx[iter()[0]]; // iter()[0] \in [0,nb_imp[
      CellLocalId cid(in_global_cell[imix]); // on récupère l'identifiant de la maille globale
      out_cell_volume[imix] = in_fracvol[imix] * in_cell_volume_g[cid];
    };
  }

  menv_queue->waitAllQueues();
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void MahycoModule::
updateDensity(MahycoUpdateDensityVars& vars)
{
  if (getSansLagrange()) return;
  debug() << my_rank << " : " << " Entree dans updateDensity() ";

  // On lance de manière asynchrone les calculs des valeurs globales/pures sur GPU sur queue_glob
  auto queue_glob = m_acc_env->newQueue();
  queue_glob.setAsync(true);
  {
    auto command = makeCommand(queue_glob);

    Real inv_deltat = 1.0/m_global_deltat(); // ne pas appeler de méthodes de this dans le kernel

    auto in_cell_mass_g   = ax::viewIn(command, vars.m_cell_mass.globalVariable());
    auto in_cell_volume_g = ax::viewIn(command, vars.m_cell_volume.globalVariable());
    auto in_density_n_g   = ax::viewIn(command, vars.m_density_n.globalVariable());

    auto iou_density_g     = ax::viewInOut(command, vars.m_density.globalVariable());
    auto iou_tau_density_g = ax::viewInOut(command, vars.m_tau_density.globalVariable());

    auto out_div_u = ax::viewOut(command, vars.m_div_u);

    command << RUNCOMMAND_ENUMERATE(Cell, cid, allCells()){

      Real new_density, tau_density;
      compute_density_tau(in_density_n_g[cid], 
          in_cell_mass_g[cid], in_cell_volume_g[cid], 
          /*OUT*/new_density, /*OUT*/tau_density);

      iou_density_g[cid] = new_density;
      iou_tau_density_g[cid] = tau_density;

      // divergence de la vitesse mode A1
      out_div_u[cid] =
        inv_deltat  * ( 1.0 / iou_density_g[cid] - 1.0 / in_density_n_g[cid] )
        / iou_tau_density_g[cid];
    };
  }
  // Pendant ce temps, calcul sur GPU sur la queue_glob

  auto menv_queue = m_acc_env->multiEnvMng()->multiEnvQueue();
#if 0
  ENUMERATE_ENV(ienv,mm){
    IMeshEnvironment* env = *ienv;
    ENUMERATE_ENVCELL(ienvcell,env){
      EnvCell ev = *ienvcell;
      Cell cell = ev.globalCell();
       // info() << my_rank << " : " << cell.uniqueId() << " " << m_cell_volume[ev];
       Real new_density = m_cell_mass[ev] / m_cell_volume[ev];
       // nouvelle density
       m_density[ev] = new_density;
       // volume specifique de l'environnement au temps n+1/2
       m_tau_density[ev] = 
        0.5 * (1.0 / m_density_n[ev] + 1.0 / m_density[ev]);
        
    }
  }
#else
  // Les calculs des valeurs mixtes sur les environnements sont indépendants 
  // les uns des autres mais ne dépendent pas non plus des valeurs globales/pures
  // Rappel : menv_queue->queue(*) sont des queues asynchrones indépendantes
  ENUMERATE_ENV(ienv,mm){
    IMeshEnvironment* env = *ienv;

    auto command = makeCommand(menv_queue->queue(env->id()));

    // Pour les mailles impures (mixtes), liste des indices valides 
    Span<const Int32> in_imp_idx(env->impureEnvItems().valueIndexes());
    Integer nb_imp = in_imp_idx.size();

    Span<const Real> in_cell_volume(envView(vars.m_cell_volume, env));
    Span<const Real> in_cell_mass(envView(vars.m_cell_mass, env));
    Span<const Real> in_density_n(envView(vars.m_density_n, env));

    Span<Real> out_density(envView(vars.m_density, env));
    Span<Real> out_tau_density(envView(vars.m_tau_density, env));

    command << RUNCOMMAND_LOOP1(iter, nb_imp) {
      auto imix = in_imp_idx[iter()[0]]; // iter()[0] \in [0,nb_imp[

      compute_density_tau(in_density_n[imix], 
          in_cell_mass[imix], in_cell_volume[imix], 
          /*OUT*/out_density[imix], /*OUT*/out_tau_density[imix]);

    }; // asynchrone par rapport au CPU et aux autres queues
  }
#endif
  queue_glob.barrier();
  menv_queue->waitAllQueues();
  
//   m_density.synchronize();
//   m_tau_density.synchronize();
//   m_div_u.synchronize();
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void MahycoModule::
updateEnergyAndPressure(MahycoUpdateEnergyAndPressureVars& vars)
{
  m_acc_env->multiEnvMng()->checkMultiEnvGlobalCellId();

  if (getWithNewton()) 
    updateEnergyAndPressurebyNewton();
  else
    updateEnergyAndPressureforGP();  
   
#if 0
  // maille mixte
  // moyenne sur la maille
  CellToAllEnvCellConverter all_env_cell_converter(mm);
  ENUMERATE_CELL(icell, allCells()){
    Cell cell = * icell;
    AllEnvCell all_env_cell = all_env_cell_converter[cell];
    if (all_env_cell.nbEnvironment() !=1) {
      vars.m_internal_energy[cell] = 0.;
      ENUMERATE_CELL_ENVCELL(ienvcell,all_env_cell) {
        EnvCell ev = *ienvcell;
        vars.m_internal_energy[cell] += vars.m_mass_fraction[ev] * vars.m_internal_energy[ev];
      }
    }
  }
#else
  // Moyennes reportées dans updateEnergyAndPressurebyNewton() et updateEnergyAndPressureforGP()
#endif
  if (!getWithProjection()) {
    // Calcul de la Pression si on ne fait pas de projection 
    for( Integer i=0,n=getEnvironment().size(); i<n; ++i ) {
        IMeshEnvironment* ienv = mm->environments()[i];
        // Calcul de la pression et de la vitesse du son
        getEnvironment()[i].eosModel()->applyEOS(ienv);
    }
    computePressionMoyenne();
  }
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void MahycoModule::
updateEnergyAndPressurebyNewton(MahycoUpdateEnergyAndPressurebyNewtonVars& vars)
{
  if (getSansLagrange()) return;
    debug() << " Entree dans updateEnergyAndPressure()";
    bool csts = getSchemaCsts();
    bool pseudo_centree = getPseudoCentree();
    // Calcul de l'énergie interne
    if (!csts) {
        ENUMERATE_ENV(ienv,mm){
        IMeshEnvironment* env = *ienv;
        ENUMERATE_ENVCELL(ienvcell,env){
            EnvCell ev = *ienvcell;
            Real pseudo(0.);
            if (pseudo_centree &&
            ((vars.m_pseudo_viscosity_n[ev] + vars.m_pseudo_viscosity[ev]) * (1.0 / vars.m_density[ev] - 1.0 / vars.m_density_n[ev]) < 0.))
            pseudo = 0.5 * (vars.m_pseudo_viscosity[ev] + vars.m_pseudo_viscosity_n[ev]);
            if (!pseudo_centree &&
                (vars.m_pseudo_viscosity[ev] * (1.0 / vars.m_density[ev] - 1.0 / vars.m_density_n[ev]) < 0.))
            pseudo = vars.m_pseudo_viscosity[ev];
            
            double rn  = vars.m_density_n[ev];
            double pn  = vars.m_pressure_n[ev];
            double qnn1 = pseudo;
            double rn1 = vars.m_density[ev];
            double en  = vars.m_internal_energy_n[ev];
            // les iterations denewton
            double epsilon = getTreshold();
            double itermax = 50;
            double enew=0, e=en, p=0., c=0., dpde;
            int i = 0;
        
            while(i<itermax && abs(fvnr(e, p, dpde, en, qnn1, pn, rn1, rn))>=epsilon)
            {
                vars.m_internal_energy[ev] = e;
                getEnvironment()[env->id()].eosModel()->applyOneCellEOS(env, ev);
                p = vars.m_pressure[ev];
                c = vars.m_sound_speed[ev];
                dpde = vars.m_dpde[ev];
                enew = e - fvnr(e, p, dpde, en, qnn1, pn, rn1, rn) / fvnrderiv(e, dpde, rn1, rn);
                e = enew;
                i++;
            }
            vars.m_internal_energy[ev] = e;
            vars.m_sound_speed[ev] = c;
            vars.m_pressure[ev] = p;
        }
        }
        // maille mixte
        // moyenne sur la maille
        // Précedemment calculé dans updateEnergyAndPressure()
        CellToAllEnvCellConverter all_env_cell_converter(mm);
        ENUMERATE_CELL(icell, allCells()){
        Cell cell = * icell;
        AllEnvCell all_env_cell = all_env_cell_converter[cell];
        if (all_env_cell.nbEnvironment() !=1) {
            vars.m_internal_energy[cell] = 0.;
            ENUMERATE_CELL_ENVCELL(ienvcell,all_env_cell) {
            EnvCell ev = *ienvcell;
            vars.m_internal_energy[cell] += vars.m_mass_fraction[ev] * vars.m_internal_energy[ev];
            }
        }
        }
    } else {
        ENUMERATE_ENV(ienv,mm){
        IMeshEnvironment* env = *ienv;
        ENUMERATE_ENVCELL(ienvcell,env){
            EnvCell ev = *ienvcell;
            Cell cell=ev.globalCell();
            Real cqs_v_nplus1(0.);
            Real cqs_v_n(0.);
            Real cqs_delta_v(0.);
            Real cqs_v_old_n(0.);
            for (Integer inode = 0; inode < cell.nbNode(); ++inode) {
            cqs_v_nplus1 += math::dot(vars.m_velocity[cell.node(inode)], vars.m_cell_cqs[cell] [inode])
                * m_global_deltat();
            cqs_v_n += math::dot(vars.m_velocity[cell.node(inode)], vars.m_cell_cqs_n[cell] [inode])
                * m_global_deltat();
            cqs_delta_v +=  math::dot(vars.m_velocity[cell.node(inode)] - vars.m_velocity_n[cell.node(inode)], vars.m_cell_cqs_n[cell] [inode])
            * (m_global_deltat() - m_global_old_deltat());
            cqs_v_old_n += math::dot(vars.m_velocity_n[cell.node(inode)], vars.m_cell_cqs_n[cell] [inode])
            * m_global_old_deltat();
            }
            double pn  = vars.m_pressure_n[ev];
            double qn = vars.m_pseudo_viscosity_n[ev];
            double qn1 = vars.m_pseudo_viscosity[ev];
            double m   = vars.m_cell_mass[ev];
            double en  = vars.m_internal_energy_n[ev];
            double cn1 = cqs_v_nplus1;
            double cn = cqs_v_n;
            double cdn = cqs_delta_v;
            double cdon = 0. ;
            double qnm1 = vars.m_pseudo_viscosity_nmoins1[ev]; 
            // les iterations de newton
            double epsilon = getThreshold();
            double itermax = 50;
            double enew=0, e=en, p=0., c=0., dpde;
            int i = 0;
        
            while(i<itermax && abs(f(e, p, dpde, en, qn, pn, cn1, cn, m, qn1, cdn, cdon, qnm1))>=epsilon)
            {
                vars.m_internal_energy[ev] = e;
                getEnvironment()[env->id()].eosModel()->applyOneCellEOS(env, ev);
                p = vars.m_pressure[ev];
                c = vars.m_sound_speed[ev];
                dpde = vars.m_dpde[ev];
                enew = e - f(e, p, dpde, en, qn, pn, cn1, cn, m, qn1, cdn, cdon, qnm1) / fderiv(e, p, dpde, cn1, m);
                e = enew;
                i++;
            }
            vars.m_internal_energy[ev] = e;
            vars.m_sound_speed[ev] = c;
            vars.m_pressure[ev] = p;
        }
        }
        // maille mixte
        // moyenne sur la maille
        // Précedemment calculé dans updateEnergyAndPressure()
        CellToAllEnvCellConverter all_env_cell_converter(mm);
        ENUMERATE_CELL(icell, allCells()){
        Cell cell = * icell;
        AllEnvCell all_env_cell = all_env_cell_converter[cell];
        if (all_env_cell.nbEnvironment() !=1) {
            vars.m_internal_energy[cell] = 0.;
            ENUMERATE_CELL_ENVCELL(ienvcell,all_env_cell) {
            EnvCell ev = *ienvcell;
            vars.m_internal_energy[cell] += vars.m_mass_fraction[ev] * vars.m_internal_energy[ev];
            }
        }
        }
    }
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void MahycoModule::
updateEnergyAndPressureforGP(MahycoUpdateEnergyAndPressureforGPVars& vars)
{
  if (getSansLagrange()) return;
  debug() << " Entree dans updateEnergyAndPressure()";
  bool csts = getSchemaCsts();
  bool pseudo_centree = getPseudoCentree();
  // Calcul de l'énergie interne
  if (!csts) {
#if 0
    ENUMERATE_ENV(ienv,mm){
      IMeshEnvironment* env = *ienv;
      Real adiabatic_cst = getEnvironment()[env->id()].eosModel()->getAdiabaticCst(env);
      ENUMERATE_ENVCELL(ienvcell,env){
        EnvCell ev = *ienvcell;
        Real pseudo(0.);
        Cell cell = ev.globalCell();
        if (pseudo_centree &&
            ((vars.m_pseudo_viscosity_n[ev] + vars.m_pseudo_viscosity[ev]) * (1.0 / vars.m_density[ev] - 1.0 / vars.m_density_n[ev]) < 0.))
          pseudo = 0.5 * (vars.m_pseudo_viscosity[ev] + vars.m_pseudo_viscosity_n[ev]);
        if (!pseudo_centree &&
            (vars.m_pseudo_viscosity[ev] * (1.0 / vars.m_density[ev] - 1.0 / vars.m_density_n[ev]) < 0.))
          pseudo = vars.m_pseudo_viscosity[ev];
          
        Real denom_accrois_nrj(1 + 0.5 * (adiabatic_cst - 1.0) *
                               vars.m_density[ev] *
                               (1.0 / vars.m_density[ev] -
                                1.0 / vars.m_density_n[ev]));
        Real numer_accrois_nrj(vars.m_internal_energy_n[ev] -
                               (0.5 * vars.m_pressure[ev] + pseudo) *
                               (1.0 / vars.m_density[ev] - 1.0 / vars.m_density_n[ev]));
        vars.m_internal_energy[ev] = numer_accrois_nrj / denom_accrois_nrj;
      }
    }
#else
    // Traitements dépendants des mailles pures/globales 
    // puis des mailles mixtes qui vont mettre à jour les valeurs globales

    auto queue = m_acc_env->newQueue();
    // Traitement des mailles pures via les tableaux .globalVariable()
    {
      auto command = makeCommand(queue);

      auto in_env_id               = ax::viewIn(command, m_acc_env->multiEnvMng()->envId());
      auto in_adiabatic_cst_env    = ax::viewIn(command, vars.m_adiabatic_cst_env);

      auto in_pseudo_viscosity_n   = ax::viewIn(command, vars.m_pseudo_viscosity_n.globalVariable()); 
      auto in_pseudo_viscosity     = ax::viewIn(command, vars.m_pseudo_viscosity.globalVariable());
      auto in_density_n            = ax::viewIn(command, vars.m_density_n.globalVariable()); 
      auto in_density              = ax::viewIn(command, vars.m_density.globalVariable()); 
      auto in_pressure             = ax::viewIn(command, vars.m_pressure.globalVariable()); 
      auto in_internal_energy_n    = ax::viewIn(command, vars.m_internal_energy_n.globalVariable());

      auto out_internal_energy     = ax::viewOut(command, vars.m_internal_energy.globalVariable());

      command << RUNCOMMAND_ENUMERATE(Cell,cid,allCells()) {
        out_internal_energy[cid] = 0.; // initialisation pour une future maj des mailles moyennes (globales)
        Integer env_id = in_env_id[cid]; // id de l'env si maille pure, <0 sinon
        if (env_id>=0) { // vrai ssi cid maille pure
          Real adiabatic_cst = in_adiabatic_cst_env(env_id);
          CellLocalId ev_cid(cid); // exactement même valeur mais met en évidence le caractère "environnement" de la maille pure
          out_internal_energy[ev_cid] = compute_eint(pseudo_centree, adiabatic_cst,
              in_pseudo_viscosity_n[ev_cid], in_pseudo_viscosity[ev_cid],
              in_density_n[ev_cid], in_density[ev_cid], 
              in_pressure[ev_cid], in_internal_energy_n[ev_cid]);
        }
      }; // non-bloquant
    }

    // Traitement des mailles mixtes via les envView(...)

    ENUMERATE_ENV(ienv,mm){
      IMeshEnvironment* env = *ienv;

      // Les kernels sont lancés environnement par environnement les uns après les autres
      auto command = makeCommand(queue);

      Span<const Real> in_pseudo_viscosity_n(envView(vars.m_pseudo_viscosity_n, env)); 
      Span<const Real> in_pseudo_viscosity  (envView(vars.m_pseudo_viscosity, env));
      Span<const Real> in_density_n         (envView(vars.m_density_n, env)); 
      Span<const Real> in_density           (envView(vars.m_density, env)); 
      Span<const Real> in_pressure          (envView(vars.m_pressure, env)); 
      Span<const Real> in_internal_energy_n (envView(vars.m_internal_energy_n, env));
      Span<const Real> in_mass_fraction     (envView(vars.m_mass_fraction, env));
      Span<const Integer> in_global_cell    (envView(m_acc_env->multiEnvMng()->globalCell(), env));

      Span<Real> out_internal_energy        (envView(vars.m_internal_energy, env));
      auto inout_internal_energy_g = ax::viewInOut(command, vars.m_internal_energy.globalVariable());

      Real adiabatic_cst = m_adiabatic_cst_env(env->id());

      // Pour les mailles impures (mixtes), liste des indices valides 
      Span<const Int32> in_imp_idx(env->impureEnvItems().valueIndexes());
      Integer nb_imp = in_imp_idx.size();

      command << RUNCOMMAND_LOOP1(iter, nb_imp) {
	auto imix = in_imp_idx[iter()[0]]; // iter()[0] \in [0,nb_imp[
        CellLocalId cid(in_global_cell[imix]); // on récupère l'identifiant de la maille globale

        Real internal_energy = compute_eint(pseudo_centree, adiabatic_cst,
            in_pseudo_viscosity_n[imix], in_pseudo_viscosity[imix],
            in_density_n[imix], in_density[imix], 
            in_pressure[imix], in_internal_energy_n[imix]);

        out_internal_energy[imix] = internal_energy;

        // Maj de la grandeur global (ie moyenne)
        // inout_internal_energy_g[cid] a été initialisée à 0 par le kernel sur les grandeurs globales
        inout_internal_energy_g[cid] += in_mass_fraction[imix] * internal_energy;
      }; // bloquant
    }
#endif
  } else {
    ENUMERATE_ENV(ienv,mm){
      IMeshEnvironment* env = *ienv;
      Real adiabatic_cst = getEnvironment()[env->id()].eosModel()->getAdiabaticCst();
      ENUMERATE_ENVCELL(ienvcell,env){
        EnvCell ev = *ienvcell;
        Cell cell = ev.globalCell();
        Real cqs_v_nplus1(0.);
        Real cqs_v_n(0.);
        Real cqs_delta_v(0.);
        Real cqs_v_old_n(0.);
        for (Integer inode = 0; inode < cell.nbNode(); ++inode) {
          cqs_v_nplus1 += math::dot(vars.m_velocity[cell.node(inode)], vars.m_cell_cqs[cell] [inode])
            * m_global_deltat();
          cqs_v_n += math::dot(vars.m_velocity[cell.node(inode)], vars.m_cell_cqs_n[cell] [inode])
            * m_global_deltat();
          cqs_delta_v +=  math::dot(vars.m_velocity[cell.node(inode)] - vars.m_velocity_n[cell.node(inode)], vars.m_cell_cqs_n[cell] [inode])
            * (m_global_deltat() - m_global_old_deltat());
          cqs_v_old_n += math::dot(vars.m_velocity_n[cell.node(inode)], vars.m_cell_cqs_n[cell] [inode])
            * m_global_old_deltat();
        }
        Real denom_accrois_nrj(1 + 0.5 * (adiabatic_cst - 1.0)
                               * vars.m_density[ev] * cqs_v_nplus1 / vars.m_cell_mass[ev]) ;
        Real numer_accrois_nrj(vars.m_internal_energy[ev]
                               - (0.5 * (vars.m_pressure_n[ev] + vars.m_pseudo_viscosity_n[ev])
                                  * cqs_v_n / vars.m_cell_mass[ev])
                               - (0.5 * vars.m_pseudo_viscosity[ev]
                                  * cqs_v_nplus1 / vars.m_cell_mass[ev])
                               + (0.25 * (vars.m_pressure_n[ev] + vars.m_pseudo_viscosity_n[ev]) 
                                  * cqs_delta_v / vars.m_cell_mass[ev])
                               - (0.5 * (vars.m_pseudo_viscosity_n[ev] - vars.m_pseudo_viscosity_nmoins1[ev]) 
                                  * cqs_v_old_n / vars.m_cell_mass[ev])
                               );

        vars.m_internal_energy[ev] = numer_accrois_nrj / denom_accrois_nrj;
      }
    }

    // maille mixte
    // moyenne sur la maille
    // Précedemment calculé dans updateEnergyAndPressure()
    CellToAllEnvCellConverter all_env_cell_converter(mm);
    ENUMERATE_CELL(icell, allCells()){
      Cell cell = * icell;
      AllEnvCell all_env_cell = all_env_cell_converter[cell];
      if (all_env_cell.nbEnvironment() !=1) {
        vars.m_internal_energy[cell] = 0.;
        ENUMERATE_CELL_ENVCELL(ienvcell,all_env_cell) {
          EnvCell ev = *ienvcell;
          vars.m_internal_energy[cell] += vars.m_mass_fraction[ev] * vars.m_internal_energy[ev];
        }
      }
    }
  }
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void MahycoModule::
computeAveragePressure(MahycoComputeAveragePressureVars& vars)
{
  if (getSansLagrange()) return;
  debug() << " Entree dans computePressionMoyenne() ";
  // maille mixte
  // moyenne sur la maille
#if 0
  CellToAllEnvCellConverter all_env_cell_converter(mm);
  ENUMERATE_CELL(icell, allCells()){
    Cell cell = * icell;
    AllEnvCell all_env_cell = all_env_cell_converter[cell];
    if (all_env_cell.nbEnvironment() !=1) {
      vars.m_pressure[cell] = 0.;
      vars.m_sound_speed[icell] = 1.e-20;
      ENUMERATE_CELL_ENVCELL(ienvcell,all_env_cell) {
        EnvCell ev = *ienvcell;        
        vars.m_pressure[cell] += vars.m_fracvol[ev] * vars.m_pressure[ev];
        vars.m_sound_speed[cell] = std::max(vars.m_sound_speed[ev], vars.m_sound_speed[cell]);
      }
    }
  }
#else
  m_acc_env->multiEnvMng()->checkMultiEnvGlobalCellId();

  // Pas très efficace mais on va lancer un kernel sur tout le maillage pour
  // ne sélectionner que les mailles mixtes et initialiser les grandeus
  // moyennes
  // puis on va calculer les grandeurs partielles environnement par
  // environnement et mettre à jour au fur et à mesure les grandeurs moy.

  // Toutes les étapes doivent se faire les unes après les autres d'où une
  // queue unique
  auto queue = m_acc_env->newQueue();
  {
    auto command = makeCommand(queue);

    auto in_env_id       = ax::viewIn(command, m_acc_env->multiEnvMng()->envId());
    auto out_pressure    = ax::viewOut(command, vars.m_pressure.globalVariable());
    auto out_sound_speed = ax::viewOut(command, vars.m_sound_speed.globalVariable());

    command << RUNCOMMAND_ENUMERATE(Cell,cid,allCells()) {
      Integer env_id = in_env_id[cid]; // id de l'env si maille pure, <0 sinon

      if (env_id<0) { // vrai si maille mixte (nbEnv() == -env_id-1)
        out_pressure[cid] = 0.;
        out_sound_speed[cid] = 1.e-20;
      }
    };
  }
 
  ENUMERATE_ENV(ienv,mm){
    IMeshEnvironment* env = *ienv;

    // Les kernels sont lancés environnement par environnement les uns après les autres
    auto command = makeCommand(queue);
    
    Span<const Integer> in_global_cell    (envView(m_acc_env->multiEnvMng()->globalCell(), env));
    Span<const Real>    in_fracvol        (envView(vars.m_fracvol,     env)); 
    Span<const Real>    in_pressure       (envView(vars.m_pressure,    env)); 
    Span<const Real>    in_sound_speed    (envView(vars.m_sound_speed, env)); 

    auto inout_pressure    = ax::viewInOut(command, vars.m_pressure.globalVariable());
    auto inout_sound_speed = ax::viewInOut(command, vars.m_sound_speed.globalVariable());

    // Pour les mailles impures (mixtes), liste des indices valides 
    Span<const Int32> in_imp_idx(env->impureEnvItems().valueIndexes());
    Integer nb_imp = in_imp_idx.size();

    command << RUNCOMMAND_LOOP1(iter, nb_imp) {
      auto imix = in_imp_idx[iter()[0]]; // iter()[0] \in [0,nb_imp[
      CellLocalId cid(in_global_cell[imix]); // on récupère l'identifiant de la maille globale

      inout_pressure[cid] += in_fracvol[imix] * in_pressure[imix];
      inout_sound_speed[cid] = math::max(in_sound_speed[imix], inout_sound_speed[cid]);
    };
  }
#endif
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void MahycoModule::
prepareFaceGroupForBc(MahycoPrepareFaceGroupForBcVars& vars)
{
  Int32UniqueArray face_x0_lid;
  Int32UniqueArray face_y0_lid;
  Int32UniqueArray face_z0_lid;
  Int32UniqueArray face_xmax_lid;
  Int32UniqueArray face_ymax_lid;
  Int32UniqueArray face_zmax_lid;
  Real3 maxCoor= {-1. , -1. , -1.};
  ENUMERATE_NODE(inode, allNodes()){
      maxCoor.x = std::max(maxCoor.x, vars.m_node_coord[inode].x);
      maxCoor.y = std::max(maxCoor.y, vars.m_node_coord[inode].y);
      maxCoor.z = std::max(maxCoor.z, vars.m_node_coord[inode].z);
  }
  ENUMERATE_FACE(iface, allFaces()){
     const Face& face = *iface;
     Integer face_local_id = face.localId();
     for (Integer idir = 0 ; idir <  mesh()->dimension() ; ++idir) {
         vars.m_is_dir_face[face][idir] = false;
     }
     bool flag_x0(true);
     bool flag_y0(true);
     bool flag_z0(true);
     bool flag_xmax(true);
     bool flag_ymax(true);
     bool flag_zmax(true);
     for (NodeEnumerator inode(face.nodes()); inode.index() < face.nbNode(); ++inode) {
         if (vars.m_node_coord[inode].x > getTreshold())  flag_x0 = false;
         if (vars.m_node_coord[inode].y > getTreshold())  flag_y0 = false;
         if (vars.m_node_coord[inode].z > getTreshold())  flag_z0 = false;
         if (math::abs(vars.m_node_coord[inode].x - maxCoor.x) > getTreshold()) flag_xmax = false;
         if (math::abs(vars.m_node_coord[inode].y - maxCoor.y) > getTreshold()) flag_ymax = false;
         if (math::abs(vars.m_node_coord[inode].z - maxCoor.z) > getTreshold()) flag_zmax = false;
     }
     if (flag_x0 == true) face_x0_lid.add(face_local_id);
     if (flag_y0 == true) face_y0_lid.add(face_local_id);
     if (flag_z0 == true) face_z0_lid.add(face_local_id);
     if (flag_xmax == true) face_xmax_lid.add(face_local_id);
     if (flag_ymax == true) face_ymax_lid.add(face_local_id);
     if (flag_zmax == true) face_zmax_lid.add(face_local_id);
   }
   
   mesh()->faceFamily()->createGroup("XMIN", face_x0_lid,true);
   mesh()->faceFamily()->createGroup("YMIN", face_y0_lid,true);
   mesh()->faceFamily()->createGroup("ZMIN", face_z0_lid,true);
   FaceGroup facexmin = mesh()->faceFamily()->findGroup("XMIN");
   FaceGroup faceymin = mesh()->faceFamily()->findGroup("YMIN");
   FaceGroup facezmin = mesh()->faceFamily()->findGroup("ZMIN");
   info() << " taille x 0 " << facexmin.size();
   info() << " taille y 0 " << faceymin.size();
   info() << " taille z 0 " << facezmin.size();
   
   mesh()->faceFamily()->createGroup("XMAX", face_xmax_lid,true);
   mesh()->faceFamily()->createGroup("YMAX", face_ymax_lid,true);
   mesh()->faceFamily()->createGroup("ZMAX", face_zmax_lid,true);
   FaceGroup facexmax = mesh()->faceFamily()->findGroup("XMAX");
   FaceGroup faceymax = mesh()->faceFamily()->findGroup("YMAX");
   FaceGroup facezmax = mesh()->faceFamily()->findGroup("ZMAX");
   info() << " taille x max " << facexmax.size();
   info() << " taille y max " << faceymax.size();
   info() << " taille z max " << facezmax.size();
   
 
   info() << " nombre total de face " << allFaces().size();
   
   info() << " creation des groupes de dimension " << m_dimension;
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void MahycoModule::
computeDeltaT(MahycoComputeDeltaTVars& vars)
{
  debug() << " Entree dans compute DT avec " << m_global_old_deltat()
         << " et " << getDeltatInit()
         << " et " << m_global_deltat()
         << " et " << getDeltatMax();
         
  m_global_old_deltat = m_global_deltat;
  m_old_deltat = m_global_old_deltat();
         
  Real new_dt = FloatInfo < Real >::maxValue();
  if (getSansLagrange()) {
    // on garde le meme pas de temps
    new_dt = getDeltatInit();
    
  } else {
#if 0
    CellToAllEnvCellConverter all_env_cell_converter(mm);

    // Calcul du pas de temps pour le respect du critère de CFL
    Real minimum_aux = FloatInfo < Real >::maxValue();
    Integer cell_id(-1), nbenvcell(-1);
    Real cc(0.), ll(0.);

    ENUMERATE_CELL(icell, allCells()){
        Cell cell = * icell;
        Real cell_dx = vars.m_caracteristic_length[icell];
        Real sound_speed = vars.m_sound_speed[icell];
        Real vmax(0.);
        if (getWithProjection())
          for (NodeEnumerator inode(cell.nodes()); inode.index() < cell.nbNode(); ++inode) {
            vmax = math::max(vars.m_velocity[inode].normL2(), vmax);
          }
        Real dx_sound = cell_dx / (sound_speed + vmax);
        minimum_aux = math::min(minimum_aux, dx_sound);
        if (minimum_aux == dx_sound) {
            cell_id = icell.localId();
            cc = vars.m_sound_speed[icell];
            ll = vars.m_caracteristic_length[icell];
            AllEnvCell all_env_cell = all_env_cell_converter[cell];
            nbenvcell = all_env_cell.nbEnvironment();
        }
    }

    new_dt = getCfl() * minimum_aux;
    new_dt = parallelMng()->reduce(Parallel::ReduceMin, new_dt);
    
    // respect de taux de croissance max
    new_dt = math::min(new_dt, 1.05 * m_global_old_deltat());
    // respect de la valeur max imposée par le fichier de données .plt
    debug() << " nouveau pas de temps " << new_dt << " par " << cell_id << 
        " (avec " << nbenvcell << " envs) avec " << cc << " " << ll << " et min " << minimum_aux;
    new_dt = math::min(new_dt, getDeltatMax());
    // respect du pas de temps minimum
    if (new_dt < getDeltatMin()) {
        info() << " pas de temps minimum ";
        info() << " nouveau pas de temps " << new_dt << " par " << cell_id 
            << " (avec " << nbenvcell << " envs) avec vitson = " << cc << " et longeur  =  " << ll << " et min " << minimum_aux;
        exit(1);
    }
#else
#ifdef ARCANE_DEBUG
    DtCellInfo dt_cell_info(defaultMesh()); // en debug, collecte des infos sur la maille qui fait le pas de temps
#else
    DtCellInfoVoid dt_cell_info; // en optimisé, on ne calcule pas les infos sur la maille qui fait le pas de temps
#endif
    new_dt = computeHydroDeltaT(dt_cell_info);
    
    // respect de taux de croissance max
    new_dt = math::min(new_dt, 1.05 * m_global_old_deltat());
    // respect de la valeur max imposée par le fichier de données .plt
    debug() << " nouveau pas de temps " << new_dt << dt_cell_info.strInfo();
    new_dt = math::min(new_dt, getDeltatMax());
    // respect du pas de temps minimum
    if (new_dt < getDeltatMin()) {
      // On RECALCULE le pas de temps en récupérant les infos sur la maille cette fois-ci
      DtCellInfo dt_cell_info_min(defaultMesh());
      new_dt = computeHydroDeltaT(dt_cell_info_min);
      info() << " pas de temps minimum ";
      info() << " nouveau pas de temps " << new_dt << dt_cell_info_min.strInfo();
      exit(1);
    }
#endif
    
    debug() << " nouveau pas de temps2 " << new_dt;
        
  }
  
  // Mise à jour du pas de temps
  m_global_deltat = new_dt;
  
  // Le dernier calcul se fait exactement au temps stopTime()
  Real stop_time  = getFinalTime();
  bool not_yet_finish = (m_global_time() < stop_time);
  bool finish = (m_global_time() > stop_time);
  bool too_much = ((m_global_time()+new_dt) > stop_time);

  
  debug() << " nouveau pas de temps " << new_dt;
  if ( not_yet_finish && too_much){
    new_dt = stop_time - m_global_time();
    subDomain()->timeLoopMng()->stopComputeLoop(true);
  }
  if (finish) {
    subDomain()->timeLoopMng()->stopComputeLoop(true);
  }
    
  debug() << " time " << m_global_time() << " et fin à " << stop_time;
  debug() << " not_yet_finish " << not_yet_finish;
  debug() << " finish " << finish;
  debug() << " too_much " << too_much;
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

Real MahycoModule::
computeHydroDeltaT(MahycoComputeHydroDeltaTVars& vars)
{
  // Calcul du pas de temps pour le respect du critère de CFL
  Real minimum_aux;
  {
    auto queue = m_acc_env->newQueue();
    auto command = makeCommand(queue);
    ax::ReducerMin<Real> minimum_aux_reducer(command);

    bool with_projection = getWithProjection();

    auto in_caracteristic_length = ax::viewIn(command, vars.m_caracteristic_length);
    auto in_sound_speed          = ax::viewIn(command, vars.m_sound_speed.globalVariable());
    auto in_velocity             = ax::viewIn(command, vars.m_velocity);
    typename DtCellInfoType::VarCellSetter out_dx_sound(dt_cell_info.dxSoundSetter(command));

    auto cnc = m_acc_env->connectivityView().cellNode();

    command << RUNCOMMAND_ENUMERATE(Cell,cid,allCells()) {
      Real cell_dx = in_caracteristic_length[cid];
      Real sound_speed = in_sound_speed[cid];
      Real vmax(0.);
      if (with_projection) {
        for( NodeLocalId nid : cnc.nodes(cid) ){
          vmax = math::max(in_velocity[nid].normL2(), vmax);
        }
      }
      Real dx_sound = cell_dx / (sound_speed + vmax);
      minimum_aux_reducer.min(dx_sound);
      // On récupère éventuellement (ça va dépendre du type de dt_cell_info) la valeur de dx_sound sur cid
      out_dx_sound.setCellValue(cid, dx_sound);
    };
    minimum_aux = minimum_aux_reducer.reduce();
  }
  // En fonction du type de dt_cell_info, on calcule ou pas les infos sur la maille qui fait le pas de temps
  [[maybe_unused]] Real h_minimum_aux = dt_cell_info.computeMinCellInfo(allCells(), mm, m_sound_speed, m_caracteristic_length);
  ARCANE_ASSERT(h_minimum_aux==minimum_aux, ("Les minimum_aux calculés sur CPU et GPU sont différents"));

  Real dt_hydro = getCfl() * minimum_aux;
  dt_hydro = parallelMng()->reduce(Parallel::ReduceMin, dt_hydro);

  return dt_hydro;
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

ARCANE_REGISTER_MODULE_MAHYCO(MahycoModule);

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace Mahyco
