#ifndef REMAP___REMAPADISERVICECONTEXTS_H
#define REMAP___REMAPADISERVICECONTEXTS_H

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
#include "scihook/SciHook.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

using namespace Arcane;
using namespace Arcane::Materials;
namespace Remap {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

//! Classe de contexte d'exécution pour synchronizeDualUremap
struct RemapADISynchronizeDualUremapExecutionContext final : SciHook::SciHookExecutionContext
{
  RemapADISynchronizeDualUremapExecutionContext(std::string execution_context_name,
      RemapADISynchronizeDualUremapVars *vars)
  : SciHookExecutionContext(execution_context_name)
  , vars(vars)
  {}
  
  const RemapADISynchronizeDualUremapVars *vars;

  const pybind11::object get_m_phi_dual_lagrange() const {
    return pybind11::cast(vars->m_phi_dual_lagrange);
  }

  const pybind11::object get_m_u_dual_lagrange() const {
    return pybind11::cast(vars->m_u_dual_lagrange);
  }
};

//! Classe de contexte d'exécution pour computeGradPhiFace
struct RemapADIComputeGradPhiFaceExecutionContext final : SciHook::SciHookExecutionContext
{
  RemapADIComputeGradPhiFaceExecutionContext(std::string execution_context_name,
      RemapADIComputeGradPhiFaceVars *vars,
      const Integer idir,
      const Integer nb_vars_to_project,
      const Integer nb_env)
  : SciHookExecutionContext(execution_context_name)
  , idir(idir)
  , nb_vars_to_project(nb_vars_to_project)
  , nb_env(nb_env)
  , vars(vars)
  {}
  
  const Integer idir;
  const Integer nb_vars_to_project;
  const Integer nb_env;
  const RemapADIComputeGradPhiFaceVars *vars;

  const pybind11::object get_idir() const {
    return pybind11::cast(idir);
  }

  const pybind11::object get_nb_vars_to_project() const {
    return pybind11::cast(nb_vars_to_project);
  }

  const pybind11::object get_nb_env() const {
    return pybind11::cast(nb_env);
  }

  const pybind11::object get_m_face_normal() const {
    return pybind11::cast(vars->m_face_normal);
  }

  const pybind11::object get_m_cell_coord() const {
    return pybind11::cast(vars->m_cell_coord);
  }

  const pybind11::object get_m_phi_lagrange() const {
    return pybind11::cast(vars->m_phi_lagrange);
  }

  const pybind11::object get_m_face_coord() const {
    return pybind11::cast(vars->m_face_coord);
  }

  const pybind11::object get_m_cell_coord() const {
    return pybind11::cast(vars->m_cell_coord);
  }

  const pybind11::object get_m_is_dir_face() const {
    return pybind11::cast(vars->m_is_dir_face);
  }

  const pybind11::object get_m_grad_phi_face() const {
    return pybind11::cast(vars->m_grad_phi_face);
  }

  const pybind11::object get_m_deltax_lagrange() const {
    return pybind11::cast(vars->m_deltax_lagrange);
  }

  const pybind11::object get_m_h_cell_lagrange() const {
    return pybind11::cast(vars->m_h_cell_lagrange);
  }
};

//! Classe de contexte d'exécution pour computeGradPhiCell
struct RemapADIComputeGradPhiCellExecutionContext final : SciHook::SciHookExecutionContext
{
  RemapADIComputeGradPhiCellExecutionContext(std::string execution_context_name,
      RemapADIComputeGradPhiCellVars *vars,
      const Integer idir,
      const Integer nb_vars_to_project,
      const Integer nb_env)
  : SciHookExecutionContext(execution_context_name)
  , idir(idir)
  , nb_vars_to_project(nb_vars_to_project)
  , nb_env(nb_env)
  , vars(vars)
  {}
  
  const Integer idir;
  const Integer nb_vars_to_project;
  const Integer nb_env;
  const RemapADIComputeGradPhiCellVars *vars;

