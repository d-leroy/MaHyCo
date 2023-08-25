#ifndef MAHYCO___MAHYCOMODULEBINDINGS_H
#define MAHYCO___MAHYCOMODULEBINDINGS_H

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
#include "mahyco/__MahycoModuleContexts.h"
#include "SciHook.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

using namespace Arcane;
using namespace Arcane::Materials;
namespace Mahyco {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void bind_mahyco_mahyco(py::module __attribute__((unused)) &m)
{
  #if not defined(SCIHOOK_MAHYCO_MAHYCO_DISABLED)
  auto sub_mahyco_mahyco = m.def_submodule("mahyco_mahyco", "Bindings for Mahyco");
  #if not defined(SCIHOOK_MAHYCO_MAHYCO_ALLOCCQS_DISABLED)
  pybind11::class_<Mahyco::MahycoAllocCqsExecutionContext, std::shared_ptr<Mahyco::MahycoAllocCqsExecutionContext>, SciHook::SciHookExecutionContext>(sub_mahyco_mahyco, "MahycoAllocCqsExecutionContext")
    .def_property_readonly("cell_cqs", &Mahyco::MahycoAllocCqsExecutionContext::get_m_cell_cqs)
    .def_property_readonly("cell_cqs_n", &Mahyco::MahycoAllocCqsExecutionContext::get_m_cell_cqs_n)
    .def("__str__", [](Mahyco::MahycoAllocCqsExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Mahyco::MahycoAllocCqsExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_MAHYCO_MAHYCO_ALLOCCQS_DISABLED)
  #if not defined(SCIHOOK_MAHYCO_MAHYCO_INITHYDROVAR_DISABLED)
  pybind11::class_<Mahyco::MahycoInitHydroVarExecutionContext, std::shared_ptr<Mahyco::MahycoInitHydroVarExecutionContext>, SciHook::SciHookExecutionContext>(sub_mahyco_mahyco, "MahycoInitHydroVarExecutionContext")
    .def_property_readonly("cell_cqs", &Mahyco::MahycoInitHydroVarExecutionContext::get_m_cell_cqs)
    .def_property_readonly("mass_fraction", &Mahyco::MahycoInitHydroVarExecutionContext::get_m_mass_fraction)
    .def_property_readonly("node_coord", &Mahyco::MahycoInitHydroVarExecutionContext::get_m_node_coord)
    .def_property_readonly("euler_volume", &Mahyco::MahycoInitHydroVarExecutionContext::get_m_euler_volume)
    .def_property_readonly("cell_volume", &Mahyco::MahycoInitHydroVarExecutionContext::get_m_cell_volume)
    .def_property_readonly("internal_energy", &Mahyco::MahycoInitHydroVarExecutionContext::get_m_internal_energy)
    .def_property_readonly("sound_speed", &Mahyco::MahycoInitHydroVarExecutionContext::get_m_sound_speed)
    .def("__str__", [](Mahyco::MahycoInitHydroVarExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Mahyco::MahycoInitHydroVarExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_MAHYCO_MAHYCO_INITHYDROVAR_DISABLED)
  #if not defined(SCIHOOK_MAHYCO_MAHYCO_HYDROSTARTINITENVANDMAT_DISABLED)
  pybind11::class_<Mahyco::MahycoHydroStartInitEnvAndMatExecutionContext, std::shared_ptr<Mahyco::MahycoHydroStartInitEnvAndMatExecutionContext>, SciHook::SciHookExecutionContext>(sub_mahyco_mahyco, "MahycoHydroStartInitEnvAndMatExecutionContext")
    .def_property_readonly("materiau", &Mahyco::MahycoHydroStartInitEnvAndMatExecutionContext::get_m_materiau)
    .def_property_readonly("sens_projection", &Mahyco::MahycoHydroStartInitEnvAndMatExecutionContext::get_m_sens_projection)
    .def_property_readonly("node_coord", &Mahyco::MahycoHydroStartInitEnvAndMatExecutionContext::get_m_node_coord)
    .def_property_readonly("cell_coord", &Mahyco::MahycoHydroStartInitEnvAndMatExecutionContext::get_m_cell_coord)
    .def("__str__", [](Mahyco::MahycoHydroStartInitEnvAndMatExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Mahyco::MahycoHydroStartInitEnvAndMatExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_MAHYCO_MAHYCO_HYDROSTARTINITENVANDMAT_DISABLED)
  #if not defined(SCIHOOK_MAHYCO_MAHYCO_PREPAREFACEGROUPFORBC_DISABLED)
  pybind11::class_<Mahyco::MahycoPrepareFaceGroupForBcExecutionContext, std::shared_ptr<Mahyco::MahycoPrepareFaceGroupForBcExecutionContext>, SciHook::SciHookExecutionContext>(sub_mahyco_mahyco, "MahycoPrepareFaceGroupForBcExecutionContext")
    .def_property_readonly("node_coord", &Mahyco::MahycoPrepareFaceGroupForBcExecutionContext::get_m_node_coord)
    .def_property_readonly("is_dir_face", &Mahyco::MahycoPrepareFaceGroupForBcExecutionContext::get_m_is_dir_face)
    .def("__str__", [](Mahyco::MahycoPrepareFaceGroupForBcExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Mahyco::MahycoPrepareFaceGroupForBcExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_MAHYCO_MAHYCO_PREPAREFACEGROUPFORBC_DISABLED)
  #if not defined(SCIHOOK_MAHYCO_MAHYCO_COMPUTECELLMASS_DISABLED)
  pybind11::class_<Mahyco::MahycoComputeCellMassExecutionContext, std::shared_ptr<Mahyco::MahycoComputeCellMassExecutionContext>, SciHook::SciHookExecutionContext>(sub_mahyco_mahyco, "MahycoComputeCellMassExecutionContext")
    .def_property_readonly("density", &Mahyco::MahycoComputeCellMassExecutionContext::get_m_density)
    .def_property_readonly("cell_volume", &Mahyco::MahycoComputeCellMassExecutionContext::get_m_cell_volume)
    .def_property_readonly("mass_fraction", &Mahyco::MahycoComputeCellMassExecutionContext::get_m_mass_fraction)
    .def_property_readonly("cell_mass", &Mahyco::MahycoComputeCellMassExecutionContext::get_m_cell_mass)
    .def("__str__", [](Mahyco::MahycoComputeCellMassExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Mahyco::MahycoComputeCellMassExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_MAHYCO_MAHYCO_COMPUTECELLMASS_DISABLED)
  #if not defined(SCIHOOK_MAHYCO_MAHYCO_COMPUTENODEMASS_DISABLED)
  pybind11::class_<Mahyco::MahycoComputeNodeMassExecutionContext, std::shared_ptr<Mahyco::MahycoComputeNodeMassExecutionContext>, SciHook::SciHookExecutionContext>(sub_mahyco_mahyco, "MahycoComputeNodeMassExecutionContext")
    .def_property_readonly("cell_mass", &Mahyco::MahycoComputeNodeMassExecutionContext::get_m_cell_mass)
    .def_property_readonly("node_mass", &Mahyco::MahycoComputeNodeMassExecutionContext::get_m_node_mass)
    .def("__str__", [](Mahyco::MahycoComputeNodeMassExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Mahyco::MahycoComputeNodeMassExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_MAHYCO_MAHYCO_COMPUTENODEMASS_DISABLED)
  #if not defined(SCIHOOK_MAHYCO_MAHYCO_CONTINUEFORITERATIONDT_DISABLED)
  pybind11::class_<Mahyco::MahycoContinueForIterationDtExecutionContext, std::shared_ptr<Mahyco::MahycoContinueForIterationDtExecutionContext>, SciHook::SciHookExecutionContext>(sub_mahyco_mahyco, "MahycoContinueForIterationDtExecutionContext")
    .def_property_readonly("old_deltat", &Mahyco::MahycoContinueForIterationDtExecutionContext::get_m_old_deltat)
    .def("__str__", [](Mahyco::MahycoContinueForIterationDtExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Mahyco::MahycoContinueForIterationDtExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_MAHYCO_MAHYCO_CONTINUEFORITERATIONDT_DISABLED)
  #if not defined(SCIHOOK_MAHYCO_MAHYCO_SAVEVALUESATN_DISABLED)
  pybind11::class_<Mahyco::MahycoSaveValuesAtNExecutionContext, std::shared_ptr<Mahyco::MahycoSaveValuesAtNExecutionContext>, SciHook::SciHookExecutionContext>(sub_mahyco_mahyco, "MahycoSaveValuesAtNExecutionContext")
    .def_property_readonly("old_deltat", &Mahyco::MahycoSaveValuesAtNExecutionContext::get_m_old_deltat)
    .def_property_readonly("pseudo_viscosity", &Mahyco::MahycoSaveValuesAtNExecutionContext::get_m_pseudo_viscosity)
    .def_property_readonly("pressure", &Mahyco::MahycoSaveValuesAtNExecutionContext::get_m_pressure)
    .def_property_readonly("cell_volume", &Mahyco::MahycoSaveValuesAtNExecutionContext::get_m_cell_volume)
    .def_property_readonly("density", &Mahyco::MahycoSaveValuesAtNExecutionContext::get_m_density)
    .def_property_readonly("internal_energy", &Mahyco::MahycoSaveValuesAtNExecutionContext::get_m_internal_energy)
    .def_property_readonly("cell_cqs", &Mahyco::MahycoSaveValuesAtNExecutionContext::get_m_cell_cqs)
    .def_property_readonly("velocity", &Mahyco::MahycoSaveValuesAtNExecutionContext::get_m_velocity)
    .def_property_readonly("node_coord_0", &Mahyco::MahycoSaveValuesAtNExecutionContext::get_m_node_coord_0)
    .def_property_readonly("pseudo_viscosity_nmoins1", &Mahyco::MahycoSaveValuesAtNExecutionContext::get_m_pseudo_viscosity_nmoins1)
    .def_property_readonly("pressure_n", &Mahyco::MahycoSaveValuesAtNExecutionContext::get_m_pressure_n)
    .def_property_readonly("cell_volume_n", &Mahyco::MahycoSaveValuesAtNExecutionContext::get_m_cell_volume_n)
    .def_property_readonly("density_n", &Mahyco::MahycoSaveValuesAtNExecutionContext::get_m_density_n)
    .def_property_readonly("internal_energy_n", &Mahyco::MahycoSaveValuesAtNExecutionContext::get_m_internal_energy_n)
    .def_property_readonly("cell_cqs_n", &Mahyco::MahycoSaveValuesAtNExecutionContext::get_m_cell_cqs_n)
    .def_property_readonly("velocity_n", &Mahyco::MahycoSaveValuesAtNExecutionContext::get_m_velocity_n)
    .def_property_readonly("node_coord", &Mahyco::MahycoSaveValuesAtNExecutionContext::get_m_node_coord)
    .def_property_readonly("pseudo_viscosity_n", &Mahyco::MahycoSaveValuesAtNExecutionContext::get_m_pseudo_viscosity_n)
    .def("__str__", [](Mahyco::MahycoSaveValuesAtNExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Mahyco::MahycoSaveValuesAtNExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_MAHYCO_MAHYCO_SAVEVALUESATN_DISABLED)
  #if not defined(SCIHOOK_MAHYCO_MAHYCO_UPDATEVELOCITY_DISABLED)
  pybind11::class_<Mahyco::MahycoUpdateVelocityExecutionContext, std::shared_ptr<Mahyco::MahycoUpdateVelocityExecutionContext>, SciHook::SciHookExecutionContext>(sub_mahyco_mahyco, "MahycoUpdateVelocityExecutionContext")
    .def_property_readonly("pressure_n", &Mahyco::MahycoUpdateVelocityExecutionContext::get_m_pressure_n)
    .def_property_readonly("pseudo_viscosity_n", &Mahyco::MahycoUpdateVelocityExecutionContext::get_m_pseudo_viscosity_n)
    .def_property_readonly("cell_cqs_n", &Mahyco::MahycoUpdateVelocityExecutionContext::get_m_cell_cqs_n)
    .def_property_readonly("velocity_n", &Mahyco::MahycoUpdateVelocityExecutionContext::get_m_velocity_n)
    .def_property_readonly("velocity", &Mahyco::MahycoUpdateVelocityExecutionContext::get_m_velocity)
    .def("__str__", [](Mahyco::MahycoUpdateVelocityExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Mahyco::MahycoUpdateVelocityExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_MAHYCO_MAHYCO_UPDATEVELOCITY_DISABLED)
  #if not defined(SCIHOOK_MAHYCO_MAHYCO_APPLYBOUNDARYCONDITION_DISABLED)
  pybind11::class_<Mahyco::MahycoApplyBoundaryConditionExecutionContext, std::shared_ptr<Mahyco::MahycoApplyBoundaryConditionExecutionContext>, SciHook::SciHookExecutionContext>(sub_mahyco_mahyco, "MahycoApplyBoundaryConditionExecutionContext")
    .def_property_readonly("velocity", &Mahyco::MahycoApplyBoundaryConditionExecutionContext::get_m_velocity)
    .def("__str__", [](Mahyco::MahycoApplyBoundaryConditionExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Mahyco::MahycoApplyBoundaryConditionExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_MAHYCO_MAHYCO_APPLYBOUNDARYCONDITION_DISABLED)
  #if not defined(SCIHOOK_MAHYCO_MAHYCO_UPDATEPOSITION_DISABLED)
  pybind11::class_<Mahyco::MahycoUpdatePositionExecutionContext, std::shared_ptr<Mahyco::MahycoUpdatePositionExecutionContext>, SciHook::SciHookExecutionContext>(sub_mahyco_mahyco, "MahycoUpdatePositionExecutionContext")
    .def_property_readonly("velocity", &Mahyco::MahycoUpdatePositionExecutionContext::get_m_velocity)
    .def_property_readonly("cell_coord", &Mahyco::MahycoUpdatePositionExecutionContext::get_m_cell_coord)
    .def_property_readonly("node_coord", &Mahyco::MahycoUpdatePositionExecutionContext::get_m_node_coord)
    .def("__str__", [](Mahyco::MahycoUpdatePositionExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Mahyco::MahycoUpdatePositionExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_MAHYCO_MAHYCO_UPDATEPOSITION_DISABLED)
  #if not defined(SCIHOOK_MAHYCO_MAHYCO_UPDATEDENSITY_DISABLED)
  pybind11::class_<Mahyco::MahycoUpdateDensityExecutionContext, std::shared_ptr<Mahyco::MahycoUpdateDensityExecutionContext>, SciHook::SciHookExecutionContext>(sub_mahyco_mahyco, "MahycoUpdateDensityExecutionContext")
    .def_property_readonly("cell_mass", &Mahyco::MahycoUpdateDensityExecutionContext::get_m_cell_mass)
    .def_property_readonly("cell_volume", &Mahyco::MahycoUpdateDensityExecutionContext::get_m_cell_volume)
    .def_property_readonly("density_n", &Mahyco::MahycoUpdateDensityExecutionContext::get_m_density_n)
    .def_property_readonly("div_u", &Mahyco::MahycoUpdateDensityExecutionContext::get_m_div_u)
    .def_property_readonly("density", &Mahyco::MahycoUpdateDensityExecutionContext::get_m_density)
    .def_property_readonly("tau_density", &Mahyco::MahycoUpdateDensityExecutionContext::get_m_tau_density)
    .def("__str__", [](Mahyco::MahycoUpdateDensityExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Mahyco::MahycoUpdateDensityExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_MAHYCO_MAHYCO_UPDATEDENSITY_DISABLED)
  #if not defined(SCIHOOK_MAHYCO_MAHYCO_COMPUTEARTIFICIALVISCOSITY_DISABLED)
  pybind11::class_<Mahyco::MahycoComputeArtificialViscosityExecutionContext, std::shared_ptr<Mahyco::MahycoComputeArtificialViscosityExecutionContext>, SciHook::SciHookExecutionContext>(sub_mahyco_mahyco, "MahycoComputeArtificialViscosityExecutionContext")
    .def_property_readonly("div_u", &Mahyco::MahycoComputeArtificialViscosityExecutionContext::get_m_div_u)
    .def_property_readonly("caracteristic_length", &Mahyco::MahycoComputeArtificialViscosityExecutionContext::get_m_caracteristic_length)
    .def_property_readonly("sound_speed", &Mahyco::MahycoComputeArtificialViscosityExecutionContext::get_m_sound_speed)
    .def_property_readonly("tau_density", &Mahyco::MahycoComputeArtificialViscosityExecutionContext::get_m_tau_density)
    .def_property_readonly("fracvol", &Mahyco::MahycoComputeArtificialViscosityExecutionContext::get_m_fracvol)
    .def_property_readonly("pseudo_viscosity", &Mahyco::MahycoComputeArtificialViscosityExecutionContext::get_m_pseudo_viscosity)
    .def("__str__", [](Mahyco::MahycoComputeArtificialViscosityExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Mahyco::MahycoComputeArtificialViscosityExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_MAHYCO_MAHYCO_COMPUTEARTIFICIALVISCOSITY_DISABLED)
  #if not defined(SCIHOOK_MAHYCO_MAHYCO_REMAP_DISABLED)
  pybind11::class_<Mahyco::MahycoRemapExecutionContext, std::shared_ptr<Mahyco::MahycoRemapExecutionContext>, SciHook::SciHookExecutionContext>(sub_mahyco_mahyco, "MahycoRemapExecutionContext")
    .def_property_readonly("fracvol", &Mahyco::MahycoRemapExecutionContext::get_m_fracvol)
    .def_property_readonly("materiau", &Mahyco::MahycoRemapExecutionContext::get_m_materiau)
    .def_property_readonly("pseudo_viscosity_n", &Mahyco::MahycoRemapExecutionContext::get_m_pseudo_viscosity_n)
    .def_property_readonly("pressure_n", &Mahyco::MahycoRemapExecutionContext::get_m_pressure_n)
    .def_property_readonly("cell_volume_n", &Mahyco::MahycoRemapExecutionContext::get_m_cell_volume_n)
    .def_property_readonly("density_n", &Mahyco::MahycoRemapExecutionContext::get_m_density_n)
    .def_property_readonly("internal_energy_n", &Mahyco::MahycoRemapExecutionContext::get_m_internal_energy_n)
    .def_property_readonly("tau_density", &Mahyco::MahycoRemapExecutionContext::get_m_tau_density)
    .def("__str__", [](Mahyco::MahycoRemapExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Mahyco::MahycoRemapExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_MAHYCO_MAHYCO_REMAP_DISABLED)
  #if not defined(SCIHOOK_MAHYCO_MAHYCO_COMPUTEDELTAT_DISABLED)
  pybind11::class_<Mahyco::MahycoComputeDeltaTExecutionContext, std::shared_ptr<Mahyco::MahycoComputeDeltaTExecutionContext>, SciHook::SciHookExecutionContext>(sub_mahyco_mahyco, "MahycoComputeDeltaTExecutionContext")
    .def_property_readonly("old_deltat", &Mahyco::MahycoComputeDeltaTExecutionContext::get_m_old_deltat)
    .def("__str__", [](Mahyco::MahycoComputeDeltaTExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Mahyco::MahycoComputeDeltaTExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_MAHYCO_MAHYCO_COMPUTEDELTAT_DISABLED)
  #if not defined(SCIHOOK_MAHYCO_MAHYCO_INITGEOMETRICVALUES_DISABLED)
  pybind11::class_<Mahyco::MahycoInitGeometricValuesExecutionContext, std::shared_ptr<Mahyco::MahycoInitGeometricValuesExecutionContext>, SciHook::SciHookExecutionContext>(sub_mahyco_mahyco, "MahycoInitGeometricValuesExecutionContext")
    .def_property_readonly("cell_coord", &Mahyco::MahycoInitGeometricValuesExecutionContext::get_m_cell_coord)
    .def_property_readonly("node_coord", &Mahyco::MahycoInitGeometricValuesExecutionContext::get_m_node_coord)
    .def_property_readonly("node_coord_0", &Mahyco::MahycoInitGeometricValuesExecutionContext::get_m_node_coord_0)
    .def_property_readonly("outer_face_normal", &Mahyco::MahycoInitGeometricValuesExecutionContext::get_m_outer_face_normal)
    .def_property_readonly("face_coord", &Mahyco::MahycoInitGeometricValuesExecutionContext::get_m_face_coord)
    .def_property_readonly("face_normal", &Mahyco::MahycoInitGeometricValuesExecutionContext::get_m_face_normal)
    .def("__str__", [](Mahyco::MahycoInitGeometricValuesExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Mahyco::MahycoInitGeometricValuesExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_MAHYCO_MAHYCO_INITGEOMETRICVALUES_DISABLED)
  #if not defined(SCIHOOK_MAHYCO_MAHYCO_COMPUTEGEOMETRICVALUESAUX_DISABLED)
  pybind11::class_<Mahyco::MahycoComputeGeometricValuesAuxExecutionContext, std::shared_ptr<Mahyco::MahycoComputeGeometricValuesAuxExecutionContext>, SciHook::SciHookExecutionContext>(sub_mahyco_mahyco, "MahycoComputeGeometricValuesAuxExecutionContext")
    .def_property_readonly("fracvol", &Mahyco::MahycoComputeGeometricValuesAuxExecutionContext::get_m_fracvol)
    .def_property_readonly("velocity", &Mahyco::MahycoComputeGeometricValuesAuxExecutionContext::get_m_velocity)
    .def_property_readonly("cell_cqs", &Mahyco::MahycoComputeGeometricValuesAuxExecutionContext::get_m_cell_cqs)
    .def_property_readonly("caracteristic_length", &Mahyco::MahycoComputeGeometricValuesAuxExecutionContext::get_m_caracteristic_length)
    .def_property_readonly("node_coord", &Mahyco::MahycoComputeGeometricValuesAuxExecutionContext::get_m_node_coord)
    .def_property_readonly("cell_volume", &Mahyco::MahycoComputeGeometricValuesAuxExecutionContext::get_m_cell_volume)
    .def("__str__", [](Mahyco::MahycoComputeGeometricValuesAuxExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Mahyco::MahycoComputeGeometricValuesAuxExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_MAHYCO_MAHYCO_COMPUTEGEOMETRICVALUESAUX_DISABLED)
  #if not defined(SCIHOOK_MAHYCO_MAHYCO_UPDATEVELOCITYWITHOUTLAGRANGE_DISABLED)
  pybind11::class_<Mahyco::MahycoUpdateVelocityWithoutLagrangeExecutionContext, std::shared_ptr<Mahyco::MahycoUpdateVelocityWithoutLagrangeExecutionContext>, SciHook::SciHookExecutionContext>(sub_mahyco_mahyco, "MahycoUpdateVelocityWithoutLagrangeExecutionContext")
    .def_property_readonly("velocity_n", &Mahyco::MahycoUpdateVelocityWithoutLagrangeExecutionContext::get_m_velocity_n)
    .def_property_readonly("velocity", &Mahyco::MahycoUpdateVelocityWithoutLagrangeExecutionContext::get_m_velocity)
    .def("__str__", [](Mahyco::MahycoUpdateVelocityWithoutLagrangeExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Mahyco::MahycoUpdateVelocityWithoutLagrangeExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_MAHYCO_MAHYCO_UPDATEVELOCITYWITHOUTLAGRANGE_DISABLED)
  #if not defined(SCIHOOK_MAHYCO_MAHYCO_UPDATEVELOCITYBACKWARD_DISABLED)
  pybind11::class_<Mahyco::MahycoUpdateVelocityBackwardExecutionContext, std::shared_ptr<Mahyco::MahycoUpdateVelocityBackwardExecutionContext>, SciHook::SciHookExecutionContext>(sub_mahyco_mahyco, "MahycoUpdateVelocityBackwardExecutionContext")
    .def_property_readonly("pressure_n", &Mahyco::MahycoUpdateVelocityBackwardExecutionContext::get_m_pressure_n)
    .def_property_readonly("pseudo_viscosity_n", &Mahyco::MahycoUpdateVelocityBackwardExecutionContext::get_m_pseudo_viscosity_n)
    .def_property_readonly("cell_cqs_n", &Mahyco::MahycoUpdateVelocityBackwardExecutionContext::get_m_cell_cqs_n)
    .def_property_readonly("velocity_n", &Mahyco::MahycoUpdateVelocityBackwardExecutionContext::get_m_velocity_n)
    .def("__str__", [](Mahyco::MahycoUpdateVelocityBackwardExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Mahyco::MahycoUpdateVelocityBackwardExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_MAHYCO_MAHYCO_UPDATEVELOCITYBACKWARD_DISABLED)
  #if not defined(SCIHOOK_MAHYCO_MAHYCO_UPDATEVELOCITYFORWARD_DISABLED)
  pybind11::class_<Mahyco::MahycoUpdateVelocityForwardExecutionContext, std::shared_ptr<Mahyco::MahycoUpdateVelocityForwardExecutionContext>, SciHook::SciHookExecutionContext>(sub_mahyco_mahyco, "MahycoUpdateVelocityForwardExecutionContext")
    .def_property_readonly("pressure", &Mahyco::MahycoUpdateVelocityForwardExecutionContext::get_m_pressure)
    .def_property_readonly("pseudo_viscosity", &Mahyco::MahycoUpdateVelocityForwardExecutionContext::get_m_pseudo_viscosity)
    .def_property_readonly("cell_cqs", &Mahyco::MahycoUpdateVelocityForwardExecutionContext::get_m_cell_cqs)
    .def_property_readonly("velocity", &Mahyco::MahycoUpdateVelocityForwardExecutionContext::get_m_velocity)
    .def("__str__", [](Mahyco::MahycoUpdateVelocityForwardExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Mahyco::MahycoUpdateVelocityForwardExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_MAHYCO_MAHYCO_UPDATEVELOCITYFORWARD_DISABLED)
  #if not defined(SCIHOOK_MAHYCO_MAHYCO_UPDATEFORCEANDVELOCITY_DISABLED)
  pybind11::class_<Mahyco::MahycoUpdateForceAndVelocityExecutionContext, std::shared_ptr<Mahyco::MahycoUpdateForceAndVelocityExecutionContext>, SciHook::SciHookExecutionContext>(sub_mahyco_mahyco, "MahycoUpdateForceAndVelocityExecutionContext")
    .def_property_readonly("dt", &Mahyco::MahycoUpdateForceAndVelocityExecutionContext::get_dt)
    .def_property_readonly("node_mass", &Mahyco::MahycoUpdateForceAndVelocityExecutionContext::get_m_node_mass)
    .def_property_readonly("force", &Mahyco::MahycoUpdateForceAndVelocityExecutionContext::get_m_force)
    .def_property_readonly("pressure", &Mahyco::MahycoUpdateForceAndVelocityExecutionContext::get_m_pressure)
    .def_property_readonly("pseudo_viscosity", &Mahyco::MahycoUpdateForceAndVelocityExecutionContext::get_m_pseudo_viscosity)
    .def_property_readonly("cell_cqs", &Mahyco::MahycoUpdateForceAndVelocityExecutionContext::get_m_cell_cqs)
    .def_property_readonly("velocity_in", &Mahyco::MahycoUpdateForceAndVelocityExecutionContext::get_m_velocity_in)
    .def_property_readonly("velocity_out", &Mahyco::MahycoUpdateForceAndVelocityExecutionContext::get_m_velocity_out)
    .def("__str__", [](Mahyco::MahycoUpdateForceAndVelocityExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Mahyco::MahycoUpdateForceAndVelocityExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_MAHYCO_MAHYCO_UPDATEFORCEANDVELOCITY_DISABLED)
  #if not defined(SCIHOOK_MAHYCO_MAHYCO_UPDATEENERGYANDPRESSUREBYNEWTON_DISABLED)
  pybind11::class_<Mahyco::MahycoUpdateEnergyAndPressurebyNewtonExecutionContext, std::shared_ptr<Mahyco::MahycoUpdateEnergyAndPressurebyNewtonExecutionContext>, SciHook::SciHookExecutionContext>(sub_mahyco_mahyco, "MahycoUpdateEnergyAndPressurebyNewtonExecutionContext")
    .def_property_readonly("pseudo_viscosity", &Mahyco::MahycoUpdateEnergyAndPressurebyNewtonExecutionContext::get_m_pseudo_viscosity)
    .def_property_readonly("pseudo_viscosity_n", &Mahyco::MahycoUpdateEnergyAndPressurebyNewtonExecutionContext::get_m_pseudo_viscosity_n)
    .def_property_readonly("pseudo_viscosity_nmoins1", &Mahyco::MahycoUpdateEnergyAndPressurebyNewtonExecutionContext::get_m_pseudo_viscosity_nmoins1)
    .def_property_readonly("density", &Mahyco::MahycoUpdateEnergyAndPressurebyNewtonExecutionContext::get_m_density)
    .def_property_readonly("density_n", &Mahyco::MahycoUpdateEnergyAndPressurebyNewtonExecutionContext::get_m_density_n)
    .def_property_readonly("internal_energy_n", &Mahyco::MahycoUpdateEnergyAndPressurebyNewtonExecutionContext::get_m_internal_energy_n)
    .def_property_readonly("pressure_n", &Mahyco::MahycoUpdateEnergyAndPressurebyNewtonExecutionContext::get_m_pressure_n)
    .def_property_readonly("dpde", &Mahyco::MahycoUpdateEnergyAndPressurebyNewtonExecutionContext::get_m_dpde)
    .def_property_readonly("mass_fraction", &Mahyco::MahycoUpdateEnergyAndPressurebyNewtonExecutionContext::get_m_mass_fraction)
    .def_property_readonly("velocity", &Mahyco::MahycoUpdateEnergyAndPressurebyNewtonExecutionContext::get_m_velocity)
    .def_property_readonly("velocity_n", &Mahyco::MahycoUpdateEnergyAndPressurebyNewtonExecutionContext::get_m_velocity_n)
    .def_property_readonly("cell_cqs", &Mahyco::MahycoUpdateEnergyAndPressurebyNewtonExecutionContext::get_m_cell_cqs)
    .def_property_readonly("cell_cqs_n", &Mahyco::MahycoUpdateEnergyAndPressurebyNewtonExecutionContext::get_m_cell_cqs_n)
    .def_property_readonly("cell_mass", &Mahyco::MahycoUpdateEnergyAndPressurebyNewtonExecutionContext::get_m_cell_mass)
    .def_property_readonly("internal_energy", &Mahyco::MahycoUpdateEnergyAndPressurebyNewtonExecutionContext::get_m_internal_energy)
    .def_property_readonly("pressure", &Mahyco::MahycoUpdateEnergyAndPressurebyNewtonExecutionContext::get_m_pressure)
    .def_property_readonly("sound_speed", &Mahyco::MahycoUpdateEnergyAndPressurebyNewtonExecutionContext::get_m_sound_speed)
    .def("__str__", [](Mahyco::MahycoUpdateEnergyAndPressurebyNewtonExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Mahyco::MahycoUpdateEnergyAndPressurebyNewtonExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_MAHYCO_MAHYCO_UPDATEENERGYANDPRESSUREBYNEWTON_DISABLED)
  #if not defined(SCIHOOK_MAHYCO_MAHYCO_UPDATEENERGYANDPRESSUREFORGP_DISABLED)
  pybind11::class_<Mahyco::MahycoUpdateEnergyAndPressureforGPExecutionContext, std::shared_ptr<Mahyco::MahycoUpdateEnergyAndPressureforGPExecutionContext>, SciHook::SciHookExecutionContext>(sub_mahyco_mahyco, "MahycoUpdateEnergyAndPressureforGPExecutionContext")
    .def_property_readonly("pseudo_viscosity", &Mahyco::MahycoUpdateEnergyAndPressureforGPExecutionContext::get_m_pseudo_viscosity)
    .def_property_readonly("pseudo_viscosity_n", &Mahyco::MahycoUpdateEnergyAndPressureforGPExecutionContext::get_m_pseudo_viscosity_n)
    .def_property_readonly("pseudo_viscosity_nmoins1", &Mahyco::MahycoUpdateEnergyAndPressureforGPExecutionContext::get_m_pseudo_viscosity_nmoins1)
    .def_property_readonly("density", &Mahyco::MahycoUpdateEnergyAndPressureforGPExecutionContext::get_m_density)
    .def_property_readonly("density_n", &Mahyco::MahycoUpdateEnergyAndPressureforGPExecutionContext::get_m_density_n)
    .def_property_readonly("internal_energy_n", &Mahyco::MahycoUpdateEnergyAndPressureforGPExecutionContext::get_m_internal_energy_n)
    .def_property_readonly("pressure_n", &Mahyco::MahycoUpdateEnergyAndPressureforGPExecutionContext::get_m_pressure_n)
    .def_property_readonly("mass_fraction", &Mahyco::MahycoUpdateEnergyAndPressureforGPExecutionContext::get_m_mass_fraction)
    .def_property_readonly("velocity", &Mahyco::MahycoUpdateEnergyAndPressureforGPExecutionContext::get_m_velocity)
    .def_property_readonly("velocity_n", &Mahyco::MahycoUpdateEnergyAndPressureforGPExecutionContext::get_m_velocity_n)
    .def_property_readonly("cell_cqs", &Mahyco::MahycoUpdateEnergyAndPressureforGPExecutionContext::get_m_cell_cqs)
    .def_property_readonly("cell_cqs_n", &Mahyco::MahycoUpdateEnergyAndPressureforGPExecutionContext::get_m_cell_cqs_n)
    .def_property_readonly("cell_mass", &Mahyco::MahycoUpdateEnergyAndPressureforGPExecutionContext::get_m_cell_mass)
    .def_property_readonly("internal_energy", &Mahyco::MahycoUpdateEnergyAndPressureforGPExecutionContext::get_m_internal_energy)
    .def_property_readonly("pressure", &Mahyco::MahycoUpdateEnergyAndPressureforGPExecutionContext::get_m_pressure)
    .def("__str__", [](Mahyco::MahycoUpdateEnergyAndPressureforGPExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Mahyco::MahycoUpdateEnergyAndPressureforGPExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_MAHYCO_MAHYCO_UPDATEENERGYANDPRESSUREFORGP_DISABLED)
  #if not defined(SCIHOOK_MAHYCO_MAHYCO_COMPUTEAVERAGEPRESSURE_DISABLED)
  pybind11::class_<Mahyco::MahycoComputeAveragePressureExecutionContext, std::shared_ptr<Mahyco::MahycoComputeAveragePressureExecutionContext>, SciHook::SciHookExecutionContext>(sub_mahyco_mahyco, "MahycoComputeAveragePressureExecutionContext")
    .def_property_readonly("fracvol", &Mahyco::MahycoComputeAveragePressureExecutionContext::get_m_fracvol)
    .def_property_readonly("pressure", &Mahyco::MahycoComputeAveragePressureExecutionContext::get_m_pressure)
    .def_property_readonly("sound_speed", &Mahyco::MahycoComputeAveragePressureExecutionContext::get_m_sound_speed)
    .def("__str__", [](Mahyco::MahycoComputeAveragePressureExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Mahyco::MahycoComputeAveragePressureExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_MAHYCO_MAHYCO_COMPUTEAVERAGEPRESSURE_DISABLED)
  #if not defined(SCIHOOK_MAHYCO_MAHYCO_COMPUTEVARIABLESFORREMAP_DISABLED)
  pybind11::class_<Mahyco::MahycoComputeVariablesForRemapExecutionContext, std::shared_ptr<Mahyco::MahycoComputeVariablesForRemapExecutionContext>, SciHook::SciHookExecutionContext>(sub_mahyco_mahyco, "MahycoComputeVariablesForRemapExecutionContext")
    .def_property_readonly("cell_volume", &Mahyco::MahycoComputeVariablesForRemapExecutionContext::get_m_cell_volume)
    .def_property_readonly("density", &Mahyco::MahycoComputeVariablesForRemapExecutionContext::get_m_density)
    .def_property_readonly("internal_energy", &Mahyco::MahycoComputeVariablesForRemapExecutionContext::get_m_internal_energy)
    .def_property_readonly("pseudo_viscosity", &Mahyco::MahycoComputeVariablesForRemapExecutionContext::get_m_pseudo_viscosity)
    .def_property_readonly("fracvol", &Mahyco::MahycoComputeVariablesForRemapExecutionContext::get_m_fracvol)
    .def_property_readonly("node_mass", &Mahyco::MahycoComputeVariablesForRemapExecutionContext::get_m_node_mass)
    .def_property_readonly("velocity", &Mahyco::MahycoComputeVariablesForRemapExecutionContext::get_m_velocity)
    .def_property_readonly("u_lagrange", &Mahyco::MahycoComputeVariablesForRemapExecutionContext::get_m_u_lagrange)
    .def_property_readonly("u_dual_lagrange", &Mahyco::MahycoComputeVariablesForRemapExecutionContext::get_m_u_dual_lagrange)
    .def_property_readonly("phi_lagrange", &Mahyco::MahycoComputeVariablesForRemapExecutionContext::get_m_phi_lagrange)
    .def_property_readonly("phi_dual_lagrange", &Mahyco::MahycoComputeVariablesForRemapExecutionContext::get_m_phi_dual_lagrange)
    .def("__str__", [](Mahyco::MahycoComputeVariablesForRemapExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Mahyco::MahycoComputeVariablesForRemapExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_MAHYCO_MAHYCO_COMPUTEVARIABLESFORREMAP_DISABLED)
  #if not defined(SCIHOOK_MAHYCO_MAHYCO_COMPUTEVARIABLESFORREMAPPBORN0_DISABLED)
  pybind11::class_<Mahyco::MahycoComputeVariablesForRemapPBorn0ExecutionContext, std::shared_ptr<Mahyco::MahycoComputeVariablesForRemapPBorn0ExecutionContext>, SciHook::SciHookExecutionContext>(sub_mahyco_mahyco, "MahycoComputeVariablesForRemapPBorn0ExecutionContext")
    .def_property_readonly("pseudo_viscosity", &Mahyco::MahycoComputeVariablesForRemapPBorn0ExecutionContext::get_m_pseudo_viscosity)
    .def_property_readonly("density", &Mahyco::MahycoComputeVariablesForRemapPBorn0ExecutionContext::get_m_density)
    .def_property_readonly("cell_volume", &Mahyco::MahycoComputeVariablesForRemapPBorn0ExecutionContext::get_m_cell_volume)
    .def_property_readonly("internal_energy", &Mahyco::MahycoComputeVariablesForRemapPBorn0ExecutionContext::get_m_internal_energy)
    .def_property_readonly("node_mass", &Mahyco::MahycoComputeVariablesForRemapPBorn0ExecutionContext::get_m_node_mass)
    .def_property_readonly("velocity", &Mahyco::MahycoComputeVariablesForRemapPBorn0ExecutionContext::get_m_velocity)
    .def_property_readonly("u_lagrange", &Mahyco::MahycoComputeVariablesForRemapPBorn0ExecutionContext::get_m_u_lagrange)
    .def_property_readonly("u_dual_lagrange", &Mahyco::MahycoComputeVariablesForRemapPBorn0ExecutionContext::get_m_u_dual_lagrange)
    .def_property_readonly("phi_lagrange", &Mahyco::MahycoComputeVariablesForRemapPBorn0ExecutionContext::get_m_phi_lagrange)
    .def_property_readonly("phi_dual_lagrange", &Mahyco::MahycoComputeVariablesForRemapPBorn0ExecutionContext::get_m_phi_dual_lagrange)
    .def("__str__", [](Mahyco::MahycoComputeVariablesForRemapPBorn0ExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Mahyco::MahycoComputeVariablesForRemapPBorn0ExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_MAHYCO_MAHYCO_COMPUTEVARIABLESFORREMAPPBORN0_DISABLED)
  #if not defined(SCIHOOK_MAHYCO_MAHYCO_COMPUTEFACEQUANTITESFORREMAP_DISABLED)
  pybind11::class_<Mahyco::MahycoComputeFaceQuantitesForRemapExecutionContext, std::shared_ptr<Mahyco::MahycoComputeFaceQuantitesForRemapExecutionContext>, SciHook::SciHookExecutionContext>(sub_mahyco_mahyco, "MahycoComputeFaceQuantitesForRemapExecutionContext")
    .def_property_readonly("cell_coord", &Mahyco::MahycoComputeFaceQuantitesForRemapExecutionContext::get_m_cell_coord)
    .def_property_readonly("node_coord", &Mahyco::MahycoComputeFaceQuantitesForRemapExecutionContext::get_m_node_coord)
    .def_property_readonly("face_normal", &Mahyco::MahycoComputeFaceQuantitesForRemapExecutionContext::get_m_face_normal)
    .def_property_readonly("velocity", &Mahyco::MahycoComputeFaceQuantitesForRemapExecutionContext::get_m_velocity)
    .def_property_readonly("velocity_n", &Mahyco::MahycoComputeFaceQuantitesForRemapExecutionContext::get_m_velocity_n)
    .def_property_readonly("face_coord", &Mahyco::MahycoComputeFaceQuantitesForRemapExecutionContext::get_m_face_coord)
    .def_property_readonly("face_length_lagrange", &Mahyco::MahycoComputeFaceQuantitesForRemapExecutionContext::get_m_face_length_lagrange)
    .def_property_readonly("face_normal_velocity", &Mahyco::MahycoComputeFaceQuantitesForRemapExecutionContext::get_m_face_normal_velocity)
    .def("__str__", [](Mahyco::MahycoComputeFaceQuantitesForRemapExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Mahyco::MahycoComputeFaceQuantitesForRemapExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_MAHYCO_MAHYCO_COMPUTEFACEQUANTITESFORREMAP_DISABLED)
  #endif // not defined(SCIHOOK_MAHYCO_MAHYCO_DISABLED)
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace Mahyco

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // MAHYCO___MAHYCOMODULEBINDINGS_H
