#include "RemapADIService.h"

namespace RemapAdi {

/*!
 *******************************************************************************
 * \file computeDualVerticalGradPhi
 * \brief Calcul du grandient des variables duales 
 *        par appel à computeAndLimitGradPhi
 *        construction des grandients top et bottom et des largeurs h des 
 *        mailles duales
 * \param  pNodes
 * \return valeur du gradient dual et limité
 *******************************************************************************
 */
void RemapADIService::
computeDualGradPhi(RemapADIComputeDualGradPhiVars& vars,
        const Node inode,
        const Node frontfrontnode,
        const Node frontnode,
        const Node backnode,
        const Node backbacknode,
        const Integer idir) {
    
  Real3 grad_front(0. , 0. , 0.);
  Real3 grad_back(0. , 0. , 0.);
  Types_mahyco::Limiteur limiter = options()->projectionLimiteurId;
  
  // gradient vitesse X selon la direction idir
  grad_front[0] = (vars.m_phi_dual_lagrange[frontnode][0] - vars.m_phi_dual_lagrange[inode][0]) /
                (vars.m_node_coord[frontnode][idir] - vars.m_node_coord[inode][idir]);

  grad_back[0] = (vars.m_phi_dual_lagrange[inode][0] - vars.m_phi_dual_lagrange[backnode][0]) /
                (vars.m_node_coord[inode][idir] - vars.m_node_coord[backnode][idir]);

  // gradient vitesse Y selon la direction idir
  grad_front[1] = (vars.m_phi_dual_lagrange[frontnode][1] - vars.m_phi_dual_lagrange[inode][1]) /
                (vars.m_node_coord[frontnode][idir] - vars.m_node_coord[inode][idir]);

  grad_back[1] = (vars.m_phi_dual_lagrange[inode][1] - vars.m_phi_dual_lagrange[backnode][1]) /
                (vars.m_node_coord[inode][idir] - vars.m_node_coord[backnode][idir]);

  // gradient vitesse Z selon la direction idir
  grad_front[2] = (vars.m_phi_dual_lagrange[frontnode][2] - vars.m_phi_dual_lagrange[inode][2]) /
                (vars.m_node_coord[frontnode][idir] - vars.m_node_coord[inode][idir]);

  grad_back[2] = (vars.m_phi_dual_lagrange[inode][2] - vars.m_phi_dual_lagrange[backnode][2]) /
                (vars.m_node_coord[inode][idir] - vars.m_node_coord[backnode][idir]);

  // largeurs des mailles duales
  Real hmoins, h0, hplus;
  h0 = 0.5 * (vars.m_node_coord[frontnode][idir]- vars.m_node_coord[backnode][idir]);
  if (backbacknode.localId() == -1) {
    hmoins = 0.;
    hplus = 0.5 * (vars.m_node_coord[frontfrontnode][idir]- vars.m_node_coord[inode][idir]);
  } else if (frontfrontnode.localId() == -1) {
    hplus = 0.;
    hmoins = 0.5 * (vars.m_node_coord[inode][idir] - vars.m_node_coord[backbacknode][idir]);
  } else {
    hmoins = 0.5 * (vars.m_node_coord[inode][idir] - vars.m_node_coord[backbacknode][idir]);
    hplus = 0.5 * (vars.m_node_coord[frontfrontnode][idir]- vars.m_node_coord[inode][idir]);
  }

  // la fonction appelee ici
  RemapADIServiceBase<RemapADIService>::computeAndLimitGradPhiDual(limiter, 
                             inode, frontnode, backnode,
                             grad_front, grad_back, 
                             h0, hplus, hmoins);
  // std::cout << " Nodes " << pNode << " gradV " << res << std::endl;
  // std::cout << " Nodes " << BottomBottomNode << " " << BottomNode << " " <<
  //   pNode << " " <<  TopNode << " " << TopTopNode << std::endl;   if (projectionLimiterId < minmodG) {
}

/*!
 *******************************************************************************
 * \file computeAndLimitGradPhi
 * \brief Calcul du grandient des variables  (phi) à partir
 *        des mailles et des faces amonts : backcell et backFace
 *        et avals : frontcell et frontFace 
 * \param  
 * \return valeur du gradient limité de chaque variables phi
 *******************************************************************************
 */
void RemapADIService::
computeAndLimitGradPhi(RemapADIComputeAndLimitGradPhiVars& vars,
        Types_mahyco::Limiteur projectionLimiterId, Face frontFace, Face backFace, 
        Cell cell, Cell frontcell, Cell backcell, int nb_vars) {
    
   if (projectionLimiterId < Types_mahyco::Limiteur::MinmodG) {
     // info() << " Passage gradient limite Classique ";
    for (Integer ivar = 0; ivar < nb_vars; ivar++) {
      vars.m_grad_phi[cell][ivar] = 0.;
      if (vars.m_grad_phi_face[backFace][ivar] != 0.) 
        vars.m_grad_phi[cell][ivar] += 0.5 * (
                RemapAdi::RemapADIServiceBase<RemapADIService>::fluxLimiter(projectionLimiterId, 
                    vars.m_grad_phi_face[frontFace][ivar] /
                    vars.m_grad_phi_face[backFace][ivar]) 
                    * vars.m_grad_phi_face[backFace][ivar]);
     if (vars.m_grad_phi_face[frontFace][ivar] !=0.) 
        vars.m_grad_phi[cell][ivar] += 0.5 * (
                RemapAdi::RemapADIServiceBase<RemapADIService>::fluxLimiter(projectionLimiterId, 
                    vars.m_grad_phi_face[backFace][ivar] /
                    vars.m_grad_phi_face[frontFace][ivar]) 
                    * vars.m_grad_phi_face[frontFace][ivar]);
    }
  } else {
    // info() << " Passage gradient limite Genéralisé ";
    for (Integer ivar = 0; ivar < nb_vars; ivar++) {
      vars.m_grad_phi[cell][ivar] =
          RemapAdi::RemapADIServiceBase<RemapADIService>::fluxLimiterG(projectionLimiterId, vars.m_grad_phi_face[frontFace][ivar], 
                       vars.m_grad_phi_face[backFace][ivar], vars.m_phi_lagrange[cell][ivar],
                       vars.m_phi_lagrange[frontcell][ivar], vars.m_phi_lagrange[backcell][ivar],
                       vars.m_h_cell_lagrange[cell],
                       vars.m_h_cell_lagrange[frontcell], vars.m_h_cell_lagrange[backcell]);
    }
  }
}

/*!
 ******************************************************************************** 
 * \file computeAndLimitGradPhiDual
 * \brief Calcul du grandient des variables (m_phi_dual_lagrange) à partir
 *        des noeuds amont : backcnode et aval : frontnode 
 * \param  grad_back et grad_front - gradients en amon et aval du noeud
 *          h0,  hplus,  hmoins : largeur des cellules duales
 * \return valeur du gradient limité  m_dual_grad_phi
 
 *******************************************************************************
 */
void RemapADIService::
computeAndLimitGradPhiDual(RemapADIComputeAndLimitGradPhiDualVars& vars,
        const Types_mahyco::Limiteur projectionLimiterId,
        const Node inode,
        const Node frontnode,
        const Node backnode,
        const Real3 grad_front,
        const Real3 grad_back,
        const Real h0,
        const Real hplus,
        const Real hmoins) {
    
   if (projectionLimiterId < Types_mahyco::Limiteur::MinmodG) {
     // info() << " Passage gradient limite Classique ";
    for (Integer ivar = 0; ivar < 3; ivar++) {
      vars.m_dual_grad_phi[inode][ivar] = 0.;
      if (grad_back[ivar] != 0. ) 
        vars.m_dual_grad_phi[inode][ivar] += 0.5 *
                RemapAdi::RemapADIServiceBase<RemapADIService>::fluxLimiter(projectionLimiterId, 
                    grad_front[ivar] / grad_back[ivar]) 
                    * grad_back[ivar];
      if (grad_front[ivar] !=0.)
         vars.m_dual_grad_phi[inode][ivar] += 0.5 *
                RemapAdi::RemapADIServiceBase<RemapADIService>::fluxLimiter(projectionLimiterId, 
                    grad_back[ivar] / grad_front[ivar]) 
                    * grad_front[ivar];
    }
  } else {
    // info() << " Passage gradient limite Genéralisé ";
    for (Integer ivar = 0; ivar < 3; ivar++) {
      vars.m_dual_grad_phi[inode][ivar] =
          RemapAdi::RemapADIServiceBase<RemapADIService>::fluxLimiterG(projectionLimiterId, grad_front[ivar], 
                       grad_back[ivar], 
                       vars.m_phi_dual_lagrange[inode][ivar],
                       vars.m_phi_dual_lagrange[frontnode][ivar], vars.m_phi_dual_lagrange[backnode][ivar],
                       h0, hplus, hmoins);
    }
  }
}

/*!
 *******************************************************************************
 * \file fluxLimiter
 * \brief retourne le valeur du limiteur demandé par la méthode classique
 *        qui suppose que les 3 mailles (utilise pour le calcul des gradient)
 *        ont la meme largeur
 * \param  r = gradmoins / gradplus ou gradplus / gradmoins
 * \return valeur du limiteur demandé
 *******************************************************************************
 */
 Real RemapADIService::
 fluxLimiter(RemapADIFluxLimiterVars& vars,
        Types_mahyco::Limiteur projectionLimiterId, Real r) {
  if (projectionLimiterId == Types_mahyco::Limiteur::Minmod) {
    return std::max(0.0, std::min(1.0, r));
  } else if (projectionLimiterId == Types_mahyco::Limiteur::SuperBee) {
    return std::max(0.0, std::max(std::min(2.0 * r, 1.0), std::min(r, 2.0)));
  } else if (projectionLimiterId == Types_mahyco::Limiteur::VanLeer) {
    if (r <= 0.0)
      return 0.0;
    else
      return 2.0 * r / (1.0 + r);
  } else
    return 0.0;  // ordre 1
}

/*!
 *******************************************************************************
 * \file fluxLimiterG
 * \brief retourne le valeur du limiteur demandé par la méthode exacte
 *        qui ne suppose pas que les 3 mailles (utilise pour le calcul des
 *gradient) ont la meme largeur (h0 != hplus != hmoins) \param  h0, hplus,
 *hmoins, gradplus, gradmoins \return valeur du limiteur demandé
 *******************************************************************************
 */
Real RemapADIService::
fluxLimiterG(RemapADIFluxLimiterGVars& vars,
        const Types_mahyco::Limiteur projectionLimiterId,
        const Real gradplus,
        const Real gradmoins,
        const Real y0,
        const Real yplus,
        const Real ymoins,
        const Real h0,
        const Real hplus,
        const Real hmoins) {
  Real grady=0., gradM, gradMplus, gradMmoins;
  // limitation rupture de pente (formule 16 si on utilise pas le plateau pente)
  if (gradplus * gradmoins < 0.0) return 0.;

  if (projectionLimiterId == Types_mahyco::Limiteur::MinmodG)  // formule 9c
  {
    if ((yplus - ymoins) > 0.)
      grady = std::min(fabs(gradplus), fabs(gradmoins));
    else
      grady = -std::min(fabs(gradplus), fabs(gradmoins));
  } else if (projectionLimiterId == Types_mahyco::Limiteur::SuperBeeG)  // formule 9g
  {
    if ((yplus - ymoins) > 0.)
      grady = std::max(fabs(gradplus), fabs(gradmoins));
    else
      grady = -std::max(fabs(gradplus), fabs(gradmoins));
  } else if (projectionLimiterId == Types_mahyco::Limiteur::VanLeerG)  // formule 9e
  {
    Real lambdaplus = (h0 / 2. + hplus) / (h0 + hplus + hmoins);
    Real lambdamoins = (h0 / 2. + hmoins) / (h0 + hplus + hmoins);
    if ((lambdaplus * gradplus + lambdamoins * gradmoins) != 0.) {
      grady = gradplus * gradmoins /
              (lambdaplus * gradplus + lambdamoins * gradmoins);
    } else
      grady = 0.;
  } else if (projectionLimiterId == Types_mahyco::Limiteur::UltrabeeG) {
    grady = (yplus - ymoins) / h0;
  } else if (projectionLimiterId == Types_mahyco::Limiteur::ArithmeticG) {
    Real lambdaplus = (h0 / 2. + hplus) / (h0 + hplus + hmoins);
    Real lambdamoins = (h0 / 2. + hmoins) / (h0 + hplus + hmoins);
    grady = lambdamoins * gradplus + lambdaplus * gradmoins;
  }
  // limitation simple-pente (formule 10)
  gradMplus = gradplus * (h0 + hplus) / h0;
  gradMmoins = gradmoins * (h0 + hmoins) / h0;
  gradM = std::min(fabs(gradMplus), fabs(gradMmoins));
  if ((yplus - ymoins) > 0.)
    grady = std::min(fabs(gradM), fabs(grady));
  else
    grady = -std::min(fabs(gradM), fabs(grady));

  return grady;
}

/*!
 *******************************************************************************
 * \file computeFluxPP
 * \brief Calcul des flux pente-borne à partir des valeurs des variables 
 *  sur 3 mailles moins, 0, plus
 *  On integre sur -h0/2 et -h0/2.+partie_positive_v pour le flux à gauche (type 0)
 *  On integre sur  h0/2.-partie_positive_v et h0/2 pour le flux à droite (type 1)
 *
 *  pour les mailles mixtes ou celles à voisinages mixtes 
 *     on deduit des flux des volumes partiels, les flux des masses partielles
 *     dm = rho * dv
 *     on deduit des flux des masses partielles, les flux d'energie et de vitesse
 *     d(me) = e * (dm)
 *     rho est soit la valeur dans la maille de la densite 
 *     soit et une valeur reconstruite a par des flux (option complet)
 *     e celle dans la maille de l'energie interne
 *     soit et une valeur reconstruite a par des flux (option complet)
 *
 *  On calcule de la meme facon des flux "duales" en integrant
 *  entre 0 et partie_positive_v pour le flux duale 
 * \param 
 * \return flux des variables phi
 *******************************************************************************
 */
void RemapADIService::
computeFluxPP(RemapADIComputeFluxPPVars& vars,
        const Cell cell,
        const Cell frontcell,
        const Cell backcell,
        const Real face_normal_velocity,
        const Real deltat_n,
        const Integer type,
        const Real flux_threshold,
        const Integer projectionPenteBorneDebarFix,
        const Real dual_normal_velocity,
        const Integer calcul_flux_dual,
        RealArrayView* Flux_ptr,
        RealArrayView* Flux_dual_ptr,
        const Integer nbmat,
        const Integer nb_vars)
{
  RealUniqueArray Flux = *Flux_ptr;
  RealUniqueArray Flux_dual = *Flux_dual_ptr;
  Flux.fill(0.0);
  Flux_dual.fill(0.0);

  Real y0plus, y0moins, xd, xg, yd, yg;
  Real flux1, flux2, flux3, flux1m, flux2m, flux3m;
  Real partie_positive_v = 0.5 * (face_normal_velocity + abs(face_normal_velocity)) * deltat_n;
  Real partie_positive_dual_v = 0.5 * (dual_normal_velocity + abs(dual_normal_velocity)) * deltat_n;
  for (Integer ivar = 0; ivar < nb_vars; ivar++) {
    Real h0 = vars.m_h_cell_lagrange[cell];
    Real hplus = vars.m_h_cell_lagrange[frontcell];
    Real hmoins = vars.m_h_cell_lagrange[backcell];
    // calcul des seuils y0plus, y0moins pour cCells
    y0plus = RemapAdi::RemapADIServiceBase<RemapADIService>::computeY0(options()->projectionLimiteurId, 
                        vars.m_phi_lagrange[cell][ivar],        
                        vars.m_phi_lagrange[frontcell][ivar], 
                        vars.m_phi_lagrange[backcell][ivar], 
                        h0, hplus, hmoins, 0);
    
    y0moins = RemapAdi::RemapADIServiceBase<RemapADIService>::computeY0(options()->projectionLimiteurId, 
                        vars.m_phi_lagrange[cell][ivar],        
                        vars.m_phi_lagrange[frontcell][ivar], 
                        vars.m_phi_lagrange[backcell][ivar], 
                        h0, hplus, hmoins, 1);
    // calcul des points d'intersections xd,xg
    xg = RemapAdi::RemapADIServiceBase<RemapADIService>::computexgxd(vars.m_phi_lagrange[cell][ivar], 
                    vars.m_phi_lagrange[frontcell][ivar], 
                    vars.m_phi_lagrange[backcell][ivar], 
                    h0, y0plus, y0moins, 0);
    xd = RemapAdi::RemapADIServiceBase<RemapADIService>::computexgxd(vars.m_phi_lagrange[cell][ivar], 
                    vars.m_phi_lagrange[frontcell][ivar], 
                    vars.m_phi_lagrange[backcell][ivar], 
                    h0, y0plus, y0moins, 1);
    // calcul des valeurs sur ces points d'intersections
    yg = RemapAdi::RemapADIServiceBase<RemapADIService>::computeygyd(vars.m_phi_lagrange[cell][ivar], 
                    vars.m_phi_lagrange[frontcell][ivar], 
                    vars.m_phi_lagrange[backcell][ivar], 
                    h0, y0plus, y0moins, vars.m_grad_phi[cell][ivar], 0);
    yd = RemapAdi::RemapADIServiceBase<RemapADIService>::computeygyd(vars.m_phi_lagrange[cell][ivar], 
                    vars.m_phi_lagrange[frontcell][ivar], 
                    vars.m_phi_lagrange[backcell][ivar], 
                    h0, y0plus, y0moins, vars.m_grad_phi[cell][ivar], 1);
    //  
    if (type == 0)  
        // flux arriere ou en dessous de cCells, integration entre
        // -h0/2. et -h0/2.+abs(face_normal_velocity)*deltat_n
    {
      // Flux1m : integrale -inf,  -h0/2.+partie_positive_v
      flux1m = RemapAdi::RemapADIServiceBase<RemapADIService>::intY(-h0 / 2. + partie_positive_v, -h0 / 2., vars.m_phi_lagrange[backcell][ivar], xg, yg);
      // Flux1m : integrale -inf,  -h0/2.
      flux1 = RemapAdi::RemapADIServiceBase<RemapADIService>::intY(-h0 / 2., -h0 / 2., vars.m_phi_lagrange[backcell][ivar], xg, yg);
      // Flux2m : integrale -inf,  -h0/2.+partie_positive_v
      flux2m = RemapAdi::RemapADIServiceBase<RemapADIService>::intY(-h0 / 2. + partie_positive_v, xg, yg, xd, yd);
      // Flux2 : integrale -inf,  -h0/2.
      flux2 = RemapAdi::RemapADIServiceBase<RemapADIService>::intY(-h0 / 2., xg, yg, xd, yd);
      // Flux3m : integrale -inf,  -h0/2.+partie_positive_v
      flux3m = RemapAdi::RemapADIServiceBase<RemapADIService>::intY(-h0 / 2. + partie_positive_v, xd, yd, h0 / 2., vars.m_phi_lagrange[frontcell][ivar]);
      // Flux3 : integrale -inf,  -h0/2.
      flux3 = RemapAdi::RemapADIServiceBase<RemapADIService>::intY(-h0 / 2., xd, yd, h0 / 2., vars.m_phi_lagrange[frontcell][ivar]);
      // integrale positive
      Flux[ivar] = std::max(
          ((flux1m - flux1) + (flux2m - flux2) + (flux3m - flux3)), 0.);
      // formule 16
      if (((vars.m_phi_lagrange[frontcell][ivar] - vars.m_phi_lagrange[cell][ivar]) * 
          (vars.m_phi_lagrange[backcell][ivar] - vars.m_phi_lagrange[cell][ivar])) >= 0.)
      Flux[ivar] = vars.m_phi_lagrange[cell][ivar] * partie_positive_v;
      
      //
      // et calcul du flux dual si calcul_flux_dual=1
      if (calcul_flux_dual == 1) {
      // Flux1m : integrale -inf, partie_positive_dual_v
      flux1m = RemapADIServiceBase<RemapADIService>::intY(partie_positive_dual_v, -h0 / 2., vars.m_phi_lagrange[backcell][ivar], xg, yg);
      // Flux1m : integrale -inf,  0..
      flux1 = RemapAdi::RemapADIServiceBase<RemapADIService>::intY(0., -h0 / 2., vars.m_phi_lagrange[backcell][ivar], xg, yg);
      // Flux2m : integrale -inf, partie_positive_dual_v
      flux2m = RemapAdi::RemapADIServiceBase<RemapADIService>::intY(partie_positive_dual_v, xg, yg, xd, yd);
      // Flux2 : integrale -inf, 0.
      flux2 = RemapAdi::RemapADIServiceBase<RemapADIService>::intY(0., xg, yg, xd, yd);
      // Flux3m : integrale -inf, partie_positive_dual_v
      flux3m = RemapAdi::RemapADIServiceBase<RemapADIService>::intY(partie_positive_dual_v, xd, yd, h0 / 2., vars.m_phi_lagrange[frontcell][ivar]);
      // Flux3 : integrale -inf, 0.
      flux3 = RemapAdi::RemapADIServiceBase<RemapADIService>::intY(0., xd, yd, h0 / 2., vars.m_phi_lagrange[frontcell][ivar]);
      // integrale positive
      Flux_dual[ivar] = std::max(
          ((flux1m - flux1) + (flux2m - flux2) + (flux3m - flux3)), 0.);
      // formule 16
      if (((vars.m_phi_lagrange[frontcell][ivar] - vars.m_phi_lagrange[cell][ivar]) * 
          (vars.m_phi_lagrange[backcell][ivar] - vars.m_phi_lagrange[cell][ivar])) >= 0.)
          Flux_dual[ivar] = vars.m_phi_lagrange[cell][ivar] * partie_positive_dual_v;
      //
      }
    } else if (type == 1) {
        // flux devant ou au dessus de cCells, integration entre
        // h0/2.-abs(face_normal_velocity)*deltat_n et h0/2.
        // Flux1 : integrale -inf,  h0/2.-partie_positive_v
        flux1 = RemapAdi::RemapADIServiceBase<RemapADIService>::intY(h0 / 2. - partie_positive_v, -h0 / 2., vars.m_phi_lagrange[backcell][ivar], xg, yg);
        // Flux1m : integrale -inf,  -h0/2.
        flux1m = RemapAdi::RemapADIServiceBase<RemapADIService>::intY(h0 / 2., -h0 / 2., vars.m_phi_lagrange[backcell][ivar], xg, yg);
        //
        // Flux2 : integrale -inf,  h0/2.-partie_positive_v
        flux2 = RemapAdi::RemapADIServiceBase<RemapADIService>::intY(h0 / 2. - partie_positive_v, xg, yg, xd, yd);
        // Flux2m : integrale -inf,  -h0/2.
        flux2m = RemapAdi::RemapADIServiceBase<RemapADIService>::intY(h0 / 2., xg, yg, xd, yd);
        //
        // Flux3 : integrale -inf,  h0/2.-partie_positive_v
        flux3 = RemapAdi::RemapADIServiceBase<RemapADIService>::intY(h0 / 2. - partie_positive_v, xd, yd, h0 / 2., vars.m_phi_lagrange[frontcell][ivar] );
        // Flux3m : integrale -inf,  -h0/2.
        flux3m = RemapAdi::RemapADIServiceBase<RemapADIService>::intY(h0 / 2., xd, yd, h0 / 2., vars.m_phi_lagrange[frontcell][ivar] );
        //
        // integrale positive
        Flux[ivar] = std::max(
            ((flux1m - flux1) + (flux2m - flux2) + (flux3m - flux3)), 0.);
        // formule 16
        if (((vars.m_phi_lagrange[frontcell][ivar] - vars.m_phi_lagrange[cell][ivar]) * 
            (vars.m_phi_lagrange[backcell][ivar] - vars.m_phi_lagrange[cell][ivar])) >= 0.)
        Flux[ivar] = vars.m_phi_lagrange[cell][ivar] * partie_positive_v;
        //
        // et calcul du flux dual si calcul_flux_dual=1
        if (calcul_flux_dual == 1) {
        // flux dual deja calculé lors du premier appel à la fonction
        Flux_dual[ivar] = 0.;
        }
    }
  }
  if (projectionPenteBorneDebarFix == 1) {
    // pinfo() << "projectionPenteBorneDebarFix" << projectionPenteBorneDebarFix;
    // les flux de masse se déduisent des flux de volume en utilisant une valeur
    // moyenne de Rho calculée par le flux de masse / flux de volume Celles des
    // energies massiques avec une valeur moyenne de e calculée par le flux
    // d'energie / flux de volume Celles de quantité de mouvement avec une
    // valeur moyenne de u calculée par le flux de vitesse / flux de volume
    Real somme_flux_masse = 0.;
    Real somme_flux_volume = 0.;
    for (int imat = 0; imat < nbmat; imat++) somme_flux_volume += Flux[imat];

    if (std::fabs(somme_flux_volume) > flux_threshold ) {
      for (int imat = 0; imat < nbmat; imat++) {
        Flux[nbmat + imat] =
            (Flux[nbmat + imat] / somme_flux_volume) * Flux[imat];
        Flux[2. * nbmat + imat] =
            (Flux[2. * nbmat + imat] / somme_flux_volume) * Flux[nbmat + imat];
        somme_flux_masse += Flux[nbmat + imat];
      }

      Flux[3 * nbmat] = (Flux[3 * nbmat] / somme_flux_volume) *
                        somme_flux_masse;  // flux de quantité de mouvement x
      Flux[3 * nbmat + 1] =
          (Flux[3 * nbmat + 1] / somme_flux_volume) *
          somme_flux_masse;  // flux de quantité de mouvement y
      Flux[3 * nbmat + 2] =
          (Flux[3 * nbmat + 2] / somme_flux_volume) * somme_flux_masse;
      Flux[3 * nbmat + 3] =
          vars.m_phi_lagrange[cell][3 * nbmat + 3] * somme_flux_volume;  // flux pour la pseudo VNR
    } else {
      Flux.fill(0.);
    }
  } else if (projectionPenteBorneDebarFix == 2) {
    // pinfo() << "projectionPenteBorneDebarFix" << projectionPenteBorneDebarFix;
    // les flux de masse, de quantité de mouvement et d'energie massique se
    // deduisent des flux de volumes avec la valeur de rho, e et u à la maille
    Real somme_flux_masse = 0.;
    Real somme_flux_volume = 0.;
    for (int imat = 0; imat < nbmat; imat++) {
      Flux[nbmat + imat] =
          vars.m_phi_lagrange[cell][nbmat + imat] * Flux[imat];  // flux de masse de imat
      Flux[2 * nbmat + imat] =
          vars.m_phi_lagrange[cell][2 * nbmat + imat] *
          Flux[nbmat + imat];  // flux de masse energy de imat
      somme_flux_masse += Flux[nbmat + imat];
      somme_flux_volume += Flux[imat];
    }
    Flux[3 * nbmat] =
        vars.m_phi_lagrange[cell][3 * nbmat] * somme_flux_masse;  // flux de quantité de mouvement x
    Flux[3 * nbmat + 1] = vars.m_phi_lagrange[cell][3 * nbmat + 1] *
                          somme_flux_masse;  // flux de quantité de mouvement y
    Flux[3 * nbmat + 2] =
        vars.m_phi_lagrange[cell][3 * nbmat + 2] * somme_flux_masse;  // flux d'energie cinetique
    Flux[3 * nbmat + 3] =
        vars.m_phi_lagrange[cell][3 * nbmat + 3] * somme_flux_volume;  // flux pour la pseudo VNR
  }

  if (partie_positive_v == 0.) Flux.fill(0.);
  if (partie_positive_dual_v == 0.) Flux_dual.fill(0.);

  return;
}

/*!
 *******************************************************************************
 * \file computeY0
 * \brief calcul des Seuils de monotonie des reconstructions lineraires
 *  simple-pente pour l'option pente-borne
 *
 * \param  h0, hplus, hmoins, y0, yplus, ymoins
 * \return y0plus, y0moins
 *******************************************************************************
 */
Real RemapADIService::
computeY0(RemapADIComputeY0Vars& vars,
        const Types_mahyco::Limiteur projectionLimiterId,
        const Real y0,
        const Real yplus,
        const Real ymoins,
        const Real h0,
        const Real hplus,
        const Real hmoins,
        const Integer type)
{
  // retourne {{y0plus, y0moins}}
  Real y0plus = 0., y0moins = 0.;
  if (projectionLimiterId == Types_mahyco::Limiteur::MinmodG ||
      projectionLimiterId == Types_mahyco::Limiteur::Minmod)  // minmod
  {
    y0plus = yplus;
    y0moins = ymoins;
  } else if (projectionLimiterId == Types_mahyco::Limiteur::SuperBeeG ||
             projectionLimiterId == Types_mahyco::Limiteur::SuperBee)  // superbee
  {
    y0plus = ((h0 + hmoins) * yplus + h0 * ymoins) / (2 * h0 + hmoins);
    y0moins = ((h0 + hplus) * ymoins + h0 * yplus) / (2 * h0 + hplus);
  } else if (projectionLimiterId == Types_mahyco::Limiteur::VanLeerG ||
             projectionLimiterId == Types_mahyco::Limiteur::VanLeer)  // vanleer
  {
    Real a = math::min(yplus, ymoins);
    Real b = math::max(yplus, ymoins);
    Real xplus = (h0 * h0 + 3 * h0 * hmoins + 2 * hmoins * hmoins) * yplus;
    Real xmoins = (h0 * h0 + 3 * h0 * hplus + 2 * hplus * hplus) * ymoins;
    xplus +=
        (h0 * h0 - h0 * hplus - 2 * hplus * hplus + 2 * h0 * hmoins) * ymoins;
    xmoins +=
        (h0 * h0 - h0 * hmoins - 2 * hmoins * hmoins + 2 * h0 * hplus) * yplus;
    xplus /= (2 * h0 * h0 + 5 * h0 * hmoins + 2 * hmoins * hmoins - h0 * hplus -
              2 * hplus * hplus);
    xmoins /= (2 * h0 * h0 + 5 * h0 * hplus + 2 * hplus * hplus - h0 * hmoins -
               2 * hmoins * hmoins);

    y0plus = math::min(math::max(xplus, a), b);
    y0moins = math::min(math::max(xmoins, a), b);
  } else if (projectionLimiterId == Types_mahyco::Limiteur::UltrabeeG) {
    y0plus = (yplus + ymoins) / 2.;
    y0moins = (yplus + ymoins) / 2.;
  } else if (projectionLimiterId == Types_mahyco::Limiteur::ArithmeticG) {
    y0plus = ((h0 + hmoins + hplus) * yplus + h0 * ymoins) /
             (2 * h0 + hmoins + hplus);
    y0moins = ((h0 + hmoins + hplus) * ymoins + h0 * yplus) /
              (2 * h0 + hmoins + hplus);
  }
  // What to do here? What is 3000?
  // else if (projectionLimiterId == 3000) {
  //   y0plus = yplus;
  //   y0moins = ymoins;
  // }
  if (type == 0)
    return y0plus;
  else if (type == 1)
    return y0moins;
  else
    return 0.0;  // lancer forcement avec type 0 ou 1 mais warning compile
}

/*!
 *******************************************************************************
 * \file computexgxd
 * \brief calcul des absisses des points d'appui de la reconstruction en 3
 *morceaux
 *
 * \param  h0, hplus, hmoins, y0, yplus, ymoins
 * \return xg, xd
 *******************************************************************************
 */
Real RemapADIService::
computexgxd(RemapADIComputexgxdVars& vars,
        const Real y0,
        const Real yplus,
        const Real ymoins,
        const Real h0,
        const Real y0plus,
        const Real y0moins,
        const Integer type)
{
  // retourne {{xg, xd}}
  Real xd = 0., xg = 0.;
  Real xplus = 1.;
  if (abs(y0plus - yplus) > options()->threshold)
    xplus = (y0 - yplus) / (y0plus - yplus) - 1. / 2.;
  Real xmoins = 1.;
  if (abs(y0moins - ymoins) > options()->threshold)
    xmoins = (y0 - ymoins) / (y0moins - ymoins) - 1. / 2.;
  xd = +h0 * math::min(math::max(xplus, -1. / 2.), 1. / 2.);
  xg = -h0 * math::min(math::max(xmoins, -1. / 2.), 1. / 2.);
  if (type == 0)
    return xg;
  else if (type == 1)
    return xd;
  else
    return 0.0;  // lancer forcement avec type 0 ou 1 mais warning compile
}

/*!
 *******************************************************************************
 * \file computeygyd
 * \brief calcul des ordonnees des points d'appui de la reconstruction en 3
 *morceaux
 *
 * \param  h0, hplus, hmoins, y0, yplus, ymoins
 * \return yg, yd
 *******************************************************************************
 */
Real RemapADIService::
computeygyd(RemapADIComputeygydVars& vars,
        const Real y0,
        const Real yplus,
        const Real ymoins,
        const Real h0,
        const Real y0plus,
        const Real y0moins,
        const Real grady,
        const Integer type)
{
  // retourne {{yg, yd}}
  Real yd, yg;
  Real xtd = y0 + h0 / 2 * grady;
  Real xtg = y0 - h0 / 2 * grady;
  Real ad = math::min(yplus, 2. * y0moins - ymoins);
  Real bd = math::max(yplus, 2. * y0moins - ymoins);
  Real ag = math::min(ymoins, 2. * y0plus - yplus);
  Real bg = math::max(ymoins, 2. * y0plus - yplus);
  yd = math::min(math::max(xtd, ad), bd);
  yg = math::min(math::max(xtg, ag), bg);
  if (type == 0)
    return yg;
  else if (type == 1)
    return yd;
  else
    return 0.0;  // lancer forcement avec type 0 ou 1 mais warning compile
}

/*!
 *******************************************************************************
 * \file intY
 * \brief calcul de l'integrale de -infini à X de la fonction lineaire
 *    1_[x0,x1] ((x1 − x)y0 + (x − x0)y1)/(x1-x0)
 *    valant :
 *     y0 + 0.5 δ(y1 − y0)(x1 − x0)δ ou δ = S_[0,1]((X − x0)/(x1 − x0))
 *     zt S_[0,1](x) = min{max{x, 0}, 1}
 * \param  X, x0, y0, x1, y1
 * \return  valeur de l'integral
 *******************************************************************************
 */
 Real RemapADIService::
 intY(RemapADIIntYVars& vars,
        Real X,
        Real x0,
        Real y0,
        Real x1,
        Real y1)
{
  Real flux = 0.;
  // std::cout << " x0 " << x0 << std::endl;
  // std::cout << " x1 " << x1 << std::endl;
  if (abs(x1 - x0) > options()->threshold) {
    Real eta =
        math::min(math::max(0., (X - x0) / (x1 - x0)), 1.);
    // std::cout << " eta " << eta << std::endl;
    flux = (y0 + 0.5 * eta * (y1 - y0)) * (x1 - x0) * eta;
  }
  return flux;
}

/*!
 *******************************************************************************
 * \file computeFluxPPPure
 * \brief Calcul des flux pente-borne à partir des valeurs des variables 
 *  sur 3 mailles moins, 0, plus
 *  utilises pour les mailles pures à voisinages pures, 
 *  On integre sur -h0/2 et -h0/2.+partie_positive_v pour le flux à gauche (type 0)
 *  On integre sur  h0/2.-partie_positive_v et h0/2 pour le flux à droite (type 1)
 *
 *     on deduit des flux des volumes partiels, les flux des masses partielles
 *     dm = rho * dv
 *     on deduit des flux des masses partielles, les flux d'energie et de vitesse
 *     d(me) = e * (dm)
 *     rho est soit la valeur dans la maille de la densite 
 *     soit et une valeur reconstruite a par des flux (option complet)
 *     e celle dans la maille de l'energie interne
 *     soit et une valeur reconstruite a par des flux (option complet)
 *
 *  On calcule de la meme facon des flux "duales" en integrant
 *  entre 0 et partie_positive_v pour le flux duale 
 * \param 
 * \return Flux, Flux_dual
 *******************************************************************************
 */
void RemapADIService::
computeFluxPPPure(RemapADIComputeFluxPPPureVars& vars,
        Cell cell,
        Cell frontcell,
        Cell backcell, 
        Real face_normal_velocity, 
        Real deltat_n,
        Integer type,
        Real flux_threshold, 
        Integer projectionPenteBorneDebarFix, 
        Real dual_normal_velocity,
        Integer calcul_flux_dual,
        RealArrayView* Flux_ptr,
        RealArrayView* Flux_dual_ptr,
        int nbmat,
        int nb_vars)
{
  RealArrayView Flux = *Flux_ptr;
  RealArrayView Flux_dual = *Flux_dual_ptr;
  Flux.fill(0.0);
  Flux_dual.fill(0.0);   
  Real y0plus, y0moins, xd, xg, yd, yg;
  Real flux1, flux2, flux3, flux1m, flux2m, flux3m;
  Real partie_positive_v = 0.5 * (face_normal_velocity + abs(face_normal_velocity)) * deltat_n;
  Real partie_positive_dual_v = 0.5 * (dual_normal_velocity + abs(dual_normal_velocity)) * deltat_n;
  // on ne fait que la projection des volumes et masses
  for (Integer ivar = 0; ivar < nb_vars; ivar++) {
    Real h0 = vars.m_h_cell_lagrange[cell];
    Real hplus = vars.m_h_cell_lagrange[frontcell];
    Real hmoins = vars.m_h_cell_lagrange[backcell];
    // calcul des seuils y0plus, y0moins pour cCells
    y0plus = RemapAdi::RemapADIServiceBase<RemapADIService>::computeY0(options()->projectionLimiteurPureId,
                         vars.m_phi_lagrange[cell][ivar],        
                         vars.m_phi_lagrange[frontcell][ivar], 
                         vars.m_phi_lagrange[backcell][ivar], 
                         h0, hplus, hmoins, 0);
      
    y0moins = RemapAdi::RemapADIServiceBase<RemapADIService>::computeY0(options()->projectionLimiteurPureId,
                         vars.m_phi_lagrange[cell][ivar],        
                         vars.m_phi_lagrange[frontcell][ivar], 
                         vars.m_phi_lagrange[backcell][ivar], 
                         h0, hplus, hmoins, 1);
    // calcul des points d'intersections xd,xg
    xg = RemapAdi::RemapADIServiceBase<RemapADIService>::computexgxd(vars.m_phi_lagrange[cell][ivar], 
                      vars.m_phi_lagrange[frontcell][ivar], 
                      vars.m_phi_lagrange[backcell][ivar], 
                      h0, y0plus, y0moins, 0);
    xd = RemapAdi::RemapADIServiceBase<RemapADIService>::computexgxd(vars.m_phi_lagrange[cell][ivar], 
                      vars.m_phi_lagrange[frontcell][ivar], 
                      vars.m_phi_lagrange[backcell][ivar], 
                      h0, y0plus, y0moins, 1);
    // calcul des valeurs sur ces points d'intersections
    yg = RemapAdi::RemapADIServiceBase<RemapADIService>::computeygyd(vars.m_phi_lagrange[cell][ivar], 
                      vars.m_phi_lagrange[frontcell][ivar], 
                      vars.m_phi_lagrange[backcell][ivar], 
                      h0, y0plus, y0moins, vars.m_grad_phi[cell][ivar], 0);
    yd = RemapAdi::RemapADIServiceBase<RemapADIService>::computeygyd(vars.m_phi_lagrange[cell][ivar], 
                      vars.m_phi_lagrange[frontcell][ivar], 
                      vars.m_phi_lagrange[backcell][ivar], 
                      h0, y0plus, y0moins, vars.m_grad_phi[cell][ivar], 1);
     //  

    if (type == 0)  // flux arriere ou en dessous de cCells, integration entre
                    // -h0/2. et -h0/2.+abs(face_normal_velocity)*deltat_n
    {
      // Flux1m : integrale -inf,  -h0/2.+partie_positive_v
      flux1m = RemapAdi::RemapADIServiceBase<RemapADIService>::intY(-h0 / 2. + partie_positive_v, -h0 / 2., vars.m_phi_lagrange[backcell][ivar], xg, yg);
      // Flux1m : integrale -inf,  -h0/2.
      flux1 = RemapAdi::RemapADIServiceBase<RemapADIService>::intY(-h0 / 2., -h0 / 2., vars.m_phi_lagrange[backcell][ivar], xg, yg);
      //
      // Flux2m : integrale -inf,  -h0/2.+partie_positive_v
      flux2m = RemapAdi::RemapADIServiceBase<RemapADIService>::intY(-h0 / 2. + partie_positive_v, xg, yg, xd, yd);
      // Flux2 : integrale -inf,  -h0/2.
      flux2 = RemapAdi::RemapADIServiceBase<RemapADIService>::intY(-h0 / 2., xg, yg, xd, yd);
      //
      // Flux3m : integrale -inf,  -h0/2.+partie_positive_v
      flux3m = RemapAdi::RemapADIServiceBase<RemapADIService>::intY(-h0 / 2. + partie_positive_v, xd, yd, h0 / 2., vars.m_phi_lagrange[frontcell][ivar]);
      // Flux3 : integrale -inf,  -h0/2.
      flux3 = RemapAdi::RemapADIServiceBase<RemapADIService>::intY(-h0 / 2., xd, yd, h0 / 2., vars.m_phi_lagrange[frontcell][ivar]);
      //
      // integrale positive
      Flux[ivar] = std::max(
          ((flux1m - flux1) + (flux2m - flux2) + (flux3m - flux3)), 0.);
      // formule 16
      if (((vars.m_phi_lagrange[frontcell][ivar] - vars.m_phi_lagrange[cell][ivar]) * 
          (vars.m_phi_lagrange[backcell][ivar] - vars.m_phi_lagrange[cell][ivar])) >= 0.) 
        Flux[ivar] = vars.m_phi_lagrange[cell][ivar]  * partie_positive_v;
      //
      // et calcul du flux dual si calcul_flux_dual=1
      if (calcul_flux_dual == 1) {
        // Flux1m : integrale -inf, partie_positive_dual_v
        flux1m = RemapAdi::RemapADIServiceBase<RemapADIService>::intY(partie_positive_dual_v, -h0 / 2., vars.m_phi_lagrange[backcell][ivar], xg, yg);
        // Flux1m : integrale -inf,  0..
        flux1 = RemapAdi::RemapADIServiceBase<RemapADIService>::intY(0., -h0 / 2., vars.m_phi_lagrange[backcell][ivar], xg, yg);
        // Flux2m : integrale -inf, partie_positive_dual_v
        flux2m = RemapAdi::RemapADIServiceBase<RemapADIService>::intY(partie_positive_dual_v, xg, yg, xd, yd);
        // Flux2 : integrale -inf, 0.
        flux2 = RemapAdi::RemapADIServiceBase<RemapADIService>::intY(0., xg, yg, xd, yd);
        // Flux3m : integrale -inf, partie_positive_dual_v
        flux3m = RemapAdi::RemapADIServiceBase<RemapADIService>::intY(partie_positive_dual_v, xd, yd, h0 / 2., vars.m_phi_lagrange[frontcell][ivar]);
        // Flux3 : integrale -inf, 0.
        flux3 = RemapAdi::RemapADIServiceBase<RemapADIService>::intY(0., xd, yd, h0 / 2., vars.m_phi_lagrange[frontcell][ivar]);
        // integrale positive
        Flux_dual[ivar] = std::max(
            ((flux1m - flux1) + (flux2m - flux2) + (flux3m - flux3)), 0.);
        // formule 16
        if (((vars.m_phi_lagrange[frontcell][ivar] - vars.m_phi_lagrange[cell][ivar]) * 
          (vars.m_phi_lagrange[backcell][ivar] - vars.m_phi_lagrange[cell][ivar])) >= 0.)
          Flux_dual[ivar] = vars.m_phi_lagrange[cell][ivar] * partie_positive_dual_v;
        //
      }
    } else if (type == 1) {
      // flux devant ou au dessus de cCells, integration entre
      // h0/2.-abs(face_normal_velocity)*deltat_n et h0/2.
      // Flux1 : integrale -inf,  h0/2.-partie_positive_v
      flux1 = RemapAdi::RemapADIServiceBase<RemapADIService>::intY(h0 / 2. - partie_positive_v, -h0 / 2., vars.m_phi_lagrange[backcell][ivar], xg, yg);
      // Flux1m : integrale -inf,  -h0/2.
      flux1m = RemapAdi::RemapADIServiceBase<RemapADIService>::intY(h0 / 2., -h0 / 2., vars.m_phi_lagrange[backcell][ivar], xg, yg);
      // Flux2 : integrale -inf,  h0/2.-partie_positive_v
      flux2 = RemapAdi::RemapADIServiceBase<RemapADIService>::intY(h0 / 2. - partie_positive_v, xg, yg, xd, yd);
      // Flux2m : integrale -inf,  -h0/2.
      flux2m = RemapAdi::RemapADIServiceBase<RemapADIService>::intY(h0 / 2., xg, yg, xd, yd);
      //
      // Flux3 : integrale -inf,  h0/2.-partie_positive_v
      flux3 = RemapAdi::RemapADIServiceBase<RemapADIService>::intY(h0 / 2. - partie_positive_v, xd, yd, h0 / 2., vars.m_phi_lagrange[frontcell][ivar]);
      // Flux3m : integrale -inf,  -h0/2.
      flux3m = RemapAdi::RemapADIServiceBase<RemapADIService>::intY(h0 / 2., xd, yd, h0 / 2., vars.m_phi_lagrange[frontcell][ivar]);
      // integrale positive
      Flux[ivar] = std::max(
          ((flux1m - flux1) + (flux2m - flux2) + (flux3m - flux3)), 0.);
      // formule 16
      if (((vars.m_phi_lagrange[frontcell][ivar] - vars.m_phi_lagrange[cell][ivar]) * 
          (vars.m_phi_lagrange[backcell][ivar] - vars.m_phi_lagrange[cell][ivar])) >= 0.)
        Flux[ivar] = vars.m_phi_lagrange[cell][ivar] * partie_positive_v;
      // et calcul du flux dual si calcul_flux_dual=1
      if (calcul_flux_dual == 1) {
        // flux dual deja calculé lors du premier appel à la fonction
        Flux_dual[ivar] = 0.;
      }
    }
  }
  if (projectionPenteBorneDebarFix == 1) {
    // les flux d' energie se déduisent des flux de masse en utilisant 
    // une valeur moyenne de e calculée par le flux
    // d'energie / flux de volume Celles de quantité de mouvement avec une
    // valeur moyenne de u calculée par le flux de vitesse / flux de volume
    Real somme_flux_masse = 0.;
    Real somme_flux_volume = 0.;
    for (int imat = 0; imat < nbmat; imat++) somme_flux_volume += Flux[imat];

    if (std::fabs(somme_flux_volume) > flux_threshold ) {
      for (int imat = 0; imat < nbmat; imat++) {
        Flux[2. * nbmat + imat] =
            (Flux[2. * nbmat + imat] / somme_flux_volume) * Flux[nbmat + imat];
        somme_flux_masse += Flux[nbmat + imat];
      }

      Flux[3 * nbmat] = (Flux[3 * nbmat] / somme_flux_volume) *
                        somme_flux_masse;  // flux de quantité de mouvement x
      Flux[3 * nbmat + 1] =
          (Flux[3 * nbmat + 1] / somme_flux_volume) *
          somme_flux_masse;  // flux de quantité de mouvement y
      Flux[3 * nbmat + 2] =
          (Flux[3 * nbmat + 2] / somme_flux_volume) * somme_flux_masse;
      Flux[3 * nbmat + 3] =
          vars.m_phi_lagrange[cell][3 * nbmat + 3] * somme_flux_volume;  // flux pour la pseudo VNR
    } else {
      Flux.fill(0.);
    }
  } else if (projectionPenteBorneDebarFix == 2) {
    // les flux d'energie massique se
    // deduisent des flux de volumes * densite (dans phi)
    Real somme_flux_masse = 0.;
    Real somme_flux_volume = 0.;
    for (int imat = 0; imat < nbmat; imat++) {
      Flux[2 * nbmat + imat] =
          vars.m_phi_lagrange[cell][2 * nbmat + imat] *
          Flux[nbmat + imat];  // flux de masse energy de imat
      somme_flux_masse += Flux[nbmat + imat];
      somme_flux_volume += Flux[imat];
    }
    Flux[3 * nbmat] =
        vars.m_phi_lagrange[cell][3 * nbmat] * somme_flux_masse;  // flux de quantité de mouvement x
    Flux[3 * nbmat + 1] = vars.m_phi_lagrange[cell][3 * nbmat + 1] *
                          somme_flux_masse;  // flux de quantité de mouvement y
    Flux[3 * nbmat + 2] =
        vars.m_phi_lagrange[cell][3 * nbmat + 2] * somme_flux_masse;  // flux d'energie cinetique
    Flux[3 * nbmat + 3] =
        vars.m_phi_lagrange[cell][3 * nbmat + 3] * somme_flux_volume;  // flux pour la pseudo VNR
  }

  if (partie_positive_v == 0.) {
    Flux.fill(0.);
  }
  if (partie_positive_dual_v == 0.) {
    Flux_dual.fill(0.);
  }
  return;
}

/*!
 *******************************************************************************
 * \file computeRemapFlux
 * \brief Calcul final des flux
 *  cas classique : phi_face * v * dt * l * (n.ex ou n.ey)
 *  phi_face contient la valeur de phi reconstruite à l'ordre voulu
 *  cas pente-borne : phi_face * l * (n.ex ou n.ey)
 *  phi_face contient deja le flux integre
 * \param  
 * \return valeur de phi 
 *******************************************************************************
 */
Real RemapADIService::
computeRemapFlux(RemapADIComputeRemapFluxVars& vars,
        [[maybe_unused]] Integer projectionOrder, Integer projectionAvecPlateauPente,
        Real face_normal_velocity, [[maybe_unused]] Real3 face_normal,
        Real face_length, Real phi_face,
        Real3 outer_face_normal, Real3 exy, Real deltat_n) {
    
  if (projectionAvecPlateauPente == 0) {
    // cas projection ordre 3 ou 1 ou 2 sans plateau pente (flux calculé ici
    // avec phi_face)
    return (math::dot(outer_face_normal, exy) * face_normal_velocity * face_length * deltat_n * phi_face);
  } else {
    // cas projection ordre 2 avec plateau pente (flux dans la variable
    // phi_face)
    return (math::dot(outer_face_normal, exy) * face_length * phi_face);
  }
}

// fonctions pour l'ordre 3
// ----------------------------------
// fonction pour evaluer le gradient
Real RemapADIService::
evaluate_grad(Real hm, Real h0, Real hp, Real ym,
                            Real y0, Real yp) {
  Real grad;
  grad = h0 / (hm + h0 + hp) *
         ((2. * hm + h0) / (h0 + hp) * (yp - y0) +
          (h0 + 2. * hp) / (hm + h0) * (y0 - ym));
  return grad;
}
// ----------------------------------
// fonction pour évaluer ystar
Real RemapADIService::
evaluate_ystar(Real hmm, Real hm, Real hp, Real hpp,
                             [[maybe_unused]] Real ymm, Real ym, Real yp, [[maybe_unused]] Real ypp,
                             Real gradm, Real gradp) {
  Real ystar, tmp1, tmp2;
  tmp1 = (2. * hp * hm) / (hm + hp) *
         ((hmm + hm) / (2. * hm + hp) - (hpp + hp) / (2. * hp + hm)) *
         (yp - ym);
  tmp2 = -hm * (hmm + hm) / (2. * hm + hp) * gradp +
         hp * (hp + hpp) / (hm + 2. * hp) * gradm;
  ystar = ym + hm / (hm + hp) * (yp - ym) +
          1. / (hmm + hm + hp + hpp) * (tmp1 + tmp2);
  return ystar;
}
// ----------------------------------
// fonction pour évaluer fm
Real RemapADIService::
evaluate_fm(Real x, Real dx, Real up, Real du,
                          Real u6) {
  Real fm;
  fm = up - 0.5 * x / dx * (du - (1. - 2. / 3. * x / dx) * u6);
  return fm;
}
// ----------------------------------
// fonction pour évaluer fr
Real RemapADIService::
evaluate_fp(Real x, Real dx, Real um, Real du,
                          Real u6) {
  Real fp;
  fp = um + 0.5 * x / dx * (du - (1. - 2. / 3. * x / dx) * u6);
  return fp;
}
// ----------------------------------
// fonction pour initialiser la structure interval
Real2 RemapADIService::
define_interval(Real a, Real b) {
  Real2 I;
  I[0] = math::min(a, b);
  I[1] = math::max(a, b);
  return I;
}
// ----------------------------------
// fonction pour calculer l'intersection entre deux intervals
Real2 RemapADIService::
intersection(Real2 I1, Real2 I2) {
  Real2 I;
  if ((I1[1] < I2[0]) || (I2[1] < I1[0])) {
    I[0] = 0.;
    I[1] = 0.;
  } else {
    I[0] = math::max(I1[0], I2[0]);
    I[1] = math::min(I1[1], I2[1]);
  }
  return I;
}
// ----------------------------------
// fonction pour calculer le flux
Real RemapADIService::
ComputeFluxOrdre3(Real ymmm, Real ymm, Real ym, Real yp,
                                Real ypp, Real yppp, Real hmmm,
                                Real hmm, Real hm, Real hp, Real hpp,
                                Real hppp, Real vdt) {

  Real flux=0.;
  Real gradmm, gradm, gradp, gradpp;
  Real ystarm, ystar, ystarp;
  Real ym_m, ym_p, yp_m, yp_p;
  Real grad_m, grad_p, ym6, yp6;
  //
  gradmm = evaluate_grad(hmmm, hmm, hm, ymmm, ymm, ym);
  gradm = evaluate_grad(hmm, hm, hp, ymm, ym, yp);
  gradp = evaluate_grad(hm, hp, hpp, ym, yp, ypp);
  gradpp = evaluate_grad(hp, hpp, hppp, yp, ypp, yppp);
  //
  ystarm = evaluate_ystar(hmmm, hmm, hm, hp, ymmm, ymm, ym, yp, gradmm, gradm);
  ystar = evaluate_ystar(hmm, hm, hp, hpp, ymm, ym, yp, ypp, gradm, gradp);
  ystarp = evaluate_ystar(hm, hp, hpp, hppp, ym, yp, ypp, yppp, gradp, gradpp);
  //
  ym_m = ystarm;
  ym_p = ystar;
  yp_m = ystar;
  yp_p = ystarp;
  //
  grad_m = ym_p - ym_m;
  grad_p = yp_p - yp_m;
  //
  ym6 = 6. * (ym - 0.5 * (ym_m + ym_p));
  yp6 = 6. * (yp - 0.5 * (yp_m + yp_p));
  //
  if (vdt > 0.) {
    flux = evaluate_fm(vdt, hm, ym_p, grad_m, ym6);
  } else if (vdt < 0.) {
    flux = evaluate_fp(-vdt, hp, yp_m, grad_p, yp6);
  } else if (vdt == 0.) {
    return 0.;
  }
  // Limitation TVD
  Real num, nup, ym_ym, yp_ym;
  Real2 I1, I2, limiteur;
  num = vdt / hm;
  nup = vdt / hp;
  ym_ym = ym + (1. - num) / num * (ym - ymm);
  yp_ym = yp - (1. + nup) / nup * (yp - ypp);
  
  if (vdt >= 0.) {
    I1 = define_interval(ym, yp);
    I2 = define_interval(ym, ym_ym);
  } else {
    I1 = define_interval(ym, yp);
    I2 = define_interval(yp, yp_ym);
  }
  limiteur = intersection(I1, I2);
  if (flux < limiteur[0]) {
    flux = limiteur[0];
  }
  if (flux > limiteur[1]) {
    flux = limiteur[1];
  }
  //
  return flux;
}

}