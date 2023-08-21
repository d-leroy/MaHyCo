#ifndef CAS_TEST_RIDER___RIDERSERVICECONTEXTS_H
#define CAS_TEST_RIDER___RIDERSERVICECONTEXTS_H

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
#include "cas_test/RIDER/__RiderServiceVars.h"
#include "scihook/scihookdefs.h"
#include "SciHook.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_RIDER_DISABLED)

using namespace Arcane;
using namespace Arcane::Materials;
namespace Cas_testRIDER {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

//! Classe de contexte d'exécution pour initMatMono
struct RiderInitMatMonoExecutionContext final : SciHook::SciHookExecutionContext
{
  RiderInitMatMonoExecutionContext(std::string execution_context_name,
      RiderInitMatMonoVars *vars,
      const Integer dim)
  : SciHookExecutionContext(execution_context_name)
  , dim(dim)
  , vars(vars)
  {}

  const Integer dim;
  const RiderInitMatMonoVars *vars;

  const pybind11::object get_dim() const {
    return pybind11::cast(dim);
  }

  const pybind11::object get_m_materiau() const {
    return pybind11::cast(vars->m_materiau);
  }
};

//! Classe de contexte d'exécution pour initVarMono
struct RiderInitVarMonoExecutionContext final : SciHook::SciHookExecutionContext
{
  RiderInitVarMonoExecutionContext(std::string execution_context_name,
      RiderInitVarMonoVars *vars,
      const Integer dim)
  : SciHookExecutionContext(execution_context_name)
  , dim(dim)
  , vars(vars)
  {}

  const Integer dim;
  const RiderInitVarMonoVars *vars;

  const pybind11::object get_dim() const {
    return pybind11::cast(dim);
  }

  const pybind11::object get_m_node_coord() const {
    return pybind11::cast(vars->m_node_coord);
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

//! Classe de contexte d'exécution pour initMat
struct RiderInitMatExecutionContext final : SciHook::SciHookExecutionContext
{
  RiderInitMatExecutionContext(std::string execution_context_name,
      RiderInitMatVars *vars,
      const Integer dim)
  : SciHookExecutionContext(execution_context_name)
  , dim(dim)
  , vars(vars)
  {}

  const Integer dim;
  const RiderInitMatVars *vars;

  const pybind11::object get_dim() const {
    return pybind11::cast(dim);
  }

  const pybind11::object get_m_node_coord() const {
    return pybind11::cast(vars->m_node_coord);
  }

  const pybind11::object get_m_materiau() const {
    return pybind11::cast(vars->m_materiau);
  }
};

//! Classe de contexte d'exécution pour initVar
struct RiderInitVarExecutionContext final : SciHook::SciHookExecutionContext
{
  RiderInitVarExecutionContext(std::string execution_context_name,
      RiderInitVarVars *vars,
      const Integer dim)
  : SciHookExecutionContext(execution_context_name)
  , dim(dim)
  , vars(vars)
  {}

  const Integer dim;
  const RiderInitVarVars *vars;

  const pybind11::object get_dim() const {
    return pybind11::cast(dim);
  }

  const pybind11::object get_m_node_coord() const {
    return pybind11::cast(vars->m_node_coord);
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

}  // namespace Cas_testRIDER

#endif // defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_RIDER_DISABLED)

#endif  // CAS_TEST_RIDER___RIDERSERVICECONTEXTS_H
