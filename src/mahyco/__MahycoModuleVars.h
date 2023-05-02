#ifndef MAHYCO___MAHYCOMODULEVARS_H
#define MAHYCO___MAHYCOMODULEVARS_H

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

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

using namespace Arcane;
using namespace Arcane::Materials;
namespace Mahyco {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

//! Classe de variable pour allocCqs
struct MahycoAllocCqsVars final
{
  MahycoAllocCqsVars(VariableCellArrayReal3& cell_cqs,
      VariableCellArrayReal3& cell_cqs_n)
  : m_cell_cqs(cell_cqs)
  , m_cell_cqs_n(cell_cqs_n)
  {}

  /*!
  [out] cell_cqs
  */
  VariableCellArrayReal3& m_cell_cqs;
  /*!
  [out] cell_cqs_n
  */
  VariableCellArrayReal3& m_cell_cqs_n;
};

//! Classe de variable pour initDtIni
struct MahycoInitDtIniVars final
{
  MahycoInitDtIniVars()
  {}
};

//! Classe de variable pour initHydroVar
struct MahycoInitHydroVarVars final
{
  MahycoInitHydroVarVars(const VariableCellArrayReal3& cell_cqs,
      const MaterialVariableCellReal& mass_fraction,
      const VariableNodeReal3& node_coord,
      VariableCellReal& euler_volume,
      MaterialVariableCellReal& cell_volume,
      MaterialVariableCellReal& internal_energy,
      MaterialVariableCellReal& sound_speed)
  : m_cell_cqs(cell_cqs)
  , m_mass_fraction(mass_fraction)
  , m_node_coord(node_coord)
  , m_euler_volume(euler_volume)
  , m_cell_volume(cell_volume)
  , m_internal_energy(internal_energy)
  , m_sound_speed(sound_speed)
  {}

  /*!
  [in] cell_cqs
  */
  const VariableCellArrayReal3& m_cell_cqs;
  /*!
  [in] mass_fraction
  */
  const MaterialVariableCellReal& m_mass_fraction;
  /*!
  [in] node_coord
  */
  const VariableNodeReal3& m_node_coord;
  /*!
  [out] euler_volume
  */
  VariableCellReal& m_euler_volume;
  /*!
  [inout] cell_volume
  */
  MaterialVariableCellReal& m_cell_volume;
  /*!
  [inout] internal_energy
  */
  MaterialVariableCellReal& m_internal_energy;
  /*!
  [inout] sound_speed
  */
  MaterialVariableCellReal& m_sound_speed;
};

//! Classe de variable pour computeGeometricValuesIni
struct MahycoComputeGeometricValuesIniVars final
{
  MahycoComputeGeometricValuesIniVars()
  {}
};

//! Classe de variable pour prepareFaceGroupForBc
struct MahycoPrepareFaceGroupForBcVars final
{
  explicit MahycoPrepareFaceGroupForBcVars(const VariableNodeReal3& node_coord)
  : m_node_coord(node_coord)
  {}

  /*!
  [in] node_coord
  */
  const VariableNodeReal3& m_node_coord;
};

//! Classe de variable pour computeCellMass
struct MahycoComputeCellMassVars final
{
  MahycoComputeCellMassVars(const MaterialVariableCellReal& density,
      const MaterialVariableCellReal& cell_volume,
      const MaterialVariableCellReal& mass_fraction,
      MaterialVariableCellReal& cell_mass)
  : m_density(density)
  , m_cell_volume(cell_volume)
  , m_mass_fraction(mass_fraction)
  , m_cell_mass(cell_mass)
  {}

  /*!
  [in] density
  */
  const MaterialVariableCellReal& m_density;
  /*!
  [in] cell_volume
  */
  const MaterialVariableCellReal& m_cell_volume;
  /*!
  [in] mass_fraction
  */
  const MaterialVariableCellReal& m_mass_fraction;
  /*!
  [inout] cell_mass
  */
  MaterialVariableCellReal& m_cell_mass;
};

//! Classe de variable pour computeNodeMass
struct MahycoComputeNodeMassVars final
{
  MahycoComputeNodeMassVars(const MaterialVariableCellReal& cell_mass,
      VariableNodeReal& node_mass)
  : m_cell_mass(cell_mass)
  , m_node_mass(node_mass)
  {}

