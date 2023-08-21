#ifndef CAS_TEST_SEDOV___SEDOVSERVICEBINDINGS_H
#define CAS_TEST_SEDOV___SEDOVSERVICEBINDINGS_H

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
#include "cas_test/SEDOV/__SedovServiceContexts.h"
#include "SciHook.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

using namespace Arcane;
using namespace Arcane::Materials;
namespace Cas_testSEDOV {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void bind_cas_test_sedov_sedov(py::module __attribute__((unused)) &m)
{
  #if not defined(SCIHOOK_CAS_TEST_SEDOV_SEDOV_DISABLED)
  auto sub_cas_test_sedov_sedov = m.def_submodule("cas_test_sedov_sedov", "Bindings for Sedov");
  #if not defined(SCIHOOK_CAS_TEST_SEDOV_SEDOV_INITMATMONO_DISABLED)
  pybind11::class_<Cas_testSEDOV::SedovInitMatMonoExecutionContext, std::shared_ptr<Cas_testSEDOV::SedovInitMatMonoExecutionContext>, SciHook::SciHookExecutionContext>(sub_cas_test_sedov_sedov, "SedovInitMatMonoExecutionContext")
    .def_property_readonly("dim", &Cas_testSEDOV::SedovInitMatMonoExecutionContext::get_dim)
    .def_property_readonly("materiau", &Cas_testSEDOV::SedovInitMatMonoExecutionContext::get_m_materiau)
    .def("__str__", [](Cas_testSEDOV::SedovInitMatMonoExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Cas_testSEDOV::SedovInitMatMonoExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_CAS_TEST_SEDOV_SEDOV_INITMATMONO_DISABLED)
  #if not defined(SCIHOOK_CAS_TEST_SEDOV_SEDOV_INITVARMONO_DISABLED)
  pybind11::class_<Cas_testSEDOV::SedovInitVarMonoExecutionContext, std::shared_ptr<Cas_testSEDOV::SedovInitVarMonoExecutionContext>, SciHook::SciHookExecutionContext>(sub_cas_test_sedov_sedov, "SedovInitVarMonoExecutionContext")
    .def_property_readonly("dim", &Cas_testSEDOV::SedovInitVarMonoExecutionContext::get_dim)
    .def_property_readonly("node_coord", &Cas_testSEDOV::SedovInitVarMonoExecutionContext::get_m_node_coord)
    .def_property_readonly("cell_volume", &Cas_testSEDOV::SedovInitVarMonoExecutionContext::get_m_cell_volume)
    .def_property_readonly("density", &Cas_testSEDOV::SedovInitVarMonoExecutionContext::get_m_density)
    .def_property_readonly("pressure", &Cas_testSEDOV::SedovInitVarMonoExecutionContext::get_m_pressure)
    .def_property_readonly("fracvol", &Cas_testSEDOV::SedovInitVarMonoExecutionContext::get_m_fracvol)
    .def_property_readonly("mass_fraction", &Cas_testSEDOV::SedovInitVarMonoExecutionContext::get_m_mass_fraction)
    .def_property_readonly("velocity", &Cas_testSEDOV::SedovInitVarMonoExecutionContext::get_m_velocity)
    .def_property_readonly("internal_energy", &Cas_testSEDOV::SedovInitVarMonoExecutionContext::get_m_internal_energy)
    .def("__str__", [](Cas_testSEDOV::SedovInitVarMonoExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Cas_testSEDOV::SedovInitVarMonoExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_CAS_TEST_SEDOV_SEDOV_INITVARMONO_DISABLED)
  #if not defined(SCIHOOK_CAS_TEST_SEDOV_SEDOV_INITMAT_DISABLED)
  pybind11::class_<Cas_testSEDOV::SedovInitMatExecutionContext, std::shared_ptr<Cas_testSEDOV::SedovInitMatExecutionContext>, SciHook::SciHookExecutionContext>(sub_cas_test_sedov_sedov, "SedovInitMatExecutionContext")
    .def_property_readonly("dim", &Cas_testSEDOV::SedovInitMatExecutionContext::get_dim)
    .def_property_readonly("node_coord", &Cas_testSEDOV::SedovInitMatExecutionContext::get_m_node_coord)
    .def_property_readonly("materiau", &Cas_testSEDOV::SedovInitMatExecutionContext::get_m_materiau)
    .def("__str__", [](Cas_testSEDOV::SedovInitMatExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Cas_testSEDOV::SedovInitMatExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_CAS_TEST_SEDOV_SEDOV_INITMAT_DISABLED)
  #if not defined(SCIHOOK_CAS_TEST_SEDOV_SEDOV_INITVAR_DISABLED)
  pybind11::class_<Cas_testSEDOV::SedovInitVarExecutionContext, std::shared_ptr<Cas_testSEDOV::SedovInitVarExecutionContext>, SciHook::SciHookExecutionContext>(sub_cas_test_sedov_sedov, "SedovInitVarExecutionContext")
    .def_property_readonly("dim", &Cas_testSEDOV::SedovInitVarExecutionContext::get_dim)
    .def_property_readonly("node_coord", &Cas_testSEDOV::SedovInitVarExecutionContext::get_m_node_coord)
    .def_property_readonly("cell_volume", &Cas_testSEDOV::SedovInitVarExecutionContext::get_m_cell_volume)
    .def_property_readonly("density", &Cas_testSEDOV::SedovInitVarExecutionContext::get_m_density)
    .def_property_readonly("pressure", &Cas_testSEDOV::SedovInitVarExecutionContext::get_m_pressure)
    .def_property_readonly("fracvol", &Cas_testSEDOV::SedovInitVarExecutionContext::get_m_fracvol)
    .def_property_readonly("mass_fraction", &Cas_testSEDOV::SedovInitVarExecutionContext::get_m_mass_fraction)
    .def_property_readonly("velocity", &Cas_testSEDOV::SedovInitVarExecutionContext::get_m_velocity)
    .def_property_readonly("internal_energy", &Cas_testSEDOV::SedovInitVarExecutionContext::get_m_internal_energy)
    .def("__str__", [](Cas_testSEDOV::SedovInitVarExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Cas_testSEDOV::SedovInitVarExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_CAS_TEST_SEDOV_SEDOV_INITVAR_DISABLED)
  #endif // not defined(SCIHOOK_CAS_TEST_SEDOV_SEDOV_DISABLED)
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace Cas_testSEDOV

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // CAS_TEST_SEDOV___SEDOVSERVICEBINDINGS_H
