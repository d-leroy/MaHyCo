#ifndef REMAP_ADI___REMAPADISERVICECONTEXTS_H
#define REMAP_ADI___REMAPADISERVICECONTEXTS_H

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
#include "remap/adi/__RemapADIServiceVars.h"
#include "types_mahyco/__Limiteur.h"
#include "arcane/utils/UtilsTypes.h"
#include "scihook/scihookdefs.h"
#include "SciHook.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_ADI_DISABLED)

using namespace Arcane;
using namespace Arcane::Materials;
namespace RemapAdi {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

//! Classe de contexte d'exécution pour synchronizeDualUremap
struct RemapADISynchronizeDualUremapExecutionContext final : SciHook::SciHookExecutionContext
{
  RemapADISynchronizeDualUremapExecutionContext(std::string execution_context_name,
      RemapADISynchronizeDualUremapVars *vars)
  : SciHookExecutionContext(execution_context_name)
  , vars(vars)
  {}

  const RemapADISynchronizeDualUremapVars *vars;

  const pybind11::object get_m_phi_dual_lagrange() const {
    return pybind11::cast(vars->m_phi_dual_lagrange);
  }

  const pybind11::object get_m_u_dual_lagrange() const {
    return pybind11::cast(vars->m_u_dual_lagrange);
  }
};

//! Classe de contexte d'exécution pour computeAndLimitGradPhi
struct RemapADIComputeAndLimitGradPhiExecutionContext final : SciHook::SciHookExecutionContext
{
  RemapADIComputeAndLimitGradPhiExecutionContext(std::string execution_context_name,
      RemapADIComputeAndLimitGradPhiVars *vars,
      const ::Types_mahyco::Limiteur projectionLimiterId,
      const Face frontFace,
      const Face backFace,
      const Cell cell,
      const Cell frontcell,
      const Cell backcell,
      const Integer nb_vars)
  : SciHookExecutionContext(execution_context_name)
  , projectionLimiterId(projectionLimiterId)
  , frontFace(frontFace)
  , backFace(backFace)
  , cell(cell)
  , frontcell(frontcell)
  , backcell(backcell)
  , nb_vars(nb_vars)
  , vars(vars)
  {}

  const ::Types_mahyco::Limiteur projectionLimiterId;
  const Face frontFace;
  const Face backFace;
  const Cell cell;
  const Cell frontcell;
  const Cell backcell;
  const Integer nb_vars;
  const RemapADIComputeAndLimitGradPhiVars *vars;

  const pybind11::object get_projectionLimiterId() const {
    return pybind11::cast(projectionLimiterId);
  }

  const pybind11::object get_frontFace() const {
    return pybind11::cast(frontFace);
  }

  const pybind11::object get_backFace() const {
    return pybind11::cast(backFace);
  }

  const pybind11::object get_cell() const {
    return pybind11::cast(cell);
  }

  const pybind11::object get_frontcell() const {
    return pybind11::cast(frontcell);
  }

  const pybind11::object get_backcell() const {
    return pybind11::cast(backcell);
  }

  const pybind11::object get_nb_vars() const {
    return pybind11::cast(nb_vars);
  }

  const pybind11::object get_m_grad_phi() const {
    return pybind11::cast(vars->m_grad_phi);
  }

  const pybind11::object get_m_grad_phi_face() const {
    return pybind11::cast(vars->m_grad_phi_face);
  }

  const pybind11::object get_m_phi_lagrange() const {
    return pybind11::cast(vars->m_phi_lagrange);
  }

  const pybind11::object get_m_h_cell_lagrange() const {
    return pybind11::cast(vars->m_h_cell_lagrange);
  }
};

//! Classe de contexte d'exécution pour computeDualGradPhi
struct RemapADIComputeDualGradPhiExecutionContext final : SciHook::SciHookExecutionContext
{
  RemapADIComputeDualGradPhiExecutionContext(std::string execution_context_name,
      RemapADIComputeDualGradPhiVars *vars,
      const Node inode,
      const Node frontfrontnode,
      const Node frontnode,
      const Node backnode,
      const Node backbacknode,
      const Integer idir)
  : SciHookExecutionContext(execution_context_name)
  , inode(inode)
  , frontfrontnode(frontfrontnode)
  , frontnode(frontnode)
  , backnode(backnode)
  , backbacknode(backbacknode)
  , idir(idir)
  , vars(vars)
  {}

  const Node inode;
  const Node frontfrontnode;
  const Node frontnode;
  const Node backnode;
  const Node backbacknode;
  const Integer idir;
  const RemapADIComputeDualGradPhiVars *vars;

  const pybind11::object get_inode() const {
    return pybind11::cast(inode);
  }

  const pybind11::object get_frontfrontnode() const {
    return pybind11::cast(frontfrontnode);
  }

  const pybind11::object get_frontnode() const {
    return pybind11::cast(frontnode);
  }

  const pybind11::object get_backnode() const {
    return pybind11::cast(backnode);
  }

  const pybind11::object get_backbacknode() const {
    return pybind11::cast(backbacknode);
  }

  const pybind11::object get_idir() const {
    return pybind11::cast(idir);
  }

  const pybind11::object get_m_phi_dual_lagrange() const {
    return pybind11::cast(vars->m_phi_dual_lagrange);
  }

  const pybind11::object get_m_node_coord() const {
    return pybind11::cast(vars->m_node_coord);
  }
};

//! Classe de contexte d'exécution pour computeAndLimitGradPhiDual
struct RemapADIComputeAndLimitGradPhiDualExecutionContext final : SciHook::SciHookExecutionContext
{
  RemapADIComputeAndLimitGradPhiDualExecutionContext(std::string execution_context_name,
      RemapADIComputeAndLimitGradPhiDualVars *vars,
      const ::Types_mahyco::Limiteur projectionLimiterId,
      const Node inode,
      const Node frontnode,
      const Node backnode,
      const Real3 grad_front,
      const Real3 grad_back,
      const Real h0,
      const Real hplus,
      const Real hmoins)
  : SciHookExecutionContext(execution_context_name)
  , projectionLimiterId(projectionLimiterId)
  , inode(inode)
  , frontnode(frontnode)
  , backnode(backnode)
  , grad_front(grad_front)
  , grad_back(grad_back)
  , h0(h0)
  , hplus(hplus)
  , hmoins(hmoins)
  , vars(vars)
  {}

