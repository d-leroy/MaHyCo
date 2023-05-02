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
#include "remap/__IRemap.h"
#include "remap/__RemapADIServiceVars.h"
#include "remap/__RemapADIServiceContexts.h"
#include "scihook/scihookdefs.h"
#include "remap/RemapADI_axl.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

using namespace Arcane;
using namespace Arcane::Materials;
namespace Remap {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_DISABLED)
PYBIND11_EMBEDDED_MODULE(remap_remapadi, m)
{
  pybind11::class_<Remap::RemapADISynchronizeDualUremapExecutionContext, std::shared_ptr<Remap::RemapADISynchronizeDualUremapExecutionContext>, SciHook::SciHookExecutionContext>(m, "RemapADISynchronizeDualUremapExecutionContext")
    .def_property_readonly("phi_dual_lagrange", &Remap::RemapADISynchronizeDualUremapExecutionContext::get_m_phi_dual_lagrange)
    .def_property_readonly("u_dual_lagrange", &Remap::RemapADISynchronizeDualUremapExecutionContext::get_m_u_dual_lagrange)
    .def("__str__", [](Remap::RemapADISynchronizeDualUremapExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Remap::RemapADISynchronizeDualUremapExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  pybind11::class_<Remap::RemapADIComputeGradPhiFaceExecutionContext, std::shared_ptr<Remap::RemapADIComputeGradPhiFaceExecutionContext>, SciHook::SciHookExecutionContext>(m, "RemapADIComputeGradPhiFaceExecutionContext")
    .def_property_readonly("idir", &Remap::RemapADIComputeGradPhiFaceExecutionContext::get_idir)
    .def_property_readonly("nb_vars_to_project", &Remap::RemapADIComputeGradPhiFaceExecutionContext::get_nb_vars_to_project)
    .def_property_readonly("nb_env", &Remap::RemapADIComputeGradPhiFaceExecutionContext::get_nb_env)
    .def_property_readonly("face_normal", &Remap::RemapADIComputeGradPhiFaceExecutionContext::get_m_face_normal)
    .def_property_readonly("cell_coord", &Remap::RemapADIComputeGradPhiFaceExecutionContext::get_m_cell_coord)
    .def_property_readonly("phi_lagrange", &Remap::RemapADIComputeGradPhiFaceExecutionContext::get_m_phi_lagrange)
    .def_property_readonly("face_coord", &Remap::RemapADIComputeGradPhiFaceExecutionContext::get_m_face_coord)
    .def_property_readonly("cell_coord", &Remap::RemapADIComputeGradPhiFaceExecutionContext::get_m_cell_coord)
    .def_property_readonly("is_dir_face", &Remap::RemapADIComputeGradPhiFaceExecutionContext::get_m_is_dir_face)
    .def_property_readonly("grad_phi_face", &Remap::RemapADIComputeGradPhiFaceExecutionContext::get_m_grad_phi_face)
    .def_property_readonly("deltax_lagrange", &Remap::RemapADIComputeGradPhiFaceExecutionContext::get_m_deltax_lagrange)
    .def_property_readonly("h_cell_lagrange", &Remap::RemapADIComputeGradPhiFaceExecutionContext::get_m_h_cell_lagrange)
    .def("__str__", [](Remap::RemapADIComputeGradPhiFaceExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Remap::RemapADIComputeGradPhiFaceExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  pybind11::class_<Remap::RemapADIComputeGradPhiCellExecutionContext, std::shared_ptr<Remap::RemapADIComputeGradPhiCellExecutionContext>, SciHook::SciHookExecutionContext>(m, "RemapADIComputeGradPhiCellExecutionContext")
    .def_property_readonly("idir", &Remap::RemapADIComputeGradPhiCellExecutionContext::get_idir)
    .def_property_readonly("nb_vars_to_project", &Remap::RemapADIComputeGradPhiCellExecutionContext::get_nb_vars_to_project)
    .def_property_readonly("nb_env", &Remap::RemapADIComputeGradPhiCellExecutionContext::get_nb_env)
    .def_property_readonly("outer_face_normal", &Remap::RemapADIComputeGradPhiCellExecutionContext::get_m_outer_face_normal)
    .def_property_readonly("face_normal_velocity", &Remap::RemapADIComputeGradPhiCellExecutionContext::get_m_face_normal_velocity)
    .def_property_readonly("face_length_lagrange", &Remap::RemapADIComputeGradPhiCellExecutionContext::get_m_face_length_lagrange)
    .def_property_readonly("is_dir_face", &Remap::RemapADIComputeGradPhiCellExecutionContext::get_m_is_dir_face)
    .def_property_readonly("grad_phi", &Remap::RemapADIComputeGradPhiCellExecutionContext::get_m_grad_phi)
    .def_property_readonly("dual_phi_flux", &Remap::RemapADIComputeGradPhiCellExecutionContext::get_m_dual_phi_flux)
    .def_property_readonly("delta_phi_face_av", &Remap::RemapADIComputeGradPhiCellExecutionContext::get_m_delta_phi_face_av)
    .def_property_readonly("delta_phi_face_ar", &Remap::RemapADIComputeGradPhiCellExecutionContext::get_m_delta_phi_face_ar)
    .def_property_readonly("est_mixte", &Remap::RemapADIComputeGradPhiCellExecutionContext::get_m_est_mixte)
    .def_property_readonly("est_pure", &Remap::RemapADIComputeGradPhiCellExecutionContext::get_m_est_pure)
    .def("__str__", [](Remap::RemapADIComputeGradPhiCellExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Remap::RemapADIComputeGradPhiCellExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  pybind11::class_<Remap::RemapADIComputeGradPhiCell_PBorn0_LimCExecutionContext, std::shared_ptr<Remap::RemapADIComputeGradPhiCell_PBorn0_LimCExecutionContext>, SciHook::SciHookExecutionContext>(m, "RemapADIComputeGradPhiCell_PBorn0_LimCExecutionContext")
    .def_property_readonly("idir", &Remap::RemapADIComputeGradPhiCell_PBorn0_LimCExecutionContext::get_idir)
    .def_property_readonly("nb_vars_to_project", &Remap::RemapADIComputeGradPhiCell_PBorn0_LimCExecutionContext::get_nb_vars_to_project)
    .def_property_readonly("grad_phi_face", &Remap::RemapADIComputeGradPhiCell_PBorn0_LimCExecutionContext::get_m_grad_phi_face)
    .def_property_readonly("grad_phi", &Remap::RemapADIComputeGradPhiCell_PBorn0_LimCExecutionContext::get_m_grad_phi)
    .def_property_readonly("delta_phi_face_ar", &Remap::RemapADIComputeGradPhiCell_PBorn0_LimCExecutionContext::get_m_delta_phi_face_ar)
    .def_property_readonly("delta_phi_face_av", &Remap::RemapADIComputeGradPhiCell_PBorn0_LimCExecutionContext::get_m_delta_phi_face_av)
    .def("__str__", [](Remap::RemapADIComputeGradPhiCell_PBorn0_LimCExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Remap::RemapADIComputeGradPhiCell_PBorn0_LimCExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  pybind11::class_<Remap::RemapADIComputeDualGradPhi_LimCExecutionContext, std::shared_ptr<Remap::RemapADIComputeDualGradPhi_LimCExecutionContext>, SciHook::SciHookExecutionContext>(m, "RemapADIComputeDualGradPhi_LimCExecutionContext")
    .def_property_readonly("idir", &Remap::RemapADIComputeDualGradPhi_LimCExecutionContext::get_idir)
    .def_property_readonly("phi_dual_lagrange", &Remap::RemapADIComputeDualGradPhi_LimCExecutionContext::get_m_phi_dual_lagrange)
    .def_property_readonly("node_coord", &Remap::RemapADIComputeDualGradPhi_LimCExecutionContext::get_m_node_coord)
    .def_property_readonly("dual_grad_phi", &Remap::RemapADIComputeDualGradPhi_LimCExecutionContext::get_m_dual_grad_phi)
    .def("__str__", [](Remap::RemapADIComputeDualGradPhi_LimCExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Remap::RemapADIComputeDualGradPhi_LimCExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  pybind11::class_<Remap::RemapADIComputeUpwindFaceQuantitiesForProjectionExecutionContext, std::shared_ptr<Remap::RemapADIComputeUpwindFaceQuantitiesForProjectionExecutionContext>, SciHook::SciHookExecutionContext>(m, "RemapADIComputeUpwindFaceQuantitiesForProjectionExecutionContext")
    .def_property_readonly("idir", &Remap::RemapADIComputeUpwindFaceQuantitiesForProjectionExecutionContext::get_idir)
    .def_property_readonly("nb_vars_to_project", &Remap::RemapADIComputeUpwindFaceQuantitiesForProjectionExecutionContext::get_nb_vars_to_project)
    .def_property_readonly("nb_env", &Remap::RemapADIComputeUpwindFaceQuantitiesForProjectionExecutionContext::get_nb_env)
    .def_property_readonly("face_normal_velocity", &Remap::RemapADIComputeUpwindFaceQuantitiesForProjectionExecutionContext::get_m_face_normal_velocity)
    .def_property_readonly("deltax_lagrange", &Remap::RemapADIComputeUpwindFaceQuantitiesForProjectionExecutionContext::get_m_deltax_lagrange)
    .def_property_readonly("phi_lagrange", &Remap::RemapADIComputeUpwindFaceQuantitiesForProjectionExecutionContext::get_m_phi_lagrange)
    .def_property_readonly("face_coord", &Remap::RemapADIComputeUpwindFaceQuantitiesForProjectionExecutionContext::get_m_face_coord)
    .def_property_readonly("cell_coord", &Remap::RemapADIComputeUpwindFaceQuantitiesForProjectionExecutionContext::get_m_cell_coord)
    .def_property_readonly("face_normal", &Remap::RemapADIComputeUpwindFaceQuantitiesForProjectionExecutionContext::get_m_face_normal)
    .def_property_readonly("grad_phi", &Remap::RemapADIComputeUpwindFaceQuantitiesForProjectionExecutionContext::get_m_grad_phi)
    .def_property_readonly("delta_phi_face_av", &Remap::RemapADIComputeUpwindFaceQuantitiesForProjectionExecutionContext::get_m_delta_phi_face_av)
    .def_property_readonly("delta_phi_face_ar", &Remap::RemapADIComputeUpwindFaceQuantitiesForProjectionExecutionContext::get_m_delta_phi_face_ar)
    .def_property_readonly("h_cell_lagrange", &Remap::RemapADIComputeUpwindFaceQuantitiesForProjectionExecutionContext::get_m_h_cell_lagrange)
    .def_property_readonly("est_mixte", &Remap::RemapADIComputeUpwindFaceQuantitiesForProjectionExecutionContext::get_m_est_mixte)
    .def_property_readonly("est_pure", &Remap::RemapADIComputeUpwindFaceQuantitiesForProjectionExecutionContext::get_m_est_pure)
    .def_property_readonly("phi_face", &Remap::RemapADIComputeUpwindFaceQuantitiesForProjectionExecutionContext::get_m_phi_face)
    .def("__str__", [](Remap::RemapADIComputeUpwindFaceQuantitiesForProjectionExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Remap::RemapADIComputeUpwindFaceQuantitiesForProjectionExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  pybind11::class_<Remap::RemapADIComputeUpwindFaceQuantitiesForProjection_PBorn0_O2ExecutionContext, std::shared_ptr<Remap::RemapADIComputeUpwindFaceQuantitiesForProjection_PBorn0_O2ExecutionContext>, SciHook::SciHookExecutionContext>(m, "RemapADIComputeUpwindFaceQuantitiesForProjection_PBorn0_O2ExecutionContext")
    .def_property_readonly("idir", &Remap::RemapADIComputeUpwindFaceQuantitiesForProjection_PBorn0_O2ExecutionContext::get_idir)
    .def_property_readonly("nb_vars_to_project", &Remap::RemapADIComputeUpwindFaceQuantitiesForProjection_PBorn0_O2ExecutionContext::get_nb_vars_to_project)
    .def_property_readonly("deltax_lagrange", &Remap::RemapADIComputeUpwindFaceQuantitiesForProjection_PBorn0_O2ExecutionContext::get_m_deltax_lagrange)
    .def_property_readonly("face_normal_velocity", &Remap::RemapADIComputeUpwindFaceQuantitiesForProjection_PBorn0_O2ExecutionContext::get_m_face_normal_velocity)
    .def_property_readonly("phi_lagrange", &Remap::RemapADIComputeUpwindFaceQuantitiesForProjection_PBorn0_O2ExecutionContext::get_m_phi_lagrange)
    .def_property_readonly("face_coord", &Remap::RemapADIComputeUpwindFaceQuantitiesForProjection_PBorn0_O2ExecutionContext::get_m_face_coord)
    .def_property_readonly("face_normal", &Remap::RemapADIComputeUpwindFaceQuantitiesForProjection_PBorn0_O2ExecutionContext::get_m_face_normal)
    .def_property_readonly("cell_coord", &Remap::RemapADIComputeUpwindFaceQuantitiesForProjection_PBorn0_O2ExecutionContext::get_m_cell_coord)
    .def_property_readonly("grad_phi", &Remap::RemapADIComputeUpwindFaceQuantitiesForProjection_PBorn0_O2ExecutionContext::get_m_grad_phi)
    .def_property_readonly("phi_face", &Remap::RemapADIComputeUpwindFaceQuantitiesForProjection_PBorn0_O2ExecutionContext::get_m_phi_face)
    .def("__str__", [](Remap::RemapADIComputeUpwindFaceQuantitiesForProjection_PBorn0_O2ExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Remap::RemapADIComputeUpwindFaceQuantitiesForProjection_PBorn0_O2ExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  pybind11::class_<Remap::RemapADIComputeUremapExecutionContext, std::shared_ptr<Remap::RemapADIComputeUremapExecutionContext>, SciHook::SciHookExecutionContext>(m, "RemapADIComputeUremapExecutionContext")
    .def_property_readonly("idir", &Remap::RemapADIComputeUremapExecutionContext::get_idir)
    .def_property_readonly("nb_vars_to_project", &Remap::RemapADIComputeUremapExecutionContext::get_nb_vars_to_project)
    .def_property_readonly("nb_env", &Remap::RemapADIComputeUremapExecutionContext::get_nb_env)
    .def_property_readonly("face_normal", &Remap::RemapADIComputeUremapExecutionContext::get_m_face_normal)
    .def_property_readonly("face_length_lagrange", &Remap::RemapADIComputeUremapExecutionContext::get_m_face_length_lagrange)
    .def_property_readonly("outer_face_normal", &Remap::RemapADIComputeUremapExecutionContext::get_m_outer_face_normal)
    .def_property_readonly("phi_face", &Remap::RemapADIComputeUremapExecutionContext::get_m_phi_face)
    .def_property_readonly("dual_phi_flux", &Remap::RemapADIComputeUremapExecutionContext::get_m_dual_phi_flux)
    .def_property_readonly("est_mixte", &Remap::RemapADIComputeUremapExecutionContext::get_m_est_mixte)
    .def_property_readonly("est_pure", &Remap::RemapADIComputeUremapExecutionContext::get_m_est_pure)
    .def_property_readonly("u_lagrange", &Remap::RemapADIComputeUremapExecutionContext::get_m_u_lagrange)
    .def_property_readonly("phi_lagrange", &Remap::RemapADIComputeUremapExecutionContext::get_m_phi_lagrange)
    .def("__str__", [](Remap::RemapADIComputeUremapExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Remap::RemapADIComputeUremapExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  pybind11::class_<Remap::RemapADIComputeUremap_PBorn0ExecutionContext, std::shared_ptr<Remap::RemapADIComputeUremap_PBorn0ExecutionContext>, SciHook::SciHookExecutionContext>(m, "RemapADIComputeUremap_PBorn0ExecutionContext")
    .def_property_readonly("idir", &Remap::RemapADIComputeUremap_PBorn0ExecutionContext::get_idir)
    .def_property_readonly("nb_vars_to_project", &Remap::RemapADIComputeUremap_PBorn0ExecutionContext::get_nb_vars_to_project)
    .def_property_readonly("nb_env", &Remap::RemapADIComputeUremap_PBorn0ExecutionContext::get_nb_env)
    .def_property_readonly("face_normal", &Remap::RemapADIComputeUremap_PBorn0ExecutionContext::get_m_face_normal)
    .def_property_readonly("face_normal_velocity", &Remap::RemapADIComputeUremap_PBorn0ExecutionContext::get_m_face_normal_velocity)
    .def_property_readonly("face_length_lagrange", &Remap::RemapADIComputeUremap_PBorn0ExecutionContext::get_m_face_length_lagrange)
    .def_property_readonly("outer_face_normal", &Remap::RemapADIComputeUremap_PBorn0ExecutionContext::get_m_outer_face_normal)
    .def_property_readonly("phi_face", &Remap::RemapADIComputeUremap_PBorn0ExecutionContext::get_m_phi_face)
    .def_property_readonly("dual_phi_flux", &Remap::RemapADIComputeUremap_PBorn0ExecutionContext::get_m_dual_phi_flux)
    .def_property_readonly("est_mixte", &Remap::RemapADIComputeUremap_PBorn0ExecutionContext::get_m_est_mixte)
    .def_property_readonly("est_pure", &Remap::RemapADIComputeUremap_PBorn0ExecutionContext::get_m_est_pure)
    .def_property_readonly("u_lagrange", &Remap::RemapADIComputeUremap_PBorn0ExecutionContext::get_m_u_lagrange)
    .def_property_readonly("phi_lagrange", &Remap::RemapADIComputeUremap_PBorn0ExecutionContext::get_m_phi_lagrange)
    .def("__str__", [](Remap::RemapADIComputeUremap_PBorn0ExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Remap::RemapADIComputeUremap_PBorn0ExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  pybind11::class_<Remap::RemapADIComputeDualUremapExecutionContext, std::shared_ptr<Remap::RemapADIComputeDualUremapExecutionContext>, SciHook::SciHookExecutionContext>(m, "RemapADIComputeDualUremapExecutionContext")
    .def_property_readonly("dual_phi_flux", &Remap::RemapADIComputeDualUremapExecutionContext::get_m_dual_phi_flux)
    .def_property_readonly("node_coord", &Remap::RemapADIComputeDualUremapExecutionContext::get_m_node_coord)
    .def_property_readonly("dual_grad_phi", &Remap::RemapADIComputeDualUremapExecutionContext::get_m_dual_grad_phi)
    .def_property_readonly("back_flux_contrib_env", &Remap::RemapADIComputeDualUremapExecutionContext::get_m_back_flux_contrib_env)
    .def_property_readonly("front_flux_contrib_env", &Remap::RemapADIComputeDualUremapExecutionContext::get_m_front_flux_contrib_env)
    .def_property_readonly("back_flux_mass", &Remap::RemapADIComputeDualUremapExecutionContext::get_m_back_flux_mass)
    .def_property_readonly("front_flux_mass", &Remap::RemapADIComputeDualUremapExecutionContext::get_m_front_flux_mass)
    .def_property_readonly("back_flux_mass_env", &Remap::RemapADIComputeDualUremapExecutionContext::get_m_back_flux_mass_env)
    .def_property_readonly("front_flux_mass_env", &Remap::RemapADIComputeDualUremapExecutionContext::get_m_front_flux_mass_env)
    .def_property_readonly("u_dual_lagrange", &Remap::RemapADIComputeDualUremapExecutionContext::get_m_u_dual_lagrange)
    .def_property_readonly("phi_dual_lagrange", &Remap::RemapADIComputeDualUremapExecutionContext::get_m_phi_dual_lagrange)
    .def("__str__", [](Remap::RemapADIComputeDualUremapExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Remap::RemapADIComputeDualUremapExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  pybind11::class_<Remap::RemapADIAppliRemapExecutionContext, std::shared_ptr<Remap::RemapADIAppliRemapExecutionContext>, SciHook::SciHookExecutionContext>(m, "RemapADIAppliRemapExecutionContext")
    .def_property_readonly("dimension", &Remap::RemapADIAppliRemapExecutionContext::get_dimension)
    .def_property_readonly("withDualProjection", &Remap::RemapADIAppliRemapExecutionContext::get_withDualProjection)
    .def_property_readonly("nb_vars_to_project", &Remap::RemapADIAppliRemapExecutionContext::get_nb_vars_to_project)
    .def_property_readonly("nb_env", &Remap::RemapADIAppliRemapExecutionContext::get_nb_env)
    .def_property_readonly("sens_projection", &Remap::RemapADIAppliRemapExecutionContext::get_m_sens_projection)
    .def("__str__", [](Remap::RemapADIAppliRemapExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Remap::RemapADIAppliRemapExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  pybind11::class_<Remap::RemapADIResizeRemapVariablesExecutionContext, std::shared_ptr<Remap::RemapADIResizeRemapVariablesExecutionContext>, SciHook::SciHookExecutionContext>(m, "RemapADIResizeRemapVariablesExecutionContext")
    .def_property_readonly("nb_vars_to_project", &Remap::RemapADIResizeRemapVariablesExecutionContext::get_nb_vars_to_project)
    .def_property_readonly("nb_env", &Remap::RemapADIResizeRemapVariablesExecutionContext::get_nb_env)
    .def_property_readonly("u_lagrange", &Remap::RemapADIResizeRemapVariablesExecutionContext::get_m_u_lagrange)
    .def_property_readonly("u_dual_lagrange", &Remap::RemapADIResizeRemapVariablesExecutionContext::get_m_u_dual_lagrange)
    .def_property_readonly("phi_lagrange", &Remap::RemapADIResizeRemapVariablesExecutionContext::get_m_phi_lagrange)
    .def_property_readonly("phi_dual_lagrange", &Remap::RemapADIResizeRemapVariablesExecutionContext::get_m_phi_dual_lagrange)
    .def_property_readonly("dual_grad_phi", &Remap::RemapADIResizeRemapVariablesExecutionContext::get_m_dual_grad_phi)
    .def_property_readonly("grad_phi", &Remap::RemapADIResizeRemapVariablesExecutionContext::get_m_grad_phi)
    .def_property_readonly("phi_face", &Remap::RemapADIResizeRemapVariablesExecutionContext::get_m_phi_face)
    .def_property_readonly("grad_phi_face", &Remap::RemapADIResizeRemapVariablesExecutionContext::get_m_grad_phi_face)
    .def_property_readonly("delta_phi_face_ar", &Remap::RemapADIResizeRemapVariablesExecutionContext::get_m_delta_phi_face_ar)
    .def_property_readonly("delta_phi_face_av", &Remap::RemapADIResizeRemapVariablesExecutionContext::get_m_delta_phi_face_av)
    .def_property_readonly("dual_phi_flux", &Remap::RemapADIResizeRemapVariablesExecutionContext::get_m_dual_phi_flux)
    .def_property_readonly("front_flux_mass_env", &Remap::RemapADIResizeRemapVariablesExecutionContext::get_m_front_flux_mass_env)
    .def_property_readonly("back_flux_mass_env", &Remap::RemapADIResizeRemapVariablesExecutionContext::get_m_back_flux_mass_env)
    .def_property_readonly("back_flux_contrib_env", &Remap::RemapADIResizeRemapVariablesExecutionContext::get_m_back_flux_contrib_env)
    .def_property_readonly("front_flux_contrib_env", &Remap::RemapADIResizeRemapVariablesExecutionContext::get_m_front_flux_contrib_env)
    .def("__str__", [](Remap::RemapADIResizeRemapVariablesExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Remap::RemapADIResizeRemapVariablesExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  pybind11::class_<Remap::RemapADISynchronizeUremapExecutionContext, std::shared_ptr<Remap::RemapADISynchronizeUremapExecutionContext>, SciHook::SciHookExecutionContext>(m, "RemapADISynchronizeUremapExecutionContext")
    .def_property_readonly("phi_lagrange", &Remap::RemapADISynchronizeUremapExecutionContext::get_m_phi_lagrange)
    .def_property_readonly("u_lagrange", &Remap::RemapADISynchronizeUremapExecutionContext::get_m_u_lagrange)
    .def_property_readonly("dual_phi_flux", &Remap::RemapADISynchronizeUremapExecutionContext::get_m_dual_phi_flux)
    .def_property_readonly("est_mixte", &Remap::RemapADISynchronizeUremapExecutionContext::get_m_est_mixte)
    .def_property_readonly("est_pure", &Remap::RemapADISynchronizeUremapExecutionContext::get_m_est_pure)
    .def("__str__", [](Remap::RemapADISynchronizeUremapExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Remap::RemapADISynchronizeUremapExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  pybind11::class_<Remap::RemapADIRemapVariablesExecutionContext, std::shared_ptr<Remap::RemapADIRemapVariablesExecutionContext>, SciHook::SciHookExecutionContext>(m, "RemapADIRemapVariablesExecutionContext")
    .def_property_readonly("dimension", &Remap::RemapADIRemapVariablesExecutionContext::get_dimension)
    .def_property_readonly("withDualProjection", &Remap::RemapADIRemapVariablesExecutionContext::get_withDualProjection)
    .def_property_readonly("nb_vars_to_project", &Remap::RemapADIRemapVariablesExecutionContext::get_nb_vars_to_project)
    .def_property_readonly("nb_env", &Remap::RemapADIRemapVariablesExecutionContext::get_nb_env)
    .def_property_readonly("euler_volume", &Remap::RemapADIRemapVariablesExecutionContext::get_m_euler_volume)
    .def_property_readonly("u_lagrange", &Remap::RemapADIRemapVariablesExecutionContext::get_m_u_lagrange)
    .def_property_readonly("u_dual_lagrange", &Remap::RemapADIRemapVariablesExecutionContext::get_m_u_dual_lagrange)
    .def_property_readonly("est_pure", &Remap::RemapADIRemapVariablesExecutionContext::get_m_est_pure)
    .def_property_readonly("velocity", &Remap::RemapADIRemapVariablesExecutionContext::get_m_velocity)
    .def_property_readonly("node_mass", &Remap::RemapADIRemapVariablesExecutionContext::get_m_node_mass)
    .def_property_readonly("cell_volume", &Remap::RemapADIRemapVariablesExecutionContext::get_m_cell_volume)
    .def_property_readonly("cell_status", &Remap::RemapADIRemapVariablesExecutionContext::get_m_cell_status)
    .def_property_readonly("est_mixte", &Remap::RemapADIRemapVariablesExecutionContext::get_m_est_mixte)
    .def_property_readonly("cell_mass", &Remap::RemapADIRemapVariablesExecutionContext::get_m_cell_mass)
    .def_property_readonly("fracvol", &Remap::RemapADIRemapVariablesExecutionContext::get_m_fracvol)
    .def_property_readonly("mass_fraction", &Remap::RemapADIRemapVariablesExecutionContext::get_m_mass_fraction)
    .def_property_readonly("pseudo_viscosity", &Remap::RemapADIRemapVariablesExecutionContext::get_m_pseudo_viscosity)
    .def_property_readonly("density", &Remap::RemapADIRemapVariablesExecutionContext::get_m_density)
    .def_property_readonly("internal_energy", &Remap::RemapADIRemapVariablesExecutionContext::get_m_internal_energy)
    .def("__str__", [](Remap::RemapADIRemapVariablesExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](Remap::RemapADIRemapVariablesExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
}
#endif

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace Remap
