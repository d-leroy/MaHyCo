#ifndef EOS_STIFFENEDGAS___STIFFENEDGASACCSERVICEBINDINGS_H
#define EOS_STIFFENEDGAS___STIFFENEDGASACCSERVICEBINDINGS_H

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
#include "eos/stiffenedgas/__StiffenedGasAccServiceContexts.h"
#include "SciHook.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

using namespace Arcane;
using namespace Arcane::Materials;
namespace EosStiffenedgas {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void bind_eos_stiffenedgas_stiffenedgasacc(py::module __attribute__((unused)) &m)
{
  #if not defined(SCIHOOK_EOS_STIFFENEDGAS_STIFFENEDGASACC_DISABLED)
  auto sub_eos_stiffenedgas_stiffenedgasacc = m.def_submodule("eos_stiffenedgas_stiffenedgasacc", "Bindings for StiffenedGasAcc");
  #if not defined(SCIHOOK_EOS_STIFFENEDGAS_STIFFENEDGASACC_APPLYEOSWITHSUPPORT_DISABLED)
  pybind11::class_<EosStiffenedgas::StiffenedGasAccApplyEOSWithSupportExecutionContext, std::shared_ptr<EosStiffenedgas::StiffenedGasAccApplyEOSWithSupportExecutionContext>, SciHook::SciHookExecutionContext>(sub_eos_stiffenedgas_stiffenedgasacc, "StiffenedGasAccApplyEOSWithSupportExecutionContext")
    .def_property_readonly("internal_energy", &EosStiffenedgas::StiffenedGasAccApplyEOSWithSupportExecutionContext::get_internal_energy)
    .def_property_readonly("density", &EosStiffenedgas::StiffenedGasAccApplyEOSWithSupportExecutionContext::get_density)
    .def_property_readonly("tension_limit_cst", &EosStiffenedgas::StiffenedGasAccApplyEOSWithSupportExecutionContext::get_tension_limit_cst)
    .def_property_readonly("adiabatic_cst", &EosStiffenedgas::StiffenedGasAccApplyEOSWithSupportExecutionContext::get_adiabatic_cst)
    .def_property_readonly("pressure", &EosStiffenedgas::StiffenedGasAccApplyEOSWithSupportExecutionContext::get_pressure)
    .def_property_readonly("sound_speed", &EosStiffenedgas::StiffenedGasAccApplyEOSWithSupportExecutionContext::get_sound_speed)
    .def_property_readonly("dpde", &EosStiffenedgas::StiffenedGasAccApplyEOSWithSupportExecutionContext::get_dpde)
    .def("__str__", [](EosStiffenedgas::StiffenedGasAccApplyEOSWithSupportExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](EosStiffenedgas::StiffenedGasAccApplyEOSWithSupportExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_EOS_STIFFENEDGAS_STIFFENEDGASACC_APPLYEOSWITHSUPPORT_DISABLED)
  #if not defined(SCIHOOK_EOS_STIFFENEDGAS_STIFFENEDGASACC_INITEOS_DISABLED)
  pybind11::class_<EosStiffenedgas::StiffenedGasAccInitEOSExecutionContext, std::shared_ptr<EosStiffenedgas::StiffenedGasAccInitEOSExecutionContext>, SciHook::SciHookExecutionContext>(sub_eos_stiffenedgas_stiffenedgasacc, "StiffenedGasAccInitEOSExecutionContext")
    .def_property_readonly("env", &EosStiffenedgas::StiffenedGasAccInitEOSExecutionContext::get_env)
    .def_property_readonly("pressure", &EosStiffenedgas::StiffenedGasAccInitEOSExecutionContext::get_pressure)
    .def_property_readonly("density", &EosStiffenedgas::StiffenedGasAccInitEOSExecutionContext::get_density)
    .def_property_readonly("internal_energy", &EosStiffenedgas::StiffenedGasAccInitEOSExecutionContext::get_internal_energy)
    .def_property_readonly("sound_speed", &EosStiffenedgas::StiffenedGasAccInitEOSExecutionContext::get_sound_speed)
    .def("__str__", [](EosStiffenedgas::StiffenedGasAccInitEOSExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](EosStiffenedgas::StiffenedGasAccInitEOSExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_EOS_STIFFENEDGAS_STIFFENEDGASACC_INITEOS_DISABLED)
  #if not defined(SCIHOOK_EOS_STIFFENEDGAS_STIFFENEDGASACC_APPLYEOS_DISABLED)
  pybind11::class_<EosStiffenedgas::StiffenedGasAccApplyEOSExecutionContext, std::shared_ptr<EosStiffenedgas::StiffenedGasAccApplyEOSExecutionContext>, SciHook::SciHookExecutionContext>(sub_eos_stiffenedgas_stiffenedgasacc, "StiffenedGasAccApplyEOSExecutionContext")
    .def_property_readonly("env", &EosStiffenedgas::StiffenedGasAccApplyEOSExecutionContext::get_env)
    .def("__str__", [](EosStiffenedgas::StiffenedGasAccApplyEOSExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](EosStiffenedgas::StiffenedGasAccApplyEOSExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_EOS_STIFFENEDGAS_STIFFENEDGASACC_APPLYEOS_DISABLED)
  #if not defined(SCIHOOK_EOS_STIFFENEDGAS_STIFFENEDGASACC_APPLYONECELLEOS_DISABLED)
  pybind11::class_<EosStiffenedgas::StiffenedGasAccApplyOneCellEOSExecutionContext, std::shared_ptr<EosStiffenedgas::StiffenedGasAccApplyOneCellEOSExecutionContext>, SciHook::SciHookExecutionContext>(sub_eos_stiffenedgas_stiffenedgasacc, "StiffenedGasAccApplyOneCellEOSExecutionContext")
    .def_property_readonly("env", &EosStiffenedgas::StiffenedGasAccApplyOneCellEOSExecutionContext::get_env)
    .def_property_readonly("ev", &EosStiffenedgas::StiffenedGasAccApplyOneCellEOSExecutionContext::get_ev)
    .def_property_readonly("internal_energy", &EosStiffenedgas::StiffenedGasAccApplyOneCellEOSExecutionContext::get_internal_energy)
    .def_property_readonly("density", &EosStiffenedgas::StiffenedGasAccApplyOneCellEOSExecutionContext::get_density)
    .def_property_readonly("pressure", &EosStiffenedgas::StiffenedGasAccApplyOneCellEOSExecutionContext::get_pressure)
    .def_property_readonly("sound_speed", &EosStiffenedgas::StiffenedGasAccApplyOneCellEOSExecutionContext::get_sound_speed)
    .def_property_readonly("dpde", &EosStiffenedgas::StiffenedGasAccApplyOneCellEOSExecutionContext::get_dpde)
    .def("__str__", [](EosStiffenedgas::StiffenedGasAccApplyOneCellEOSExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](EosStiffenedgas::StiffenedGasAccApplyOneCellEOSExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_EOS_STIFFENEDGAS_STIFFENEDGASACC_APPLYONECELLEOS_DISABLED)
  #endif // not defined(SCIHOOK_EOS_STIFFENEDGAS_STIFFENEDGASACC_DISABLED)
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace EosStiffenedgas

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // EOS_STIFFENEDGAS___STIFFENEDGASACCSERVICEBINDINGS_H
