#ifndef EOS_PERFECTGAS___PERFECTGASPACCSERVICECONTEXTS_H
#define EOS_PERFECTGAS___PERFECTGASPACCSERVICECONTEXTS_H

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
#include "eos/perfectgas/__PerfectGasPAccServiceVars.h"
#include "arcane/materials/IMeshEnvironment.h"
#include "scihook/scihookdefs.h"
#include "SciHook.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_EOS_PERFECTGAS_DISABLED)

using namespace Arcane;
using namespace Arcane::Materials;
namespace EosPerfectgas {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

//! Classe de contexte d'exécution pour initEOS
struct PerfectGasPAccInitEOSExecutionContext final : SciHook::SciHookExecutionContext
{
  PerfectGasPAccInitEOSExecutionContext(std::string execution_context_name,
      PerfectGasPAccInitEOSVars *vars,
      ::Arcane::Materials::IMeshEnvironment* env)
  : SciHookExecutionContext(execution_context_name)
  , env(env)
  , vars(vars)
  {}

  ::Arcane::Materials::IMeshEnvironment* env;
  const PerfectGasPAccInitEOSVars *vars;

  const pybind11::object get_env() const {
    return pybind11::cast(env);
  }

  const pybind11::object get_pressure() const {
    return pybind11::cast(vars->m_pressure);
  }

  const pybind11::object get_density() const {
    return pybind11::cast(vars->m_density);
  }

  const pybind11::object get_internal_energy() const {
    return pybind11::cast(vars->m_internal_energy);
  }

  const pybind11::object get_sound_speed() const {
    return pybind11::cast(vars->m_sound_speed);
  }
};

//! Classe de contexte d'exécution pour applyEOS
struct PerfectGasPAccApplyEOSExecutionContext final : SciHook::SciHookExecutionContext
{
  PerfectGasPAccApplyEOSExecutionContext(std::string execution_context_name,
      PerfectGasPAccApplyEOSVars *vars,
      ::Arcane::Materials::IMeshEnvironment* env)
  : SciHookExecutionContext(execution_context_name)
  , env(env)
  , vars(vars)
  {}

  ::Arcane::Materials::IMeshEnvironment* env;
  const PerfectGasPAccApplyEOSVars *vars;

  const pybind11::object get_env() const {
    return pybind11::cast(env);
  }

  const pybind11::object get_density() const {
    return pybind11::cast(vars->m_density);
  }

  const pybind11::object get_internal_energy() const {
    return pybind11::cast(vars->m_internal_energy);
  }

  const pybind11::object get_pressure() const {
    return pybind11::cast(vars->m_pressure);
  }

  const pybind11::object get_sound_speed() const {
    return pybind11::cast(vars->m_sound_speed);
  }

  const pybind11::object get_dpde() const {
    return pybind11::cast(vars->m_dpde);
  }
};

//! Classe de contexte d'exécution pour applyOneCellEOS
struct PerfectGasPAccApplyOneCellEOSExecutionContext final : SciHook::SciHookExecutionContext
{
  PerfectGasPAccApplyOneCellEOSExecutionContext(std::string execution_context_name,
      PerfectGasPAccApplyOneCellEOSVars *vars,
      const ::Arcane::Materials::IMeshEnvironment* env,
      const EnvCell ev)
  : SciHookExecutionContext(execution_context_name)
  , env(env)
  , ev(ev)
  , vars(vars)
  {}

  const ::Arcane::Materials::IMeshEnvironment* env;
  const EnvCell ev;
  const PerfectGasPAccApplyOneCellEOSVars *vars;

  const pybind11::object get_env() const {
    return pybind11::cast(env);
  }

  const pybind11::object get_ev() const {
    return pybind11::cast(ev);
  }

  const pybind11::object get_density() const {
    return pybind11::cast(vars->m_density);
  }

  const pybind11::object get_internal_energy() const {
    return pybind11::cast(vars->m_internal_energy);
  }

  const pybind11::object get_pressure() const {
    return pybind11::cast(vars->m_pressure);
  }

  const pybind11::object get_sound_speed() const {
    return pybind11::cast(vars->m_sound_speed);
  }

  const pybind11::object get_dpde() const {
    return pybind11::cast(vars->m_dpde);
  }
};

}  // namespace EosPerfectgas

#endif // defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_EOS_PERFECTGAS_DISABLED)

#endif  // EOS_PERFECTGAS___PERFECTGASPACCSERVICECONTEXTS_H
