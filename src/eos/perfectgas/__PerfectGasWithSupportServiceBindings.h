#ifndef EOS_PERFECTGAS___PERFECTGASWITHSUPPORTSERVICEBINDINGS_H
#define EOS_PERFECTGAS___PERFECTGASWITHSUPPORTSERVICEBINDINGS_H

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
#include "eos/perfectgas/__PerfectGasWithSupportServiceContexts.h"
#include "SciHook.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

using namespace Arcane;
using namespace Arcane::Materials;
namespace EosPerfectgas {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void bind_eos_perfectgas_perfectgaswithsupport(py::module __attribute__((unused)) &m)
{
  #if not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGASWITHSUPPORT_DISABLED)
  auto sub_eos_perfectgas_perfectgaswithsupport = m.def_submodule("eos_perfectgas_perfectgaswithsupport", "Bindings for PerfectGasWithSupport");
  #if not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGASWITHSUPPORT_APPLYEOSWITHSUPPORT_DISABLED)
  pybind11::class_<EosPerfectgas::PerfectGasWithSupportApplyEOSWithSupportExecutionContext, std::shared_ptr<EosPerfectgas::PerfectGasWithSupportApplyEOSWithSupportExecutionContext>, SciHook::SciHookExecutionContext>(sub_eos_perfectgas_perfectgaswithsupport, "PerfectGasWithSupportApplyEOSWithSupportExecutionContext")
    .def_property_readonly("env", &EosPerfectgas::PerfectGasWithSupportApplyEOSWithSupportExecutionContext::get_env)
    .def_property_readonly("density", &EosPerfectgas::PerfectGasWithSupportApplyEOSWithSupportExecutionContext::get_m_density)
    .def_property_readonly("internal_energy", &EosPerfectgas::PerfectGasWithSupportApplyEOSWithSupportExecutionContext::get_m_internal_energy)
    .def_property_readonly("adiabatic_cst", &EosPerfectgas::PerfectGasWithSupportApplyEOSWithSupportExecutionContext::get_m_adiabatic_cst)
    .def_property_readonly("pressure", &EosPerfectgas::PerfectGasWithSupportApplyEOSWithSupportExecutionContext::get_m_pressure)
    .def_property_readonly("sound_speed", &EosPerfectgas::PerfectGasWithSupportApplyEOSWithSupportExecutionContext::get_m_sound_speed)
    .def_property_readonly("dpde", &EosPerfectgas::PerfectGasWithSupportApplyEOSWithSupportExecutionContext::get_m_dpde)
    .def("__str__", [](EosPerfectgas::PerfectGasWithSupportApplyEOSWithSupportExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](EosPerfectgas::PerfectGasWithSupportApplyEOSWithSupportExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGASWITHSUPPORT_APPLYEOSWITHSUPPORT_DISABLED)
  #if not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGASWITHSUPPORT_INITEOS_DISABLED)
  pybind11::class_<EosPerfectgas::PerfectGasWithSupportInitEOSExecutionContext, std::shared_ptr<EosPerfectgas::PerfectGasWithSupportInitEOSExecutionContext>, SciHook::SciHookExecutionContext>(sub_eos_perfectgas_perfectgaswithsupport, "PerfectGasWithSupportInitEOSExecutionContext")
    .def_property_readonly("env", &EosPerfectgas::PerfectGasWithSupportInitEOSExecutionContext::get_env)
    .def_property_readonly("pressure", &EosPerfectgas::PerfectGasWithSupportInitEOSExecutionContext::get_m_pressure)
    .def_property_readonly("density", &EosPerfectgas::PerfectGasWithSupportInitEOSExecutionContext::get_m_density)
    .def_property_readonly("internal_energy", &EosPerfectgas::PerfectGasWithSupportInitEOSExecutionContext::get_m_internal_energy)
    .def_property_readonly("sound_speed", &EosPerfectgas::PerfectGasWithSupportInitEOSExecutionContext::get_m_sound_speed)
    .def("__str__", [](EosPerfectgas::PerfectGasWithSupportInitEOSExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](EosPerfectgas::PerfectGasWithSupportInitEOSExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGASWITHSUPPORT_INITEOS_DISABLED)
  #if not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGASWITHSUPPORT_APPLYEOS_DISABLED)
  pybind11::class_<EosPerfectgas::PerfectGasWithSupportApplyEOSExecutionContext, std::shared_ptr<EosPerfectgas::PerfectGasWithSupportApplyEOSExecutionContext>, SciHook::SciHookExecutionContext>(sub_eos_perfectgas_perfectgaswithsupport, "PerfectGasWithSupportApplyEOSExecutionContext")
    .def_property_readonly("env", &EosPerfectgas::PerfectGasWithSupportApplyEOSExecutionContext::get_env)
    .def("__str__", [](EosPerfectgas::PerfectGasWithSupportApplyEOSExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](EosPerfectgas::PerfectGasWithSupportApplyEOSExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGASWITHSUPPORT_APPLYEOS_DISABLED)
  #if not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGASWITHSUPPORT_APPLYONECELLEOS_DISABLED)
  pybind11::class_<EosPerfectgas::PerfectGasWithSupportApplyOneCellEOSExecutionContext, std::shared_ptr<EosPerfectgas::PerfectGasWithSupportApplyOneCellEOSExecutionContext>, SciHook::SciHookExecutionContext>(sub_eos_perfectgas_perfectgaswithsupport, "PerfectGasWithSupportApplyOneCellEOSExecutionContext")
    .def_property_readonly("env", &EosPerfectgas::PerfectGasWithSupportApplyOneCellEOSExecutionContext::get_env)
    .def_property_readonly("ev", &EosPerfectgas::PerfectGasWithSupportApplyOneCellEOSExecutionContext::get_ev)
    .def_property_readonly("density", &EosPerfectgas::PerfectGasWithSupportApplyOneCellEOSExecutionContext::get_m_density)
    .def_property_readonly("internal_energy", &EosPerfectgas::PerfectGasWithSupportApplyOneCellEOSExecutionContext::get_m_internal_energy)
    .def_property_readonly("pressure", &EosPerfectgas::PerfectGasWithSupportApplyOneCellEOSExecutionContext::get_m_pressure)
    .def_property_readonly("sound_speed", &EosPerfectgas::PerfectGasWithSupportApplyOneCellEOSExecutionContext::get_m_sound_speed)
    .def_property_readonly("dpde", &EosPerfectgas::PerfectGasWithSupportApplyOneCellEOSExecutionContext::get_m_dpde)
    .def("__str__", [](EosPerfectgas::PerfectGasWithSupportApplyOneCellEOSExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](EosPerfectgas::PerfectGasWithSupportApplyOneCellEOSExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGASWITHSUPPORT_APPLYONECELLEOS_DISABLED)
  #endif // not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGASWITHSUPPORT_DISABLED)
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace EosPerfectgas

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // EOS_PERFECTGAS___PERFECTGASWITHSUPPORTSERVICEBINDINGS_H