  /*!
  [in] cell_mass
  */
  const MaterialVariableCellReal& m_cell_mass;
  /*!
  [out] node_mass
  */
  VariableNodeReal& m_node_mass;
};

//! Classe de variable pour continueForIterationDt
struct MahycoContinueForIterationDtVars final
{
  explicit MahycoContinueForIterationDtVars(const VariableScalarReal& old_deltat)
  : m_old_deltat(old_deltat)
  {}

  /*!
  [in] old_deltat
  */
  const VariableScalarReal& m_old_deltat;
};

//! Classe de variable pour saveValuesAtN
struct MahycoSaveValuesAtNVars final
{
  MahycoSaveValuesAtNVars(const VariableScalarReal& old_deltat,
      const MaterialVariableCellReal& pseudo_viscosity,
      const MaterialVariableCellReal& pressure,
      const MaterialVariableCellReal& cell_volume,
      const MaterialVariableCellReal& density,
      const MaterialVariableCellReal& internal_energy,
      const VariableCellArrayReal3& cell_cqs,
      const VariableNodeReal3& velocity,
      const VariableNodeReal3& node_coord_0,
      MaterialVariableCellReal& pseudo_viscosity_nmoins1,
      MaterialVariableCellReal& pressure_n,
      MaterialVariableCellReal& cell_volume_n,
      MaterialVariableCellReal& density_n,
      MaterialVariableCellReal& internal_energy_n,
      VariableCellArrayReal3& cell_cqs_n,
      VariableNodeReal3& velocity_n,
      VariableNodeReal3& node_coord,
      MaterialVariableCellReal& pseudo_viscosity_n)
  : m_old_deltat(old_deltat)
  , m_pseudo_viscosity(pseudo_viscosity)
  , m_pressure(pressure)
  , m_cell_volume(cell_volume)
  , m_density(density)
  , m_internal_energy(internal_energy)
  , m_cell_cqs(cell_cqs)
  , m_velocity(velocity)
  , m_node_coord_0(node_coord_0)
  , m_pseudo_viscosity_nmoins1(pseudo_viscosity_nmoins1)
  , m_pressure_n(pressure_n)
  , m_cell_volume_n(cell_volume_n)
  , m_density_n(density_n)
  , m_internal_energy_n(internal_energy_n)
  , m_cell_cqs_n(cell_cqs_n)
  , m_velocity_n(velocity_n)
  , m_node_coord(node_coord)
  , m_pseudo_viscosity_n(pseudo_viscosity_n)
  {}

  /*!
  [in] old_deltat
  */
  const VariableScalarReal& m_old_deltat;
  /*!
  [in] pseudo_viscosity
  */
  const MaterialVariableCellReal& m_pseudo_viscosity;
  /*!
  [in] pressure
  */
  const MaterialVariableCellReal& m_pressure;
  /*!
  [in] cell_volume
  */
  const MaterialVariableCellReal& m_cell_volume;
  /*!
  [in] density
  */
  const MaterialVariableCellReal& m_density;
  /*!
  [in] internal_energy
  */
  const MaterialVariableCellReal& m_internal_energy;
  /*!
  [in] cell_cqs
  */
  const VariableCellArrayReal3& m_cell_cqs;
  /*!
  [in] velocity
  */
  const VariableNodeReal3& m_velocity;
  /*!
  [in] node_coord_0
  */
  const VariableNodeReal3& m_node_coord_0;
  /*!
  [out] pseudo_viscosity_nmoins1
  */
  MaterialVariableCellReal& m_pseudo_viscosity_nmoins1;
  /*!
  [out] pressure_n
  */
  MaterialVariableCellReal& m_pressure_n;
  /*!
  [out] cell_volume_n
  */
  MaterialVariableCellReal& m_cell_volume_n;
  /*!
  [out] density_n
  */
  MaterialVariableCellReal& m_density_n;
  /*!
  [out] internal_energy_n
  */
  MaterialVariableCellReal& m_internal_energy_n;
  /*!
  [out] cell_cqs_n
  */
  VariableCellArrayReal3& m_cell_cqs_n;
  /*!
  [out] velocity_n
  */
  VariableNodeReal3& m_velocity_n;
  /*!
  [out] node_coord
  */
  VariableNodeReal3& m_node_coord;
  /*!
  [inout] pseudo_viscosity_n
  */
  MaterialVariableCellReal& m_pseudo_viscosity_n;
};

//! Classe de variable pour updateVelocity
struct MahycoUpdateVelocityVars final
{
  MahycoUpdateVelocityVars()
  {}
};

//! Classe de variable pour updatePosition
struct MahycoUpdatePositionVars final
{
  MahycoUpdatePositionVars(const VariableNodeReal3& velocity,
      VariableCellReal3& cell_coord,
      VariableNodeReal3& node_coord)
  : m_velocity(velocity)
  , m_cell_coord(cell_coord)
  , m_node_coord(node_coord)
  {}

