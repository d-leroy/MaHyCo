#include "remap/adi/RemapADIService.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

namespace RemapAdi {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

RemapADIService::
RemapADIService(const ServiceBuildInfo& bi)
: RemapADIServiceBase<RemapADIService>(bi)
{
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

RemapADIService::
~RemapADIService()
{
}


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void RemapADIService::
synchronizeDualUremap(RemapADISynchronizeDualUremapVars& vars)
{
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void RemapADIService::
computeGradPhiFace(RemapADIComputeGradPhiFaceVars& vars, const Integer idir, const Integer nb_vars_to_project, const Integer nb_env)
{
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void RemapADIService::
computeGradPhiCell(RemapADIComputeGradPhiCellVars& vars, const Integer idir, const Integer nb_vars_to_project, const Integer nb_env)
{
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void RemapADIService::
computeGradPhiCell_PBorn0_LimC(RemapADIComputeGradPhiCell_PBorn0_LimCVars& vars, const Integer idir, const Integer nb_vars_to_project)
{
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void RemapADIService::
computeDualGradPhi_LimC(RemapADIComputeDualGradPhi_LimCVars& vars, const Integer idir)
{
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void RemapADIService::
computeUpwindFaceQuantitiesForProjection(RemapADIComputeUpwindFaceQuantitiesForProjectionVars& vars, const Integer idir, const Integer nb_vars_to_project, const Integer nb_env)
{
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void RemapADIService::
computeUpwindFaceQuantitiesForProjection_PBorn0_O2(RemapADIComputeUpwindFaceQuantitiesForProjection_PBorn0_O2Vars& vars, const Integer idir, const Integer nb_vars_to_project)
{
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void RemapADIService::
computeUremap(RemapADIComputeUremapVars& vars, const Integer idir, const Integer nb_vars_to_project, const Integer nb_env)
{
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void RemapADIService::
computeUremap_PBorn0(RemapADIComputeUremap_PBorn0Vars& vars, const Integer idir, const Integer nb_vars_to_project, const Integer nb_env)
{
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void RemapADIService::
computeDualUremap(RemapADIComputeDualUremapVars& vars)
{
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void RemapADIService::
appliRemap(RemapADIAppliRemapVars& vars, const Integer dimension, const Integer withDualProjection, const Integer nb_vars_to_project, const Integer nb_env)
{
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void RemapADIService::
resizeRemapVariables(RemapADIResizeRemapVariablesVars& vars, const Integer nb_vars_to_project, const Integer nb_env)
{
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void RemapADIService::
synchronizeUremap(RemapADISynchronizeUremapVars& vars)
{
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void RemapADIService::
remapVariables(RemapADIRemapVariablesVars& vars, const Integer dimension, const Integer withDualProjection, const Integer nb_vars_to_project, const Integer nb_env)
{
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

ARCANE_REGISTER_SERVICE_REMAPADI(RemapADI, RemapADIService);

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace RemapAdi