  const pybind11::object get_idir() const {
    return pybind11::cast(idir);
  }

  const pybind11::object get_nb_vars_to_project() const {
    return pybind11::cast(nb_vars_to_project);
  }

  const pybind11::object get_nb_env() const {
    return pybind11::cast(nb_env);
  }

  const pybind11::object get_m_outer_face_normal() const {
    return pybind11::cast(vars->m_outer_face_normal);
  }

  const pybind11::object get_m_face_normal_velocity() const {
    return pybind11::cast(vars->m_face_normal_velocity);
  }

  const pybind11::object get_m_face_length_lagrange() const {
    return pybind11::cast(vars->m_face_length_lagrange);
  }

  const pybind11::object get_m_is_dir_face() const {
    return pybind11::cast(vars->m_is_dir_face);
  }

  const pybind11::object get_m_grad_phi() const {
    return pybind11::cast(vars->m_grad_phi);
  }

  const pybind11::object get_m_dual_phi_flux() const {
    return pybind11::cast(vars->m_dual_phi_flux);
  }

  const pybind11::object get_m_delta_phi_face_av() const {
    return pybind11::cast(vars->m_delta_phi_face_av);
  }

  const pybind11::object get_m_delta_phi_face_ar() const {
    return pybind11::cast(vars->m_delta_phi_face_ar);
  }

  const pybind11::object get_m_est_mixte() const {
    return pybind11::cast(vars->m_est_mixte);
  }

  const pybind11::object get_m_est_pure() const {
    return pybind11::cast(vars->m_est_pure);
  }
};

//! Classe de contexte d'exécution pour computeGradPhiCell_PBorn0_LimC
struct RemapADIComputeGradPhiCell_PBorn0_LimCExecutionContext final : SciHook::SciHookExecutionContext
{
  RemapADIComputeGradPhiCell_PBorn0_LimCExecutionContext(std::string execution_context_name,
      RemapADIComputeGradPhiCell_PBorn0_LimCVars *vars,
      const Integer idir,
      const Integer nb_vars_to_project)
  : SciHookExecutionContext(execution_context_name)
  , idir(idir)
  , nb_vars_to_project(nb_vars_to_project)
  , vars(vars)
  {}
  
  const Integer idir;
  const Integer nb_vars_to_project;
  const RemapADIComputeGradPhiCell_PBorn0_LimCVars *vars;

  const pybind11::object get_idir() const {
    return pybind11::cast(idir);
  }

  const pybind11::object get_nb_vars_to_project() const {
    return pybind11::cast(nb_vars_to_project);
  }

  const pybind11::object get_m_grad_phi_face() const {
    return pybind11::cast(vars->m_grad_phi_face);
  }

  const pybind11::object get_m_grad_phi() const {
    return pybind11::cast(vars->m_grad_phi);
  }

  const pybind11::object get_m_delta_phi_face_ar() const {
    return pybind11::cast(vars->m_delta_phi_face_ar);
  }

  const pybind11::object get_m_delta_phi_face_av() const {
    return pybind11::cast(vars->m_delta_phi_face_av);
  }
};

//! Classe de contexte d'exécution pour computeDualGradPhi_LimC
struct RemapADIComputeDualGradPhi_LimCExecutionContext final : SciHook::SciHookExecutionContext
{
  RemapADIComputeDualGradPhi_LimCExecutionContext(std::string execution_context_name,
      RemapADIComputeDualGradPhi_LimCVars *vars,
      const Integer idir)
  : SciHookExecutionContext(execution_context_name)
  , idir(idir)
  , vars(vars)
  {}
  
  const Integer idir;
  const RemapADIComputeDualGradPhi_LimCVars *vars;

  const pybind11::object get_idir() const {
    return pybind11::cast(idir);
  }

  const pybind11::object get_m_phi_dual_lagrange() const {
    return pybind11::cast(vars->m_phi_dual_lagrange);
  }

