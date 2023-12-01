#ifndef EOS_PERFECTGAS___PERFECTGASPACCSERVICEBINDINGS_H
#define EOS_PERFECTGAS___PERFECTGASPACCSERVICEBINDINGS_H

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
#include "eos/perfectgas/__PerfectGasPAccServiceContexts.h"
#include "SciHook.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

using namespace Arcane;
using namespace Arcane::Materials;
namespace EosPerfectgas {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void bind_eos_perfectgas_perfectgaspacc(py::module __attribute__((unused)) &m)
{
  #if not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGASPACC_DISABLED)
  auto sub_eos_perfectgas_perfectgaspacc = m.def_submodule("eos_perfectgas_perfectgaspacc", "Bindings for PerfectGasPAcc");
  #if not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGASPACC_INITEOS_DISABLED)
  pybind11::class_<EosPerfectgas::PerfectGasPAccInitEOSExecutionContext, std::shared_ptr<EosPerfectgas::PerfectGasPAccInitEOSExecutionContext>, SciHook::SciHookExecutionContext>(sub_eos_perfectgas_perfectgaspacc, "PerfectGasPAccInitEOSExecutionContext")
    .def_property_readonly("env", &EosPerfectgas::PerfectGasPAccInitEOSExecutionContext::get_env)
    .def_property_readonly("pressure", &EosPerfectgas::PerfectGasPAccInitEOSExecutionContext::get_pressure)
    .def_property_readonly("density", &EosPerfectgas::PerfectGasPAccInitEOSExecutionContext::get_density)
    .def_property_readonly("internal_energy", &EosPerfectgas::PerfectGasPAccInitEOSExecutionContext::get_internal_energy)
    .def_property_readonly("sound_speed", &EosPerfectgas::PerfectGasPAccInitEOSExecutionContext::get_sound_speed)
    .def("__str__", [](EosPerfectgas::PerfectGasPAccInitEOSExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](EosPerfectgas::PerfectGasPAccInitEOSExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGASPACC_INITEOS_DISABLED)
  #if not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGASPACC_APPLYEOS_DISABLED)
  pybind11::class_<EosPerfectgas::PerfectGasPAccApplyEOSExecutionContext, std::shared_ptr<EosPerfectgas::PerfectGasPAccApplyEOSExecutionContext>, SciHook::SciHookExecutionContext>(sub_eos_perfectgas_perfectgaspacc, "PerfectGasPAccApplyEOSExecutionContext")
    .def_property_readonly("env", &EosPerfectgas::PerfectGasPAccApplyEOSExecutionContext::get_env)
    .def_property_readonly("density", &EosPerfectgas::PerfectGasPAccApplyEOSExecutionContext::get_density)
    .def_property_readonly("internal_energy", &EosPerfectgas::PerfectGasPAccApplyEOSExecutionContext::get_internal_energy)
    .def_property_readonly("pressure", &EosPerfectgas::PerfectGasPAccApplyEOSExecutionContext::get_pressure)
    .def_property_readonly("sound_speed", &EosPerfectgas::PerfectGasPAccApplyEOSExecutionContext::get_sound_speed)
    .def_property_readonly("dpde", &EosPerfectgas::PerfectGasPAccApplyEOSExecutionContext::get_dpde)
    .def("__str__", [](EosPerfectgas::PerfectGasPAccApplyEOSExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](EosPerfectgas::PerfectGasPAccApplyEOSExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGASPACC_APPLYEOS_DISABLED)
  #if not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGASPACC_APPLYONECELLEOS_DISABLED)
  pybind11::class_<EosPerfectgas::PerfectGasPAccApplyOneCellEOSExecutionContext, std::shared_ptr<EosPerfectgas::PerfectGasPAccApplyOneCellEOSExecutionContext>, SciHook::SciHookExecutionContext>(sub_eos_perfectgas_perfectgaspacc, "PerfectGasPAccApplyOneCellEOSExecutionContext")
    .def_property_readonly("env", &EosPerfectgas::PerfectGasPAccApplyOneCellEOSExecutionContext::get_env)
    .def_property_readonly("ev", &EosPerfectgas::PerfectGasPAccApplyOneCellEOSExecutionContext::get_ev)
    .def_property_readonly("density", &EosPerfectgas::PerfectGasPAccApplyOneCellEOSExecutionContext::get_density)
    .def_property_readonly("internal_energy", &EosPerfectgas::PerfectGasPAccApplyOneCellEOSExecutionContext::get_internal_energy)
    .def_property_readonly("pressure", &EosPerfectgas::PerfectGasPAccApplyOneCellEOSExecutionContext::get_pressure)
    .def_property_readonly("sound_speed", &EosPerfectgas::PerfectGasPAccApplyOneCellEOSExecutionContext::get_sound_speed)
    .def_property_readonly("dpde", &EosPerfectgas::PerfectGasPAccApplyOneCellEOSExecutionContext::get_dpde)
    .def("__str__", [](EosPerfectgas::PerfectGasPAccApplyOneCellEOSExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](EosPerfectgas::PerfectGasPAccApplyOneCellEOSExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGASPACC_APPLYONECELLEOS_DISABLED)
  #endif // not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGASPACC_DISABLED)
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace EosPerfectgas

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // EOS_PERFECTGAS___PERFECTGASPACCSERVICEBINDINGS_H