  const ::Types_mahyco::Limiteur projectionLimiterId;
  const Node inode;
  const Node frontnode;
  const Node backnode;
  const Real3 grad_front;
  const Real3 grad_back;
  const Real h0;
  const Real hplus;
  const Real hmoins;
  const RemapADIComputeAndLimitGradPhiDualVars *vars;

  const pybind11::object get_projectionLimiterId() const {
    return pybind11::cast(projectionLimiterId);
  }

  const pybind11::object get_inode() const {
    return pybind11::cast(inode);
  }

  const pybind11::object get_frontnode() const {
    return pybind11::cast(frontnode);
  }

  const pybind11::object get_backnode() const {
    return pybind11::cast(backnode);
  }

  const pybind11::object get_grad_front() const {
    return pybind11::cast(grad_front);
  }

  const pybind11::object get_grad_back() const {
    return pybind11::cast(grad_back);
  }

  const pybind11::object get_h0() const {
    return pybind11::cast(h0);
  }

  const pybind11::object get_hplus() const {
    return pybind11::cast(hplus);
  }

  const pybind11::object get_hmoins() const {
    return pybind11::cast(hmoins);
  }

  const pybind11::object get_m_phi_dual_lagrange() const {
    return pybind11::cast(vars->m_phi_dual_lagrange);
  }

  const pybind11::object get_m_dual_grad_phi() const {
    return pybind11::cast(vars->m_dual_grad_phi);
  }
};

//! Classe de contexte d'exécution pour fluxLimiter
struct RemapADIFluxLimiterExecutionContext final : SciHook::SciHookExecutionContext
{
  RemapADIFluxLimiterExecutionContext(std::string execution_context_name,
      const ::Types_mahyco::Limiteur projectionLimiterId,
      const Real r)
  : SciHookExecutionContext(execution_context_name)
  , projectionLimiterId(projectionLimiterId)
  , r(r)
  {}

  const ::Types_mahyco::Limiteur projectionLimiterId;
  const Real r;

  const pybind11::object get_projectionLimiterId() const {
    return pybind11::cast(projectionLimiterId);
  }

  const pybind11::object get_r() const {
    return pybind11::cast(r);
  }
};

//! Classe de contexte d'exécution pour fluxLimiterG
struct RemapADIFluxLimiterGExecutionContext final : SciHook::SciHookExecutionContext
{
  RemapADIFluxLimiterGExecutionContext(std::string execution_context_name,
      const ::Types_mahyco::Limiteur projectionLimiterId,
      const Real gradplus,
      const Real gradmoins,
      const Real y0,
      const Real yplus,
      const Real ymoins,
      const Real h0,
      const Real hplus,
      const Real hmoins)
  : SciHookExecutionContext(execution_context_name)
  , projectionLimiterId(projectionLimiterId)
  , gradplus(gradplus)
  , gradmoins(gradmoins)
  , y0(y0)
  , yplus(yplus)
  , ymoins(ymoins)
  , h0(h0)
  , hplus(hplus)
  , hmoins(hmoins)
  {}

  const ::Types_mahyco::Limiteur projectionLimiterId;
  const Real gradplus;
  const Real gradmoins;
  const Real y0;
  const Real yplus;
  const Real ymoins;
  const Real h0;
  const Real hplus;
  const Real hmoins;

  const pybind11::object get_projectionLimiterId() const {
    return pybind11::cast(projectionLimiterId);
  }

  const pybind11::object get_gradplus() const {
    return pybind11::cast(gradplus);
  }

  const pybind11::object get_gradmoins() const {
    return pybind11::cast(gradmoins);
  }

  const pybind11::object get_y0() const {
    return pybind11::cast(y0);
  }

  const pybind11::object get_yplus() const {
    return pybind11::cast(yplus);
  }

  const pybind11::object get_ymoins() const {
    return pybind11::cast(ymoins);
  }

  const pybind11::object get_h0() const {
    return pybind11::cast(h0);
  }

  const pybind11::object get_hplus() const {
    return pybind11::cast(hplus);
  }

  const pybind11::object get_hmoins() const {
    return pybind11::cast(hmoins);
  }
};

//! Classe de contexte d'exécution pour computeFluxPP
struct RemapADIComputeFluxPPExecutionContext final : SciHook::SciHookExecutionContext
{
  RemapADIComputeFluxPPExecutionContext(std::string execution_context_name,
      RemapADIComputeFluxPPVars *vars,
      const Cell cell,
      const Cell frontcell,
      const Cell backcell,
      const Real face_normal_velocity,
      const Real deltat_n,
      const Integer type,
      const Real flux_threshold,
      const Integer projectionPenteBorneDebarFix,
      const Real dual_normal_velocity,
      const Integer calcul_flux_dual,
      ::Arcane::RealArrayView* flux,
      ::Arcane::RealArrayView* flux_dual,
      const Integer nbmat,
      const Integer nb_vars)
  : SciHookExecutionContext(execution_context_name)
  , cell(cell)
  , frontcell(frontcell)
  , backcell(backcell)
  , face_normal_velocity(face_normal_velocity)
  , deltat_n(deltat_n)
  , type(type)
  , flux_threshold(flux_threshold)
  , projectionPenteBorneDebarFix(projectionPenteBorneDebarFix)
  , dual_normal_velocity(dual_normal_velocity)
  , calcul_flux_dual(calcul_flux_dual)
  , flux(flux)
  , flux_dual(flux_dual)
  , nbmat(nbmat)
  , nb_vars(nb_vars)
  , vars(vars)
  {}

  const Cell cell;
  const Cell frontcell;
  const Cell backcell;
  const Real face_normal_velocity;
  const Real deltat_n;
  const Integer type;
  const Real flux_threshold;
  const Integer projectionPenteBorneDebarFix;
  const Real dual_normal_velocity;
  const Integer calcul_flux_dual;
  ::Arcane::RealArrayView* flux;
  ::Arcane::RealArrayView* flux_dual;
  const Integer nbmat;
  const Integer nb_vars;
  const RemapADIComputeFluxPPVars *vars;

  const pybind11::object get_cell() const {
    return pybind11::cast(cell);
  }