  /*!
  [in] velocity
  */
  const VariableNodeReal3& m_velocity;
  /*!
  [out] cell_coord
  */
  VariableCellReal3& m_cell_coord;
  /*!
  [inout] node_coord
  */
  VariableNodeReal3& m_node_coord;
};

//! Classe de variable pour computeGeometricValues
struct MahycoComputeGeometricValuesVars final
{
  MahycoComputeGeometricValuesVars()
  {}
};

//! Classe de variable pour updateDensity
struct MahycoUpdateDensityVars final
{
  MahycoUpdateDensityVars(const MaterialVariableCellReal& cell_mass,
      const MaterialVariableCellReal& cell_volume,
      const MaterialVariableCellReal& density_n,
      VariableCellReal& div_u,
      MaterialVariableCellReal& density,
      MaterialVariableCellReal& tau_density)
  : m_cell_mass(cell_mass)
  , m_cell_volume(cell_volume)
  , m_density_n(density_n)
  , m_div_u(div_u)
  , m_density(density)
  , m_tau_density(tau_density)
  {}

  /*!
  [in] cell_mass
  */
  const MaterialVariableCellReal& m_cell_mass;
  /*!
  [in] cell_volume
  */
  const MaterialVariableCellReal& m_cell_volume;
  /*!
  [in] density_n
  */
  const MaterialVariableCellReal& m_density_n;
  /*!
  [out] div_u
  */
  VariableCellReal& m_div_u;
  /*!
  [inout] density
  */
  MaterialVariableCellReal& m_density;
  /*!
  [inout] tau_density
  */
  MaterialVariableCellReal& m_tau_density;
};

//! Classe de variable pour computeArtificialViscosity
struct MahycoComputeArtificialViscosityVars final
{
  MahycoComputeArtificialViscosityVars(const VariableCellReal& div_u,
      const VariableCellReal& caracteristic_length,
      const MaterialVariableCellReal& sound_speed,
      const MaterialVariableCellReal& tau_density,
      const MaterialVariableCellReal& fracvol,
      MaterialVariableCellReal& pseudo_viscosity)
  : m_div_u(div_u)
  , m_caracteristic_length(caracteristic_length)
  , m_sound_speed(sound_speed)
  , m_tau_density(tau_density)
  , m_fracvol(fracvol)
  , m_pseudo_viscosity(pseudo_viscosity)
  {}

  /*!
  [in] div_u
  */
  const VariableCellReal& m_div_u;
  /*!
  [in] caracteristic_length
  */
  const VariableCellReal& m_caracteristic_length;
  /*!
  [in] sound_speed
  */
  const MaterialVariableCellReal& m_sound_speed;
  /*!
  [in] tau_density
  */
  const MaterialVariableCellReal& m_tau_density;
  /*!
  [in] fracvol
  */
  const MaterialVariableCellReal& m_fracvol;
  /*!
  [inout] pseudo_viscosity
  */
  MaterialVariableCellReal& m_pseudo_viscosity;
};

//! Classe de variable pour updateEnergyAndPressure
struct MahycoUpdateEnergyAndPressureVars final
{
  MahycoUpdateEnergyAndPressureVars()
  {}
};

//! Classe de variable pour computeDeltaT
struct MahycoComputeDeltaTVars final
{
  explicit MahycoComputeDeltaTVars(VariableScalarReal& old_deltat)
  : m_old_deltat(old_deltat)
  {}

