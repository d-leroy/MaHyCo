#ifndef MAHYCO___MAHYCOMODULECONTEXTS_H
#define MAHYCO___MAHYCOMODULECONTEXTS_H

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
namespace Mahyco {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

//! Classe de contexte d'exécution pour allocCqs
struct MahycoAllocCqsExecutionContext final : SciHook::SciHookExecutionContext
{
  MahycoAllocCqsExecutionContext(std::string execution_context_name,
      MahycoAllocCqsVars *vars)
  : SciHookExecutionContext(execution_context_name)
  , vars(vars)
  {}
  
  const MahycoAllocCqsVars *vars;

  const pybind11::object get_m_cell_cqs() const {
    return pybind11::cast(vars->m_cell_cqs);
  }

  const pybind11::object get_m_cell_cqs_n() const {
    return pybind11::cast(vars->m_cell_cqs_n);
  }
};

//! Classe de contexte d'exécution pour initHydroVar
struct MahycoInitHydroVarExecutionContext final : SciHook::SciHookExecutionContext
{
  MahycoInitHydroVarExecutionContext(std::string execution_context_name,
      MahycoInitHydroVarVars *vars)
  : SciHookExecutionContext(execution_context_name)
  , vars(vars)
  {}
  
  const MahycoInitHydroVarVars *vars;

  const pybind11::object get_m_cell_cqs() const {
    return pybind11::cast(vars->m_cell_cqs);
  }

  const pybind11::object get_m_mass_fraction() const {
    return pybind11::cast(vars->m_mass_fraction);
  }

  const pybind11::object get_m_node_coord() const {
    return pybind11::cast(vars->m_node_coord);
  }

  const pybind11::object get_m_euler_volume() const {
    return pybind11::cast(vars->m_euler_volume);
  }

  const pybind11::object get_m_cell_volume() const {
    return pybind11::cast(vars->m_cell_volume);
  }

  const pybind11::object get_m_internal_energy() const {
    return pybind11::cast(vars->m_internal_energy);
  }

  const pybind11::object get_m_sound_speed() const {
    return pybind11::cast(vars->m_sound_speed);
  }
};

//! Classe de contexte d'exécution pour prepareFaceGroupForBc
struct MahycoPrepareFaceGroupForBcExecutionContext final : SciHook::SciHookExecutionContext
{
  MahycoPrepareFaceGroupForBcExecutionContext(std::string execution_context_name,
      MahycoPrepareFaceGroupForBcVars *vars)
  : SciHookExecutionContext(execution_context_name)
  , vars(vars)
  {}
  
  const MahycoPrepareFaceGroupForBcVars *vars;

  const pybind11::object get_m_node_coord() const {
    return pybind11::cast(vars->m_node_coord);
  }
};

//! Classe de contexte d'exécution pour computeCellMass
struct MahycoComputeCellMassExecutionContext final : SciHook::SciHookExecutionContext
{
  MahycoComputeCellMassExecutionContext(std::string execution_context_name,
      MahycoComputeCellMassVars *vars)
  : SciHookExecutionContext(execution_context_name)
  , vars(vars)
  {}
  
  const MahycoComputeCellMassVars *vars;

  const pybind11::object get_m_density() const {
    return pybind11::cast(vars->m_density);
  }

  const pybind11::object get_m_cell_volume() const {
    return pybind11::cast(vars->m_cell_volume);
  }

  const pybind11::object get_m_mass_fraction() const {
    return pybind11::cast(vars->m_mass_fraction);
  }

  const pybind11::object get_m_cell_mass() const {
    return pybind11::cast(vars->m_cell_mass);
  }
};

//! Classe de contexte d'exécution pour computeNodeMass
struct MahycoComputeNodeMassExecutionContext final : SciHook::SciHookExecutionContext
{
  MahycoComputeNodeMassExecutionContext(std::string execution_context_name,
      MahycoComputeNodeMassVars *vars)
  : SciHookExecutionContext(execution_context_name)
  , vars(vars)
  {}
  
  const MahycoComputeNodeMassVars *vars;

  const pybind11::object get_m_cell_mass() const {
    return pybind11::cast(vars->m_cell_mass);
  }

