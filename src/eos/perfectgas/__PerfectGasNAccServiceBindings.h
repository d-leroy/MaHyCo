#ifndef EOS_PERFECTGAS___PERFECTGASNACCSERVICEBINDINGS_H
#define EOS_PERFECTGAS___PERFECTGASNACCSERVICEBINDINGS_H

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
#include "eos/perfectgas/__PerfectGasNAccServiceContexts.h"
#include "SciHook.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

using namespace Arcane;
using namespace Arcane::Materials;
namespace EosPerfectgas {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void bind_eos_perfectgas_perfectgasnacc(py::module __attribute__((unused)) &m)
{
  #if not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGASNACC_DISABLED)
  auto sub_eos_perfectgas_perfectgasnacc = m.def_submodule("eos_perfectgas_perfectgasnacc", "Bindings for PerfectGasNAcc");
  #if not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGASNACC_INITEOS_DISABLED)
  pybind11::class_<EosPerfectgas::PerfectGasNAccInitEOSExecutionContext, std::shared_ptr<EosPerfectgas::PerfectGasNAccInitEOSExecutionContext>, SciHook::SciHookExecutionContext>(sub_eos_perfectgas_perfectgasnacc, "PerfectGasNAccInitEOSExecutionContext")
    .def_property_readonly("env", &EosPerfectgas::PerfectGasNAccInitEOSExecutionContext::get_env)
    .def_property_readonly("pressure", &EosPerfectgas::PerfectGasNAccInitEOSExecutionContext::get_pressure)
    .def_property_readonly("density", &EosPerfectgas::PerfectGasNAccInitEOSExecutionContext::get_density)
    .def_property_readonly("internal_energy", &EosPerfectgas::PerfectGasNAccInitEOSExecutionContext::get_internal_energy)
    .def_property_readonly("sound_speed", &EosPerfectgas::PerfectGasNAccInitEOSExecutionContext::get_sound_speed)
    .def("__str__", [](EosPerfectgas::PerfectGasNAccInitEOSExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](EosPerfectgas::PerfectGasNAccInitEOSExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGASNACC_INITEOS_DISABLED)
  #if not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGASNACC_APPLYEOS_DISABLED)
  pybind11::class_<EosPerfectgas::PerfectGasNAccApplyEOSExecutionContext, std::shared_ptr<EosPerfectgas::PerfectGasNAccApplyEOSExecutionContext>, SciHook::SciHookExecutionContext>(sub_eos_perfectgas_perfectgasnacc, "PerfectGasNAccApplyEOSExecutionContext")
    .def_property_readonly("env", &EosPerfectgas::PerfectGasNAccApplyEOSExecutionContext::get_env)
    .def_property_readonly("density", &EosPerfectgas::PerfectGasNAccApplyEOSExecutionContext::get_density)
    .def_property_readonly("internal_energy", &EosPerfectgas::PerfectGasNAccApplyEOSExecutionContext::get_internal_energy)
    .def_property_readonly("adiabatic_cst", &EosPerfectgas::PerfectGasNAccApplyEOSExecutionContext::get_adiabatic_cst)
    .def_property_readonly("pressure", &EosPerfectgas::PerfectGasNAccApplyEOSExecutionContext::get_pressure)
    .def_property_readonly("sound_speed", &EosPerfectgas::PerfectGasNAccApplyEOSExecutionContext::get_sound_speed)
    .def_property_readonly("dpde", &EosPerfectgas::PerfectGasNAccApplyEOSExecutionContext::get_dpde)
    .def("__str__", [](EosPerfectgas::PerfectGasNAccApplyEOSExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](EosPerfectgas::PerfectGasNAccApplyEOSExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGASNACC_APPLYEOS_DISABLED)
  #if not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGASNACC_APPLYONECELLEOS_DISABLED)
  pybind11::class_<EosPerfectgas::PerfectGasNAccApplyOneCellEOSExecutionContext, std::shared_ptr<EosPerfectgas::PerfectGasNAccApplyOneCellEOSExecutionContext>, SciHook::SciHookExecutionContext>(sub_eos_perfectgas_perfectgasnacc, "PerfectGasNAccApplyOneCellEOSExecutionContext")
    .def_property_readonly("env", &EosPerfectgas::PerfectGasNAccApplyOneCellEOSExecutionContext::get_env)
    .def_property_readonly("ev", &EosPerfectgas::PerfectGasNAccApplyOneCellEOSExecutionContext::get_ev)
    .def_property_readonly("density", &EosPerfectgas::PerfectGasNAccApplyOneCellEOSExecutionContext::get_density)
    .def_property_readonly("internal_energy", &EosPerfectgas::PerfectGasNAccApplyOneCellEOSExecutionContext::get_internal_energy)
    .def_property_readonly("pressure", &EosPerfectgas::PerfectGasNAccApplyOneCellEOSExecutionContext::get_pressure)
    .def_property_readonly("sound_speed", &EosPerfectgas::PerfectGasNAccApplyOneCellEOSExecutionContext::get_sound_speed)
    .def_property_readonly("dpde", &EosPerfectgas::PerfectGasNAccApplyOneCellEOSExecutionContext::get_dpde)
    .def("__str__", [](EosPerfectgas::PerfectGasNAccApplyOneCellEOSExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](EosPerfectgas::PerfectGasNAccApplyOneCellEOSExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGASNACC_APPLYONECELLEOS_DISABLED)
  #endif // not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGASNACC_DISABLED)
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace EosPerfectgas

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // EOS_PERFECTGAS___PERFECTGASNACCSERVICEBINDINGS_H
