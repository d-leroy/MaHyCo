#ifndef EOS_PERFECTGAS___PERFECTGASACCSERVICEBINDINGS_H
#define EOS_PERFECTGAS___PERFECTGASACCSERVICEBINDINGS_H

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
#include "eos/perfectgas/__PerfectGasAccServiceContexts.h"
#include "SciHook.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

using namespace Arcane;
using namespace Arcane::Materials;
namespace EosPerfectgas {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void bind_eos_perfectgas_perfectgasacc(py::module __attribute__((unused)) &m)
{
  #if not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGASACC_DISABLED)
  auto sub_eos_perfectgas_perfectgasacc = m.def_submodule("eos_perfectgas_perfectgasacc", "Bindings for PerfectGasAcc");
  #if not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGASACC_APPLYEOSWITHSUPPORT_DISABLED)
  pybind11::class_<EosPerfectgas::PerfectGasAccApplyEOSWithSupportExecutionContext, std::shared_ptr<EosPerfectgas::PerfectGasAccApplyEOSWithSupportExecutionContext>, SciHook::SciHookExecutionContext>(sub_eos_perfectgas_perfectgasacc, "PerfectGasAccApplyEOSWithSupportExecutionContext")
    .def_property_readonly("env", &EosPerfectgas::PerfectGasAccApplyEOSWithSupportExecutionContext::get_env)
    .def_property_readonly("density", &EosPerfectgas::PerfectGasAccApplyEOSWithSupportExecutionContext::get_m_density)
    .def_property_readonly("internal_energy", &EosPerfectgas::PerfectGasAccApplyEOSWithSupportExecutionContext::get_m_internal_energy)
    .def_property_readonly("adiabatic_cst", &EosPerfectgas::PerfectGasAccApplyEOSWithSupportExecutionContext::get_m_adiabatic_cst)
    .def_property_readonly("pressure", &EosPerfectgas::PerfectGasAccApplyEOSWithSupportExecutionContext::get_m_pressure)
    .def_property_readonly("sound_speed", &EosPerfectgas::PerfectGasAccApplyEOSWithSupportExecutionContext::get_m_sound_speed)
    .def_property_readonly("dpde", &EosPerfectgas::PerfectGasAccApplyEOSWithSupportExecutionContext::get_m_dpde)
    .def("__str__", [](EosPerfectgas::PerfectGasAccApplyEOSWithSupportExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](EosPerfectgas::PerfectGasAccApplyEOSWithSupportExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGASACC_APPLYEOSWITHSUPPORT_DISABLED)
  #if not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGASACC_INITEOS_DISABLED)
  pybind11::class_<EosPerfectgas::PerfectGasAccInitEOSExecutionContext, std::shared_ptr<EosPerfectgas::PerfectGasAccInitEOSExecutionContext>, SciHook::SciHookExecutionContext>(sub_eos_perfectgas_perfectgasacc, "PerfectGasAccInitEOSExecutionContext")
    .def_property_readonly("env", &EosPerfectgas::PerfectGasAccInitEOSExecutionContext::get_env)
    .def_property_readonly("pressure", &EosPerfectgas::PerfectGasAccInitEOSExecutionContext::get_m_pressure)
    .def_property_readonly("density", &EosPerfectgas::PerfectGasAccInitEOSExecutionContext::get_m_density)
    .def_property_readonly("internal_energy", &EosPerfectgas::PerfectGasAccInitEOSExecutionContext::get_m_internal_energy)
    .def_property_readonly("sound_speed", &EosPerfectgas::PerfectGasAccInitEOSExecutionContext::get_m_sound_speed)
    .def("__str__", [](EosPerfectgas::PerfectGasAccInitEOSExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](EosPerfectgas::PerfectGasAccInitEOSExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGASACC_INITEOS_DISABLED)
  #if not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGASACC_APPLYEOS_DISABLED)
  pybind11::class_<EosPerfectgas::PerfectGasAccApplyEOSExecutionContext, std::shared_ptr<EosPerfectgas::PerfectGasAccApplyEOSExecutionContext>, SciHook::SciHookExecutionContext>(sub_eos_perfectgas_perfectgasacc, "PerfectGasAccApplyEOSExecutionContext")
    .def_property_readonly("env", &EosPerfectgas::PerfectGasAccApplyEOSExecutionContext::get_env)
    .def("__str__", [](EosPerfectgas::PerfectGasAccApplyEOSExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](EosPerfectgas::PerfectGasAccApplyEOSExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGASACC_APPLYEOS_DISABLED)
  #if not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGASACC_APPLYONECELLEOS_DISABLED)
  pybind11::class_<EosPerfectgas::PerfectGasAccApplyOneCellEOSExecutionContext, std::shared_ptr<EosPerfectgas::PerfectGasAccApplyOneCellEOSExecutionContext>, SciHook::SciHookExecutionContext>(sub_eos_perfectgas_perfectgasacc, "PerfectGasAccApplyOneCellEOSExecutionContext")
    .def_property_readonly("env", &EosPerfectgas::PerfectGasAccApplyOneCellEOSExecutionContext::get_env)
    .def_property_readonly("ev", &EosPerfectgas::PerfectGasAccApplyOneCellEOSExecutionContext::get_ev)
    .def_property_readonly("density", &EosPerfectgas::PerfectGasAccApplyOneCellEOSExecutionContext::get_m_density)
    .def_property_readonly("internal_energy", &EosPerfectgas::PerfectGasAccApplyOneCellEOSExecutionContext::get_m_internal_energy)
    .def_property_readonly("pressure", &EosPerfectgas::PerfectGasAccApplyOneCellEOSExecutionContext::get_m_pressure)
    .def_property_readonly("sound_speed", &EosPerfectgas::PerfectGasAccApplyOneCellEOSExecutionContext::get_m_sound_speed)
    .def_property_readonly("dpde", &EosPerfectgas::PerfectGasAccApplyOneCellEOSExecutionContext::get_m_dpde)
    .def("__str__", [](EosPerfectgas::PerfectGasAccApplyOneCellEOSExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](EosPerfectgas::PerfectGasAccApplyOneCellEOSExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGASACC_APPLYONECELLEOS_DISABLED)
  #endif // not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGASACC_DISABLED)
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace EosPerfectgas

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // EOS_PERFECTGAS___PERFECTGASACCSERVICEBINDINGS_H
