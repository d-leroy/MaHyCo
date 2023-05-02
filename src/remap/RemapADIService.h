#ifndef REMAP_REMAPADISERVICE_H
#define REMAP_REMAPADISERVICE_H

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#include "remap/__RemapADIServiceBase.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

namespace Remap {

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

 public:
  void synchronizeDualUremap(RemapADISynchronizeDualUremapVars& vars) override;
  void computeGradPhiFace(RemapADIComputeGradPhiFaceVars& vars, const Integer idir, const Integer nb_vars_to_project, const Integer nb_env) override;
  void computeGradPhiCell(RemapADIComputeGradPhiCellVars& vars, const Integer idir, const Integer nb_vars_to_project, const Integer nb_env) override;
  void computeGradPhiCell_PBorn0_LimC(RemapADIComputeGradPhiCell_PBorn0_LimCVars& vars, const Integer idir, const Integer nb_vars_to_project) override;
  void computeDualGradPhi_LimC(RemapADIComputeDualGradPhi_LimCVars& vars, const Integer idir) override;
  void computeUpwindFaceQuantitiesForProjection(RemapADIComputeUpwindFaceQuantitiesForProjectionVars& vars, const Integer idir, const Integer nb_vars_to_project, const Integer nb_env) override;
  void computeUpwindFaceQuantitiesForProjection_PBorn0_O2(RemapADIComputeUpwindFaceQuantitiesForProjection_PBorn0_O2Vars& vars, const Integer idir, const Integer nb_vars_to_project) override;
  void computeUremap(RemapADIComputeUremapVars& vars, const Integer idir, const Integer nb_vars_to_project, const Integer nb_env) override;
  void computeUremap_PBorn0(RemapADIComputeUremap_PBorn0Vars& vars, const Integer idir, const Integer nb_vars_to_project, const Integer nb_env) override;
  void computeDualUremap(RemapADIComputeDualUremapVars& vars) override;
  void appliRemap(RemapADIAppliRemapVars& vars, const Integer dimension, const Integer withDualProjection, const Integer nb_vars_to_project, const Integer nb_env) override;
  void resizeRemapVariables(RemapADIResizeRemapVariablesVars& vars, const Integer nb_vars_to_project, const Integer nb_env) override;
  void synchronizeUremap(RemapADISynchronizeUremapVars& vars) override;
};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace Remap

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // REMAP_REMAPADISERVICE_H
