#include "remap/adi/RemapADIService.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

namespace RemapAdi {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

RemapADIService::
RemapADIService(const ServiceBuildInfo& bi)
: RemapADIServiceBase<RemapADIService>(bi)
{
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

RemapADIService::
~RemapADIService()
{
}


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void RemapADIService::
synchronizeDualUremap(RemapADISynchronizeDualUremapVars& vars)
{
    debug() << " Entree dans synchronizeUremap()";
#if 0
    vars.m_phi_dual_lagrange.synchronize();
    vars.m_u_dual_lagrange.synchronize();
#else
    MeshVariableSynchronizerList mvsl(m_acc_env->vsyncMng());

    mvsl.add(vars.m_phi_dual_lagrange);
    mvsl.add(vars.m_u_dual_lagrange);

    auto queue_synchronize = m_acc_env->refQueueAsync();
    m_acc_env->vsyncMng()->synchronize(mvsl, queue_synchronize);
#endif
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void RemapADIService::
computeGradPhiFace(RemapADIComputeGradPhiFaceVars& vars, const Integer idir, const Integer nb_vars_to_project, const Integer nb_env)
{
  debug() << " Entree dans computeGradPhiFace()";
  
#if 0
  
  FaceDirectionMng fdm(vars.m_cartesian_mesh->faceDirection(idir));
  
  ENUMERATE_FACE(iface, fdm.allFaces()) {
    Face face = *iface; 
    vars.m_is_dir_face[face][idir] = true;
  }
  
  vars.m_h_cell_lagrange.fill(0.0);
  
  ENUMERATE_FACE(iface, fdm.innerFaces()) {
    Face face = *iface; 
    DirFace dir_face = fdm[face];
    Cell cellb = dir_face.previousCell();
    Cell cellf = dir_face.nextCell();
    vars.m_deltax_lagrange[face] = math::dot(
     (vars.m_cell_coord[cellf] -  vars.m_cell_coord[cellb]), vars.m_face_normal[face]); 

    for (Integer ivar = 0 ; ivar <  nb_vars_to_project ; ++ivar) {
      vars.m_grad_phi_face[iface][ivar] = (vars.m_phi_lagrange[cellf][ivar] - vars.m_phi_lagrange[cellb][ivar]) 
                                  / vars.m_deltax_lagrange[iface];
    }
    // somme des distances entre le milieu de la maille et le milieu de la face
    vars.m_h_cell_lagrange[cellb] +=  (vars.m_face_coord[iface] - vars.m_cell_coord[cellb]).normL2();
    vars.m_h_cell_lagrange[cellf] +=  (vars.m_face_coord[iface] - vars.m_cell_coord[cellf]).normL2();     
  }

#else

  Cartesian::FactCartDirectionMng fact_cart(mesh());

  auto queue_dfac = m_acc_env->newQueue();
  queue_dfac.setAsync(true);
  {
    auto command = makeCommand(queue_dfac);

    auto cart_fdm = fact_cart.faceDirection(idir);
    auto f2cid_stm = cart_fdm.face2CellIdStencil();
    auto face_group = cart_fdm.allFaces();

    auto out_is_dir_face = ax::viewOut(command,vars.m_is_dir_face);

    command.addKernelName("is_dir_face") << RUNCOMMAND_LOOP(iter, face_group.loopRanges()) {
      auto [fid, idx] = f2cid_stm.idIdx(iter); // id face + (i,j,k) face

      out_is_dir_face[fid][idir] = true;
    };
  }
  
  {
    auto queue_gphi = m_acc_env->newQueue();
    queue_gphi.setAsync(true);
    {
      auto command_f = makeCommand(queue_gphi);

      auto cart_fdm = fact_cart.faceDirection(idir);
      auto f2cid_stm = cart_fdm.face2CellIdStencil();
      auto face_group = cart_fdm.innerFaces();

      auto in_face_normal  = ax::viewIn(command_f, vars.m_face_normal);
      auto in_cell_coord   = ax::viewIn(command_f, vars.m_cell_coord);
      auto in_phi_lagrange = ax::viewIn(command_f, vars.m_phi_lagrange);

      auto inout_deltax_lagrange = ax::viewInOut(command_f, vars.m_deltax_lagrange);

      auto out_grad_phi_face = ax::viewOut(command_f, vars.m_grad_phi_face);

      command_f.addKernelName("gphi") << RUNCOMMAND_LOOP(iter, face_group.loopRanges()) {
        auto [fid, idx] = f2cid_stm.idIdx(iter); // id face + (i,j,k) face

        // Acces mailles gauche/droite 
        auto f2cid = f2cid_stm.face(fid, idx);
        CellLocalId pcid(f2cid.previousCell());
        CellLocalId ncid(f2cid.nextCell());

        inout_deltax_lagrange[fid] = math::dot(
            (in_cell_coord[ncid] -  in_cell_coord[pcid]), in_face_normal[fid]);

        for (Integer ivar = 0 ; ivar <  nb_vars_to_project ; ++ivar) {
          out_grad_phi_face[fid][ivar] = (in_phi_lagrange[ncid][ivar] - in_phi_lagrange[pcid][ivar]) 
            / inout_deltax_lagrange[fid];
        }
      }; // Asynchrone par rapport à l'hôte et aux autres queues
    }

//#define HCELL_BY_FACES
#define HCELL_BY_CELLS

#if defined(HCELL_BY_FACES)
    auto queue_hcell = m_acc_env->newQueue();
    {
      auto command_p = makeCommand(queue_hcell);

      auto cart_fdm = fact_cart.faceDirection(idir);
      auto f2cid_stm = cart_fdm.face2CellIdStencil();
      auto face_group = cart_fdm.innerFaces();

      auto in_face_coord   = ax::viewIn(command_p, vars.m_face_coord);
      auto in_cell_coord   = ax::viewIn(command_p, vars.m_cell_coord);
      auto inout_h_cell_lagrange = ax::viewInOut(command_p, vars.m_h_cell_lagrange);

      // D'abord contribution dans toutes les mailles précédentes
      command_p.addKernelName("hcell_prev") << RUNCOMMAND_LOOP(iter, face_group.loopRanges()) {
        auto [fid, idx] = f2cid_stm.idIdx(iter); // id face + (i,j,k) face

        // Acces maille gauche
        auto f2cid = f2cid_stm.face(fid, idx);
        CellLocalId pcid(f2cid.previousCell());

        // somme des distances entre le milieu de la maille et le milieu de la face
        inout_h_cell_lagrange[pcid] =  (in_face_coord[fid] - in_cell_coord[pcid]).normL2();
      };

      const Integer last_idx = fact_cart.cartesianGrid()->cartNumCell().nbItemDir(idir)-1;
      // Puis, contrib dans toutes les mailles suivantes
      command_p.addKernelName("hcell_next") << RUNCOMMAND_LOOP(iter, face_group.loopRanges()) {
        auto [fid, idx] = f2cid_stm.idIdx(iter); // id face + (i,j,k) face

        // Acces maille droite
        auto f2cid = f2cid_stm.face(fid, idx);
        CellLocalId ncid(f2cid.nextCell());

        // somme des distances entre le milieu de la maille et le milieu de la face
        Real hcell = (idx[idir]==last_idx ? 0. : inout_h_cell_lagrange[ncid]);
        hcell +=  (in_face_coord[fid] - in_cell_coord[ncid]).normL2();
        inout_h_cell_lagrange[ncid] = hcell;
      };
    }
#elif defined(HCELL_BY_CELLS)
    auto queue_hcell = m_acc_env->newQueue();
    {
      auto command_c = makeCommand(queue_hcell);

      auto cart_cdm = fact_cart.cellDirection(idir);
      auto c2fid_stm = cart_cdm.cell2FaceIdStencil();
      auto cell_group = cart_cdm.allCells();

      // Nb de mailles-1 dans la direction idir
      const Integer ncell_m1 = fact_cart.cartesianGrid()->cartNumCell().nbItemDir(idir)-1;

      auto in_face_coord   = ax::viewIn(command_c, vars.m_face_coord);
      auto in_cell_coord   = ax::viewIn(command_c, vars.m_cell_coord);
      auto out_h_cell_lagrange = ax::viewOut(command_c, vars.m_h_cell_lagrange);

      // Parcours de toutes les mailles en excluant les contribs des faces de bord
      command_c.addKernelName("hcell") << RUNCOMMAND_LOOP(iter, cell_group.loopRanges()) {
        auto [cid, idx] = c2fid_stm.idIdx(iter); // id maille + (i,j,k) maille
        
        // Acces faces gauche/droite qui existent forcement
        auto c2fid = c2fid_stm.cellFace(cid, idx);
        FaceLocalId pfid(c2fid.previousId());
        FaceLocalId nfid(c2fid.nextId());

        // somme des distances entre le milieu de la maille et les milieux des faces adjacentes dans idir
        Real hcell = 0;
        if (idx[idir]>0) // Si maille bord gauche, on exclut la contrib de la face sur le bord gauche
          hcell +=  (in_face_coord[pfid] - in_cell_coord[cid]).normL2();
        if (idx[idir]<ncell_m1) // Si maille bord droit, on exclut la contrib de la face sur le bord droit
          hcell +=  (in_face_coord[nfid] - in_cell_coord[cid]).normL2();

        // Plus besoin d'appeler m_h_cell_lagrange.fill(0.0). On boucle ici sur toutes les mailles
        out_h_cell_lagrange[cid] = hcell;
      };
    }
#else
#error "HCELL_BY_FACES ou bien HCELL_BY_CELLS doit etre defini"
#endif

    queue_gphi.barrier();
  } 
  queue_dfac.barrier(); // fin calcul m_is_dir_face
#endif
#if 0
  vars.m_grad_phi_face.synchronize(); // INUTILE ?
  vars.m_h_cell_lagrange.synchronize();
#else
  MeshVariableSynchronizerList mvsl(m_acc_env->vsyncMng());

  mvsl.add(vars.m_grad_phi_face);
  mvsl.add(vars.m_h_cell_lagrange);
  
  auto queue_synchronize = m_acc_env->refQueueAsync();
  m_acc_env->vsyncMng()->synchronize(mvsl, queue_synchronize);
#endif
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void RemapADIService::
computeGradPhiCell(RemapADIComputeGradPhiCellVars& vars, const Integer idir, const Integer nb_vars_to_project, const Integer nb_env)
{
  PROF_ACC_BEGIN(__FUNCTION__);
  debug() << " Entree dans computeGradPhiCell()";

  // il faut initialiser m_grad_phi = 0 pour le cas ordre 1 (CPU ou GPU). On passe par un RUNCOMMAND_ENUMERATE 
  // pour couvrir les cas GPU et CPU plutot qu'un fill qui conduirait à des transferts lors d'un run GPU.
//   m_grad_phi.fill(0.0);
  auto queue = m_acc_env->newQueue();
  {
    auto command = makeCommand(queue);
    
    auto out_grad_phi = ax::viewOut(command, vars.m_grad_phi);
    
    command << RUNCOMMAND_ENUMERATE(Cell, cid, allCells()) {
      for (Integer ivar = 0; ivar < nb_vars_to_project; ivar++)
        out_grad_phi[cid][ivar] = 0.;
    };
  }
  
  if (options()->ordreProjection > 1 && 
      options()->projectionPenteBorneMixte == false &&
      options()->projectionPenteBorne == 0 &&
      options()->projectionLimiteurId < Types_mahyco::Limiteur::MinmodG) 
  {
    // Spécialisation
    switch (options()->projectionLimiteurId) {
      case Types_mahyco::Limiteur::Minmod  : computeGradPhiCell_PBorn0_LimC<MinMod>   (idir, nb_vars_to_project); break;
      case Types_mahyco::Limiteur::SuperBee: computeGradPhiCell_PBorn0_LimC<SuperBee> (idir, nb_vars_to_project); break;
      case Types_mahyco::Limiteur::VanLeer : computeGradPhiCell_PBorn0_LimC<VanLeer>  (idir, nb_vars_to_project); break;
      default      : computeGradPhiCell_PBorn0_LimC<DefaultO1>(idir, nb_vars_to_project);
    }
    PROF_ACC_END;
    return;
  }

  Real deltat = m_global_deltat();
  Real3 dirproj = {0.5 * (1-idir) * (2-idir), 
                   1.0 * idir * (2 -idir), 
                   -0.5 * idir * (1 - idir)};  

  // uniquement utilisés pour (options()->ordreProjection > 1) && (options()->projectionPenteBorne == 1)
  vars.m_delta_phi_face_av.fill(0.0);
  vars.m_delta_phi_face_ar.fill(0.0);
  
  FaceDirectionMng fdm(m_cartesian_mesh->faceDirection(idir));
  if (options()->ordreProjection > 1) {
#if 0
    info() << "options()->ordreProjection > 1";
    info() << "options()->projectionPenteBorneMixte : " << options()->projectionPenteBorneMixte;
    info() << "options()->projectionLimiteurId : " << options()->projectionLimiteurId;
    info() << "options()->getProjectionLimiteurPureId() : " << options()->getProjectionLimiteurPureId();
    info() << "options()->projectionPenteBorne : " << options()->projectionPenteBorne;
    info() << "options()->threshold : " << options()->threshold;
    info() << "options()->projectionPenteBorneDebarFix : " << options()->projectionPenteBorneDebarFix;
#endif
    ENUMERATE_CELL(icell,allCells()) {
      Cell cell = * icell;
      Cell backcell = cell; // pour les mailles de bord
      Cell frontcell = cell; // pour les mailles de bord
      Face backFace;
      Face frontFace;
      Integer indexbackface;
      Integer indexfrontface;
      Integer cas_possible(0);
      ENUMERATE_FACE(iface, cell.faces()){
        const Face& face = *iface;
        
        if ( vars.m_is_dir_face[face][idir] == true) {
          DirFace dir_face = fdm[face];
          if (dir_face.previousCell() == cell) {
          frontFace = face;
          indexfrontface = iface.index(); 
          if (dir_face.nextCell().localId() != -1) frontcell = dir_face.nextCell();
          cas_possible++;
          } 
          else if ( dir_face.nextCell() == cell) {
          backFace = face;
          indexbackface = iface.index(); 
          if (dir_face.previousCell().localId() != -1) backcell = dir_face.previousCell();
          cas_possible++;
          }
        }
        if (cas_possible > 2) info() << " mauvais algo maille " << cell.localId();
        if (cas_possible == 2) continue;
      }
      bool voisinage_pure = (options()->projectionPenteBorneMixte == true &&
        vars.m_est_mixte[cell] == 0 && vars.m_est_mixte[frontcell] == 0 && vars.m_est_mixte[backcell] == 0 &&
        vars.m_est_pure[cell] == vars.m_est_pure[frontcell] && vars.m_est_pure[cell] == vars.m_est_pure[backcell] );
      
      Types_mahyco::Limiteur limiter = options()->projectionLimiteurId;
      if ((options()->getProjectionLimiteurPureId() == Types_mahyco::Limiteur::SuperBee) && voisinage_pure)
      {
        limiter = options()->projectionLimiteurPureId;
      }
      // calcul de m_grad_phi[cell] 
      RemapAdi::RemapADIServiceBase<RemapADIService>::computeAndLimitGradPhi(limiter, frontFace, backFace, cell, frontcell, backcell, nb_vars_to_project);
      

      if (options()->projectionPenteBorne == 1) {
        // if (cstmesh->cylindrical_mesh) exy = varlp->faceNormal(flFaces);
        Real Flux_sortant_ar = math::dot(vars.m_outer_face_normal[cell][indexbackface], dirproj) * vars.m_face_normal_velocity[backFace];
        // if (cstmesh->cylindrical_mesh) exy = varlp->faceNormal(frFaces);
        Real Flux_sortant_av = math::dot(vars.m_outer_face_normal[cell][indexfrontface], dirproj) * vars.m_face_normal_velocity[frontFace];
        
        Real flux_dual = 0.5 * (Flux_sortant_ar + Flux_sortant_av);
        
        Integer calcul_flux_dual(1); // a supprimer - calcul du flux dual fait en pente borne
        
        RealUniqueArray delta_phi_face(nb_vars_to_project);
        RealUniqueArray dual_phi_flux(nb_vars_to_project);
       
        RealArrayView delta_phi_face_view(delta_phi_face);
        RealArrayView dual_phi_flux_view(dual_phi_flux);

        // calcul de m_delta_phi_face_ar et m_dual_phi_flux
        if (voisinage_pure)
            RemapAdi::RemapADIServiceBase<RemapADIService>::computeFluxPPPure(cell, frontcell, backcell, Flux_sortant_ar, 
                            deltat, 0, options()->threshold, 
                            options()->projectionPenteBorneDebarFix, flux_dual,
                            calcul_flux_dual, &delta_phi_face_view, &dual_phi_flux_view,
                            nb_env, nb_vars_to_project);
        else
            RemapAdi::RemapADIServiceBase<RemapADIService>::computeFluxPP(cell, frontcell, backcell, Flux_sortant_ar, 
                            deltat, 0, options()->threshold, 
                            options()->projectionPenteBorneDebarFix, flux_dual,
                            calcul_flux_dual, &delta_phi_face_view, &dual_phi_flux_view,
                            nb_env, nb_vars_to_project);
            
        for (Integer ivar = 0; ivar < nb_vars_to_project; ivar++) {    
            vars.m_delta_phi_face_ar[cell][ivar] = delta_phi_face[ivar];
            // et pour avoir un flux dual 2D
            vars.m_dual_phi_flux[cell][ivar] = dual_phi_flux[ivar] * 
            0.5 * (vars.m_face_length_lagrange[backFace][idir] + vars.m_face_length_lagrange[frontFace][idir]);
        }
        // calcul de m_delta_phi_face_av
        if (voisinage_pure)
            RemapAdi::RemapADIServiceBase<RemapADIService>::computeFluxPPPure(cell, frontcell, backcell, Flux_sortant_av, 
                            deltat, 1, options()->threshold, 
                            options()->projectionPenteBorneDebarFix, flux_dual,
                            calcul_flux_dual, &delta_phi_face_view, &dual_phi_flux_view,
                            nb_env, nb_vars_to_project);
        else
            RemapAdi::RemapADIServiceBase<RemapADIService>::computeFluxPP(cell, frontcell, backcell, Flux_sortant_av, 
                            deltat, 1, options()->threshold, 
                            options()->projectionPenteBorneDebarFix, flux_dual,
                            calcul_flux_dual, &delta_phi_face_view, &dual_phi_flux_view,
                            nb_env, nb_vars_to_project);
            
        for (Integer ivar = 0; ivar < nb_vars_to_project; ivar++) {    
            vars.m_delta_phi_face_av[cell][ivar] = delta_phi_face[ivar];
            // dual_phi_flux ne sert pas ici : le flux dual a dèjà été calculé
        }
      }
    }     
  }
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

/**
 *******************************************************************************
 * \file computeGradPhiCell_PBorn0_LimC()
 * \brief Spécialisation de computeGradPhiCell
 *        pour options()->projectionPenteBorne[Mixte] == false
 *        et options()->projectionLimiteurId < minmodG (limiteur classique)
 * \param
 * \return m_grad_phi_face, m_delta_phi_face_ar, m_delta_phi_face_av
 *******************************************************************************
 */
template<typename LimType>
void RemapADIService::
computeGradPhiCell_PBorn0_LimC(Integer idir, Integer nb_vars_to_project) {
  Cartesian::FactCartDirectionMng fact_cart(mesh());

  auto queue = m_acc_env->newQueue();
  {
    auto command = makeCommand(queue);
    
    auto cart_cdm = fact_cart.cellDirection(idir);
#if 0
    auto c2cid_stm = cart_cdm.cell2CellIdStencil();
#endif
    auto c2fid_stm = cart_cdm.cell2FaceIdStencil();
    auto cell_group = cart_cdm.allCells();

    auto in_grad_phi_face = ax::viewIn(command, m_grad_phi_face);
    auto out_grad_phi = ax::viewOut(command, m_grad_phi);

    auto out_delta_phi_face_av = ax::viewOut(command, m_delta_phi_face_av);
    auto out_delta_phi_face_ar = ax::viewOut(command, m_delta_phi_face_ar);

    command << RUNCOMMAND_LOOP(iter, cell_group.loopRanges()) {
      auto [cid, idx] = c2fid_stm.idIdx(iter); // id maille + (i,j,k) maille

      // Acces faces gauche/droite qui existent forcement
      auto c2fid = c2fid_stm.cellFace(cid, idx);
      FaceLocalId backFid(c2fid.previousId()); // back face
      FaceLocalId frontFid(c2fid.nextId()); // front face

#if 0
      // Acces mailles gauche/droite
      auto c2cid = c2cid_stm.cell(cid, idx);
      CellLocalId backCid(c2cid.previous()); // back cell
      CellLocalId frontCid(c2cid.next()); // front cell

      // Si maille voisine n'existe pas (bord), alors on prend maille centrale
      if (ItemId::null(backCid))
        backCid = cid;
      if (ItemId::null(frontCid))
        frontCid = cid;
#endif

      // calcul de m_grad_phi[cell]
      // Spécialisation de computeAndLimitGradPhi 
      // pour options()->projectionLimiteurId < minmodG (limiteur classique)
      // info() << " Passage gradient limite Classique ";
      for (Integer ivar = 0; ivar < nb_vars_to_project; ivar++) {
        Real grad_phi_cell = 0.;
        Real grad_phi_face_back = in_grad_phi_face[backFid][ivar];
        Real grad_phi_face_front = in_grad_phi_face[frontFid][ivar];
        if (grad_phi_face_back != 0.) 
          grad_phi_cell += 0.5 * (LimType::fluxLimiter(grad_phi_face_front /grad_phi_face_back) * grad_phi_face_back);
        if (grad_phi_face_front !=0.) 
          grad_phi_cell += 0.5 * (LimType::fluxLimiter(grad_phi_face_back / grad_phi_face_front) * grad_phi_face_front);
        out_grad_phi[cid][ivar] = grad_phi_cell;
      }

      // Init sur GPU de m_delta_phi_face_av et m_delta_phi_face_ar
      for (Integer ivar = 0; ivar < nb_vars_to_project; ivar++) {
        out_delta_phi_face_av[cid][ivar] = 0.;
        out_delta_phi_face_ar[cid][ivar] = 0.;
      }
    };
  }
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void RemapADIService::
computeUpwindFaceQuantitiesForProjection(RemapADIComputeUpwindFaceQuantitiesForProjectionVars& vars, const Integer idir, const Integer nb_vars_to_project, const Integer nb_env)
{
  #if 0
  info() << "options()->ordreProjection : " << options()->ordreProjection;
  info() << "options()->projectionPenteBorne : " << options()->projectionPenteBorne;
#endif
  if (options()->ordreProjection <= 2 &&
      options()->projectionPenteBorne == 0)
  {
    // Spécialisation
    RemapADIServiceBase<RemapADIService>::computeUpwindFaceQuantitiesForProjectionPBorn0O2(idir, nb_vars_to_project);
    return;
  }
  
  debug() << " Entree dans computeUpwindFaceQuantitiesForProjection()";
  Real deltat = m_global_deltat();
  CellDirectionMng cdm(m_cartesian_mesh->cellDirection(idir));
  FaceDirectionMng fdm(m_cartesian_mesh->faceDirection(idir));
  vars.m_phi_face.fill(0.0);
  Integer order2 = options()->ordreProjection - 1;
  ENUMERATE_FACE(iface, fdm.innerFaces()) {
      Face face = *iface;
      DirFace dir_face = fdm[face];
      Cell cellb = dir_face.previousCell();
      Cell cellf = dir_face.nextCell();
      
      // phiFace1 correspond
      // à la valeur de phi(x) à la face pour l'ordre 2 sans plateau pente
      // à la valeur du flux (integration de phi(x)) pour l'ordre 2 avec
      // Plateau-Pente à la valeur du flux (integration de phi(x)) pour
      // l'ordre 3
      if (options()->ordreProjection <= 2) {
        if (options()->projectionPenteBorne == 0) {
          if (vars.m_face_normal_velocity[face] * vars.m_deltax_lagrange[face] > 0.0) {
              // phi_cb + (dot((x_f - x_cb), face_normal) * grad_phi_cb)   
            for (Integer ivar = 0; ivar < nb_vars_to_project; ivar++)
              vars.m_phi_face[face][ivar] = vars.m_phi_lagrange[cellb][ivar]
                    + order2 * math::dot((vars.m_face_coord[face] - vars.m_cell_coord[cellb]),
                    vars.m_face_normal[face]) * vars.m_grad_phi[cellb][ivar];
          } else {
            for (Integer ivar = 0; ivar < nb_vars_to_project; ivar++)
              vars.m_phi_face[face][ivar] = vars.m_phi_lagrange[cellf][ivar]
                    + order2 * math::dot((vars.m_face_coord[face] - vars.m_cell_coord[cellf]),
                    vars.m_face_normal[face]) * vars.m_grad_phi[cellf][ivar];
          }
        } else {
          for (Integer ivar = 0; ivar < nb_vars_to_project; ivar++) {
            vars.m_phi_face[face][ivar] = (vars.m_delta_phi_face_av[cellb][ivar] - vars.m_delta_phi_face_ar[cellf][ivar]);
          }
        }
     } else if (options()->ordreProjection == 3) {
        Cell cellbb = cellb;
        Cell cellbbb = cellb;
        Cell cellff = cellf;
        Cell cellfff = cellf;
        DirCell ccb(cdm.cell(cellb));
        if (ccb.previous().localId() != -1) {
          cellbb = ccb.previous();
          cellbbb = cellbb;
          DirCell ccbb(cdm.cell(cellbb));
          if (ccbb.previous().localId() != -1) {
            cellbbb = ccbb.previous();
          }
        }
        DirCell ccf(cdm.cell(cellf));
        if (ccf.next().localId() != -1) {
          cellff = ccf.next();
          cellfff = cellff;
          DirCell ccff(cdm.cell(cellff));
          if (ccff.next().localId() != -1) {
            cellfff = ccff.next();   
          }
        }
        Real vdt  = vars.m_face_normal_velocity[face] * deltat;
        for (Integer ivar = 0; ivar < nb_vars_to_project; ivar++) {
            vars.m_phi_face[face][ivar] = ComputeFluxOrdre3(
                vars.m_phi_lagrange[cellbbb][ivar],
                vars.m_phi_lagrange[cellbb][ivar],
                vars.m_phi_lagrange[cellb][ivar],
                vars.m_phi_lagrange[cellf][ivar],
                vars.m_phi_lagrange[cellff][ivar],
                vars.m_phi_lagrange[cellfff][ivar],
                vars.m_h_cell_lagrange[cellbbb],
                vars.m_h_cell_lagrange[cellbb],
                vars.m_h_cell_lagrange[cellb],
                vars.m_h_cell_lagrange[cellf],
                vars.m_h_cell_lagrange[cellff],
                vars.m_h_cell_lagrange[cellfff],
                vdt);
        }
        bool voisinage_pure = (vars.m_est_mixte[cellb] == 0 && vars.m_est_mixte[cellf] == 0 && 
        vars.m_est_pure[cellb] == vars.m_est_pure[cellf]);
        int nbmat = nb_env;
        if (!voisinage_pure) {
          // comme dans le pente borne, on evite le pb de debar sur les maille a voisinage mixte
          // pinfo() << " voisinage mixte " << cellb.localId() << " et " << cellf.localId();
          for (int imat = 0; imat < nbmat; imat++) {
            if (vdt>0. && vars.m_phi_lagrange[cellb][imat]!=0. && vars.m_phi_lagrange[cellb][nbmat+imat]!=0.) {
             vars.m_phi_face[face][nbmat+imat] = (vars.m_phi_lagrange[cellb][nbmat+imat]/vars.m_phi_lagrange[cellb][imat])
                *vars.m_phi_face[face][imat];
             vars.m_phi_face[face][2*nbmat+imat] = (vars.m_phi_lagrange[cellb][2*nbmat+imat]/vars.m_phi_lagrange[cellb][nbmat+imat])
                *vars.m_phi_face[face][nbmat+imat];
            } else if (vdt<0. && vars.m_phi_lagrange[cellf][imat]!=0. && vars.m_phi_lagrange[cellf][nbmat+imat]!=0.) {
             vars.m_phi_face[face][nbmat+imat] = (vars.m_phi_lagrange[cellf][nbmat+imat]/vars.m_phi_lagrange[cellf][imat])
                *vars.m_phi_face[face][imat];
             vars.m_phi_face[face][2*nbmat+imat] = (vars.m_phi_lagrange[cellf][2*nbmat+imat]/vars.m_phi_lagrange[cellf][nbmat+imat])
                *vars.m_phi_face[face][nbmat+imat];
            }
          }
        }
     }
  }
  vars.m_phi_face.synchronize();
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void RemapADIService::
computeUpwindFaceQuantitiesForProjectionPBorn0O2(RemapADIComputeUpwindFaceQuantitiesForProjectionPBorn0O2Vars& vars, const Integer idir, const Integer nb_vars_to_project)
{
  Cartesian::FactCartDirectionMng fact_cart(mesh());

  auto ref_queue = m_acc_env->refQueueAsync();
  // Init 0, pour simplifier sur toutes les faces
  {
    auto command = makeCommand(ref_queue.get());

    auto out_phi_face = ax::viewOut(command, vars.m_phi_face);

    command << RUNCOMMAND_ENUMERATE(Face, fid, allFaces()) {
      for (Integer ivar = 0; ivar < nb_vars_to_project; ivar++)
        out_phi_face[fid][ivar] = 0.;
    };
  }
  // Puis on calcule m_grad_phi que que les faces intérieures dans la direction idir
  {
    Integer order2 = options()->ordreProjection - 1;
    
    auto command = makeCommand(ref_queue.get());

    auto cart_fdm = fact_cart.faceDirection(idir);
    auto f2cid_stm = cart_fdm.face2CellIdStencil();
    auto face_group = cart_fdm.innerFaces();

    auto in_deltax_lagrange      = ax::viewIn(command, vars.m_deltax_lagrange);
    auto in_face_normal_velocity = ax::viewIn(command, vars.m_face_normal_velocity);
    auto in_phi_lagrange         = ax::viewIn(command, vars.m_phi_lagrange);
    auto in_face_coord           = ax::viewIn(command, vars.m_face_coord);
    auto in_face_normal          = ax::viewIn(command, vars.m_face_normal);
    auto in_cell_coord           = ax::viewIn(command, vars.m_cell_coord);
    auto in_grad_phi             = ax::viewIn(command, vars.m_grad_phi);

    auto out_phi_face = ax::viewOut(command, vars.m_phi_face);
    
    command << RUNCOMMAND_LOOP(iter, face_group.loopRanges()) {
      auto [fid, idx] = f2cid_stm.idIdx(iter); // id face + (i,j,k) face

      // Acces mailles gauche/droite
      auto f2cid = f2cid_stm.face(fid, idx);
      CellLocalId bCid(f2cid.previousCell());
      CellLocalId fCid(f2cid.nextCell());

      // Maille upwind
      CellLocalId upwCid = (in_face_normal_velocity[fid] * in_deltax_lagrange[fid] > 0.0 ? bCid : fCid);

      // Independemment de ivar, on calcule dot((x_f - x_cb), face_normal)
      Real dot_xf = math::dot((in_face_coord[fid] - in_cell_coord[upwCid]), in_face_normal[fid]);

      // phi_cb + (dot((x_f - x_cb), face_normal) * grad_phi_cb)   
      for (Integer ivar = 0; ivar < nb_vars_to_project; ivar++) 
        out_phi_face[fid][ivar] = in_phi_lagrange[upwCid][ivar] + order2 * dot_xf * in_grad_phi[upwCid][ivar];
    };
  }

#if 0
  vars.m_phi_face.synchronize(); // INUTILE ?
#else
  // ref_queue va être synchronisée dans globalSynchronize
  m_acc_env->vsyncMng()->globalSynchronize(ref_queue, vars.m_phi_face);
#endif
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void RemapADIService::
computeUremap(RemapADIComputeUremapVars& vars, const Integer idir, const Integer nb_vars_to_project, const Integer nb_env)
{
  if (options()->projectionPenteBorne == 0)
  {
    // Spécialisation
    RemapADIServiceBase<RemapADIService>::computeUremapPBorn0(idir, nb_vars_to_project, nb_env);
    return;
  }
  
  
  Real3 dirproj = {0.5 * (1-idir) * (2-idir),
                 1.0 * idir * (2 -idir), 
                 -0.5 * idir * (1 - idir)};
  int nbmat = nb_env;
  Real deltat = m_global_deltat();
  Real flux;    
  vars.m_dual_phi_flux.fill(0.);
  ENUMERATE_CELL(icell,allCells()) {
    Cell cell = * icell;
    RealUniqueArray flux_face(nb_vars_to_project);
    flux_face.fill(0.);
    ENUMERATE_FACE(iface, cell.faces()){
      const Face& face = *iface;
      Integer i = iface.index(); 
      if (std::fabs(math::dot(vars.m_face_normal[face], dirproj)) >= 1.0E-10) {
        Real face_normal_velocity(vars.m_face_normal_velocity[face]);
        Real face_length(vars.m_face_length_lagrange[face][idir]);
        Real3 outer_face_normal(vars.m_outer_face_normal[cell][i]);
        Real outer_face_normal_dir = math::dot(outer_face_normal, dirproj);
        if (options()->projectionPenteBorne == 0) {
          for (Integer ivar = 0; ivar < nb_vars_to_project; ivar++) {  
              flux = outer_face_normal_dir * face_normal_velocity * face_length * deltat * vars.m_phi_face[face][ivar];
              flux_face[ivar] += flux;
              vars.m_dual_phi_flux[cell][ivar] += 0.5 * flux * outer_face_normal[idir];
          }
        } else {
          for (Integer ivar = 0; ivar < nb_vars_to_project; ivar++) {
              flux = outer_face_normal_dir * face_length * vars.m_phi_face[face][ivar];
              flux_face[ivar] += flux;
              vars.m_dual_phi_flux[cell][ivar] += 0.5 * flux * outer_face_normal[idir];
          }
        }
      }
    }

    for (Integer ivar = 0; ivar < nb_vars_to_project; ivar++) {
      // flux dual comme demi somme des flux des deux faces contributives dans la direction idir
//       m_dual_phi_flux[cell][ivar] = 0.5* flux_face[ivar]; 
      vars.m_u_lagrange[cell][ivar] -= flux_face[ivar];
    }
    // diagnostics et controle
    for (int imat = 0; imat < nbmat; imat++) {
      if (vars.m_u_lagrange[cell][nbmat + imat] < 0.) {
        if (abs(vars.m_u_lagrange[cell][nbmat + imat]) > 1.e2 * options()->threshold)
          info() << " cell " << cell.localId()
                  << " proj 1 --masse tres faiblement negative   "
                  << " soit " << vars.m_u_lagrange[cell][nbmat + imat]
                  << " et volume " << vars.m_u_lagrange[cell][imat];
        vars.m_u_lagrange[cell][nbmat + imat] = 0.;
      }
      if (vars.m_u_lagrange[cell][2 * nbmat + imat] < 0.) {
        if (abs(vars.m_u_lagrange[cell][nbmat + imat]) > 1.e2 * options()->threshold)
          info() << " cell " << cell.localId()
                  << " --energie tres faiblement negative "
                  << " cell " << vars.m_u_lagrange[cell][2 * nbmat + imat];
        vars.m_u_lagrange[cell][2 * nbmat + imat] = 0.;
      }
    }
    // Calcul du volume de la maille apres 
    double somme_volume = 0.;
    for (int imat = 0; imat < nbmat; imat++) {
      somme_volume += vars.m_u_lagrange[cell][imat];
    }
    if (options()->projectionPenteBorne == 1) {
      // option ou on ne regarde pas la variation de rho, V et e
      // phi = (f1, f2, rho1*f1, rho2*f2, Vx, Vy, e1, e2
      // ce qui permet d'ecrire le flux telque
      // Flux = (dv1 = f1dv, dv2=f2*dv, dm1=rho1*df1, dm2=rho2*df2, d(mVx) =
      // Vx*(dm1+dm2), d(mVy) = Vy*(dm1+dm2), d(m1e1) = e1*dm1,  d(m2e2) =
      // e2*dm2 dans computeFluxPP
      // Phi volume
      double somme_masse = 0.;
      for (int imat = 0; imat < nbmat; imat++) {
        vars.m_phi_lagrange[cell][imat] = vars.m_u_lagrange[cell][imat] / somme_volume;
      // Phi masse
      if (vars.m_u_lagrange[cell][imat] != 0.)
        vars.m_phi_lagrange[cell][nbmat + imat] =
              vars.m_u_lagrange[cell][nbmat + imat] / vars.m_u_lagrange[cell][imat];
      else
        vars.m_phi_lagrange[cell][nbmat + imat] = 0.;
      somme_masse += vars.m_u_lagrange[cell][nbmat + imat];
      }
      if (somme_masse!=0) {
        // Phi Vitesse
        vars.m_phi_lagrange[cell][3 * nbmat] =
              vars.m_u_lagrange[cell][3 * nbmat] / somme_masse;
        vars.m_phi_lagrange[cell][3 * nbmat + 1] =
              vars.m_u_lagrange[cell][3 * nbmat + 1] / somme_masse;
      }
      // Phi energie
      for (int imat = 0; imat < nbmat; imat++) {
      if (vars.m_u_lagrange[cell][nbmat + imat] != 0.)
          vars.m_phi_lagrange[cell][2 * nbmat + imat] =
              vars.m_u_lagrange[cell][2 * nbmat + imat] /
              vars.m_u_lagrange[cell][nbmat + imat];
      else
          vars.m_phi_lagrange[cell][2 * nbmat + imat] = 0.;
      }
      // Phi energie cinétique
      if (options()->conservationEnergieTotale == 1)
        vars.m_phi_lagrange[cell][3 * nbmat + 2] =
          vars.m_u_lagrange[cell][3 * nbmat + 2] / somme_masse;

    } else {
        // somme_volume doit etre égale à m_cell_volume[cell]
      for (Integer ivar = 0; ivar < nb_vars_to_project; ivar++) {
        vars.m_phi_lagrange[cell][ivar] = vars.m_u_lagrange[cell][ivar] / somme_volume;
      }
    }
    // Mises à jour de l'indicateur mailles mixtes
    Integer imatcell(0);
    Integer imatpure(-1);
    for (int imat = 0; imat < nbmat; imat++)
      if (vars.m_phi_lagrange[cell][imat] > 0.) {
        imatcell++;
        imatpure = imat;
      }
    if (imatcell > 1) {
      vars.m_est_mixte[cell] = 1;
      vars.m_est_pure[cell] = -1;
    } else {
      vars.m_est_mixte[cell] = 0;
      vars.m_est_pure[cell] = imatpure;
    }
  }
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void RemapADIService::
computeUremapPBorn0(RemapADIComputeUremapPBorn0Vars& vars, const Integer idir, const Integer nb_vars_to_project, const Integer nb_env)
{
//  Real threshold = options()->threshold;
  int nbmat = nb_env;
  Real deltat = m_global_deltat();
          
  for (Integer ivar = 0; ivar < nb_vars_to_project; ivar++) {  
  
    auto queue = m_acc_env->newQueue();
    queue.setAsync(true);
    auto command = makeCommand(queue);
    
    auto cfc = m_acc_env->connectivityView().cellFace();
    
    auto in_face_normal          = ax::viewIn(command, vars.m_face_normal         );
    auto in_face_normal_velocity = ax::viewIn(command, vars.m_face_normal_velocity);
    auto in_face_length_lagrange = ax::viewIn(command, vars.m_face_length_lagrange);
    auto in_outer_face_normal    = ax::viewIn(command, vars.m_outer_face_normal   );
    auto in_phi_face             = ax::viewIn(command, vars.m_phi_face            );
    
    auto out_dual_phi_flux = ax::viewInOut(command, vars.m_dual_phi_flux );
    auto out_u_lagrange    = ax::viewInOut(command, vars.m_u_lagrange    );
    
    command << RUNCOMMAND_ENUMERATE(Cell, cid, allCells()) {
      
      out_dual_phi_flux[cid][ivar] = 0.;
      
      Real flux = 0.;
      Real flux_face = 0.;
      
      // On a besoin de la variable index car m_outer_face_normal a été rempli suivant 
      // le parcours ENUMERATE_CELL(cell,allCells()) -> ENUMERATE_FACE(face,cell.faces())
      // m_outer_face_normal[cell][face.index()] = ...
      // Sur GPU, on a gardé le meme pattern cell -> cell.faces(), ainsi pour accéder à 
      // m_outer_face_normal[cell][face.index()], il suffit d'un int que l'on incrémente
      // au fur et à mesure du parcours faces(cell). (pas besoin de face_index_in_cells finalement)
      Integer index = 0;
      for( FaceLocalId fid : cfc.faces(cid) ) {
        Real in_face_normal_face_idir = in_face_normal[fid][idir];
        if (std::fabs(in_face_normal_face_idir) >= 1.0E-10) {
          Real face_normal_velocity(in_face_normal_velocity[fid]);
          Real face_length(in_face_length_lagrange[fid][idir]);
          Real3 outer_face_normal(in_outer_face_normal[cid][index]);
          Real outer_face_normal_dir = outer_face_normal[idir];
          flux = outer_face_normal_dir * face_normal_velocity * face_length * deltat * in_phi_face[fid][ivar];
          flux_face += flux;
          out_dual_phi_flux[cid][ivar] += 0.5 * flux * outer_face_normal[idir];
        }
        ++index;
      }
      out_u_lagrange[cid][ivar] = out_u_lagrange[cid][ivar] - flux_face;
    }; 
  }
  
  // On fait les diagnostics et controles 
  {
    auto queue = m_acc_env->newQueue();
    auto command = makeCommand(queue);
    
    auto out_est_mixte = ax::viewOut(command, vars.m_est_mixte);
    auto out_est_pure  = ax::viewOut(command, vars.m_est_pure);
    
    auto inout_u_lagrange   = ax::viewInOut(command, vars.m_u_lagrange);
    auto inout_phi_lagrange = ax::viewInOut(command, vars.m_phi_lagrange);
    
    command << RUNCOMMAND_ENUMERATE(Cell, cid, allCells()) {
      for (int imat = 0; imat < nbmat; imat++) {
        if (inout_u_lagrange[cid][nbmat + imat] < 0.) {
          inout_u_lagrange[cid][nbmat + imat] = 0.;
        }
        if (inout_u_lagrange[cid][2*nbmat + imat] < 0.) {
          inout_u_lagrange[cid][2*nbmat + imat] = 0.;
        }
      }
      
      // Calcul du volume de la maille apres 
      double somme_volume = 0.;
      for (int imat = 0; imat < nbmat; imat++) {
        somme_volume += inout_u_lagrange[cid][imat];
      }
      
      // somme_volume doit etre égale à m_cell_volume[cell]
      for (Integer ivar = 0; ivar < nb_vars_to_project; ivar++) {
        inout_phi_lagrange[cid][ivar] = inout_u_lagrange[cid][ivar] / somme_volume;
      }
      
      // Mises à jour de l'indicateur mailles mixtes   
      Integer imatcell(0);
      Integer imatpure(-1);  
      for (int imat = 0; imat < nbmat; imat++) {
        if (inout_phi_lagrange[cid][imat] > 0.) {
          imatcell++;
          imatpure = imat;
        }  
        if (imatcell > 1) {
          out_est_mixte[cid] = 1;
          out_est_pure[cid] = -1;
        } else {
          out_est_mixte[cid] = 0;
          out_est_pure[cid] = imatpure;
        }
      }
    };
  }
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void RemapADIService::
appliRemap(RemapADIAppliRemapVars& vars, const Integer dimension, const Integer withDualProjection, const Integer nb_vars_to_project, const Integer nb_env)
{
  RemapAdi::RemapADIServiceBase<RemapADIService>::synchronizeUremap();  
  RemapAdi::RemapADIServiceBase<RemapADIService>::synchronizeDualUremap();
  
  Integer idir(-1);
  m_cartesian_mesh = CartesianInterface::ICartesianMesh::getReference(mesh());
  
  for( Integer i=0; i< mesh()->dimension(); ++i){
    
    idir = (i + m_sens_projection())%(mesh()->dimension());
    // cas 2D : epaisseur de une maillage dans la direciton de projection
    if (m_cartesian_mesh->cellDirection(idir).globalNbCell() == 1) continue;
    
    // calcul des gradients des quantites à projeter aux faces 
    RemapAdi::RemapADIServiceBase<RemapADIService>::computeGradPhiFace(idir, nb_vars_to_project, nb_env);
    // calcul des gradients des quantites à projeter aux cellules
    // (avec limiteur ordinaire) 
    // et pour le pente borne, calcul des flux aux faces des cellules
    RemapAdi::RemapADIServiceBase<RemapADIService>::computeGradPhiCell(idir, nb_vars_to_project, nb_env);
    // calcul de m_phi_face
    // qui contient la valeur reconstruite à l'ordre 1, 2 ou 3 des variables projetees 
    // et qui contient les flux des variables projetees avec l'option pente-borne
    RemapAdi::RemapADIServiceBase<RemapADIService>::computeUpwindFaceQuantitiesForProjection(idir, nb_vars_to_project, nb_env);
    
    
    RemapAdi::RemapADIServiceBase<RemapADIService>::computeUremap(idir, nb_vars_to_project, nb_env);
    RemapAdi::RemapADIServiceBase<RemapADIService>::synchronizeUremap();
    
    if (withDualProjection) {
      RemapAdi::RemapADIServiceBase<RemapADIService>::computeDualUremap(idir, nb_env);
      RemapAdi::RemapADIServiceBase<RemapADIService>::synchronizeDualUremap();
    }
  }
  m_sens_projection = m_sens_projection()+1;
  m_sens_projection = m_sens_projection()%(mesh()->dimension());
  
  // recuperation des quantités aux cells et aux envcell
  RemapAdi::RemapADIServiceBase<RemapADIService>::remapVariables(dimension,  withDualProjection,  nb_vars_to_project,  nb_env);
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void RemapADIService::
resizeRemapVariables(RemapADIResizeRemapVariablesVars& vars, const Integer nb_vars_to_project, const Integer nb_env)
{
  vars.m_u_lagrange.resize(nb_vars_to_project);
  vars.m_u_dual_lagrange.resize(nb_vars_to_project);
  vars.m_phi_lagrange.resize(nb_vars_to_project);
  vars.m_phi_dual_lagrange.resize(nb_vars_to_project);
  vars.m_dual_grad_phi.resize(nb_vars_to_project);
  vars.m_grad_phi.resize(nb_vars_to_project);
  vars.m_phi_face.resize(nb_vars_to_project);
  vars.m_grad_phi_face.resize(nb_vars_to_project);
  vars.m_delta_phi_face_ar.resize(nb_vars_to_project);
  vars.m_delta_phi_face_av.resize(nb_vars_to_project);
  vars.m_dual_phi_flux.resize(nb_vars_to_project);
  vars.m_front_flux_mass_env.resize(nb_env);
  vars.m_back_flux_mass_env.resize(nb_env);
  vars.m_back_flux_contrib_env.resize(nb_env);
  vars.m_front_flux_contrib_env.resize(nb_env);
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void RemapADIService::
synchronizeUremap(RemapADISynchronizeUremapVars& vars)
{
#if 0
    vars.m_phi_lagrange.synchronize(); // INUTILE ?
    vars.m_u_lagrange.synchronize();
    vars.m_dual_phi_flux.synchronize();
    vars.m_est_mixte.synchronize();
    vars.m_est_pure.synchronize();
#else
    MeshVariableSynchronizerList mvsl(m_acc_env->vsyncMng());

    mvsl.add(vars.m_phi_lagrange); // INUTILE ?
    mvsl.add(vars.m_u_lagrange);
    mvsl.add(vars.m_dual_phi_flux);
    mvsl.add(vars.m_est_mixte);
    mvsl.add(vars.m_est_pure);

    auto queue_synchronize = m_acc_env->refQueueAsync();
    m_acc_env->vsyncMng()->synchronize(mvsl, queue_synchronize);
#endif
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

ARCANE_REGISTER_SERVICE_REMAPADI(RemapADI, RemapADIService);

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace RemapAdi
