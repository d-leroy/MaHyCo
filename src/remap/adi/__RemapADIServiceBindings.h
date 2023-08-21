#ifndef REMAP_ADI___REMAPADISERVICEBINDINGS_H
#define REMAP_ADI___REMAPADISERVICEBINDINGS_H

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
#include "remap/adi/__RemapADIServiceContexts.h"
#include "SciHook.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

using namespace Arcane;
using namespace Arcane::Materials;
namespace RemapAdi {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void bind_remap_adi_remapadi(py::module __attribute__((unused)) &m)
{
  #if not defined(SCIHOOK_REMAP_ADI_REMAPADI_DISABLED)
  auto sub_remap_adi_remapadi = m.def_submodule("remap_adi_remapadi", "Bindings for RemapADI");
  #if not defined(SCIHOOK_REMAP_ADI_REMAPADI_SYNCHRONIZEDUALUREMAP_DISABLED)
  pybind11::class_<RemapAdi::RemapADISynchronizeDualUremapExecutionContext, std::shared_ptr<RemapAdi::RemapADISynchronizeDualUremapExecutionContext>, SciHook::SciHookExecutionContext>(sub_remap_adi_remapadi, "RemapADISynchronizeDualUremapExecutionContext")
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
  #endif // not defined(SCIHOOK_REMAP_ADI_REMAPADI_SYNCHRONIZEDUALUREMAP_DISABLED)
  #if not defined(SCIHOOK_REMAP_ADI_REMAPADI_COMPUTEANDLIMITGRADPHI_DISABLED)
  pybind11::class_<RemapAdi::RemapADIComputeAndLimitGradPhiExecutionContext, std::shared_ptr<RemapAdi::RemapADIComputeAndLimitGradPhiExecutionContext>, SciHook::SciHookExecutionContext>(sub_remap_adi_remapadi, "RemapADIComputeAndLimitGradPhiExecutionContext")
    .def_property_readonly("projectionLimiterId", &RemapAdi::RemapADIComputeAndLimitGradPhiExecutionContext::get_projectionLimiterId)
    .def_property_readonly("frontFace", &RemapAdi::RemapADIComputeAndLimitGradPhiExecutionContext::get_frontFace)
    .def_property_readonly("backFace", &RemapAdi::RemapADIComputeAndLimitGradPhiExecutionContext::get_backFace)
    .def_property_readonly("cell", &RemapAdi::RemapADIComputeAndLimitGradPhiExecutionContext::get_cell)
    .def_property_readonly("frontcell", &RemapAdi::RemapADIComputeAndLimitGradPhiExecutionContext::get_frontcell)
    .def_property_readonly("backcell", &RemapAdi::RemapADIComputeAndLimitGradPhiExecutionContext::get_backcell)
    .def_property_readonly("nb_vars", &RemapAdi::RemapADIComputeAndLimitGradPhiExecutionContext::get_nb_vars)
    .def_property_readonly("grad_phi", &RemapAdi::RemapADIComputeAndLimitGradPhiExecutionContext::get_m_grad_phi)
    .def_property_readonly("grad_phi_face", &RemapAdi::RemapADIComputeAndLimitGradPhiExecutionContext::get_m_grad_phi_face)
    .def_property_readonly("phi_lagrange", &RemapAdi::RemapADIComputeAndLimitGradPhiExecutionContext::get_m_phi_lagrange)
    .def_property_readonly("h_cell_lagrange", &RemapAdi::RemapADIComputeAndLimitGradPhiExecutionContext::get_m_h_cell_lagrange)
    .def("__str__", [](RemapAdi::RemapADIComputeAndLimitGradPhiExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](RemapAdi::RemapADIComputeAndLimitGradPhiExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_REMAP_ADI_REMAPADI_COMPUTEANDLIMITGRADPHI_DISABLED)
  #if not defined(SCIHOOK_REMAP_ADI_REMAPADI_COMPUTEDUALGRADPHI_DISABLED)
  pybind11::class_<RemapAdi::RemapADIComputeDualGradPhiExecutionContext, std::shared_ptr<RemapAdi::RemapADIComputeDualGradPhiExecutionContext>, SciHook::SciHookExecutionContext>(sub_remap_adi_remapadi, "RemapADIComputeDualGradPhiExecutionContext")
    .def_property_readonly("inode", &RemapAdi::RemapADIComputeDualGradPhiExecutionContext::get_inode)
    .def_property_readonly("frontfrontnode", &RemapAdi::RemapADIComputeDualGradPhiExecutionContext::get_frontfrontnode)
    .def_property_readonly("frontnode", &RemapAdi::RemapADIComputeDualGradPhiExecutionContext::get_frontnode)
    .def_property_readonly("backnode", &RemapAdi::RemapADIComputeDualGradPhiExecutionContext::get_backnode)
    .def_property_readonly("backbacknode", &RemapAdi::RemapADIComputeDualGradPhiExecutionContext::get_backbacknode)
    .def_property_readonly("idir", &RemapAdi::RemapADIComputeDualGradPhiExecutionContext::get_idir)
    .def_property_readonly("phi_dual_lagrange", &RemapAdi::RemapADIComputeDualGradPhiExecutionContext::get_m_phi_dual_lagrange)
    .def_property_readonly("node_coord", &RemapAdi::RemapADIComputeDualGradPhiExecutionContext::get_m_node_coord)
    .def("__str__", [](RemapAdi::RemapADIComputeDualGradPhiExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](RemapAdi::RemapADIComputeDualGradPhiExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_REMAP_ADI_REMAPADI_COMPUTEDUALGRADPHI_DISABLED)
  #if not defined(SCIHOOK_REMAP_ADI_REMAPADI_COMPUTEANDLIMITGRADPHIDUAL_DISABLED)
  pybind11::class_<RemapAdi::RemapADIComputeAndLimitGradPhiDualExecutionContext, std::shared_ptr<RemapAdi::RemapADIComputeAndLimitGradPhiDualExecutionContext>, SciHook::SciHookExecutionContext>(sub_remap_adi_remapadi, "RemapADIComputeAndLimitGradPhiDualExecutionContext")
    .def_property_readonly("projectionLimiterId", &RemapAdi::RemapADIComputeAndLimitGradPhiDualExecutionContext::get_projectionLimiterId)
    .def_property_readonly("inode", &RemapAdi::RemapADIComputeAndLimitGradPhiDualExecutionContext::get_inode)
    .def_property_readonly("frontnode", &RemapAdi::RemapADIComputeAndLimitGradPhiDualExecutionContext::get_frontnode)
    .def_property_readonly("backnode", &RemapAdi::RemapADIComputeAndLimitGradPhiDualExecutionContext::get_backnode)
    .def_property_readonly("grad_front", &RemapAdi::RemapADIComputeAndLimitGradPhiDualExecutionContext::get_grad_front)
    .def_property_readonly("grad_back", &RemapAdi::RemapADIComputeAndLimitGradPhiDualExecutionContext::get_grad_back)
    .def_property_readonly("h0", &RemapAdi::RemapADIComputeAndLimitGradPhiDualExecutionContext::get_h0)
    .def_property_readonly("hplus", &RemapAdi::RemapADIComputeAndLimitGradPhiDualExecutionContext::get_hplus)
    .def_property_readonly("hmoins", &RemapAdi::RemapADIComputeAndLimitGradPhiDualExecutionContext::get_hmoins)
    .def_property_readonly("phi_dual_lagrange", &RemapAdi::RemapADIComputeAndLimitGradPhiDualExecutionContext::get_m_phi_dual_lagrange)
    .def_property_readonly("dual_grad_phi", &RemapAdi::RemapADIComputeAndLimitGradPhiDualExecutionContext::get_m_dual_grad_phi)
    .def("__str__", [](RemapAdi::RemapADIComputeAndLimitGradPhiDualExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](RemapAdi::RemapADIComputeAndLimitGradPhiDualExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_REMAP_ADI_REMAPADI_COMPUTEANDLIMITGRADPHIDUAL_DISABLED)
  #if not defined(SCIHOOK_REMAP_ADI_REMAPADI_FLUXLIMITER_DISABLED)
  pybind11::class_<RemapAdi::RemapADIFluxLimiterExecutionContext, std::shared_ptr<RemapAdi::RemapADIFluxLimiterExecutionContext>, SciHook::SciHookExecutionContext>(sub_remap_adi_remapadi, "RemapADIFluxLimiterExecutionContext")
    .def_property_readonly("projectionLimiterId", &RemapAdi::RemapADIFluxLimiterExecutionContext::get_projectionLimiterId)
    .def_property_readonly("r", &RemapAdi::RemapADIFluxLimiterExecutionContext::get_r)
    .def("__str__", [](RemapAdi::RemapADIFluxLimiterExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](RemapAdi::RemapADIFluxLimiterExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_REMAP_ADI_REMAPADI_FLUXLIMITER_DISABLED)
  #if not defined(SCIHOOK_REMAP_ADI_REMAPADI_FLUXLIMITERG_DISABLED)
  pybind11::class_<RemapAdi::RemapADIFluxLimiterGExecutionContext, std::shared_ptr<RemapAdi::RemapADIFluxLimiterGExecutionContext>, SciHook::SciHookExecutionContext>(sub_remap_adi_remapadi, "RemapADIFluxLimiterGExecutionContext")
    .def_property_readonly("projectionLimiterId", &RemapAdi::RemapADIFluxLimiterGExecutionContext::get_projectionLimiterId)
    .def_property_readonly("gradplus", &RemapAdi::RemapADIFluxLimiterGExecutionContext::get_gradplus)
    .def_property_readonly("gradmoins", &RemapAdi::RemapADIFluxLimiterGExecutionContext::get_gradmoins)
    .def_property_readonly("y0", &RemapAdi::RemapADIFluxLimiterGExecutionContext::get_y0)
    .def_property_readonly("yplus", &RemapAdi::RemapADIFluxLimiterGExecutionContext::get_yplus)
    .def_property_readonly("ymoins", &RemapAdi::RemapADIFluxLimiterGExecutionContext::get_ymoins)
    .def_property_readonly("h0", &RemapAdi::RemapADIFluxLimiterGExecutionContext::get_h0)
    .def_property_readonly("hplus", &RemapAdi::RemapADIFluxLimiterGExecutionContext::get_hplus)
    .def_property_readonly("hmoins", &RemapAdi::RemapADIFluxLimiterGExecutionContext::get_hmoins)
    .def("__str__", [](RemapAdi::RemapADIFluxLimiterGExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](RemapAdi::RemapADIFluxLimiterGExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_REMAP_ADI_REMAPADI_FLUXLIMITERG_DISABLED)
  #if not defined(SCIHOOK_REMAP_ADI_REMAPADI_COMPUTEFLUXPP_DISABLED)
  pybind11::class_<RemapAdi::RemapADIComputeFluxPPExecutionContext, std::shared_ptr<RemapAdi::RemapADIComputeFluxPPExecutionContext>, SciHook::SciHookExecutionContext>(sub_remap_adi_remapadi, "RemapADIComputeFluxPPExecutionContext")
    .def_property_readonly("cell", &RemapAdi::RemapADIComputeFluxPPExecutionContext::get_cell)
    .def_property_readonly("frontcell", &RemapAdi::RemapADIComputeFluxPPExecutionContext::get_frontcell)
    .def_property_readonly("backcell", &RemapAdi::RemapADIComputeFluxPPExecutionContext::get_backcell)
    .def_property_readonly("face_normal_velocity", &RemapAdi::RemapADIComputeFluxPPExecutionContext::get_face_normal_velocity)
    .def_property_readonly("deltat_n", &RemapAdi::RemapADIComputeFluxPPExecutionContext::get_deltat_n)
    .def_property_readonly("type", &RemapAdi::RemapADIComputeFluxPPExecutionContext::get_type)
    .def_property_readonly("flux_threshold", &RemapAdi::RemapADIComputeFluxPPExecutionContext::get_flux_threshold)
    .def_property_readonly("projectionPenteBorneDebarFix", &RemapAdi::RemapADIComputeFluxPPExecutionContext::get_projectionPenteBorneDebarFix)
    .def_property_readonly("dual_normal_velocity", &RemapAdi::RemapADIComputeFluxPPExecutionContext::get_dual_normal_velocity)
    .def_property_readonly("calcul_flux_dual", &RemapAdi::RemapADIComputeFluxPPExecutionContext::get_calcul_flux_dual)
    .def_property_readonly("flux", &RemapAdi::RemapADIComputeFluxPPExecutionContext::get_flux)
    .def_property_readonly("flux_dual", &RemapAdi::RemapADIComputeFluxPPExecutionContext::get_flux_dual)
    .def_property_readonly("nbmat", &RemapAdi::RemapADIComputeFluxPPExecutionContext::get_nbmat)
    .def_property_readonly("nb_vars", &RemapAdi::RemapADIComputeFluxPPExecutionContext::get_nb_vars)
    .def_property_readonly("h_cell_lagrange", &RemapAdi::RemapADIComputeFluxPPExecutionContext::get_m_h_cell_lagrange)
    .def_property_readonly("phi_lagrange", &RemapAdi::RemapADIComputeFluxPPExecutionContext::get_m_phi_lagrange)
    .def_property_readonly("grad_phi", &RemapAdi::RemapADIComputeFluxPPExecutionContext::get_m_grad_phi)
    .def("__str__", [](RemapAdi::RemapADIComputeFluxPPExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](RemapAdi::RemapADIComputeFluxPPExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_REMAP_ADI_REMAPADI_COMPUTEFLUXPP_DISABLED)
  #if not defined(SCIHOOK_REMAP_ADI_REMAPADI_COMPUTEY0_DISABLED)
  pybind11::class_<RemapAdi::RemapADIComputeY0ExecutionContext, std::shared_ptr<RemapAdi::RemapADIComputeY0ExecutionContext>, SciHook::SciHookExecutionContext>(sub_remap_adi_remapadi, "RemapADIComputeY0ExecutionContext")
    .def_property_readonly("projectionLimiterId", &RemapAdi::RemapADIComputeY0ExecutionContext::get_projectionLimiterId)
    .def_property_readonly("y0", &RemapAdi::RemapADIComputeY0ExecutionContext::get_y0)
    .def_property_readonly("yplus", &RemapAdi::RemapADIComputeY0ExecutionContext::get_yplus)
    .def_property_readonly("ymoins", &RemapAdi::RemapADIComputeY0ExecutionContext::get_ymoins)
    .def_property_readonly("h0", &RemapAdi::RemapADIComputeY0ExecutionContext::get_h0)
    .def_property_readonly("hplus", &RemapAdi::RemapADIComputeY0ExecutionContext::get_hplus)
    .def_property_readonly("hmoins", &RemapAdi::RemapADIComputeY0ExecutionContext::get_hmoins)
    .def_property_readonly("type", &RemapAdi::RemapADIComputeY0ExecutionContext::get_type)
    .def("__str__", [](RemapAdi::RemapADIComputeY0ExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](RemapAdi::RemapADIComputeY0ExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_REMAP_ADI_REMAPADI_COMPUTEY0_DISABLED)
  #if not defined(SCIHOOK_REMAP_ADI_REMAPADI_COMPUTEXGXD_DISABLED)
  pybind11::class_<RemapAdi::RemapADIComputexgxdExecutionContext, std::shared_ptr<RemapAdi::RemapADIComputexgxdExecutionContext>, SciHook::SciHookExecutionContext>(sub_remap_adi_remapadi, "RemapADIComputexgxdExecutionContext")
    .def_property_readonly("y0", &RemapAdi::RemapADIComputexgxdExecutionContext::get_y0)
    .def_property_readonly("yplus", &RemapAdi::RemapADIComputexgxdExecutionContext::get_yplus)
    .def_property_readonly("ymoins", &RemapAdi::RemapADIComputexgxdExecutionContext::get_ymoins)
    .def_property_readonly("h0", &RemapAdi::RemapADIComputexgxdExecutionContext::get_h0)
    .def_property_readonly("y0plus", &RemapAdi::RemapADIComputexgxdExecutionContext::get_y0plus)
    .def_property_readonly("y0moins", &RemapAdi::RemapADIComputexgxdExecutionContext::get_y0moins)
    .def_property_readonly("type", &RemapAdi::RemapADIComputexgxdExecutionContext::get_type)
    .def("__str__", [](RemapAdi::RemapADIComputexgxdExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](RemapAdi::RemapADIComputexgxdExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_REMAP_ADI_REMAPADI_COMPUTEXGXD_DISABLED)
  #if not defined(SCIHOOK_REMAP_ADI_REMAPADI_COMPUTEYGYD_DISABLED)
  pybind11::class_<RemapAdi::RemapADIComputeygydExecutionContext, std::shared_ptr<RemapAdi::RemapADIComputeygydExecutionContext>, SciHook::SciHookExecutionContext>(sub_remap_adi_remapadi, "RemapADIComputeygydExecutionContext")
    .def_property_readonly("y0", &RemapAdi::RemapADIComputeygydExecutionContext::get_y0)
    .def_property_readonly("yplus", &RemapAdi::RemapADIComputeygydExecutionContext::get_yplus)
    .def_property_readonly("ymoins", &RemapAdi::RemapADIComputeygydExecutionContext::get_ymoins)
    .def_property_readonly("h0", &RemapAdi::RemapADIComputeygydExecutionContext::get_h0)
    .def_property_readonly("y0plus", &RemapAdi::RemapADIComputeygydExecutionContext::get_y0plus)
    .def_property_readonly("y0moins", &RemapAdi::RemapADIComputeygydExecutionContext::get_y0moins)
    .def_property_readonly("grady", &RemapAdi::RemapADIComputeygydExecutionContext::get_grady)
    .def_property_readonly("type", &RemapAdi::RemapADIComputeygydExecutionContext::get_type)
    .def("__str__", [](RemapAdi::RemapADIComputeygydExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](RemapAdi::RemapADIComputeygydExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_REMAP_ADI_REMAPADI_COMPUTEYGYD_DISABLED)
  #if not defined(SCIHOOK_REMAP_ADI_REMAPADI_INTY_DISABLED)
  pybind11::class_<RemapAdi::RemapADIINTYExecutionContext, std::shared_ptr<RemapAdi::RemapADIINTYExecutionContext>, SciHook::SciHookExecutionContext>(sub_remap_adi_remapadi, "RemapADIINTYExecutionContext")
    .def_property_readonly("X", &RemapAdi::RemapADIINTYExecutionContext::get_X)
    .def_property_readonly("x0", &RemapAdi::RemapADIINTYExecutionContext::get_x0)
    .def_property_readonly("y0", &RemapAdi::RemapADIINTYExecutionContext::get_y0)
    .def_property_readonly("x1", &RemapAdi::RemapADIINTYExecutionContext::get_x1)
    .def_property_readonly("y1", &RemapAdi::RemapADIINTYExecutionContext::get_y1)
    .def("__str__", [](RemapAdi::RemapADIINTYExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](RemapAdi::RemapADIINTYExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_REMAP_ADI_REMAPADI_INTY_DISABLED)
  #if not defined(SCIHOOK_REMAP_ADI_REMAPADI_COMPUTEFLUXPPPURE_DISABLED)
  pybind11::class_<RemapAdi::RemapADIComputeFluxPPPureExecutionContext, std::shared_ptr<RemapAdi::RemapADIComputeFluxPPPureExecutionContext>, SciHook::SciHookExecutionContext>(sub_remap_adi_remapadi, "RemapADIComputeFluxPPPureExecutionContext")
    .def_property_readonly("cell", &RemapAdi::RemapADIComputeFluxPPPureExecutionContext::get_cell)
    .def_property_readonly("frontcell", &RemapAdi::RemapADIComputeFluxPPPureExecutionContext::get_frontcell)
    .def_property_readonly("backcell", &RemapAdi::RemapADIComputeFluxPPPureExecutionContext::get_backcell)
    .def_property_readonly("face_normal_velocity", &RemapAdi::RemapADIComputeFluxPPPureExecutionContext::get_face_normal_velocity)
    .def_property_readonly("deltat_n", &RemapAdi::RemapADIComputeFluxPPPureExecutionContext::get_deltat_n)
    .def_property_readonly("type", &RemapAdi::RemapADIComputeFluxPPPureExecutionContext::get_type)
    .def_property_readonly("flux_threshold", &RemapAdi::RemapADIComputeFluxPPPureExecutionContext::get_flux_threshold)
    .def_property_readonly("projectionPenteBorneDebarFix", &RemapAdi::RemapADIComputeFluxPPPureExecutionContext::get_projectionPenteBorneDebarFix)
    .def_property_readonly("dual_normal_velocity", &RemapAdi::RemapADIComputeFluxPPPureExecutionContext::get_dual_normal_velocity)
    .def_property_readonly("calcul_flux_dual", &RemapAdi::RemapADIComputeFluxPPPureExecutionContext::get_calcul_flux_dual)
    .def_property_readonly("Flux", &RemapAdi::RemapADIComputeFluxPPPureExecutionContext::get_Flux)
    .def_property_readonly("Flux_dual", &RemapAdi::RemapADIComputeFluxPPPureExecutionContext::get_Flux_dual)
    .def_property_readonly("nbmat", &RemapAdi::RemapADIComputeFluxPPPureExecutionContext::get_nbmat)
    .def_property_readonly("nb_vars", &RemapAdi::RemapADIComputeFluxPPPureExecutionContext::get_nb_vars)
    .def_property_readonly("h_cell_lagrange", &RemapAdi::RemapADIComputeFluxPPPureExecutionContext::get_m_h_cell_lagrange)
    .def_property_readonly("phi_lagrange", &RemapAdi::RemapADIComputeFluxPPPureExecutionContext::get_m_phi_lagrange)
    .def_property_readonly("grad_phi", &RemapAdi::RemapADIComputeFluxPPPureExecutionContext::get_m_grad_phi)
    .def("__str__", [](RemapAdi::RemapADIComputeFluxPPPureExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](RemapAdi::RemapADIComputeFluxPPPureExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_REMAP_ADI_REMAPADI_COMPUTEFLUXPPPURE_DISABLED)
  #if not defined(SCIHOOK_REMAP_ADI_REMAPADI_COMPUTEGRADPHIFACE_DISABLED)
  pybind11::class_<RemapAdi::RemapADIComputeGradPhiFaceExecutionContext, std::shared_ptr<RemapAdi::RemapADIComputeGradPhiFaceExecutionContext>, SciHook::SciHookExecutionContext>(sub_remap_adi_remapadi, "RemapADIComputeGradPhiFaceExecutionContext")
    .def_property_readonly("idir", &RemapAdi::RemapADIComputeGradPhiFaceExecutionContext::get_idir)
    .def_property_readonly("nb_vars_to_project", &RemapAdi::RemapADIComputeGradPhiFaceExecutionContext::get_nb_vars_to_project)
    .def_property_readonly("nb_env", &RemapAdi::RemapADIComputeGradPhiFaceExecutionContext::get_nb_env)
    .def_property_readonly("face_normal", &RemapAdi::RemapADIComputeGradPhiFaceExecutionContext::get_m_face_normal)
    .def_property_readonly("cell_coord", &RemapAdi::RemapADIComputeGradPhiFaceExecutionContext::get_m_cell_coord)
    .def_property_readonly("phi_lagrange", &RemapAdi::RemapADIComputeGradPhiFaceExecutionContext::get_m_phi_lagrange)
    .def_property_readonly("face_coord", &RemapAdi::RemapADIComputeGradPhiFaceExecutionContext::get_m_face_coord)
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
  #endif // not defined(SCIHOOK_REMAP_ADI_REMAPADI_COMPUTEGRADPHIFACE_DISABLED)
  #if not defined(SCIHOOK_REMAP_ADI_REMAPADI_COMPUTEGRADPHICELL_DISABLED)
  pybind11::class_<RemapAdi::RemapADIComputeGradPhiCellExecutionContext, std::shared_ptr<RemapAdi::RemapADIComputeGradPhiCellExecutionContext>, SciHook::SciHookExecutionContext>(sub_remap_adi_remapadi, "RemapADIComputeGradPhiCellExecutionContext")
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
  #endif // not defined(SCIHOOK_REMAP_ADI_REMAPADI_COMPUTEGRADPHICELL_DISABLED)
  #if not defined(SCIHOOK_REMAP_ADI_REMAPADI_COMPUTEUPWINDFACEQUANTITIESFORPROJECTION_DISABLED)
  pybind11::class_<RemapAdi::RemapADIComputeUpwindFaceQuantitiesForProjectionExecutionContext, std::shared_ptr<RemapAdi::RemapADIComputeUpwindFaceQuantitiesForProjectionExecutionContext>, SciHook::SciHookExecutionContext>(sub_remap_adi_remapadi, "RemapADIComputeUpwindFaceQuantitiesForProjectionExecutionContext")
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
  #endif // not defined(SCIHOOK_REMAP_ADI_REMAPADI_COMPUTEUPWINDFACEQUANTITIESFORPROJECTION_DISABLED)
  #if not defined(SCIHOOK_REMAP_ADI_REMAPADI_COMPUTEUPWINDFACEQUANTITIESFORPROJECTION_PBORN0_O2_DISABLED)
  pybind11::class_<RemapAdi::RemapADIComputeUpwindFaceQuantitiesForProjection_PBorn0_O2ExecutionContext, std::shared_ptr<RemapAdi::RemapADIComputeUpwindFaceQuantitiesForProjection_PBorn0_O2ExecutionContext>, SciHook::SciHookExecutionContext>(sub_remap_adi_remapadi, "RemapADIComputeUpwindFaceQuantitiesForProjection_PBorn0_O2ExecutionContext")
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
  #endif // not defined(SCIHOOK_REMAP_ADI_REMAPADI_COMPUTEUPWINDFACEQUANTITIESFORPROJECTION_PBORN0_O2_DISABLED)
  #if not defined(SCIHOOK_REMAP_ADI_REMAPADI_COMPUTEUREMAP_DISABLED)
  pybind11::class_<RemapAdi::RemapADIComputeUremapExecutionContext, std::shared_ptr<RemapAdi::RemapADIComputeUremapExecutionContext>, SciHook::SciHookExecutionContext>(sub_remap_adi_remapadi, "RemapADIComputeUremapExecutionContext")
    .def_property_readonly("idir", &RemapAdi::RemapADIComputeUremapExecutionContext::get_idir)
    .def_property_readonly("nb_vars_to_project", &RemapAdi::RemapADIComputeUremapExecutionContext::get_nb_vars_to_project)
    .def_property_readonly("nb_env", &RemapAdi::RemapADIComputeUremapExecutionContext::get_nb_env)
    .def_property_readonly("face_normal", &RemapAdi::RemapADIComputeUremapExecutionContext::get_m_face_normal)
    .def_property_readonly("face_length_lagrange", &RemapAdi::RemapADIComputeUremapExecutionContext::get_m_face_length_lagrange)
    .def_property_readonly("outer_face_normal", &RemapAdi::RemapADIComputeUremapExecutionContext::get_m_outer_face_normal)
    .def_property_readonly("face_normal_velocity", &RemapAdi::RemapADIComputeUremapExecutionContext::get_m_face_normal_velocity)
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
  #endif // not defined(SCIHOOK_REMAP_ADI_REMAPADI_COMPUTEUREMAP_DISABLED)
  #if not defined(SCIHOOK_REMAP_ADI_REMAPADI_COMPUTEUREMAP_PBORN0_DISABLED)
  pybind11::class_<RemapAdi::RemapADIComputeUremap_PBorn0ExecutionContext, std::shared_ptr<RemapAdi::RemapADIComputeUremap_PBorn0ExecutionContext>, SciHook::SciHookExecutionContext>(sub_remap_adi_remapadi, "RemapADIComputeUremap_PBorn0ExecutionContext")
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
  #endif // not defined(SCIHOOK_REMAP_ADI_REMAPADI_COMPUTEUREMAP_PBORN0_DISABLED)
  #if not defined(SCIHOOK_REMAP_ADI_REMAPADI_COMPUTEDUALUREMAP_DISABLED)
  pybind11::class_<RemapAdi::RemapADIComputeDualUremapExecutionContext, std::shared_ptr<RemapAdi::RemapADIComputeDualUremapExecutionContext>, SciHook::SciHookExecutionContext>(sub_remap_adi_remapadi, "RemapADIComputeDualUremapExecutionContext")
    .def_property_readonly("idir", &RemapAdi::RemapADIComputeDualUremapExecutionContext::get_idir)
    .def_property_readonly("nb_env", &RemapAdi::RemapADIComputeDualUremapExecutionContext::get_nb_env)
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
  #endif // not defined(SCIHOOK_REMAP_ADI_REMAPADI_COMPUTEDUALUREMAP_DISABLED)
  #if not defined(SCIHOOK_REMAP_ADI_REMAPADI_COMPUTEREMAPFLUX_DISABLED)
  pybind11::class_<RemapAdi::RemapADIComputeRemapFluxExecutionContext, std::shared_ptr<RemapAdi::RemapADIComputeRemapFluxExecutionContext>, SciHook::SciHookExecutionContext>(sub_remap_adi_remapadi, "RemapADIComputeRemapFluxExecutionContext")
    .def_property_readonly("projectionOrder", &RemapAdi::RemapADIComputeRemapFluxExecutionContext::get_projectionOrder)
    .def_property_readonly("projectionAvecPlateauPente", &RemapAdi::RemapADIComputeRemapFluxExecutionContext::get_projectionAvecPlateauPente)
    .def_property_readonly("face_normal_velocity", &RemapAdi::RemapADIComputeRemapFluxExecutionContext::get_face_normal_velocity)
    .def_property_readonly("face_normal", &RemapAdi::RemapADIComputeRemapFluxExecutionContext::get_face_normal)
    .def_property_readonly("face_length", &RemapAdi::RemapADIComputeRemapFluxExecutionContext::get_face_length)
    .def_property_readonly("phi_face", &RemapAdi::RemapADIComputeRemapFluxExecutionContext::get_phi_face)
    .def_property_readonly("outer_face_normal", &RemapAdi::RemapADIComputeRemapFluxExecutionContext::get_outer_face_normal)
    .def_property_readonly("exy", &RemapAdi::RemapADIComputeRemapFluxExecutionContext::get_exy)
    .def_property_readonly("deltat_n", &RemapAdi::RemapADIComputeRemapFluxExecutionContext::get_deltat_n)
    .def("__str__", [](RemapAdi::RemapADIComputeRemapFluxExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    })
    .def("__repr__", [](RemapAdi::RemapADIComputeRemapFluxExecutionContext &self)
    {
      std::ostringstream oss;
      oss << "[" << self.name << "]";
      return oss.str();
    });
  #endif // not defined(SCIHOOK_REMAP_ADI_REMAPADI_COMPUTEREMAPFLUX_DISABLED)
  #if not defined(SCIHOOK_REMAP_ADI_REMAPADI_APPLIREMAP_DISABLED)
  pybind11::class_<RemapAdi::RemapADIAppliRemapExecutionContext, std::shared_ptr<RemapAdi::RemapADIAppliRemapExecutionContext>, SciHook::SciHookExecutionContext>(sub_remap_adi_remapadi, "RemapADIAppliRemapExecutionContext")
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
  #endif // not defined(SCIHOOK_REMAP_ADI_REMAPADI_APPLIREMAP_DISABLED)
  #if not defined(SCIHOOK_REMAP_ADI_REMAPADI_RESIZEREMAPVARIABLES_DISABLED)
  pybind11::class_<RemapAdi::RemapADIResizeRemapVariablesExecutionContext, std::shared_ptr<RemapAdi::RemapADIResizeRemapVariablesExecutionContext>, SciHook::SciHookExecutionContext>(sub_remap_adi_remapadi, "RemapADIResizeRemapVariablesExecutionContext")
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
  #endif // not defined(SCIHOOK_REMAP_ADI_REMAPADI_RESIZEREMAPVARIABLES_DISABLED)
  #if not defined(SCIHOOK_REMAP_ADI_REMAPADI_SYNCHRONIZEUREMAP_DISABLED)
  pybind11::class_<RemapAdi::RemapADISynchronizeUremapExecutionContext, std::shared_ptr<RemapAdi::RemapADISynchronizeUremapExecutionContext>, SciHook::SciHookExecutionContext>(sub_remap_adi_remapadi, "RemapADISynchronizeUremapExecutionContext")
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
  #endif // not defined(SCIHOOK_REMAP_ADI_REMAPADI_SYNCHRONIZEUREMAP_DISABLED)
  #if not defined(SCIHOOK_REMAP_ADI_REMAPADI_REMAPVARIABLES_DISABLED)
  pybind11::class_<RemapAdi::RemapADIRemapVariablesExecutionContext, std::shared_ptr<RemapAdi::RemapADIRemapVariablesExecutionContext>, SciHook::SciHookExecutionContext>(sub_remap_adi_remapadi, "RemapADIRemapVariablesExecutionContext")
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
  #endif // not defined(SCIHOOK_REMAP_ADI_REMAPADI_REMAPVARIABLES_DISABLED)
  #endif // not defined(SCIHOOK_REMAP_ADI_REMAPADI_DISABLED)
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace RemapAdi

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // REMAP_ADI___REMAPADISERVICEBINDINGS_H