  const pybind11::object get_m_node_coord() const {
    return pybind11::cast(vars->m_node_coord);
  }

  const pybind11::object get_m_dual_grad_phi() const {
    return pybind11::cast(vars->m_dual_grad_phi);
  }
};

//! Classe de contexte d'exécution pour computeUpwindFaceQuantitiesForProjection
struct RemapADIComputeUpwindFaceQuantitiesForProjectionExecutionContext final : SciHook::SciHookExecutionContext
{
  RemapADIComputeUpwindFaceQuantitiesForProjectionExecutionContext(std::string execution_context_name,
      RemapADIComputeUpwindFaceQuantitiesForProjectionVars *vars,
      const Integer idir,
      const Integer nb_vars_to_project,
      const Integer nb_env)
  : SciHookExecutionContext(execution_context_name)
  , idir(idir)
  , nb_vars_to_project(nb_vars_to_project)
  , nb_env(nb_env)
  , vars(vars)
  {}
  
  const Integer idir;
  const Integer nb_vars_to_project;
  const Integer nb_env;
  const RemapADIComputeUpwindFaceQuantitiesForProjectionVars *vars;

  const pybind11::object get_idir() const {
    return pybind11::cast(idir);
  }

  const pybind11::object get_nb_vars_to_project() const {
    return pybind11::cast(nb_vars_to_project);
  }

  const pybind11::object get_nb_env() const {
    return pybind11::cast(nb_env);
  }

  const pybind11::object get_m_face_normal_velocity() const {
    return pybind11::cast(vars->m_face_normal_velocity);
  }

  const pybind11::object get_m_deltax_lagrange() const {
    return pybind11::cast(vars->m_deltax_lagrange);
  }

  const pybind11::object get_m_phi_lagrange() const {
    return pybind11::cast(vars->m_phi_lagrange);
  }

  const pybind11::object get_m_face_coord() const {
    return pybind11::cast(vars->m_face_coord);
  }

  const pybind11::object get_m_cell_coord() const {
    return pybind11::cast(vars->m_cell_coord);
  }

  const pybind11::object get_m_face_normal() const {
    return pybind11::cast(vars->m_face_normal);
  }

  const pybind11::object get_m_grad_phi() const {
    return pybind11::cast(vars->m_grad_phi);
  }

  const pybind11::object get_m_delta_phi_face_av() const {
    return pybind11::cast(vars->m_delta_phi_face_av);
  }

  const pybind11::object get_m_delta_phi_face_ar() const {
    return pybind11::cast(vars->m_delta_phi_face_ar);
  }

  const pybind11::object get_m_h_cell_lagrange() const {
    return pybind11::cast(vars->m_h_cell_lagrange);
  }

  const pybind11::object get_m_est_mixte() const {
    return pybind11::cast(vars->m_est_mixte);
  }

  const pybind11::object get_m_est_pure() const {
    return pybind11::cast(vars->m_est_pure);
  }

  const pybind11::object get_m_phi_face() const {
    return pybind11::cast(vars->m_phi_face);
  }
};

//! Classe de contexte d'exécution pour computeUpwindFaceQuantitiesForProjection_PBorn0_O2
struct RemapADIComputeUpwindFaceQuantitiesForProjection_PBorn0_O2ExecutionContext final : SciHook::SciHookExecutionContext
{
  RemapADIComputeUpwindFaceQuantitiesForProjection_PBorn0_O2ExecutionContext(std::string execution_context_name,
      RemapADIComputeUpwindFaceQuantitiesForProjection_PBorn0_O2Vars *vars,
      const Integer idir,
      const Integer nb_vars_to_project)
  : SciHookExecutionContext(execution_context_name)
  , idir(idir)
  , nb_vars_to_project(nb_vars_to_project)
  , vars(vars)
  {}
  
  const Integer idir;
  const Integer nb_vars_to_project;
  const RemapADIComputeUpwindFaceQuantitiesForProjection_PBorn0_O2Vars *vars;

