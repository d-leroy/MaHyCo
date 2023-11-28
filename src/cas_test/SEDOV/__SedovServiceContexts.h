#ifndef CAS_TEST_SEDOV___SEDOVSERVICECONTEXTS_H
#define CAS_TEST_SEDOV___SEDOVSERVICECONTEXTS_H

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
#include "cas_test/SEDOV/__SedovServiceVars.h"
#include "scihook/scihookdefs.h"
#include "SciHook.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_SEDOV_DISABLED)

using namespace Arcane;
using namespace Arcane::Materials;
namespace Cas_testSEDOV {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

//! Classe de contexte d'exécution pour initMatMono
struct SedovInitMatMonoExecutionContext final : SciHook::SciHookExecutionContext
{
  SedovInitMatMonoExecutionContext(std::string execution_context_name,
      SedovInitMatMonoVars *vars,
      const Integer dim)
  : SciHookExecutionContext(execution_context_name)
  , dim(dim)
  , vars(vars)
  {}

  const Integer dim;
  const SedovInitMatMonoVars *vars;

  const pybind11::object get_dim() const {
    return pybind11::cast(dim);
  }

  const pybind11::object get_materiau() const {
    return pybind11::cast(vars->m_materiau);
  }
};

//! Classe de contexte d'exécution pour initVarMono
struct SedovInitVarMonoExecutionContext final : SciHook::SciHookExecutionContext
{
  SedovInitVarMonoExecutionContext(std::string execution_context_name,
      SedovInitVarMonoVars *vars,
      const Integer dim)
  : SciHookExecutionContext(execution_context_name)
  , dim(dim)
  , vars(vars)
  {}

  const Integer dim;
  const SedovInitVarMonoVars *vars;

  const pybind11::object get_dim() const {
    return pybind11::cast(dim);
  }

  const pybind11::object get_node_coord() const {
    return pybind11::cast(vars->m_node_coord);
  }

  const pybind11::object get_cell_volume() const {
    return pybind11::cast(vars->m_cell_volume);
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

  const pybind11::object get_internal_energy() const {
    return pybind11::cast(vars->m_internal_energy);
  }
};

//! Classe de contexte d'exécution pour initMat
struct SedovInitMatExecutionContext final : SciHook::SciHookExecutionContext
{
  SedovInitMatExecutionContext(std::string execution_context_name,
      SedovInitMatVars *vars,
      const Integer dim)
  : SciHookExecutionContext(execution_context_name)
  , dim(dim)
  , vars(vars)
  {}

  const Integer dim;
  const SedovInitMatVars *vars;

  const pybind11::object get_dim() const {
    return pybind11::cast(dim);
  }

  const pybind11::object get_node_coord() const {
    return pybind11::cast(vars->m_node_coord);
  }

  const pybind11::object get_materiau() const {
    return pybind11::cast(vars->m_materiau);
  }
};

//! Classe de contexte d'exécution pour initVar
struct SedovInitVarExecutionContext final : SciHook::SciHookExecutionContext
{
  SedovInitVarExecutionContext(std::string execution_context_name,
      SedovInitVarVars *vars,
      const Integer dim)
  : SciHookExecutionContext(execution_context_name)
  , dim(dim)
  , vars(vars)
  {}

  const Integer dim;
  const SedovInitVarVars *vars;

  const pybind11::object get_dim() const {
    return pybind11::cast(dim);
  }

  const pybind11::object get_node_coord() const {
    return pybind11::cast(vars->m_node_coord);
  }

  const pybind11::object get_cell_volume() const {
    return pybind11::cast(vars->m_cell_volume);
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

  const pybind11::object get_internal_energy() const {
    return pybind11::cast(vars->m_internal_energy);
  }
};

}  // namespace Cas_testSEDOV

#endif // defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_SEDOV_DISABLED)

#endif  // CAS_TEST_SEDOV___SEDOVSERVICECONTEXTS_H