  const pybind11::object get_frontcell() const {
    return pybind11::cast(frontcell);
  }

  const pybind11::object get_backcell() const {
    return pybind11::cast(backcell);
  }

  const pybind11::object get_face_normal_velocity() const {
    return pybind11::cast(face_normal_velocity);
  }

  const pybind11::object get_deltat_n() const {
    return pybind11::cast(deltat_n);
  }

  const pybind11::object get_type() const {
    return pybind11::cast(type);
  }

  const pybind11::object get_flux_threshold() const {
    return pybind11::cast(flux_threshold);
  }

  const pybind11::object get_projectionPenteBorneDebarFix() const {
    return pybind11::cast(projectionPenteBorneDebarFix);
  }

  const pybind11::object get_dual_normal_velocity() const {
    return pybind11::cast(dual_normal_velocity);
  }

  const pybind11::object get_calcul_flux_dual() const {
    return pybind11::cast(calcul_flux_dual);
  }

  const pybind11::object get_flux() const {
    return pybind11::cast(flux);
  }

  const pybind11::object get_flux_dual() const {
    return pybind11::cast(flux_dual);
  }

  const pybind11::object get_nbmat() const {
    return pybind11::cast(nbmat);
  }

  const pybind11::object get_nb_vars() const {
    return pybind11::cast(nb_vars);
  }

  const pybind11::object get_m_h_cell_lagrange() const {
    return pybind11::cast(vars->m_h_cell_lagrange);
  }

  const pybind11::object get_m_phi_lagrange() const {
    return pybind11::cast(vars->m_phi_lagrange);
  }

  const pybind11::object get_m_grad_phi() const {
    return pybind11::cast(vars->m_grad_phi);
  }
};

//! Classe de contexte d'exécution pour computeY0
struct RemapADIComputeY0ExecutionContext final : SciHook::SciHookExecutionContext
{
  RemapADIComputeY0ExecutionContext(std::string execution_context_name,
      const ::Types_mahyco::Limiteur projectionLimiterId,
      const Real y0,
      const Real yplus,
      const Real ymoins,
      const Real h0,
      const Real hplus,
      const Real hmoins,
      const Integer type)
  : SciHookExecutionContext(execution_context_name)
  , projectionLimiterId(projectionLimiterId)
  , y0(y0)
  , yplus(yplus)
  , ymoins(ymoins)
  , h0(h0)
  , hplus(hplus)
  , hmoins(hmoins)
  , type(type)
  {}

  const ::Types_mahyco::Limiteur projectionLimiterId;
  const Real y0;
  const Real yplus;
  const Real ymoins;
  const Real h0;
  const Real hplus;
  const Real hmoins;
  const Integer type;

  const pybind11::object get_projectionLimiterId() const {
    return pybind11::cast(projectionLimiterId);
  }

  const pybind11::object get_y0() const {
    return pybind11::cast(y0);
  }

  const pybind11::object get_yplus() const {
    return pybind11::cast(yplus);
  }

  const pybind11::object get_ymoins() const {
    return pybind11::cast(ymoins);
  }

  const pybind11::object get_h0() const {
    return pybind11::cast(h0);
  }

  const pybind11::object get_hplus() const {
    return pybind11::cast(hplus);
  }

  const pybind11::object get_hmoins() const {
    return pybind11::cast(hmoins);
  }

  const pybind11::object get_type() const {
    return pybind11::cast(type);
  }
};

//! Classe de contexte d'exécution pour computexgxd
struct RemapADIComputexgxdExecutionContext final : SciHook::SciHookExecutionContext
{
  RemapADIComputexgxdExecutionContext(std::string execution_context_name,
      const Real y0,
      const Real yplus,
      const Real ymoins,
      const Real h0,
      const Real y0plus,
      const Real y0moins,
      const Integer type)
  : SciHookExecutionContext(execution_context_name)
  , y0(y0)
  , yplus(yplus)
  , ymoins(ymoins)
  , h0(h0)
  , y0plus(y0plus)
  , y0moins(y0moins)
  , type(type)
  {}

  const Real y0;
  const Real yplus;
  const Real ymoins;
  const Real h0;
  const Real y0plus;
  const Real y0moins;
  const Integer type;

  const pybind11::object get_y0() const {
    return pybind11::cast(y0);
  }

  const pybind11::object get_yplus() const {
    return pybind11::cast(yplus);
  }

  const pybind11::object get_ymoins() const {
    return pybind11::cast(ymoins);
  }

  const pybind11::object get_h0() const {
    return pybind11::cast(h0);
  }

  const pybind11::object get_y0plus() const {
    return pybind11::cast(y0plus);
  }

  const pybind11::object get_y0moins() const {
    return pybind11::cast(y0moins);
  }

  const pybind11::object get_type() const {
    return pybind11::cast(type);
  }
};

//! Classe de contexte d'exécution pour computeygyd
struct RemapADIComputeygydExecutionContext final : SciHook::SciHookExecutionContext
{
  RemapADIComputeygydExecutionContext(std::string execution_context_name,
      const Real y0,
      const Real yplus,
      const Real ymoins,
      const Real h0,
      const Real y0plus,
      const Real y0moins,
      const Real grady,
      const Integer type)
  : SciHookExecutionContext(execution_context_name)
  , y0(y0)
  , yplus(yplus)
  , ymoins(ymoins)
  , h0(h0)
  , y0plus(y0plus)
  , y0moins(y0moins)
  , grady(grady)
  , type(type)
  {}

  const Real y0;
  const Real yplus;
  const Real ymoins;
  const Real h0;
  const Real y0plus;
  const Real y0moins;
  const Real grady;
  const Integer type;

  const pybind11::object get_y0() const {
    return pybind11::cast(y0);
  }

  const pybind11::object get_yplus() const {
    return pybind11::cast(yplus);
  }

  const pybind11::object get_ymoins() const {
    return pybind11::cast(ymoins);
  }

  const pybind11::object get_h0() const {
    return pybind11::cast(h0);
  }

  const pybind11::object get_y0plus() const {
    return pybind11::cast(y0plus);
  }

  const pybind11::object get_y0moins() const {
    return pybind11::cast(y0moins);
  }

  const pybind11::object get_grady() const {
    return pybind11::cast(grady);
  }

