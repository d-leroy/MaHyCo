#ifndef EOS_STIFFENEDGAS___STIFFENEDGASSERVICEVIEWS_H
#define EOS_STIFFENEDGAS___STIFFENEDGASSERVICEVIEWS_H

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

//! Classe de vues accélérateur pour applyEOS
struct StiffenedGasApplyEOSViews final
{
  StiffenedGasApplyEOSViews(const ax::MatItemVariableScalarInViewT<Cell,Real>& internal_energy,
      const ax::ItemVariableScalarInViewT<Cell,Real>& internal_energy_g,
      const ax::MatItemVariableScalarInViewT<Cell,Real>& density,
      const ax::ItemVariableScalarInViewT<Cell,Real>& density_g,
      const Real tension_limit_cst,
      const Real adiabatic_cst,
      const ax::MatItemVariableScalarOutViewT<Cell,ax::DataViewSetter<Real>>& pressure,
      const ax::ItemVariableScalarOutViewT<Cell,ax::DataViewSetter<Real>>& pressure_g,
      const ax::MatItemVariableScalarOutViewT<Cell,ax::DataViewSetter<Real>>& sound_speed,
      const ax::ItemVariableScalarOutViewT<Cell,ax::DataViewSetter<Real>>& sound_speed_g,
      const ax::MatItemVariableScalarOutViewT<Cell,ax::DataViewSetter<Real>>& dpde,
      const ax::ItemVariableScalarOutViewT<Cell,ax::DataViewSetter<Real>>& dpde_g)
  : in_internal_energy(internal_energy)
  , in_internal_energy_g(internal_energy_g)
  , in_density(density)
  , in_density_g(density_g)
  , in_tension_limit_cst(tension_limit_cst)
  , in_adiabatic_cst(adiabatic_cst)
  , out_pressure(pressure)
  , out_pressure_g(pressure_g)
  , out_sound_speed(sound_speed)
  , out_sound_speed_g(sound_speed_g)
  , out_dpde(dpde)
  , out_dpde_g(dpde_g)
  {}

  /*!
  [in] internal_energy
   INTERNAL ENERGY 
  */
  const ax::MatItemVariableScalarInViewT<Cell,Real> in_internal_energy;
  const ax::ItemVariableScalarInViewT<Cell,Real> in_internal_energy_g;
  /*!
  [in] density
   DENSITY 
  */
  const ax::MatItemVariableScalarInViewT<Cell,Real> in_density;
  const ax::ItemVariableScalarInViewT<Cell,Real> in_density_g;
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
  const ax::ItemVariableScalarOutViewT<Cell,ax::DataViewSetter<Real>> out_pressure_g;
  /*!
  [out] sound_speed
   SOUND SPEED 
  */
  const ax::MatItemVariableScalarOutViewT<Cell,ax::DataViewSetter<Real>> out_sound_speed;
  const ax::ItemVariableScalarOutViewT<Cell,ax::DataViewSetter<Real>> out_sound_speed_g;
  /*!
  [out] dpde
   DPDE 
  */
  const ax::MatItemVariableScalarOutViewT<Cell,ax::DataViewSetter<Real>> out_dpde;
  const ax::ItemVariableScalarOutViewT<Cell,ax::DataViewSetter<Real>> out_dpde_g;

  ARCCORE_HOST_DEVICE inline void apply(ComponentItemLocalId iid) const;
};


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace EosStiffenedgas

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // EOS_STIFFENEDGAS___STIFFENEDGASSERVICEVIEWS_H
