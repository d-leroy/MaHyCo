#ifndef REMAP_ADI___REMAPADISERVICEBASE_H
#define REMAP_ADI___REMAPADISERVICEBASE_H

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#include "arcane/ArcaneTypes.h"
#include "arcane/ItemTypes.h"
#include "arcane/Item.h"
#include "arcane/ItemVector.h"
#include "arcane/ItemVectorView.h"
#include "arcane/VariableTypes.h"
#include "arcane/utils/Array.h"
#include "arcane/materials/ComponentItemVector.h"
#include "arcane/materials/ComponentItemVectorView.h"
#include "arcane/materials/MeshEnvironmentVariableRef.h"
#include "arcane/materials/MeshMaterialVariableRef.h"
#include "arcane/materials/IMeshMaterialMng.h"
#include "remap/__IRemap.h"
#include "remap/adi/__RemapADIServiceVars.h"
#include "types_mahyco/__Limiteur.h"
#include "remap/adi/AdiTypeDeclarations.h"
#include "remap/adi/RemapADI_axl.h"
#include "remap/adi/__RemapADIServiceSciHookMacros.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

using namespace Arcane;
using namespace Arcane::Materials;
namespace RemapAdi {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

/*!
 * \brief Service RemapADI : classe de base. 
 * 
 */
template<class T>
class RemapADIServiceBase
: public ArcaneRemapADIObject
{
 SCIHOOK_DECLARE_REMAP_ADI_REMAPADI_EVENTS

 public:  // ***** CONSTRUCTEUR & DESTRUCTEUR
  explicit RemapADIServiceBase(const ServiceBuildInfo& bi)
  : ArcaneRemapADIObject(bi)
  , m_mesh_material_mng(IMeshMaterialMng::getReference(bi.mesh()))
  {
    SCIHOOK_INITIALIZE_REMAP_ADI_REMAPADI_EVENTS
  }

  virtual ~RemapADIServiceBase()
  {
  }

 public:  // ***** ACCESSEURS
  Integer getOrdreProjection() { return options()->getOrdreProjection(); }
  Real getThreshold() { return options()->getThreshold(); }
  Real getArithmeticThreshold() { return options()->getArithmeticThreshold(); }
  bool getIsEulerScheme() { return options()->getIsEulerScheme(); }
  bool getConservationEnergieTotale() { return options()->getConservationEnergieTotale(); }
  bool getProjectionPenteBorneMixte() { return options()->getProjectionPenteBorneMixte(); }
  ::Types_mahyco::Limiteur getProjectionLimiteurId() { return options()->getProjectionLimiteurId(); }
  ::Types_mahyco::Limiteur getProjectionLimiteurPureId() { return options()->getProjectionLimiteurPureId(); }
  bool getProjectionPenteBorne() { return options()->getProjectionPenteBorne(); }
  Integer getProjectionPenteBorneDebarFix() { return options()->getProjectionPenteBorneDebarFix(); }
  Integer getCalculFluxMasse() { return options()->getCalculFluxMasse(); }
  const String getImplName() const { return "RemapADIService"; }
  IMeshMaterialMng* getMeshMaterialMng() const { return m_mesh_material_mng; }

 public:  // ***** METHODES CONCRETES
  /*!
   \dot
     digraph synchronizeDualUremapGraph
     {
       compound="true";
       edge [arrowsize="0.5", fontsize="8"];
       node [shape="box", fontname="Arial", fontsize="10"];
       {
         rank=same;
         synchronizeDualUremap [style="rounded, filled", fillcolor="gray"];
         outVars [shape="record", label="phi_dual_lagrange | u_dual_lagrange"];
         synchronizeDualUremap -> outVars;
       }

     }
   \enddot
   Cette méthode construit les variables et appelle RemapADIService::synchronizeDualUremap.
  */
  void synchronizeDualUremap()
  {
    RemapADISynchronizeDualUremapVars vars(m_phi_dual_lagrange
        , m_u_dual_lagrange);
    SCIHOOK_TRIGGER_REMAP_ADI_REMAPADI_SYNCHRONIZEDUALUREMAP_BEFORE
    this->synchronizeDualUremap(vars);
    SCIHOOK_TRIGGER_REMAP_ADI_REMAPADI_SYNCHRONIZEDUALUREMAP_AFTER
  }

  /*!
   \dot
     digraph computeAndLimitGradPhiGraph
     {
       compound="true";
       edge [arrowsize="0.5", fontsize="8"];
       node [shape="box", fontname="Arial", fontsize="10"];
       {
         rank=same;
         computeAndLimitGradPhi [style="rounded, filled", fillcolor="gray"];
         inVars [shape="record", label="grad_phi_face | phi_lagrange | h_cell_lagrange"];
         inVars -> computeAndLimitGradPhi;
         outVars [shape="record", label="grad_phi"];
         computeAndLimitGradPhi -> outVars;
       }

       subgraph clusterCalledFuncs
       {
         center="true";
         color="navy";
         RemapADIServiceBase_fluxLimiter [label="fluxLimiter", color="navy", fontcolor="navy", style="rounded", URL="\ref RemapAdi::RemapADIServiceBase::fluxLimiter"];
         RemapADIServiceBase_fluxLimiterG [label="fluxLimiterG", color="navy", fontcolor="navy", style="rounded", URL="\ref RemapAdi::RemapADIServiceBase::fluxLimiterG"];
       }
       computeAndLimitGradPhi -> RemapADIServiceBase_fluxLimiterG [lhead="clusterCalledFuncs", style="dashed", label=" call"];
     }
   \enddot
   Cette méthode construit les variables et appelle RemapADIService::computeAndLimitGradPhi.
  */
  void computeAndLimitGradPhi(const ::Types_mahyco::Limiteur projectionLimiterId, const Face frontFace, const Face backFace, const Cell cell, const Cell frontcell, const Cell backcell, const Integer nb_vars)
  {
    RemapADIComputeAndLimitGradPhiVars vars(m_grad_phi
        , m_grad_phi_face
        , m_phi_lagrange
        , m_h_cell_lagrange);
    SCIHOOK_TRIGGER_REMAP_ADI_REMAPADI_COMPUTEANDLIMITGRADPHI_BEFORE
    this->computeAndLimitGradPhi(vars, projectionLimiterId, frontFace, backFace, cell, frontcell, backcell, nb_vars);
    SCIHOOK_TRIGGER_REMAP_ADI_REMAPADI_COMPUTEANDLIMITGRADPHI_AFTER
  }

  /*!
   \dot
     digraph computeDualGradPhiGraph
     {
       compound="true";
       edge [arrowsize="0.5", fontsize="8"];
       node [shape="box", fontname="Arial", fontsize="10"];
       {
         rank=same;
         computeDualGradPhi [style="rounded, filled", fillcolor="gray"];
         inVars [shape="record", label="phi_dual_lagrange | node_coord"];
         inVars -> computeDualGradPhi;
       }

       subgraph clusterCalledFuncs
       {
         center="true";
         color="navy";
         RemapADIServiceBase_computeAndLimitGradPhiDual [label="computeAndLimitGradPhiDual", color="navy", fontcolor="navy", style="rounded", URL="\ref RemapAdi::RemapADIServiceBase::computeAndLimitGradPhiDual"];
         RemapADIServiceBase_fluxLimiter [label="fluxLimiter", color="navy", fontcolor="navy", style="rounded", URL="\ref RemapAdi::RemapADIServiceBase::fluxLimiter"];
       }
       computeDualGradPhi -> RemapADIServiceBase_fluxLimiter [lhead="clusterCalledFuncs", style="dashed", label=" call"];
     }
   \enddot
   Cette méthode construit les variables et appelle RemapADIService::computeDualGradPhi.
  */
  void computeDualGradPhi(const Node inode, const Node frontfrontnode, const Node frontnode, const Node backnode, const Node backbacknode, const Integer idir)
  {
    RemapADIComputeDualGradPhiVars vars(m_phi_dual_lagrange
        , m_node_coord);
    SCIHOOK_TRIGGER_REMAP_ADI_REMAPADI_COMPUTEDUALGRADPHI_BEFORE
    this->computeDualGradPhi(vars, inode, frontfrontnode, frontnode, backnode, backbacknode, idir);
    SCIHOOK_TRIGGER_REMAP_ADI_REMAPADI_COMPUTEDUALGRADPHI_AFTER
  }

  /*!
   \dot
     digraph computeAndLimitGradPhiDualGraph
     {
       compound="true";
       edge [arrowsize="0.5", fontsize="8"];
       node [shape="box", fontname="Arial", fontsize="10"];
       {
         rank=same;
         computeAndLimitGradPhiDual [style="rounded, filled", fillcolor="gray"];
         inVars [shape="record", label="phi_dual_lagrange"];
         inVars -> computeAndLimitGradPhiDual;
         outVars [shape="record", label="dual_grad_phi"];
         computeAndLimitGradPhiDual -> outVars;
       }

       subgraph clusterCalledFuncs
       {
         center="true";
         color="navy";
         RemapADIServiceBase_fluxLimiter [label="fluxLimiter", color="navy", fontcolor="navy", style="rounded", URL="\ref RemapAdi::RemapADIServiceBase::fluxLimiter"];
         RemapADIServiceBase_fluxLimiterG [label="fluxLimiterG", color="navy", fontcolor="navy", style="rounded", URL="\ref RemapAdi::RemapADIServiceBase::fluxLimiterG"];
       }
       computeAndLimitGradPhiDual -> RemapADIServiceBase_fluxLimiterG [lhead="clusterCalledFuncs", style="dashed", label=" call"];
     }
   \enddot
   Cette méthode construit les variables et appelle RemapADIService::computeAndLimitGradPhiDual.
  */
  void computeAndLimitGradPhiDual(const ::Types_mahyco::Limiteur projectionLimiterId, const Node inode, const Node frontnode, const Node backnode, const Real3 grad_front, const Real3 grad_back, const Real h0, const Real hplus, const Real hmoins)
  {
    RemapADIComputeAndLimitGradPhiDualVars vars(m_phi_dual_lagrange
        , m_dual_grad_phi);
    SCIHOOK_TRIGGER_REMAP_ADI_REMAPADI_COMPUTEANDLIMITGRADPHIDUAL_BEFORE
    this->computeAndLimitGradPhiDual(vars, projectionLimiterId, inode, frontnode, backnode, grad_front, grad_back, h0, hplus, hmoins);
    SCIHOOK_TRIGGER_REMAP_ADI_REMAPADI_COMPUTEANDLIMITGRADPHIDUAL_AFTER
  }

  /*!
   Cette méthode construit les variables et appelle RemapADIService::fluxLimiter.
  */
  Real fluxLimiter(const ::Types_mahyco::Limiteur projectionLimiterId, const Real r)
  {
    RemapADIFluxLimiterVars vars;
    SCIHOOK_TRIGGER_REMAP_ADI_REMAPADI_FLUXLIMITER_BEFORE
    auto result = this->fluxLimiter(vars, projectionLimiterId, r);
    SCIHOOK_TRIGGER_REMAP_ADI_REMAPADI_FLUXLIMITER_AFTER
    return result;
  }

  /*!
   Cette méthode construit les variables et appelle RemapADIService::fluxLimiterG.
  */
  Real fluxLimiterG(const ::Types_mahyco::Limiteur projectionLimiterId, const Real gradplus, const Real gradmoins, const Real y0, const Real yplus, const Real ymoins, const Real h0, const Real hplus, const Real hmoins)
  {
    RemapADIFluxLimiterGVars vars;
    SCIHOOK_TRIGGER_REMAP_ADI_REMAPADI_FLUXLIMITERG_BEFORE
    auto result = this->fluxLimiterG(vars, projectionLimiterId, gradplus, gradmoins, y0, yplus, ymoins, h0, hplus, hmoins);
    SCIHOOK_TRIGGER_REMAP_ADI_REMAPADI_FLUXLIMITERG_AFTER
    return result;
  }

  /*!
   \dot
     digraph computeFluxPPGraph
     {
       compound="true";
       edge [arrowsize="0.5", fontsize="8"];
       node [shape="box", fontname="Arial", fontsize="10"];
       {
         rank=same;
         computeFluxPP [style="rounded, filled", fillcolor="gray"];
         inVars [shape="record", label="h_cell_lagrange | phi_lagrange | grad_phi"];
         inVars -> computeFluxPP;
       }

       subgraph clusterCalledFuncs
       {
         center="true";
         color="navy";
         RemapADIServiceBase_computeY0 [label="computeY0", color="navy", fontcolor="navy", style="rounded", URL="\ref RemapAdi::RemapADIServiceBase::computeY0"];
         RemapADIServiceBase_computexgxd [label="computexgxd", color="navy", fontcolor="navy", style="rounded", URL="\ref RemapAdi::RemapADIServiceBase::computexgxd"];
         RemapADIServiceBase_computeygyd [label="computeygyd", color="navy", fontcolor="navy", style="rounded", URL="\ref RemapAdi::RemapADIServiceBase::computeygyd"];
         RemapADIServiceBase_intY [label="intY", color="navy", fontcolor="navy", style="rounded", URL="\ref RemapAdi::RemapADIServiceBase::intY"];
       }
       computeFluxPP -> RemapADIServiceBase_intY [lhead="clusterCalledFuncs", style="dashed", label=" call"];
     }
   \enddot
   Cette méthode construit les variables et appelle RemapADIService::computeFluxPP.
  */
  void computeFluxPP(const Cell cell, const Cell frontcell, const Cell backcell, const Real face_normal_velocity, const Real deltat_n, const Integer type, const Real flux_threshold, const Integer projectionPenteBorneDebarFix, const Real dual_normal_velocity, const Integer calcul_flux_dual, ::Arcane::RealArrayView* flux, ::Arcane::RealArrayView* flux_dual, const Integer nbmat, const Integer nb_vars)
  {
    RemapADIComputeFluxPPVars vars(m_h_cell_lagrange
        , m_phi_lagrange
        , m_grad_phi);
    SCIHOOK_TRIGGER_REMAP_ADI_REMAPADI_COMPUTEFLUXPP_BEFORE
    this->computeFluxPP(vars, cell, frontcell, backcell, face_normal_velocity, deltat_n, type, flux_threshold, projectionPenteBorneDebarFix, dual_normal_velocity, calcul_flux_dual, flux, flux_dual, nbmat, nb_vars);
    SCIHOOK_TRIGGER_REMAP_ADI_REMAPADI_COMPUTEFLUXPP_AFTER
  }

  /*!
   Cette méthode construit les variables et appelle RemapADIService::computeY0.
  */
  Real computeY0(const ::Types_mahyco::Limiteur projectionLimiterId, const Real y0, const Real yplus, const Real ymoins, const Real h0, const Real hplus, const Real hmoins, const Integer type)
  {
    RemapADIComputeY0Vars vars;
    SCIHOOK_TRIGGER_REMAP_ADI_REMAPADI_COMPUTEY0_BEFORE
    auto result = this->computeY0(vars, projectionLimiterId, y0, yplus, ymoins, h0, hplus, hmoins, type);
    SCIHOOK_TRIGGER_REMAP_ADI_REMAPADI_COMPUTEY0_AFTER
    return result;
  }

  /*!
   Cette méthode construit les variables et appelle RemapADIService::computexgxd.
  */
  Real computexgxd(const Real y0, const Real yplus, const Real ymoins, const Real h0, const Real y0plus, const Real y0moins, const Integer type)
  {
    RemapADIComputexgxdVars vars;
    SCIHOOK_TRIGGER_REMAP_ADI_REMAPADI_COMPUTEXGXD_BEFORE
    auto result = this->computexgxd(vars, y0, yplus, ymoins, h0, y0plus, y0moins, type);
    SCIHOOK_TRIGGER_REMAP_ADI_REMAPADI_COMPUTEXGXD_AFTER
    return result;
  }

  /*!
   Cette méthode construit les variables et appelle RemapADIService::computeygyd.
  */
  Real computeygyd(const Real y0, const Real yplus, const Real ymoins, const Real h0, const Real y0plus, const Real y0moins, const Real grady, const Integer type)
  {
    RemapADIComputeygydVars vars;
    SCIHOOK_TRIGGER_REMAP_ADI_REMAPADI_COMPUTEYGYD_BEFORE
    auto result = this->computeygyd(vars, y0, yplus, ymoins, h0, y0plus, y0moins, grady, type);
    SCIHOOK_TRIGGER_REMAP_ADI_REMAPADI_COMPUTEYGYD_AFTER
    return result;
  }

  /*!
   Cette méthode construit les variables et appelle RemapADIService::intY.
  */
  Real intY(const Real X, const Real x0, const Real y0, const Real x1, const Real y1)
  {
    RemapADIIntYVars vars;
    SCIHOOK_TRIGGER_REMAP_ADI_REMAPADI_INTY_BEFORE
    auto result = this->intY(vars, X, x0, y0, x1, y1);
    SCIHOOK_TRIGGER_REMAP_ADI_REMAPADI_INTY_AFTER
    return result;
  }

  /*!
   \dot
     digraph computeFluxPPPureGraph
     {
       compound="true";
       edge [arrowsize="0.5", fontsize="8"];
       node [shape="box", fontname="Arial", fontsize="10"];
       {
         rank=same;
         computeFluxPPPure [style="rounded, filled", fillcolor="gray"];
         inVars [shape="record", label="h_cell_lagrange | phi_lagrange | grad_phi"];
         inVars -> computeFluxPPPure;
       }

       subgraph clusterCalledFuncs
       {
         center="true";
         color="navy";
         RemapADIServiceBase_computeY0 [label="computeY0", color="navy", fontcolor="navy", style="rounded", URL="\ref RemapAdi::RemapADIServiceBase::computeY0"];
         RemapADIServiceBase_computexgxd [label="computexgxd", color="navy", fontcolor="navy", style="rounded", URL="\ref RemapAdi::RemapADIServiceBase::computexgxd"];
         RemapADIServiceBase_computeygyd [label="computeygyd", color="navy", fontcolor="navy", style="rounded", URL="\ref RemapAdi::RemapADIServiceBase::computeygyd"];
         RemapADIServiceBase_intY [label="intY", color="navy", fontcolor="navy", style="rounded", URL="\ref RemapAdi::RemapADIServiceBase::intY"];
       }
       computeFluxPPPure -> RemapADIServiceBase_intY [lhead="clusterCalledFuncs", style="dashed", label=" call"];
     }
   \enddot
   Cette méthode construit les variables et appelle RemapADIService::computeFluxPPPure.
  */
  void computeFluxPPPure(const Cell cell, const Cell frontcell, const Cell backcell, const Real face_normal_velocity, const Real deltat_n, const Integer type, const Real flux_threshold, const Integer projectionPenteBorneDebarFix, const Real dual_normal_velocity, const Integer calcul_flux_dual, ::Arcane::RealArrayView* Flux, ::Arcane::RealArrayView* Flux_dual, const Integer nbmat, const Integer nb_vars)
  {
    RemapADIComputeFluxPPPureVars vars(m_h_cell_lagrange
        , m_phi_lagrange
        , m_grad_phi);
    SCIHOOK_TRIGGER_REMAP_ADI_REMAPADI_COMPUTEFLUXPPPURE_BEFORE
    this->computeFluxPPPure(vars, cell, frontcell, backcell, face_normal_velocity, deltat_n, type, flux_threshold, projectionPenteBorneDebarFix, dual_normal_velocity, calcul_flux_dual, Flux, Flux_dual, nbmat, nb_vars);
    SCIHOOK_TRIGGER_REMAP_ADI_REMAPADI_COMPUTEFLUXPPPURE_AFTER
  }

  /*!
   \dot
     digraph computeGradPhiFaceGraph
     {
       compound="true";
       edge [arrowsize="0.5", fontsize="8"];
       node [shape="box", fontname="Arial", fontsize="10"];
       {
         rank=same;
         computeGradPhiFace [style="rounded, filled", fillcolor="gray"];
         inVars [shape="record", label="face_normal | cell_coord | phi_lagrange | face_coord | deltax_lagrange | h_cell_lagrange"];
         inVars -> computeGradPhiFace;
         outVars [shape="record", label="is_dir_face | grad_phi_face | deltax_lagrange | h_cell_lagrange"];
         computeGradPhiFace -> outVars;
       }

     }
   \enddot
   Cette méthode construit les variables et appelle RemapADIService::computeGradPhiFace.
  */
  void computeGradPhiFace(const Integer idir, const Integer nb_vars_to_project, const Integer nb_env)
  {
    RemapADIComputeGradPhiFaceVars vars(m_face_normal
        , m_cell_coord
        , m_phi_lagrange
        , m_face_coord
        , m_is_dir_face
        , m_grad_phi_face
        , m_deltax_lagrange
        , m_h_cell_lagrange);
    SCIHOOK_TRIGGER_REMAP_ADI_REMAPADI_COMPUTEGRADPHIFACE_BEFORE
    this->computeGradPhiFace(vars, idir, nb_vars_to_project, nb_env);
    SCIHOOK_TRIGGER_REMAP_ADI_REMAPADI_COMPUTEGRADPHIFACE_AFTER
  }

  /*!
   \dot
     digraph computeGradPhiCellGraph
     {
       compound="true";
       edge [arrowsize="0.5", fontsize="8"];
       node [shape="box", fontname="Arial", fontsize="10"];
       {
         rank=same;
         computeGradPhiCell [style="rounded, filled", fillcolor="gray"];
         inVars [shape="record", label="outer_face_normal | face_normal_velocity | face_length_lagrange | is_dir_face | est_mixte | est_pure"];
         inVars -> computeGradPhiCell;
         outVars [shape="record", label="grad_phi | dual_phi_flux | delta_phi_face_av | delta_phi_face_ar | est_mixte | est_pure"];
         computeGradPhiCell -> outVars;
       }

     }
   \enddot
   Cette méthode construit les variables et appelle RemapADIService::computeGradPhiCell.
  */
  void computeGradPhiCell(const Integer idir, const Integer nb_vars_to_project, const Integer nb_env)
  {
    RemapADIComputeGradPhiCellVars vars(m_outer_face_normal
        , m_face_normal_velocity
        , m_face_length_lagrange
        , m_is_dir_face
        , m_grad_phi
        , m_dual_phi_flux
        , m_delta_phi_face_av
        , m_delta_phi_face_ar
        , m_est_mixte
        , m_est_pure);
    SCIHOOK_TRIGGER_REMAP_ADI_REMAPADI_COMPUTEGRADPHICELL_BEFORE
    this->computeGradPhiCell(vars, idir, nb_vars_to_project, nb_env);
    SCIHOOK_TRIGGER_REMAP_ADI_REMAPADI_COMPUTEGRADPHICELL_AFTER
  }

  /*!
   \dot
     digraph computeUpwindFaceQuantitiesForProjectionGraph
     {
       compound="true";
       edge [arrowsize="0.5", fontsize="8"];
       node [shape="box", fontname="Arial", fontsize="10"];
       {
         rank=same;
         computeUpwindFaceQuantitiesForProjection [style="rounded, filled", fillcolor="gray"];
         inVars [shape="record", label="face_normal_velocity | deltax_lagrange | phi_lagrange | face_coord | cell_coord | face_normal | grad_phi | delta_phi_face_av | delta_phi_face_ar | h_cell_lagrange | est_mixte | est_pure | phi_face"];
         inVars -> computeUpwindFaceQuantitiesForProjection;
         outVars [shape="record", label="phi_face"];
         computeUpwindFaceQuantitiesForProjection -> outVars;
       }

       subgraph clusterCalledFuncs
       {
         center="true";
         color="navy";
         RemapADIServiceBase_computeUpwindFaceQuantitiesForProjectionPBorn0O2 [label="computeUpwindFaceQuantitiesForProjectionPBorn0O2", color="navy", fontcolor="navy", style="rounded", URL="\ref RemapAdi::RemapADIServiceBase::computeUpwindFaceQuantitiesForProjectionPBorn0O2"];
       }
       computeUpwindFaceQuantitiesForProjection -> RemapADIServiceBase_computeUpwindFaceQuantitiesForProjectionPBorn0O2 [lhead="clusterCalledFuncs", style="dashed", label=" call"];
     }
   \enddot
   Cette méthode construit les variables et appelle RemapADIService::computeUpwindFaceQuantitiesForProjection.
  */
  void computeUpwindFaceQuantitiesForProjection(const Integer idir, const Integer nb_vars_to_project, const Integer nb_env)
  {
    RemapADIComputeUpwindFaceQuantitiesForProjectionVars vars(m_face_normal_velocity
        , m_deltax_lagrange
        , m_phi_lagrange
        , m_face_coord
        , m_cell_coord
        , m_face_normal
        , m_grad_phi
        , m_delta_phi_face_av
        , m_delta_phi_face_ar
        , m_h_cell_lagrange
        , m_est_mixte
        , m_est_pure
        , m_phi_face);
    SCIHOOK_TRIGGER_REMAP_ADI_REMAPADI_COMPUTEUPWINDFACEQUANTITIESFORPROJECTION_BEFORE
    this->computeUpwindFaceQuantitiesForProjection(vars, idir, nb_vars_to_project, nb_env);
    SCIHOOK_TRIGGER_REMAP_ADI_REMAPADI_COMPUTEUPWINDFACEQUANTITIESFORPROJECTION_AFTER
  }

  /*!
   \dot
     digraph computeUpwindFaceQuantitiesForProjectionPBorn0O2Graph
     {
       compound="true";
       edge [arrowsize="0.5", fontsize="8"];
       node [shape="box", fontname="Arial", fontsize="10"];
       {
         rank=same;
         computeUpwindFaceQuantitiesForProjectionPBorn0O2 [style="rounded, filled", fillcolor="gray"];
         inVars [shape="record", label="deltax_lagrange | face_normal_velocity | phi_lagrange | face_coord | face_normal | cell_coord | grad_phi"];
         inVars -> computeUpwindFaceQuantitiesForProjectionPBorn0O2;
         outVars [shape="record", label="phi_face"];
         computeUpwindFaceQuantitiesForProjectionPBorn0O2 -> outVars;
       }

     }
   \enddot
   Cette méthode construit les variables et appelle RemapADIService::computeUpwindFaceQuantitiesForProjectionPBorn0O2.
  */
  void computeUpwindFaceQuantitiesForProjectionPBorn0O2(const Integer idir, const Integer nb_vars_to_project)
  {
    RemapADIComputeUpwindFaceQuantitiesForProjectionPBorn0O2Vars vars(m_deltax_lagrange
        , m_face_normal_velocity
        , m_phi_lagrange
        , m_face_coord
        , m_face_normal
        , m_cell_coord
        , m_grad_phi
        , m_phi_face);
    SCIHOOK_TRIGGER_REMAP_ADI_REMAPADI_COMPUTEUPWINDFACEQUANTITIESFORPROJECTIONPBORN0O2_BEFORE
    this->computeUpwindFaceQuantitiesForProjectionPBorn0O2(vars, idir, nb_vars_to_project);
    SCIHOOK_TRIGGER_REMAP_ADI_REMAPADI_COMPUTEUPWINDFACEQUANTITIESFORPROJECTIONPBORN0O2_AFTER
  }

  /*!
   \dot
     digraph computeUremapGraph
     {
       compound="true";
       edge [arrowsize="0.5", fontsize="8"];
       node [shape="box", fontname="Arial", fontsize="10"];
       {
         rank=same;
         computeUremap [style="rounded, filled", fillcolor="gray"];
         inVars [shape="record", label="face_normal | face_length_lagrange | outer_face_normal | face_normal_velocity | phi_face | u_lagrange | phi_lagrange"];
         inVars -> computeUremap;
         outVars [shape="record", label="dual_phi_flux | est_mixte | est_pure | u_lagrange | phi_lagrange"];
         computeUremap -> outVars;
       }

       subgraph clusterCalledFuncs
       {
         center="true";
         color="navy";
         RemapADIServiceBase_computeUremapPBorn0 [label="computeUremapPBorn0", color="navy", fontcolor="navy", style="rounded", URL="\ref RemapAdi::RemapADIServiceBase::computeUremapPBorn0"];
       }
       computeUremap -> RemapADIServiceBase_computeUremapPBorn0 [lhead="clusterCalledFuncs", style="dashed", label=" call"];
     }
   \enddot
   Cette méthode construit les variables et appelle RemapADIService::computeUremap.
  */
  void computeUremap(const Integer idir, const Integer nb_vars_to_project, const Integer nb_env)
  {
    RemapADIComputeUremapVars vars(m_face_normal
        , m_face_length_lagrange
        , m_outer_face_normal
        , m_face_normal_velocity
        , m_phi_face
        , m_dual_phi_flux
        , m_est_mixte
        , m_est_pure
        , m_u_lagrange
        , m_phi_lagrange);
    SCIHOOK_TRIGGER_REMAP_ADI_REMAPADI_COMPUTEUREMAP_BEFORE
    this->computeUremap(vars, idir, nb_vars_to_project, nb_env);
    SCIHOOK_TRIGGER_REMAP_ADI_REMAPADI_COMPUTEUREMAP_AFTER
  }

  /*!
   \dot
     digraph computeUremapPBorn0Graph
     {
       compound="true";
       edge [arrowsize="0.5", fontsize="8"];
       node [shape="box", fontname="Arial", fontsize="10"];
       {
         rank=same;
         computeUremapPBorn0 [style="rounded, filled", fillcolor="gray"];
         inVars [shape="record", label="face_normal | face_normal_velocity | face_length_lagrange | outer_face_normal | phi_face | u_lagrange | phi_lagrange"];
         inVars -> computeUremapPBorn0;
         outVars [shape="record", label="dual_phi_flux | est_mixte | est_pure | u_lagrange | phi_lagrange"];
         computeUremapPBorn0 -> outVars;
       }

     }
   \enddot
   Cette méthode construit les variables et appelle RemapADIService::computeUremapPBorn0.
  */
  void computeUremapPBorn0(const Integer idir, const Integer nb_vars_to_project, const Integer nb_env)
  {
    RemapADIComputeUremapPBorn0Vars vars(m_face_normal
        , m_face_normal_velocity
        , m_face_length_lagrange
        , m_outer_face_normal
        , m_phi_face
        , m_dual_phi_flux
        , m_est_mixte
        , m_est_pure
        , m_u_lagrange
        , m_phi_lagrange);
    SCIHOOK_TRIGGER_REMAP_ADI_REMAPADI_COMPUTEUREMAPPBORN0_BEFORE
    this->computeUremapPBorn0(vars, idir, nb_vars_to_project, nb_env);
    SCIHOOK_TRIGGER_REMAP_ADI_REMAPADI_COMPUTEUREMAPPBORN0_AFTER
  }

  /*!
   \dot
     digraph computeDualUremapGraph
     {
       compound="true";
       edge [arrowsize="0.5", fontsize="8"];
       node [shape="box", fontname="Arial", fontsize="10"];
       {
         rank=same;
         computeDualUremap [style="rounded, filled", fillcolor="gray"];
         inVars [shape="record", label="dual_phi_flux | node_coord | dual_grad_phi | back_flux_contrib_env | front_flux_contrib_env | back_flux_mass | front_flux_mass | back_flux_mass_env | front_flux_mass_env | u_dual_lagrange | phi_dual_lagrange"];
         inVars -> computeDualUremap;
         outVars [shape="record", label="dual_grad_phi | back_flux_contrib_env | front_flux_contrib_env | back_flux_mass | front_flux_mass | back_flux_mass_env | front_flux_mass_env | u_dual_lagrange | phi_dual_lagrange"];
         computeDualUremap -> outVars;
       }

     }
   \enddot
   Cette méthode construit les variables et appelle RemapADIService::computeDualUremap.
  */
  void computeDualUremap(const Integer idir, const Integer nb_env)
  {
    RemapADIComputeDualUremapVars vars(m_dual_phi_flux
        , m_node_coord
        , m_dual_grad_phi
        , m_back_flux_contrib_env
        , m_front_flux_contrib_env
        , m_back_flux_mass
        , m_front_flux_mass
        , m_back_flux_mass_env
        , m_front_flux_mass_env
        , m_u_dual_lagrange
        , m_phi_dual_lagrange);
    SCIHOOK_TRIGGER_REMAP_ADI_REMAPADI_COMPUTEDUALUREMAP_BEFORE
    this->computeDualUremap(vars, idir, nb_env);
    SCIHOOK_TRIGGER_REMAP_ADI_REMAPADI_COMPUTEDUALUREMAP_AFTER
  }

  /*!
   Cette méthode construit les variables et appelle RemapADIService::computeRemapFlux.
  */
  Real computeRemapFlux(const Integer projectionOrder, const Integer projectionAvecPlateauPente, const Real face_normal_velocity, const Real3 face_normal, const Real face_length, const Real phi_face, const Real3 outer_face_normal, const Real3 exy, const Real deltat_n)
  {
    RemapADIComputeRemapFluxVars vars;
    SCIHOOK_TRIGGER_REMAP_ADI_REMAPADI_COMPUTEREMAPFLUX_BEFORE
    auto result = this->computeRemapFlux(vars, projectionOrder, projectionAvecPlateauPente, face_normal_velocity, face_normal, face_length, phi_face, outer_face_normal, exy, deltat_n);
    SCIHOOK_TRIGGER_REMAP_ADI_REMAPADI_COMPUTEREMAPFLUX_AFTER
    return result;
  }

  /*!
   \dot
     digraph appliRemapGraph
     {
       compound="true";
       edge [arrowsize="0.5", fontsize="8"];
       node [shape="box", fontname="Arial", fontsize="10"];
       {
         rank=same;
         appliRemap [style="rounded, filled", fillcolor="gray"];
         inVars [shape="record", label="sens_projection"];
         inVars -> appliRemap;
       }

       subgraph clusterCalledFuncs
       {
         center="true";
         color="navy";
         IRemap_synchronizeUremap [label="synchronizeUremap", color="navy", fontcolor="navy", style="rounded", URL="\ref Remap::IRemap::synchronizeUremap"];
         RemapADIServiceBase_synchronizeDualUremap [label="synchronizeDualUremap", color="navy", fontcolor="navy", style="rounded", URL="\ref RemapAdi::RemapADIServiceBase::synchronizeDualUremap"];
         RemapADIServiceBase_computeGradPhiFace [label="computeGradPhiFace", color="navy", fontcolor="navy", style="rounded", URL="\ref RemapAdi::RemapADIServiceBase::computeGradPhiFace"];
         RemapADIServiceBase_computeGradPhiCell [label="computeGradPhiCell", color="navy", fontcolor="navy", style="rounded", URL="\ref RemapAdi::RemapADIServiceBase::computeGradPhiCell"];
         RemapADIServiceBase_computeUpwindFaceQuantitiesForProjection [label="computeUpwindFaceQuantitiesForProjection", color="navy", fontcolor="navy", style="rounded", URL="\ref RemapAdi::RemapADIServiceBase::computeUpwindFaceQuantitiesForProjection"];
         RemapADIServiceBase_computeUremap [label="computeUremap", color="navy", fontcolor="navy", style="rounded", URL="\ref RemapAdi::RemapADIServiceBase::computeUremap"];
         RemapADIServiceBase_computeDualUremap [label="computeDualUremap", color="navy", fontcolor="navy", style="rounded", URL="\ref RemapAdi::RemapADIServiceBase::computeDualUremap"];
         IRemap_remapVariables [label="remapVariables", color="navy", fontcolor="navy", style="rounded", URL="\ref Remap::IRemap::remapVariables"];
       }
       appliRemap -> IRemap_remapVariables [lhead="clusterCalledFuncs", style="dashed", label=" call"];
     }
   \enddot
   Cette méthode construit les variables et appelle RemapADIService::appliRemap.
  */
  void appliRemap(const Integer dimension, const Integer withDualProjection, const Integer nb_vars_to_project, const Integer nb_env) override
  {
    RemapADIAppliRemapVars vars(m_sens_projection);
    SCIHOOK_TRIGGER_REMAP_ADI_REMAPADI_APPLIREMAP_BEFORE
    this->appliRemap(vars, dimension, withDualProjection, nb_vars_to_project, nb_env);
    SCIHOOK_TRIGGER_REMAP_ADI_REMAPADI_APPLIREMAP_AFTER
  }

  /*!
   \dot
     digraph resizeRemapVariablesGraph
     {
       compound="true";
       edge [arrowsize="0.5", fontsize="8"];
       node [shape="box", fontname="Arial", fontsize="10"];
       {
         rank=same;
         resizeRemapVariables [style="rounded, filled", fillcolor="gray"];
         outVars [shape="record", label="u_lagrange | u_dual_lagrange | phi_lagrange | phi_dual_lagrange | dual_grad_phi | grad_phi | phi_face | grad_phi_face | delta_phi_face_ar | delta_phi_face_av | dual_phi_flux | front_flux_mass_env | back_flux_mass_env | back_flux_contrib_env | front_flux_contrib_env"];
         resizeRemapVariables -> outVars;
       }

     }
   \enddot
   Cette méthode construit les variables et appelle RemapADIService::resizeRemapVariables.
  */
  void resizeRemapVariables(const Integer nb_vars_to_project, const Integer nb_env) override
  {
    RemapADIResizeRemapVariablesVars vars(m_u_lagrange
        , m_u_dual_lagrange
        , m_phi_lagrange
        , m_phi_dual_lagrange
        , m_dual_grad_phi
        , m_grad_phi
        , m_phi_face
        , m_grad_phi_face
        , m_delta_phi_face_ar
        , m_delta_phi_face_av
        , m_dual_phi_flux
        , m_front_flux_mass_env
        , m_back_flux_mass_env
        , m_back_flux_contrib_env
        , m_front_flux_contrib_env);
    SCIHOOK_TRIGGER_REMAP_ADI_REMAPADI_RESIZEREMAPVARIABLES_BEFORE
    this->resizeRemapVariables(vars, nb_vars_to_project, nb_env);
    SCIHOOK_TRIGGER_REMAP_ADI_REMAPADI_RESIZEREMAPVARIABLES_AFTER
  }

  /*!
   \dot
     digraph synchronizeUremapGraph
     {
       compound="true";
       edge [arrowsize="0.5", fontsize="8"];
       node [shape="box", fontname="Arial", fontsize="10"];
       {
         rank=same;
         synchronizeUremap [style="rounded, filled", fillcolor="gray"];
         outVars [shape="record", label="phi_lagrange | u_lagrange | dual_phi_flux | est_mixte | est_pure"];
         synchronizeUremap -> outVars;
       }

     }
   \enddot
   Cette méthode construit les variables et appelle RemapADIService::synchronizeUremap.
  */
  void synchronizeUremap() override
  {
    RemapADISynchronizeUremapVars vars(m_phi_lagrange
        , m_u_lagrange
        , m_dual_phi_flux
        , m_est_mixte
        , m_est_pure);
    SCIHOOK_TRIGGER_REMAP_ADI_REMAPADI_SYNCHRONIZEUREMAP_BEFORE
    this->synchronizeUremap(vars);
    SCIHOOK_TRIGGER_REMAP_ADI_REMAPADI_SYNCHRONIZEUREMAP_AFTER
  }

  /*!
   \dot
     digraph remapVariablesGraph
     {
       compound="true";
       edge [arrowsize="0.5", fontsize="8"];
       node [shape="box", fontname="Arial", fontsize="10"];
       {
         rank=same;
         remapVariables [style="rounded, filled", fillcolor="gray"];
         inVars [shape="record", label="euler_volume | u_lagrange | u_dual_lagrange | cell_volume | cell_status | est_mixte | cell_mass | fracvol | mass_fraction | pseudo_viscosity | density | internal_energy"];
         inVars -> remapVariables;
         outVars [shape="record", label="est_pure | velocity | node_mass | cell_volume | cell_status | est_mixte | cell_mass | fracvol | mass_fraction | pseudo_viscosity | density | internal_energy"];
         remapVariables -> outVars;
       }

     }
   \enddot
   Cette méthode construit les variables et appelle RemapADIService::remapVariables.
  */
  void remapVariables(const Integer dimension, const Integer withDualProjection, const Integer nb_vars_to_project, const Integer nb_env) override
  {
    RemapADIRemapVariablesVars vars(m_euler_volume
        , m_u_lagrange
        , m_u_dual_lagrange
        , m_est_pure
        , m_velocity
        , m_node_mass
        , m_cell_volume
        , m_cell_status
        , m_est_mixte
        , m_cell_mass
        , m_fracvol
        , m_mass_fraction
        , m_pseudo_viscosity
        , m_density
        , m_internal_energy);
    SCIHOOK_TRIGGER_REMAP_ADI_REMAPADI_REMAPVARIABLES_BEFORE
    this->remapVariables(vars, dimension, withDualProjection, nb_vars_to_project, nb_env);
    SCIHOOK_TRIGGER_REMAP_ADI_REMAPADI_REMAPVARIABLES_AFTER
  }


 public:  // ***** METHODES ABSTRAITES
  virtual void synchronizeDualUremap(RemapADISynchronizeDualUremapVars& vars) = 0;
  virtual void computeAndLimitGradPhi(RemapADIComputeAndLimitGradPhiVars& vars, const ::Types_mahyco::Limiteur projectionLimiterId, const Face frontFace, const Face backFace, const Cell cell, const Cell frontcell, const Cell backcell, const Integer nb_vars) = 0;
  virtual void computeDualGradPhi(RemapADIComputeDualGradPhiVars& vars, const Node inode, const Node frontfrontnode, const Node frontnode, const Node backnode, const Node backbacknode, const Integer idir) = 0;
  virtual void computeAndLimitGradPhiDual(RemapADIComputeAndLimitGradPhiDualVars& vars, const ::Types_mahyco::Limiteur projectionLimiterId, const Node inode, const Node frontnode, const Node backnode, const Real3 grad_front, const Real3 grad_back, const Real h0, const Real hplus, const Real hmoins) = 0;
  virtual Real fluxLimiter(RemapADIFluxLimiterVars& vars, const ::Types_mahyco::Limiteur projectionLimiterId, const Real r) = 0;
  virtual Real fluxLimiterG(RemapADIFluxLimiterGVars& vars, const ::Types_mahyco::Limiteur projectionLimiterId, const Real gradplus, const Real gradmoins, const Real y0, const Real yplus, const Real ymoins, const Real h0, const Real hplus, const Real hmoins) = 0;
  virtual void computeFluxPP(RemapADIComputeFluxPPVars& vars, const Cell cell, const Cell frontcell, const Cell backcell, const Real face_normal_velocity, const Real deltat_n, const Integer type, const Real flux_threshold, const Integer projectionPenteBorneDebarFix, const Real dual_normal_velocity, const Integer calcul_flux_dual, ::Arcane::RealArrayView* flux, ::Arcane::RealArrayView* flux_dual, const Integer nbmat, const Integer nb_vars) = 0;
  virtual Real computeY0(RemapADIComputeY0Vars& vars, const ::Types_mahyco::Limiteur projectionLimiterId, const Real y0, const Real yplus, const Real ymoins, const Real h0, const Real hplus, const Real hmoins, const Integer type) = 0;
  virtual Real computexgxd(RemapADIComputexgxdVars& vars, const Real y0, const Real yplus, const Real ymoins, const Real h0, const Real y0plus, const Real y0moins, const Integer type) = 0;
  virtual Real computeygyd(RemapADIComputeygydVars& vars, const Real y0, const Real yplus, const Real ymoins, const Real h0, const Real y0plus, const Real y0moins, const Real grady, const Integer type) = 0;
  virtual Real intY(RemapADIIntYVars& vars, const Real X, const Real x0, const Real y0, const Real x1, const Real y1) = 0;
  virtual void computeFluxPPPure(RemapADIComputeFluxPPPureVars& vars, const Cell cell, const Cell frontcell, const Cell backcell, const Real face_normal_velocity, const Real deltat_n, const Integer type, const Real flux_threshold, const Integer projectionPenteBorneDebarFix, const Real dual_normal_velocity, const Integer calcul_flux_dual, ::Arcane::RealArrayView* Flux, ::Arcane::RealArrayView* Flux_dual, const Integer nbmat, const Integer nb_vars) = 0;
  virtual void computeGradPhiFace(RemapADIComputeGradPhiFaceVars& vars, const Integer idir, const Integer nb_vars_to_project, const Integer nb_env) = 0;
  virtual void computeGradPhiCell(RemapADIComputeGradPhiCellVars& vars, const Integer idir, const Integer nb_vars_to_project, const Integer nb_env) = 0;
  virtual void computeUpwindFaceQuantitiesForProjection(RemapADIComputeUpwindFaceQuantitiesForProjectionVars& vars, const Integer idir, const Integer nb_vars_to_project, const Integer nb_env) = 0;
  virtual void computeUpwindFaceQuantitiesForProjectionPBorn0O2(RemapADIComputeUpwindFaceQuantitiesForProjectionPBorn0O2Vars& vars, const Integer idir, const Integer nb_vars_to_project) = 0;
  virtual void computeUremap(RemapADIComputeUremapVars& vars, const Integer idir, const Integer nb_vars_to_project, const Integer nb_env) = 0;
  virtual void computeUremapPBorn0(RemapADIComputeUremapPBorn0Vars& vars, const Integer idir, const Integer nb_vars_to_project, const Integer nb_env) = 0;
  virtual void computeDualUremap(RemapADIComputeDualUremapVars& vars, const Integer idir, const Integer nb_env) = 0;
  virtual Real computeRemapFlux(RemapADIComputeRemapFluxVars& vars, const Integer projectionOrder, const Integer projectionAvecPlateauPente, const Real face_normal_velocity, const Real3 face_normal, const Real face_length, const Real phi_face, const Real3 outer_face_normal, const Real3 exy, const Real deltat_n) = 0;
  virtual void appliRemap(RemapADIAppliRemapVars& vars, const Integer dimension, const Integer withDualProjection, const Integer nb_vars_to_project, const Integer nb_env) = 0;
  virtual void resizeRemapVariables(RemapADIResizeRemapVariablesVars& vars, const Integer nb_vars_to_project, const Integer nb_env) = 0;
  virtual void synchronizeUremap(RemapADISynchronizeUremapVars& vars) = 0;
  virtual void remapVariables(RemapADIRemapVariablesVars& vars, const Integer dimension, const Integer withDualProjection, const Integer nb_vars_to_project, const Integer nb_env) = 0;

 protected:  // ***** ATTRIBUTS
  IMeshMaterialMng* m_mesh_material_mng;
};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace RemapAdi

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // REMAP_ADI___REMAPADISERVICEBASE_H