  const pybind11::object get_type() const {
    return pybind11::cast(type);
  }
};

//! Classe de contexte d'exécution pour intY
struct RemapADIIntYExecutionContext final : SciHook::SciHookExecutionContext
{
  RemapADIIntYExecutionContext(std::string execution_context_name,
      const Real X,
      const Real x0,
      const Real y0,
      const Real x1,
      const Real y1)
  : SciHookExecutionContext(execution_context_name)
  , X(X)
  , x0(x0)
  , y0(y0)
  , x1(x1)
  , y1(y1)
  {}

  const Real X;
  const Real x0;
  const Real y0;
  const Real x1;
  const Real y1;

  const pybind11::object get_X() const {
    return pybind11::cast(X);
  }

  const pybind11::object get_x0() const {
    return pybind11::cast(x0);
  }

  const pybind11::object get_y0() const {
    return pybind11::cast(y0);
  }

  const pybind11::object get_x1() const {
    return pybind11::cast(x1);
  }

  const pybind11::object get_y1() const {
    return pybind11::cast(y1);
  }
};

//! Classe de contexte d'exécution pour computeFluxPPPure
struct RemapADIComputeFluxPPPureExecutionContext final : SciHook::SciHookExecutionContext
{
  RemapADIComputeFluxPPPureExecutionContext(std::string execution_context_name,
      RemapADIComputeFluxPPPureVars *vars,
      const Cell cell,
      const Cell frontcell,
      const Cell backcell,
      const Real face_normal_velocity,
      const Real deltat_n,
      const Integer type,
      const Real flux_threshold,
      const Integer projectionPenteBorneDebarFix,
      const Real dual_normal_velocity,
      const Integer calcul_flux_dual,
      ::Arcane::RealArrayView* Flux,
      ::Arcane::RealArrayView* Flux_dual,
      const Integer nbmat,
      const Integer nb_vars)
  : SciHookExecutionContext(execution_context_name)
  , cell(cell)
  , frontcell(frontcell)
  , backcell(backcell)
  , face_normal_velocity(face_normal_velocity)
  , deltat_n(deltat_n)
  , type(type)
  , flux_threshold(flux_threshold)
  , projectionPenteBorneDebarFix(projectionPenteBorneDebarFix)
  , dual_normal_velocity(dual_normal_velocity)
  , calcul_flux_dual(calcul_flux_dual)
  , Flux(Flux)
  , Flux_dual(Flux_dual)
  , nbmat(nbmat)
  , nb_vars(nb_vars)
  , vars(vars)
  {}

  const Cell cell;
  const Cell frontcell;
  const Cell backcell;
  const Real face_normal_velocity;
  const Real deltat_n;
  const Integer type;
  const Real flux_threshold;
  const Integer projectionPenteBorneDebarFix;
  const Real dual_normal_velocity;
  const Integer calcul_flux_dual;
  ::Arcane::RealArrayView* Flux;
  ::Arcane::RealArrayView* Flux_dual;
  const Integer nbmat;
  const Integer nb_vars;
  const RemapADIComputeFluxPPPureVars *vars;

  const pybind11::object get_cell() const {
    return pybind11::cast(cell);
  }

  const pybind11::object get_frontcell() const {
    return pybind11::cast(frontcell);
  }

  const pybind11::object get_backcell() const {
    return pybind11::cast(backcell);
  }

  const pybind11::object get_face_normal_velocity() const {
    return pybind11::cast(face_normal_velocity);
  }

  const pybind11::object get_deltat_n() const {
    return pybind11::cast(deltat_n);
  }

  const pybind11::object get_type() const {
    return pybind11::cast(type);
  }

  const pybind11::object get_flux_threshold() const {
    return pybind11::cast(flux_threshold);
  }

  const pybind11::object get_projectionPenteBorneDebarFix() const {
    return pybind11::cast(projectionPenteBorneDebarFix);
  }

  const pybind11::object get_dual_normal_velocity() const {
    return pybind11::cast(dual_normal_velocity);
  }

  const pybind11::object get_calcul_flux_dual() const {
    return pybind11::cast(calcul_flux_dual);
  }

  const pybind11::object get_Flux() const {
    return pybind11::cast(Flux);
  }

  const pybind11::object get_Flux_dual() const {
    return pybind11::cast(Flux_dual);
  }

  const pybind11::object get_nbmat() const {
    return pybind11::cast(nbmat);
  }

  const pybind11::object get_nb_vars() const {
    return pybind11::cast(nb_vars);
  }

  const pybind11::object get_m_h_cell_lagrange() const {
    return pybind11::cast(vars->m_h_cell_lagrange);
  }

  const pybind11::object get_m_phi_lagrange() const {
    return pybind11::cast(vars->m_phi_lagrange);
  }

  const pybind11::object get_m_grad_phi() const {
    return pybind11::cast(vars->m_grad_phi);
  }
};

//! Classe de contexte d'exécution pour computeGradPhiFace
struct RemapADIComputeGradPhiFaceExecutionContext final : SciHook::SciHookExecutionContext
{
  RemapADIComputeGradPhiFaceExecutionContext(std::string execution_context_name,
      RemapADIComputeGradPhiFaceVars *vars,
      const Integer idir,
      const Integer nb_vars_to_project,
      const Integer nb_env)
  : SciHookExecutionContext(execution_context_name)
  , idir(idir)
  , nb_vars_to_project(nb_vars_to_project)
  , nb_env(nb_env)
  , vars(vars)
  {}

  const Integer idir;
  const Integer nb_vars_to_project;
  const Integer nb_env;
  const RemapADIComputeGradPhiFaceVars *vars;

  const pybind11::object get_idir() const {
    return pybind11::cast(idir);
  }

  const pybind11::object get_nb_vars_to_project() const {
    return pybind11::cast(nb_vars_to_project);
  }

  const pybind11::object get_nb_env() const {
    return pybind11::cast(nb_env);
  }

  const pybind11::object get_m_face_normal() const {
    return pybind11::cast(vars->m_face_normal);
  }

  const pybind11::object get_m_cell_coord() const {
    return pybind11::cast(vars->m_cell_coord);
  }

  const pybind11::object get_m_phi_lagrange() const {
    return pybind11::cast(vars->m_phi_lagrange);
  }

