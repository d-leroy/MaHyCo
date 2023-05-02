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
#include "eos/__IEquationOfState.h"
#include "eos/perfectgas/__PerfectGasServiceVars.h"
#include "eos/perfectgas/__PerfectGasServiceContexts.h"
#include "scihook/scihookdefs.h"
#include "eos/perfectgas/PerfectGas_axl.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

using namespace Arcane;
using namespace Arcane::Materials;
namespace EosPerfectgas {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_EOS_PERFECTGAS_DISABLED)
PYBIND11_EMBEDDED_MODULE(eosperfectgas_perfectgas, m)
{
  pybind11::class_<EosPerfectgas::PerfectGasInitEOSExecutionContext, std::shared_ptr<EosPerfectgas::PerfectGasInitEOSExecutionContext>, SciHook::SciHookExecutionContext>(m, "PerfectGasInitEOSExecutionContext")
    .def_property_readonly("env", &EosPerfectgas::PerfectGasInitEOSExecutionContext::get_env)
    .def_property_readonly("pressure", &EosPerfectgas::PerfectGasInitEOSExecutionContext::get_m_pressure)
    .def_property_readonly("density", &EosPerfectgas::PerfectGasInitEOSExecutionContext::get_m_density)
    .def_property_readonly("internal_energy", &EosPerfectgas::PerfectGasInitEOSExecutionContext::get_m_internal_energy)
    .def_property_readonly("sound_speed", &EosPerfectgas::PerfectGasInitEOSExecutionContext::get_m_sound_speed)
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
  pybind11::class_<EosPerfectgas::PerfectGasApplyEOSExecutionContext, std::shared_ptr<EosPerfectgas::PerfectGasApplyEOSExecutionContext>, SciHook::SciHookExecutionContext>(m, "PerfectGasApplyEOSExecutionContext")
    .def_property_readonly("env", &EosPerfectgas::PerfectGasApplyEOSExecutionContext::get_env)
    .def_property_readonly("density", &EosPerfectgas::PerfectGasApplyEOSExecutionContext::get_m_density)
    .def_property_readonly("internal_energy", &EosPerfectgas::PerfectGasApplyEOSExecutionContext::get_m_internal_energy)
    .def_property_readonly("pressure", &EosPerfectgas::PerfectGasApplyEOSExecutionContext::get_m_pressure)
    .def_property_readonly("sound_speed", &EosPerfectgas::PerfectGasApplyEOSExecutionContext::get_m_sound_speed)
    .def_property_readonly("dpde", &EosPerfectgas::PerfectGasApplyEOSExecutionContext::get_m_dpde)
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
  pybind11::class_<EosPerfectgas::PerfectGasApplyOneCellEOSExecutionContext, std::shared_ptr<EosPerfectgas::PerfectGasApplyOneCellEOSExecutionContext>, SciHook::SciHookExecutionContext>(m, "PerfectGasApplyOneCellEOSExecutionContext")
    .def_property_readonly("env", &EosPerfectgas::PerfectGasApplyOneCellEOSExecutionContext::get_env)
    .def_property_readonly("ev", &EosPerfectgas::PerfectGasApplyOneCellEOSExecutionContext::get_ev)
    .def_property_readonly("density", &EosPerfectgas::PerfectGasApplyOneCellEOSExecutionContext::get_m_density)
    .def_property_readonly("internal_energy", &EosPerfectgas::PerfectGasApplyOneCellEOSExecutionContext::get_m_internal_energy)
    .def_property_readonly("pressure", &EosPerfectgas::PerfectGasApplyOneCellEOSExecutionContext::get_m_pressure)
    .def_property_readonly("sound_speed", &EosPerfectgas::PerfectGasApplyOneCellEOSExecutionContext::get_m_sound_speed)
    .def_property_readonly("dpde", &EosPerfectgas::PerfectGasApplyOneCellEOSExecutionContext::get_m_dpde)
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
}
#endif

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace EosPerfectgas