  const pybind11::object get_m_node_mass() const {
    return pybind11::cast(vars->m_node_mass);
  }
};

//! Classe de contexte d'exécution pour continueForIterationDt
struct MahycoContinueForIterationDtExecutionContext final : SciHook::SciHookExecutionContext
{
  MahycoContinueForIterationDtExecutionContext(std::string execution_context_name,
      MahycoContinueForIterationDtVars *vars)
  : SciHookExecutionContext(execution_context_name)
  , vars(vars)
  {}
  
  const MahycoContinueForIterationDtVars *vars;

  const pybind11::object get_m_old_deltat() const {
    return pybind11::cast(vars->m_old_deltat);
  }
};

//! Classe de contexte d'exécution pour saveValuesAtN
struct MahycoSaveValuesAtNExecutionContext final : SciHook::SciHookExecutionContext
{
  MahycoSaveValuesAtNExecutionContext(std::string execution_context_name,
      MahycoSaveValuesAtNVars *vars)
  : SciHookExecutionContext(execution_context_name)
  , vars(vars)
  {}
  
  const MahycoSaveValuesAtNVars *vars;

  const pybind11::object get_m_old_deltat() const {
    return pybind11::cast(vars->m_old_deltat);
  }

  const pybind11::object get_m_pseudo_viscosity() const {
    return pybind11::cast(vars->m_pseudo_viscosity);
  }

  const pybind11::object get_m_pressure() const {
    return pybind11::cast(vars->m_pressure);
  }

  const pybind11::object get_m_cell_volume() const {
    return pybind11::cast(vars->m_cell_volume);
  }

  const pybind11::object get_m_density() const {
    return pybind11::cast(vars->m_density);
  }

  const pybind11::object get_m_internal_energy() const {
    return pybind11::cast(vars->m_internal_energy);
  }

  const pybind11::object get_m_cell_cqs() const {
    return pybind11::cast(vars->m_cell_cqs);
  }

  const pybind11::object get_m_velocity() const {
    return pybind11::cast(vars->m_velocity);
  }

  const pybind11::object get_m_node_coord_0() const {
    return pybind11::cast(vars->m_node_coord_0);
  }

  const pybind11::object get_m_pseudo_viscosity_nmoins1() const {
    return pybind11::cast(vars->m_pseudo_viscosity_nmoins1);
  }

  const pybind11::object get_m_pressure_n() const {
    return pybind11::cast(vars->m_pressure_n);
  }

  const pybind11::object get_m_cell_volume_n() const {
    return pybind11::cast(vars->m_cell_volume_n);
  }

  const pybind11::object get_m_density_n() const {
    return pybind11::cast(vars->m_density_n);
  }

  const pybind11::object get_m_internal_energy_n() const {
    return pybind11::cast(vars->m_internal_energy_n);
  }

  const pybind11::object get_m_cell_cqs_n() const {
    return pybind11::cast(vars->m_cell_cqs_n);
  }

  const pybind11::object get_m_velocity_n() const {
    return pybind11::cast(vars->m_velocity_n);
  }

  const pybind11::object get_m_node_coord() const {
    return pybind11::cast(vars->m_node_coord);
  }

  const pybind11::object get_m_pseudo_viscosity_n() const {
    return pybind11::cast(vars->m_pseudo_viscosity_n);
  }
};

//! Classe de contexte d'exécution pour updatePosition
struct MahycoUpdatePositionExecutionContext final : SciHook::SciHookExecutionContext
{
  MahycoUpdatePositionExecutionContext(std::string execution_context_name,
      MahycoUpdatePositionVars *vars)
  : SciHookExecutionContext(execution_context_name)
  , vars(vars)
  {}
  
  const MahycoUpdatePositionVars *vars;

  const pybind11::object get_m_velocity() const {
    return pybind11::cast(vars->m_velocity);
  }

  const pybind11::object get_m_cell_coord() const {
    return pybind11::cast(vars->m_cell_coord);
  }

  const pybind11::object get_m_node_coord() const {
    return pybind11::cast(vars->m_node_coord);
  }
};

//! Classe de contexte d'exécution pour updateDensity
struct MahycoUpdateDensityExecutionContext final : SciHook::SciHookExecutionContext
{
  MahycoUpdateDensityExecutionContext(std::string execution_context_name,
      MahycoUpdateDensityVars *vars)
  : SciHookExecutionContext(execution_context_name)
  , vars(vars)
  {}
  
  const MahycoUpdateDensityVars *vars;

  const pybind11::object get_m_cell_mass() const {
    return pybind11::cast(vars->m_cell_mass);
  }

