#ifndef REMAP_ADI_REMAPADISERVICE_H
#define REMAP_ADI_REMAPADISERVICE_H

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#include "remap/adi/__RemapADIServiceBase.h"

#include "accenv/IAccEnv.h"

#include "arcane/IMesh.h"
#include "arcane/IItemFamily.h"
#include "arcane/materials/IMeshMaterial.h"
#include "arcane/materials/IMeshEnvironment.h"
#include "arcane/materials/IMeshBlock.h"
#include "arcane/materials/MeshMaterialModifier.h"
#include "arcane/materials/MaterialVariableBuildInfo.h"
#include "arcane/materials/MeshBlockBuildInfo.h"
#include "arcane/materials/MeshEnvironmentBuildInfo.h"
#include "arcane/materials/MeshMaterialVariableDependInfo.h"
#include "arcane/materials/CellToAllEnvCellConverter.h"
#include "arcane/materials/MatCellVector.h"
#include "arcane/materials/EnvCellVector.h"
#include "arcane/materials/MatConcurrency.h"
#include "arcane/materials/MeshMaterialIndirectModifier.h"
#include "arcane/materials/MeshMaterialVariableSynchronizerList.h"
#include "arcane/materials/ComponentSimd.h"

#include "cartesian/FactCartDirectionMng.h"

#include "cartesian/interface/CartesianConnectivity.h"
#include "cartesian/interface/CellDirectionMng.h"
#include "cartesian/interface/FaceDirectionMng.h"
#include "cartesian/interface/ICartesianMesh.h"
#include "cartesian/interface/NodeDirectionMng.h"

class IAccEnv;

using namespace Arcane;
using namespace Arcane::Materials;

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