  /*!
  [out] old_deltat
  */
  VariableScalarReal& m_old_deltat;
};

//! Classe de variable pour initGeometricValues
struct MahycoInitGeometricValuesVars final
{
  MahycoInitGeometricValuesVars(const VariableCellReal3& cell_coord,
      const VariableNodeReal3& node_coord,
      VariableNodeReal3& node_coord_0,
      VariableCellArrayReal3& outer_face_normal,
      VariableFaceReal3& face_coord,
      VariableFaceReal3& face_normal)
  : m_cell_coord(cell_coord)
  , m_node_coord(node_coord)
  , m_node_coord_0(node_coord_0)
  , m_outer_face_normal(outer_face_normal)
  , m_face_coord(face_coord)
  , m_face_normal(face_normal)
  {}

  /*!
  [in] cell_coord
  */
  const VariableCellReal3& m_cell_coord;
  /*!
  [in] node_coord
  */
  const VariableNodeReal3& m_node_coord;
  /*!
  [out] node_coord_0
  */
  VariableNodeReal3& m_node_coord_0;
  /*!
  [out] outer_face_normal
  */
  VariableCellArrayReal3& m_outer_face_normal;
  /*!
  [inout] face_coord
  */
  VariableFaceReal3& m_face_coord;
  /*!
  [inout] face_normal
  */
  VariableFaceReal3& m_face_normal;
};

//! Classe de variable pour computeGeometricValuesAux
struct MahycoComputeGeometricValuesAuxVars final
{
  MahycoComputeGeometricValuesAuxVars(const MaterialVariableCellReal& fracvol,
      const VariableNodeReal3& velocity,
      VariableCellArrayReal3& cell_cqs,
      VariableNodeReal3& node_coord,
      MaterialVariableCellReal& cell_volume)
  : m_fracvol(fracvol)
  , m_velocity(velocity)
  , m_cell_cqs(cell_cqs)
  , m_node_coord(node_coord)
  , m_cell_volume(cell_volume)
  {}

  /*!
  [in] fracvol
  */
  const MaterialVariableCellReal& m_fracvol;
  /*!
  [in] velocity
  */
  const VariableNodeReal3& m_velocity;
  /*!
  [out] cell_cqs
  */
  VariableCellArrayReal3& m_cell_cqs;
  /*!
  [inout] node_coord
  */
  VariableNodeReal3& m_node_coord;
  /*!
  [inout] cell_volume
  */
  MaterialVariableCellReal& m_cell_volume;
};

//! Classe de variable pour updateVelocityWithoutLagrange
struct MahycoUpdateVelocityWithoutLagrangeVars final
{
  MahycoUpdateVelocityWithoutLagrangeVars(const VariableNodeReal3& velocity_n,
      VariableNodeReal3& velocity)
  : m_velocity_n(velocity_n)
  , m_velocity(velocity)
  {}

  /*!
  [in] velocity_n
  */
  const VariableNodeReal3& m_velocity_n;
  /*!
  [out] velocity
  */
  VariableNodeReal3& m_velocity;
};

//! Classe de variable pour updateForceAndVelocity
struct MahycoUpdateForceAndVelocityVars final
{
  MahycoUpdateForceAndVelocityVars(const MaterialVariableCellReal& pressure,
      const MaterialVariableCellReal& pseudo_viscosity,
      const VariableCellArrayReal3& cell_cqs,
      const VariableNodeReal& node_mass,
      VariableNodeReal3& force,
      VariableNodeReal3& velocity)
  : m_pressure(pressure)
  , m_pseudo_viscosity(pseudo_viscosity)
  , m_cell_cqs(cell_cqs)
  , m_node_mass(node_mass)
  , m_force(force)
  , m_velocity(velocity)
  {}

