#ifndef EOS_STIFFENEDGAS___STIFFENEDGASACCSERVICEVIEWS_H
#define EOS_STIFFENEDGAS___STIFFENEDGASACCSERVICEVIEWS_H

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
#include "accenv/IAccEnv.h"
#include "arcane/accelerator/VariableViews.h"
#include "arcane/accelerator/MaterialVariableViews.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

using namespace Arcane;
using namespace Arcane::Materials;
namespace ax = Arcane::Accelerator;
namespace EosStiffenedgas {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

//! Classe de vues accélérateur pour applyEOSWithSupport
struct StiffenedGasAccApplyEOSWithSupportViews final
{
  StiffenedGasAccApplyEOSWithSupportViews(const ax::MatItemVariableScalarInViewT<Cell,Real>& internal_energy,
      const ax::MatItemVariableScalarInViewT<Cell,Real>& density,
      const Real tension_limit_cst,
      const Real adiabatic_cst,
      const ax::MatItemVariableScalarOutViewT<Cell,ax::DataViewSetter<Real>>& pressure,
      const ax::MatItemVariableScalarOutViewT<Cell,ax::DataViewSetter<Real>>& sound_speed,
      const ax::MatItemVariableScalarOutViewT<Cell,ax::DataViewSetter<Real>>& dpde)
  : in_internal_energy(internal_energy)
  , in_density(density)
  , in_tension_limit_cst(tension_limit_cst)
  , in_adiabatic_cst(adiabatic_cst)
  , out_pressure(pressure)
  , out_sound_speed(sound_speed)
  , out_dpde(dpde)
  {}

  /*!
  [in] internal_energy
   INTERNAL ENERGY 
  */
  const ax::MatItemVariableScalarInViewT<Cell,Real> in_internal_energy;
  /*!
  [in] density
   DENSITY 
  */
  const ax::MatItemVariableScalarInViewT<Cell,Real> in_density;
  /*!
  [in] tension_limit_cst
   Définition de la tension limite 
  */
  const Real in_tension_limit_cst;
  /*!
  [in] adiabatic_cst
   Définition de la constante adiabatique 
  */
  const Real in_adiabatic_cst;
  /*!
  [out] pressure
   PRESSURE 
  */
  const ax::MatItemVariableScalarOutViewT<Cell,ax::DataViewSetter<Real>> out_pressure;
  /*!
  [out] sound_speed
   SOUND SPEED 
  */
  const ax::MatItemVariableScalarOutViewT<Cell,ax::DataViewSetter<Real>> out_sound_speed;
  /*!
  [out] dpde
   DPDE 
  */
  const ax::MatItemVariableScalarOutViewT<Cell,ax::DataViewSetter<Real>> out_dpde;

  ARCCORE_HOST_DEVICE inline void apply(ComponentItemLocalId mvi, CellLocalId cid) const;
};


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace EosStiffenedgas

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // EOS_STIFFENEDGAS___STIFFENEDGASACCSERVICEVIEWS_H