  const pybind11::object get_idir() const {
    return pybind11::cast(idir);
  }

  const pybind11::object get_nb_vars_to_project() const {
    return pybind11::cast(nb_vars_to_project);
  }

  const pybind11::object get_m_deltax_lagrange() const {
    return pybind11::cast(vars->m_deltax_lagrange);
  }

  const pybind11::object get_m_face_normal_velocity() const {
    return pybind11::cast(vars->m_face_normal_velocity);
  }

  const pybind11::object get_m_phi_lagrange() const {
    return pybind11::cast(vars->m_phi_lagrange);
  }

  const pybind11::object get_m_face_coord() const {
    return pybind11::cast(vars->m_face_coord);
  }

  const pybind11::object get_m_face_normal() const {
    return pybind11::cast(vars->m_face_normal);
  }

  const pybind11::object get_m_cell_coord() const {
    return pybind11::cast(vars->m_cell_coord);
  }

  const pybind11::object get_m_grad_phi() const {
    return pybind11::cast(vars->m_grad_phi);
  }

  const pybind11::object get_m_phi_face() const {
    return pybind11::cast(vars->m_phi_face);
  }
};

//! Classe de contexte d'exécution pour computeUremap
struct RemapADIComputeUremapExecutionContext final : SciHook::SciHookExecutionContext
{
  RemapADIComputeUremapExecutionContext(std::string execution_context_name,
      RemapADIComputeUremapVars *vars,
      const Integer idir,
      const Integer nb_vars_to_project,
      const Integer nb_env)
  : SciHookExecutionContext(execution_context_name)
  , idir(idir)
  , nb_vars_to_project(nb_vars_to_project)
  , nb_env(nb_env)
  , vars(vars)
  {}
  
  const Integer idir;
  const Integer nb_vars_to_project;
  const Integer nb_env;
  const RemapADIComputeUremapVars *vars;

  const pybind11::object get_idir() const {
    return pybind11::cast(idir);
  }

  const pybind11::object get_nb_vars_to_project() const {
    return pybind11::cast(nb_vars_to_project);
  }

  const pybind11::object get_nb_env() const {
    return pybind11::cast(nb_env);
  }

  const pybind11::object get_m_face_normal() const {
    return pybind11::cast(vars->m_face_normal);
  }

  const pybind11::object get_m_face_length_lagrange() const {
    return pybind11::cast(vars->m_face_length_lagrange);
  }

  const pybind11::object get_m_outer_face_normal() const {
    return pybind11::cast(vars->m_outer_face_normal);
  }

  const pybind11::object get_m_phi_face() const {
    return pybind11::cast(vars->m_phi_face);
  }

  const pybind11::object get_m_dual_phi_flux() const {
    return pybind11::cast(vars->m_dual_phi_flux);
  }

  const pybind11::object get_m_est_mixte() const {
    return pybind11::cast(vars->m_est_mixte);
  }

  const pybind11::object get_m_est_pure() const {
    return pybind11::cast(vars->m_est_pure);
  }

  const pybind11::object get_m_u_lagrange() const {
    return pybind11::cast(vars->m_u_lagrange);
  }

  const pybind11::object get_m_phi_lagrange() const {
    return pybind11::cast(vars->m_phi_lagrange);
  }
};

//! Classe de contexte d'exécution pour computeUremap_PBorn0
struct RemapADIComputeUremap_PBorn0ExecutionContext final : SciHook::SciHookExecutionContext
{
  RemapADIComputeUremap_PBorn0ExecutionContext(std::string execution_context_name,
      RemapADIComputeUremap_PBorn0Vars *vars,
      const Integer idir,
      const Integer nb_vars_to_project,
      const Integer nb_env)
  : SciHookExecutionContext(execution_context_name)
  , idir(idir)
  , nb_vars_to_project(nb_vars_to_project)
  , nb_env(nb_env)
  , vars(vars)
  {}
  
  const Integer idir;
  const Integer nb_vars_to_project;
  const Integer nb_env;
  const RemapADIComputeUremap_PBorn0Vars *vars;

