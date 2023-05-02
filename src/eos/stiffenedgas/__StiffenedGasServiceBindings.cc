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
#include "eos/stiffenedgas/__StiffenedGasServiceVars.h"
#include "eos/stiffenedgas/__StiffenedGasServiceContexts.h"
#include "scihook/scihookdefs.h"
#include "eos/stiffenedgas/StiffenedGas_axl.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

using namespace Arcane;
using namespace Arcane::Materials;
namespace EosStiffenedgas {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_EOS_STIFFENEDGAS_DISABLED)
PYBIND11_EMBEDDED_MODULE(eosstiffenedgas_stiffenedgas, m)
{
  pybind11::class_<EosStiffenedgas::StiffenedGasInitEOSExecutionContext, std::shared_ptr<EosStiffenedgas::StiffenedGasInitEOSExecutionContext>, SciHook::SciHookExecutionContext>(m, "StiffenedGasInitEOSExecutionContext")
    .def_property_readonly("env", &EosStiffenedgas::StiffenedGasInitEOSExecutionContext::get_env)
    .def_property_readonly("pressure", &EosStiffenedgas::StiffenedGasInitEOSExecutionContext::get_m_pressure)
    .def_property_readonly("density", &EosStiffenedgas::StiffenedGasInitEOSExecutionContext::get_m_density)
    .def_property_readonly("internal_energy", &EosStiffenedgas::StiffenedGasInitEOSExecutionContext::get_m_internal_energy)
    .def_property_readonly("sound_speed", &EosStiffenedgas::StiffenedGasInitEOSExecutionContext::get_m_sound_speed)
    .def("__str__", [](EosStiffenedgas::StiffenedGasInitEOSExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](EosStiffenedgas::StiffenedGasInitEOSExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  pybind11::class_<EosStiffenedgas::StiffenedGasApplyEOSExecutionContext, std::shared_ptr<EosStiffenedgas::StiffenedGasApplyEOSExecutionContext>, SciHook::SciHookExecutionContext>(m, "StiffenedGasApplyEOSExecutionContext")
    .def_property_readonly("env", &EosStiffenedgas::StiffenedGasApplyEOSExecutionContext::get_env)
    .def_property_readonly("internal_energy", &EosStiffenedgas::StiffenedGasApplyEOSExecutionContext::get_m_internal_energy)
    .def_property_readonly("density", &EosStiffenedgas::StiffenedGasApplyEOSExecutionContext::get_m_density)
    .def_property_readonly("pressure", &EosStiffenedgas::StiffenedGasApplyEOSExecutionContext::get_m_pressure)
    .def_property_readonly("sound_speed", &EosStiffenedgas::StiffenedGasApplyEOSExecutionContext::get_m_sound_speed)
    .def_property_readonly("dpde", &EosStiffenedgas::StiffenedGasApplyEOSExecutionContext::get_m_dpde)
    .def("__str__", [](EosStiffenedgas::StiffenedGasApplyEOSExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](EosStiffenedgas::StiffenedGasApplyEOSExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  pybind11::class_<EosStiffenedgas::StiffenedGasApplyOneCellEOSExecutionContext, std::shared_ptr<EosStiffenedgas::StiffenedGasApplyOneCellEOSExecutionContext>, SciHook::SciHookExecutionContext>(m, "StiffenedGasApplyOneCellEOSExecutionContext")
    .def_property_readonly("env", &EosStiffenedgas::StiffenedGasApplyOneCellEOSExecutionContext::get_env)
    .def_property_readonly("ev", &EosStiffenedgas::StiffenedGasApplyOneCellEOSExecutionContext::get_ev)
    .def_property_readonly("internal_energy", &EosStiffenedgas::StiffenedGasApplyOneCellEOSExecutionContext::get_m_internal_energy)
    .def_property_readonly("density", &EosStiffenedgas::StiffenedGasApplyOneCellEOSExecutionContext::get_m_density)
    .def_property_readonly("pressure", &EosStiffenedgas::StiffenedGasApplyOneCellEOSExecutionContext::get_m_pressure)
    .def_property_readonly("sound_speed", &EosStiffenedgas::StiffenedGasApplyOneCellEOSExecutionContext::get_m_sound_speed)
    .def_property_readonly("dpde", &EosStiffenedgas::StiffenedGasApplyOneCellEOSExecutionContext::get_m_dpde)
    .def("__str__", [](EosStiffenedgas::StiffenedGasApplyOneCellEOSExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](EosStiffenedgas::StiffenedGasApplyOneCellEOSExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
}
#endif

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace EosStiffenedgas
