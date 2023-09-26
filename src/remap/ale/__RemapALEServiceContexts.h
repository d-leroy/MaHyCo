#ifndef REMAP_ALE___REMAPALESERVICECONTEXTS_H
#define REMAP_ALE___REMAPALESERVICECONTEXTS_H

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#include "arcane/ArcaneTypes.h"
#include "arcane/ItemTypes.h"
#include "arcane/Item.h"
#include "arcane/ItemVector.h"
#include "arcane/ItemVectorView.h"
#include "arcane/VariableTypes.h"
#include "arcane/utils/Array.h"
#include "scihook/scihookdefs.h"
#include "SciHook.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_ALE_DISABLED)

using namespace Arcane;
namespace RemapAle {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

//! Classe de contexte d'exécution pour appliRemap
struct RemapALEAppliRemapExecutionContext final : SciHook::SciHookExecutionContext
{
  RemapALEAppliRemapExecutionContext(std::string execution_context_name,
      const Integer dimension,
      const Integer withDualProjection,
      const Integer nb_vars_to_project,
      const Integer nb_env)
  : SciHookExecutionContext(execution_context_name)
  , dimension(dimension)
  , withDualProjection(withDualProjection)
  , nb_vars_to_project(nb_vars_to_project)
  , nb_env(nb_env)
  {}

  const Integer dimension;
  const Integer withDualProjection;
  const Integer nb_vars_to_project;
  const Integer nb_env;

  const pybind11::object get_dimension() const {
    return pybind11::cast(dimension);
  }

  const pybind11::object get_withDualProjection() const {
    return pybind11::cast(withDualProjection);
  }

  const pybind11::object get_nb_vars_to_project() const {
    return pybind11::cast(nb_vars_to_project);
  }

  const pybind11::object get_nb_env() const {
    return pybind11::cast(nb_env);
  }
};

//! Classe de contexte d'exécution pour resizeRemapVariables
struct RemapALEResizeRemapVariablesExecutionContext final : SciHook::SciHookExecutionContext
{
  RemapALEResizeRemapVariablesExecutionContext(std::string execution_context_name,
      const Integer nb_vars_to_project,
      const Integer nb_env)
  : SciHookExecutionContext(execution_context_name)
  , nb_vars_to_project(nb_vars_to_project)
  , nb_env(nb_env)
  {}

  const Integer nb_vars_to_project;
  const Integer nb_env;

  const pybind11::object get_nb_vars_to_project() const {
    return pybind11::cast(nb_vars_to_project);
  }

  const pybind11::object get_nb_env() const {
    return pybind11::cast(nb_env);
  }
};

//! Classe de contexte d'exécution pour remapVariables
struct RemapALERemapVariablesExecutionContext final : SciHook::SciHookExecutionContext
{
  RemapALERemapVariablesExecutionContext(std::string execution_context_name,
      const Integer dimension,
      const Integer withDualProjection,
      const Integer nb_vars_to_project,
      const Integer nb_env)
  : SciHookExecutionContext(execution_context_name)
  , dimension(dimension)
  , withDualProjection(withDualProjection)
  , nb_vars_to_project(nb_vars_to_project)
  , nb_env(nb_env)
  {}

  const Integer dimension;
  const Integer withDualProjection;
  const Integer nb_vars_to_project;
  const Integer nb_env;

  const pybind11::object get_dimension() const {
    return pybind11::cast(dimension);
  }

  const pybind11::object get_withDualProjection() const {
    return pybind11::cast(withDualProjection);
  }

  const pybind11::object get_nb_vars_to_project() const {
    return pybind11::cast(nb_vars_to_project);
  }

  const pybind11::object get_nb_env() const {
    return pybind11::cast(nb_env);
  }
};

}  // namespace RemapAle

#endif // defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_ALE_DISABLED)

#endif  // REMAP_ALE___REMAPALESERVICECONTEXTS_H
