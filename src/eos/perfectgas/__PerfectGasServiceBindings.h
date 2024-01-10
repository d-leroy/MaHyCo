#ifndef EOS_PERFECTGAS___PERFECTGASSERVICEBINDINGS_H
#define EOS_PERFECTGAS___PERFECTGASSERVICEBINDINGS_H

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
#include "scihook/scihookdefs.h"
#include "eos/perfectgas/__PerfectGasServiceContexts.h"
#include "SciHook.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

using namespace Arcane;
using namespace Arcane::Materials;
namespace EosPerfectgas {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void bind_eos_perfectgas_perfectgas(py::module __attribute__((unused)) &m)
{
  #if not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGAS_DISABLED)
  auto sub_eos_perfectgas_perfectgas = m.def_submodule("eos_perfectgas_perfectgas", "Bindings for PerfectGas");
  #if not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGAS_INITEOS_DISABLED)
  pybind11::class_<EosPerfectgas::PerfectGasInitEOSExecutionContext, std::shared_ptr<EosPerfectgas::PerfectGasInitEOSExecutionContext>, SciHook::SciHookExecutionContext>(sub_eos_perfectgas_perfectgas, "PerfectGasInitEOSExecutionContext")
    .def_property_readonly("env", &EosPerfectgas::PerfectGasInitEOSExecutionContext::get_env)
    .def_property_readonly("pressure", &EosPerfectgas::PerfectGasInitEOSExecutionContext::get_pressure)
    .def_property_readonly("density", &EosPerfectgas::PerfectGasInitEOSExecutionContext::get_density)
    .def_property_readonly("internal_energy", &EosPerfectgas::PerfectGasInitEOSExecutionContext::get_internal_energy)
    .def_property_readonly("sound_speed", &EosPerfectgas::PerfectGasInitEOSExecutionContext::get_sound_speed)
    .def("__str__", [](EosPerfectgas::PerfectGasInitEOSExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](EosPerfectgas::PerfectGasInitEOSExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGAS_INITEOS_DISABLED)
  #if not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGAS_APPLYEOS_DISABLED)
  pybind11::class_<EosPerfectgas::PerfectGasApplyEOSExecutionContext, std::shared_ptr<EosPerfectgas::PerfectGasApplyEOSExecutionContext>, SciHook::SciHookExecutionContext>(sub_eos_perfectgas_perfectgas, "PerfectGasApplyEOSExecutionContext")
    .def_property_readonly("env", &EosPerfectgas::PerfectGasApplyEOSExecutionContext::get_env)
    .def_property_readonly("density", &EosPerfectgas::PerfectGasApplyEOSExecutionContext::get_density)
    .def_property_readonly("internal_energy", &EosPerfectgas::PerfectGasApplyEOSExecutionContext::get_internal_energy)
    .def_property_readonly("adiabatic_cst", &EosPerfectgas::PerfectGasApplyEOSExecutionContext::get_adiabatic_cst)
    .def_property_readonly("pressure", &EosPerfectgas::PerfectGasApplyEOSExecutionContext::get_pressure)
    .def_property_readonly("sound_speed", &EosPerfectgas::PerfectGasApplyEOSExecutionContext::get_sound_speed)
    .def_property_readonly("dpde", &EosPerfectgas::PerfectGasApplyEOSExecutionContext::get_dpde)
    .def("__str__", [](EosPerfectgas::PerfectGasApplyEOSExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](EosPerfectgas::PerfectGasApplyEOSExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGAS_APPLYEOS_DISABLED)
  #if not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGAS_APPLYONECELLEOS_DISABLED)
  pybind11::class_<EosPerfectgas::PerfectGasApplyOneCellEOSExecutionContext, std::shared_ptr<EosPerfectgas::PerfectGasApplyOneCellEOSExecutionContext>, SciHook::SciHookExecutionContext>(sub_eos_perfectgas_perfectgas, "PerfectGasApplyOneCellEOSExecutionContext")
    .def_property_readonly("env", &EosPerfectgas::PerfectGasApplyOneCellEOSExecutionContext::get_env)
    .def_property_readonly("ev", &EosPerfectgas::PerfectGasApplyOneCellEOSExecutionContext::get_ev)
    .def_property_readonly("density", &EosPerfectgas::PerfectGasApplyOneCellEOSExecutionContext::get_density)
    .def_property_readonly("internal_energy", &EosPerfectgas::PerfectGasApplyOneCellEOSExecutionContext::get_internal_energy)
    .def_property_readonly("pressure", &EosPerfectgas::PerfectGasApplyOneCellEOSExecutionContext::get_pressure)
    .def_property_readonly("sound_speed", &EosPerfectgas::PerfectGasApplyOneCellEOSExecutionContext::get_sound_speed)
    .def_property_readonly("dpde", &EosPerfectgas::PerfectGasApplyOneCellEOSExecutionContext::get_dpde)
    .def("__str__", [](EosPerfectgas::PerfectGasApplyOneCellEOSExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](EosPerfectgas::PerfectGasApplyOneCellEOSExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGAS_APPLYONECELLEOS_DISABLED)
  #endif // not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGAS_DISABLED)
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace EosPerfectgas

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // EOS_PERFECTGAS___PERFECTGASSERVICEBINDINGS_H
