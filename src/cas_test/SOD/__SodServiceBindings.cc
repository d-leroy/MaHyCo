#include "arcane/ArcaneTypes.h"
#include "arcane/ItemTypes.h"
#include "arcane/Item.h"
#include "arcane/ItemVector.h"
#include "arcane/ItemVectorView.h"
#include "arcane/VariableTypes.h"
#include "arcane/utils/Array.h"
#include "cas_test/__IInitialisations.h"
#include "cas_test/SOD/__SodServiceVars.h"
#include "cas_test/SOD/__SodServiceContexts.h"
#include "scihook/scihookdefs.h"
#include "cas_test/SOD/Sod_axl.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

using namespace Arcane;
namespace Cas_testSOD {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_SOD_DISABLED)
PYBIND11_EMBEDDED_MODULE(cas_testsod_sod, m)
{
  pybind11::class_<Cas_testSOD::SodInitMatMonoExecutionContext, std::shared_ptr<Cas_testSOD::SodInitMatMonoExecutionContext>, SciHook::SciHookExecutionContext>(m, "SodInitMatMonoExecutionContext")
    .def_property_readonly("dim", &Cas_testSOD::SodInitMatMonoExecutionContext::get_dim)
    .def("__str__", [](Cas_testSOD::SodInitMatMonoExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Cas_testSOD::SodInitMatMonoExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  pybind11::class_<Cas_testSOD::SodInitVarMonoExecutionContext, std::shared_ptr<Cas_testSOD::SodInitVarMonoExecutionContext>, SciHook::SciHookExecutionContext>(m, "SodInitVarMonoExecutionContext")
    .def_property_readonly("dim", &Cas_testSOD::SodInitVarMonoExecutionContext::get_dim)
    .def("__str__", [](Cas_testSOD::SodInitVarMonoExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Cas_testSOD::SodInitVarMonoExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  pybind11::class_<Cas_testSOD::SodInitMatExecutionContext, std::shared_ptr<Cas_testSOD::SodInitMatExecutionContext>, SciHook::SciHookExecutionContext>(m, "SodInitMatExecutionContext")
    .def_property_readonly("dim", &Cas_testSOD::SodInitMatExecutionContext::get_dim)
    .def("__str__", [](Cas_testSOD::SodInitMatExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Cas_testSOD::SodInitMatExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  pybind11::class_<Cas_testSOD::SodInitVarExecutionContext, std::shared_ptr<Cas_testSOD::SodInitVarExecutionContext>, SciHook::SciHookExecutionContext>(m, "SodInitVarExecutionContext")
    .def_property_readonly("dim", &Cas_testSOD::SodInitVarExecutionContext::get_dim)
    .def("__str__", [](Cas_testSOD::SodInitVarExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Cas_testSOD::SodInitVarExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
}
#endif

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace Cas_testSOD
