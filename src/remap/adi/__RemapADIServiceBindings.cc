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
#include "remap/adi/__RemapADIServiceVars.h"
#include "remap/adi/__RemapADIServiceContexts.h"
#include "scihook/scihookdefs.h"
#include "remap/adi/RemapADI_axl.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

using namespace Arcane;
using namespace Arcane::Materials;
namespace RemapAdi {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_ADI_DISABLED)
PYBIND11_EMBEDDED_MODULE(remapadi_remapadi, m)
{
  pybind11::class_<RemapAdi::RemapADISynchronizeDualUremapExecutionContext, std::shared_ptr<RemapAdi::RemapADISynchronizeDualUremapExecutionContext>, SciHook::SciHookExecutionContext>(m, "RemapADISynchronizeDualUremapExecutionContext")
    .def_property_readonly("phi_dual_lagrange", &RemapAdi::RemapADISynchronizeDualUremapExecutionContext::get_m_phi_dual_lagrange)
    .def_property_readonly("u_dual_lagrange", &RemapAdi::RemapADISynchronizeDualUremapExecutionContext::get_m_u_dual_lagrange)
    .def("__str__", [](RemapAdi::RemapADISynchronizeDualUremapExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](RemapAdi::RemapADISynchronizeDualUremapExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  pybind11::class_<RemapAdi::RemapADIComputeGradPhiFaceExecutionContext, std::shared_ptr<RemapAdi::RemapADIComputeGradPhiFaceExecutionContext>, SciHook::SciHookExecutionContext>(m, "RemapADIComputeGradPhiFaceExecutionContext")
    .def_property_readonly("idir", &RemapAdi::RemapADIComputeGradPhiFaceExecutionContext::get_idir)
    .def_property_readonly("nb_vars_to_project", &RemapAdi::RemapADIComputeGradPhiFaceExecutionContext::get_nb_vars_to_project)
    .def_property_readonly("nb_env", &RemapAdi::RemapADIComputeGradPhiFaceExecutionContext::get_nb_env)
    .def_property_readonly("face_normal", &RemapAdi::RemapADIComputeGradPhiFaceExecutionContext::get_m_face_normal)
    .def_property_readonly("cell_coord", &RemapAdi::RemapADIComputeGradPhiFaceExecutionContext::get_m_cell_coord)
    .def_property_readonly("phi_lagrange", &RemapAdi::RemapADIComputeGradPhiFaceExecutionContext::get_m_phi_lagrange)
    .def_property_readonly("face_coord", &RemapAdi::RemapADIComputeGradPhiFaceExecutionContext::get_m_face_coord)
    .def_property_readonly("cell_coord", &RemapAdi::RemapADIComputeGradPhiFaceExecutionContext::get_m_cell_coord)
    .def_property_readonly("is_dir_face", &RemapAdi::RemapADIComputeGradPhiFaceExecutionContext::get_m_is_dir_face)
    .def_property_readonly("grad_phi_face", &RemapAdi::RemapADIComputeGradPhiFaceExecutionContext::get_m_grad_phi_face)
    .def_property_readonly("deltax_lagrange", &RemapAdi::RemapADIComputeGradPhiFaceExecutionContext::get_m_deltax_lagrange)
    .def_property_readonly("h_cell_lagrange", &RemapAdi::RemapADIComputeGradPhiFaceExecutionContext::get_m_h_cell_lagrange)
    .def("__str__", [](RemapAdi::RemapADIComputeGradPhiFaceExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](RemapAdi::RemapADIComputeGradPhiFaceExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  pybind11::class_<RemapAdi::RemapADIComputeGradPhiCellExecutionContext, std::shared_ptr<RemapAdi::RemapADIComputeGradPhiCellExecutionContext>, SciHook::SciHookExecutionContext>(m, "RemapADIComputeGradPhiCellExecutionContext")
    .def_property_readonly("idir", &RemapAdi::RemapADIComputeGradPhiCellExecutionContext::get_idir)
    .def_property_readonly("nb_vars_to_project", &RemapAdi::RemapADIComputeGradPhiCellExecutionContext::get_nb_vars_to_project)
    .def_property_readonly("nb_env", &RemapAdi::RemapADIComputeGradPhiCellExecutionContext::get_nb_env)
    .def_property_readonly("outer_face_normal", &RemapAdi::RemapADIComputeGradPhiCellExecutionContext::get_m_outer_face_normal)
    .def_property_readonly("face_normal_velocity", &RemapAdi::RemapADIComputeGradPhiCellExecutionContext::get_m_face_normal_velocity)
    .def_property_readonly("face_length_lagrange", &RemapAdi::RemapADIComputeGradPhiCellExecutionContext::get_m_face_length_lagrange)
    .def_property_readonly("is_dir_face", &RemapAdi::RemapADIComputeGradPhiCellExecutionContext::get_m_is_dir_face)
    .def_property_readonly("grad_phi", &RemapAdi::RemapADIComputeGradPhiCellExecutionContext::get_m_grad_phi)
    .def_property_readonly("dual_phi_flux", &RemapAdi::RemapADIComputeGradPhiCellExecutionContext::get_m_dual_phi_flux)
    .def_property_readonly("delta_phi_face_av", &RemapAdi::RemapADIComputeGradPhiCellExecutionContext::get_m_delta_phi_face_av)
    .def_property_readonly("delta_phi_face_ar", &RemapAdi::RemapADIComputeGradPhiCellExecutionContext::get_m_delta_phi_face_ar)
    .def_property_readonly("est_mixte", &RemapAdi::RemapADIComputeGradPhiCellExecutionContext::get_m_est_mixte)
    .def_property_readonly("est_pure", &RemapAdi::RemapADIComputeGradPhiCellExecutionContext::get_m_est_pure)
    .def("__str__", [](RemapAdi::RemapADIComputeGradPhiCellExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](RemapAdi::RemapADIComputeGradPhiCellExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  pybind11::class_<RemapAdi::RemapADIComputeGradPhiCell_PBorn0_LimCExecutionContext, std::shared_ptr<RemapAdi::RemapADIComputeGradPhiCell_PBorn0_LimCExecutionContext>, SciHook::SciHookExecutionContext>(m, "RemapADIComputeGradPhiCell_PBorn0_LimCExecutionContext")
    .def_property_readonly("idir", &RemapAdi::RemapADIComputeGradPhiCell_PBorn0_LimCExecutionContext::get_idir)
    .def_property_readonly("nb_vars_to_project", &RemapAdi::RemapADIComputeGradPhiCell_PBorn0_LimCExecutionContext::get_nb_vars_to_project)
    .def_property_readonly("grad_phi_face", &RemapAdi::RemapADIComputeGradPhiCell_PBorn0_LimCExecutionContext::get_m_grad_phi_face)
    .def_property_readonly("grad_phi", &RemapAdi::RemapADIComputeGradPhiCell_PBorn0_LimCExecutionContext::get_m_grad_phi)
    .def_property_readonly("delta_phi_face_ar", &RemapAdi::RemapADIComputeGradPhiCell_PBorn0_LimCExecutionContext::get_m_delta_phi_face_ar)
    .def_property_readonly("delta_phi_face_av", &RemapAdi::RemapADIComputeGradPhiCell_PBorn0_LimCExecutionContext::get_m_delta_phi_face_av)
    .def("__str__", [](RemapAdi::RemapADIComputeGradPhiCell_PBorn0_LimCExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](RemapAdi::RemapADIComputeGradPhiCell_PBorn0_LimCExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  pybind11::class_<RemapAdi::RemapADIComputeDualGradPhi_LimCExecutionContext, std::shared_ptr<RemapAdi::RemapADIComputeDualGradPhi_LimCExecutionContext>, SciHook::SciHookExecutionContext>(m, "RemapADIComputeDualGradPhi_LimCExecutionContext")
    .def_property_readonly("idir", &RemapAdi::RemapADIComputeDualGradPhi_LimCExecutionContext::get_idir)
    .def_property_readonly("phi_dual_lagrange", &RemapAdi::RemapADIComputeDualGradPhi_LimCExecutionContext::get_m_phi_dual_lagrange)
    .def_property_readonly("node_coord", &RemapAdi::RemapADIComputeDualGradPhi_LimCExecutionContext::get_m_node_coord)
    .def_property_readonly("dual_grad_phi", &RemapAdi::RemapADIComputeDualGradPhi_LimCExecutionContext::get_m_dual_grad_phi)
    .def("__str__", [](RemapAdi::RemapADIComputeDualGradPhi_LimCExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](RemapAdi::RemapADIComputeDualGradPhi_LimCExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  pybind11::class_<RemapAdi::RemapADIComputeUpwindFaceQuantitiesForProjectionExecutionContext, std::shared_ptr<RemapAdi::RemapADIComputeUpwindFaceQuantitiesForProjectionExecutionContext>, SciHook::SciHookExecutionContext>(m, "RemapADIComputeUpwindFaceQuantitiesForProjectionExecutionContext")
    .def_property_readonly("idir", &RemapAdi::RemapADIComputeUpwindFaceQuantitiesForProjectionExecutionContext::get_idir)
    .def_property_readonly("nb_vars_to_project", &RemapAdi::RemapADIComputeUpwindFaceQuantitiesForProjectionExecutionContext::get_nb_vars_to_project)
    .def_property_readonly("nb_env", &RemapAdi::RemapADIComputeUpwindFaceQuantitiesForProjectionExecutionContext::get_nb_env)
    .def_property_readonly("face_normal_velocity", &RemapAdi::RemapADIComputeUpwindFaceQuantitiesForProjectionExecutionContext::get_m_face_normal_velocity)
    .def_property_readonly("deltax_lagrange", &RemapAdi::RemapADIComputeUpwindFaceQuantitiesForProjectionExecutionContext::get_m_deltax_lagrange)
    .def_property_readonly("phi_lagrange", &RemapAdi::RemapADIComputeUpwindFaceQuantitiesForProjectionExecutionContext::get_m_phi_lagrange)
    .def_property_readonly("face_coord", &RemapAdi::RemapADIComputeUpwindFaceQuantitiesForProjectionExecutionContext::get_m_face_coord)
    .def_property_readonly("cell_coord", &RemapAdi::RemapADIComputeUpwindFaceQuantitiesForProjectionExecutionContext::get_m_cell_coord)
    .def_property_readonly("face_normal", &RemapAdi::RemapADIComputeUpwindFaceQuantitiesForProjectionExecutionContext::get_m_face_normal)
    .def_property_readonly("grad_phi", &RemapAdi::RemapADIComputeUpwindFaceQuantitiesForProjectionExecutionContext::get_m_grad_phi)
    .def_property_readonly("delta_phi_face_av", &RemapAdi::RemapADIComputeUpwindFaceQuantitiesForProjectionExecutionContext::get_m_delta_phi_face_av)
    .def_property_readonly("delta_phi_face_ar", &RemapAdi::RemapADIComputeUpwindFaceQuantitiesForProjectionExecutionContext::get_m_delta_phi_face_ar)
    .def_property_readonly("h_cell_lagrange", &RemapAdi::RemapADIComputeUpwindFaceQuantitiesForProjectionExecutionContext::get_m_h_cell_lagrange)
    .def_property_readonly("est_mixte", &RemapAdi::RemapADIComputeUpwindFaceQuantitiesForProjectionExecutionContext::get_m_est_mixte)
    .def_property_readonly("est_pure", &RemapAdi::RemapADIComputeUpwindFaceQuantitiesForProjectionExecutionContext::get_m_est_pure)
    .def_property_readonly("phi_face", &RemapAdi::RemapADIComputeUpwindFaceQuantitiesForProjectionExecutionContext::get_m_phi_face)
    .def("__str__", [](RemapAdi::RemapADIComputeUpwindFaceQuantitiesForProjectionExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](RemapAdi::RemapADIComputeUpwindFaceQuantitiesForProjectionExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  pybind11::class_<RemapAdi::RemapADIComputeUpwindFaceQuantitiesForProjection_PBorn0_O2ExecutionContext, std::shared_ptr<RemapAdi::RemapADIComputeUpwindFaceQuantitiesForProjection_PBorn0_O2ExecutionContext>, SciHook::SciHookExecutionContext>(m, "RemapADIComputeUpwindFaceQuantitiesForProjection_PBorn0_O2ExecutionContext")
    .def_property_readonly("idir", &RemapAdi::RemapADIComputeUpwindFaceQuantitiesForProjection_PBorn0_O2ExecutionContext::get_idir)
    .def_property_readonly("nb_vars_to_project", &RemapAdi::RemapADIComputeUpwindFaceQuantitiesForProjection_PBorn0_O2ExecutionContext::get_nb_vars_to_project)
    .def_property_readonly("deltax_lagrange", &RemapAdi::RemapADIComputeUpwindFaceQuantitiesForProjection_PBorn0_O2ExecutionContext::get_m_deltax_lagrange)
    .def_property_readonly("face_normal_velocity", &RemapAdi::RemapADIComputeUpwindFaceQuantitiesForProjection_PBorn0_O2ExecutionContext::get_m_face_normal_velocity)
    .def_property_readonly("phi_lagrange", &RemapAdi::RemapADIComputeUpwindFaceQuantitiesForProjection_PBorn0_O2ExecutionContext::get_m_phi_lagrange)
    .def_property_readonly("face_coord", &RemapAdi::RemapADIComputeUpwindFaceQuantitiesForProjection_PBorn0_O2ExecutionContext::get_m_face_coord)
    .def_property_readonly("face_normal", &RemapAdi::RemapADIComputeUpwindFaceQuantitiesForProjection_PBorn0_O2ExecutionContext::get_m_face_normal)
    .def_property_readonly("cell_coord", &RemapAdi::RemapADIComputeUpwindFaceQuantitiesForProjection_PBorn0_O2ExecutionContext::get_m_cell_coord)
    .def_property_readonly("grad_phi", &RemapAdi::RemapADIComputeUpwindFaceQuantitiesForProjection_PBorn0_O2ExecutionContext::get_m_grad_phi)
    .def_property_readonly("phi_face", &RemapAdi::RemapADIComputeUpwindFaceQuantitiesForProjection_PBorn0_O2ExecutionContext::get_m_phi_face)
    .def("__str__", [](RemapAdi::RemapADIComputeUpwindFaceQuantitiesForProjection_PBorn0_O2ExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](RemapAdi::RemapADIComputeUpwindFaceQuantitiesForProjection_PBorn0_O2ExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  pybind11::class_<RemapAdi::RemapADIComputeUremapExecutionContext, std::shared_ptr<RemapAdi::RemapADIComputeUremapExecutionContext>, SciHook::SciHookExecutionContext>(m, "RemapADIComputeUremapExecutionContext")
    .def_property_readonly("idir", &RemapAdi::RemapADIComputeUremapExecutionContext::get_idir)
    .def_property_readonly("nb_vars_to_project", &RemapAdi::RemapADIComputeUremapExecutionContext::get_nb_vars_to_project)
    .def_property_readonly("nb_env", &RemapAdi::RemapADIComputeUremapExecutionContext::get_nb_env)
    .def_property_readonly("face_normal", &RemapAdi::RemapADIComputeUremapExecutionContext::get_m_face_normal)
    .def_property_readonly("face_length_lagrange", &RemapAdi::RemapADIComputeUremapExecutionContext::get_m_face_length_lagrange)
    .def_property_readonly("outer_face_normal", &RemapAdi::RemapADIComputeUremapExecutionContext::get_m_outer_face_normal)
    .def_property_readonly("phi_face", &RemapAdi::RemapADIComputeUremapExecutionContext::get_m_phi_face)
    .def_property_readonly("dual_phi_flux", &RemapAdi::RemapADIComputeUremapExecutionContext::get_m_dual_phi_flux)
    .def_property_readonly("est_mixte", &RemapAdi::RemapADIComputeUremapExecutionContext::get_m_est_mixte)
    .def_property_readonly("est_pure", &RemapAdi::RemapADIComputeUremapExecutionContext::get_m_est_pure)
    .def_property_readonly("u_lagrange", &RemapAdi::RemapADIComputeUremapExecutionContext::get_m_u_lagrange)
    .def_property_readonly("phi_lagrange", &RemapAdi::RemapADIComputeUremapExecutionContext::get_m_phi_lagrange)
    .def("__str__", [](RemapAdi::RemapADIComputeUremapExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](RemapAdi::RemapADIComputeUremapExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  pybind11::class_<RemapAdi::RemapADIComputeUremap_PBorn0ExecutionContext, std::shared_ptr<RemapAdi::RemapADIComputeUremap_PBorn0ExecutionContext>, SciHook::SciHookExecutionContext>(m, "RemapADIComputeUremap_PBorn0ExecutionContext")
    .def_property_readonly("idir", &RemapAdi::RemapADIComputeUremap_PBorn0ExecutionContext::get_idir)
    .def_property_readonly("nb_vars_to_project", &RemapAdi::RemapADIComputeUremap_PBorn0ExecutionContext::get_nb_vars_to_project)
    .def_property_readonly("nb_env", &RemapAdi::RemapADIComputeUremap_PBorn0ExecutionContext::get_nb_env)
    .def_property_readonly("face_normal", &RemapAdi::RemapADIComputeUremap_PBorn0ExecutionContext::get_m_face_normal)
    .def_property_readonly("face_normal_velocity", &RemapAdi::RemapADIComputeUremap_PBorn0ExecutionContext::get_m_face_normal_velocity)
    .def_property_readonly("face_length_lagrange", &RemapAdi::RemapADIComputeUremap_PBorn0ExecutionContext::get_m_face_length_lagrange)
    .def_property_readonly("outer_face_normal", &RemapAdi::RemapADIComputeUremap_PBorn0ExecutionContext::get_m_outer_face_normal)
    .def_property_readonly("phi_face", &RemapAdi::RemapADIComputeUremap_PBorn0ExecutionContext::get_m_phi_face)
    .def_property_readonly("dual_phi_flux", &RemapAdi::RemapADIComputeUremap_PBorn0ExecutionContext::get_m_dual_phi_flux)
    .def_property_readonly("est_mixte", &RemapAdi::RemapADIComputeUremap_PBorn0ExecutionContext::get_m_est_mixte)
    .def_property_readonly("est_pure", &RemapAdi::RemapADIComputeUremap_PBorn0ExecutionContext::get_m_est_pure)
    .def_property_readonly("u_lagrange", &RemapAdi::RemapADIComputeUremap_PBorn0ExecutionContext::get_m_u_lagrange)
    .def_property_readonly("phi_lagrange", &RemapAdi::RemapADIComputeUremap_PBorn0ExecutionContext::get_m_phi_lagrange)
    .def("__str__", [](RemapAdi::RemapADIComputeUremap_PBorn0ExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](RemapAdi::RemapADIComputeUremap_PBorn0ExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  pybind11::class_<RemapAdi::RemapADIComputeDualUremapExecutionContext, std::shared_ptr<RemapAdi::RemapADIComputeDualUremapExecutionContext>, SciHook::SciHookExecutionContext>(m, "RemapADIComputeDualUremapExecutionContext")
    .def_property_readonly("dual_phi_flux", &RemapAdi::RemapADIComputeDualUremapExecutionContext::get_m_dual_phi_flux)
    .def_property_readonly("node_coord", &RemapAdi::RemapADIComputeDualUremapExecutionContext::get_m_node_coord)
    .def_property_readonly("dual_grad_phi", &RemapAdi::RemapADIComputeDualUremapExecutionContext::get_m_dual_grad_phi)
    .def_property_readonly("back_flux_contrib_env", &RemapAdi::RemapADIComputeDualUremapExecutionContext::get_m_back_flux_contrib_env)
    .def_property_readonly("front_flux_contrib_env", &RemapAdi::RemapADIComputeDualUremapExecutionContext::get_m_front_flux_contrib_env)
    .def_property_readonly("back_flux_mass", &RemapAdi::RemapADIComputeDualUremapExecutionContext::get_m_back_flux_mass)
    .def_property_readonly("front_flux_mass", &RemapAdi::RemapADIComputeDualUremapExecutionContext::get_m_front_flux_mass)
    .def_property_readonly("back_flux_mass_env", &RemapAdi::RemapADIComputeDualUremapExecutionContext::get_m_back_flux_mass_env)
    .def_property_readonly("front_flux_mass_env", &RemapAdi::RemapADIComputeDualUremapExecutionContext::get_m_front_flux_mass_env)
    .def_property_readonly("u_dual_lagrange", &RemapAdi::RemapADIComputeDualUremapExecutionContext::get_m_u_dual_lagrange)
    .def_property_readonly("phi_dual_lagrange", &RemapAdi::RemapADIComputeDualUremapExecutionContext::get_m_phi_dual_lagrange)
    .def("__str__", [](RemapAdi::RemapADIComputeDualUremapExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](RemapAdi::RemapADIComputeDualUremapExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  pybind11::class_<RemapAdi::RemapADIAppliRemapExecutionContext, std::shared_ptr<RemapAdi::RemapADIAppliRemapExecutionContext>, SciHook::SciHookExecutionContext>(m, "RemapADIAppliRemapExecutionContext")
    .def_property_readonly("dimension", &RemapAdi::RemapADIAppliRemapExecutionContext::get_dimension)
    .def_property_readonly("withDualProjection", &RemapAdi::RemapADIAppliRemapExecutionContext::get_withDualProjection)
    .def_property_readonly("nb_vars_to_project", &RemapAdi::RemapADIAppliRemapExecutionContext::get_nb_vars_to_project)
    .def_property_readonly("nb_env", &RemapAdi::RemapADIAppliRemapExecutionContext::get_nb_env)
    .def_property_readonly("sens_projection", &RemapAdi::RemapADIAppliRemapExecutionContext::get_m_sens_projection)
    .def("__str__", [](RemapAdi::RemapADIAppliRemapExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](RemapAdi::RemapADIAppliRemapExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  pybind11::class_<RemapAdi::RemapADIResizeRemapVariablesExecutionContext, std::shared_ptr<RemapAdi::RemapADIResizeRemapVariablesExecutionContext>, SciHook::SciHookExecutionContext>(m, "RemapADIResizeRemapVariablesExecutionContext")
    .def_property_readonly("nb_vars_to_project", &RemapAdi::RemapADIResizeRemapVariablesExecutionContext::get_nb_vars_to_project)
    .def_property_readonly("nb_env", &RemapAdi::RemapADIResizeRemapVariablesExecutionContext::get_nb_env)
    .def_property_readonly("u_lagrange", &RemapAdi::RemapADIResizeRemapVariablesExecutionContext::get_m_u_lagrange)
    .def_property_readonly("u_dual_lagrange", &RemapAdi::RemapADIResizeRemapVariablesExecutionContext::get_m_u_dual_lagrange)
    .def_property_readonly("phi_lagrange", &RemapAdi::RemapADIResizeRemapVariablesExecutionContext::get_m_phi_lagrange)
    .def_property_readonly("phi_dual_lagrange", &RemapAdi::RemapADIResizeRemapVariablesExecutionContext::get_m_phi_dual_lagrange)
    .def_property_readonly("dual_grad_phi", &RemapAdi::RemapADIResizeRemapVariablesExecutionContext::get_m_dual_grad_phi)
    .def_property_readonly("grad_phi", &RemapAdi::RemapADIResizeRemapVariablesExecutionContext::get_m_grad_phi)
    .def_property_readonly("phi_face", &RemapAdi::RemapADIResizeRemapVariablesExecutionContext::get_m_phi_face)
    .def_property_readonly("grad_phi_face", &RemapAdi::RemapADIResizeRemapVariablesExecutionContext::get_m_grad_phi_face)
    .def_property_readonly("delta_phi_face_ar", &RemapAdi::RemapADIResizeRemapVariablesExecutionContext::get_m_delta_phi_face_ar)
    .def_property_readonly("delta_phi_face_av", &RemapAdi::RemapADIResizeRemapVariablesExecutionContext::get_m_delta_phi_face_av)
    .def_property_readonly("dual_phi_flux", &RemapAdi::RemapADIResizeRemapVariablesExecutionContext::get_m_dual_phi_flux)
    .def_property_readonly("front_flux_mass_env", &RemapAdi::RemapADIResizeRemapVariablesExecutionContext::get_m_front_flux_mass_env)
    .def_property_readonly("back_flux_mass_env", &RemapAdi::RemapADIResizeRemapVariablesExecutionContext::get_m_back_flux_mass_env)
    .def_property_readonly("back_flux_contrib_env", &RemapAdi::RemapADIResizeRemapVariablesExecutionContext::get_m_back_flux_contrib_env)
    .def_property_readonly("front_flux_contrib_env", &RemapAdi::RemapADIResizeRemapVariablesExecutionContext::get_m_front_flux_contrib_env)
    .def("__str__", [](RemapAdi::RemapADIResizeRemapVariablesExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](RemapAdi::RemapADIResizeRemapVariablesExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  pybind11::class_<RemapAdi::RemapADISynchronizeUremapExecutionContext, std::shared_ptr<RemapAdi::RemapADISynchronizeUremapExecutionContext>, SciHook::SciHookExecutionContext>(m, "RemapADISynchronizeUremapExecutionContext")
    .def_property_readonly("phi_lagrange", &RemapAdi::RemapADISynchronizeUremapExecutionContext::get_m_phi_lagrange)
    .def_property_readonly("u_lagrange", &RemapAdi::RemapADISynchronizeUremapExecutionContext::get_m_u_lagrange)
    .def_property_readonly("dual_phi_flux", &RemapAdi::RemapADISynchronizeUremapExecutionContext::get_m_dual_phi_flux)
    .def_property_readonly("est_mixte", &RemapAdi::RemapADISynchronizeUremapExecutionContext::get_m_est_mixte)
    .def_property_readonly("est_pure", &RemapAdi::RemapADISynchronizeUremapExecutionContext::get_m_est_pure)
    .def("__str__", [](RemapAdi::RemapADISynchronizeUremapExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](RemapAdi::RemapADISynchronizeUremapExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  pybind11::class_<RemapAdi::RemapADIRemapVariablesExecutionContext, std::shared_ptr<RemapAdi::RemapADIRemapVariablesExecutionContext>, SciHook::SciHookExecutionContext>(m, "RemapADIRemapVariablesExecutionContext")
    .def_property_readonly("dimension", &RemapAdi::RemapADIRemapVariablesExecutionContext::get_dimension)
    .def_property_readonly("withDualProjection", &RemapAdi::RemapADIRemapVariablesExecutionContext::get_withDualProjection)
    .def_property_readonly("nb_vars_to_project", &RemapAdi::RemapADIRemapVariablesExecutionContext::get_nb_vars_to_project)
    .def_property_readonly("nb_env", &RemapAdi::RemapADIRemapVariablesExecutionContext::get_nb_env)
    .def_property_readonly("euler_volume", &RemapAdi::RemapADIRemapVariablesExecutionContext::get_m_euler_volume)
    .def_property_readonly("u_lagrange", &RemapAdi::RemapADIRemapVariablesExecutionContext::get_m_u_lagrange)
    .def_property_readonly("u_dual_lagrange", &RemapAdi::RemapADIRemapVariablesExecutionContext::get_m_u_dual_lagrange)
    .def_property_readonly("est_pure", &RemapAdi::RemapADIRemapVariablesExecutionContext::get_m_est_pure)
    .def_property_readonly("velocity", &RemapAdi::RemapADIRemapVariablesExecutionContext::get_m_velocity)
    .def_property_readonly("node_mass", &RemapAdi::RemapADIRemapVariablesExecutionContext::get_m_node_mass)
    .def_property_readonly("cell_volume", &RemapAdi::RemapADIRemapVariablesExecutionContext::get_m_cell_volume)
    .def_property_readonly("cell_status", &RemapAdi::RemapADIRemapVariablesExecutionContext::get_m_cell_status)
    .def_property_readonly("est_mixte", &RemapAdi::RemapADIRemapVariablesExecutionContext::get_m_est_mixte)
    .def_property_readonly("cell_mass", &RemapAdi::RemapADIRemapVariablesExecutionContext::get_m_cell_mass)
    .def_property_readonly("fracvol", &RemapAdi::RemapADIRemapVariablesExecutionContext::get_m_fracvol)
    .def_property_readonly("mass_fraction", &RemapAdi::RemapADIRemapVariablesExecutionContext::get_m_mass_fraction)
    .def_property_readonly("pseudo_viscosity", &RemapAdi::RemapADIRemapVariablesExecutionContext::get_m_pseudo_viscosity)
    .def_property_readonly("density", &RemapAdi::RemapADIRemapVariablesExecutionContext::get_m_density)
    .def_property_readonly("internal_energy", &RemapAdi::RemapADIRemapVariablesExecutionContext::get_m_internal_energy)
    .def("__str__", [](RemapAdi::RemapADIRemapVariablesExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](RemapAdi::RemapADIRemapVariablesExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
}
#endif

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace RemapAdi
