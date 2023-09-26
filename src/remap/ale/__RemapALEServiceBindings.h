#ifndef REMAP_ALE___REMAPALESERVICEBINDINGS_H
#define REMAP_ALE___REMAPALESERVICEBINDINGS_H

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
#include "remap/ale/__RemapALEServiceContexts.h"
#include "SciHook.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

using namespace Arcane;
namespace RemapAle {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void bind_remap_ale_remapale(py::module __attribute__((unused)) &m)
{
  #if not defined(SCIHOOK_REMAP_ALE_REMAPALE_DISABLED)
  auto sub_remap_ale_remapale = m.def_submodule("remap_ale_remapale", "Bindings for RemapALE");
  #if not defined(SCIHOOK_REMAP_ALE_REMAPALE_APPLIREMAP_DISABLED)
  pybind11::class_<RemapAle::RemapALEAppliRemapExecutionContext, std::shared_ptr<RemapAle::RemapALEAppliRemapExecutionContext>, SciHook::SciHookExecutionContext>(sub_remap_ale_remapale, "RemapALEAppliRemapExecutionContext")
    .def_property_readonly("dimension", &RemapAle::RemapALEAppliRemapExecutionContext::get_dimension)
    .def_property_readonly("withDualProjection", &RemapAle::RemapALEAppliRemapExecutionContext::get_withDualProjection)
    .def_property_readonly("nb_vars_to_project", &RemapAle::RemapALEAppliRemapExecutionContext::get_nb_vars_to_project)
    .def_property_readonly("nb_env", &RemapAle::RemapALEAppliRemapExecutionContext::get_nb_env)
    .def("__str__", [](RemapAle::RemapALEAppliRemapExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](RemapAle::RemapALEAppliRemapExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_REMAP_ALE_REMAPALE_APPLIREMAP_DISABLED)
  #if not defined(SCIHOOK_REMAP_ALE_REMAPALE_RESIZEREMAPVARIABLES_DISABLED)
  pybind11::class_<RemapAle::RemapALEResizeRemapVariablesExecutionContext, std::shared_ptr<RemapAle::RemapALEResizeRemapVariablesExecutionContext>, SciHook::SciHookExecutionContext>(sub_remap_ale_remapale, "RemapALEResizeRemapVariablesExecutionContext")
    .def_property_readonly("nb_vars_to_project", &RemapAle::RemapALEResizeRemapVariablesExecutionContext::get_nb_vars_to_project)
    .def_property_readonly("nb_env", &RemapAle::RemapALEResizeRemapVariablesExecutionContext::get_nb_env)
    .def("__str__", [](RemapAle::RemapALEResizeRemapVariablesExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](RemapAle::RemapALEResizeRemapVariablesExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_REMAP_ALE_REMAPALE_RESIZEREMAPVARIABLES_DISABLED)
  #if not defined(SCIHOOK_REMAP_ALE_REMAPALE_REMAPVARIABLES_DISABLED)
  pybind11::class_<RemapAle::RemapALERemapVariablesExecutionContext, std::shared_ptr<RemapAle::RemapALERemapVariablesExecutionContext>, SciHook::SciHookExecutionContext>(sub_remap_ale_remapale, "RemapALERemapVariablesExecutionContext")
    .def_property_readonly("dimension", &RemapAle::RemapALERemapVariablesExecutionContext::get_dimension)
    .def_property_readonly("withDualProjection", &RemapAle::RemapALERemapVariablesExecutionContext::get_withDualProjection)
    .def_property_readonly("nb_vars_to_project", &RemapAle::RemapALERemapVariablesExecutionContext::get_nb_vars_to_project)
    .def_property_readonly("nb_env", &RemapAle::RemapALERemapVariablesExecutionContext::get_nb_env)
    .def("__str__", [](RemapAle::RemapALERemapVariablesExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](RemapAle::RemapALERemapVariablesExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_REMAP_ALE_REMAPALE_REMAPVARIABLES_DISABLED)
  #endif // not defined(SCIHOOK_REMAP_ALE_REMAPALE_DISABLED)
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace RemapAle

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // REMAP_ALE___REMAPALESERVICEBINDINGS_H
