#ifndef REMAP_ADI___REMAPADISERVICESCIHOOKMACROS_H
#define REMAP_ADI___REMAPADISERVICESCIHOOKMACROS_H

#include "scihook/scihookdefs.h"
#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_ADI_REMAPADI_DISABLED)
#include "SciHook.h"
#include "remap/adi/__RemapADIServiceContexts.h"
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_ADI_REMAPADI_DISABLED)
#define SCIHOOK_DECLARE_REMAP_ADI_REMAPADI_EVENTS \
private:\
 size_t SYNCHRONIZEDUALUREMAP_BEFORE;\
 size_t SYNCHRONIZEDUALUREMAP_AFTER;\
 size_t COMPUTEANDLIMITGRADPHI_BEFORE;\
 size_t COMPUTEANDLIMITGRADPHI_AFTER;\
 size_t COMPUTEDUALGRADPHI_BEFORE;\
 size_t COMPUTEDUALGRADPHI_AFTER;\
 size_t COMPUTEANDLIMITGRADPHIDUAL_BEFORE;\
 size_t COMPUTEANDLIMITGRADPHIDUAL_AFTER;\
 size_t FLUXLIMITER_BEFORE;\
 size_t FLUXLIMITER_AFTER;\
 size_t FLUXLIMITERG_BEFORE;\
 size_t FLUXLIMITERG_AFTER;\
 size_t COMPUTEFLUXPP_BEFORE;\
 size_t COMPUTEFLUXPP_AFTER;\
 size_t COMPUTEY0_BEFORE;\
 size_t COMPUTEY0_AFTER;\
 size_t COMPUTEXGXD_BEFORE;\
 size_t COMPUTEXGXD_AFTER;\
 size_t COMPUTEYGYD_BEFORE;\
 size_t COMPUTEYGYD_AFTER;\
 size_t INTY_BEFORE;\
 size_t INTY_AFTER;\
 size_t COMPUTEFLUXPPPURE_BEFORE;\
 size_t COMPUTEFLUXPPPURE_AFTER;\
 size_t COMPUTEGRADPHIFACE_BEFORE;\
 size_t COMPUTEGRADPHIFACE_AFTER;\
 size_t COMPUTEGRADPHICELL_BEFORE;\
 size_t COMPUTEGRADPHICELL_AFTER;\
 size_t COMPUTEUPWINDFACEQUANTITIESFORPROJECTION_BEFORE;\
 size_t COMPUTEUPWINDFACEQUANTITIESFORPROJECTION_AFTER;\
 size_t COMPUTEUPWINDFACEQUANTITIESFORPROJECTION_PBORN0_O2_BEFORE;\
 size_t COMPUTEUPWINDFACEQUANTITIESFORPROJECTION_PBORN0_O2_AFTER;\
 size_t COMPUTEUREMAP_BEFORE;\
 size_t COMPUTEUREMAP_AFTER;\
 size_t COMPUTEUREMAP_PBORN0_BEFORE;\
 size_t COMPUTEUREMAP_PBORN0_AFTER;\
 size_t COMPUTEDUALUREMAP_BEFORE;\
 size_t COMPUTEDUALUREMAP_AFTER;\
 size_t COMPUTEREMAPFLUX_BEFORE;\
 size_t COMPUTEREMAPFLUX_AFTER;\
 size_t APPLIREMAP_BEFORE;\
 size_t APPLIREMAP_AFTER;\
 size_t RESIZEREMAPVARIABLES_BEFORE;\
 size_t RESIZEREMAPVARIABLES_AFTER;\
 size_t SYNCHRONIZEUREMAP_BEFORE;\
 size_t SYNCHRONIZEUREMAP_AFTER;\
 size_t REMAPVARIABLES_BEFORE;\
 size_t REMAPVARIABLES_AFTER;