  const pybind11::object get_m_face_coord() const {
    return pybind11::cast(vars->m_face_coord);
  }

  const pybind11::object get_m_is_dir_face() const {
    return pybind11::cast(vars->m_is_dir_face);
  }

  const pybind11::object get_m_grad_phi_face() const {
    return pybind11::cast(vars->m_grad_phi_face);
  }

  const pybind11::object get_m_deltax_lagrange() const {
    return pybind11::cast(vars->m_deltax_lagrange);
  }

  const pybind11::object get_m_h_cell_lagrange() const {
    return pybind11::cast(vars->m_h_cell_lagrange);
  }
};

//! Classe de contexte d'exécution pour computeGradPhiCell
struct RemapADIComputeGradPhiCellExecutionContext final : SciHook::SciHookExecutionContext
{
  RemapADIComputeGradPhiCellExecutionContext(std::string execution_context_name,
      RemapADIComputeGradPhiCellVars *vars,
      const Integer idir,
      const Integer nb_vars_to_project,
      const Integer nb_env)
  : SciHookExecutionContext(execution_context_name)
  , idir(idir)
  , nb_vars_to_project(nb_vars_to_project)
  , nb_env(nb_env)
  , vars(vars)
  {}

  const Integer idir;
  const Integer nb_vars_to_project;
  const Integer nb_env;
  const RemapADIComputeGradPhiCellVars *vars;

  const pybind11::object get_idir() const {
    return pybind11::cast(idir);
  }

  const pybind11::object get_nb_vars_to_project() const {
    return pybind11::cast(nb_vars_to_project);
  }

  const pybind11::object get_nb_env() const {
    return pybind11::cast(nb_env);
  }

  const pybind11::object get_m_outer_face_normal() const {
    return pybind11::cast(vars->m_outer_face_normal);
  }

  const pybind11::object get_m_face_normal_velocity() const {
    return pybind11::cast(vars->m_face_normal_velocity);
  }

  const pybind11::object get_m_face_length_lagrange() const {
    return pybind11::cast(vars->m_face_length_lagrange);
  }

  const pybind11::object get_m_is_dir_face() const {
    return pybind11::cast(vars->m_is_dir_face);
  }

  const pybind11::object get_m_grad_phi() const {
    return pybind11::cast(vars->m_grad_phi);
  }

  const pybind11::object get_m_dual_phi_flux() const {
    return pybind11::cast(vars->m_dual_phi_flux);
  }

  const pybind11::object get_m_delta_phi_face_av() const {
    return pybind11::cast(vars->m_delta_phi_face_av);
  }

  const pybind11::object get_m_delta_phi_face_ar() const {
    return pybind11::cast(vars->m_delta_phi_face_ar);
  }

  const pybind11::object get_m_est_mixte() const {
    return pybind11::cast(vars->m_est_mixte);
  }

  const pybind11::object get_m_est_pure() const {
    return pybind11::cast(vars->m_est_pure);
  }
};

//! Classe de contexte d'exécution pour computeUpwindFaceQuantitiesForProjection
struct RemapADIComputeUpwindFaceQuantitiesForProjectionExecutionContext final : SciHook::SciHookExecutionContext
{
  RemapADIComputeUpwindFaceQuantitiesForProjectionExecutionContext(std::string execution_context_name,
      RemapADIComputeUpwindFaceQuantitiesForProjectionVars *vars,
      const Integer idir,
      const Integer nb_vars_to_project,
      const Integer nb_env)
  : SciHookExecutionContext(execution_context_name)
  , idir(idir)
  , nb_vars_to_project(nb_vars_to_project)
  , nb_env(nb_env)
  , vars(vars)
  {}

  const Integer idir;
  const Integer nb_vars_to_project;
  const Integer nb_env;
  const RemapADIComputeUpwindFaceQuantitiesForProjectionVars *vars;

  const pybind11::object get_idir() const {
    return pybind11::cast(idir);
  }

  const pybind11::object get_nb_vars_to_project() const {
    return pybind11::cast(nb_vars_to_project);
  }

  const pybind11::object get_nb_env() const {
    return pybind11::cast(nb_env);
  }

  const pybind11::object get_m_face_normal_velocity() const {
    return pybind11::cast(vars->m_face_normal_velocity);
  }

  const pybind11::object get_m_deltax_lagrange() const {
    return pybind11::cast(vars->m_deltax_lagrange);
  }

  const pybind11::object get_m_phi_lagrange() const {
    return pybind11::cast(vars->m_phi_lagrange);
  }

  const pybind11::object get_m_face_coord() const {
    return pybind11::cast(vars->m_face_coord);
  }

  const pybind11::object get_m_cell_coord() const {
    return pybind11::cast(vars->m_cell_coord);
  }

  const pybind11::object get_m_face_normal() const {
    return pybind11::cast(vars->m_face_normal);
  }

  const pybind11::object get_m_grad_phi() const {
    return pybind11::cast(vars->m_grad_phi);
  }

  const pybind11::object get_m_delta_phi_face_av() const {
    return pybind11::cast(vars->m_delta_phi_face_av);
  }

  const pybind11::object get_m_delta_phi_face_ar() const {
    return pybind11::cast(vars->m_delta_phi_face_ar);
  }

  const pybind11::object get_m_h_cell_lagrange() const {
    return pybind11::cast(vars->m_h_cell_lagrange);
  }

  const pybind11::object get_m_est_mixte() const {
    return pybind11::cast(vars->m_est_mixte);
  }

  const pybind11::object get_m_est_pure() const {
    return pybind11::cast(vars->m_est_pure);
  }

  const pybind11::object get_m_phi_face() const {
    return pybind11::cast(vars->m_phi_face);
  }
};

//! Classe de contexte d'exécution pour computeUpwindFaceQuantitiesForProjectionPBorn0O2
struct RemapADIComputeUpwindFaceQuantitiesForProjectionPBorn0O2ExecutionContext final : SciHook::SciHookExecutionContext
{
  RemapADIComputeUpwindFaceQuantitiesForProjectionPBorn0O2ExecutionContext(std::string execution_context_name,
      RemapADIComputeUpwindFaceQuantitiesForProjectionPBorn0O2Vars *vars,
      const Integer idir,
      const Integer nb_vars_to_project)
  : SciHookExecutionContext(execution_context_name)
  , idir(idir)
  , nb_vars_to_project(nb_vars_to_project)
  , vars(vars)
  {}

