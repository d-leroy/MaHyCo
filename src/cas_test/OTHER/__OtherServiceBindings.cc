#include "arcane/ArcaneTypes.h"
#include "arcane/ItemTypes.h"
#include "arcane/Item.h"
#include "arcane/ItemVector.h"
#include "arcane/ItemVectorView.h"
#include "arcane/VariableTypes.h"
#include "arcane/utils/Array.h"
#include "cas_test/__IInitialisations.h"
#include "cas_test/OTHER/__OtherServiceVars.h"
#include "cas_test/OTHER/__OtherServiceContexts.h"
#include "scihook/scihookdefs.h"
#include "cas_test/OTHER/Other_axl.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

using namespace Arcane;
namespace Cas_testOTHER {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_OTHER_DISABLED)
PYBIND11_EMBEDDED_MODULE(cas_testother_other, m)
{
  pybind11::class_<Cas_testOTHER::OtherInitMatMonoExecutionContext, std::shared_ptr<Cas_testOTHER::OtherInitMatMonoExecutionContext>, SciHook::SciHookExecutionContext>(m, "OtherInitMatMonoExecutionContext")
    .def_property_readonly("dim", &Cas_testOTHER::OtherInitMatMonoExecutionContext::get_dim)
    .def("__str__", [](Cas_testOTHER::OtherInitMatMonoExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Cas_testOTHER::OtherInitMatMonoExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  pybind11::class_<Cas_testOTHER::OtherInitVarMonoExecutionContext, std::shared_ptr<Cas_testOTHER::OtherInitVarMonoExecutionContext>, SciHook::SciHookExecutionContext>(m, "OtherInitVarMonoExecutionContext")
    .def_property_readonly("dim", &Cas_testOTHER::OtherInitVarMonoExecutionContext::get_dim)
    .def("__str__", [](Cas_testOTHER::OtherInitVarMonoExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Cas_testOTHER::OtherInitVarMonoExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  pybind11::class_<Cas_testOTHER::OtherInitMatExecutionContext, std::shared_ptr<Cas_testOTHER::OtherInitMatExecutionContext>, SciHook::SciHookExecutionContext>(m, "OtherInitMatExecutionContext")
    .def_property_readonly("dim", &Cas_testOTHER::OtherInitMatExecutionContext::get_dim)
    .def("__str__", [](Cas_testOTHER::OtherInitMatExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Cas_testOTHER::OtherInitMatExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  pybind11::class_<Cas_testOTHER::OtherInitVarExecutionContext, std::shared_ptr<Cas_testOTHER::OtherInitVarExecutionContext>, SciHook::SciHookExecutionContext>(m, "OtherInitVarExecutionContext")
    .def_property_readonly("dim", &Cas_testOTHER::OtherInitVarExecutionContext::get_dim)
    .def("__str__", [](Cas_testOTHER::OtherInitVarExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Cas_testOTHER::OtherInitVarExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
}
#endif

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace Cas_testOTHER
