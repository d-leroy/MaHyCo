#ifndef CAS_TEST_SOD___SODSERVICECONTEXTS_H
#define CAS_TEST_SOD___SODSERVICECONTEXTS_H

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
#include "cas_test/SOD/__SodServiceVars.h"
#include "scihook/scihookdefs.h"
#include "SciHook.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_SOD_DISABLED)

using namespace Arcane;
using namespace Arcane::Materials;
namespace Cas_testSOD {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

//! Classe de contexte d'exécution pour initMatMono
struct SodInitMatMonoExecutionContext final : SciHook::SciHookExecutionContext
{
  SodInitMatMonoExecutionContext(std::string execution_context_name,
      SodInitMatMonoVars *vars,
      const Integer dim)
  : SciHookExecutionContext(execution_context_name)
  , dim(dim)
  , vars(vars)
  {}

  const Integer dim;
  const SodInitMatMonoVars *vars;

  const pybind11::object get_dim() const {
    return pybind11::cast(dim);
  }

  const pybind11::object get_materiau() const {
    return pybind11::cast(vars->m_materiau);
  }
};

//! Classe de contexte d'exécution pour initVarMono
struct SodInitVarMonoExecutionContext final : SciHook::SciHookExecutionContext
{
  SodInitVarMonoExecutionContext(std::string execution_context_name,
      SodInitVarMonoVars *vars,
      const Integer dim)
  : SciHookExecutionContext(execution_context_name)
  , dim(dim)
  , vars(vars)
  {}

  const Integer dim;
  const SodInitVarMonoVars *vars;

  const pybind11::object get_dim() const {
    return pybind11::cast(dim);
  }

  const pybind11::object get_cell_coord() const {
    return pybind11::cast(vars->m_cell_coord);
  }

  const pybind11::object get_density() const {
    return pybind11::cast(vars->m_density);
  }

  const pybind11::object get_pressure() const {
    return pybind11::cast(vars->m_pressure);
  }

  const pybind11::object get_fracvol() const {
    return pybind11::cast(vars->m_fracvol);
  }

  const pybind11::object get_mass_fraction() const {
    return pybind11::cast(vars->m_mass_fraction);
  }

  const pybind11::object get_velocity() const {
    return pybind11::cast(vars->m_velocity);
  }
};

//! Classe de contexte d'exécution pour initMat
struct SodInitMatExecutionContext final : SciHook::SciHookExecutionContext
{
  SodInitMatExecutionContext(std::string execution_context_name,
      SodInitMatVars *vars,
      const Integer dim)
  : SciHookExecutionContext(execution_context_name)
  , dim(dim)
  , vars(vars)
  {}

  const Integer dim;
  const SodInitMatVars *vars;

  const pybind11::object get_dim() const {
    return pybind11::cast(dim);
  }

  const pybind11::object get_cell_coord() const {
    return pybind11::cast(vars->m_cell_coord);
  }

  const pybind11::object get_materiau() const {
    return pybind11::cast(vars->m_materiau);
  }
};

//! Classe de contexte d'exécution pour initVar
struct SodInitVarExecutionContext final : SciHook::SciHookExecutionContext
{
  SodInitVarExecutionContext(std::string execution_context_name,
      SodInitVarVars *vars,
      const Integer dim)
  : SciHookExecutionContext(execution_context_name)
  , dim(dim)
  , vars(vars)
  {}

  const Integer dim;
  const SodInitVarVars *vars;

  const pybind11::object get_dim() const {
    return pybind11::cast(dim);
  }

  const pybind11::object get_cell_coord() const {
    return pybind11::cast(vars->m_cell_coord);
  }

  const pybind11::object get_density() const {
    return pybind11::cast(vars->m_density);
  }

  const pybind11::object get_pressure() const {
    return pybind11::cast(vars->m_pressure);
  }

  const pybind11::object get_fracvol() const {
    return pybind11::cast(vars->m_fracvol);
  }

  const pybind11::object get_mass_fraction() const {
    return pybind11::cast(vars->m_mass_fraction);
  }

  const pybind11::object get_velocity() const {
    return pybind11::cast(vars->m_velocity);
  }
};

}  // namespace Cas_testSOD

#endif // defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_SOD_DISABLED)

#endif  // CAS_TEST_SOD___SODSERVICECONTEXTS_H