  const pybind11::object get_m_cell_volume() const {
    return pybind11::cast(vars->m_cell_volume);
  }

  const pybind11::object get_m_density_n() const {
    return pybind11::cast(vars->m_density_n);
  }

  const pybind11::object get_m_div_u() const {
    return pybind11::cast(vars->m_div_u);
  }

  const pybind11::object get_m_density() const {
    return pybind11::cast(vars->m_density);
  }

  const pybind11::object get_m_tau_density() const {
    return pybind11::cast(vars->m_tau_density);
  }
};

//! Classe de contexte d'exécution pour computeArtificialViscosity
struct MahycoComputeArtificialViscosityExecutionContext final : SciHook::SciHookExecutionContext
{
  MahycoComputeArtificialViscosityExecutionContext(std::string execution_context_name,
      MahycoComputeArtificialViscosityVars *vars)
  : SciHookExecutionContext(execution_context_name)
  , vars(vars)
  {}
  
  const MahycoComputeArtificialViscosityVars *vars;

  const pybind11::object get_m_div_u() const {
    return pybind11::cast(vars->m_div_u);
  }

  const pybind11::object get_m_caracteristic_length() const {
    return pybind11::cast(vars->m_caracteristic_length);
  }

  const pybind11::object get_m_sound_speed() const {
    return pybind11::cast(vars->m_sound_speed);
  }

  const pybind11::object get_m_tau_density() const {
    return pybind11::cast(vars->m_tau_density);
  }

  const pybind11::object get_m_fracvol() const {
    return pybind11::cast(vars->m_fracvol);
  }

  const pybind11::object get_m_pseudo_viscosity() const {
    return pybind11::cast(vars->m_pseudo_viscosity);
  }
};

//! Classe de contexte d'exécution pour computeDeltaT
struct MahycoComputeDeltaTExecutionContext final : SciHook::SciHookExecutionContext
{
  MahycoComputeDeltaTExecutionContext(std::string execution_context_name,
      MahycoComputeDeltaTVars *vars)
  : SciHookExecutionContext(execution_context_name)
  , vars(vars)
  {}
  
  const MahycoComputeDeltaTVars *vars;

  const pybind11::object get_m_old_deltat() const {
    return pybind11::cast(vars->m_old_deltat);
  }
};

//! Classe de contexte d'exécution pour initGeometricValues
struct MahycoInitGeometricValuesExecutionContext final : SciHook::SciHookExecutionContext
{
  MahycoInitGeometricValuesExecutionContext(std::string execution_context_name,
      MahycoInitGeometricValuesVars *vars)
  : SciHookExecutionContext(execution_context_name)
  , vars(vars)
  {}
  
  const MahycoInitGeometricValuesVars *vars;

  const pybind11::object get_m_cell_coord() const {
    return pybind11::cast(vars->m_cell_coord);
  }

  const pybind11::object get_m_node_coord() const {
    return pybind11::cast(vars->m_node_coord);
  }

  const pybind11::object get_m_node_coord_0() const {
    return pybind11::cast(vars->m_node_coord_0);
  }

  const pybind11::object get_m_outer_face_normal() const {
    return pybind11::cast(vars->m_outer_face_normal);
  }

  const pybind11::object get_m_face_coord() const {
    return pybind11::cast(vars->m_face_coord);
  }

  const pybind11::object get_m_face_normal() const {
    return pybind11::cast(vars->m_face_normal);
  }
};

//! Classe de contexte d'exécution pour computeGeometricValuesAux
struct MahycoComputeGeometricValuesAuxExecutionContext final : SciHook::SciHookExecutionContext
{
  MahycoComputeGeometricValuesAuxExecutionContext(std::string execution_context_name,
      MahycoComputeGeometricValuesAuxVars *vars)
  : SciHookExecutionContext(execution_context_name)
  , vars(vars)
  {}
  
  const MahycoComputeGeometricValuesAuxVars *vars;

  const pybind11::object get_m_fracvol() const {
    return pybind11::cast(vars->m_fracvol);
  }

  const pybind11::object get_m_velocity() const {
    return pybind11::cast(vars->m_velocity);
  }

  const pybind11::object get_m_cell_cqs() const {
    return pybind11::cast(vars->m_cell_cqs);
  }

  const pybind11::object get_m_node_coord() const {
    return pybind11::cast(vars->m_node_coord);
  }

