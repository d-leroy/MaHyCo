#ifndef MAHYCO___MAHYCOMODULESCIHOOKMACROS_H
#define MAHYCO___MAHYCOMODULESCIHOOKMACROS_H

#include "scihook/scihookdefs.h"
#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_DISABLED)
#include "SciHook.h"
#include "mahyco/__MahycoModuleContexts.h"
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_DISABLED)
#define SCIHOOK_DECLARE_MAHYCO_MAHYCO_EVENTS \
private:\
 size_t ACCBUILD_BEFORE;\
 size_t ACCBUILD_AFTER;\
 size_t CHECKOPTIONS_BEFORE;\
 size_t CHECKOPTIONS_AFTER;\
 size_t INITCARTESIANMESH_BEFORE;\
 size_t INITCARTESIANMESH_AFTER;\
 size_t ALLOCCQS_BEFORE;\
 size_t ALLOCCQS_AFTER;\
 size_t INITDTINI_BEFORE;\
 size_t INITDTINI_AFTER;\
 size_t INITHYDROVAR_BEFORE;\
 size_t INITHYDROVAR_AFTER;\
 size_t HYDROSTARTINITENVANDMAT_BEFORE;\
 size_t HYDROSTARTINITENVANDMAT_AFTER;\
 size_t INITENVFORACC_BEFORE;\
 size_t INITENVFORACC_AFTER;\
 size_t COMPUTEGEOMETRICVALUESINI_BEFORE;\
 size_t COMPUTEGEOMETRICVALUESINI_AFTER;\
 size_t PREPAREFACEGROUPFORBC_BEFORE;\
 size_t PREPAREFACEGROUPFORBC_AFTER;\
 size_t INITBOUNDARYCONDITIONSFORACC_BEFORE;\
 size_t INITBOUNDARYCONDITIONSFORACC_AFTER;\
 size_t SETSYNCVARVERS_BEFORE;\
 size_t SETSYNCVARVERS_AFTER;\
 size_t COMPUTECELLMASS_BEFORE;\
 size_t COMPUTECELLMASS_AFTER;\
 size_t COMPUTENODEMASS_BEFORE;\
 size_t COMPUTENODEMASS_AFTER;\
 size_t CONTINUEFORMULTIMAT_BEFORE;\
 size_t CONTINUEFORMULTIMAT_AFTER;\
 size_t CONTINUEFORITERATIONDT_BEFORE;\
 size_t CONTINUEFORITERATIONDT_AFTER;\
 size_t SAVEVALUESATN_BEFORE;\
 size_t SAVEVALUESATN_AFTER;\
 size_t UPDATEVELOCITY_BEFORE;\
 size_t UPDATEVELOCITY_AFTER;\
 size_t APPLYBOUNDARYCONDITION_BEFORE;\
 size_t APPLYBOUNDARYCONDITION_AFTER;\
 size_t UPDATEPOSITION_BEFORE;\
 size_t UPDATEPOSITION_AFTER;\
 size_t COMPUTEGEOMETRICVALUES_BEFORE;\
 size_t COMPUTEGEOMETRICVALUES_AFTER;\
 size_t UPDATEDENSITY_BEFORE;\
 size_t UPDATEDENSITY_AFTER;\
 size_t COMPUTEARTIFICIALVISCOSITY_BEFORE;\
 size_t COMPUTEARTIFICIALVISCOSITY_AFTER;\
 size_t UPDATEENERGYANDPRESSURE_BEFORE;\
 size_t UPDATEENERGYANDPRESSURE_AFTER;\
 size_t REMAP_BEFORE;\
 size_t REMAP_AFTER;\
 size_t COMPUTEDELTAT_BEFORE;\
 size_t COMPUTEDELTAT_AFTER;\
 size_t INITGEOMETRICVALUES_BEFORE;\
 size_t INITGEOMETRICVALUES_AFTER;\
 size_t COMPUTEGEOMETRICVALUESAUX_BEFORE;\
 size_t COMPUTEGEOMETRICVALUESAUX_AFTER;\
 size_t UPDATEVELOCITYWITHOUTLAGRANGE_BEFORE;\
 size_t UPDATEVELOCITYWITHOUTLAGRANGE_AFTER;\
 size_t UPDATEVELOCITYBACKWARD_BEFORE;\
 size_t UPDATEVELOCITYBACKWARD_AFTER;\
 size_t UPDATEVELOCITYFORWARD_BEFORE;\
 size_t UPDATEVELOCITYFORWARD_AFTER;\
 size_t UPDATEFORCEANDVELOCITY_BEFORE;\
 size_t UPDATEFORCEANDVELOCITY_AFTER;\
 size_t UPDATEENERGYANDPRESSUREBYNEWTON_BEFORE;\
 size_t UPDATEENERGYANDPRESSUREBYNEWTON_AFTER;\
 size_t UPDATEENERGYANDPRESSUREFORGP_BEFORE;\
 size_t UPDATEENERGYANDPRESSUREFORGP_AFTER;\
 size_t COMPUTEAVERAGEPRESSURE_BEFORE;\
 size_t COMPUTEAVERAGEPRESSURE_AFTER;\
 size_t COMPUTEVARIABLESFORREMAP_BEFORE;\
 size_t COMPUTEVARIABLESFORREMAP_AFTER;\
 size_t COMPUTEVARIABLESFORREMAPPBORN0_BEFORE;\
 size_t COMPUTEVARIABLESFORREMAPPBORN0_AFTER;\
 size_t COMPUTEFACEQUANTITESFORREMAP_BEFORE;\
 size_t COMPUTEFACEQUANTITESFORREMAP_AFTER;