  const pybind11::object get_idir() const {
    return pybind11::cast(idir);
  }

  const pybind11::object get_nb_vars_to_project() const {
    return pybind11::cast(nb_vars_to_project);
  }

  const pybind11::object get_nb_env() const {
    return pybind11::cast(nb_env);
  }

  const pybind11::object get_m_face_normal() const {
    return pybind11::cast(vars->m_face_normal);
  }

  const pybind11::object get_m_face_normal_velocity() const {
    return pybind11::cast(vars->m_face_normal_velocity);
  }

  const pybind11::object get_m_face_length_lagrange() const {
    return pybind11::cast(vars->m_face_length_lagrange);
  }

  const pybind11::object get_m_outer_face_normal() const {
    return pybind11::cast(vars->m_outer_face_normal);
  }

  const pybind11::object get_m_phi_face() const {
    return pybind11::cast(vars->m_phi_face);
  }

  const pybind11::object get_m_dual_phi_flux() const {
    return pybind11::cast(vars->m_dual_phi_flux);
  }

  const pybind11::object get_m_est_mixte() const {
    return pybind11::cast(vars->m_est_mixte);
  }

  const pybind11::object get_m_est_pure() const {
    return pybind11::cast(vars->m_est_pure);
  }

  const pybind11::object get_m_u_lagrange() const {
    return pybind11::cast(vars->m_u_lagrange);
  }

  const pybind11::object get_m_phi_lagrange() const {
    return pybind11::cast(vars->m_phi_lagrange);
  }
};

//! Classe de contexte d'exécution pour computeDualUremap
struct RemapADIComputeDualUremapExecutionContext final : SciHook::SciHookExecutionContext
{
  RemapADIComputeDualUremapExecutionContext(std::string execution_context_name,
      RemapADIComputeDualUremapVars *vars)
  : SciHookExecutionContext(execution_context_name)
  , vars(vars)
  {}
  
  const RemapADIComputeDualUremapVars *vars;

  const pybind11::object get_m_dual_phi_flux() const {
    return pybind11::cast(vars->m_dual_phi_flux);
  }

  const pybind11::object get_m_node_coord() const {
    return pybind11::cast(vars->m_node_coord);
  }

  const pybind11::object get_m_dual_grad_phi() const {
    return pybind11::cast(vars->m_dual_grad_phi);
  }

  const pybind11::object get_m_back_flux_contrib_env() const {
    return pybind11::cast(vars->m_back_flux_contrib_env);
  }

  const pybind11::object get_m_front_flux_contrib_env() const {
    return pybind11::cast(vars->m_front_flux_contrib_env);
  }

  const pybind11::object get_m_back_flux_mass() const {
    return pybind11::cast(vars->m_back_flux_mass);
  }

  const pybind11::object get_m_front_flux_mass() const {
    return pybind11::cast(vars->m_front_flux_mass);
  }

  const pybind11::object get_m_back_flux_mass_env() const {
    return pybind11::cast(vars->m_back_flux_mass_env);
  }

  const pybind11::object get_m_front_flux_mass_env() const {
    return pybind11::cast(vars->m_front_flux_mass_env);
  }

  const pybind11::object get_m_u_dual_lagrange() const {
    return pybind11::cast(vars->m_u_dual_lagrange);
  }

  const pybind11::object get_m_phi_dual_lagrange() const {
    return pybind11::cast(vars->m_phi_dual_lagrange);
  }
};

//! Classe de contexte d'exécution pour appliRemap
struct RemapADIAppliRemapExecutionContext final : SciHook::SciHookExecutionContext
{
  RemapADIAppliRemapExecutionContext(std::string execution_context_name,
      RemapADIAppliRemapVars *vars,
      const Integer dimension,
      const Integer withDualProjection,
      const Integer nb_vars_to_project,
      const Integer nb_env)
  : SciHookExecutionContext(execution_context_name)
  , dimension(dimension)
  , withDualProjection(withDualProjection)
  , nb_vars_to_project(nb_vars_to_project)
  , nb_env(nb_env)
  , vars(vars)
  {}
  
