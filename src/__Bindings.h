#include "SciHook.h"

void
try_import(const char *module_name) {
  try {
    pybind11::module_::import(module_name);
  } catch (pybind11::error_already_set &e) {
    std::cout << e.what() << '\n';
  }
}

void
import_modules(pybind11::module_ __attribute__((unused)) m) {
  try_import("cas_testother_other");
  try_import("cas_testrider_rider");
  try_import("cas_testsedov_sedov");
  try_import("cas_testsod_sod");
  try_import("eosperfectgas_perfectgas");
  try_import("eosstiffenedgas_stiffenedgas");
  try_import("mahyco_mahyco");
  try_import("remapadi_remapadi");
}
