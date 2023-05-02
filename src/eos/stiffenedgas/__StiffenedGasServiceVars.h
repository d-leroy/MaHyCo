#ifndef EOS_STIFFENEDGAS___STIFFENEDGASSERVICEVARS_H
#define EOS_STIFFENEDGAS___STIFFENEDGASSERVICEVARS_H

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
namespace EosStiffenedgas {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

//! Classe de variable pour initEOS
struct StiffenedGasInitEOSVars final
{
  StiffenedGasInitEOSVars(const MaterialVariableCellReal& pressure,
      const MaterialVariableCellReal& density,
      MaterialVariableCellReal& internal_energy,
      MaterialVariableCellReal& sound_speed)
  : m_pressure(pressure)
  , m_density(density)
  , m_internal_energy(internal_energy)
  , m_sound_speed(sound_speed)
  {}

  /*!
  [in] pressure
   PRESSURE 
  */
  const MaterialVariableCellReal& m_pressure;
  /*!
  [in] density
   DENSITY 
  */
  const MaterialVariableCellReal& m_density;
  /*!
  [out] internal_energy
   INTERNAL ENERGY 
  */
  MaterialVariableCellReal& m_internal_energy;
  /*!
  [out] sound_speed
   SOUND SPEED 
  */
  MaterialVariableCellReal& m_sound_speed;
};

//! Classe de variable pour applyEOS
struct StiffenedGasApplyEOSVars final
{
  StiffenedGasApplyEOSVars(const MaterialVariableCellReal& internal_energy,
      const MaterialVariableCellReal& density,
      MaterialVariableCellReal& pressure,
      MaterialVariableCellReal& sound_speed,
      MaterialVariableCellReal& dpde)
  : m_internal_energy(internal_energy)
  , m_density(density)
  , m_pressure(pressure)
  , m_sound_speed(sound_speed)
  , m_dpde(dpde)
  {}

  /*!
  [in] internal_energy
   INTERNAL ENERGY 
  */
  const MaterialVariableCellReal& m_internal_energy;
  /*!
  [in] density
   DENSITY 
  */
  const MaterialVariableCellReal& m_density;
  /*!
  [out] pressure
   PRESSURE 
  */
  MaterialVariableCellReal& m_pressure;
  /*!
  [out] sound_speed
   SOUND SPEED 
  */
  MaterialVariableCellReal& m_sound_speed;
  /*!
  [out] dpde
   DPDE 
  */
  MaterialVariableCellReal& m_dpde;
};

//! Classe de variable pour applyOneCellEOS
struct StiffenedGasApplyOneCellEOSVars final
{
  StiffenedGasApplyOneCellEOSVars(const MaterialVariableCellReal& internal_energy,
      const MaterialVariableCellReal& density,
      MaterialVariableCellReal& pressure,
      MaterialVariableCellReal& sound_speed,
      MaterialVariableCellReal& dpde)
  : m_internal_energy(internal_energy)
  , m_density(density)
  , m_pressure(pressure)
  , m_sound_speed(sound_speed)
  , m_dpde(dpde)
  {}

  /*!
  [in] internal_energy
   INTERNAL ENERGY 
  */
  const MaterialVariableCellReal& m_internal_energy;
  /*!
  [in] density
   DENSITY 
  */
  const MaterialVariableCellReal& m_density;
  /*!
  [out] pressure
   PRESSURE 
  */
  MaterialVariableCellReal& m_pressure;
  /*!
  [out] sound_speed
   SOUND SPEED 
  */
  MaterialVariableCellReal& m_sound_speed;
  /*!
  [out] dpde
   DPDE 
  */
  MaterialVariableCellReal& m_dpde;
};


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace EosStiffenedgas

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // EOS_STIFFENEDGAS___STIFFENEDGASSERVICEVARS_H
