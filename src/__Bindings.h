#include "mahyco/__MahycoModuleBindings.h"
#include "cas_test/OTHER/__OtherServiceBindings.h"
#include "cas_test/RIDER/__RiderServiceBindings.h"
#include "cas_test/SOD/__SodServiceBindings.h"
#include "cas_test/SEDOV/__SedovServiceBindings.h"
#include "eos/perfectgas/__PerfectGasServiceBindings.h"
#include "eos/stiffenedgas/__StiffenedGasServiceBindings.h"
#include "remap/adi/__RemapADIServiceBindings.h"

void bind_submodules(py::module __attribute__((unused)) &m) {
  py::module_ arcpy = py::module_::import("arcpy");
  Mahyco::bind_mahyco_mahyco(m);
  Cas_testOTHER::bind_cas_test_other_other(m);
  Cas_testRIDER::bind_cas_test_rider_rider(m);
  Cas_testSOD::bind_cas_test_sod_sod(m);
  Cas_testSEDOV::bind_cas_test_sedov_sedov(m);
  EosPerfectgas::bind_eos_perfectgas_perfectgas(m);
  EosStiffenedgas::bind_eos_stiffenedgas_stiffenedgas(m);
  RemapAdi::bind_remap_adi_remapadi(m);
}
