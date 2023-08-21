#ifndef CAS_TEST_SEDOV___SEDOVSERVICEVARS_H
#define CAS_TEST_SEDOV___SEDOVSERVICEVARS_H

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
namespace Cas_testSEDOV {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

//! Classe de variable pour initMatMono
struct SedovInitMatMonoVars final
{
  explicit SedovInitMatMonoVars(VariableCellReal& materiau)
  : m_materiau(materiau)
  {}

  /*!
  [out] materiau
   Materiau 
  */
  VariableCellReal& m_materiau;
};

//! Classe de variable pour initVarMono
struct SedovInitVarMonoVars final
{
  SedovInitVarMonoVars(const VariableNodeReal3& node_coord,
      const MaterialVariableCellReal& cell_volume,
      MaterialVariableCellReal& density,
      MaterialVariableCellReal& pressure,
      MaterialVariableCellReal& fracvol,
      MaterialVariableCellReal& mass_fraction,
      VariableNodeReal3& velocity,
      MaterialVariableCellReal& internal_energy)
  : m_node_coord(node_coord)
  , m_cell_volume(cell_volume)
  , m_density(density)
  , m_pressure(pressure)
  , m_fracvol(fracvol)
  , m_mass_fraction(mass_fraction)
  , m_velocity(velocity)
  , m_internal_energy(internal_energy)
  {}

  /*!
  [in] node_coord
   NODE COORD 
  */
  const VariableNodeReal3& m_node_coord;
  /*!
  [in] cell_volume
   CELL VOLUME 
  */
  const MaterialVariableCellReal& m_cell_volume;
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
  [out] velocity
   VELOCITY 
  */
  VariableNodeReal3& m_velocity;
  /*!
  [inout] internal_energy
   INTERNAL ENERGY 
  */
  MaterialVariableCellReal& m_internal_energy;
};

//! Classe de variable pour initMat
struct SedovInitMatVars final
{
  SedovInitMatVars(const VariableNodeReal3& node_coord,
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
struct SedovInitVarVars final
{
  SedovInitVarVars(const VariableNodeReal3& node_coord,
      const MaterialVariableCellReal& cell_volume,
      MaterialVariableCellReal& density,
      MaterialVariableCellReal& pressure,
      MaterialVariableCellReal& fracvol,
      MaterialVariableCellReal& mass_fraction,
      VariableNodeReal3& velocity,
      MaterialVariableCellReal& internal_energy)
  : m_node_coord(node_coord)
  , m_cell_volume(cell_volume)
  , m_density(density)
  , m_pressure(pressure)
  , m_fracvol(fracvol)
  , m_mass_fraction(mass_fraction)
  , m_velocity(velocity)
  , m_internal_energy(internal_energy)
  {}

  /*!
  [in] node_coord
   NODE COORD 
  */
  const VariableNodeReal3& m_node_coord;
  /*!
  [in] cell_volume
   CELL VOLUME 
  */
  const MaterialVariableCellReal& m_cell_volume;
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
  [out] velocity
   VELOCITY 
  */
  VariableNodeReal3& m_velocity;
  /*!
  [inout] internal_energy
   INTERNAL ENERGY 
  */
  MaterialVariableCellReal& m_internal_energy;
};


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace Cas_testSEDOV

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // CAS_TEST_SEDOV___SEDOVSERVICEVARS_H
