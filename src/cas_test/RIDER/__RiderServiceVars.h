#ifndef CAS_TEST_RIDER___RIDERSERVICEVARS_H
#define CAS_TEST_RIDER___RIDERSERVICEVARS_H

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
namespace Cas_testRIDER {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

//! Classe de variable pour initMatMono
struct RiderInitMatMonoVars final
{
  explicit RiderInitMatMonoVars(VariableCellReal& materiau)
  : m_materiau(materiau)
  {}

  /*!
  [out] materiau
   Materiau 
  */
  VariableCellReal& m_materiau;
};

//! Classe de variable pour initVarMono
struct RiderInitVarMonoVars final
{
  RiderInitVarMonoVars(const VariableNodeReal3& node_coord,
      MaterialVariableCellReal& pseudo_viscosity,
      MaterialVariableCellReal& density,
      MaterialVariableCellReal& pressure,
      MaterialVariableCellReal& fracvol,
      MaterialVariableCellReal& mass_fraction,
      VariableNodeReal3& velocity_n,
      VariableNodeReal3& velocity)
  : m_node_coord(node_coord)
  , m_pseudo_viscosity(pseudo_viscosity)
  , m_density(density)
  , m_pressure(pressure)
  , m_fracvol(fracvol)
  , m_mass_fraction(mass_fraction)
  , m_velocity_n(velocity_n)
  , m_velocity(velocity)
  {}

  /*!
  [in] node_coord
   NODE COORD 
  */
  const VariableNodeReal3& m_node_coord;
  /*!
  [out] pseudo_viscosity
   PSEUDO 
  */
  MaterialVariableCellReal& m_pseudo_viscosity;
  /*!
  [out] density
   DENSITY 
  */
  MaterialVariableCellReal& m_density;
  /*!
  [out] pressure
   PRESSURE 
  */
  MaterialVariableCellReal& m_pressure;
  /*!
  [out] fracvol
   FRACVOL 
  */
  MaterialVariableCellReal& m_fracvol;
  /*!
  [out] mass_fraction
   MASS FRACTION 
  */
  MaterialVariableCellReal& m_mass_fraction;
  /*!
  [out] velocity_n
   VELOCITY OLD N 
  */
  VariableNodeReal3& m_velocity_n;
  /*!
  [inout] velocity
   VELOCITY 
  */
  VariableNodeReal3& m_velocity;
};

//! Classe de variable pour initMat
struct RiderInitMatVars final
{
  RiderInitMatVars(const VariableNodeReal3& node_coord,
      VariableCellReal& materiau)
  : m_node_coord(node_coord)
  , m_materiau(materiau)
  {}

  /*!
  [in] node_coord
   NODE COORD 
  */
  const VariableNodeReal3& m_node_coord;
  /*!
  [out] materiau
   Materiau 
  */
  VariableCellReal& m_materiau;
};

//! Classe de variable pour initVar
struct RiderInitVarVars final
{
  RiderInitVarVars(const VariableNodeReal3& node_coord,
      MaterialVariableCellReal& pseudo_viscosity,
      MaterialVariableCellReal& density,
      MaterialVariableCellReal& pressure,
      MaterialVariableCellReal& fracvol,
      MaterialVariableCellReal& mass_fraction,
      VariableNodeReal3& velocity_n,
      VariableNodeReal3& velocity)
  : m_node_coord(node_coord)
  , m_pseudo_viscosity(pseudo_viscosity)
  , m_density(density)
  , m_pressure(pressure)
  , m_fracvol(fracvol)
  , m_mass_fraction(mass_fraction)
  , m_velocity_n(velocity_n)
  , m_velocity(velocity)
  {}

  /*!
  [in] node_coord
   NODE COORD 
  */
  const VariableNodeReal3& m_node_coord;
  /*!
  [out] pseudo_viscosity
   PSEUDO 
  */
  MaterialVariableCellReal& m_pseudo_viscosity;
  /*!
  [out] density
   DENSITY 
  */
  MaterialVariableCellReal& m_density;
  /*!
  [out] pressure
   PRESSURE 
  */
  MaterialVariableCellReal& m_pressure;
  /*!
  [out] fracvol
   FRACVOL 
  */
  MaterialVariableCellReal& m_fracvol;
  /*!
  [out] mass_fraction
   MASS FRACTION 
  */
  MaterialVariableCellReal& m_mass_fraction;
  /*!
  [out] velocity_n
   VELOCITY OLD N 
  */
  VariableNodeReal3& m_velocity_n;
  /*!
  [inout] velocity
   VELOCITY 
  */
  VariableNodeReal3& m_velocity;
};


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace Cas_testRIDER

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // CAS_TEST_RIDER___RIDERSERVICEVARS_H