  const Integer idir;
  const Integer nb_vars_to_project;
  const RemapADIComputeUpwindFaceQuantitiesForProjectionPBorn0O2Vars *vars;

  const pybind11::object get_idir() const {
    return pybind11::cast(idir);
  }

  const pybind11::object get_nb_vars_to_project() const {
    return pybind11::cast(nb_vars_to_project);
  }

  const pybind11::object get_m_deltax_lagrange() const {
    return pybind11::cast(vars->m_deltax_lagrange);
  }

  const pybind11::object get_m_face_normal_velocity() const {
    return pybind11::cast(vars->m_face_normal_velocity);
  }

  const pybind11::object get_m_phi_lagrange() const {
    return pybind11::cast(vars->m_phi_lagrange);
  }

  const pybind11::object get_m_face_coord() const {
    return pybind11::cast(vars->m_face_coord);
  }

  const pybind11::object get_m_face_normal() const {
    return pybind11::cast(vars->m_face_normal);
  }

  const pybind11::object get_m_cell_coord() const {
    return pybind11::cast(vars->m_cell_coord);
  }

  const pybind11::object get_m_grad_phi() const {
    return pybind11::cast(vars->m_grad_phi);
  }

  const pybind11::object get_m_phi_face() const {
    return pybind11::cast(vars->m_phi_face);
  }
};

//! Classe de contexte d'exécution pour computeUremap
struct RemapADIComputeUremapExecutionContext final : SciHook::SciHookExecutionContext
{
  RemapADIComputeUremapExecutionContext(std::string execution_context_name,
      RemapADIComputeUremapVars *vars,
      const Integer idir,
      const Integer nb_vars_to_project,
      const Integer nb_env)
  : SciHookExecutionContext(execution_context_name)
  , idir(idir)
  , nb_vars_to_project(nb_vars_to_project)
  , nb_env(nb_env)
  , vars(vars)
  {}

  const Integer idir;
  const Integer nb_vars_to_project;
  const Integer nb_env;
  const RemapADIComputeUremapVars *vars;

  const pybind11::object get_idir() const {
    return pybind11::cast(idir);
  }

  const pybind11::object get_nb_vars_to_project() const {
    return pybind11::cast(nb_vars_to_project);
  }

  const pybind11::object get_nb_env() const {
    return pybind11::cast(nb_env);
  }

  const pybind11::object get_m_face_normal() const {
    return pybind11::cast(vars->m_face_normal);
  }

  const pybind11::object get_m_face_length_lagrange() const {
    return pybind11::cast(vars->m_face_length_lagrange);
  }

  const pybind11::object get_m_outer_face_normal() const {
    return pybind11::cast(vars->m_outer_face_normal);
  }

  const pybind11::object get_m_face_normal_velocity() const {
    return pybind11::cast(vars->m_face_normal_velocity);
  }

  const pybind11::object get_m_phi_face() const {
    return pybind11::cast(vars->m_phi_face);
  }

  const pybind11::object get_m_dual_phi_flux() const {
    return pybind11::cast(vars->m_dual_phi_flux);
  }

  const pybind11::object get_m_est_mixte() const {
    return pybind11::cast(vars->m_est_mixte);
  }

  const pybind11::object get_m_est_pure() const {
    return pybind11::cast(vars->m_est_pure);
  }

  const pybind11::object get_m_u_lagrange() const {
    return pybind11::cast(vars->m_u_lagrange);
  }

  const pybind11::object get_m_phi_lagrange() const {
    return pybind11::cast(vars->m_phi_lagrange);
  }
};

//! Classe de contexte d'exécution pour computeUremapPBorn0
struct RemapADIComputeUremapPBorn0ExecutionContext final : SciHook::SciHookExecutionContext
{
  RemapADIComputeUremapPBorn0ExecutionContext(std::string execution_context_name,
      RemapADIComputeUremapPBorn0Vars *vars,
      const Integer idir,
      const Integer nb_vars_to_project,
      const Integer nb_env)
  : SciHookExecutionContext(execution_context_name)
  , idir(idir)
  , nb_vars_to_project(nb_vars_to_project)
  , nb_env(nb_env)
  , vars(vars)
  {}

  const Integer idir;
  const Integer nb_vars_to_project;
  const Integer nb_env;
  const RemapADIComputeUremapPBorn0Vars *vars;

  const pybind11::object get_idir() const {
    return pybind11::cast(idir);
  }

  const pybind11::object get_nb_vars_to_project() const {
    return pybind11::cast(nb_vars_to_project);
  }

  const pybind11::object get_nb_env() const {
    return pybind11::cast(nb_env);
  }

  const pybind11::object get_m_face_normal() const {
    return pybind11::cast(vars->m_face_normal);
  }

  const pybind11::object get_m_face_normal_velocity() const {
    return pybind11::cast(vars->m_face_normal_velocity);
  }

  const pybind11::object get_m_face_length_lagrange() const {
    return pybind11::cast(vars->m_face_length_lagrange);
  }

  const pybind11::object get_m_outer_face_normal() const {
    return pybind11::cast(vars->m_outer_face_normal);
  }

  const pybind11::object get_m_phi_face() const {
    return pybind11::cast(vars->m_phi_face);
  }

  const pybind11::object get_m_dual_phi_flux() const {
    return pybind11::cast(vars->m_dual_phi_flux);
  }

  const pybind11::object get_m_est_mixte() const {
    return pybind11::cast(vars->m_est_mixte);
  }

  const pybind11::object get_m_est_pure() const {
    return pybind11::cast(vars->m_est_pure);
  }

  const pybind11::object get_m_u_lagrange() const {
    return pybind11::cast(vars->m_u_lagrange);
  }

  const pybind11::object get_m_phi_lagrange() const {
    return pybind11::cast(vars->m_phi_lagrange);
  }
};

//! Classe de contexte d'exécution pour computeDualUremap
struct RemapADIComputeDualUremapExecutionContext final : SciHook::SciHookExecutionContext
{
  RemapADIComputeDualUremapExecutionContext(std::string execution_context_name,
      RemapADIComputeDualUremapVars *vars,
      const Integer idir,
      const Integer nb_env)
  : SciHookExecutionContext(execution_context_name)
  , idir(idir)
  , nb_env(nb_env)
  , vars(vars)
  {}

