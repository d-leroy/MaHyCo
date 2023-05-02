#include "arcane/ArcaneTypes.h"
#include "arcane/ItemTypes.h"
#include "arcane/Item.h"
#include "arcane/ItemVector.h"
#include "arcane/ItemVectorView.h"
#include "arcane/VariableTypes.h"
#include "arcane/utils/Array.h"
#include "cas_test/__IInitialisations.h"
#include "cas_test/RIDER/__RiderServiceVars.h"
#include "cas_test/RIDER/__RiderServiceContexts.h"
#include "scihook/scihookdefs.h"
#include "cas_test/RIDER/Rider_axl.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

using namespace Arcane;
namespace Cas_testRIDER {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_RIDER_DISABLED)
PYBIND11_EMBEDDED_MODULE(cas_testrider_rider, m)
{
  pybind11::class_<Cas_testRIDER::RiderInitMatMonoExecutionContext, std::shared_ptr<Cas_testRIDER::RiderInitMatMonoExecutionContext>, SciHook::SciHookExecutionContext>(m, "RiderInitMatMonoExecutionContext")
    .def_property_readonly("dim", &Cas_testRIDER::RiderInitMatMonoExecutionContext::get_dim)
    .def("__str__", [](Cas_testRIDER::RiderInitMatMonoExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Cas_testRIDER::RiderInitMatMonoExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  pybind11::class_<Cas_testRIDER::RiderInitVarMonoExecutionContext, std::shared_ptr<Cas_testRIDER::RiderInitVarMonoExecutionContext>, SciHook::SciHookExecutionContext>(m, "RiderInitVarMonoExecutionContext")
    .def_property_readonly("dim", &Cas_testRIDER::RiderInitVarMonoExecutionContext::get_dim)
    .def("__str__", [](Cas_testRIDER::RiderInitVarMonoExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Cas_testRIDER::RiderInitVarMonoExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  pybind11::class_<Cas_testRIDER::RiderInitMatExecutionContext, std::shared_ptr<Cas_testRIDER::RiderInitMatExecutionContext>, SciHook::SciHookExecutionContext>(m, "RiderInitMatExecutionContext")
    .def_property_readonly("dim", &Cas_testRIDER::RiderInitMatExecutionContext::get_dim)
    .def("__str__", [](Cas_testRIDER::RiderInitMatExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Cas_testRIDER::RiderInitMatExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  pybind11::class_<Cas_testRIDER::RiderInitVarExecutionContext, std::shared_ptr<Cas_testRIDER::RiderInitVarExecutionContext>, SciHook::SciHookExecutionContext>(m, "RiderInitVarExecutionContext")
    .def_property_readonly("dim", &Cas_testRIDER::RiderInitVarExecutionContext::get_dim)
    .def("__str__", [](Cas_testRIDER::RiderInitVarExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Cas_testRIDER::RiderInitVarExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
}
#endif

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace Cas_testRIDER
