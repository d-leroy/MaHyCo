#ifndef CAS_TEST_OTHER___OTHERSERVICEBINDINGS_H
#define CAS_TEST_OTHER___OTHERSERVICEBINDINGS_H

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
#include "cas_test/OTHER/__OtherServiceContexts.h"
#include "SciHook.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

using namespace Arcane;
using namespace Arcane::Materials;
namespace Cas_testOTHER {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void bind_cas_test_other_other(py::module __attribute__((unused)) &m)
{
  #if not defined(SCIHOOK_CAS_TEST_OTHER_OTHER_DISABLED)
  auto sub_cas_test_other_other = m.def_submodule("cas_test_other_other", "Bindings for Other");
  #if not defined(SCIHOOK_CAS_TEST_OTHER_OTHER_INITMATMONO_DISABLED)
  pybind11::class_<Cas_testOTHER::OtherInitMatMonoExecutionContext, std::shared_ptr<Cas_testOTHER::OtherInitMatMonoExecutionContext>, SciHook::SciHookExecutionContext>(sub_cas_test_other_other, "OtherInitMatMonoExecutionContext")
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
  #endif // not defined(SCIHOOK_CAS_TEST_OTHER_OTHER_INITMATMONO_DISABLED)
  #if not defined(SCIHOOK_CAS_TEST_OTHER_OTHER_INITVARMONO_DISABLED)
  pybind11::class_<Cas_testOTHER::OtherInitVarMonoExecutionContext, std::shared_ptr<Cas_testOTHER::OtherInitVarMonoExecutionContext>, SciHook::SciHookExecutionContext>(sub_cas_test_other_other, "OtherInitVarMonoExecutionContext")
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
  #endif // not defined(SCIHOOK_CAS_TEST_OTHER_OTHER_INITVARMONO_DISABLED)
  #if not defined(SCIHOOK_CAS_TEST_OTHER_OTHER_INITMAT_DISABLED)
  pybind11::class_<Cas_testOTHER::OtherInitMatExecutionContext, std::shared_ptr<Cas_testOTHER::OtherInitMatExecutionContext>, SciHook::SciHookExecutionContext>(sub_cas_test_other_other, "OtherInitMatExecutionContext")
    .def_property_readonly("dim", &Cas_testOTHER::OtherInitMatExecutionContext::get_dim)
    .def_property_readonly("cell_coord", &Cas_testOTHER::OtherInitMatExecutionContext::get_cell_coord)
    .def_property_readonly("materiau", &Cas_testOTHER::OtherInitMatExecutionContext::get_materiau)
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
  #endif // not defined(SCIHOOK_CAS_TEST_OTHER_OTHER_INITMAT_DISABLED)
  #if not defined(SCIHOOK_CAS_TEST_OTHER_OTHER_INITVAR_DISABLED)
  pybind11::class_<Cas_testOTHER::OtherInitVarExecutionContext, std::shared_ptr<Cas_testOTHER::OtherInitVarExecutionContext>, SciHook::SciHookExecutionContext>(sub_cas_test_other_other, "OtherInitVarExecutionContext")
    .def_property_readonly("dim", &Cas_testOTHER::OtherInitVarExecutionContext::get_dim)
    .def_property_readonly("cell_coord", &Cas_testOTHER::OtherInitVarExecutionContext::get_cell_coord)
    .def_property_readonly("pseudo_viscosity", &Cas_testOTHER::OtherInitVarExecutionContext::get_pseudo_viscosity)
    .def_property_readonly("density", &Cas_testOTHER::OtherInitVarExecutionContext::get_density)
    .def_property_readonly("pressure", &Cas_testOTHER::OtherInitVarExecutionContext::get_pressure)
    .def_property_readonly("internal_energy", &Cas_testOTHER::OtherInitVarExecutionContext::get_internal_energy)
    .def_property_readonly("fracvol", &Cas_testOTHER::OtherInitVarExecutionContext::get_fracvol)
    .def_property_readonly("mass_fraction", &Cas_testOTHER::OtherInitVarExecutionContext::get_mass_fraction)
    .def_property_readonly("velocity_n", &Cas_testOTHER::OtherInitVarExecutionContext::get_velocity_n)
    .def_property_readonly("velocity", &Cas_testOTHER::OtherInitVarExecutionContext::get_velocity)
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
  #endif // not defined(SCIHOOK_CAS_TEST_OTHER_OTHER_INITVAR_DISABLED)
  #endif // not defined(SCIHOOK_CAS_TEST_OTHER_OTHER_DISABLED)
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace Cas_testOTHER

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // CAS_TEST_OTHER___OTHERSERVICEBINDINGS_H
