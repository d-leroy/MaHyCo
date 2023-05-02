#include "arcane/ArcaneTypes.h"
#include "arcane/ItemTypes.h"
#include "arcane/Item.h"
#include "arcane/ItemVector.h"
#include "arcane/ItemVectorView.h"
#include "arcane/VariableTypes.h"
#include "arcane/utils/Array.h"
#include "cas_test/__IInitialisations.h"
#include "cas_test/SEDOV/__SedovServiceVars.h"
#include "cas_test/SEDOV/__SedovServiceContexts.h"
#include "scihook/scihookdefs.h"
#include "cas_test/SEDOV/Sedov_axl.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

using namespace Arcane;
namespace Cas_testSEDOV {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_SEDOV_DISABLED)
PYBIND11_EMBEDDED_MODULE(cas_testsedov_sedov, m)
{
  pybind11::class_<Cas_testSEDOV::SedovInitMatMonoExecutionContext, std::shared_ptr<Cas_testSEDOV::SedovInitMatMonoExecutionContext>, SciHook::SciHookExecutionContext>(m, "SedovInitMatMonoExecutionContext")
    .def_property_readonly("dim", &Cas_testSEDOV::SedovInitMatMonoExecutionContext::get_dim)
    .def("__str__", [](Cas_testSEDOV::SedovInitMatMonoExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Cas_testSEDOV::SedovInitMatMonoExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  pybind11::class_<Cas_testSEDOV::SedovInitVarMonoExecutionContext, std::shared_ptr<Cas_testSEDOV::SedovInitVarMonoExecutionContext>, SciHook::SciHookExecutionContext>(m, "SedovInitVarMonoExecutionContext")
    .def_property_readonly("dim", &Cas_testSEDOV::SedovInitVarMonoExecutionContext::get_dim)
    .def("__str__", [](Cas_testSEDOV::SedovInitVarMonoExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Cas_testSEDOV::SedovInitVarMonoExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  pybind11::class_<Cas_testSEDOV::SedovInitMatExecutionContext, std::shared_ptr<Cas_testSEDOV::SedovInitMatExecutionContext>, SciHook::SciHookExecutionContext>(m, "SedovInitMatExecutionContext")
    .def_property_readonly("dim", &Cas_testSEDOV::SedovInitMatExecutionContext::get_dim)
    .def("__str__", [](Cas_testSEDOV::SedovInitMatExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Cas_testSEDOV::SedovInitMatExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  pybind11::class_<Cas_testSEDOV::SedovInitVarExecutionContext, std::shared_ptr<Cas_testSEDOV::SedovInitVarExecutionContext>, SciHook::SciHookExecutionContext>(m, "SedovInitVarExecutionContext")
    .def_property_readonly("dim", &Cas_testSEDOV::SedovInitVarExecutionContext::get_dim)
    .def("__str__", [](Cas_testSEDOV::SedovInitVarExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Cas_testSEDOV::SedovInitVarExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
}
#endif

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace Cas_testSEDOV