#define SCIHOOK_INITIALIZE_REMAP_ADI_REMAPADI_EVENTS \
SYNCHRONIZEDUALUREMAP_BEFORE = SciHook::register_base_event("RemapADI.SynchronizeDualUremap.Before");\
SYNCHRONIZEDUALUREMAP_AFTER = SciHook::register_base_event("RemapADI.SynchronizeDualUremap.After");\
COMPUTEANDLIMITGRADPHI_BEFORE = SciHook::register_base_event("RemapADI.ComputeAndLimitGradPhi.Before");\
COMPUTEANDLIMITGRADPHI_AFTER = SciHook::register_base_event("RemapADI.ComputeAndLimitGradPhi.After");\
COMPUTEDUALGRADPHI_BEFORE = SciHook::register_base_event("RemapADI.ComputeDualGradPhi.Before");\
COMPUTEDUALGRADPHI_AFTER = SciHook::register_base_event("RemapADI.ComputeDualGradPhi.After");\
COMPUTEANDLIMITGRADPHIDUAL_BEFORE = SciHook::register_base_event("RemapADI.ComputeAndLimitGradPhiDual.Before");\
COMPUTEANDLIMITGRADPHIDUAL_AFTER = SciHook::register_base_event("RemapADI.ComputeAndLimitGradPhiDual.After");\
FLUXLIMITER_BEFORE = SciHook::register_base_event("RemapADI.FluxLimiter.Before");\
FLUXLIMITER_AFTER = SciHook::register_base_event("RemapADI.FluxLimiter.After");\
FLUXLIMITERG_BEFORE = SciHook::register_base_event("RemapADI.FluxLimiterG.Before");\
FLUXLIMITERG_AFTER = SciHook::register_base_event("RemapADI.FluxLimiterG.After");\
COMPUTEFLUXPP_BEFORE = SciHook::register_base_event("RemapADI.ComputeFluxPP.Before");\
COMPUTEFLUXPP_AFTER = SciHook::register_base_event("RemapADI.ComputeFluxPP.After");\
COMPUTEY0_BEFORE = SciHook::register_base_event("RemapADI.ComputeY0.Before");\
COMPUTEY0_AFTER = SciHook::register_base_event("RemapADI.ComputeY0.After");\
COMPUTEXGXD_BEFORE = SciHook::register_base_event("RemapADI.Computexgxd.Before");\
COMPUTEXGXD_AFTER = SciHook::register_base_event("RemapADI.Computexgxd.After");\
COMPUTEYGYD_BEFORE = SciHook::register_base_event("RemapADI.Computeygyd.Before");\
COMPUTEYGYD_AFTER = SciHook::register_base_event("RemapADI.Computeygyd.After");\
INTY_BEFORE = SciHook::register_base_event("RemapADI.INTY.Before");\
INTY_AFTER = SciHook::register_base_event("RemapADI.INTY.After");\
COMPUTEFLUXPPPURE_BEFORE = SciHook::register_base_event("RemapADI.ComputeFluxPPPure.Before");\
COMPUTEFLUXPPPURE_AFTER = SciHook::register_base_event("RemapADI.ComputeFluxPPPure.After");\
COMPUTEGRADPHIFACE_BEFORE = SciHook::register_base_event("RemapADI.ComputeGradPhiFace.Before");\
COMPUTEGRADPHIFACE_AFTER = SciHook::register_base_event("RemapADI.ComputeGradPhiFace.After");\
COMPUTEGRADPHICELL_BEFORE = SciHook::register_base_event("RemapADI.ComputeGradPhiCell.Before");\
COMPUTEGRADPHICELL_AFTER = SciHook::register_base_event("RemapADI.ComputeGradPhiCell.After");\
COMPUTEUPWINDFACEQUANTITIESFORPROJECTION_BEFORE = SciHook::register_base_event("RemapADI.ComputeUpwindFaceQuantitiesForProjection.Before");\
COMPUTEUPWINDFACEQUANTITIESFORPROJECTION_AFTER = SciHook::register_base_event("RemapADI.ComputeUpwindFaceQuantitiesForProjection.After");\
COMPUTEUPWINDFACEQUANTITIESFORPROJECTION_PBORN0_O2_BEFORE = SciHook::register_base_event("RemapADI.ComputeUpwindFaceQuantitiesForProjection_PBorn0_O2.Before");\
COMPUTEUPWINDFACEQUANTITIESFORPROJECTION_PBORN0_O2_AFTER = SciHook::register_base_event("RemapADI.ComputeUpwindFaceQuantitiesForProjection_PBorn0_O2.After");\
COMPUTEUREMAP_BEFORE = SciHook::register_base_event("RemapADI.ComputeUremap.Before");\
COMPUTEUREMAP_AFTER = SciHook::register_base_event("RemapADI.ComputeUremap.After");\
COMPUTEUREMAP_PBORN0_BEFORE = SciHook::register_base_event("RemapADI.ComputeUremap_PBorn0.Before");\
COMPUTEUREMAP_PBORN0_AFTER = SciHook::register_base_event("RemapADI.ComputeUremap_PBorn0.After");\
COMPUTEDUALUREMAP_BEFORE = SciHook::register_base_event("RemapADI.ComputeDualUremap.Before");\
COMPUTEDUALUREMAP_AFTER = SciHook::register_base_event("RemapADI.ComputeDualUremap.After");\
COMPUTEREMAPFLUX_BEFORE = SciHook::register_base_event("RemapADI.ComputeRemapFlux.Before");\
COMPUTEREMAPFLUX_AFTER = SciHook::register_base_event("RemapADI.ComputeRemapFlux.After");\
APPLIREMAP_BEFORE = SciHook::register_base_event("RemapADI.AppliRemap.Before");\
APPLIREMAP_AFTER = SciHook::register_base_event("RemapADI.AppliRemap.After");\
RESIZEREMAPVARIABLES_BEFORE = SciHook::register_base_event("RemapADI.ResizeRemapVariables.Before");\
RESIZEREMAPVARIABLES_AFTER = SciHook::register_base_event("RemapADI.ResizeRemapVariables.After");\
SYNCHRONIZEUREMAP_BEFORE = SciHook::register_base_event("RemapADI.SynchronizeUremap.Before");\
SYNCHRONIZEUREMAP_AFTER = SciHook::register_base_event("RemapADI.SynchronizeUremap.After");\
REMAPVARIABLES_BEFORE = SciHook::register_base_event("RemapADI.RemapVariables.Before");\
REMAPVARIABLES_AFTER = SciHook::register_base_event("RemapADI.RemapVariables.After");
#else
#define SCIHOOK_DECLARE_REMAP_ADI_REMAPADI_EVENTS
#define SCIHOOK_INITIALIZE_REMAP_ADI_REMAPADI_EVENTS
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_ADI_REMAPADI_DISABLED) && not defined(SCIHOOK_REMAP_ADI_REMAPADI_SYNCHRONIZEDUALUREMAP_DISABLED)
#define SCIHOOK_TRIGGER_SYNCHRONIZEDUALUREMAP_BEFORE \
std::shared_ptr<RemapADISynchronizeDualUremapExecutionContext> ctx(new RemapADISynchronizeDualUremapExecutionContext("SynchronizeDualUremapExecutionContext", &vars));\
SciHook::trigger(SYNCHRONIZEDUALUREMAP_BEFORE, ctx);
#define SCIHOOK_TRIGGER_SYNCHRONIZEDUALUREMAP_AFTER SciHook::trigger(SYNCHRONIZEDUALUREMAP_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_SYNCHRONIZEDUALUREMAP_BEFORE
#define SCIHOOK_TRIGGER_SYNCHRONIZEDUALUREMAP_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_ADI_REMAPADI_DISABLED) && not defined(SCIHOOK_REMAP_ADI_REMAPADI_COMPUTEANDLIMITGRADPHI_DISABLED)
#define SCIHOOK_TRIGGER_COMPUTEANDLIMITGRADPHI_BEFORE \
std::shared_ptr<RemapADIComputeAndLimitGradPhiExecutionContext> ctx(new RemapADIComputeAndLimitGradPhiExecutionContext("ComputeAndLimitGradPhiExecutionContext", &vars, projectionLimiterId, frontFace, backFace, cell, frontcell, backcell, nb_vars));\
SciHook::trigger(COMPUTEANDLIMITGRADPHI_BEFORE, ctx);
#define SCIHOOK_TRIGGER_COMPUTEANDLIMITGRADPHI_AFTER SciHook::trigger(COMPUTEANDLIMITGRADPHI_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_COMPUTEANDLIMITGRADPHI_BEFORE
#define SCIHOOK_TRIGGER_COMPUTEANDLIMITGRADPHI_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_ADI_REMAPADI_DISABLED) && not defined(SCIHOOK_REMAP_ADI_REMAPADI_COMPUTEDUALGRADPHI_DISABLED)
#define SCIHOOK_TRIGGER_COMPUTEDUALGRADPHI_BEFORE \
std::shared_ptr<RemapADIComputeDualGradPhiExecutionContext> ctx(new RemapADIComputeDualGradPhiExecutionContext("ComputeDualGradPhiExecutionContext", &vars, inode, frontfrontnode, frontnode, backnode, backbacknode, idir));\
SciHook::trigger(COMPUTEDUALGRADPHI_BEFORE, ctx);
#define SCIHOOK_TRIGGER_COMPUTEDUALGRADPHI_AFTER SciHook::trigger(COMPUTEDUALGRADPHI_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_COMPUTEDUALGRADPHI_BEFORE
#define SCIHOOK_TRIGGER_COMPUTEDUALGRADPHI_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_ADI_REMAPADI_DISABLED) && not defined(SCIHOOK_REMAP_ADI_REMAPADI_COMPUTEANDLIMITGRADPHIDUAL_DISABLED)
#define SCIHOOK_TRIGGER_COMPUTEANDLIMITGRADPHIDUAL_BEFORE \
std::shared_ptr<RemapADIComputeAndLimitGradPhiDualExecutionContext> ctx(new RemapADIComputeAndLimitGradPhiDualExecutionContext("ComputeAndLimitGradPhiDualExecutionContext", &vars, projectionLimiterId, inode, frontnode, backnode, grad_front, grad_back, h0, hplus, hmoins));\
SciHook::trigger(COMPUTEANDLIMITGRADPHIDUAL_BEFORE, ctx);
#define SCIHOOK_TRIGGER_COMPUTEANDLIMITGRADPHIDUAL_AFTER SciHook::trigger(COMPUTEANDLIMITGRADPHIDUAL_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_COMPUTEANDLIMITGRADPHIDUAL_BEFORE
#define SCIHOOK_TRIGGER_COMPUTEANDLIMITGRADPHIDUAL_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_ADI_REMAPADI_DISABLED) && not defined(SCIHOOK_REMAP_ADI_REMAPADI_FLUXLIMITER_DISABLED)
#define SCIHOOK_TRIGGER_FLUXLIMITER_BEFORE \
std::shared_ptr<RemapADIFluxLimiterExecutionContext> ctx(new RemapADIFluxLimiterExecutionContext("FluxLimiterExecutionContext", projectionLimiterId, r));\
SciHook::trigger(FLUXLIMITER_BEFORE, ctx);
#define SCIHOOK_TRIGGER_FLUXLIMITER_AFTER SciHook::trigger(FLUXLIMITER_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_FLUXLIMITER_BEFORE
#define SCIHOOK_TRIGGER_FLUXLIMITER_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_ADI_REMAPADI_DISABLED) && not defined(SCIHOOK_REMAP_ADI_REMAPADI_FLUXLIMITERG_DISABLED)
#define SCIHOOK_TRIGGER_FLUXLIMITERG_BEFORE \
std::shared_ptr<RemapADIFluxLimiterGExecutionContext> ctx(new RemapADIFluxLimiterGExecutionContext("FluxLimiterGExecutionContext", projectionLimiterId, gradplus, gradmoins, y0, yplus, ymoins, h0, hplus, hmoins));\
SciHook::trigger(FLUXLIMITERG_BEFORE, ctx);
#define SCIHOOK_TRIGGER_FLUXLIMITERG_AFTER SciHook::trigger(FLUXLIMITERG_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_FLUXLIMITERG_BEFORE
#define SCIHOOK_TRIGGER_FLUXLIMITERG_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_ADI_REMAPADI_DISABLED) && not defined(SCIHOOK_REMAP_ADI_REMAPADI_COMPUTEFLUXPP_DISABLED)
#define SCIHOOK_TRIGGER_COMPUTEFLUXPP_BEFORE \
std::shared_ptr<RemapADIComputeFluxPPExecutionContext> ctx(new RemapADIComputeFluxPPExecutionContext("ComputeFluxPPExecutionContext", &vars, cell, frontcell, backcell, face_normal_velocity, deltat_n, type, flux_threshold, projectionPenteBorneDebarFix, dual_normal_velocity, calcul_flux_dual, flux, flux_dual, nbmat, nb_vars));\
SciHook::trigger(COMPUTEFLUXPP_BEFORE, ctx);
#define SCIHOOK_TRIGGER_COMPUTEFLUXPP_AFTER SciHook::trigger(COMPUTEFLUXPP_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_COMPUTEFLUXPP_BEFORE
#define SCIHOOK_TRIGGER_COMPUTEFLUXPP_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_ADI_REMAPADI_DISABLED) && not defined(SCIHOOK_REMAP_ADI_REMAPADI_COMPUTEY0_DISABLED)
#define SCIHOOK_TRIGGER_COMPUTEY0_BEFORE \
std::shared_ptr<RemapADIComputeY0ExecutionContext> ctx(new RemapADIComputeY0ExecutionContext("ComputeY0ExecutionContext", projectionLimiterId, y0, yplus, ymoins, h0, hplus, hmoins, type));\
SciHook::trigger(COMPUTEY0_BEFORE, ctx);
#define SCIHOOK_TRIGGER_COMPUTEY0_AFTER SciHook::trigger(COMPUTEY0_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_COMPUTEY0_BEFORE
#define SCIHOOK_TRIGGER_COMPUTEY0_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_ADI_REMAPADI_DISABLED) && not defined(SCIHOOK_REMAP_ADI_REMAPADI_COMPUTEXGXD_DISABLED)
#define SCIHOOK_TRIGGER_COMPUTEXGXD_BEFORE \
std::shared_ptr<RemapADIComputexgxdExecutionContext> ctx(new RemapADIComputexgxdExecutionContext("ComputexgxdExecutionContext", y0, yplus, ymoins, h0, y0plus, y0moins, type));\
SciHook::trigger(COMPUTEXGXD_BEFORE, ctx);
#define SCIHOOK_TRIGGER_COMPUTEXGXD_AFTER SciHook::trigger(COMPUTEXGXD_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_COMPUTEXGXD_BEFORE
#define SCIHOOK_TRIGGER_COMPUTEXGXD_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_ADI_REMAPADI_DISABLED) && not defined(SCIHOOK_REMAP_ADI_REMAPADI_COMPUTEYGYD_DISABLED)
#define SCIHOOK_TRIGGER_COMPUTEYGYD_BEFORE \
std::shared_ptr<RemapADIComputeygydExecutionContext> ctx(new RemapADIComputeygydExecutionContext("ComputeygydExecutionContext", y0, yplus, ymoins, h0, y0plus, y0moins, grady, type));\
SciHook::trigger(COMPUTEYGYD_BEFORE, ctx);
#define SCIHOOK_TRIGGER_COMPUTEYGYD_AFTER SciHook::trigger(COMPUTEYGYD_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_COMPUTEYGYD_BEFORE
#define SCIHOOK_TRIGGER_COMPUTEYGYD_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_ADI_REMAPADI_DISABLED) && not defined(SCIHOOK_REMAP_ADI_REMAPADI_INTY_DISABLED)
#define SCIHOOK_TRIGGER_INTY_BEFORE \
std::shared_ptr<RemapADIINTYExecutionContext> ctx(new RemapADIINTYExecutionContext("INTYExecutionContext", X, x0, y0, x1, y1));\
SciHook::trigger(INTY_BEFORE, ctx);
#define SCIHOOK_TRIGGER_INTY_AFTER SciHook::trigger(INTY_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_INTY_BEFORE
#define SCIHOOK_TRIGGER_INTY_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_ADI_REMAPADI_DISABLED) && not defined(SCIHOOK_REMAP_ADI_REMAPADI_COMPUTEFLUXPPPURE_DISABLED)
#define SCIHOOK_TRIGGER_COMPUTEFLUXPPPURE_BEFORE \
std::shared_ptr<RemapADIComputeFluxPPPureExecutionContext> ctx(new RemapADIComputeFluxPPPureExecutionContext("ComputeFluxPPPureExecutionContext", &vars, cell, frontcell, backcell, face_normal_velocity, deltat_n, type, flux_threshold, projectionPenteBorneDebarFix, dual_normal_velocity, calcul_flux_dual, Flux, Flux_dual, nbmat, nb_vars));\
SciHook::trigger(COMPUTEFLUXPPPURE_BEFORE, ctx);
#define SCIHOOK_TRIGGER_COMPUTEFLUXPPPURE_AFTER SciHook::trigger(COMPUTEFLUXPPPURE_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_COMPUTEFLUXPPPURE_BEFORE
#define SCIHOOK_TRIGGER_COMPUTEFLUXPPPURE_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_ADI_REMAPADI_DISABLED) && not defined(SCIHOOK_REMAP_ADI_REMAPADI_COMPUTEGRADPHIFACE_DISABLED)
#define SCIHOOK_TRIGGER_COMPUTEGRADPHIFACE_BEFORE \
std::shared_ptr<RemapADIComputeGradPhiFaceExecutionContext> ctx(new RemapADIComputeGradPhiFaceExecutionContext("ComputeGradPhiFaceExecutionContext", &vars, idir, nb_vars_to_project, nb_env));\
SciHook::trigger(COMPUTEGRADPHIFACE_BEFORE, ctx);
#define SCIHOOK_TRIGGER_COMPUTEGRADPHIFACE_AFTER SciHook::trigger(COMPUTEGRADPHIFACE_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_COMPUTEGRADPHIFACE_BEFORE
#define SCIHOOK_TRIGGER_COMPUTEGRADPHIFACE_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_ADI_REMAPADI_DISABLED) && not defined(SCIHOOK_REMAP_ADI_REMAPADI_COMPUTEGRADPHICELL_DISABLED)
#define SCIHOOK_TRIGGER_COMPUTEGRADPHICELL_BEFORE \
std::shared_ptr<RemapADIComputeGradPhiCellExecutionContext> ctx(new RemapADIComputeGradPhiCellExecutionContext("ComputeGradPhiCellExecutionContext", &vars, idir, nb_vars_to_project, nb_env));\
SciHook::trigger(COMPUTEGRADPHICELL_BEFORE, ctx);
#define SCIHOOK_TRIGGER_COMPUTEGRADPHICELL_AFTER SciHook::trigger(COMPUTEGRADPHICELL_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_COMPUTEGRADPHICELL_BEFORE
#define SCIHOOK_TRIGGER_COMPUTEGRADPHICELL_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_ADI_REMAPADI_DISABLED) && not defined(SCIHOOK_REMAP_ADI_REMAPADI_COMPUTEUPWINDFACEQUANTITIESFORPROJECTION_DISABLED)
#define SCIHOOK_TRIGGER_COMPUTEUPWINDFACEQUANTITIESFORPROJECTION_BEFORE \
std::shared_ptr<RemapADIComputeUpwindFaceQuantitiesForProjectionExecutionContext> ctx(new RemapADIComputeUpwindFaceQuantitiesForProjectionExecutionContext("ComputeUpwindFaceQuantitiesForProjectionExecutionContext", &vars, idir, nb_vars_to_project, nb_env));\
SciHook::trigger(COMPUTEUPWINDFACEQUANTITIESFORPROJECTION_BEFORE, ctx);
#define SCIHOOK_TRIGGER_COMPUTEUPWINDFACEQUANTITIESFORPROJECTION_AFTER SciHook::trigger(COMPUTEUPWINDFACEQUANTITIESFORPROJECTION_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_COMPUTEUPWINDFACEQUANTITIESFORPROJECTION_BEFORE
#define SCIHOOK_TRIGGER_COMPUTEUPWINDFACEQUANTITIESFORPROJECTION_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_ADI_REMAPADI_DISABLED) && not defined(SCIHOOK_REMAP_ADI_REMAPADI_COMPUTEUPWINDFACEQUANTITIESFORPROJECTION_PBORN0_O2_DISABLED)
#define SCIHOOK_TRIGGER_COMPUTEUPWINDFACEQUANTITIESFORPROJECTION_PBORN0_O2_BEFORE \
std::shared_ptr<RemapADIComputeUpwindFaceQuantitiesForProjection_PBorn0_O2ExecutionContext> ctx(new RemapADIComputeUpwindFaceQuantitiesForProjection_PBorn0_O2ExecutionContext("ComputeUpwindFaceQuantitiesForProjection_PBorn0_O2ExecutionContext", &vars, idir, nb_vars_to_project));\
SciHook::trigger(COMPUTEUPWINDFACEQUANTITIESFORPROJECTION_PBORN0_O2_BEFORE, ctx);
#define SCIHOOK_TRIGGER_COMPUTEUPWINDFACEQUANTITIESFORPROJECTION_PBORN0_O2_AFTER SciHook::trigger(COMPUTEUPWINDFACEQUANTITIESFORPROJECTION_PBORN0_O2_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_COMPUTEUPWINDFACEQUANTITIESFORPROJECTION_PBORN0_O2_BEFORE
#define SCIHOOK_TRIGGER_COMPUTEUPWINDFACEQUANTITIESFORPROJECTION_PBORN0_O2_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_ADI_REMAPADI_DISABLED) && not defined(SCIHOOK_REMAP_ADI_REMAPADI_COMPUTEUREMAP_DISABLED)
#define SCIHOOK_TRIGGER_COMPUTEUREMAP_BEFORE \
std::shared_ptr<RemapADIComputeUremapExecutionContext> ctx(new RemapADIComputeUremapExecutionContext("ComputeUremapExecutionContext", &vars, idir, nb_vars_to_project, nb_env));\
SciHook::trigger(COMPUTEUREMAP_BEFORE, ctx);
#define SCIHOOK_TRIGGER_COMPUTEUREMAP_AFTER SciHook::trigger(COMPUTEUREMAP_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_COMPUTEUREMAP_BEFORE
#define SCIHOOK_TRIGGER_COMPUTEUREMAP_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_ADI_REMAPADI_DISABLED) && not defined(SCIHOOK_REMAP_ADI_REMAPADI_COMPUTEUREMAP_PBORN0_DISABLED)
#define SCIHOOK_TRIGGER_COMPUTEUREMAP_PBORN0_BEFORE \
std::shared_ptr<RemapADIComputeUremap_PBorn0ExecutionContext> ctx(new RemapADIComputeUremap_PBorn0ExecutionContext("ComputeUremap_PBorn0ExecutionContext", &vars, idir, nb_vars_to_project, nb_env));\
SciHook::trigger(COMPUTEUREMAP_PBORN0_BEFORE, ctx);
#define SCIHOOK_TRIGGER_COMPUTEUREMAP_PBORN0_AFTER SciHook::trigger(COMPUTEUREMAP_PBORN0_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_COMPUTEUREMAP_PBORN0_BEFORE
#define SCIHOOK_TRIGGER_COMPUTEUREMAP_PBORN0_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_ADI_REMAPADI_DISABLED) && not defined(SCIHOOK_REMAP_ADI_REMAPADI_COMPUTEDUALUREMAP_DISABLED)
#define SCIHOOK_TRIGGER_COMPUTEDUALUREMAP_BEFORE \
std::shared_ptr<RemapADIComputeDualUremapExecutionContext> ctx(new RemapADIComputeDualUremapExecutionContext("ComputeDualUremapExecutionContext", &vars, idir, nb_env));\
SciHook::trigger(COMPUTEDUALUREMAP_BEFORE, ctx);
#define SCIHOOK_TRIGGER_COMPUTEDUALUREMAP_AFTER SciHook::trigger(COMPUTEDUALUREMAP_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_COMPUTEDUALUREMAP_BEFORE
#define SCIHOOK_TRIGGER_COMPUTEDUALUREMAP_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_ADI_REMAPADI_DISABLED) && not defined(SCIHOOK_REMAP_ADI_REMAPADI_COMPUTEREMAPFLUX_DISABLED)
#define SCIHOOK_TRIGGER_COMPUTEREMAPFLUX_BEFORE \
std::shared_ptr<RemapADIComputeRemapFluxExecutionContext> ctx(new RemapADIComputeRemapFluxExecutionContext("ComputeRemapFluxExecutionContext", projectionOrder, projectionAvecPlateauPente, face_normal_velocity, face_normal, face_length, phi_face, outer_face_normal, exy, deltat_n));\
SciHook::trigger(COMPUTEREMAPFLUX_BEFORE, ctx);
#define SCIHOOK_TRIGGER_COMPUTEREMAPFLUX_AFTER SciHook::trigger(COMPUTEREMAPFLUX_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_COMPUTEREMAPFLUX_BEFORE
#define SCIHOOK_TRIGGER_COMPUTEREMAPFLUX_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_ADI_REMAPADI_DISABLED) && not defined(SCIHOOK_REMAP_ADI_REMAPADI_APPLIREMAP_DISABLED)
#define SCIHOOK_TRIGGER_APPLIREMAP_BEFORE \
std::shared_ptr<RemapADIAppliRemapExecutionContext> ctx(new RemapADIAppliRemapExecutionContext("AppliRemapExecutionContext", &vars, dimension, withDualProjection, nb_vars_to_project, nb_env));\
SciHook::trigger(APPLIREMAP_BEFORE, ctx);
#define SCIHOOK_TRIGGER_APPLIREMAP_AFTER SciHook::trigger(APPLIREMAP_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_APPLIREMAP_BEFORE
#define SCIHOOK_TRIGGER_APPLIREMAP_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_ADI_REMAPADI_DISABLED) && not defined(SCIHOOK_REMAP_ADI_REMAPADI_RESIZEREMAPVARIABLES_DISABLED)
#define SCIHOOK_TRIGGER_RESIZEREMAPVARIABLES_BEFORE \
std::shared_ptr<RemapADIResizeRemapVariablesExecutionContext> ctx(new RemapADIResizeRemapVariablesExecutionContext("ResizeRemapVariablesExecutionContext", &vars, nb_vars_to_project, nb_env));\
SciHook::trigger(RESIZEREMAPVARIABLES_BEFORE, ctx);
#define SCIHOOK_TRIGGER_RESIZEREMAPVARIABLES_AFTER SciHook::trigger(RESIZEREMAPVARIABLES_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_RESIZEREMAPVARIABLES_BEFORE
#define SCIHOOK_TRIGGER_RESIZEREMAPVARIABLES_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_ADI_REMAPADI_DISABLED) && not defined(SCIHOOK_REMAP_ADI_REMAPADI_SYNCHRONIZEUREMAP_DISABLED)
#define SCIHOOK_TRIGGER_SYNCHRONIZEUREMAP_BEFORE \
std::shared_ptr<RemapADISynchronizeUremapExecutionContext> ctx(new RemapADISynchronizeUremapExecutionContext("SynchronizeUremapExecutionContext", &vars));\
SciHook::trigger(SYNCHRONIZEUREMAP_BEFORE, ctx);
#define SCIHOOK_TRIGGER_SYNCHRONIZEUREMAP_AFTER SciHook::trigger(SYNCHRONIZEUREMAP_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_SYNCHRONIZEUREMAP_BEFORE
#define SCIHOOK_TRIGGER_SYNCHRONIZEUREMAP_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_ADI_REMAPADI_DISABLED) && not defined(SCIHOOK_REMAP_ADI_REMAPADI_REMAPVARIABLES_DISABLED)
#define SCIHOOK_TRIGGER_REMAPVARIABLES_BEFORE \
std::shared_ptr<RemapADIRemapVariablesExecutionContext> ctx(new RemapADIRemapVariablesExecutionContext("RemapVariablesExecutionContext", &vars, dimension, withDualProjection, nb_vars_to_project, nb_env));\
SciHook::trigger(REMAPVARIABLES_BEFORE, ctx);
#define SCIHOOK_TRIGGER_REMAPVARIABLES_AFTER SciHook::trigger(REMAPVARIABLES_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_REMAPVARIABLES_BEFORE
#define SCIHOOK_TRIGGER_REMAPVARIABLES_AFTER
#endif

#endif // REMAP_ADI___REMAPADISERVICESCIHOOKMACROS_H