  /*!
  [in] pressure
  */
  const MaterialVariableCellReal& m_pressure;
  /*!
  [in] pseudo_viscosity
  */
  const MaterialVariableCellReal& m_pseudo_viscosity;
  /*!
  [in] cell_cqs
  */
  const VariableCellArrayReal3& m_cell_cqs;
  /*!
  [in] node_mass
  */
  const VariableNodeReal& m_node_mass;
  /*!
  [out] force
  */
  VariableNodeReal3& m_force;
  /*!
  [inout] velocity
  */
  VariableNodeReal3& m_velocity;
};

//! Classe de variable pour updateEnergyAndPressurebyNewton
struct MahycoUpdateEnergyAndPressurebyNewtonVars final
{
  MahycoUpdateEnergyAndPressurebyNewtonVars(const MaterialVariableCellReal& pseudo_viscosity,
      const MaterialVariableCellReal& pseudo_viscosity_n,
      const MaterialVariableCellReal& pseudo_viscosity_nmoins1,
      const MaterialVariableCellReal& density,
      const MaterialVariableCellReal& density_n,
      const MaterialVariableCellReal& internal_energy_n,
      const MaterialVariableCellReal& pressure_n,
      const MaterialVariableCellReal& dpde,
      const MaterialVariableCellReal& mass_fraction,
      const VariableNodeReal3& velocity,
      const VariableNodeReal3& velocity_n,
      const VariableCellArrayReal3& cell_cqs,
      const VariableCellArrayReal3& cell_cqs_n,
      const MaterialVariableCellReal& cell_mass,
      MaterialVariableCellReal& internal_energy,
      MaterialVariableCellReal& pressure,
      MaterialVariableCellReal& sound_speed)
  : m_pseudo_viscosity(pseudo_viscosity)
  , m_pseudo_viscosity_n(pseudo_viscosity_n)
  , m_pseudo_viscosity_nmoins1(pseudo_viscosity_nmoins1)
  , m_density(density)
  , m_density_n(density_n)
  , m_internal_energy_n(internal_energy_n)
  , m_pressure_n(pressure_n)
  , m_dpde(dpde)
  , m_mass_fraction(mass_fraction)
  , m_velocity(velocity)
  , m_velocity_n(velocity_n)
  , m_cell_cqs(cell_cqs)
  , m_cell_cqs_n(cell_cqs_n)
  , m_cell_mass(cell_mass)
  , m_internal_energy(internal_energy)
  , m_pressure(pressure)
  , m_sound_speed(sound_speed)
  {}

  /*!
  [in] pseudo_viscosity
  */
  const MaterialVariableCellReal& m_pseudo_viscosity;
  /*!
  [in] pseudo_viscosity_n
  */
  const MaterialVariableCellReal& m_pseudo_viscosity_n;
  /*!
  [in] pseudo_viscosity_nmoins1
  */
  const MaterialVariableCellReal& m_pseudo_viscosity_nmoins1;
  /*!
  [in] density
  */
  const MaterialVariableCellReal& m_density;
  /*!
  [in] density_n
  */
  const MaterialVariableCellReal& m_density_n;
  /*!
  [in] internal_energy_n
  */
  const MaterialVariableCellReal& m_internal_energy_n;
  /*!
  [in] pressure_n
  */
  const MaterialVariableCellReal& m_pressure_n;
  /*!
  [in] dpde
  */
  const MaterialVariableCellReal& m_dpde;
  /*!
  [in] mass_fraction
  */
  const MaterialVariableCellReal& m_mass_fraction;
  /*!
  [in] velocity
  */
  const VariableNodeReal3& m_velocity;
  /*!
  [in] velocity_n
  */
  const VariableNodeReal3& m_velocity_n;
  /*!
  [in] cell_cqs
  */
  const VariableCellArrayReal3& m_cell_cqs;
  /*!
  [in] cell_cqs_n
  */
  const VariableCellArrayReal3& m_cell_cqs_n;
  /*!
  [in] cell_mass
  */
  const MaterialVariableCellReal& m_cell_mass;
  /*!
  [out] internal_energy
  */
  MaterialVariableCellReal& m_internal_energy;
  /*!
  [inout] pressure
  */
  MaterialVariableCellReal& m_pressure;
  /*!
  [inout] sound_speed
  */
  MaterialVariableCellReal& m_sound_speed;
};

//! Classe de variable pour updateEnergyAndPressureforGP
struct MahycoUpdateEnergyAndPressureforGPVars final
{
  MahycoUpdateEnergyAndPressureforGPVars(const MaterialVariableCellReal& pseudo_viscosity,
      const MaterialVariableCellReal& pseudo_viscosity_n,
      const MaterialVariableCellReal& pseudo_viscosity_nmoins1,
      const MaterialVariableCellReal& density,
      const MaterialVariableCellReal& density_n,
      const MaterialVariableCellReal& internal_energy_n,
      const MaterialVariableCellReal& pressure_n,
      const MaterialVariableCellReal& mass_fraction,
      const VariableNodeReal3& velocity,
      const VariableNodeReal3& velocity_n,
      const VariableCellArrayReal3& cell_cqs,
      const VariableCellArrayReal3& cell_cqs_n,
      const MaterialVariableCellReal& cell_mass,
      MaterialVariableCellReal& internal_energy,
      MaterialVariableCellReal& pressure)
  : m_pseudo_viscosity(pseudo_viscosity)
  , m_pseudo_viscosity_n(pseudo_viscosity_n)
  , m_pseudo_viscosity_nmoins1(pseudo_viscosity_nmoins1)
  , m_density(density)
  , m_density_n(density_n)
  , m_internal_energy_n(internal_energy_n)
  , m_pressure_n(pressure_n)
  , m_mass_fraction(mass_fraction)
  , m_velocity(velocity)
  , m_velocity_n(velocity_n)
  , m_cell_cqs(cell_cqs)
  , m_cell_cqs_n(cell_cqs_n)
  , m_cell_mass(cell_mass)
  , m_internal_energy(internal_energy)
  , m_pressure(pressure)
  {}

