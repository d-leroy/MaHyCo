#include <SciHook.h>

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
  try_import("eosperfectgas_perfectgas");
  try_import("eosstiffenedgas_stiffenedgas");
}