  const Integer dimension;
  const Integer withDualProjection;
  const Integer nb_vars_to_project;
  const Integer nb_env;
  const RemapADIAppliRemapVars *vars;

  const pybind11::object get_dimension() const {
    return pybind11::cast(dimension);
  }

  const pybind11::object get_withDualProjection() const {
    return pybind11::cast(withDualProjection);
  }

  const pybind11::object get_nb_vars_to_project() const {
    return pybind11::cast(nb_vars_to_project);
  }

  const pybind11::object get_nb_env() const {
    return pybind11::cast(nb_env);
  }

  const pybind11::object get_m_sens_projection() const {
    return pybind11::cast(vars->m_sens_projection);
  }
};

//! Classe de contexte d'exécution pour resizeRemapVariables
struct RemapADIResizeRemapVariablesExecutionContext final : SciHook::SciHookExecutionContext
{
  RemapADIResizeRemapVariablesExecutionContext(std::string execution_context_name,
      RemapADIResizeRemapVariablesVars *vars,
      const Integer nb_vars_to_project,
      const Integer nb_env)
  : SciHookExecutionContext(execution_context_name)
  , nb_vars_to_project(nb_vars_to_project)
  , nb_env(nb_env)
  , vars(vars)
  {}
  
  const Integer nb_vars_to_project;
  const Integer nb_env;
  const RemapADIResizeRemapVariablesVars *vars;

  const pybind11::object get_nb_vars_to_project() const {
    return pybind11::cast(nb_vars_to_project);
  }

  const pybind11::object get_nb_env() const {
    return pybind11::cast(nb_env);
  }

  const pybind11::object get_m_u_lagrange() const {
    return pybind11::cast(vars->m_u_lagrange);
  }

  const pybind11::object get_m_u_dual_lagrange() const {
    return pybind11::cast(vars->m_u_dual_lagrange);
  }

  const pybind11::object get_m_phi_lagrange() const {
    return pybind11::cast(vars->m_phi_lagrange);
  }

  const pybind11::object get_m_phi_dual_lagrange() const {
    return pybind11::cast(vars->m_phi_dual_lagrange);
  }

  const pybind11::object get_m_dual_grad_phi() const {
    return pybind11::cast(vars->m_dual_grad_phi);
  }

  const pybind11::object get_m_grad_phi() const {
    return pybind11::cast(vars->m_grad_phi);
  }

  const pybind11::object get_m_phi_face() const {
    return pybind11::cast(vars->m_phi_face);
  }

  const pybind11::object get_m_grad_phi_face() const {
    return pybind11::cast(vars->m_grad_phi_face);
  }

  const pybind11::object get_m_delta_phi_face_ar() const {
    return pybind11::cast(vars->m_delta_phi_face_ar);
  }

  const pybind11::object get_m_delta_phi_face_av() const {
    return pybind11::cast(vars->m_delta_phi_face_av);
  }

  const pybind11::object get_m_dual_phi_flux() const {
    return pybind11::cast(vars->m_dual_phi_flux);
  }

  const pybind11::object get_m_front_flux_mass_env() const {
    return pybind11::cast(vars->m_front_flux_mass_env);
  }

  const pybind11::object get_m_back_flux_mass_env() const {
    return pybind11::cast(vars->m_back_flux_mass_env);
  }

  const pybind11::object get_m_back_flux_contrib_env() const {
    return pybind11::cast(vars->m_back_flux_contrib_env);
  }

  const pybind11::object get_m_front_flux_contrib_env() const {
    return pybind11::cast(vars->m_front_flux_contrib_env);
  }
};

//! Classe de contexte d'exécution pour synchronizeUremap
struct RemapADISynchronizeUremapExecutionContext final : SciHook::SciHookExecutionContext
{
  RemapADISynchronizeUremapExecutionContext(std::string execution_context_name,
      RemapADISynchronizeUremapVars *vars)
  : SciHookExecutionContext(execution_context_name)
  , vars(vars)
  {}
  
