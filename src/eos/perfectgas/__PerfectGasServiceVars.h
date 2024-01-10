#ifndef EOS_PERFECTGAS___PERFECTGASSERVICEVARS_H
#define EOS_PERFECTGAS___PERFECTGASSERVICEVARS_H

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
namespace EosPerfectgas {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

//! Classe de variable pour initEOS
struct PerfectGasInitEOSVars final
{
  PerfectGasInitEOSVars(const MaterialVariableCellReal& pressure,
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
struct PerfectGasApplyEOSVars final
{
  PerfectGasApplyEOSVars(const MaterialVariableCellReal& density,
      const MaterialVariableCellReal& internal_energy,
      const Real adiabatic_cst,
      MaterialVariableCellReal& pressure,
      MaterialVariableCellReal& sound_speed,
      MaterialVariableCellReal& dpde)
  : m_density(density)
  , m_internal_energy(internal_energy)
  , m_adiabatic_cst(adiabatic_cst)
  , m_pressure(pressure)
  , m_sound_speed(sound_speed)
  , m_dpde(dpde)
  {}

  /*!
  [in] density
   DENSITY 
  */
  const MaterialVariableCellReal& m_density;
  /*!
  [in] internal_energy
   INTERNAL ENERGY 
  */
  const MaterialVariableCellReal& m_internal_energy;
  /*!
  [in] adiabatic_cst
   Définition de la constante adiabatique 
  */
  const Real m_adiabatic_cst;
  /*!
  [inout] pressure
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
struct PerfectGasApplyOneCellEOSVars final
{
  PerfectGasApplyOneCellEOSVars(const MaterialVariableCellReal& density,
      const MaterialVariableCellReal& internal_energy,
      MaterialVariableCellReal& pressure,
      MaterialVariableCellReal& sound_speed,
      MaterialVariableCellReal& dpde)
  : m_density(density)
  , m_internal_energy(internal_energy)
  , m_pressure(pressure)
  , m_sound_speed(sound_speed)
  , m_dpde(dpde)
  {}

  /*!
  [in] density
   DENSITY 
  */
  const MaterialVariableCellReal& m_density;
  /*!
  [in] internal_energy
   INTERNAL ENERGY 
  */
  const MaterialVariableCellReal& m_internal_energy;
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

}  // namespace EosPerfectgas

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // EOS_PERFECTGAS___PERFECTGASSERVICEVARS_H
