#ifndef CAS_TEST_OTHER___OTHERSERVICEVARS_H
#define CAS_TEST_OTHER___OTHERSERVICEVARS_H

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
namespace Cas_testOTHER {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

//! Classe de variable pour initMatMono
struct OtherInitMatMonoVars final
{
  OtherInitMatMonoVars()
  {}
};

//! Classe de variable pour initVarMono
struct OtherInitVarMonoVars final
{
  OtherInitVarMonoVars()
  {}
};

//! Classe de variable pour initMat
struct OtherInitMatVars final
{
  OtherInitMatVars(const VariableCellReal3& cell_coord,
      VariableCellReal& materiau)
  : m_cell_coord(cell_coord)
  , m_materiau(materiau)
  {}

  /*!
  [in] cell_coord
   CELL COORD 
  */
  const VariableCellReal3& m_cell_coord;
  /*!
  [out] materiau
   Materiau 
  */
  VariableCellReal& m_materiau;
};

//! Classe de variable pour initVar
struct OtherInitVarVars final
{
  OtherInitVarVars(const VariableCellReal3& cell_coord,
      MaterialVariableCellReal& pseudo_viscosity,
      MaterialVariableCellReal& density,
      MaterialVariableCellReal& pressure,
      MaterialVariableCellReal& internal_energy,
      MaterialVariableCellReal& fracvol,
      MaterialVariableCellReal& mass_fraction,
      VariableNodeReal3& velocity_n,
      VariableNodeReal3& velocity)
  : m_cell_coord(cell_coord)
  , m_pseudo_viscosity(pseudo_viscosity)
  , m_density(density)
  , m_pressure(pressure)
  , m_internal_energy(internal_energy)
  , m_fracvol(fracvol)
  , m_mass_fraction(mass_fraction)
  , m_velocity_n(velocity_n)
  , m_velocity(velocity)
  {}

  /*!
  [in] cell_coord
   CELL COORD 
  */
  const VariableCellReal3& m_cell_coord;
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
  [out] internal_energy
   INTERNAL ENERGY 
  */
  MaterialVariableCellReal& m_internal_energy;
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

}  // namespace Cas_testOTHER

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // CAS_TEST_OTHER___OTHERSERVICEVARS_H