  const pybind11::object get_m_cell_volume() const {
    return pybind11::cast(vars->m_cell_volume);
  }
};

//! Classe de contexte d'exécution pour updateVelocityWithoutLagrange
struct MahycoUpdateVelocityWithoutLagrangeExecutionContext final : SciHook::SciHookExecutionContext
{
  MahycoUpdateVelocityWithoutLagrangeExecutionContext(std::string execution_context_name,
      MahycoUpdateVelocityWithoutLagrangeVars *vars)
  : SciHookExecutionContext(execution_context_name)
  , vars(vars)
  {}
  
  const MahycoUpdateVelocityWithoutLagrangeVars *vars;

  const pybind11::object get_m_velocity_n() const {
    return pybind11::cast(vars->m_velocity_n);
  }

  const pybind11::object get_m_velocity() const {
    return pybind11::cast(vars->m_velocity);
  }
};

//! Classe de contexte d'exécution pour updateForceAndVelocity
struct MahycoUpdateForceAndVelocityExecutionContext final : SciHook::SciHookExecutionContext
{
  MahycoUpdateForceAndVelocityExecutionContext(std::string execution_context_name,
      MahycoUpdateForceAndVelocityVars *vars)
  : SciHookExecutionContext(execution_context_name)
  , vars(vars)
  {}
  
  const MahycoUpdateForceAndVelocityVars *vars;

  const pybind11::object get_m_pressure() const {
    return pybind11::cast(vars->m_pressure);
  }

  const pybind11::object get_m_pseudo_viscosity() const {
    return pybind11::cast(vars->m_pseudo_viscosity);
  }

  const pybind11::object get_m_cell_cqs() const {
    return pybind11::cast(vars->m_cell_cqs);
  }

  const pybind11::object get_m_node_mass() const {
    return pybind11::cast(vars->m_node_mass);
  }

  const pybind11::object get_m_force() const {
    return pybind11::cast(vars->m_force);
  }

  const pybind11::object get_m_velocity() const {
    return pybind11::cast(vars->m_velocity);
  }
};

//! Classe de contexte d'exécution pour updateEnergyAndPressurebyNewton
struct MahycoUpdateEnergyAndPressurebyNewtonExecutionContext final : SciHook::SciHookExecutionContext
{
  MahycoUpdateEnergyAndPressurebyNewtonExecutionContext(std::string execution_context_name,
      MahycoUpdateEnergyAndPressurebyNewtonVars *vars)
  : SciHookExecutionContext(execution_context_name)
  , vars(vars)
  {}
  
  const MahycoUpdateEnergyAndPressurebyNewtonVars *vars;

  const pybind11::object get_m_pseudo_viscosity() const {
    return pybind11::cast(vars->m_pseudo_viscosity);
  }

  const pybind11::object get_m_pseudo_viscosity_n() const {
    return pybind11::cast(vars->m_pseudo_viscosity_n);
  }

  const pybind11::object get_m_pseudo_viscosity_nmoins1() const {
    return pybind11::cast(vars->m_pseudo_viscosity_nmoins1);
  }

  const pybind11::object get_m_density() const {
    return pybind11::cast(vars->m_density);
  }

  const pybind11::object get_m_density_n() const {
    return pybind11::cast(vars->m_density_n);
  }

  const pybind11::object get_m_internal_energy_n() const {
    return pybind11::cast(vars->m_internal_energy_n);
  }

  const pybind11::object get_m_pressure_n() const {
    return pybind11::cast(vars->m_pressure_n);
  }

  const pybind11::object get_m_dpde() const {
    return pybind11::cast(vars->m_dpde);
  }

  const pybind11::object get_m_mass_fraction() const {
    return pybind11::cast(vars->m_mass_fraction);
  }

  const pybind11::object get_m_velocity() const {
    return pybind11::cast(vars->m_velocity);
  }

  const pybind11::object get_m_velocity_n() const {
    return pybind11::cast(vars->m_velocity_n);
  }

  const pybind11::object get_m_cell_cqs() const {
    return pybind11::cast(vars->m_cell_cqs);
  }

  const pybind11::object get_m_cell_cqs_n() const {
    return pybind11::cast(vars->m_cell_cqs_n);
  }

  const pybind11::object get_m_cell_mass() const {
    return pybind11::cast(vars->m_cell_mass);
  }

