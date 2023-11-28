#ifndef EOS_STIFFENEDGAS___STIFFENEDGASSERVICECONTEXTS_H
#define EOS_STIFFENEDGAS___STIFFENEDGASSERVICECONTEXTS_H

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
#include "eos/stiffenedgas/__StiffenedGasServiceVars.h"
#include "arcane/materials/IMeshEnvironment.h"
#include "scihook/scihookdefs.h"
#include "SciHook.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_EOS_STIFFENEDGAS_DISABLED)

using namespace Arcane;
using namespace Arcane::Materials;
namespace EosStiffenedgas {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

//! Classe de contexte d'exécution pour initEOS
struct StiffenedGasInitEOSExecutionContext final : SciHook::SciHookExecutionContext
{
  StiffenedGasInitEOSExecutionContext(std::string execution_context_name,
      StiffenedGasInitEOSVars *vars,
      ::Arcane::Materials::IMeshEnvironment* env)
  : SciHookExecutionContext(execution_context_name)
  , env(env)
  , vars(vars)
  {}

  ::Arcane::Materials::IMeshEnvironment* env;
  const StiffenedGasInitEOSVars *vars;

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
struct StiffenedGasApplyEOSExecutionContext final : SciHook::SciHookExecutionContext
{
  StiffenedGasApplyEOSExecutionContext(std::string execution_context_name,
      StiffenedGasApplyEOSVars *vars,
      ::Arcane::Materials::IMeshEnvironment* env)
  : SciHookExecutionContext(execution_context_name)
  , env(env)
  , vars(vars)
  {}

  ::Arcane::Materials::IMeshEnvironment* env;
  const StiffenedGasApplyEOSVars *vars;

  const pybind11::object get_env() const {
    return pybind11::cast(env);
  }

  const pybind11::object get_internal_energy() const {
    return pybind11::cast(vars->m_internal_energy);
  }

  const pybind11::object get_density() const {
    return pybind11::cast(vars->m_density);
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
struct StiffenedGasApplyOneCellEOSExecutionContext final : SciHook::SciHookExecutionContext
{
  StiffenedGasApplyOneCellEOSExecutionContext(std::string execution_context_name,
      StiffenedGasApplyOneCellEOSVars *vars,
      const ::Arcane::Materials::IMeshEnvironment* env,
      const EnvCell ev)
  : SciHookExecutionContext(execution_context_name)
  , env(env)
  , ev(ev)
  , vars(vars)
  {}

  const ::Arcane::Materials::IMeshEnvironment* env;
  const EnvCell ev;
  const StiffenedGasApplyOneCellEOSVars *vars;

  const pybind11::object get_env() const {
    return pybind11::cast(env);
  }

  const pybind11::object get_ev() const {
    return pybind11::cast(ev);
  }

  const pybind11::object get_internal_energy() const {
    return pybind11::cast(vars->m_internal_energy);
  }

  const pybind11::object get_density() const {
    return pybind11::cast(vars->m_density);
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

}  // namespace EosStiffenedgas

#endif // defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_EOS_STIFFENEDGAS_DISABLED)

#endif  // EOS_STIFFENEDGAS___STIFFENEDGASSERVICECONTEXTS_H
