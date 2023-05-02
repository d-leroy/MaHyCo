#ifndef REMAP___REMAPADISERVICEBASE_H
#define REMAP___REMAPADISERVICEBASE_H

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
#include "remap/__RemapADIServiceVars.h"
#include "scihook/scihookdefs.h"
#include "remap/RemapADI_axl.h"
#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_DISABLED)
#include "remap/__RemapADIServiceContexts.h"
#endif

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

using namespace Arcane;
using namespace Arcane::Materials;
namespace Remap {

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
 #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_DISABLED)
 private:
  size_t SYNCHRONIZEDUALUREMAP_BEFORE;
  size_t SYNCHRONIZEDUALUREMAP_AFTER;
  size_t COMPUTEGRADPHIFACE_BEFORE;
  size_t COMPUTEGRADPHIFACE_AFTER;
  size_t COMPUTEGRADPHICELL_BEFORE;
  size_t COMPUTEGRADPHICELL_AFTER;
  size_t COMPUTEGRADPHICELL_PBORN0_LIMC_BEFORE;
  size_t COMPUTEGRADPHICELL_PBORN0_LIMC_AFTER;
  size_t COMPUTEDUALGRADPHI_LIMC_BEFORE;
  size_t COMPUTEDUALGRADPHI_LIMC_AFTER;
  size_t COMPUTEUPWINDFACEQUANTITIESFORPROJECTION_BEFORE;
  size_t COMPUTEUPWINDFACEQUANTITIESFORPROJECTION_AFTER;
  size_t COMPUTEUPWINDFACEQUANTITIESFORPROJECTION_PBORN0_O2_BEFORE;
  size_t COMPUTEUPWINDFACEQUANTITIESFORPROJECTION_PBORN0_O2_AFTER;
  size_t COMPUTEUREMAP_BEFORE;
  size_t COMPUTEUREMAP_AFTER;
  size_t COMPUTEUREMAP_PBORN0_BEFORE;
  size_t COMPUTEUREMAP_PBORN0_AFTER;
  size_t COMPUTEDUALUREMAP_BEFORE;
  size_t COMPUTEDUALUREMAP_AFTER;
  size_t APPLIREMAP_BEFORE;
  size_t APPLIREMAP_AFTER;
  size_t RESIZEREMAPVARIABLES_BEFORE;
  size_t RESIZEREMAPVARIABLES_AFTER;
  size_t SYNCHRONIZEUREMAP_BEFORE;
  size_t SYNCHRONIZEUREMAP_AFTER;
  size_t REMAPVARIABLES_BEFORE;
  size_t REMAPVARIABLES_AFTER;
 #endif
 public:  // ***** CONSTRUCTEUR & DESTRUCTEUR
  explicit RemapADIServiceBase(const ServiceBuildInfo& bi)
  : ArcaneRemapADIObject(bi)
  , m_mesh_material_mng(IMeshMaterialMng::getReference(bi.mesh()))
  {
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_DISABLED)
    SYNCHRONIZEDUALUREMAP_BEFORE = SciHook::register_base_event("RemapADIServiceBase.SynchronizeDualUremap.Before");
    SYNCHRONIZEDUALUREMAP_AFTER = SciHook::register_base_event("RemapADIServiceBase.SynchronizeDualUremap.After");
    COMPUTEGRADPHIFACE_BEFORE = SciHook::register_base_event("RemapADIServiceBase.ComputeGradPhiFace.Before");
    COMPUTEGRADPHIFACE_AFTER = SciHook::register_base_event("RemapADIServiceBase.ComputeGradPhiFace.After");
    COMPUTEGRADPHICELL_BEFORE = SciHook::register_base_event("RemapADIServiceBase.ComputeGradPhiCell.Before");
    COMPUTEGRADPHICELL_AFTER = SciHook::register_base_event("RemapADIServiceBase.ComputeGradPhiCell.After");
    COMPUTEGRADPHICELL_PBORN0_LIMC_BEFORE = SciHook::register_base_event("RemapADIServiceBase.ComputeGradPhiCell_PBorn0_LimC.Before");
    COMPUTEGRADPHICELL_PBORN0_LIMC_AFTER = SciHook::register_base_event("RemapADIServiceBase.ComputeGradPhiCell_PBorn0_LimC.After");
    COMPUTEDUALGRADPHI_LIMC_BEFORE = SciHook::register_base_event("RemapADIServiceBase.ComputeDualGradPhi_LimC.Before");
    COMPUTEDUALGRADPHI_LIMC_AFTER = SciHook::register_base_event("RemapADIServiceBase.ComputeDualGradPhi_LimC.After");
    COMPUTEUPWINDFACEQUANTITIESFORPROJECTION_BEFORE = SciHook::register_base_event("RemapADIServiceBase.ComputeUpwindFaceQuantitiesForProjection.Before");
    COMPUTEUPWINDFACEQUANTITIESFORPROJECTION_AFTER = SciHook::register_base_event("RemapADIServiceBase.ComputeUpwindFaceQuantitiesForProjection.After");
    COMPUTEUPWINDFACEQUANTITIESFORPROJECTION_PBORN0_O2_BEFORE = SciHook::register_base_event("RemapADIServiceBase.ComputeUpwindFaceQuantitiesForProjection_PBorn0_O2.Before");
    COMPUTEUPWINDFACEQUANTITIESFORPROJECTION_PBORN0_O2_AFTER = SciHook::register_base_event("RemapADIServiceBase.ComputeUpwindFaceQuantitiesForProjection_PBorn0_O2.After");
    COMPUTEUREMAP_BEFORE = SciHook::register_base_event("RemapADIServiceBase.ComputeUremap.Before");
    COMPUTEUREMAP_AFTER = SciHook::register_base_event("RemapADIServiceBase.ComputeUremap.After");
    COMPUTEUREMAP_PBORN0_BEFORE = SciHook::register_base_event("RemapADIServiceBase.ComputeUremap_PBorn0.Before");
    COMPUTEUREMAP_PBORN0_AFTER = SciHook::register_base_event("RemapADIServiceBase.ComputeUremap_PBorn0.After");
    COMPUTEDUALUREMAP_BEFORE = SciHook::register_base_event("RemapADIServiceBase.ComputeDualUremap.Before");
    COMPUTEDUALUREMAP_AFTER = SciHook::register_base_event("RemapADIServiceBase.ComputeDualUremap.After");
    APPLIREMAP_BEFORE = SciHook::register_base_event("RemapADIServiceBase.AppliRemap.Before");
    APPLIREMAP_AFTER = SciHook::register_base_event("RemapADIServiceBase.AppliRemap.After");
    RESIZEREMAPVARIABLES_BEFORE = SciHook::register_base_event("RemapADIServiceBase.ResizeRemapVariables.Before");
    RESIZEREMAPVARIABLES_AFTER = SciHook::register_base_event("RemapADIServiceBase.ResizeRemapVariables.After");
    SYNCHRONIZEUREMAP_BEFORE = SciHook::register_base_event("RemapADIServiceBase.SynchronizeUremap.Before");
    SYNCHRONIZEUREMAP_AFTER = SciHook::register_base_event("RemapADIServiceBase.SynchronizeUremap.After");
    REMAPVARIABLES_BEFORE = SciHook::register_base_event("RemapADIServiceBase.RemapVariables.Before");
    REMAPVARIABLES_AFTER = SciHook::register_base_event("RemapADIServiceBase.RemapVariables.After");
    #endif
  }

  virtual ~RemapADIServiceBase()
  {
  }

 public:  // ***** ACCESSEURS
  Real getThreshold() { return options()->getThreshold(); }
  bool getIsEulerScheme() { return options()->getIsEulerScheme(); }
  Integer getOrdreProjection() { return options()->getOrdreProjection(); }
  bool getConservationEnergieTotale() { return options()->getConservationEnergieTotale(); }
  bool getProjectionPenteBorneMixte() { return options()->getProjectionPenteBorneMixte(); }
  Integer getProjectionLimiteurId() { return options()->getProjectionLimiteurId(); }
  Integer getProjectionLimiteurPureId() { return options()->getProjectionLimiteurPureId(); }
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
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_DISABLED) && not defined(SCIHOOK_REMAP_SYNCHRONIZEDUALUREMAP_DISABLED)
    std::shared_ptr<RemapADISynchronizeDualUremapExecutionContext> ctx(
        new RemapADISynchronizeDualUremapExecutionContext("SynchronizeDualUremapExecutionContext"
            , &vars));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_DISABLED) && not defined(SCIHOOK_REMAP_SYNCHRONIZEDUALUREMAP_DISABLED)
    SciHook::trigger(SYNCHRONIZEDUALUREMAP_BEFORE, ctx);
    this->synchronizeDualUremap(vars);
    SciHook::trigger(SYNCHRONIZEDUALUREMAP_AFTER, ctx);
    #else
    this->synchronizeDualUremap(vars);
    #endif
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
         inVars [shape="record", label="face_normal | cell_coord | phi_lagrange | face_coord | cell_coord | deltax_lagrange | h_cell_lagrange"];
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
        , m_cell_coord
        , m_is_dir_face
        , m_grad_phi_face
        , m_deltax_lagrange
        , m_h_cell_lagrange);
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_DISABLED) && not defined(SCIHOOK_REMAP_COMPUTEGRADPHIFACE_DISABLED)
    std::shared_ptr<RemapADIComputeGradPhiFaceExecutionContext> ctx(
        new RemapADIComputeGradPhiFaceExecutionContext("ComputeGradPhiFaceExecutionContext"
            , &vars
            , idir
            , nb_vars_to_project
            , nb_env));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_DISABLED) && not defined(SCIHOOK_REMAP_COMPUTEGRADPHIFACE_DISABLED)
    SciHook::trigger(COMPUTEGRADPHIFACE_BEFORE, ctx);
    this->computeGradPhiFace(vars, idir, nb_vars_to_project, nb_env);
    SciHook::trigger(COMPUTEGRADPHIFACE_AFTER, ctx);
    #else
    this->computeGradPhiFace(vars, idir, nb_vars_to_project, nb_env);
    #endif
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
   
       subgraph clusterCalledFuncs
       {
         center="true";
         color="navy";
         RemapADIServiceBase_computeGradPhiCell_PBorn0_LimC [label="computeGradPhiCell_PBorn0_LimC", color="navy", fontcolor="navy", style="rounded", URL="\ref Remap::RemapADIServiceBase::computeGradPhiCell_PBorn0_LimC"];
       }
       computeGradPhiCell -> RemapADIServiceBase_computeGradPhiCell_PBorn0_LimC [lhead="clusterCalledFuncs", style="dashed", label=" call"];
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
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_DISABLED) && not defined(SCIHOOK_REMAP_COMPUTEGRADPHICELL_DISABLED)
    std::shared_ptr<RemapADIComputeGradPhiCellExecutionContext> ctx(
        new RemapADIComputeGradPhiCellExecutionContext("ComputeGradPhiCellExecutionContext"
            , &vars
            , idir
            , nb_vars_to_project
            , nb_env));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_DISABLED) && not defined(SCIHOOK_REMAP_COMPUTEGRADPHICELL_DISABLED)
    SciHook::trigger(COMPUTEGRADPHICELL_BEFORE, ctx);
    this->computeGradPhiCell(vars, idir, nb_vars_to_project, nb_env);
    SciHook::trigger(COMPUTEGRADPHICELL_AFTER, ctx);
    #else
    this->computeGradPhiCell(vars, idir, nb_vars_to_project, nb_env);
    #endif
  }

  /*!
   \dot
     digraph computeGradPhiCell_PBorn0_LimCGraph
     {
       compound="true";
       edge [arrowsize="0.5", fontsize="8"];
       node [shape="box", fontname="Arial", fontsize="10"];
       {
         rank=same;
         computeGradPhiCell_PBorn0_LimC [style="rounded, filled", fillcolor="gray"];
         inVars [shape="record", label="grad_phi_face"];
         inVars -> computeGradPhiCell_PBorn0_LimC;
         outVars [shape="record", label="grad_phi | delta_phi_face_ar | delta_phi_face_av"];
         computeGradPhiCell_PBorn0_LimC -> outVars;
       }
   
     }
   \enddot
   Cette méthode construit les variables et appelle RemapADIService::computeGradPhiCell_PBorn0_LimC.
  */
  void computeGradPhiCell_PBorn0_LimC(const Integer idir, const Integer nb_vars_to_project)
  {
    RemapADIComputeGradPhiCell_PBorn0_LimCVars vars(m_grad_phi_face
        , m_grad_phi
        , m_delta_phi_face_ar
        , m_delta_phi_face_av);
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_DISABLED) && not defined(SCIHOOK_REMAP_COMPUTEGRADPHICELL_PBORN0_LIMC_DISABLED)
    std::shared_ptr<RemapADIComputeGradPhiCell_PBorn0_LimCExecutionContext> ctx(
        new RemapADIComputeGradPhiCell_PBorn0_LimCExecutionContext("ComputeGradPhiCell_PBorn0_LimCExecutionContext"
            , &vars
            , idir
            , nb_vars_to_project));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_DISABLED) && not defined(SCIHOOK_REMAP_COMPUTEGRADPHICELL_PBORN0_LIMC_DISABLED)
    SciHook::trigger(COMPUTEGRADPHICELL_PBORN0_LIMC_BEFORE, ctx);
    this->computeGradPhiCell_PBorn0_LimC(vars, idir, nb_vars_to_project);
    SciHook::trigger(COMPUTEGRADPHICELL_PBORN0_LIMC_AFTER, ctx);
    #else
    this->computeGradPhiCell_PBorn0_LimC(vars, idir, nb_vars_to_project);
    #endif
  }

  /*!
   \dot
     digraph computeDualGradPhi_LimCGraph
     {
       compound="true";
       edge [arrowsize="0.5", fontsize="8"];
       node [shape="box", fontname="Arial", fontsize="10"];
       {
         rank=same;
         computeDualGradPhi_LimC [style="rounded, filled", fillcolor="gray"];
         inVars [shape="record", label="phi_dual_lagrange | node_coord"];
         inVars -> computeDualGradPhi_LimC;
         outVars [shape="record", label="dual_grad_phi"];
         computeDualGradPhi_LimC -> outVars;
       }
   
     }
   \enddot
   Cette méthode construit les variables et appelle RemapADIService::computeDualGradPhi_LimC.
  */
  void computeDualGradPhi_LimC(const Integer idir)
  {
    RemapADIComputeDualGradPhi_LimCVars vars(m_phi_dual_lagrange
        , m_node_coord
        , m_dual_grad_phi);
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_DISABLED) && not defined(SCIHOOK_REMAP_COMPUTEDUALGRADPHI_LIMC_DISABLED)
    std::shared_ptr<RemapADIComputeDualGradPhi_LimCExecutionContext> ctx(
        new RemapADIComputeDualGradPhi_LimCExecutionContext("ComputeDualGradPhi_LimCExecutionContext"
            , &vars
            , idir));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_DISABLED) && not defined(SCIHOOK_REMAP_COMPUTEDUALGRADPHI_LIMC_DISABLED)
    SciHook::trigger(COMPUTEDUALGRADPHI_LIMC_BEFORE, ctx);
    this->computeDualGradPhi_LimC(vars, idir);
    SciHook::trigger(COMPUTEDUALGRADPHI_LIMC_AFTER, ctx);
    #else
    this->computeDualGradPhi_LimC(vars, idir);
    #endif
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
         RemapADIServiceBase_computeUpwindFaceQuantitiesForProjection_PBorn0_O2 [label="computeUpwindFaceQuantitiesForProjection_PBorn0_O2", color="navy", fontcolor="navy", style="rounded", URL="\ref Remap::RemapADIServiceBase::computeUpwindFaceQuantitiesForProjection_PBorn0_O2"];
       }
       computeUpwindFaceQuantitiesForProjection -> RemapADIServiceBase_computeUpwindFaceQuantitiesForProjection_PBorn0_O2 [lhead="clusterCalledFuncs", style="dashed", label=" call"];
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
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_DISABLED) && not defined(SCIHOOK_REMAP_COMPUTEUPWINDFACEQUANTITIESFORPROJECTION_DISABLED)
    std::shared_ptr<RemapADIComputeUpwindFaceQuantitiesForProjectionExecutionContext> ctx(
        new RemapADIComputeUpwindFaceQuantitiesForProjectionExecutionContext("ComputeUpwindFaceQuantitiesForProjectionExecutionContext"
            , &vars
            , idir
            , nb_vars_to_project
            , nb_env));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_DISABLED) && not defined(SCIHOOK_REMAP_COMPUTEUPWINDFACEQUANTITIESFORPROJECTION_DISABLED)
    SciHook::trigger(COMPUTEUPWINDFACEQUANTITIESFORPROJECTION_BEFORE, ctx);
    this->computeUpwindFaceQuantitiesForProjection(vars, idir, nb_vars_to_project, nb_env);
    SciHook::trigger(COMPUTEUPWINDFACEQUANTITIESFORPROJECTION_AFTER, ctx);
    #else
    this->computeUpwindFaceQuantitiesForProjection(vars, idir, nb_vars_to_project, nb_env);
    #endif
  }

  /*!
   \dot
     digraph computeUpwindFaceQuantitiesForProjection_PBorn0_O2Graph
     {
       compound="true";
       edge [arrowsize="0.5", fontsize="8"];
       node [shape="box", fontname="Arial", fontsize="10"];
       {
         rank=same;
         computeUpwindFaceQuantitiesForProjection_PBorn0_O2 [style="rounded, filled", fillcolor="gray"];
         inVars [shape="record", label="deltax_lagrange | face_normal_velocity | phi_lagrange | face_coord | face_normal | cell_coord | grad_phi"];
         inVars -> computeUpwindFaceQuantitiesForProjection_PBorn0_O2;
         outVars [shape="record", label="phi_face"];
         computeUpwindFaceQuantitiesForProjection_PBorn0_O2 -> outVars;
       }
   
     }
   \enddot
   Cette méthode construit les variables et appelle RemapADIService::computeUpwindFaceQuantitiesForProjection_PBorn0_O2.
  */
  void computeUpwindFaceQuantitiesForProjection_PBorn0_O2(const Integer idir, const Integer nb_vars_to_project)
  {
    RemapADIComputeUpwindFaceQuantitiesForProjection_PBorn0_O2Vars vars(m_deltax_lagrange
        , m_face_normal_velocity
        , m_phi_lagrange
        , m_face_coord
        , m_face_normal
        , m_cell_coord
        , m_grad_phi
        , m_phi_face);
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_DISABLED) && not defined(SCIHOOK_REMAP_COMPUTEUPWINDFACEQUANTITIESFORPROJECTION_PBORN0_O2_DISABLED)
    std::shared_ptr<RemapADIComputeUpwindFaceQuantitiesForProjection_PBorn0_O2ExecutionContext> ctx(
        new RemapADIComputeUpwindFaceQuantitiesForProjection_PBorn0_O2ExecutionContext("ComputeUpwindFaceQuantitiesForProjection_PBorn0_O2ExecutionContext"
            , &vars
            , idir
            , nb_vars_to_project));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_DISABLED) && not defined(SCIHOOK_REMAP_COMPUTEUPWINDFACEQUANTITIESFORPROJECTION_PBORN0_O2_DISABLED)
    SciHook::trigger(COMPUTEUPWINDFACEQUANTITIESFORPROJECTION_PBORN0_O2_BEFORE, ctx);
    this->computeUpwindFaceQuantitiesForProjection_PBorn0_O2(vars, idir, nb_vars_to_project);
    SciHook::trigger(COMPUTEUPWINDFACEQUANTITIESFORPROJECTION_PBORN0_O2_AFTER, ctx);
    #else
    this->computeUpwindFaceQuantitiesForProjection_PBorn0_O2(vars, idir, nb_vars_to_project);
    #endif
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
         inVars [shape="record", label="face_normal | face_length_lagrange | outer_face_normal | phi_face | u_lagrange | phi_lagrange"];
         inVars -> computeUremap;
         outVars [shape="record", label="dual_phi_flux | est_mixte | est_pure | u_lagrange | phi_lagrange"];
         computeUremap -> outVars;
       }
   
       subgraph clusterCalledFuncs
       {
         center="true";
         color="navy";
         RemapADIServiceBase_computeUremap_PBorn0 [label="computeUremap_PBorn0", color="navy", fontcolor="navy", style="rounded", URL="\ref Remap::RemapADIServiceBase::computeUremap_PBorn0"];
       }
       computeUremap -> RemapADIServiceBase_computeUremap_PBorn0 [lhead="clusterCalledFuncs", style="dashed", label=" call"];
     }
   \enddot
   Cette méthode construit les variables et appelle RemapADIService::computeUremap.
  */
  void computeUremap(const Integer idir, const Integer nb_vars_to_project, const Integer nb_env)
  {
    RemapADIComputeUremapVars vars(m_face_normal
        , m_face_length_lagrange
        , m_outer_face_normal
        , m_phi_face
        , m_dual_phi_flux
        , m_est_mixte
        , m_est_pure
        , m_u_lagrange
        , m_phi_lagrange);
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_DISABLED) && not defined(SCIHOOK_REMAP_COMPUTEUREMAP_DISABLED)
    std::shared_ptr<RemapADIComputeUremapExecutionContext> ctx(
        new RemapADIComputeUremapExecutionContext("ComputeUremapExecutionContext"
            , &vars
            , idir
            , nb_vars_to_project
            , nb_env));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_DISABLED) && not defined(SCIHOOK_REMAP_COMPUTEUREMAP_DISABLED)
    SciHook::trigger(COMPUTEUREMAP_BEFORE, ctx);
    this->computeUremap(vars, idir, nb_vars_to_project, nb_env);
    SciHook::trigger(COMPUTEUREMAP_AFTER, ctx);
    #else
    this->computeUremap(vars, idir, nb_vars_to_project, nb_env);
    #endif
  }

  /*!
   \dot
     digraph computeUremap_PBorn0Graph
     {
       compound="true";
       edge [arrowsize="0.5", fontsize="8"];
       node [shape="box", fontname="Arial", fontsize="10"];
       {
         rank=same;
         computeUremap_PBorn0 [style="rounded, filled", fillcolor="gray"];
         inVars [shape="record", label="face_normal | face_normal_velocity | face_length_lagrange | outer_face_normal | phi_face | u_lagrange | phi_lagrange"];
         inVars -> computeUremap_PBorn0;
         outVars [shape="record", label="dual_phi_flux | est_mixte | est_pure | u_lagrange | phi_lagrange"];
         computeUremap_PBorn0 -> outVars;
       }
   
     }
   \enddot
   Cette méthode construit les variables et appelle RemapADIService::computeUremap_PBorn0.
  */
  void computeUremap_PBorn0(const Integer idir, const Integer nb_vars_to_project, const Integer nb_env)
  {
    RemapADIComputeUremap_PBorn0Vars vars(m_face_normal
        , m_face_normal_velocity
        , m_face_length_lagrange
        , m_outer_face_normal
        , m_phi_face
        , m_dual_phi_flux
        , m_est_mixte
        , m_est_pure
        , m_u_lagrange
        , m_phi_lagrange);
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_DISABLED) && not defined(SCIHOOK_REMAP_COMPUTEUREMAP_PBORN0_DISABLED)
    std::shared_ptr<RemapADIComputeUremap_PBorn0ExecutionContext> ctx(
        new RemapADIComputeUremap_PBorn0ExecutionContext("ComputeUremap_PBorn0ExecutionContext"
            , &vars
            , idir
            , nb_vars_to_project
            , nb_env));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_DISABLED) && not defined(SCIHOOK_REMAP_COMPUTEUREMAP_PBORN0_DISABLED)
    SciHook::trigger(COMPUTEUREMAP_PBORN0_BEFORE, ctx);
    this->computeUremap_PBorn0(vars, idir, nb_vars_to_project, nb_env);
    SciHook::trigger(COMPUTEUREMAP_PBORN0_AFTER, ctx);
    #else
    this->computeUremap_PBorn0(vars, idir, nb_vars_to_project, nb_env);
    #endif
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
   
       subgraph clusterCalledFuncs
       {
         center="true";
         color="navy";
         RemapADIServiceBase_computeDualGradPhi_LimC [label="computeDualGradPhi_LimC", color="navy", fontcolor="navy", style="rounded", URL="\ref Remap::RemapADIServiceBase::computeDualGradPhi_LimC"];
       }
       computeDualUremap -> RemapADIServiceBase_computeDualGradPhi_LimC [lhead="clusterCalledFuncs", style="dashed", label=" call"];
     }
   \enddot
   Cette méthode construit les variables et appelle RemapADIService::computeDualUremap.
  */
  void computeDualUremap()
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
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_DISABLED) && not defined(SCIHOOK_REMAP_COMPUTEDUALUREMAP_DISABLED)
    std::shared_ptr<RemapADIComputeDualUremapExecutionContext> ctx(
        new RemapADIComputeDualUremapExecutionContext("ComputeDualUremapExecutionContext"
            , &vars));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_DISABLED) && not defined(SCIHOOK_REMAP_COMPUTEDUALUREMAP_DISABLED)
    SciHook::trigger(COMPUTEDUALUREMAP_BEFORE, ctx);
    this->computeDualUremap(vars);
    SciHook::trigger(COMPUTEDUALUREMAP_AFTER, ctx);
    #else
    this->computeDualUremap(vars);
    #endif
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
         RemapADIServiceBase_synchronizeDualUremap [label="synchronizeDualUremap", color="navy", fontcolor="navy", style="rounded", URL="\ref Remap::RemapADIServiceBase::synchronizeDualUremap"];
         RemapADIServiceBase_computeGradPhiFace [label="computeGradPhiFace", color="navy", fontcolor="navy", style="rounded", URL="\ref Remap::RemapADIServiceBase::computeGradPhiFace"];
         RemapADIServiceBase_computeGradPhiCell [label="computeGradPhiCell", color="navy", fontcolor="navy", style="rounded", URL="\ref Remap::RemapADIServiceBase::computeGradPhiCell"];
         RemapADIServiceBase_computeUpwindFaceQuantitiesForProjection [label="computeUpwindFaceQuantitiesForProjection", color="navy", fontcolor="navy", style="rounded", URL="\ref Remap::RemapADIServiceBase::computeUpwindFaceQuantitiesForProjection"];
         RemapADIServiceBase_computeUremap [label="computeUremap", color="navy", fontcolor="navy", style="rounded", URL="\ref Remap::RemapADIServiceBase::computeUremap"];
         RemapADIServiceBase_computeDualUremap [label="computeDualUremap", color="navy", fontcolor="navy", style="rounded", URL="\ref Remap::RemapADIServiceBase::computeDualUremap"];
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
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_DISABLED) && not defined(SCIHOOK_REMAP_APPLIREMAP_DISABLED)
    std::shared_ptr<RemapADIAppliRemapExecutionContext> ctx(
        new RemapADIAppliRemapExecutionContext("AppliRemapExecutionContext"
            , &vars
            , dimension
            , withDualProjection
            , nb_vars_to_project
            , nb_env));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_DISABLED) && not defined(SCIHOOK_REMAP_APPLIREMAP_DISABLED)
    SciHook::trigger(APPLIREMAP_BEFORE, ctx);
    this->appliRemap(vars, dimension, withDualProjection, nb_vars_to_project, nb_env);
    SciHook::trigger(APPLIREMAP_AFTER, ctx);
    #else
    this->appliRemap(vars, dimension, withDualProjection, nb_vars_to_project, nb_env);
    #endif
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
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_DISABLED) && not defined(SCIHOOK_REMAP_RESIZEREMAPVARIABLES_DISABLED)
    std::shared_ptr<RemapADIResizeRemapVariablesExecutionContext> ctx(
        new RemapADIResizeRemapVariablesExecutionContext("ResizeRemapVariablesExecutionContext"
            , &vars
            , nb_vars_to_project
            , nb_env));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_DISABLED) && not defined(SCIHOOK_REMAP_RESIZEREMAPVARIABLES_DISABLED)
    SciHook::trigger(RESIZEREMAPVARIABLES_BEFORE, ctx);
    this->resizeRemapVariables(vars, nb_vars_to_project, nb_env);
    SciHook::trigger(RESIZEREMAPVARIABLES_AFTER, ctx);
    #else
    this->resizeRemapVariables(vars, nb_vars_to_project, nb_env);
    #endif
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
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_DISABLED) && not defined(SCIHOOK_REMAP_SYNCHRONIZEUREMAP_DISABLED)
    std::shared_ptr<RemapADISynchronizeUremapExecutionContext> ctx(
        new RemapADISynchronizeUremapExecutionContext("SynchronizeUremapExecutionContext"
            , &vars));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_DISABLED) && not defined(SCIHOOK_REMAP_SYNCHRONIZEUREMAP_DISABLED)
    SciHook::trigger(SYNCHRONIZEUREMAP_BEFORE, ctx);
    this->synchronizeUremap(vars);
    SciHook::trigger(SYNCHRONIZEUREMAP_AFTER, ctx);
    #else
    this->synchronizeUremap(vars);
    #endif
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
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_DISABLED) && not defined(SCIHOOK_REMAP_REMAPVARIABLES_DISABLED)
    std::shared_ptr<RemapADIRemapVariablesExecutionContext> ctx(
        new RemapADIRemapVariablesExecutionContext("RemapVariablesExecutionContext"
            , &vars
            , dimension
            , withDualProjection
            , nb_vars_to_project
            , nb_env));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_DISABLED) && not defined(SCIHOOK_REMAP_REMAPVARIABLES_DISABLED)
    SciHook::trigger(REMAPVARIABLES_BEFORE, ctx);
    this->remapVariables(vars, dimension, withDualProjection, nb_vars_to_project, nb_env);
    SciHook::trigger(REMAPVARIABLES_AFTER, ctx);
    #else
    this->remapVariables(vars, dimension, withDualProjection, nb_vars_to_project, nb_env);
    #endif
  }


 public:  // ***** METHODES ABSTRAITES
  virtual void synchronizeDualUremap(RemapADISynchronizeDualUremapVars& vars) = 0;
  virtual void computeGradPhiFace(RemapADIComputeGradPhiFaceVars& vars, const Integer idir, const Integer nb_vars_to_project, const Integer nb_env) = 0;
  virtual void computeGradPhiCell(RemapADIComputeGradPhiCellVars& vars, const Integer idir, const Integer nb_vars_to_project, const Integer nb_env) = 0;
  virtual void computeGradPhiCell_PBorn0_LimC(RemapADIComputeGradPhiCell_PBorn0_LimCVars& vars, const Integer idir, const Integer nb_vars_to_project) = 0;
  virtual void computeDualGradPhi_LimC(RemapADIComputeDualGradPhi_LimCVars& vars, const Integer idir) = 0;
  virtual void computeUpwindFaceQuantitiesForProjection(RemapADIComputeUpwindFaceQuantitiesForProjectionVars& vars, const Integer idir, const Integer nb_vars_to_project, const Integer nb_env) = 0;
  virtual void computeUpwindFaceQuantitiesForProjection_PBorn0_O2(RemapADIComputeUpwindFaceQuantitiesForProjection_PBorn0_O2Vars& vars, const Integer idir, const Integer nb_vars_to_project) = 0;
  virtual void computeUremap(RemapADIComputeUremapVars& vars, const Integer idir, const Integer nb_vars_to_project, const Integer nb_env) = 0;
  virtual void computeUremap_PBorn0(RemapADIComputeUremap_PBorn0Vars& vars, const Integer idir, const Integer nb_vars_to_project, const Integer nb_env) = 0;
  virtual void computeDualUremap(RemapADIComputeDualUremapVars& vars) = 0;
  virtual void appliRemap(RemapADIAppliRemapVars& vars, const Integer dimension, const Integer withDualProjection, const Integer nb_vars_to_project, const Integer nb_env) = 0;
  virtual void resizeRemapVariables(RemapADIResizeRemapVariablesVars& vars, const Integer nb_vars_to_project, const Integer nb_env) = 0;
  virtual void synchronizeUremap(RemapADISynchronizeUremapVars& vars) = 0;
  virtual void remapVariables(RemapADIRemapVariablesVars& vars, const Integer dimension, const Integer withDualProjection, const Integer nb_vars_to_project, const Integer nb_env) = 0;

 protected:  // ***** ATTRIBUTS
  IMeshMaterialMng* m_mesh_material_mng;
};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace Remap

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // REMAP___REMAPADISERVICEBASE_H
