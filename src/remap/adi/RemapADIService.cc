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
      
      int limiter = options()->projectionLimiteurId;
      if ((options()->getProjectionLimiteurPureId() == 1) && voisinage_pure)
        limiter = options()->projectionLimiteurPureId;
      // calcul de m_grad_phi[cell] 
      computeAndLimitGradPhi(limiter, frontFace, backFace, cell, frontcell, backcell, nb_vars_to_project);
      

      if (options()->projectionPenteBorne == 1) {
        // if (cstmesh->cylindrical_mesh) exy = varlp->faceNormal(flFaces);
        Real Flux_sortant_ar = math::dot(vars.m_outer_face_normal[cell][indexbackface], dirproj) * vars.m_face_normal_velocity[backFace];
        // if (cstmesh->cylindrical_mesh) exy = varlp->faceNormal(frFaces);
        Real Flux_sortant_av = math::dot(vars.m_outer_face_normal[cell][indexfrontface], dirproj) * vars.m_face_normal_velocity[frontFace];
        
        Real flux_dual = 0.5 * (Flux_sortant_ar + Flux_sortant_av);
        
        Integer calcul_flux_dual(1); // a supprimer - calcul du flux dual fait en pente borne
        
        RealUniqueArray delta_phi_face(nb_vars_to_project);
        RealUniqueArray dual_phi_flux(nb_vars_to_project);
       
        // calcul de m_delta_phi_face_ar et m_dual_phi_flux
        if (voisinage_pure)
            computeFluxPPPure(cell, frontcell, backcell, Flux_sortant_ar, 
                            deltat, 0, options()->threshold, 
                            options()->projectionPenteBorneDebarFix, flux_dual,
                            calcul_flux_dual, delta_phi_face, dual_phi_flux,
                            nb_env, nb_vars_to_project);
        else
            computeFluxPP(cell, frontcell, backcell, Flux_sortant_ar, 
                            deltat, 0, options()->threshold, 
                            options()->projectionPenteBorneDebarFix, flux_dual,
                            calcul_flux_dual, delta_phi_face, dual_phi_flux,
                            nb_env, nb_vars_to_project);
            
        for (Integer ivar = 0; ivar < nb_vars_to_project; ivar++) {    
            vars.m_delta_phi_face_ar[cell][ivar] = delta_phi_face[ivar];
            // et pour avoir un flux dual 2D
            vars.m_dual_phi_flux[cell][ivar] = dual_phi_flux[ivar] * 
            0.5 * (vars.m_face_length_lagrange[backFace][idir] + vars.m_face_length_lagrange[frontFace][idir]);
        }
        // calcul de m_delta_phi_face_av
        if (voisinage_pure)
            computeFluxPPPure(cell, frontcell, backcell, Flux_sortant_av, 
                            deltat, 1, options()->threshold, 
                            options()->projectionPenteBorneDebarFix, flux_dual,
                            calcul_flux_dual, delta_phi_face, dual_phi_flux,
                            nb_env, nb_vars_to_project);
        else
            computeFluxPP(cell, frontcell, backcell, Flux_sortant_av, 
                            deltat, 1, options()->threshold, 
                            options()->projectionPenteBorneDebarFix, flux_dual,
                            calcul_flux_dual, delta_phi_face, dual_phi_flux,
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
  PROF_ACC_BEGIN(__FUNCTION__);
  debug() << " Entree dans computeGradPhiCell_PBorn0_LimC()";

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

  PROF_ACC_END;
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void RemapADIService::
computeDualGradPhi_LimC(RemapADIComputeDualGradPhi_LimCVars& vars, const Integer idir)
{
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void RemapADIService::
computeUpwindFaceQuantitiesForProjection(RemapADIComputeUpwindFaceQuantitiesForProjectionVars& vars, const Integer idir, const Integer nb_vars_to_project, const Integer nb_env)
{
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void RemapADIService::
computeUpwindFaceQuantitiesForProjection_PBorn0_O2(RemapADIComputeUpwindFaceQuantitiesForProjection_PBorn0_O2Vars& vars, const Integer idir, const Integer nb_vars_to_project)
{
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void RemapADIService::
computeUremap(RemapADIComputeUremapVars& vars, const Integer idir, const Integer nb_vars_to_project, const Integer nb_env)
{
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void RemapADIService::
computeUremap_PBorn0(RemapADIComputeUremap_PBorn0Vars& vars, const Integer idir, const Integer nb_vars_to_project, const Integer nb_env)
{
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void RemapADIService::
computeDualUremap(RemapADIComputeDualUremapVars& vars)
{
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void RemapADIService::
appliRemap(RemapADIAppliRemapVars& vars, const Integer dimension, const Integer withDualProjection, const Integer nb_vars_to_project, const Integer nb_env)
{
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void RemapADIService::
resizeRemapVariables(RemapADIResizeRemapVariablesVars& vars, const Integer nb_vars_to_project, const Integer nb_env)
{
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void RemapADIService::
synchronizeUremap(RemapADISynchronizeUremapVars& vars)
{
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void RemapADIService::
remapVariables(RemapADIRemapVariablesVars& vars, const Integer dimension, const Integer withDualProjection, const Integer nb_vars_to_project, const Integer nb_env)
{
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

ARCANE_REGISTER_SERVICE_REMAPADI(RemapADI, RemapADIService);

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace RemapAdi
