#include "cas_test/OTHER/__OtherServiceBindings.h"
#include "cas_test/RIDER/__RiderServiceBindings.h"
#include "cas_test/SEDOV/__SedovServiceBindings.h"
#include "cas_test/SOD/__SodServiceBindings.h"
#include "eos/perfectgas/__PerfectGasServiceBindings.h"
#include "eos/perfectgas/__PerfectGasAccWithSupportServiceBindings.h"
#include "eos/perfectgas/__PerfectGasNAccServiceBindings.h"
#include "eos/perfectgas/__PerfectGasPAccServiceBindings.h"
#include "eos/perfectgas/__PerfectGasWithSupportServiceBindings.h"
#include "eos/stiffenedgas/__StiffenedGasServiceBindings.h"
#include "eos/stiffenedgas/__StiffenedGasAccServiceBindings.h"
#include "mahyco/__MahycoModuleBindings.h"
#include "remap/adi/__RemapADIServiceBindings.h"
#include "remap/ale/__RemapALEServiceBindings.h"

void bind_submodules(py::module __attribute__((unused)) &m) {
  py::module_ arcpy = py::module_::import("arcpy");
  Cas_testOTHER::bind_cas_test_other_other(m);
  Cas_testRIDER::bind_cas_test_rider_rider(m);
  Cas_testSEDOV::bind_cas_test_sedov_sedov(m);
  Cas_testSOD::bind_cas_test_sod_sod(m);
  EosPerfectgas::bind_eos_perfectgas_perfectgas(m);
  EosPerfectgas::bind_eos_perfectgas_perfectgasaccwithsupport(m);
  EosPerfectgas::bind_eos_perfectgas_perfectgasnacc(m);
  EosPerfectgas::bind_eos_perfectgas_perfectgaspacc(m);
  EosPerfectgas::bind_eos_perfectgas_perfectgaswithsupport(m);
  EosStiffenedgas::bind_eos_stiffenedgas_stiffenedgas(m);
  EosStiffenedgas::bind_eos_stiffenedgas_stiffenedgasacc(m);
  Mahyco::bind_mahyco_mahyco(m);
  RemapAdi::bind_remap_adi_remapadi(m);
  RemapAle::bind_remap_ale_remapale(m);
}