  /*!
  [in] pseudo_viscosity
  */
  const MaterialVariableCellReal& m_pseudo_viscosity;
  /*!
  [in] pseudo_viscosity_n
  */
  const MaterialVariableCellReal& m_pseudo_viscosity_n;
  /*!
  [in] pseudo_viscosity_nmoins1
  */
  const MaterialVariableCellReal& m_pseudo_viscosity_nmoins1;
  /*!
  [in] density
  */
  const MaterialVariableCellReal& m_density;
  /*!
  [in] density_n
  */
  const MaterialVariableCellReal& m_density_n;
  /*!
  [in] internal_energy_n
  */
  const MaterialVariableCellReal& m_internal_energy_n;
  /*!
  [in] pressure_n
  */
  const MaterialVariableCellReal& m_pressure_n;
  /*!
  [in] mass_fraction
  */
  const MaterialVariableCellReal& m_mass_fraction;
  /*!
  [in] velocity
  */
  const VariableNodeReal3& m_velocity;
  /*!
  [in] velocity_n
  */
  const VariableNodeReal3& m_velocity_n;
  /*!
  [in] cell_cqs
  */
  const VariableCellArrayReal3& m_cell_cqs;
  /*!
  [in] cell_cqs_n
  */
  const VariableCellArrayReal3& m_cell_cqs_n;
  /*!
  [in] cell_mass
  */
  const MaterialVariableCellReal& m_cell_mass;
  /*!
  [out] internal_energy
  */
  MaterialVariableCellReal& m_internal_energy;
  /*!
  [inout] pressure
  */
  MaterialVariableCellReal& m_pressure;
};

//! Classe de variable pour computeAveragePressure
struct MahycoComputeAveragePressureVars final
{
  MahycoComputeAveragePressureVars(const MaterialVariableCellReal& fracvol,
      MaterialVariableCellReal& pressure,
      MaterialVariableCellReal& sound_speed)
  : m_fracvol(fracvol)
  , m_pressure(pressure)
  , m_sound_speed(sound_speed)
  {}

  /*!
  [in] fracvol
  */
  const MaterialVariableCellReal& m_fracvol;
  /*!
  [inout] pressure
  */
  MaterialVariableCellReal& m_pressure;
  /*!
  [inout] sound_speed
  */
  MaterialVariableCellReal& m_sound_speed;
};

//! Classe de variable pour computeHydroDeltaT
struct MahycoComputeHydroDeltaTVars final
{
  MahycoComputeHydroDeltaTVars(const VariableCellReal& caracteristic_length,
      const MaterialVariableCellReal& sound_speed,
      const VariableNodeReal3& velocity)
  : m_caracteristic_length(caracteristic_length)
  , m_sound_speed(sound_speed)
  , m_velocity(velocity)
  {}

  /*!
  [in] caracteristic_length
  */
  const VariableCellReal& m_caracteristic_length;
  /*!
  [in] sound_speed
  */
  const MaterialVariableCellReal& m_sound_speed;
  /*!
  [in] velocity
  */
  const VariableNodeReal3& m_velocity;
};


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace Mahyco

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // MAHYCO___MAHYCOMODULEVARS_H