  const Integer idir;
  const Integer nb_env;
  const RemapADIComputeDualUremapVars *vars;

  const pybind11::object get_idir() const {
    return pybind11::cast(idir);
  }

  const pybind11::object get_nb_env() const {
    return pybind11::cast(nb_env);
  }

  const pybind11::object get_m_dual_phi_flux() const {
    return pybind11::cast(vars->m_dual_phi_flux);
  }

  const pybind11::object get_m_node_coord() const {
    return pybind11::cast(vars->m_node_coord);
  }

  const pybind11::object get_m_dual_grad_phi() const {
    return pybind11::cast(vars->m_dual_grad_phi);
  }

  const pybind11::object get_m_back_flux_contrib_env() const {
    return pybind11::cast(vars->m_back_flux_contrib_env);
  }

  const pybind11::object get_m_front_flux_contrib_env() const {
    return pybind11::cast(vars->m_front_flux_contrib_env);
  }

  const pybind11::object get_m_back_flux_mass() const {
    return pybind11::cast(vars->m_back_flux_mass);
  }

  const pybind11::object get_m_front_flux_mass() const {
    return pybind11::cast(vars->m_front_flux_mass);
  }

  const pybind11::object get_m_back_flux_mass_env() const {
    return pybind11::cast(vars->m_back_flux_mass_env);
  }

  const pybind11::object get_m_front_flux_mass_env() const {
    return pybind11::cast(vars->m_front_flux_mass_env);
  }

  const pybind11::object get_m_u_dual_lagrange() const {
    return pybind11::cast(vars->m_u_dual_lagrange);
  }

  const pybind11::object get_m_phi_dual_lagrange() const {
    return pybind11::cast(vars->m_phi_dual_lagrange);
  }
};

//! Classe de contexte d'exécution pour computeRemapFlux
struct RemapADIComputeRemapFluxExecutionContext final : SciHook::SciHookExecutionContext
{
  RemapADIComputeRemapFluxExecutionContext(std::string execution_context_name,
      const Integer projectionOrder,
      const Integer projectionAvecPlateauPente,
      const Real face_normal_velocity,
      const Real3 face_normal,
      const Real face_length,
      const Real phi_face,
      const Real3 outer_face_normal,
      const Real3 exy,
      const Real deltat_n)
  : SciHookExecutionContext(execution_context_name)
  , projectionOrder(projectionOrder)
  , projectionAvecPlateauPente(projectionAvecPlateauPente)
  , face_normal_velocity(face_normal_velocity)
  , face_normal(face_normal)
  , face_length(face_length)
  , phi_face(phi_face)
  , outer_face_normal(outer_face_normal)
  , exy(exy)
  , deltat_n(deltat_n)
  {}

  const Integer projectionOrder;
  const Integer projectionAvecPlateauPente;
  const Real face_normal_velocity;
  const Real3 face_normal;
  const Real face_length;
  const Real phi_face;
  const Real3 outer_face_normal;
  const Real3 exy;
  const Real deltat_n;

  const pybind11::object get_projectionOrder() const {
    return pybind11::cast(projectionOrder);
  }

  const pybind11::object get_projectionAvecPlateauPente() const {
    return pybind11::cast(projectionAvecPlateauPente);
  }

  const pybind11::object get_face_normal_velocity() const {
    return pybind11::cast(face_normal_velocity);
  }

  const pybind11::object get_face_normal() const {
    return pybind11::cast(face_normal);
  }

  const pybind11::object get_face_length() const {
    return pybind11::cast(face_length);
  }

  const pybind11::object get_phi_face() const {
    return pybind11::cast(phi_face);
  }

  const pybind11::object get_outer_face_normal() const {
    return pybind11::cast(outer_face_normal);
  }

  const pybind11::object get_exy() const {
    return pybind11::cast(exy);
  }

  const pybind11::object get_deltat_n() const {
    return pybind11::cast(deltat_n);
  }
};

//! Classe de contexte d'exécution pour appliRemap
struct RemapADIAppliRemapExecutionContext final : SciHook::SciHookExecutionContext
{
  RemapADIAppliRemapExecutionContext(std::string execution_context_name,
      RemapADIAppliRemapVars *vars,
      const Integer dimension,
      const Integer withDualProjection,
      const Integer nb_vars_to_project,
      const Integer nb_env)
  : SciHookExecutionContext(execution_context_name)
  , dimension(dimension)
  , withDualProjection(withDualProjection)
  , nb_vars_to_project(nb_vars_to_project)
  , nb_env(nb_env)
  , vars(vars)
  {}

  const Integer dimension;
  const Integer withDualProjection;
  const Integer nb_vars_to_project;
  const Integer nb_env;
  const RemapADIAppliRemapVars *vars;

  const pybind11::object get_dimension() const {
    return pybind11::cast(dimension);
  }

  const pybind11::object get_withDualProjection() const {
    return pybind11::cast(withDualProjection);
  }

  const pybind11::object get_nb_vars_to_project() const {
    return pybind11::cast(nb_vars_to_project);
  }

  const pybind11::object get_nb_env() const {
    return pybind11::cast(nb_env);
  }

  const pybind11::object get_m_sens_projection() const {
    return pybind11::cast(vars->m_sens_projection);
  }
};

//! Classe de contexte d'exécution pour resizeRemapVariables
struct RemapADIResizeRemapVariablesExecutionContext final : SciHook::SciHookExecutionContext
{
  RemapADIResizeRemapVariablesExecutionContext(std::string execution_context_name,
      RemapADIResizeRemapVariablesVars *vars,
      const Integer nb_vars_to_project,
      const Integer nb_env)
  : SciHookExecutionContext(execution_context_name)
  , nb_vars_to_project(nb_vars_to_project)
  , nb_env(nb_env)
  , vars(vars)
  {}

  const Integer nb_vars_to_project;
  const Integer nb_env;
  const RemapADIResizeRemapVariablesVars *vars;

  const pybind11::object get_nb_vars_to_project() const {
    return pybind11::cast(nb_vars_to_project);
  }