  const RemapADISynchronizeUremapVars *vars;

  const pybind11::object get_m_phi_lagrange() const {
    return pybind11::cast(vars->m_phi_lagrange);
  }

  const pybind11::object get_m_u_lagrange() const {
    return pybind11::cast(vars->m_u_lagrange);
  }

  const pybind11::object get_m_dual_phi_flux() const {
    return pybind11::cast(vars->m_dual_phi_flux);
  }

  const pybind11::object get_m_est_mixte() const {
    return pybind11::cast(vars->m_est_mixte);
  }

  const pybind11::object get_m_est_pure() const {
    return pybind11::cast(vars->m_est_pure);
  }
};

//! Classe de contexte d'exécution pour remapVariables
struct RemapADIRemapVariablesExecutionContext final : SciHook::SciHookExecutionContext
{
  RemapADIRemapVariablesExecutionContext(std::string execution_context_name,
      RemapADIRemapVariablesVars *vars,
      const Integer dimension,
      const Integer withDualProjection,
      const Integer nb_vars_to_project,
      const Integer nb_env)
  : SciHookExecutionContext(execution_context_name)
  , dimension(dimension)
  , withDualProjection(withDualProjection)
  , nb_vars_to_project(nb_vars_to_project)
  , nb_env(nb_env)
  , vars(vars)
  {}
  
  const Integer dimension;
  const Integer withDualProjection;
  const Integer nb_vars_to_project;
  const Integer nb_env;
  const RemapADIRemapVariablesVars *vars;

  const pybind11::object get_dimension() const {
    return pybind11::cast(dimension);
  }

  const pybind11::object get_withDualProjection() const {
    return pybind11::cast(withDualProjection);
  }

  const pybind11::object get_nb_vars_to_project() const {
    return pybind11::cast(nb_vars_to_project);
  }

  const pybind11::object get_nb_env() const {
    return pybind11::cast(nb_env);
  }

  const pybind11::object get_m_euler_volume() const {
    return pybind11::cast(vars->m_euler_volume);
  }

  const pybind11::object get_m_u_lagrange() const {
    return pybind11::cast(vars->m_u_lagrange);
  }

  const pybind11::object get_m_u_dual_lagrange() const {
    return pybind11::cast(vars->m_u_dual_lagrange);
  }

  const pybind11::object get_m_est_pure() const {
    return pybind11::cast(vars->m_est_pure);
  }

  const pybind11::object get_m_velocity() const {
    return pybind11::cast(vars->m_velocity);
  }

  const pybind11::object get_m_node_mass() const {
    return pybind11::cast(vars->m_node_mass);
  }

  const pybind11::object get_m_cell_volume() const {
    return pybind11::cast(vars->m_cell_volume);
  }

  const pybind11::object get_m_cell_status() const {
    return pybind11::cast(vars->m_cell_status);
  }

  const pybind11::object get_m_est_mixte() const {
    return pybind11::cast(vars->m_est_mixte);
  }

  const pybind11::object get_m_cell_mass() const {
    return pybind11::cast(vars->m_cell_mass);
  }

  const pybind11::object get_m_fracvol() const {
    return pybind11::cast(vars->m_fracvol);
  }

  const pybind11::object get_m_mass_fraction() const {
    return pybind11::cast(vars->m_mass_fraction);
  }

  const pybind11::object get_m_pseudo_viscosity() const {
    return pybind11::cast(vars->m_pseudo_viscosity);
  }

  const pybind11::object get_m_density() const {
    return pybind11::cast(vars->m_density);
  }

  const pybind11::object get_m_internal_energy() const {
    return pybind11::cast(vars->m_internal_energy);
  }
};


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace Remap

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // REMAP___REMAPADISERVICECONTEXTS_H
