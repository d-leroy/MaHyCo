#ifndef CAS_TEST_RIDER___RIDERSERVICEBINDINGS_H
#define CAS_TEST_RIDER___RIDERSERVICEBINDINGS_H

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
#include "cas_test/RIDER/__RiderServiceContexts.h"
#include "SciHook.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

using namespace Arcane;
using namespace Arcane::Materials;
namespace Cas_testRIDER {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void bind_cas_test_rider_rider(py::module __attribute__((unused)) &m)
{
  #if not defined(SCIHOOK_CAS_TEST_RIDER_RIDER_DISABLED)
  auto sub_cas_test_rider_rider = m.def_submodule("cas_test_rider_rider", "Bindings for Rider");
  #if not defined(SCIHOOK_CAS_TEST_RIDER_RIDER_INITMATMONO_DISABLED)
  pybind11::class_<Cas_testRIDER::RiderInitMatMonoExecutionContext, std::shared_ptr<Cas_testRIDER::RiderInitMatMonoExecutionContext>, SciHook::SciHookExecutionContext>(sub_cas_test_rider_rider, "RiderInitMatMonoExecutionContext")
    .def_property_readonly("dim", &Cas_testRIDER::RiderInitMatMonoExecutionContext::get_dim)
    .def_property_readonly("materiau", &Cas_testRIDER::RiderInitMatMonoExecutionContext::get_m_materiau)
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
  #endif // not defined(SCIHOOK_CAS_TEST_RIDER_RIDER_INITMATMONO_DISABLED)
  #if not defined(SCIHOOK_CAS_TEST_RIDER_RIDER_INITVARMONO_DISABLED)
  pybind11::class_<Cas_testRIDER::RiderInitVarMonoExecutionContext, std::shared_ptr<Cas_testRIDER::RiderInitVarMonoExecutionContext>, SciHook::SciHookExecutionContext>(sub_cas_test_rider_rider, "RiderInitVarMonoExecutionContext")
    .def_property_readonly("dim", &Cas_testRIDER::RiderInitVarMonoExecutionContext::get_dim)
    .def_property_readonly("node_coord", &Cas_testRIDER::RiderInitVarMonoExecutionContext::get_m_node_coord)
    .def_property_readonly("pseudo_viscosity", &Cas_testRIDER::RiderInitVarMonoExecutionContext::get_m_pseudo_viscosity)
    .def_property_readonly("density", &Cas_testRIDER::RiderInitVarMonoExecutionContext::get_m_density)
    .def_property_readonly("pressure", &Cas_testRIDER::RiderInitVarMonoExecutionContext::get_m_pressure)
    .def_property_readonly("fracvol", &Cas_testRIDER::RiderInitVarMonoExecutionContext::get_m_fracvol)
    .def_property_readonly("mass_fraction", &Cas_testRIDER::RiderInitVarMonoExecutionContext::get_m_mass_fraction)
    .def_property_readonly("velocity_n", &Cas_testRIDER::RiderInitVarMonoExecutionContext::get_m_velocity_n)
    .def_property_readonly("velocity", &Cas_testRIDER::RiderInitVarMonoExecutionContext::get_m_velocity)
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
  #endif // not defined(SCIHOOK_CAS_TEST_RIDER_RIDER_INITVARMONO_DISABLED)
  #if not defined(SCIHOOK_CAS_TEST_RIDER_RIDER_INITMAT_DISABLED)
  pybind11::class_<Cas_testRIDER::RiderInitMatExecutionContext, std::shared_ptr<Cas_testRIDER::RiderInitMatExecutionContext>, SciHook::SciHookExecutionContext>(sub_cas_test_rider_rider, "RiderInitMatExecutionContext")
    .def_property_readonly("dim", &Cas_testRIDER::RiderInitMatExecutionContext::get_dim)
    .def_property_readonly("node_coord", &Cas_testRIDER::RiderInitMatExecutionContext::get_m_node_coord)
    .def_property_readonly("materiau", &Cas_testRIDER::RiderInitMatExecutionContext::get_m_materiau)
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
  #endif // not defined(SCIHOOK_CAS_TEST_RIDER_RIDER_INITMAT_DISABLED)
  #if not defined(SCIHOOK_CAS_TEST_RIDER_RIDER_INITVAR_DISABLED)
  pybind11::class_<Cas_testRIDER::RiderInitVarExecutionContext, std::shared_ptr<Cas_testRIDER::RiderInitVarExecutionContext>, SciHook::SciHookExecutionContext>(sub_cas_test_rider_rider, "RiderInitVarExecutionContext")
    .def_property_readonly("dim", &Cas_testRIDER::RiderInitVarExecutionContext::get_dim)
    .def_property_readonly("node_coord", &Cas_testRIDER::RiderInitVarExecutionContext::get_m_node_coord)
    .def_property_readonly("pseudo_viscosity", &Cas_testRIDER::RiderInitVarExecutionContext::get_m_pseudo_viscosity)
    .def_property_readonly("density", &Cas_testRIDER::RiderInitVarExecutionContext::get_m_density)
    .def_property_readonly("pressure", &Cas_testRIDER::RiderInitVarExecutionContext::get_m_pressure)
    .def_property_readonly("fracvol", &Cas_testRIDER::RiderInitVarExecutionContext::get_m_fracvol)
    .def_property_readonly("mass_fraction", &Cas_testRIDER::RiderInitVarExecutionContext::get_m_mass_fraction)
    .def_property_readonly("velocity_n", &Cas_testRIDER::RiderInitVarExecutionContext::get_m_velocity_n)
    .def_property_readonly("velocity", &Cas_testRIDER::RiderInitVarExecutionContext::get_m_velocity)
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
  #endif // not defined(SCIHOOK_CAS_TEST_RIDER_RIDER_INITVAR_DISABLED)
  #endif // not defined(SCIHOOK_CAS_TEST_RIDER_RIDER_DISABLED)
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace Cas_testRIDER

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // CAS_TEST_RIDER___RIDERSERVICEBINDINGS_H