  const pybind11::object get_nb_env() const {
    return pybind11::cast(nb_env);
  }

  const pybind11::object get_m_u_lagrange() const {
    return pybind11::cast(vars->m_u_lagrange);
  }

  const pybind11::object get_m_u_dual_lagrange() const {
    return pybind11::cast(vars->m_u_dual_lagrange);
  }

  const pybind11::object get_m_phi_lagrange() const {
    return pybind11::cast(vars->m_phi_lagrange);
  }

  const pybind11::object get_m_phi_dual_lagrange() const {
    return pybind11::cast(vars->m_phi_dual_lagrange);
  }

  const pybind11::object get_m_dual_grad_phi() const {
    return pybind11::cast(vars->m_dual_grad_phi);
  }

  const pybind11::object get_m_grad_phi() const {
    return pybind11::cast(vars->m_grad_phi);
  }

  const pybind11::object get_m_phi_face() const {
    return pybind11::cast(vars->m_phi_face);
  }

  const pybind11::object get_m_grad_phi_face() const {
    return pybind11::cast(vars->m_grad_phi_face);
  }

  const pybind11::object get_m_delta_phi_face_ar() const {
    return pybind11::cast(vars->m_delta_phi_face_ar);
  }

  const pybind11::object get_m_delta_phi_face_av() const {
    return pybind11::cast(vars->m_delta_phi_face_av);
  }

  const pybind11::object get_m_dual_phi_flux() const {
    return pybind11::cast(vars->m_dual_phi_flux);
  }

  const pybind11::object get_m_front_flux_mass_env() const {
    return pybind11::cast(vars->m_front_flux_mass_env);
  }

  const pybind11::object get_m_back_flux_mass_env() const {
    return pybind11::cast(vars->m_back_flux_mass_env);
  }

  const pybind11::object get_m_back_flux_contrib_env() const {
    return pybind11::cast(vars->m_back_flux_contrib_env);
  }

  const pybind11::object get_m_front_flux_contrib_env() const {
    return pybind11::cast(vars->m_front_flux_contrib_env);
  }
};

//! Classe de contexte d'exécution pour synchronizeUremap
struct RemapADISynchronizeUremapExecutionContext final : SciHook::SciHookExecutionContext
{
  RemapADISynchronizeUremapExecutionContext(std::string execution_context_name,
      RemapADISynchronizeUremapVars *vars)
  : SciHookExecutionContext(execution_context_name)
  , vars(vars)
  {}

  const RemapADISynchronizeUremapVars *vars;

  const pybind11::object get_m_phi_lagrange() const {
    return pybind11::cast(vars->m_phi_lagrange);
  }

  const pybind11::object get_m_u_lagrange() const {
    return pybind11::cast(vars->m_u_lagrange);
  }

  const pybind11::object get_m_dual_phi_flux() const {
    return pybind11::cast(vars->m_dual_phi_flux);
  }

  const pybind11::object get_m_est_mixte() const {
    return pybind11::cast(vars->m_est_mixte);
  }

  const pybind11::object get_m_est_pure() const {
    return pybind11::cast(vars->m_est_pure);
  }
};

//! Classe de contexte d'exécution pour remapVariables
struct RemapADIRemapVariablesExecutionContext final : SciHook::SciHookExecutionContext
{
  RemapADIRemapVariablesExecutionContext(std::string execution_context_name,
      RemapADIRemapVariablesVars *vars,
      const Integer dimension,
      const Integer withDualProjection,
      const Integer nb_vars_to_project,
      const Integer nb_env)
  : SciHookExecutionContext(execution_context_name)
  , dimension(dimension)
  , withDualProjection(withDualProjection)
  , nb_vars_to_project(nb_vars_to_project)
  , nb_env(nb_env)
  , vars(vars)
  {}

  const Integer dimension;
  const Integer withDualProjection;
  const Integer nb_vars_to_project;
  const Integer nb_env;
  const RemapADIRemapVariablesVars *vars;

  const pybind11::object get_dimension() const {
    return pybind11::cast(dimension);
  }

  const pybind11::object get_withDualProjection() const {
    return pybind11::cast(withDualProjection);
  }

  const pybind11::object get_nb_vars_to_project() const {
    return pybind11::cast(nb_vars_to_project);
  }

  const pybind11::object get_nb_env() const {
    return pybind11::cast(nb_env);
  }

  const pybind11::object get_m_euler_volume() const {
    return pybind11::cast(vars->m_euler_volume);
  }

  const pybind11::object get_m_u_lagrange() const {
    return pybind11::cast(vars->m_u_lagrange);
  }

  const pybind11::object get_m_u_dual_lagrange() const {
    return pybind11::cast(vars->m_u_dual_lagrange);
  }

  const pybind11::object get_m_est_pure() const {
    return pybind11::cast(vars->m_est_pure);
  }

  const pybind11::object get_m_velocity() const {
    return pybind11::cast(vars->m_velocity);
  }

  const pybind11::object get_m_node_mass() const {
    return pybind11::cast(vars->m_node_mass);
  }

  const pybind11::object get_m_cell_volume() const {
    return pybind11::cast(vars->m_cell_volume);
  }

  const pybind11::object get_m_cell_status() const {
    return pybind11::cast(vars->m_cell_status);
  }

  const pybind11::object get_m_est_mixte() const {
    return pybind11::cast(vars->m_est_mixte);
  }

  const pybind11::object get_m_cell_mass() const {
    return pybind11::cast(vars->m_cell_mass);
  }

  const pybind11::object get_m_fracvol() const {
    return pybind11::cast(vars->m_fracvol);
  }

  const pybind11::object get_m_mass_fraction() const {
    return pybind11::cast(vars->m_mass_fraction);
  }

  const pybind11::object get_m_pseudo_viscosity() const {
    return pybind11::cast(vars->m_pseudo_viscosity);
  }

  const pybind11::object get_m_density() const {
    return pybind11::cast(vars->m_density);
  }

  const pybind11::object get_m_internal_energy() const {
    return pybind11::cast(vars->m_internal_energy);
  }
};

}  // namespace RemapAdi

#endif // defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_ADI_DISABLED)

#endif  // REMAP_ADI___REMAPADISERVICECONTEXTS_H
