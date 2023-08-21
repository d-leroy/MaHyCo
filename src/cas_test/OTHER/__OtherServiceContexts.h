#ifndef CAS_TEST_OTHER___OTHERSERVICECONTEXTS_H
#define CAS_TEST_OTHER___OTHERSERVICECONTEXTS_H

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
#include "cas_test/OTHER/__OtherServiceVars.h"
#include "scihook/scihookdefs.h"
#include "SciHook.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_OTHER_DISABLED)

using namespace Arcane;
using namespace Arcane::Materials;
namespace Cas_testOTHER {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

//! Classe de contexte d'exécution pour initMatMono
struct OtherInitMatMonoExecutionContext final : SciHook::SciHookExecutionContext
{
  OtherInitMatMonoExecutionContext(std::string execution_context_name,
      const Integer dim)
  : SciHookExecutionContext(execution_context_name)
  , dim(dim)
  {}

  const Integer dim;

  const pybind11::object get_dim() const {
    return pybind11::cast(dim);
  }
};

//! Classe de contexte d'exécution pour initVarMono
struct OtherInitVarMonoExecutionContext final : SciHook::SciHookExecutionContext
{
  OtherInitVarMonoExecutionContext(std::string execution_context_name,
      const Integer dim)
  : SciHookExecutionContext(execution_context_name)
  , dim(dim)
  {}

  const Integer dim;

  const pybind11::object get_dim() const {
    return pybind11::cast(dim);
  }
};

//! Classe de contexte d'exécution pour initMat
struct OtherInitMatExecutionContext final : SciHook::SciHookExecutionContext
{
  OtherInitMatExecutionContext(std::string execution_context_name,
      OtherInitMatVars *vars,
      const Integer dim)
  : SciHookExecutionContext(execution_context_name)
  , dim(dim)
  , vars(vars)
  {}

  const Integer dim;
  const OtherInitMatVars *vars;

  const pybind11::object get_dim() const {
    return pybind11::cast(dim);
  }

  const pybind11::object get_m_cell_coord() const {
    return pybind11::cast(vars->m_cell_coord);
  }

  const pybind11::object get_m_materiau() const {
    return pybind11::cast(vars->m_materiau);
  }
};

//! Classe de contexte d'exécution pour initVar
struct OtherInitVarExecutionContext final : SciHook::SciHookExecutionContext
{
  OtherInitVarExecutionContext(std::string execution_context_name,
      OtherInitVarVars *vars,
      const Integer dim)
  : SciHookExecutionContext(execution_context_name)
  , dim(dim)
  , vars(vars)
  {}

  const Integer dim;
  const OtherInitVarVars *vars;

  const pybind11::object get_dim() const {
    return pybind11::cast(dim);
  }

  const pybind11::object get_m_cell_coord() const {
    return pybind11::cast(vars->m_cell_coord);
  }

  const pybind11::object get_m_pseudo_viscosity() const {
    return pybind11::cast(vars->m_pseudo_viscosity);
  }

  const pybind11::object get_m_density() const {
    return pybind11::cast(vars->m_density);
  }

  const pybind11::object get_m_pressure() const {
    return pybind11::cast(vars->m_pressure);
  }

  const pybind11::object get_m_internal_energy() const {
    return pybind11::cast(vars->m_internal_energy);
  }

  const pybind11::object get_m_fracvol() const {
    return pybind11::cast(vars->m_fracvol);
  }

  const pybind11::object get_m_mass_fraction() const {
    return pybind11::cast(vars->m_mass_fraction);
  }

  const pybind11::object get_m_velocity_n() const {
    return pybind11::cast(vars->m_velocity_n);
  }

  const pybind11::object get_m_velocity() const {
    return pybind11::cast(vars->m_velocity);
  }
};

}  // namespace Cas_testOTHER

#endif // defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_OTHER_DISABLED)

#endif  // CAS_TEST_OTHER___OTHERSERVICECONTEXTS_H
