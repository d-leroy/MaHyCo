#ifndef EOS_STIFFENEDGAS___STIFFENEDGASACCSERVICECONTEXTS_H
#define EOS_STIFFENEDGAS___STIFFENEDGASACCSERVICECONTEXTS_H

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
#include "eos/stiffenedgas/__StiffenedGasAccServiceVars.h"
#include "eos/stiffenedgas/__StiffenedGasAccServiceViews.h"
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

//! Classe de contexte d'exécution pour applyEOSWithSupport
struct StiffenedGasAccApplyEOSWithSupportExecutionContext final : SciHook::SciHookExecutionContext
{
  StiffenedGasAccApplyEOSWithSupportExecutionContext(std::string execution_context_name,
      StiffenedGasAccApplyEOSWithSupportViews *views)
  : SciHookExecutionContext(execution_context_name)
  , views(views)
  {}

  const StiffenedGasAccApplyEOSWithSupportViews *views;

  const pybind11::object get_internal_energy() const {
    return pybind11::cast(views->in_internal_energy_g);
  }

  const pybind11::object get_density() const {
    return pybind11::cast(views->in_density_g);
  }

  const pybind11::object get_tension_limit_cst() const {
    return pybind11::cast(views->in_tension_limit_cst);
  }

  const pybind11::object get_adiabatic_cst() const {
    return pybind11::cast(views->in_adiabatic_cst);
  }

  const pybind11::object get_pressure() const {
    return pybind11::cast(views->out_pressure_g);
  }

  const pybind11::object get_sound_speed() const {
    return pybind11::cast(views->out_sound_speed_g);
  }

  const pybind11::object get_dpde() const {
    return pybind11::cast(views->out_dpde_g);
  }
};

//! Classe de contexte d'exécution pour initEOS
struct StiffenedGasAccInitEOSExecutionContext final : SciHook::SciHookExecutionContext
{
  StiffenedGasAccInitEOSExecutionContext(std::string execution_context_name,
      StiffenedGasAccInitEOSVars *vars,
      ::Arcane::Materials::IMeshEnvironment* env)
  : SciHookExecutionContext(execution_context_name)
  , env(env)
  , vars(vars)
  {}

  ::Arcane::Materials::IMeshEnvironment* env;
  const StiffenedGasAccInitEOSVars *vars;

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
struct StiffenedGasAccApplyEOSExecutionContext final : SciHook::SciHookExecutionContext
{
  StiffenedGasAccApplyEOSExecutionContext(std::string execution_context_name,
      ::Arcane::Materials::IMeshEnvironment* env)
  : SciHookExecutionContext(execution_context_name)
  , env(env)
  {}

  ::Arcane::Materials::IMeshEnvironment* env;

  const pybind11::object get_env() const {
    return pybind11::cast(env);
  }
};

//! Classe de contexte d'exécution pour applyOneCellEOS
struct StiffenedGasAccApplyOneCellEOSExecutionContext final : SciHook::SciHookExecutionContext
{
  StiffenedGasAccApplyOneCellEOSExecutionContext(std::string execution_context_name,
      StiffenedGasAccApplyOneCellEOSVars *vars,
      const ::Arcane::Materials::IMeshEnvironment* env,
      const EnvCell ev)
  : SciHookExecutionContext(execution_context_name)
  , env(env)
  , ev(ev)
  , vars(vars)
  {}

  const ::Arcane::Materials::IMeshEnvironment* env;
  const EnvCell ev;
  const StiffenedGasAccApplyOneCellEOSVars *vars;

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

#endif  // EOS_STIFFENEDGAS___STIFFENEDGASACCSERVICECONTEXTS_H