namespace RemapAdi {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

/*!
 * \brief Service RemapADI : implémentation
 * 
 */
class RemapADIService
: public RemapADIServiceBase<RemapADIService>
{
 public:
  explicit RemapADIService(const ServiceBuildInfo& bi);
  ~RemapADIService();

 private:
  Real evaluate_grad(Real hm, Real h0, Real hp, Real ym,
                            Real y0, Real yp);
  Real evaluate_ystar(Real hmm, Real hm, Real hp, Real hpp,
                            [[maybe_unused]] Real ymm, Real ym, Real yp,
                            [[maybe_unused]] Real ypp, Real gradm, Real gradp);
  Real evaluate_fm(Real x, Real dx, Real up, Real du, Real u6);
  Real evaluate_fp(Real x, Real dx, Real um, Real du, Real u6);
  Real2 define_interval(Real a, Real b);
  Real2 intersection(Real2 I1, Real2 I2);
  Real ComputeFluxOrdre3(Real ymmm, Real ymm, Real ym, Real yp,
                            Real ypp, Real yppp, Real hmmm,
                            Real hmm, Real hm, Real hp, Real hpp,
                            Real hppp, Real vdt);

 private:
   // Pour l'utilisation des accélérateurs
   IAccEnv* m_acc_env=nullptr;

 public:

  CartesianInterface::ICartesianMesh* m_cartesian_mesh;

  /**
  * Spécialisation de computeGradPhiCell
  * Est publique car fait appel à l'accélérateur
  **/
  template<typename LimType>
  void computeGradPhiCell_PBorn0_LimC(Integer idir, Integer nb_vars_to_project);

  /**
  * Spécialisation par les limiteurs classiques de computeDualGradPhi
  * Est publique car fait appel à l'accélérateur
  **/
  template<typename LimType>
  void computeDualGradPhi_LimC(Integer idir);

  void synchronizeDualUremap(RemapADISynchronizeDualUremapVars& vars) override;
  void computeAndLimitGradPhi(RemapADIComputeAndLimitGradPhiVars& vars, const Types_mahyco::Limiteur projectionLimiterId, const Face frontFace, const Face backFace, const Cell cell, const Cell frontcell, const Cell backcell, const Integer nb_vars) override;
  void computeDualGradPhi(RemapADIComputeDualGradPhiVars& vars, const Node inode, const Node frontfrontnode, const Node frontnode, const Node backnode, const Node backbacknode, const Integer idir) override;
  void computeAndLimitGradPhiDual(RemapADIComputeAndLimitGradPhiDualVars& vars, const Types_mahyco::Limiteur projectionLimiterId, const Node inode, const Node frontnode, const Node backnode, const Real3 grad_front, const Real3 grad_back, const Real h0, const Real hplus, const Real hmoins) override;
  Real fluxLimiter(RemapADIFluxLimiterVars& vars, const Types_mahyco::Limiteur projectionLimiterId, const Real r) override;
  Real fluxLimiterG(RemapADIFluxLimiterGVars& vars, const Types_mahyco::Limiteur projectionLimiterId, const Real gradplus, const Real gradmoins, const Real y0, const Real yplus, const Real ymoins, const Real h0, const Real hplus, const Real hmoins) override;
  void computeFluxPP(RemapADIComputeFluxPPVars& vars, const Cell cell, const Cell frontcell, const Cell backcell, const Real face_normal_velocity, const Real deltat_n, const Integer type, const Real flux_threshold, const Integer projectionPenteBorneDebarFix, const Real dual_normal_velocity, const Integer calcul_flux_dual, ::Arcane::RealArrayView* flux, ::Arcane::RealArrayView* flux_dual, const Integer nbmat, const Integer nb_vars) override;
  void computeFluxPPPure(RemapADIComputeFluxPPPureVars& vars, const Cell cell, const Cell frontcell, const Cell backcell, const Real face_normal_velocity, const Real deltat_n, const Integer type, const Real flux_threshold, const Integer projectionPenteBorneDebarFix, const Real dual_normal_velocity, const Integer calcul_flux_dual, ::Arcane::RealArrayView* flux, ::Arcane::RealArrayView* flux_dual, const Integer nbmat, const Integer nb_vars) override;
  Real computeY0(RemapADIComputeY0Vars& vars, const Types_mahyco::Limiteur projectionLimiterId, const Real y0, const Real yplus, const Real ymoins, const Real h0, const Real hplus, const Real hmoins, const Integer type) override;
  Real computexgxd(RemapADIComputexgxdVars& vars, const Real y0, const Real yplus, const Real ymoins, const Real h0, const Real y0plus, const Real y0moins, const Integer type) override;
  Real computeygyd(RemapADIComputeygydVars& vars, const Real y0, const Real yplus, const Real ymoins, const Real h0, const Real y0plus, const Real y0moins, const Real grady, const Integer type) override;
  Real INTY(RemapADIINTYVars& vars, const Real X, const Real x0, const Real y0, const Real x1, const Real y1) override;
  void computeGradPhiFace(RemapADIComputeGradPhiFaceVars& vars, const Integer idir, const Integer nb_vars_to_project, const Integer nb_env) override;
  void computeGradPhiCell(RemapADIComputeGradPhiCellVars& vars, const Integer idir, const Integer nb_vars_to_project, const Integer nb_env) override;
  void computeUpwindFaceQuantitiesForProjection(RemapADIComputeUpwindFaceQuantitiesForProjectionVars& vars, const Integer idir, const Integer nb_vars_to_project, const Integer nb_env) override;
  void computeUpwindFaceQuantitiesForProjection_PBorn0_O2(RemapADIComputeUpwindFaceQuantitiesForProjection_PBorn0_O2Vars& vars, const Integer idir, const Integer nb_vars_to_project) override;
  void computeUremap(RemapADIComputeUremapVars& vars, const Integer idir, const Integer nb_vars_to_project, const Integer nb_env) override;
  void computeUremap_PBorn0(RemapADIComputeUremap_PBorn0Vars& vars, const Integer idir, const Integer nb_vars_to_project, const Integer nb_env) override;
  void computeDualUremap(RemapADIComputeDualUremapVars& vars, const Integer idir, const Integer nb_env) override;
  Real computeRemapFlux(RemapADIComputeRemapFluxVars& vars, const Integer projectionOrder, const Integer projectionAvecPlateauPente, const Real face_normal_velocity, const Real3 face_normal, const Real face_length, const Real phi_face, const Real3 outer_face_normal, const Real3 exy, const Real deltat_n) override;
  void appliRemap(RemapADIAppliRemapVars& vars, const Integer dimension, const Integer withDualProjection, const Integer nb_vars_to_project, const Integer nb_env) override;
  void resizeRemapVariables(RemapADIResizeRemapVariablesVars& vars, const Integer nb_vars_to_project, const Integer nb_env) override;
  void synchronizeUremap(RemapADISynchronizeUremapVars& vars) override;
  void remapVariables(RemapADIRemapVariablesVars& vars, const Integer dimension, const Integer withDualProjection, const Integer nb_vars_to_project, const Integer nb_env) override;
};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace RemapAdi

/**
 *******************************************************************************
 * \brief Implémentation des limiteurs
 *******************************************************************************
 */
class MinMod {
 public:
  static ARCCORE_HOST_DEVICE Real fluxLimiter(Real r) {
    return std::max(0.0, std::min(1.0, r));
  }
};

class SuperBee {
 public:
  static ARCCORE_HOST_DEVICE Real fluxLimiter(Real r) {
    return std::max(0.0, std::max(std::min(2.0 * r, 1.0), std::min(r, 2.0)));
  }
};

class VanLeer {
 public:
  static ARCCORE_HOST_DEVICE Real fluxLimiter(Real r) {
    return (r <= 0.0 ? 0.0 : 2.0 * r / (1.0 + r));
  }
};

class DefaultO1 {
 public:
  static ARCCORE_HOST_DEVICE Real fluxLimiter([[maybe_unused]] Real r) {
    return 0.0;  // ordre 1
  }
};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // REMAP_ADI_REMAPADISERVICE_H
