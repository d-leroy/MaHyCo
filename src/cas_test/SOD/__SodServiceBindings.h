#ifndef CAS_TEST_SOD___SODSERVICEBINDINGS_H
#define CAS_TEST_SOD___SODSERVICEBINDINGS_H

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

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
#include "scihook/scihookdefs.h"
#include "cas_test/SOD/__SodServiceContexts.h"
#include "SciHook.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

using namespace Arcane;
using namespace Arcane::Materials;
namespace Cas_testSOD {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void bind_cas_test_sod_sod(py::module __attribute__((unused)) &m)
{
  #if not defined(SCIHOOK_CAS_TEST_SOD_SOD_DISABLED)
  auto sub_cas_test_sod_sod = m.def_submodule("cas_test_sod_sod", "Bindings for Sod");
  #if not defined(SCIHOOK_CAS_TEST_SOD_SOD_INITMATMONO_DISABLED)
  pybind11::class_<Cas_testSOD::SodInitMatMonoExecutionContext, std::shared_ptr<Cas_testSOD::SodInitMatMonoExecutionContext>, SciHook::SciHookExecutionContext>(sub_cas_test_sod_sod, "SodInitMatMonoExecutionContext")
    .def_property_readonly("dim", &Cas_testSOD::SodInitMatMonoExecutionContext::get_dim)
    .def_property_readonly("materiau", &Cas_testSOD::SodInitMatMonoExecutionContext::get_materiau)
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
  #endif // not defined(SCIHOOK_CAS_TEST_SOD_SOD_INITMATMONO_DISABLED)
  #if not defined(SCIHOOK_CAS_TEST_SOD_SOD_INITVARMONO_DISABLED)
  pybind11::class_<Cas_testSOD::SodInitVarMonoExecutionContext, std::shared_ptr<Cas_testSOD::SodInitVarMonoExecutionContext>, SciHook::SciHookExecutionContext>(sub_cas_test_sod_sod, "SodInitVarMonoExecutionContext")
    .def_property_readonly("dim", &Cas_testSOD::SodInitVarMonoExecutionContext::get_dim)
    .def_property_readonly("cell_coord", &Cas_testSOD::SodInitVarMonoExecutionContext::get_cell_coord)
    .def_property_readonly("density", &Cas_testSOD::SodInitVarMonoExecutionContext::get_density)
    .def_property_readonly("pressure", &Cas_testSOD::SodInitVarMonoExecutionContext::get_pressure)
    .def_property_readonly("fracvol", &Cas_testSOD::SodInitVarMonoExecutionContext::get_fracvol)
    .def_property_readonly("mass_fraction", &Cas_testSOD::SodInitVarMonoExecutionContext::get_mass_fraction)
    .def_property_readonly("velocity", &Cas_testSOD::SodInitVarMonoExecutionContext::get_velocity)
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
  #endif // not defined(SCIHOOK_CAS_TEST_SOD_SOD_INITVARMONO_DISABLED)
  #if not defined(SCIHOOK_CAS_TEST_SOD_SOD_INITMAT_DISABLED)
  pybind11::class_<Cas_testSOD::SodInitMatExecutionContext, std::shared_ptr<Cas_testSOD::SodInitMatExecutionContext>, SciHook::SciHookExecutionContext>(sub_cas_test_sod_sod, "SodInitMatExecutionContext")
    .def_property_readonly("dim", &Cas_testSOD::SodInitMatExecutionContext::get_dim)
    .def_property_readonly("cell_coord", &Cas_testSOD::SodInitMatExecutionContext::get_cell_coord)
    .def_property_readonly("materiau", &Cas_testSOD::SodInitMatExecutionContext::get_materiau)
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
  #endif // not defined(SCIHOOK_CAS_TEST_SOD_SOD_INITMAT_DISABLED)
  #if not defined(SCIHOOK_CAS_TEST_SOD_SOD_INITVAR_DISABLED)
  pybind11::class_<Cas_testSOD::SodInitVarExecutionContext, std::shared_ptr<Cas_testSOD::SodInitVarExecutionContext>, SciHook::SciHookExecutionContext>(sub_cas_test_sod_sod, "SodInitVarExecutionContext")
    .def_property_readonly("dim", &Cas_testSOD::SodInitVarExecutionContext::get_dim)
    .def_property_readonly("cell_coord", &Cas_testSOD::SodInitVarExecutionContext::get_cell_coord)
    .def_property_readonly("density", &Cas_testSOD::SodInitVarExecutionContext::get_density)
    .def_property_readonly("pressure", &Cas_testSOD::SodInitVarExecutionContext::get_pressure)
    .def_property_readonly("fracvol", &Cas_testSOD::SodInitVarExecutionContext::get_fracvol)
    .def_property_readonly("mass_fraction", &Cas_testSOD::SodInitVarExecutionContext::get_mass_fraction)
    .def_property_readonly("velocity", &Cas_testSOD::SodInitVarExecutionContext::get_velocity)
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
  #endif // not defined(SCIHOOK_CAS_TEST_SOD_SOD_INITVAR_DISABLED)
  #endif // not defined(SCIHOOK_CAS_TEST_SOD_SOD_DISABLED)
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace Cas_testSOD

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // CAS_TEST_SOD___SODSERVICEBINDINGS_H