  const pybind11::object get_m_internal_energy() const {
    return pybind11::cast(vars->m_internal_energy);
  }

  const pybind11::object get_m_pressure() const {
    return pybind11::cast(vars->m_pressure);
  }

  const pybind11::object get_m_sound_speed() const {
    return pybind11::cast(vars->m_sound_speed);
  }
};

//! Classe de contexte d'exécution pour updateEnergyAndPressureforGP
struct MahycoUpdateEnergyAndPressureforGPExecutionContext final : SciHook::SciHookExecutionContext
{
  MahycoUpdateEnergyAndPressureforGPExecutionContext(std::string execution_context_name,
      MahycoUpdateEnergyAndPressureforGPVars *vars)
  : SciHookExecutionContext(execution_context_name)
  , vars(vars)
  {}
  
  const MahycoUpdateEnergyAndPressureforGPVars *vars;

  const pybind11::object get_m_pseudo_viscosity() const {
    return pybind11::cast(vars->m_pseudo_viscosity);
  }

  const pybind11::object get_m_pseudo_viscosity_n() const {
    return pybind11::cast(vars->m_pseudo_viscosity_n);
  }

  const pybind11::object get_m_pseudo_viscosity_nmoins1() const {
    return pybind11::cast(vars->m_pseudo_viscosity_nmoins1);
  }

  const pybind11::object get_m_density() const {
    return pybind11::cast(vars->m_density);
  }

  const pybind11::object get_m_density_n() const {
    return pybind11::cast(vars->m_density_n);
  }

  const pybind11::object get_m_internal_energy_n() const {
    return pybind11::cast(vars->m_internal_energy_n);
  }

  const pybind11::object get_m_pressure_n() const {
    return pybind11::cast(vars->m_pressure_n);
  }

  const pybind11::object get_m_mass_fraction() const {
    return pybind11::cast(vars->m_mass_fraction);
  }

  const pybind11::object get_m_velocity() const {
    return pybind11::cast(vars->m_velocity);
  }

  const pybind11::object get_m_velocity_n() const {
    return pybind11::cast(vars->m_velocity_n);
  }

  const pybind11::object get_m_cell_cqs() const {
    return pybind11::cast(vars->m_cell_cqs);
  }

  const pybind11::object get_m_cell_cqs_n() const {
    return pybind11::cast(vars->m_cell_cqs_n);
  }

  const pybind11::object get_m_cell_mass() const {
    return pybind11::cast(vars->m_cell_mass);
  }

  const pybind11::object get_m_internal_energy() const {
    return pybind11::cast(vars->m_internal_energy);
  }

  const pybind11::object get_m_pressure() const {
    return pybind11::cast(vars->m_pressure);
  }
};

//! Classe de contexte d'exécution pour computeAveragePressure
struct MahycoComputeAveragePressureExecutionContext final : SciHook::SciHookExecutionContext
{
  MahycoComputeAveragePressureExecutionContext(std::string execution_context_name,
      MahycoComputeAveragePressureVars *vars)
  : SciHookExecutionContext(execution_context_name)
  , vars(vars)
  {}
  
  const MahycoComputeAveragePressureVars *vars;

  const pybind11::object get_m_fracvol() const {
    return pybind11::cast(vars->m_fracvol);
  }

  const pybind11::object get_m_pressure() const {
    return pybind11::cast(vars->m_pressure);
  }

  const pybind11::object get_m_sound_speed() const {
    return pybind11::cast(vars->m_sound_speed);
  }
};

//! Classe de contexte d'exécution pour computeHydroDeltaT
struct MahycoComputeHydroDeltaTExecutionContext final : SciHook::SciHookExecutionContext
{
  MahycoComputeHydroDeltaTExecutionContext(std::string execution_context_name,
      MahycoComputeHydroDeltaTVars *vars)
  : SciHookExecutionContext(execution_context_name)
  , vars(vars)
  {}
  
  const MahycoComputeHydroDeltaTVars *vars;

  const pybind11::object get_m_caracteristic_length() const {
    return pybind11::cast(vars->m_caracteristic_length);
  }

  const pybind11::object get_m_sound_speed() const {
    return pybind11::cast(vars->m_sound_speed);
  }

  const pybind11::object get_m_velocity() const {
    return pybind11::cast(vars->m_velocity);
  }
};


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace Mahyco

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // MAHYCO___MAHYCOMODULECONTEXTS_H