#define SCIHOOK_INITIALIZE_MAHYCO_MAHYCO_EVENTS \
ACCBUILD_BEFORE = SciHook::register_base_event("Mahyco.AccBuild.Before");\
ACCBUILD_AFTER = SciHook::register_base_event("Mahyco.AccBuild.After");\
CHECKOPTIONS_BEFORE = SciHook::register_base_event("Mahyco.CheckOptions.Before");\
CHECKOPTIONS_AFTER = SciHook::register_base_event("Mahyco.CheckOptions.After");\
INITCARTESIANMESH_BEFORE = SciHook::register_base_event("Mahyco.InitCartesianMesh.Before");\
INITCARTESIANMESH_AFTER = SciHook::register_base_event("Mahyco.InitCartesianMesh.After");\
ALLOCCQS_BEFORE = SciHook::register_base_event("Mahyco.AllocCqs.Before");\
ALLOCCQS_AFTER = SciHook::register_base_event("Mahyco.AllocCqs.After");\
INITDTINI_BEFORE = SciHook::register_base_event("Mahyco.InitDtIni.Before");\
INITDTINI_AFTER = SciHook::register_base_event("Mahyco.InitDtIni.After");\
INITHYDROVAR_BEFORE = SciHook::register_base_event("Mahyco.InitHydroVar.Before");\
INITHYDROVAR_AFTER = SciHook::register_base_event("Mahyco.InitHydroVar.After");\
HYDROSTARTINITENVANDMAT_BEFORE = SciHook::register_base_event("Mahyco.HydroStartInitEnvAndMat.Before");\
HYDROSTARTINITENVANDMAT_AFTER = SciHook::register_base_event("Mahyco.HydroStartInitEnvAndMat.After");\
INITENVFORACC_BEFORE = SciHook::register_base_event("Mahyco.InitEnvForAcc.Before");\
INITENVFORACC_AFTER = SciHook::register_base_event("Mahyco.InitEnvForAcc.After");\
COMPUTEGEOMETRICVALUESINI_BEFORE = SciHook::register_base_event("Mahyco.ComputeGeometricValuesIni.Before");\
COMPUTEGEOMETRICVALUESINI_AFTER = SciHook::register_base_event("Mahyco.ComputeGeometricValuesIni.After");\
PREPAREFACEGROUPFORBC_BEFORE = SciHook::register_base_event("Mahyco.PrepareFaceGroupForBc.Before");\
PREPAREFACEGROUPFORBC_AFTER = SciHook::register_base_event("Mahyco.PrepareFaceGroupForBc.After");\
INITBOUNDARYCONDITIONSFORACC_BEFORE = SciHook::register_base_event("Mahyco.InitBoundaryConditionsForAcc.Before");\
INITBOUNDARYCONDITIONSFORACC_AFTER = SciHook::register_base_event("Mahyco.InitBoundaryConditionsForAcc.After");\
SETSYNCVARVERS_BEFORE = SciHook::register_base_event("Mahyco.SetSyncVarVers.Before");\
SETSYNCVARVERS_AFTER = SciHook::register_base_event("Mahyco.SetSyncVarVers.After");\
COMPUTECELLMASS_BEFORE = SciHook::register_base_event("Mahyco.ComputeCellMass.Before");\
COMPUTECELLMASS_AFTER = SciHook::register_base_event("Mahyco.ComputeCellMass.After");\
COMPUTENODEMASS_BEFORE = SciHook::register_base_event("Mahyco.ComputeNodeMass.Before");\
COMPUTENODEMASS_AFTER = SciHook::register_base_event("Mahyco.ComputeNodeMass.After");\
CONTINUEFORMULTIMAT_BEFORE = SciHook::register_base_event("Mahyco.ContinueForMultiMat.Before");\
CONTINUEFORMULTIMAT_AFTER = SciHook::register_base_event("Mahyco.ContinueForMultiMat.After");\
CONTINUEFORITERATIONDT_BEFORE = SciHook::register_base_event("Mahyco.ContinueForIterationDt.Before");\
CONTINUEFORITERATIONDT_AFTER = SciHook::register_base_event("Mahyco.ContinueForIterationDt.After");\
SAVEVALUESATN_BEFORE = SciHook::register_base_event("Mahyco.SaveValuesAtN.Before");\
SAVEVALUESATN_AFTER = SciHook::register_base_event("Mahyco.SaveValuesAtN.After");\
UPDATEVELOCITY_BEFORE = SciHook::register_base_event("Mahyco.UpdateVelocity.Before");\
UPDATEVELOCITY_AFTER = SciHook::register_base_event("Mahyco.UpdateVelocity.After");\
APPLYBOUNDARYCONDITION_BEFORE = SciHook::register_base_event("Mahyco.ApplyBoundaryCondition.Before");\
APPLYBOUNDARYCONDITION_AFTER = SciHook::register_base_event("Mahyco.ApplyBoundaryCondition.After");\
UPDATEPOSITION_BEFORE = SciHook::register_base_event("Mahyco.UpdatePosition.Before");\
UPDATEPOSITION_AFTER = SciHook::register_base_event("Mahyco.UpdatePosition.After");\
COMPUTEGEOMETRICVALUES_BEFORE = SciHook::register_base_event("Mahyco.ComputeGeometricValues.Before");\
COMPUTEGEOMETRICVALUES_AFTER = SciHook::register_base_event("Mahyco.ComputeGeometricValues.After");\
UPDATEDENSITY_BEFORE = SciHook::register_base_event("Mahyco.UpdateDensity.Before");\
UPDATEDENSITY_AFTER = SciHook::register_base_event("Mahyco.UpdateDensity.After");\
COMPUTEARTIFICIALVISCOSITY_BEFORE = SciHook::register_base_event("Mahyco.ComputeArtificialViscosity.Before");\
COMPUTEARTIFICIALVISCOSITY_AFTER = SciHook::register_base_event("Mahyco.ComputeArtificialViscosity.After");\
UPDATEENERGYANDPRESSURE_BEFORE = SciHook::register_base_event("Mahyco.UpdateEnergyAndPressure.Before");\
UPDATEENERGYANDPRESSURE_AFTER = SciHook::register_base_event("Mahyco.UpdateEnergyAndPressure.After");\
REMAP_BEFORE = SciHook::register_base_event("Mahyco.Remap.Before");\
REMAP_AFTER = SciHook::register_base_event("Mahyco.Remap.After");\
COMPUTEDELTAT_BEFORE = SciHook::register_base_event("Mahyco.ComputeDeltaT.Before");\
COMPUTEDELTAT_AFTER = SciHook::register_base_event("Mahyco.ComputeDeltaT.After");\
INITGEOMETRICVALUES_BEFORE = SciHook::register_base_event("Mahyco.InitGeometricValues.Before");\
INITGEOMETRICVALUES_AFTER = SciHook::register_base_event("Mahyco.InitGeometricValues.After");\
COMPUTEGEOMETRICVALUESAUX_BEFORE = SciHook::register_base_event("Mahyco.ComputeGeometricValuesAux.Before");\
COMPUTEGEOMETRICVALUESAUX_AFTER = SciHook::register_base_event("Mahyco.ComputeGeometricValuesAux.After");\
UPDATEVELOCITYWITHOUTLAGRANGE_BEFORE = SciHook::register_base_event("Mahyco.UpdateVelocityWithoutLagrange.Before");\
UPDATEVELOCITYWITHOUTLAGRANGE_AFTER = SciHook::register_base_event("Mahyco.UpdateVelocityWithoutLagrange.After");\
UPDATEVELOCITYBACKWARD_BEFORE = SciHook::register_base_event("Mahyco.UpdateVelocityBackward.Before");\
UPDATEVELOCITYBACKWARD_AFTER = SciHook::register_base_event("Mahyco.UpdateVelocityBackward.After");\
UPDATEVELOCITYFORWARD_BEFORE = SciHook::register_base_event("Mahyco.UpdateVelocityForward.Before");\
UPDATEVELOCITYFORWARD_AFTER = SciHook::register_base_event("Mahyco.UpdateVelocityForward.After");\
UPDATEFORCEANDVELOCITY_BEFORE = SciHook::register_base_event("Mahyco.UpdateForceAndVelocity.Before");\
UPDATEFORCEANDVELOCITY_AFTER = SciHook::register_base_event("Mahyco.UpdateForceAndVelocity.After");\
UPDATEENERGYANDPRESSUREBYNEWTON_BEFORE = SciHook::register_base_event("Mahyco.UpdateEnergyAndPressurebyNewton.Before");\
UPDATEENERGYANDPRESSUREBYNEWTON_AFTER = SciHook::register_base_event("Mahyco.UpdateEnergyAndPressurebyNewton.After");\
UPDATEENERGYANDPRESSUREFORGP_BEFORE = SciHook::register_base_event("Mahyco.UpdateEnergyAndPressureforGP.Before");\
UPDATEENERGYANDPRESSUREFORGP_AFTER = SciHook::register_base_event("Mahyco.UpdateEnergyAndPressureforGP.After");\
COMPUTEAVERAGEPRESSURE_BEFORE = SciHook::register_base_event("Mahyco.ComputeAveragePressure.Before");\
COMPUTEAVERAGEPRESSURE_AFTER = SciHook::register_base_event("Mahyco.ComputeAveragePressure.After");\
COMPUTEVARIABLESFORREMAP_BEFORE = SciHook::register_base_event("Mahyco.ComputeVariablesForRemap.Before");\
COMPUTEVARIABLESFORREMAP_AFTER = SciHook::register_base_event("Mahyco.ComputeVariablesForRemap.After");\
COMPUTEVARIABLESFORREMAPPBORN0_BEFORE = SciHook::register_base_event("Mahyco.ComputeVariablesForRemapPBorn0.Before");\
COMPUTEVARIABLESFORREMAPPBORN0_AFTER = SciHook::register_base_event("Mahyco.ComputeVariablesForRemapPBorn0.After");\
COMPUTEFACEQUANTITESFORREMAP_BEFORE = SciHook::register_base_event("Mahyco.ComputeFaceQuantitesForRemap.Before");\
COMPUTEFACEQUANTITESFORREMAP_AFTER = SciHook::register_base_event("Mahyco.ComputeFaceQuantitesForRemap.After");
#else
#define SCIHOOK_DECLARE_MAHYCO_MAHYCO_EVENTS
#define SCIHOOK_INITIALIZE_MAHYCO_MAHYCO_EVENTS
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_ACCBUILD_DISABLED)
#define SCIHOOK_TRIGGER_ACCBUILD_BEFORE \
std::shared_ptr<SciHook::SciHookExecutionContext> ctx(new SciHook::SciHookExecutionContext("AccBuildExecutionContext"));\
SciHook::trigger(ACCBUILD_BEFORE, ctx);
#define SCIHOOK_TRIGGER_ACCBUILD_AFTER SciHook::trigger(ACCBUILD_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_ACCBUILD_BEFORE
#define SCIHOOK_TRIGGER_ACCBUILD_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_CHECKOPTIONS_DISABLED)
#define SCIHOOK_TRIGGER_CHECKOPTIONS_BEFORE \
std::shared_ptr<SciHook::SciHookExecutionContext> ctx(new SciHook::SciHookExecutionContext("CheckOptionsExecutionContext"));\
SciHook::trigger(CHECKOPTIONS_BEFORE, ctx);
#define SCIHOOK_TRIGGER_CHECKOPTIONS_AFTER SciHook::trigger(CHECKOPTIONS_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_CHECKOPTIONS_BEFORE
#define SCIHOOK_TRIGGER_CHECKOPTIONS_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_INITCARTESIANMESH_DISABLED)
#define SCIHOOK_TRIGGER_INITCARTESIANMESH_BEFORE \
std::shared_ptr<SciHook::SciHookExecutionContext> ctx(new SciHook::SciHookExecutionContext("InitCartesianMeshExecutionContext"));\
SciHook::trigger(INITCARTESIANMESH_BEFORE, ctx);
#define SCIHOOK_TRIGGER_INITCARTESIANMESH_AFTER SciHook::trigger(INITCARTESIANMESH_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_INITCARTESIANMESH_BEFORE
#define SCIHOOK_TRIGGER_INITCARTESIANMESH_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_ALLOCCQS_DISABLED)
#define SCIHOOK_TRIGGER_ALLOCCQS_BEFORE \
std::shared_ptr<MahycoAllocCqsExecutionContext> ctx(new MahycoAllocCqsExecutionContext("AllocCqsExecutionContext", &vars));\
SciHook::trigger(ALLOCCQS_BEFORE, ctx);
#define SCIHOOK_TRIGGER_ALLOCCQS_AFTER SciHook::trigger(ALLOCCQS_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_ALLOCCQS_BEFORE
#define SCIHOOK_TRIGGER_ALLOCCQS_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_INITDTINI_DISABLED)
#define SCIHOOK_TRIGGER_INITDTINI_BEFORE \
std::shared_ptr<SciHook::SciHookExecutionContext> ctx(new SciHook::SciHookExecutionContext("InitDtIniExecutionContext"));\
SciHook::trigger(INITDTINI_BEFORE, ctx);
#define SCIHOOK_TRIGGER_INITDTINI_AFTER SciHook::trigger(INITDTINI_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_INITDTINI_BEFORE
#define SCIHOOK_TRIGGER_INITDTINI_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_INITHYDROVAR_DISABLED)
#define SCIHOOK_TRIGGER_INITHYDROVAR_BEFORE \
std::shared_ptr<MahycoInitHydroVarExecutionContext> ctx(new MahycoInitHydroVarExecutionContext("InitHydroVarExecutionContext", &vars));\
SciHook::trigger(INITHYDROVAR_BEFORE, ctx);
#define SCIHOOK_TRIGGER_INITHYDROVAR_AFTER SciHook::trigger(INITHYDROVAR_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_INITHYDROVAR_BEFORE
#define SCIHOOK_TRIGGER_INITHYDROVAR_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_HYDROSTARTINITENVANDMAT_DISABLED)
#define SCIHOOK_TRIGGER_HYDROSTARTINITENVANDMAT_BEFORE \
std::shared_ptr<MahycoHydroStartInitEnvAndMatExecutionContext> ctx(new MahycoHydroStartInitEnvAndMatExecutionContext("HydroStartInitEnvAndMatExecutionContext", &vars));\
SciHook::trigger(HYDROSTARTINITENVANDMAT_BEFORE, ctx);
#define SCIHOOK_TRIGGER_HYDROSTARTINITENVANDMAT_AFTER SciHook::trigger(HYDROSTARTINITENVANDMAT_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_HYDROSTARTINITENVANDMAT_BEFORE
#define SCIHOOK_TRIGGER_HYDROSTARTINITENVANDMAT_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_INITENVFORACC_DISABLED)
#define SCIHOOK_TRIGGER_INITENVFORACC_BEFORE \
std::shared_ptr<SciHook::SciHookExecutionContext> ctx(new SciHook::SciHookExecutionContext("InitEnvForAccExecutionContext"));\
SciHook::trigger(INITENVFORACC_BEFORE, ctx);
#define SCIHOOK_TRIGGER_INITENVFORACC_AFTER SciHook::trigger(INITENVFORACC_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_INITENVFORACC_BEFORE
#define SCIHOOK_TRIGGER_INITENVFORACC_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_COMPUTEGEOMETRICVALUESINI_DISABLED)
#define SCIHOOK_TRIGGER_COMPUTEGEOMETRICVALUESINI_BEFORE \
std::shared_ptr<SciHook::SciHookExecutionContext> ctx(new SciHook::SciHookExecutionContext("ComputeGeometricValuesIniExecutionContext"));\
SciHook::trigger(COMPUTEGEOMETRICVALUESINI_BEFORE, ctx);
#define SCIHOOK_TRIGGER_COMPUTEGEOMETRICVALUESINI_AFTER SciHook::trigger(COMPUTEGEOMETRICVALUESINI_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_COMPUTEGEOMETRICVALUESINI_BEFORE
#define SCIHOOK_TRIGGER_COMPUTEGEOMETRICVALUESINI_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_PREPAREFACEGROUPFORBC_DISABLED)
#define SCIHOOK_TRIGGER_PREPAREFACEGROUPFORBC_BEFORE \
std::shared_ptr<MahycoPrepareFaceGroupForBcExecutionContext> ctx(new MahycoPrepareFaceGroupForBcExecutionContext("PrepareFaceGroupForBcExecutionContext", &vars));\
SciHook::trigger(PREPAREFACEGROUPFORBC_BEFORE, ctx);
#define SCIHOOK_TRIGGER_PREPAREFACEGROUPFORBC_AFTER SciHook::trigger(PREPAREFACEGROUPFORBC_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_PREPAREFACEGROUPFORBC_BEFORE
#define SCIHOOK_TRIGGER_PREPAREFACEGROUPFORBC_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_INITBOUNDARYCONDITIONSFORACC_DISABLED)
#define SCIHOOK_TRIGGER_INITBOUNDARYCONDITIONSFORACC_BEFORE \
std::shared_ptr<SciHook::SciHookExecutionContext> ctx(new SciHook::SciHookExecutionContext("InitBoundaryConditionsForAccExecutionContext"));\
SciHook::trigger(INITBOUNDARYCONDITIONSFORACC_BEFORE, ctx);
#define SCIHOOK_TRIGGER_INITBOUNDARYCONDITIONSFORACC_AFTER SciHook::trigger(INITBOUNDARYCONDITIONSFORACC_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_INITBOUNDARYCONDITIONSFORACC_BEFORE
#define SCIHOOK_TRIGGER_INITBOUNDARYCONDITIONSFORACC_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_SETSYNCVARVERS_DISABLED)
#define SCIHOOK_TRIGGER_SETSYNCVARVERS_BEFORE \
std::shared_ptr<SciHook::SciHookExecutionContext> ctx(new SciHook::SciHookExecutionContext("SetSyncVarVersExecutionContext"));\
SciHook::trigger(SETSYNCVARVERS_BEFORE, ctx);
#define SCIHOOK_TRIGGER_SETSYNCVARVERS_AFTER SciHook::trigger(SETSYNCVARVERS_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_SETSYNCVARVERS_BEFORE
#define SCIHOOK_TRIGGER_SETSYNCVARVERS_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_COMPUTECELLMASS_DISABLED)
#define SCIHOOK_TRIGGER_COMPUTECELLMASS_BEFORE \
std::shared_ptr<MahycoComputeCellMassExecutionContext> ctx(new MahycoComputeCellMassExecutionContext("ComputeCellMassExecutionContext", &vars));\
SciHook::trigger(COMPUTECELLMASS_BEFORE, ctx);
#define SCIHOOK_TRIGGER_COMPUTECELLMASS_AFTER SciHook::trigger(COMPUTECELLMASS_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_COMPUTECELLMASS_BEFORE
#define SCIHOOK_TRIGGER_COMPUTECELLMASS_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_COMPUTENODEMASS_DISABLED)
#define SCIHOOK_TRIGGER_COMPUTENODEMASS_BEFORE \
std::shared_ptr<MahycoComputeNodeMassExecutionContext> ctx(new MahycoComputeNodeMassExecutionContext("ComputeNodeMassExecutionContext", &vars));\
SciHook::trigger(COMPUTENODEMASS_BEFORE, ctx);
#define SCIHOOK_TRIGGER_COMPUTENODEMASS_AFTER SciHook::trigger(COMPUTENODEMASS_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_COMPUTENODEMASS_BEFORE
#define SCIHOOK_TRIGGER_COMPUTENODEMASS_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_CONTINUEFORMULTIMAT_DISABLED)
#define SCIHOOK_TRIGGER_CONTINUEFORMULTIMAT_BEFORE \
std::shared_ptr<SciHook::SciHookExecutionContext> ctx(new SciHook::SciHookExecutionContext("ContinueForMultiMatExecutionContext"));\
SciHook::trigger(CONTINUEFORMULTIMAT_BEFORE, ctx);
#define SCIHOOK_TRIGGER_CONTINUEFORMULTIMAT_AFTER SciHook::trigger(CONTINUEFORMULTIMAT_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_CONTINUEFORMULTIMAT_BEFORE
#define SCIHOOK_TRIGGER_CONTINUEFORMULTIMAT_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_CONTINUEFORITERATIONDT_DISABLED)
#define SCIHOOK_TRIGGER_CONTINUEFORITERATIONDT_BEFORE \
std::shared_ptr<MahycoContinueForIterationDtExecutionContext> ctx(new MahycoContinueForIterationDtExecutionContext("ContinueForIterationDtExecutionContext", &vars));\
SciHook::trigger(CONTINUEFORITERATIONDT_BEFORE, ctx);
#define SCIHOOK_TRIGGER_CONTINUEFORITERATIONDT_AFTER SciHook::trigger(CONTINUEFORITERATIONDT_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_CONTINUEFORITERATIONDT_BEFORE
#define SCIHOOK_TRIGGER_CONTINUEFORITERATIONDT_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_SAVEVALUESATN_DISABLED)
#define SCIHOOK_TRIGGER_SAVEVALUESATN_BEFORE \
std::shared_ptr<MahycoSaveValuesAtNExecutionContext> ctx(new MahycoSaveValuesAtNExecutionContext("SaveValuesAtNExecutionContext", &vars));\
SciHook::trigger(SAVEVALUESATN_BEFORE, ctx);
#define SCIHOOK_TRIGGER_SAVEVALUESATN_AFTER SciHook::trigger(SAVEVALUESATN_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_SAVEVALUESATN_BEFORE
#define SCIHOOK_TRIGGER_SAVEVALUESATN_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_UPDATEVELOCITY_DISABLED)
#define SCIHOOK_TRIGGER_UPDATEVELOCITY_BEFORE \
std::shared_ptr<MahycoUpdateVelocityExecutionContext> ctx(new MahycoUpdateVelocityExecutionContext("UpdateVelocityExecutionContext", &vars));\
SciHook::trigger(UPDATEVELOCITY_BEFORE, ctx);
#define SCIHOOK_TRIGGER_UPDATEVELOCITY_AFTER SciHook::trigger(UPDATEVELOCITY_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_UPDATEVELOCITY_BEFORE
#define SCIHOOK_TRIGGER_UPDATEVELOCITY_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_APPLYBOUNDARYCONDITION_DISABLED)
#define SCIHOOK_TRIGGER_APPLYBOUNDARYCONDITION_BEFORE \
std::shared_ptr<MahycoApplyBoundaryConditionExecutionContext> ctx(new MahycoApplyBoundaryConditionExecutionContext("ApplyBoundaryConditionExecutionContext", &vars));\
SciHook::trigger(APPLYBOUNDARYCONDITION_BEFORE, ctx);
#define SCIHOOK_TRIGGER_APPLYBOUNDARYCONDITION_AFTER SciHook::trigger(APPLYBOUNDARYCONDITION_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_APPLYBOUNDARYCONDITION_BEFORE
#define SCIHOOK_TRIGGER_APPLYBOUNDARYCONDITION_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_UPDATEPOSITION_DISABLED)
#define SCIHOOK_TRIGGER_UPDATEPOSITION_BEFORE \
std::shared_ptr<MahycoUpdatePositionExecutionContext> ctx(new MahycoUpdatePositionExecutionContext("UpdatePositionExecutionContext", &vars));\
SciHook::trigger(UPDATEPOSITION_BEFORE, ctx);
#define SCIHOOK_TRIGGER_UPDATEPOSITION_AFTER SciHook::trigger(UPDATEPOSITION_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_UPDATEPOSITION_BEFORE
#define SCIHOOK_TRIGGER_UPDATEPOSITION_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_COMPUTEGEOMETRICVALUES_DISABLED)
#define SCIHOOK_TRIGGER_COMPUTEGEOMETRICVALUES_BEFORE \
std::shared_ptr<SciHook::SciHookExecutionContext> ctx(new SciHook::SciHookExecutionContext("ComputeGeometricValuesExecutionContext"));\
SciHook::trigger(COMPUTEGEOMETRICVALUES_BEFORE, ctx);
#define SCIHOOK_TRIGGER_COMPUTEGEOMETRICVALUES_AFTER SciHook::trigger(COMPUTEGEOMETRICVALUES_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_COMPUTEGEOMETRICVALUES_BEFORE
#define SCIHOOK_TRIGGER_COMPUTEGEOMETRICVALUES_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_UPDATEDENSITY_DISABLED)
#define SCIHOOK_TRIGGER_UPDATEDENSITY_BEFORE \
std::shared_ptr<MahycoUpdateDensityExecutionContext> ctx(new MahycoUpdateDensityExecutionContext("UpdateDensityExecutionContext", &vars));\
SciHook::trigger(UPDATEDENSITY_BEFORE, ctx);
#define SCIHOOK_TRIGGER_UPDATEDENSITY_AFTER SciHook::trigger(UPDATEDENSITY_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_UPDATEDENSITY_BEFORE
#define SCIHOOK_TRIGGER_UPDATEDENSITY_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_COMPUTEARTIFICIALVISCOSITY_DISABLED)
#define SCIHOOK_TRIGGER_COMPUTEARTIFICIALVISCOSITY_BEFORE \
std::shared_ptr<MahycoComputeArtificialViscosityExecutionContext> ctx(new MahycoComputeArtificialViscosityExecutionContext("ComputeArtificialViscosityExecutionContext", &vars));\
SciHook::trigger(COMPUTEARTIFICIALVISCOSITY_BEFORE, ctx);
#define SCIHOOK_TRIGGER_COMPUTEARTIFICIALVISCOSITY_AFTER SciHook::trigger(COMPUTEARTIFICIALVISCOSITY_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_COMPUTEARTIFICIALVISCOSITY_BEFORE
#define SCIHOOK_TRIGGER_COMPUTEARTIFICIALVISCOSITY_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_UPDATEENERGYANDPRESSURE_DISABLED)
#define SCIHOOK_TRIGGER_UPDATEENERGYANDPRESSURE_BEFORE \
std::shared_ptr<SciHook::SciHookExecutionContext> ctx(new SciHook::SciHookExecutionContext("UpdateEnergyAndPressureExecutionContext"));\
SciHook::trigger(UPDATEENERGYANDPRESSURE_BEFORE, ctx);
#define SCIHOOK_TRIGGER_UPDATEENERGYANDPRESSURE_AFTER SciHook::trigger(UPDATEENERGYANDPRESSURE_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_UPDATEENERGYANDPRESSURE_BEFORE
#define SCIHOOK_TRIGGER_UPDATEENERGYANDPRESSURE_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_REMAP_DISABLED)
#define SCIHOOK_TRIGGER_REMAP_BEFORE \
std::shared_ptr<MahycoRemapExecutionContext> ctx(new MahycoRemapExecutionContext("RemapExecutionContext", &vars));\
SciHook::trigger(REMAP_BEFORE, ctx);
#define SCIHOOK_TRIGGER_REMAP_AFTER SciHook::trigger(REMAP_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_REMAP_BEFORE
#define SCIHOOK_TRIGGER_REMAP_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_COMPUTEDELTAT_DISABLED)
#define SCIHOOK_TRIGGER_COMPUTEDELTAT_BEFORE \
std::shared_ptr<MahycoComputeDeltaTExecutionContext> ctx(new MahycoComputeDeltaTExecutionContext("ComputeDeltaTExecutionContext", &vars));\
SciHook::trigger(COMPUTEDELTAT_BEFORE, ctx);
#define SCIHOOK_TRIGGER_COMPUTEDELTAT_AFTER SciHook::trigger(COMPUTEDELTAT_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_COMPUTEDELTAT_BEFORE
#define SCIHOOK_TRIGGER_COMPUTEDELTAT_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_INITGEOMETRICVALUES_DISABLED)
#define SCIHOOK_TRIGGER_INITGEOMETRICVALUES_BEFORE \
std::shared_ptr<MahycoInitGeometricValuesExecutionContext> ctx(new MahycoInitGeometricValuesExecutionContext("InitGeometricValuesExecutionContext", &vars));\
SciHook::trigger(INITGEOMETRICVALUES_BEFORE, ctx);
#define SCIHOOK_TRIGGER_INITGEOMETRICVALUES_AFTER SciHook::trigger(INITGEOMETRICVALUES_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_INITGEOMETRICVALUES_BEFORE
#define SCIHOOK_TRIGGER_INITGEOMETRICVALUES_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_COMPUTEGEOMETRICVALUESAUX_DISABLED)
#define SCIHOOK_TRIGGER_COMPUTEGEOMETRICVALUESAUX_BEFORE \
std::shared_ptr<MahycoComputeGeometricValuesAuxExecutionContext> ctx(new MahycoComputeGeometricValuesAuxExecutionContext("ComputeGeometricValuesAuxExecutionContext", &vars));\
SciHook::trigger(COMPUTEGEOMETRICVALUESAUX_BEFORE, ctx);
#define SCIHOOK_TRIGGER_COMPUTEGEOMETRICVALUESAUX_AFTER SciHook::trigger(COMPUTEGEOMETRICVALUESAUX_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_COMPUTEGEOMETRICVALUESAUX_BEFORE
#define SCIHOOK_TRIGGER_COMPUTEGEOMETRICVALUESAUX_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_UPDATEVELOCITYWITHOUTLAGRANGE_DISABLED)
#define SCIHOOK_TRIGGER_UPDATEVELOCITYWITHOUTLAGRANGE_BEFORE \
std::shared_ptr<MahycoUpdateVelocityWithoutLagrangeExecutionContext> ctx(new MahycoUpdateVelocityWithoutLagrangeExecutionContext("UpdateVelocityWithoutLagrangeExecutionContext", &vars));\
SciHook::trigger(UPDATEVELOCITYWITHOUTLAGRANGE_BEFORE, ctx);
#define SCIHOOK_TRIGGER_UPDATEVELOCITYWITHOUTLAGRANGE_AFTER SciHook::trigger(UPDATEVELOCITYWITHOUTLAGRANGE_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_UPDATEVELOCITYWITHOUTLAGRANGE_BEFORE
#define SCIHOOK_TRIGGER_UPDATEVELOCITYWITHOUTLAGRANGE_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_UPDATEVELOCITYBACKWARD_DISABLED)
#define SCIHOOK_TRIGGER_UPDATEVELOCITYBACKWARD_BEFORE \
std::shared_ptr<MahycoUpdateVelocityBackwardExecutionContext> ctx(new MahycoUpdateVelocityBackwardExecutionContext("UpdateVelocityBackwardExecutionContext", &vars));\
SciHook::trigger(UPDATEVELOCITYBACKWARD_BEFORE, ctx);
#define SCIHOOK_TRIGGER_UPDATEVELOCITYBACKWARD_AFTER SciHook::trigger(UPDATEVELOCITYBACKWARD_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_UPDATEVELOCITYBACKWARD_BEFORE
#define SCIHOOK_TRIGGER_UPDATEVELOCITYBACKWARD_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_UPDATEVELOCITYFORWARD_DISABLED)
#define SCIHOOK_TRIGGER_UPDATEVELOCITYFORWARD_BEFORE \
std::shared_ptr<MahycoUpdateVelocityForwardExecutionContext> ctx(new MahycoUpdateVelocityForwardExecutionContext("UpdateVelocityForwardExecutionContext", &vars));\
SciHook::trigger(UPDATEVELOCITYFORWARD_BEFORE, ctx);
#define SCIHOOK_TRIGGER_UPDATEVELOCITYFORWARD_AFTER SciHook::trigger(UPDATEVELOCITYFORWARD_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_UPDATEVELOCITYFORWARD_BEFORE
#define SCIHOOK_TRIGGER_UPDATEVELOCITYFORWARD_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_UPDATEFORCEANDVELOCITY_DISABLED)
#define SCIHOOK_TRIGGER_UPDATEFORCEANDVELOCITY_BEFORE \
std::shared_ptr<MahycoUpdateForceAndVelocityExecutionContext> ctx(new MahycoUpdateForceAndVelocityExecutionContext("UpdateForceAndVelocityExecutionContext", &vars, dt));\
SciHook::trigger(UPDATEFORCEANDVELOCITY_BEFORE, ctx);
#define SCIHOOK_TRIGGER_UPDATEFORCEANDVELOCITY_AFTER SciHook::trigger(UPDATEFORCEANDVELOCITY_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_UPDATEFORCEANDVELOCITY_BEFORE
#define SCIHOOK_TRIGGER_UPDATEFORCEANDVELOCITY_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_UPDATEENERGYANDPRESSUREBYNEWTON_DISABLED)
#define SCIHOOK_TRIGGER_UPDATEENERGYANDPRESSUREBYNEWTON_BEFORE \
std::shared_ptr<MahycoUpdateEnergyAndPressurebyNewtonExecutionContext> ctx(new MahycoUpdateEnergyAndPressurebyNewtonExecutionContext("UpdateEnergyAndPressurebyNewtonExecutionContext", &vars));\
SciHook::trigger(UPDATEENERGYANDPRESSUREBYNEWTON_BEFORE, ctx);
#define SCIHOOK_TRIGGER_UPDATEENERGYANDPRESSUREBYNEWTON_AFTER SciHook::trigger(UPDATEENERGYANDPRESSUREBYNEWTON_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_UPDATEENERGYANDPRESSUREBYNEWTON_BEFORE
#define SCIHOOK_TRIGGER_UPDATEENERGYANDPRESSUREBYNEWTON_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_UPDATEENERGYANDPRESSUREFORGP_DISABLED)
#define SCIHOOK_TRIGGER_UPDATEENERGYANDPRESSUREFORGP_BEFORE \
std::shared_ptr<MahycoUpdateEnergyAndPressureforGPExecutionContext> ctx(new MahycoUpdateEnergyAndPressureforGPExecutionContext("UpdateEnergyAndPressureforGPExecutionContext", &vars));\
SciHook::trigger(UPDATEENERGYANDPRESSUREFORGP_BEFORE, ctx);
#define SCIHOOK_TRIGGER_UPDATEENERGYANDPRESSUREFORGP_AFTER SciHook::trigger(UPDATEENERGYANDPRESSUREFORGP_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_UPDATEENERGYANDPRESSUREFORGP_BEFORE
#define SCIHOOK_TRIGGER_UPDATEENERGYANDPRESSUREFORGP_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_COMPUTEAVERAGEPRESSURE_DISABLED)
#define SCIHOOK_TRIGGER_COMPUTEAVERAGEPRESSURE_BEFORE \
std::shared_ptr<MahycoComputeAveragePressureExecutionContext> ctx(new MahycoComputeAveragePressureExecutionContext("ComputeAveragePressureExecutionContext", &vars));\
SciHook::trigger(COMPUTEAVERAGEPRESSURE_BEFORE, ctx);
#define SCIHOOK_TRIGGER_COMPUTEAVERAGEPRESSURE_AFTER SciHook::trigger(COMPUTEAVERAGEPRESSURE_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_COMPUTEAVERAGEPRESSURE_BEFORE
#define SCIHOOK_TRIGGER_COMPUTEAVERAGEPRESSURE_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_COMPUTEVARIABLESFORREMAP_DISABLED)
#define SCIHOOK_TRIGGER_COMPUTEVARIABLESFORREMAP_BEFORE \
std::shared_ptr<MahycoComputeVariablesForRemapExecutionContext> ctx(new MahycoComputeVariablesForRemapExecutionContext("ComputeVariablesForRemapExecutionContext", &vars));\
SciHook::trigger(COMPUTEVARIABLESFORREMAP_BEFORE, ctx);
#define SCIHOOK_TRIGGER_COMPUTEVARIABLESFORREMAP_AFTER SciHook::trigger(COMPUTEVARIABLESFORREMAP_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_COMPUTEVARIABLESFORREMAP_BEFORE
#define SCIHOOK_TRIGGER_COMPUTEVARIABLESFORREMAP_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_COMPUTEVARIABLESFORREMAPPBORN0_DISABLED)
#define SCIHOOK_TRIGGER_COMPUTEVARIABLESFORREMAPPBORN0_BEFORE \
std::shared_ptr<MahycoComputeVariablesForRemapPBorn0ExecutionContext> ctx(new MahycoComputeVariablesForRemapPBorn0ExecutionContext("ComputeVariablesForRemapPBorn0ExecutionContext", &vars));\
SciHook::trigger(COMPUTEVARIABLESFORREMAPPBORN0_BEFORE, ctx);
#define SCIHOOK_TRIGGER_COMPUTEVARIABLESFORREMAPPBORN0_AFTER SciHook::trigger(COMPUTEVARIABLESFORREMAPPBORN0_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_COMPUTEVARIABLESFORREMAPPBORN0_BEFORE
#define SCIHOOK_TRIGGER_COMPUTEVARIABLESFORREMAPPBORN0_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_MAHYCO_COMPUTEFACEQUANTITESFORREMAP_DISABLED)
#define SCIHOOK_TRIGGER_COMPUTEFACEQUANTITESFORREMAP_BEFORE \
std::shared_ptr<MahycoComputeFaceQuantitesForRemapExecutionContext> ctx(new MahycoComputeFaceQuantitesForRemapExecutionContext("ComputeFaceQuantitesForRemapExecutionContext", &vars));\
SciHook::trigger(COMPUTEFACEQUANTITESFORREMAP_BEFORE, ctx);
#define SCIHOOK_TRIGGER_COMPUTEFACEQUANTITESFORREMAP_AFTER SciHook::trigger(COMPUTEFACEQUANTITESFORREMAP_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_COMPUTEFACEQUANTITESFORREMAP_BEFORE
#define SCIHOOK_TRIGGER_COMPUTEFACEQUANTITESFORREMAP_AFTER
#endif

#endif // MAHYCO___MAHYCOMODULESCIHOOKMACROS_H
