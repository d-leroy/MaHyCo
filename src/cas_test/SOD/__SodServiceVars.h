#ifndef CAS_TEST_SOD___SODSERVICEVARS_H
#define CAS_TEST_SOD___SODSERVICEVARS_H

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
namespace Cas_testSOD {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

//! Classe de variable pour initMatMono
struct SodInitMatMonoVars final
{
  explicit SodInitMatMonoVars(VariableCellReal& materiau)
  : m_materiau(materiau)
  {}

  /*!
  [out] materiau
   Materiau 
  */
  VariableCellReal& m_materiau;
};

//! Classe de variable pour initVarMono
struct SodInitVarMonoVars final
{
  SodInitVarMonoVars(const VariableCellReal3& cell_coord,
      MaterialVariableCellReal& density,
      MaterialVariableCellReal& pressure,
      MaterialVariableCellReal& fracvol,
      MaterialVariableCellReal& mass_fraction,
      VariableNodeReal3& velocity)
  : m_cell_coord(cell_coord)
  , m_density(density)
  , m_pressure(pressure)
  , m_fracvol(fracvol)
  , m_mass_fraction(mass_fraction)
  , m_velocity(velocity)
  {}

  /*!
  [in] cell_coord
   CELL COORD 
  */
  const VariableCellReal3& m_cell_coord;
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
  [inout] velocity
   VELOCITY 
  */
  VariableNodeReal3& m_velocity;
};

//! Classe de variable pour initMat
struct SodInitMatVars final
{
  SodInitMatVars(const VariableCellReal3& cell_coord,
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
struct SodInitVarVars final
{
  SodInitVarVars(const VariableCellReal3& cell_coord,
      MaterialVariableCellReal& density,
      MaterialVariableCellReal& pressure,
      MaterialVariableCellReal& fracvol,
      MaterialVariableCellReal& mass_fraction,
      VariableNodeReal3& velocity)
  : m_cell_coord(cell_coord)
  , m_density(density)
  , m_pressure(pressure)
  , m_fracvol(fracvol)
  , m_mass_fraction(mass_fraction)
  , m_velocity(velocity)
  {}

  /*!
  [in] cell_coord
   CELL COORD 
  */
  const VariableCellReal3& m_cell_coord;
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
  [inout] velocity
   VELOCITY 
  */
  VariableNodeReal3& m_velocity;
};


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace Cas_testSOD

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // CAS_TEST_SOD___SODSERVICEVARS_H
