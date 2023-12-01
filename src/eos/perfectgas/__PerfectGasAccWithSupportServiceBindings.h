#ifndef EOS_PERFECTGAS___PERFECTGASACCWITHSUPPORTSERVICEBINDINGS_H
#define EOS_PERFECTGAS___PERFECTGASACCWITHSUPPORTSERVICEBINDINGS_H

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
#include "eos/perfectgas/__PerfectGasAccWithSupportServiceContexts.h"
#include "SciHook.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

using namespace Arcane;
using namespace Arcane::Materials;
namespace EosPerfectgas {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void bind_eos_perfectgas_perfectgasaccwithsupport(py::module __attribute__((unused)) &m)
{
  #if not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGASACCWITHSUPPORT_DISABLED)
  auto sub_eos_perfectgas_perfectgasaccwithsupport = m.def_submodule("eos_perfectgas_perfectgasaccwithsupport", "Bindings for PerfectGasAccWithSupport");
  #if not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGASACCWITHSUPPORT_APPLYEOSWITHSUPPORT_DISABLED)
  pybind11::class_<EosPerfectgas::PerfectGasAccWithSupportApplyEOSWithSupportExecutionContext, std::shared_ptr<EosPerfectgas::PerfectGasAccWithSupportApplyEOSWithSupportExecutionContext>, SciHook::SciHookExecutionContext>(sub_eos_perfectgas_perfectgasaccwithsupport, "PerfectGasAccWithSupportApplyEOSWithSupportExecutionContext")
    .def_property_readonly("env", &EosPerfectgas::PerfectGasAccWithSupportApplyEOSWithSupportExecutionContext::get_env)
    .def_property_readonly("density", &EosPerfectgas::PerfectGasAccWithSupportApplyEOSWithSupportExecutionContext::get_density)
    .def_property_readonly("internal_energy", &EosPerfectgas::PerfectGasAccWithSupportApplyEOSWithSupportExecutionContext::get_internal_energy)
    .def_property_readonly("adiabatic_cst", &EosPerfectgas::PerfectGasAccWithSupportApplyEOSWithSupportExecutionContext::get_adiabatic_cst)
    .def_property_readonly("pressure", &EosPerfectgas::PerfectGasAccWithSupportApplyEOSWithSupportExecutionContext::get_pressure)
    .def_property_readonly("sound_speed", &EosPerfectgas::PerfectGasAccWithSupportApplyEOSWithSupportExecutionContext::get_sound_speed)
    .def_property_readonly("dpde", &EosPerfectgas::PerfectGasAccWithSupportApplyEOSWithSupportExecutionContext::get_dpde)
    .def("__str__", [](EosPerfectgas::PerfectGasAccWithSupportApplyEOSWithSupportExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](EosPerfectgas::PerfectGasAccWithSupportApplyEOSWithSupportExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGASACCWITHSUPPORT_APPLYEOSWITHSUPPORT_DISABLED)
  #if not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGASACCWITHSUPPORT_INITEOS_DISABLED)
  pybind11::class_<EosPerfectgas::PerfectGasAccWithSupportInitEOSExecutionContext, std::shared_ptr<EosPerfectgas::PerfectGasAccWithSupportInitEOSExecutionContext>, SciHook::SciHookExecutionContext>(sub_eos_perfectgas_perfectgasaccwithsupport, "PerfectGasAccWithSupportInitEOSExecutionContext")
    .def_property_readonly("env", &EosPerfectgas::PerfectGasAccWithSupportInitEOSExecutionContext::get_env)
    .def_property_readonly("pressure", &EosPerfectgas::PerfectGasAccWithSupportInitEOSExecutionContext::get_pressure)
    .def_property_readonly("density", &EosPerfectgas::PerfectGasAccWithSupportInitEOSExecutionContext::get_density)
    .def_property_readonly("internal_energy", &EosPerfectgas::PerfectGasAccWithSupportInitEOSExecutionContext::get_internal_energy)
    .def_property_readonly("sound_speed", &EosPerfectgas::PerfectGasAccWithSupportInitEOSExecutionContext::get_sound_speed)
    .def("__str__", [](EosPerfectgas::PerfectGasAccWithSupportInitEOSExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](EosPerfectgas::PerfectGasAccWithSupportInitEOSExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGASACCWITHSUPPORT_INITEOS_DISABLED)
  #if not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGASACCWITHSUPPORT_APPLYEOS_DISABLED)
  pybind11::class_<EosPerfectgas::PerfectGasAccWithSupportApplyEOSExecutionContext, std::shared_ptr<EosPerfectgas::PerfectGasAccWithSupportApplyEOSExecutionContext>, SciHook::SciHookExecutionContext>(sub_eos_perfectgas_perfectgasaccwithsupport, "PerfectGasAccWithSupportApplyEOSExecutionContext")
    .def_property_readonly("env", &EosPerfectgas::PerfectGasAccWithSupportApplyEOSExecutionContext::get_env)
    .def("__str__", [](EosPerfectgas::PerfectGasAccWithSupportApplyEOSExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](EosPerfectgas::PerfectGasAccWithSupportApplyEOSExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGASACCWITHSUPPORT_APPLYEOS_DISABLED)
  #if not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGASACCWITHSUPPORT_APPLYONECELLEOS_DISABLED)
  pybind11::class_<EosPerfectgas::PerfectGasAccWithSupportApplyOneCellEOSExecutionContext, std::shared_ptr<EosPerfectgas::PerfectGasAccWithSupportApplyOneCellEOSExecutionContext>, SciHook::SciHookExecutionContext>(sub_eos_perfectgas_perfectgasaccwithsupport, "PerfectGasAccWithSupportApplyOneCellEOSExecutionContext")
    .def_property_readonly("env", &EosPerfectgas::PerfectGasAccWithSupportApplyOneCellEOSExecutionContext::get_env)
    .def_property_readonly("ev", &EosPerfectgas::PerfectGasAccWithSupportApplyOneCellEOSExecutionContext::get_ev)
    .def_property_readonly("density", &EosPerfectgas::PerfectGasAccWithSupportApplyOneCellEOSExecutionContext::get_density)
    .def_property_readonly("internal_energy", &EosPerfectgas::PerfectGasAccWithSupportApplyOneCellEOSExecutionContext::get_internal_energy)
    .def_property_readonly("pressure", &EosPerfectgas::PerfectGasAccWithSupportApplyOneCellEOSExecutionContext::get_pressure)
    .def_property_readonly("sound_speed", &EosPerfectgas::PerfectGasAccWithSupportApplyOneCellEOSExecutionContext::get_sound_speed)
    .def_property_readonly("dpde", &EosPerfectgas::PerfectGasAccWithSupportApplyOneCellEOSExecutionContext::get_dpde)
    .def("__str__", [](EosPerfectgas::PerfectGasAccWithSupportApplyOneCellEOSExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](EosPerfectgas::PerfectGasAccWithSupportApplyOneCellEOSExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGASACCWITHSUPPORT_APPLYONECELLEOS_DISABLED)
  #endif // not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGASACCWITHSUPPORT_DISABLED)
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace EosPerfectgas

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // EOS_PERFECTGAS___PERFECTGASACCWITHSUPPORTSERVICEBINDINGS_H
