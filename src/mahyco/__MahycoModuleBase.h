#ifndef MAHYCO___MAHYCOMODULEBASE_H
#define MAHYCO___MAHYCOMODULEBASE_H

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
#include "arcane/geometry/IGeometryMng.h"
#include "mahyco/__MahycoModuleVars.h"
#include "scihook/scihookdefs.h"
#include "types_mahyco/__IMaterial.h"
#include "types_mahyco/__IEnvironment.h"
#include "cas_test/__IInitialisations.h"
#include "remap/__IRemap.h"
#include "types_mahyco/__IBoundaryCondition.h"
#include "cartesian/interface/ICartesianMesh.h"
#include "mahyco/Mahyco_axl.h"
#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED)
#include "mahyco/__MahycoModuleContexts.h"
#endif

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

using namespace Arcane;
using namespace Arcane::Materials;
namespace Mahyco {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

/*!
 * \brief Module Mahyco : classe de base. 
 *  Descripteur du module Mahyco 
 */
template<class T>
class MahycoModuleBase
: public ArcaneMahycoObject
{
 #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED)
 private:
  size_t ACCBUILD_BEFORE;
  size_t ACCBUILD_AFTER;
  size_t CHECKOPTIONS_BEFORE;
  size_t CHECKOPTIONS_AFTER;
  size_t INITCARTESIANMESH_BEFORE;
  size_t INITCARTESIANMESH_AFTER;
  size_t ALLOCCQS_BEFORE;
  size_t ALLOCCQS_AFTER;
  size_t INITDTINI_BEFORE;
  size_t INITDTINI_AFTER;
  size_t INITHYDROVAR_BEFORE;
  size_t INITHYDROVAR_AFTER;
  size_t HYDROSTARTINITENVANDMAT_BEFORE;
  size_t HYDROSTARTINITENVANDMAT_AFTER;
  size_t INITENVFORACC_BEFORE;
  size_t INITENVFORACC_AFTER;
  size_t COMPUTEGEOMETRICVALUESINI_BEFORE;
  size_t COMPUTEGEOMETRICVALUESINI_AFTER;
  size_t PREPAREFACEGROUPFORBC_BEFORE;
  size_t PREPAREFACEGROUPFORBC_AFTER;
  size_t INITBOUNDARYCONDITIONSFORACC_BEFORE;
  size_t INITBOUNDARYCONDITIONSFORACC_AFTER;
  size_t SETSYNCVARVERS_BEFORE;
  size_t SETSYNCVARVERS_AFTER;
  size_t COMPUTECELLMASS_BEFORE;
  size_t COMPUTECELLMASS_AFTER;
  size_t COMPUTENODEMASS_BEFORE;
  size_t COMPUTENODEMASS_AFTER;
  size_t CONTINUEFORMULTIMAT_BEFORE;
  size_t CONTINUEFORMULTIMAT_AFTER;
  size_t CONTINUEFORITERATIONDT_BEFORE;
  size_t CONTINUEFORITERATIONDT_AFTER;
  size_t SAVEVALUESATN_BEFORE;
  size_t SAVEVALUESATN_AFTER;
  size_t UPDATEVELOCITY_BEFORE;
  size_t UPDATEVELOCITY_AFTER;
  size_t APPLYBOUNDARYCONDITION_BEFORE;
  size_t APPLYBOUNDARYCONDITION_AFTER;
  size_t UPDATEPOSITION_BEFORE;
  size_t UPDATEPOSITION_AFTER;
  size_t COMPUTEGEOMETRICVALUES_BEFORE;
  size_t COMPUTEGEOMETRICVALUES_AFTER;
  size_t UPDATEDENSITY_BEFORE;
  size_t UPDATEDENSITY_AFTER;
  size_t COMPUTEARTIFICIALVISCOSITY_BEFORE;
  size_t COMPUTEARTIFICIALVISCOSITY_AFTER;
  size_t UPDATEENERGYANDPRESSURE_BEFORE;
  size_t UPDATEENERGYANDPRESSURE_AFTER;
  size_t REMAP_BEFORE;
  size_t REMAP_AFTER;
  size_t COMPUTEDELTAT_BEFORE;
  size_t COMPUTEDELTAT_AFTER;
  size_t INITGEOMETRICVALUES_BEFORE;
  size_t INITGEOMETRICVALUES_AFTER;
  size_t COMPUTEGEOMETRICVALUESAUX_BEFORE;
  size_t COMPUTEGEOMETRICVALUESAUX_AFTER;
  size_t UPDATEVELOCITYWITHOUTLAGRANGE_BEFORE;
  size_t UPDATEVELOCITYWITHOUTLAGRANGE_AFTER;
  size_t UPDATEVELOCITYBACKWARD_BEFORE;
  size_t UPDATEVELOCITYBACKWARD_AFTER;
  size_t UPDATEVELOCITYFORWARD_BEFORE;
  size_t UPDATEVELOCITYFORWARD_AFTER;
  size_t UPDATEFORCEANDVELOCITY_BEFORE;
  size_t UPDATEFORCEANDVELOCITY_AFTER;
  size_t UPDATEENERGYANDPRESSUREBYNEWTON_BEFORE;
  size_t UPDATEENERGYANDPRESSUREBYNEWTON_AFTER;
  size_t UPDATEENERGYANDPRESSUREFORGP_BEFORE;
  size_t UPDATEENERGYANDPRESSUREFORGP_AFTER;
  size_t COMPUTEAVERAGEPRESSURE_BEFORE;
  size_t COMPUTEAVERAGEPRESSURE_AFTER;
  size_t COMPUTEVARIABLESFORREMAP_BEFORE;
  size_t COMPUTEVARIABLESFORREMAP_AFTER;
  size_t COMPUTEFACEQUANTITESFORREMAP_BEFORE;
  size_t COMPUTEFACEQUANTITESFORREMAP_AFTER;
 #endif
 public:  // ***** CONSTRUCTEUR & DESTRUCTEUR
  explicit MahycoModuleBase(const ModuleBuildInfo& bi)
  : ArcaneMahycoObject(bi)
  , m_mesh_material_mng(IMeshMaterialMng::getReference(bi.mesh()))
  {
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED)
    ACCBUILD_BEFORE = SciHook::register_base_event("MahycoModuleBase.AccBuild.Before");
    ACCBUILD_AFTER = SciHook::register_base_event("MahycoModuleBase.AccBuild.After");
    CHECKOPTIONS_BEFORE = SciHook::register_base_event("MahycoModuleBase.CheckOptions.Before");
    CHECKOPTIONS_AFTER = SciHook::register_base_event("MahycoModuleBase.CheckOptions.After");
    INITCARTESIANMESH_BEFORE = SciHook::register_base_event("MahycoModuleBase.InitCartesianMesh.Before");
    INITCARTESIANMESH_AFTER = SciHook::register_base_event("MahycoModuleBase.InitCartesianMesh.After");
    ALLOCCQS_BEFORE = SciHook::register_base_event("MahycoModuleBase.AllocCqs.Before");
    ALLOCCQS_AFTER = SciHook::register_base_event("MahycoModuleBase.AllocCqs.After");
    INITDTINI_BEFORE = SciHook::register_base_event("MahycoModuleBase.InitDtIni.Before");
    INITDTINI_AFTER = SciHook::register_base_event("MahycoModuleBase.InitDtIni.After");
    INITHYDROVAR_BEFORE = SciHook::register_base_event("MahycoModuleBase.InitHydroVar.Before");
    INITHYDROVAR_AFTER = SciHook::register_base_event("MahycoModuleBase.InitHydroVar.After");
    HYDROSTARTINITENVANDMAT_BEFORE = SciHook::register_base_event("MahycoModuleBase.HydroStartInitEnvAndMat.Before");
    HYDROSTARTINITENVANDMAT_AFTER = SciHook::register_base_event("MahycoModuleBase.HydroStartInitEnvAndMat.After");
    INITENVFORACC_BEFORE = SciHook::register_base_event("MahycoModuleBase.InitEnvForAcc.Before");
    INITENVFORACC_AFTER = SciHook::register_base_event("MahycoModuleBase.InitEnvForAcc.After");
    COMPUTEGEOMETRICVALUESINI_BEFORE = SciHook::register_base_event("MahycoModuleBase.ComputeGeometricValuesIni.Before");
    COMPUTEGEOMETRICVALUESINI_AFTER = SciHook::register_base_event("MahycoModuleBase.ComputeGeometricValuesIni.After");
    PREPAREFACEGROUPFORBC_BEFORE = SciHook::register_base_event("MahycoModuleBase.PrepareFaceGroupForBc.Before");
    PREPAREFACEGROUPFORBC_AFTER = SciHook::register_base_event("MahycoModuleBase.PrepareFaceGroupForBc.After");
    INITBOUNDARYCONDITIONSFORACC_BEFORE = SciHook::register_base_event("MahycoModuleBase.InitBoundaryConditionsForAcc.Before");
    INITBOUNDARYCONDITIONSFORACC_AFTER = SciHook::register_base_event("MahycoModuleBase.InitBoundaryConditionsForAcc.After");
    SETSYNCVARVERS_BEFORE = SciHook::register_base_event("MahycoModuleBase.SetSyncVarVers.Before");
    SETSYNCVARVERS_AFTER = SciHook::register_base_event("MahycoModuleBase.SetSyncVarVers.After");
    COMPUTECELLMASS_BEFORE = SciHook::register_base_event("MahycoModuleBase.ComputeCellMass.Before");
    COMPUTECELLMASS_AFTER = SciHook::register_base_event("MahycoModuleBase.ComputeCellMass.After");
    COMPUTENODEMASS_BEFORE = SciHook::register_base_event("MahycoModuleBase.ComputeNodeMass.Before");
    COMPUTENODEMASS_AFTER = SciHook::register_base_event("MahycoModuleBase.ComputeNodeMass.After");
    CONTINUEFORMULTIMAT_BEFORE = SciHook::register_base_event("MahycoModuleBase.ContinueForMultiMat.Before");
    CONTINUEFORMULTIMAT_AFTER = SciHook::register_base_event("MahycoModuleBase.ContinueForMultiMat.After");
    CONTINUEFORITERATIONDT_BEFORE = SciHook::register_base_event("MahycoModuleBase.ContinueForIterationDt.Before");
    CONTINUEFORITERATIONDT_AFTER = SciHook::register_base_event("MahycoModuleBase.ContinueForIterationDt.After");
    SAVEVALUESATN_BEFORE = SciHook::register_base_event("MahycoModuleBase.SaveValuesAtN.Before");
    SAVEVALUESATN_AFTER = SciHook::register_base_event("MahycoModuleBase.SaveValuesAtN.After");
    UPDATEVELOCITY_BEFORE = SciHook::register_base_event("MahycoModuleBase.UpdateVelocity.Before");
    UPDATEVELOCITY_AFTER = SciHook::register_base_event("MahycoModuleBase.UpdateVelocity.After");
    APPLYBOUNDARYCONDITION_BEFORE = SciHook::register_base_event("MahycoModuleBase.ApplyBoundaryCondition.Before");
    APPLYBOUNDARYCONDITION_AFTER = SciHook::register_base_event("MahycoModuleBase.ApplyBoundaryCondition.After");
    UPDATEPOSITION_BEFORE = SciHook::register_base_event("MahycoModuleBase.UpdatePosition.Before");
    UPDATEPOSITION_AFTER = SciHook::register_base_event("MahycoModuleBase.UpdatePosition.After");
    COMPUTEGEOMETRICVALUES_BEFORE = SciHook::register_base_event("MahycoModuleBase.ComputeGeometricValues.Before");
    COMPUTEGEOMETRICVALUES_AFTER = SciHook::register_base_event("MahycoModuleBase.ComputeGeometricValues.After");
    UPDATEDENSITY_BEFORE = SciHook::register_base_event("MahycoModuleBase.UpdateDensity.Before");
    UPDATEDENSITY_AFTER = SciHook::register_base_event("MahycoModuleBase.UpdateDensity.After");
    COMPUTEARTIFICIALVISCOSITY_BEFORE = SciHook::register_base_event("MahycoModuleBase.ComputeArtificialViscosity.Before");
    COMPUTEARTIFICIALVISCOSITY_AFTER = SciHook::register_base_event("MahycoModuleBase.ComputeArtificialViscosity.After");
    UPDATEENERGYANDPRESSURE_BEFORE = SciHook::register_base_event("MahycoModuleBase.UpdateEnergyAndPressure.Before");
    UPDATEENERGYANDPRESSURE_AFTER = SciHook::register_base_event("MahycoModuleBase.UpdateEnergyAndPressure.After");
    REMAP_BEFORE = SciHook::register_base_event("MahycoModuleBase.Remap.Before");
    REMAP_AFTER = SciHook::register_base_event("MahycoModuleBase.Remap.After");
    COMPUTEDELTAT_BEFORE = SciHook::register_base_event("MahycoModuleBase.ComputeDeltaT.Before");
    COMPUTEDELTAT_AFTER = SciHook::register_base_event("MahycoModuleBase.ComputeDeltaT.After");
    INITGEOMETRICVALUES_BEFORE = SciHook::register_base_event("MahycoModuleBase.InitGeometricValues.Before");
    INITGEOMETRICVALUES_AFTER = SciHook::register_base_event("MahycoModuleBase.InitGeometricValues.After");
    COMPUTEGEOMETRICVALUESAUX_BEFORE = SciHook::register_base_event("MahycoModuleBase.ComputeGeometricValuesAux.Before");
    COMPUTEGEOMETRICVALUESAUX_AFTER = SciHook::register_base_event("MahycoModuleBase.ComputeGeometricValuesAux.After");
    UPDATEVELOCITYWITHOUTLAGRANGE_BEFORE = SciHook::register_base_event("MahycoModuleBase.UpdateVelocityWithoutLagrange.Before");
    UPDATEVELOCITYWITHOUTLAGRANGE_AFTER = SciHook::register_base_event("MahycoModuleBase.UpdateVelocityWithoutLagrange.After");
    UPDATEVELOCITYBACKWARD_BEFORE = SciHook::register_base_event("MahycoModuleBase.UpdateVelocityBackward.Before");
    UPDATEVELOCITYBACKWARD_AFTER = SciHook::register_base_event("MahycoModuleBase.UpdateVelocityBackward.After");
    UPDATEVELOCITYFORWARD_BEFORE = SciHook::register_base_event("MahycoModuleBase.UpdateVelocityForward.Before");
    UPDATEVELOCITYFORWARD_AFTER = SciHook::register_base_event("MahycoModuleBase.UpdateVelocityForward.After");
    UPDATEFORCEANDVELOCITY_BEFORE = SciHook::register_base_event("MahycoModuleBase.UpdateForceAndVelocity.Before");
    UPDATEFORCEANDVELOCITY_AFTER = SciHook::register_base_event("MahycoModuleBase.UpdateForceAndVelocity.After");
    UPDATEENERGYANDPRESSUREBYNEWTON_BEFORE = SciHook::register_base_event("MahycoModuleBase.UpdateEnergyAndPressurebyNewton.Before");
    UPDATEENERGYANDPRESSUREBYNEWTON_AFTER = SciHook::register_base_event("MahycoModuleBase.UpdateEnergyAndPressurebyNewton.After");
    UPDATEENERGYANDPRESSUREFORGP_BEFORE = SciHook::register_base_event("MahycoModuleBase.UpdateEnergyAndPressureforGP.Before");
    UPDATEENERGYANDPRESSUREFORGP_AFTER = SciHook::register_base_event("MahycoModuleBase.UpdateEnergyAndPressureforGP.After");
    COMPUTEAVERAGEPRESSURE_BEFORE = SciHook::register_base_event("MahycoModuleBase.ComputeAveragePressure.Before");
    COMPUTEAVERAGEPRESSURE_AFTER = SciHook::register_base_event("MahycoModuleBase.ComputeAveragePressure.After");
    COMPUTEVARIABLESFORREMAP_BEFORE = SciHook::register_base_event("MahycoModuleBase.ComputeVariablesForRemap.Before");
    COMPUTEVARIABLESFORREMAP_AFTER = SciHook::register_base_event("MahycoModuleBase.ComputeVariablesForRemap.After");
    COMPUTEFACEQUANTITESFORREMAP_BEFORE = SciHook::register_base_event("MahycoModuleBase.ComputeFaceQuantitesForRemap.Before");
    COMPUTEFACEQUANTITESFORREMAP_AFTER = SciHook::register_base_event("MahycoModuleBase.ComputeFaceQuantitesForRemap.After");
    #endif
  }

  virtual ~MahycoModuleBase()
  {
  }

 public:  // ***** ACCESSEURS
  ConstArrayView< ::Types_mahyco::IMaterial* > getMaterial() { return options()->getMaterial(); }
  ConstArrayView< ::Types_mahyco::IEnvironment* > getEnvironment() { return options()->getEnvironment(); }
  ::Cas_test::IInitialisations* getCasModel() { return options()->getCasModel(); }
  ::Remap::IRemap* getRemap() { return options()->getRemap(); }
  bool getCartesianSortFaces() { return options()->getCartesianSortFaces(); }
  bool getSchemaCsts() { return options()->getSchemaCsts(); }
  bool getPseudoCentree() { return options()->getPseudoCentree(); }
  String getLongueurCaracteristique() { return options()->getLongueurCaracteristique(); }
  Real getDeltatMin() { return options()->getDeltatMin(); }
  Real getDeltatMax() { return options()->getDeltatMax(); }
  Real getDeltatInit() { return options()->getDeltatInit(); }
  Real getFinalTime() { return options()->getFinalTime(); }
  Real getCfl() { return options()->getCfl(); }
  Real getThreshold() { return options()->getThreshold(); }
  bool getSansLagrange() { return options()->getSansLagrange(); }
  bool getWithNewton() { return options()->getWithNewton(); }
  bool getWithProjection() { return options()->getWithProjection(); }
  ConstArrayView< ::Types_mahyco::IBoundaryCondition* > getBoundaryCondition() { return options()->getBoundaryCondition(); }
  ::Arcane::Numerics::IGeometryMng* getGeometry() { return options()->getGeometry(); }
  Integer getDimension() { return options()->getDimension(); }
  ::CartesianInterface::ICartesianMesh* getCartesianMesh() { return options()->getCartesianMesh(); }
  VersionInfo versionInfo() const { return VersionInfo("1.0"); }
  IMeshMaterialMng* getMeshMaterialMng() const { return m_mesh_material_mng; }

 public:  // ***** METHODES CONCRETES
  /*!
    Pour préparer les accélérateurs 
   Cette méthode construit les variables et appelle MahycoModule::accBuild.
  */
  void accBuild()
  {
    MahycoAccBuildVars vars;
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_ACCBUILD_DISABLED)
    std::shared_ptr<SciHook::SciHookExecutionContext> ctx(
        new SciHook::SciHookExecutionContext("AccBuildExecutionContext"));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_ACCBUILD_DISABLED)
    SciHook::trigger(ACCBUILD_BEFORE, ctx);
    this->accBuild(vars);
    SciHook::trigger(ACCBUILD_AFTER, ctx);
    #else
    this->accBuild(vars);
    #endif
  }

  /*!
    Vérification de la compatibilité des options 
   Cette méthode construit les variables et appelle MahycoModule::checkOptions.
  */
  void checkOptions()
  {
    MahycoCheckOptionsVars vars;
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_CHECKOPTIONS_DISABLED)
    std::shared_ptr<SciHook::SciHookExecutionContext> ctx(
        new SciHook::SciHookExecutionContext("CheckOptionsExecutionContext"));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_CHECKOPTIONS_DISABLED)
    SciHook::trigger(CHECKOPTIONS_BEFORE, ctx);
    this->checkOptions(vars);
    SciHook::trigger(CHECKOPTIONS_AFTER, ctx);
    #else
    this->checkOptions(vars);
    #endif
  }

  /*!
   Cette méthode construit les variables et appelle MahycoModule::initCartesianMesh.
  */
  void initCartesianMesh()
  {
    MahycoInitCartesianMeshVars vars;
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_INITCARTESIANMESH_DISABLED)
    std::shared_ptr<SciHook::SciHookExecutionContext> ctx(
        new SciHook::SciHookExecutionContext("InitCartesianMeshExecutionContext"));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_INITCARTESIANMESH_DISABLED)
    SciHook::trigger(INITCARTESIANMESH_BEFORE, ctx);
    this->initCartesianMesh(vars);
    SciHook::trigger(INITCARTESIANMESH_AFTER, ctx);
    #else
    this->initCartesianMesh(vars);
    #endif
  }

  /*!
   \dot
     digraph allocCqsGraph
     {
       compound="true";
       edge [arrowsize="0.5", fontsize="8"];
       node [shape="box", fontname="Arial", fontsize="10"];
       {
         rank=same;
         allocCqs [style="rounded, filled", fillcolor="gray"];
         outVars [shape="record", label="cell_cqs | cell_cqs_n"];
         allocCqs -> outVars;
       }
   
     }
   \enddot
   Cette méthode construit les variables et appelle MahycoModule::allocCqs.
  */
  void allocCqs()
  {
    MahycoAllocCqsVars vars(m_cell_cqs
        , m_cell_cqs_n);
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_ALLOCCQS_DISABLED)
    std::shared_ptr<MahycoAllocCqsExecutionContext> ctx(
        new MahycoAllocCqsExecutionContext("AllocCqsExecutionContext"
            , &vars));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_ALLOCCQS_DISABLED)
    SciHook::trigger(ALLOCCQS_BEFORE, ctx);
    this->allocCqs(vars);
    SciHook::trigger(ALLOCCQS_AFTER, ctx);
    #else
    this->allocCqs(vars);
    #endif
  }

  /*!
   Cette méthode construit les variables et appelle MahycoModule::initDtIni.
  */
  void initDtIni()
  {
    MahycoInitDtIniVars vars;
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_INITDTINI_DISABLED)
    std::shared_ptr<SciHook::SciHookExecutionContext> ctx(
        new SciHook::SciHookExecutionContext("InitDtIniExecutionContext"));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_INITDTINI_DISABLED)
    SciHook::trigger(INITDTINI_BEFORE, ctx);
    this->initDtIni(vars);
    SciHook::trigger(INITDTINI_AFTER, ctx);
    #else
    this->initDtIni(vars);
    #endif
  }

  /*!
   \dot
     digraph initHydroVarGraph
     {
       compound="true";
       edge [arrowsize="0.5", fontsize="8"];
       node [shape="box", fontname="Arial", fontsize="10"];
       {
         rank=same;
         initHydroVar [style="rounded, filled", fillcolor="gray"];
         inVars [shape="record", label="cell_cqs | mass_fraction | node_coord | cell_volume | internal_energy | sound_speed"];
         inVars -> initHydroVar;
         outVars [shape="record", label="euler_volume | cell_volume | internal_energy | sound_speed"];
         initHydroVar -> outVars;
       }
   
       subgraph clusterCalledFuncs
       {
         center="true";
         color="navy";
         MahycoModuleBase_initGeometricValues [label="initGeometricValues", color="navy", fontcolor="navy", style="rounded", URL="\ref Mahyco::MahycoModuleBase::initGeometricValues"];
       }
       initHydroVar -> MahycoModuleBase_initGeometricValues [lhead="clusterCalledFuncs", style="dashed", label=" call"];
     }
   \enddot
   Cette méthode construit les variables et appelle MahycoModule::initHydroVar.
  */
  void initHydroVar()
  {
    MahycoInitHydroVarVars vars(m_cell_cqs
        , m_mass_fraction
        , m_node_coord
        , m_euler_volume
        , m_cell_volume
        , m_internal_energy
        , m_sound_speed);
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_INITHYDROVAR_DISABLED)
    std::shared_ptr<MahycoInitHydroVarExecutionContext> ctx(
        new MahycoInitHydroVarExecutionContext("InitHydroVarExecutionContext"
            , &vars));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_INITHYDROVAR_DISABLED)
    SciHook::trigger(INITHYDROVAR_BEFORE, ctx);
    this->initHydroVar(vars);
    SciHook::trigger(INITHYDROVAR_AFTER, ctx);
    #else
    this->initHydroVar(vars);
    #endif
  }

  /*!
   \dot
     digraph hydroStartInitEnvAndMatGraph
     {
       compound="true";
       edge [arrowsize="0.5", fontsize="8"];
       node [shape="box", fontname="Arial", fontsize="10"];
       {
         rank=same;
         hydroStartInitEnvAndMat [style="rounded, filled", fillcolor="gray"];
         inVars [shape="record", label="materiau | node_coord"];
         inVars -> hydroStartInitEnvAndMat;
         outVars [shape="record", label="sens_projection | cell_coord"];
         hydroStartInitEnvAndMat -> outVars;
       }
   
     }
   \enddot
   Cette méthode construit les variables et appelle MahycoModule::hydroStartInitEnvAndMat.
  */
  void hydroStartInitEnvAndMat()
  {
    MahycoHydroStartInitEnvAndMatVars vars(m_materiau
        , m_sens_projection
        , m_node_coord
        , m_cell_coord);
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_HYDROSTARTINITENVANDMAT_DISABLED)
    std::shared_ptr<MahycoHydroStartInitEnvAndMatExecutionContext> ctx(
        new MahycoHydroStartInitEnvAndMatExecutionContext("HydroStartInitEnvAndMatExecutionContext"
            , &vars));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_HYDROSTARTINITENVANDMAT_DISABLED)
    SciHook::trigger(HYDROSTARTINITENVANDMAT_BEFORE, ctx);
    this->hydroStartInitEnvAndMat(vars);
    SciHook::trigger(HYDROSTARTINITENVANDMAT_AFTER, ctx);
    #else
    this->hydroStartInitEnvAndMat(vars);
    #endif
  }

  /*!
   Cette méthode construit les variables et appelle MahycoModule::initEnvForAcc.
  */
  void initEnvForAcc()
  {
    MahycoInitEnvForAccVars vars;
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_INITENVFORACC_DISABLED)
    std::shared_ptr<SciHook::SciHookExecutionContext> ctx(
        new SciHook::SciHookExecutionContext("InitEnvForAccExecutionContext"));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_INITENVFORACC_DISABLED)
    SciHook::trigger(INITENVFORACC_BEFORE, ctx);
    this->initEnvForAcc(vars);
    SciHook::trigger(INITENVFORACC_AFTER, ctx);
    #else
    this->initEnvForAcc(vars);
    #endif
  }

  /*!
   \dot
     digraph computeGeometricValuesIniGraph
     {
       compound="true";
       edge [arrowsize="0.5", fontsize="8"];
       node [shape="box", fontname="Arial", fontsize="10"];
       {
         rank=same;
         computeGeometricValuesIni [style="rounded, filled", fillcolor="gray"];
       }
   
       subgraph clusterCalledFuncs
       {
         center="true";
         color="navy";
         MahycoModuleBase_computeGeometricValuesAux [label="computeGeometricValuesAux", color="navy", fontcolor="navy", style="rounded", URL="\ref Mahyco::MahycoModuleBase::computeGeometricValuesAux"];
       }
       computeGeometricValuesIni -> MahycoModuleBase_computeGeometricValuesAux [lhead="clusterCalledFuncs", style="dashed", label=" call"];
     }
   \enddot
   Cette méthode construit les variables et appelle MahycoModule::computeGeometricValuesIni.
  */
  void computeGeometricValuesIni()
  {
    MahycoComputeGeometricValuesIniVars vars;
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_COMPUTEGEOMETRICVALUESINI_DISABLED)
    std::shared_ptr<SciHook::SciHookExecutionContext> ctx(
        new SciHook::SciHookExecutionContext("ComputeGeometricValuesIniExecutionContext"));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_COMPUTEGEOMETRICVALUESINI_DISABLED)
    SciHook::trigger(COMPUTEGEOMETRICVALUESINI_BEFORE, ctx);
    this->computeGeometricValuesIni(vars);
    SciHook::trigger(COMPUTEGEOMETRICVALUESINI_AFTER, ctx);
    #else
    this->computeGeometricValuesIni(vars);
    #endif
  }

  /*!
   \dot
     digraph prepareFaceGroupForBcGraph
     {
       compound="true";
       edge [arrowsize="0.5", fontsize="8"];
       node [shape="box", fontname="Arial", fontsize="10"];
       {
         rank=same;
         prepareFaceGroupForBc [style="rounded, filled", fillcolor="gray"];
         inVars [shape="record", label="node_coord"];
         inVars -> prepareFaceGroupForBc;
         outVars [shape="record", label="is_dir_face"];
         prepareFaceGroupForBc -> outVars;
       }
   
     }
   \enddot
   Cette méthode construit les variables et appelle MahycoModule::prepareFaceGroupForBc.
  */
  void prepareFaceGroupForBc()
  {
    MahycoPrepareFaceGroupForBcVars vars(m_node_coord
        , m_is_dir_face);
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_PREPAREFACEGROUPFORBC_DISABLED)
    std::shared_ptr<MahycoPrepareFaceGroupForBcExecutionContext> ctx(
        new MahycoPrepareFaceGroupForBcExecutionContext("PrepareFaceGroupForBcExecutionContext"
            , &vars));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_PREPAREFACEGROUPFORBC_DISABLED)
    SciHook::trigger(PREPAREFACEGROUPFORBC_BEFORE, ctx);
    this->prepareFaceGroupForBc(vars);
    SciHook::trigger(PREPAREFACEGROUPFORBC_AFTER, ctx);
    #else
    this->prepareFaceGroupForBc(vars);
    #endif
  }

  /*!
   Cette méthode construit les variables et appelle MahycoModule::initBoundaryConditionsForAcc.
  */
  void initBoundaryConditionsForAcc()
  {
    MahycoInitBoundaryConditionsForAccVars vars;
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_INITBOUNDARYCONDITIONSFORACC_DISABLED)
    std::shared_ptr<SciHook::SciHookExecutionContext> ctx(
        new SciHook::SciHookExecutionContext("InitBoundaryConditionsForAccExecutionContext"));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_INITBOUNDARYCONDITIONSFORACC_DISABLED)
    SciHook::trigger(INITBOUNDARYCONDITIONSFORACC_BEFORE, ctx);
    this->initBoundaryConditionsForAcc(vars);
    SciHook::trigger(INITBOUNDARYCONDITIONSFORACC_AFTER, ctx);
    #else
    this->initBoundaryConditionsForAcc(vars);
    #endif
  }

  /*!
   Cette méthode construit les variables et appelle MahycoModule::setSyncVarVers.
  */
  void setSyncVarVers()
  {
    MahycoSetSyncVarVersVars vars;
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_SETSYNCVARVERS_DISABLED)
    std::shared_ptr<SciHook::SciHookExecutionContext> ctx(
        new SciHook::SciHookExecutionContext("SetSyncVarVersExecutionContext"));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_SETSYNCVARVERS_DISABLED)
    SciHook::trigger(SETSYNCVARVERS_BEFORE, ctx);
    this->setSyncVarVers(vars);
    SciHook::trigger(SETSYNCVARVERS_AFTER, ctx);
    #else
    this->setSyncVarVers(vars);
    #endif
  }

  /*!
   \dot
     digraph computeCellMassGraph
     {
       compound="true";
       edge [arrowsize="0.5", fontsize="8"];
       node [shape="box", fontname="Arial", fontsize="10"];
       {
         rank=same;
         computeCellMass [style="rounded, filled", fillcolor="gray"];
         inVars [shape="record", label="density | cell_volume | mass_fraction | cell_mass"];
         inVars -> computeCellMass;
         outVars [shape="record", label="cell_mass"];
         computeCellMass -> outVars;
       }
   
     }
   \enddot
   Cette méthode construit les variables et appelle MahycoModule::computeCellMass.
  */
  void computeCellMass()
  {
    MahycoComputeCellMassVars vars(m_density
        , m_cell_volume
        , m_mass_fraction
        , m_cell_mass);
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_COMPUTECELLMASS_DISABLED)
    std::shared_ptr<MahycoComputeCellMassExecutionContext> ctx(
        new MahycoComputeCellMassExecutionContext("ComputeCellMassExecutionContext"
            , &vars));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_COMPUTECELLMASS_DISABLED)
    SciHook::trigger(COMPUTECELLMASS_BEFORE, ctx);
    this->computeCellMass(vars);
    SciHook::trigger(COMPUTECELLMASS_AFTER, ctx);
    #else
    this->computeCellMass(vars);
    #endif
  }

  /*!
   \dot
     digraph computeNodeMassGraph
     {
       compound="true";
       edge [arrowsize="0.5", fontsize="8"];
       node [shape="box", fontname="Arial", fontsize="10"];
       {
         rank=same;
         computeNodeMass [style="rounded, filled", fillcolor="gray"];
         inVars [shape="record", label="cell_mass"];
         inVars -> computeNodeMass;
         outVars [shape="record", label="node_mass"];
         computeNodeMass -> outVars;
       }
   
     }
   \enddot
   Cette méthode construit les variables et appelle MahycoModule::computeNodeMass.
  */
  void computeNodeMass()
  {
    MahycoComputeNodeMassVars vars(m_cell_mass
        , m_node_mass);
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_COMPUTENODEMASS_DISABLED)
    std::shared_ptr<MahycoComputeNodeMassExecutionContext> ctx(
        new MahycoComputeNodeMassExecutionContext("ComputeNodeMassExecutionContext"
            , &vars));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_COMPUTENODEMASS_DISABLED)
    SciHook::trigger(COMPUTENODEMASS_BEFORE, ctx);
    this->computeNodeMass(vars);
    SciHook::trigger(COMPUTENODEMASS_AFTER, ctx);
    #else
    this->computeNodeMass(vars);
    #endif
  }

  /*!
   Cette méthode construit les variables et appelle MahycoModule::continueForMultiMat.
  */
  void continueForMultiMat()
  {
    MahycoContinueForMultiMatVars vars;
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_CONTINUEFORMULTIMAT_DISABLED)
    std::shared_ptr<SciHook::SciHookExecutionContext> ctx(
        new SciHook::SciHookExecutionContext("ContinueForMultiMatExecutionContext"));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_CONTINUEFORMULTIMAT_DISABLED)
    SciHook::trigger(CONTINUEFORMULTIMAT_BEFORE, ctx);
    this->continueForMultiMat(vars);
    SciHook::trigger(CONTINUEFORMULTIMAT_AFTER, ctx);
    #else
    this->continueForMultiMat(vars);
    #endif
  }

  /*!
   \dot
     digraph continueForIterationDtGraph
     {
       compound="true";
       edge [arrowsize="0.5", fontsize="8"];
       node [shape="box", fontname="Arial", fontsize="10"];
       {
         rank=same;
         continueForIterationDt [style="rounded, filled", fillcolor="gray"];
         inVars [shape="record", label="old_deltat"];
         inVars -> continueForIterationDt;
       }
   
     }
   \enddot
   Cette méthode construit les variables et appelle MahycoModule::continueForIterationDt.
  */
  void continueForIterationDt()
  {
    MahycoContinueForIterationDtVars vars(m_old_deltat);
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_CONTINUEFORITERATIONDT_DISABLED)
    std::shared_ptr<MahycoContinueForIterationDtExecutionContext> ctx(
        new MahycoContinueForIterationDtExecutionContext("ContinueForIterationDtExecutionContext"
            , &vars));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_CONTINUEFORITERATIONDT_DISABLED)
    SciHook::trigger(CONTINUEFORITERATIONDT_BEFORE, ctx);
    this->continueForIterationDt(vars);
    SciHook::trigger(CONTINUEFORITERATIONDT_AFTER, ctx);
    #else
    this->continueForIterationDt(vars);
    #endif
  }

  /*!
   \dot
     digraph saveValuesAtNGraph
     {
       compound="true";
       edge [arrowsize="0.5", fontsize="8"];
       node [shape="box", fontname="Arial", fontsize="10"];
       {
         rank=same;
         saveValuesAtN [style="rounded, filled", fillcolor="gray"];
         inVars [shape="record", label="old_deltat | pseudo_viscosity | pressure | cell_volume | density | internal_energy | cell_cqs | velocity | node_coord_0 | pseudo_viscosity_n"];
         inVars -> saveValuesAtN;
         outVars [shape="record", label="pseudo_viscosity_nmoins1 | pressure_n | cell_volume_n | density_n | internal_energy_n | cell_cqs_n | velocity_n | node_coord | pseudo_viscosity_n"];
         saveValuesAtN -> outVars;
       }
   
     }
   \enddot
   Cette méthode construit les variables et appelle MahycoModule::saveValuesAtN.
  */
  void saveValuesAtN()
  {
    MahycoSaveValuesAtNVars vars(m_old_deltat
        , m_pseudo_viscosity
        , m_pressure
        , m_cell_volume
        , m_density
        , m_internal_energy
        , m_cell_cqs
        , m_velocity
        , m_node_coord_0
        , m_pseudo_viscosity_nmoins1
        , m_pressure_n
        , m_cell_volume_n
        , m_density_n
        , m_internal_energy_n
        , m_cell_cqs_n
        , m_velocity_n
        , m_node_coord
        , m_pseudo_viscosity_n);
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_SAVEVALUESATN_DISABLED)
    std::shared_ptr<MahycoSaveValuesAtNExecutionContext> ctx(
        new MahycoSaveValuesAtNExecutionContext("SaveValuesAtNExecutionContext"
            , &vars));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_SAVEVALUESATN_DISABLED)
    SciHook::trigger(SAVEVALUESATN_BEFORE, ctx);
    this->saveValuesAtN(vars);
    SciHook::trigger(SAVEVALUESATN_AFTER, ctx);
    #else
    this->saveValuesAtN(vars);
    #endif
  }

  /*!
   \dot
     digraph updateVelocityGraph
     {
       compound="true";
       edge [arrowsize="0.5", fontsize="8"];
       node [shape="box", fontname="Arial", fontsize="10"];
       {
         rank=same;
         updateVelocity [style="rounded, filled", fillcolor="gray"];
         inVars [shape="record", label="pressure_n | pseudo_viscosity_n | cell_cqs_n | velocity_n"];
         inVars -> updateVelocity;
         outVars [shape="record", label="velocity"];
         updateVelocity -> outVars;
       }
   
       subgraph clusterCalledFuncs
       {
         center="true";
         color="navy";
         MahycoModuleBase_updateForceAndVelocity [label="updateForceAndVelocity", color="navy", fontcolor="navy", style="rounded", URL="\ref Mahyco::MahycoModuleBase::updateForceAndVelocity"];
         MahycoModuleBase_updateVelocityBackward [label="updateVelocityBackward", color="navy", fontcolor="navy", style="rounded", URL="\ref Mahyco::MahycoModuleBase::updateVelocityBackward"];
         MahycoModuleBase_updateVelocityWithoutLagrange [label="updateVelocityWithoutLagrange", color="navy", fontcolor="navy", style="rounded", URL="\ref Mahyco::MahycoModuleBase::updateVelocityWithoutLagrange"];
       }
       updateVelocity -> MahycoModuleBase_updateVelocityWithoutLagrange [lhead="clusterCalledFuncs", style="dashed", label=" call"];
     }
   \enddot
   Cette méthode construit les variables et appelle MahycoModule::updateVelocity.
  */
  void updateVelocity()
  {
    MahycoUpdateVelocityVars vars(m_pressure_n
        , m_pseudo_viscosity_n
        , m_cell_cqs_n
        , m_velocity_n
        , m_velocity);
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_UPDATEVELOCITY_DISABLED)
    std::shared_ptr<MahycoUpdateVelocityExecutionContext> ctx(
        new MahycoUpdateVelocityExecutionContext("UpdateVelocityExecutionContext"
            , &vars));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_UPDATEVELOCITY_DISABLED)
    SciHook::trigger(UPDATEVELOCITY_BEFORE, ctx);
    this->updateVelocity(vars);
    SciHook::trigger(UPDATEVELOCITY_AFTER, ctx);
    #else
    this->updateVelocity(vars);
    #endif
  }

  /*!
   \dot
     digraph applyBoundaryConditionGraph
     {
       compound="true";
       edge [arrowsize="0.5", fontsize="8"];
       node [shape="box", fontname="Arial", fontsize="10"];
       {
         rank=same;
         applyBoundaryCondition [style="rounded, filled", fillcolor="gray"];
         inVars [shape="record", label="velocity"];
         inVars -> applyBoundaryCondition;
         outVars [shape="record", label="velocity"];
         applyBoundaryCondition -> outVars;
       }
   
     }
   \enddot
   Cette méthode construit les variables et appelle MahycoModule::applyBoundaryCondition.
  */
  void applyBoundaryCondition()
  {
    MahycoApplyBoundaryConditionVars vars(m_velocity);
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_APPLYBOUNDARYCONDITION_DISABLED)
    std::shared_ptr<MahycoApplyBoundaryConditionExecutionContext> ctx(
        new MahycoApplyBoundaryConditionExecutionContext("ApplyBoundaryConditionExecutionContext"
            , &vars));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_APPLYBOUNDARYCONDITION_DISABLED)
    SciHook::trigger(APPLYBOUNDARYCONDITION_BEFORE, ctx);
    this->applyBoundaryCondition(vars);
    SciHook::trigger(APPLYBOUNDARYCONDITION_AFTER, ctx);
    #else
    this->applyBoundaryCondition(vars);
    #endif
  }

  /*!
   \dot
     digraph updatePositionGraph
     {
       compound="true";
       edge [arrowsize="0.5", fontsize="8"];
       node [shape="box", fontname="Arial", fontsize="10"];
       {
         rank=same;
         updatePosition [style="rounded, filled", fillcolor="gray"];
         inVars [shape="record", label="velocity | node_coord"];
         inVars -> updatePosition;
         outVars [shape="record", label="cell_coord | node_coord"];
         updatePosition -> outVars;
       }
   
     }
   \enddot
   Cette méthode construit les variables et appelle MahycoModule::updatePosition.
  */
  void updatePosition()
  {
    MahycoUpdatePositionVars vars(m_velocity
        , m_cell_coord
        , m_node_coord);
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_UPDATEPOSITION_DISABLED)
    std::shared_ptr<MahycoUpdatePositionExecutionContext> ctx(
        new MahycoUpdatePositionExecutionContext("UpdatePositionExecutionContext"
            , &vars));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_UPDATEPOSITION_DISABLED)
    SciHook::trigger(UPDATEPOSITION_BEFORE, ctx);
    this->updatePosition(vars);
    SciHook::trigger(UPDATEPOSITION_AFTER, ctx);
    #else
    this->updatePosition(vars);
    #endif
  }

  /*!
   \dot
     digraph computeGeometricValuesGraph
     {
       compound="true";
       edge [arrowsize="0.5", fontsize="8"];
       node [shape="box", fontname="Arial", fontsize="10"];
       {
         rank=same;
         computeGeometricValues [style="rounded, filled", fillcolor="gray"];
       }
   
       subgraph clusterCalledFuncs
       {
         center="true";
         color="navy";
         MahycoModuleBase_computeGeometricValuesAux [label="computeGeometricValuesAux", color="navy", fontcolor="navy", style="rounded", URL="\ref Mahyco::MahycoModuleBase::computeGeometricValuesAux"];
       }
       computeGeometricValues -> MahycoModuleBase_computeGeometricValuesAux [lhead="clusterCalledFuncs", style="dashed", label=" call"];
     }
   \enddot
   Cette méthode construit les variables et appelle MahycoModule::computeGeometricValues.
  */
  void computeGeometricValues()
  {
    MahycoComputeGeometricValuesVars vars;
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_COMPUTEGEOMETRICVALUES_DISABLED)
    std::shared_ptr<SciHook::SciHookExecutionContext> ctx(
        new SciHook::SciHookExecutionContext("ComputeGeometricValuesExecutionContext"));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_COMPUTEGEOMETRICVALUES_DISABLED)
    SciHook::trigger(COMPUTEGEOMETRICVALUES_BEFORE, ctx);
    this->computeGeometricValues(vars);
    SciHook::trigger(COMPUTEGEOMETRICVALUES_AFTER, ctx);
    #else
    this->computeGeometricValues(vars);
    #endif
  }

  /*!
   \dot
     digraph updateDensityGraph
     {
       compound="true";
       edge [arrowsize="0.5", fontsize="8"];
       node [shape="box", fontname="Arial", fontsize="10"];
       {
         rank=same;
         updateDensity [style="rounded, filled", fillcolor="gray"];
         inVars [shape="record", label="cell_mass | cell_volume | density_n | density | tau_density"];
         inVars -> updateDensity;
         outVars [shape="record", label="div_u | density | tau_density"];
         updateDensity -> outVars;
       }
   
     }
   \enddot
   Cette méthode construit les variables et appelle MahycoModule::updateDensity.
  */
  void updateDensity()
  {
    MahycoUpdateDensityVars vars(m_cell_mass
        , m_cell_volume
        , m_density_n
        , m_div_u
        , m_density
        , m_tau_density);
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_UPDATEDENSITY_DISABLED)
    std::shared_ptr<MahycoUpdateDensityExecutionContext> ctx(
        new MahycoUpdateDensityExecutionContext("UpdateDensityExecutionContext"
            , &vars));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_UPDATEDENSITY_DISABLED)
    SciHook::trigger(UPDATEDENSITY_BEFORE, ctx);
    this->updateDensity(vars);
    SciHook::trigger(UPDATEDENSITY_AFTER, ctx);
    #else
    this->updateDensity(vars);
    #endif
  }

  /*!
   \dot
     digraph computeArtificialViscosityGraph
     {
       compound="true";
       edge [arrowsize="0.5", fontsize="8"];
       node [shape="box", fontname="Arial", fontsize="10"];
       {
         rank=same;
         computeArtificialViscosity [style="rounded, filled", fillcolor="gray"];
         inVars [shape="record", label="div_u | caracteristic_length | sound_speed | tau_density | fracvol | pseudo_viscosity"];
         inVars -> computeArtificialViscosity;
         outVars [shape="record", label="pseudo_viscosity"];
         computeArtificialViscosity -> outVars;
       }
   
     }
   \enddot
   Cette méthode construit les variables et appelle MahycoModule::computeArtificialViscosity.
  */
  void computeArtificialViscosity()
  {
    MahycoComputeArtificialViscosityVars vars(m_div_u
        , m_caracteristic_length
        , m_sound_speed
        , m_tau_density
        , m_fracvol
        , m_pseudo_viscosity);
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_COMPUTEARTIFICIALVISCOSITY_DISABLED)
    std::shared_ptr<MahycoComputeArtificialViscosityExecutionContext> ctx(
        new MahycoComputeArtificialViscosityExecutionContext("ComputeArtificialViscosityExecutionContext"
            , &vars));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_COMPUTEARTIFICIALVISCOSITY_DISABLED)
    SciHook::trigger(COMPUTEARTIFICIALVISCOSITY_BEFORE, ctx);
    this->computeArtificialViscosity(vars);
    SciHook::trigger(COMPUTEARTIFICIALVISCOSITY_AFTER, ctx);
    #else
    this->computeArtificialViscosity(vars);
    #endif
  }

  /*!
   \dot
     digraph updateEnergyAndPressureGraph
     {
       compound="true";
       edge [arrowsize="0.5", fontsize="8"];
       node [shape="box", fontname="Arial", fontsize="10"];
       {
         rank=same;
         updateEnergyAndPressure [style="rounded, filled", fillcolor="gray"];
       }
   
       subgraph clusterCalledFuncs
       {
         center="true";
         color="navy";
         MahycoModuleBase_updateEnergyAndPressurebyNewton [label="updateEnergyAndPressurebyNewton", color="navy", fontcolor="navy", style="rounded", URL="\ref Mahyco::MahycoModuleBase::updateEnergyAndPressurebyNewton"];
         MahycoModuleBase_updateEnergyAndPressureforGP [label="updateEnergyAndPressureforGP", color="navy", fontcolor="navy", style="rounded", URL="\ref Mahyco::MahycoModuleBase::updateEnergyAndPressureforGP"];
         MahycoModuleBase_computeAveragePressure [label="computeAveragePressure", color="navy", fontcolor="navy", style="rounded", URL="\ref Mahyco::MahycoModuleBase::computeAveragePressure"];
       }
       updateEnergyAndPressure -> MahycoModuleBase_computeAveragePressure [lhead="clusterCalledFuncs", style="dashed", label=" call"];
     }
   \enddot
   Cette méthode construit les variables et appelle MahycoModule::updateEnergyAndPressure.
  */
  void updateEnergyAndPressure()
  {
    MahycoUpdateEnergyAndPressureVars vars;
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_UPDATEENERGYANDPRESSURE_DISABLED)
    std::shared_ptr<SciHook::SciHookExecutionContext> ctx(
        new SciHook::SciHookExecutionContext("UpdateEnergyAndPressureExecutionContext"));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_UPDATEENERGYANDPRESSURE_DISABLED)
    SciHook::trigger(UPDATEENERGYANDPRESSURE_BEFORE, ctx);
    this->updateEnergyAndPressure(vars);
    SciHook::trigger(UPDATEENERGYANDPRESSURE_AFTER, ctx);
    #else
    this->updateEnergyAndPressure(vars);
    #endif
  }

  /*!
   Cette méthode construit les variables et appelle MahycoModule::remap.
  */
  void remap()
  {
    MahycoRemapVars vars;
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_REMAP_DISABLED)
    std::shared_ptr<SciHook::SciHookExecutionContext> ctx(
        new SciHook::SciHookExecutionContext("RemapExecutionContext"));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_REMAP_DISABLED)
    SciHook::trigger(REMAP_BEFORE, ctx);
    this->remap(vars);
    SciHook::trigger(REMAP_AFTER, ctx);
    #else
    this->remap(vars);
    #endif
  }

  /*!
   \dot
     digraph computeDeltaTGraph
     {
       compound="true";
       edge [arrowsize="0.5", fontsize="8"];
       node [shape="box", fontname="Arial", fontsize="10"];
       {
         rank=same;
         computeDeltaT [style="rounded, filled", fillcolor="gray"];
         outVars [shape="record", label="old_deltat"];
         computeDeltaT -> outVars;
       }
   
     }
   \enddot
   Cette méthode construit les variables et appelle MahycoModule::computeDeltaT.
  */
  void computeDeltaT()
  {
    MahycoComputeDeltaTVars vars(m_old_deltat);
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_COMPUTEDELTAT_DISABLED)
    std::shared_ptr<MahycoComputeDeltaTExecutionContext> ctx(
        new MahycoComputeDeltaTExecutionContext("ComputeDeltaTExecutionContext"
            , &vars));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_COMPUTEDELTAT_DISABLED)
    SciHook::trigger(COMPUTEDELTAT_BEFORE, ctx);
    this->computeDeltaT(vars);
    SciHook::trigger(COMPUTEDELTAT_AFTER, ctx);
    #else
    this->computeDeltaT(vars);
    #endif
  }

  /*!
   \dot
     digraph initGeometricValuesGraph
     {
       compound="true";
       edge [arrowsize="0.5", fontsize="8"];
       node [shape="box", fontname="Arial", fontsize="10"];
       {
         rank=same;
         initGeometricValues [style="rounded, filled", fillcolor="gray"];
         inVars [shape="record", label="cell_coord | node_coord | face_coord | face_normal"];
         inVars -> initGeometricValues;
         outVars [shape="record", label="node_coord_0 | outer_face_normal | face_coord | face_normal"];
         initGeometricValues -> outVars;
       }
   
     }
   \enddot
   Cette méthode construit les variables et appelle MahycoModule::initGeometricValues.
  */
  void initGeometricValues()
  {
    MahycoInitGeometricValuesVars vars(m_cell_coord
        , m_node_coord
        , m_node_coord_0
        , m_outer_face_normal
        , m_face_coord
        , m_face_normal);
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_INITGEOMETRICVALUES_DISABLED)
    std::shared_ptr<MahycoInitGeometricValuesExecutionContext> ctx(
        new MahycoInitGeometricValuesExecutionContext("InitGeometricValuesExecutionContext"
            , &vars));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_INITGEOMETRICVALUES_DISABLED)
    SciHook::trigger(INITGEOMETRICVALUES_BEFORE, ctx);
    this->initGeometricValues(vars);
    SciHook::trigger(INITGEOMETRICVALUES_AFTER, ctx);
    #else
    this->initGeometricValues(vars);
    #endif
  }

  /*!
   \dot
     digraph computeGeometricValuesAuxGraph
     {
       compound="true";
       edge [arrowsize="0.5", fontsize="8"];
       node [shape="box", fontname="Arial", fontsize="10"];
       {
         rank=same;
         computeGeometricValuesAux [style="rounded, filled", fillcolor="gray"];
         inVars [shape="record", label="fracvol | velocity | node_coord | cell_volume"];
         inVars -> computeGeometricValuesAux;
         outVars [shape="record", label="cell_cqs | caracteristic_length | node_coord | cell_volume"];
         computeGeometricValuesAux -> outVars;
       }
   
     }
   \enddot
   Cette méthode construit les variables et appelle MahycoModule::computeGeometricValuesAux.
  */
  void computeGeometricValuesAux()
  {
    MahycoComputeGeometricValuesAuxVars vars(m_fracvol
        , m_velocity
        , m_cell_cqs
        , m_caracteristic_length
        , m_node_coord
        , m_cell_volume);
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_COMPUTEGEOMETRICVALUESAUX_DISABLED)
    std::shared_ptr<MahycoComputeGeometricValuesAuxExecutionContext> ctx(
        new MahycoComputeGeometricValuesAuxExecutionContext("ComputeGeometricValuesAuxExecutionContext"
            , &vars));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_COMPUTEGEOMETRICVALUESAUX_DISABLED)
    SciHook::trigger(COMPUTEGEOMETRICVALUESAUX_BEFORE, ctx);
    this->computeGeometricValuesAux(vars);
    SciHook::trigger(COMPUTEGEOMETRICVALUESAUX_AFTER, ctx);
    #else
    this->computeGeometricValuesAux(vars);
    #endif
  }

  /*!
   \dot
     digraph updateVelocityWithoutLagrangeGraph
     {
       compound="true";
       edge [arrowsize="0.5", fontsize="8"];
       node [shape="box", fontname="Arial", fontsize="10"];
       {
         rank=same;
         updateVelocityWithoutLagrange [style="rounded, filled", fillcolor="gray"];
         inVars [shape="record", label="velocity_n"];
         inVars -> updateVelocityWithoutLagrange;
         outVars [shape="record", label="velocity"];
         updateVelocityWithoutLagrange -> outVars;
       }
   
     }
   \enddot
   Cette méthode construit les variables et appelle MahycoModule::updateVelocityWithoutLagrange.
  */
  void updateVelocityWithoutLagrange()
  {
    MahycoUpdateVelocityWithoutLagrangeVars vars(m_velocity_n
        , m_velocity);
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_UPDATEVELOCITYWITHOUTLAGRANGE_DISABLED)
    std::shared_ptr<MahycoUpdateVelocityWithoutLagrangeExecutionContext> ctx(
        new MahycoUpdateVelocityWithoutLagrangeExecutionContext("UpdateVelocityWithoutLagrangeExecutionContext"
            , &vars));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_UPDATEVELOCITYWITHOUTLAGRANGE_DISABLED)
    SciHook::trigger(UPDATEVELOCITYWITHOUTLAGRANGE_BEFORE, ctx);
    this->updateVelocityWithoutLagrange(vars);
    SciHook::trigger(UPDATEVELOCITYWITHOUTLAGRANGE_AFTER, ctx);
    #else
    this->updateVelocityWithoutLagrange(vars);
    #endif
  }

  /*!
   \dot
     digraph updateVelocityBackwardGraph
     {
       compound="true";
       edge [arrowsize="0.5", fontsize="8"];
       node [shape="box", fontname="Arial", fontsize="10"];
       {
         rank=same;
         updateVelocityBackward [style="rounded, filled", fillcolor="gray"];
         inVars [shape="record", label="pressure_n | pseudo_viscosity_n | cell_cqs_n | velocity_n"];
         inVars -> updateVelocityBackward;
         outVars [shape="record", label="velocity_n"];
         updateVelocityBackward -> outVars;
       }
   
       subgraph clusterCalledFuncs
       {
         center="true";
         color="navy";
         MahycoModuleBase_updateForceAndVelocity [label="updateForceAndVelocity", color="navy", fontcolor="navy", style="rounded", URL="\ref Mahyco::MahycoModuleBase::updateForceAndVelocity"];
       }
       updateVelocityBackward -> MahycoModuleBase_updateForceAndVelocity [lhead="clusterCalledFuncs", style="dashed", label=" call"];
     }
   \enddot
   Cette méthode construit les variables et appelle MahycoModule::updateVelocityBackward.
  */
  void updateVelocityBackward()
  {
    MahycoUpdateVelocityBackwardVars vars(m_pressure_n
        , m_pseudo_viscosity_n
        , m_cell_cqs_n
        , m_velocity_n);
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_UPDATEVELOCITYBACKWARD_DISABLED)
    std::shared_ptr<MahycoUpdateVelocityBackwardExecutionContext> ctx(
        new MahycoUpdateVelocityBackwardExecutionContext("UpdateVelocityBackwardExecutionContext"
            , &vars));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_UPDATEVELOCITYBACKWARD_DISABLED)
    SciHook::trigger(UPDATEVELOCITYBACKWARD_BEFORE, ctx);
    this->updateVelocityBackward(vars);
    SciHook::trigger(UPDATEVELOCITYBACKWARD_AFTER, ctx);
    #else
    this->updateVelocityBackward(vars);
    #endif
  }

  /*!
   \dot
     digraph updateVelocityForwardGraph
     {
       compound="true";
       edge [arrowsize="0.5", fontsize="8"];
       node [shape="box", fontname="Arial", fontsize="10"];
       {
         rank=same;
         updateVelocityForward [style="rounded, filled", fillcolor="gray"];
         inVars [shape="record", label="pressure | pseudo_viscosity | cell_cqs | velocity"];
         inVars -> updateVelocityForward;
         outVars [shape="record", label="velocity"];
         updateVelocityForward -> outVars;
       }
   
       subgraph clusterCalledFuncs
       {
         center="true";
         color="navy";
         MahycoModuleBase_updateForceAndVelocity [label="updateForceAndVelocity", color="navy", fontcolor="navy", style="rounded", URL="\ref Mahyco::MahycoModuleBase::updateForceAndVelocity"];
       }
       updateVelocityForward -> MahycoModuleBase_updateForceAndVelocity [lhead="clusterCalledFuncs", style="dashed", label=" call"];
     }
   \enddot
   Cette méthode construit les variables et appelle MahycoModule::updateVelocityForward.
  */
  void updateVelocityForward()
  {
    MahycoUpdateVelocityForwardVars vars(m_pressure
        , m_pseudo_viscosity
        , m_cell_cqs
        , m_velocity);
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_UPDATEVELOCITYFORWARD_DISABLED)
    std::shared_ptr<MahycoUpdateVelocityForwardExecutionContext> ctx(
        new MahycoUpdateVelocityForwardExecutionContext("UpdateVelocityForwardExecutionContext"
            , &vars));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_UPDATEVELOCITYFORWARD_DISABLED)
    SciHook::trigger(UPDATEVELOCITYFORWARD_BEFORE, ctx);
    this->updateVelocityForward(vars);
    SciHook::trigger(UPDATEVELOCITYFORWARD_AFTER, ctx);
    #else
    this->updateVelocityForward(vars);
    #endif
  }

  /*!
   \dot
     digraph updateForceAndVelocityGraph
     {
       compound="true";
       edge [arrowsize="0.5", fontsize="8"];
       node [shape="box", fontname="Arial", fontsize="10"];
       {
         rank=same;
         updateForceAndVelocity [style="rounded, filled", fillcolor="gray"];
         inVars [shape="record", label="node_mass | pressure | pseudo_viscosity | cell_cqs | velocity_in"];
         inVars -> updateForceAndVelocity;
         outVars [shape="record", label="force | velocity_out"];
         updateForceAndVelocity -> outVars;
       }
   
     }
   \enddot
   Cette méthode construit les variables et appelle MahycoModule::updateForceAndVelocity.
  */
  void updateForceAndVelocity(const Real dt, const MaterialVariableCellReal& pressure, const MaterialVariableCellReal& pseudo_viscosity, const VariableCellArrayReal3& cell_cqs, const VariableNodeReal3& velocity_in, VariableNodeReal3& velocity_out)
  {
    MahycoUpdateForceAndVelocityVars vars(m_node_mass
        , m_force
        , pressure
        , pseudo_viscosity
        , cell_cqs
        , velocity_in
        , velocity_out);
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_UPDATEFORCEANDVELOCITY_DISABLED)
    std::shared_ptr<MahycoUpdateForceAndVelocityExecutionContext> ctx(
        new MahycoUpdateForceAndVelocityExecutionContext("UpdateForceAndVelocityExecutionContext"
            , &vars
            , dt));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_UPDATEFORCEANDVELOCITY_DISABLED)
    SciHook::trigger(UPDATEFORCEANDVELOCITY_BEFORE, ctx);
    this->updateForceAndVelocity(vars, dt);
    SciHook::trigger(UPDATEFORCEANDVELOCITY_AFTER, ctx);
    #else
    this->updateForceAndVelocity(vars, dt);
    #endif
  }

  /*!
   \dot
     digraph updateEnergyAndPressurebyNewtonGraph
     {
       compound="true";
       edge [arrowsize="0.5", fontsize="8"];
       node [shape="box", fontname="Arial", fontsize="10"];
       {
         rank=same;
         updateEnergyAndPressurebyNewton [style="rounded, filled", fillcolor="gray"];
         inVars [shape="record", label="pseudo_viscosity | pseudo_viscosity_n | pseudo_viscosity_nmoins1 | density | density_n | internal_energy_n | pressure_n | dpde | mass_fraction | velocity | velocity_n | cell_cqs | cell_cqs_n | cell_mass | pressure | sound_speed"];
         inVars -> updateEnergyAndPressurebyNewton;
         outVars [shape="record", label="internal_energy | pressure | sound_speed"];
         updateEnergyAndPressurebyNewton -> outVars;
       }
   
     }
   \enddot
   Cette méthode construit les variables et appelle MahycoModule::updateEnergyAndPressurebyNewton.
  */
  void updateEnergyAndPressurebyNewton()
  {
    MahycoUpdateEnergyAndPressurebyNewtonVars vars(m_pseudo_viscosity
        , m_pseudo_viscosity_n
        , m_pseudo_viscosity_nmoins1
        , m_density
        , m_density_n
        , m_internal_energy_n
        , m_pressure_n
        , m_dpde
        , m_mass_fraction
        , m_velocity
        , m_velocity_n
        , m_cell_cqs
        , m_cell_cqs_n
        , m_cell_mass
        , m_internal_energy
        , m_pressure
        , m_sound_speed);
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_UPDATEENERGYANDPRESSUREBYNEWTON_DISABLED)
    std::shared_ptr<MahycoUpdateEnergyAndPressurebyNewtonExecutionContext> ctx(
        new MahycoUpdateEnergyAndPressurebyNewtonExecutionContext("UpdateEnergyAndPressurebyNewtonExecutionContext"
            , &vars));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_UPDATEENERGYANDPRESSUREBYNEWTON_DISABLED)
    SciHook::trigger(UPDATEENERGYANDPRESSUREBYNEWTON_BEFORE, ctx);
    this->updateEnergyAndPressurebyNewton(vars);
    SciHook::trigger(UPDATEENERGYANDPRESSUREBYNEWTON_AFTER, ctx);
    #else
    this->updateEnergyAndPressurebyNewton(vars);
    #endif
  }

  /*!
   \dot
     digraph updateEnergyAndPressureforGPGraph
     {
       compound="true";
       edge [arrowsize="0.5", fontsize="8"];
       node [shape="box", fontname="Arial", fontsize="10"];
       {
         rank=same;
         updateEnergyAndPressureforGP [style="rounded, filled", fillcolor="gray"];
         inVars [shape="record", label="pseudo_viscosity | pseudo_viscosity_n | pseudo_viscosity_nmoins1 | density | density_n | internal_energy_n | pressure_n | mass_fraction | velocity | velocity_n | cell_cqs | cell_cqs_n | cell_mass | pressure"];
         inVars -> updateEnergyAndPressureforGP;
         outVars [shape="record", label="internal_energy | pressure"];
         updateEnergyAndPressureforGP -> outVars;
       }
   
     }
   \enddot
   Cette méthode construit les variables et appelle MahycoModule::updateEnergyAndPressureforGP.
  */
  void updateEnergyAndPressureforGP()
  {
    MahycoUpdateEnergyAndPressureforGPVars vars(m_pseudo_viscosity
        , m_pseudo_viscosity_n
        , m_pseudo_viscosity_nmoins1
        , m_density
        , m_density_n
        , m_internal_energy_n
        , m_pressure_n
        , m_mass_fraction
        , m_velocity
        , m_velocity_n
        , m_cell_cqs
        , m_cell_cqs_n
        , m_cell_mass
        , m_internal_energy
        , m_pressure);
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_UPDATEENERGYANDPRESSUREFORGP_DISABLED)
    std::shared_ptr<MahycoUpdateEnergyAndPressureforGPExecutionContext> ctx(
        new MahycoUpdateEnergyAndPressureforGPExecutionContext("UpdateEnergyAndPressureforGPExecutionContext"
            , &vars));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_UPDATEENERGYANDPRESSUREFORGP_DISABLED)
    SciHook::trigger(UPDATEENERGYANDPRESSUREFORGP_BEFORE, ctx);
    this->updateEnergyAndPressureforGP(vars);
    SciHook::trigger(UPDATEENERGYANDPRESSUREFORGP_AFTER, ctx);
    #else
    this->updateEnergyAndPressureforGP(vars);
    #endif
  }

  /*!
   \dot
     digraph computeAveragePressureGraph
     {
       compound="true";
       edge [arrowsize="0.5", fontsize="8"];
       node [shape="box", fontname="Arial", fontsize="10"];
       {
         rank=same;
         computeAveragePressure [style="rounded, filled", fillcolor="gray"];
         inVars [shape="record", label="fracvol | pressure | sound_speed"];
         inVars -> computeAveragePressure;
         outVars [shape="record", label="pressure | sound_speed"];
         computeAveragePressure -> outVars;
       }
   
     }
   \enddot
   Cette méthode construit les variables et appelle MahycoModule::computeAveragePressure.
  */
  void computeAveragePressure()
  {
    MahycoComputeAveragePressureVars vars(m_fracvol
        , m_pressure
        , m_sound_speed);
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_COMPUTEAVERAGEPRESSURE_DISABLED)
    std::shared_ptr<MahycoComputeAveragePressureExecutionContext> ctx(
        new MahycoComputeAveragePressureExecutionContext("ComputeAveragePressureExecutionContext"
            , &vars));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_COMPUTEAVERAGEPRESSURE_DISABLED)
    SciHook::trigger(COMPUTEAVERAGEPRESSURE_BEFORE, ctx);
    this->computeAveragePressure(vars);
    SciHook::trigger(COMPUTEAVERAGEPRESSURE_AFTER, ctx);
    #else
    this->computeAveragePressure(vars);
    #endif
  }

  /*!
   \dot
     digraph computeVariablesForRemapGraph
     {
       compound="true";
       edge [arrowsize="0.5", fontsize="8"];
       node [shape="box", fontname="Arial", fontsize="10"];
       {
         rank=same;
         computeVariablesForRemap [style="rounded, filled", fillcolor="gray"];
         inVars [shape="record", label="cell_volume | density | internal_energy | pseudo_viscosity | fracvol | node_mass | velocity | u_lagrange"];
         inVars -> computeVariablesForRemap;
         outVars [shape="record", label="u_lagrange | u_dual_lagrange | phi_lagrange | phi_dual_lagrange"];
         computeVariablesForRemap -> outVars;
       }
   
     }
   \enddot
   Cette méthode construit les variables et appelle MahycoModule::computeVariablesForRemap.
  */
  void computeVariablesForRemap()
  {
    MahycoComputeVariablesForRemapVars vars(m_cell_volume
        , m_density
        , m_internal_energy
        , m_pseudo_viscosity
        , m_fracvol
        , m_node_mass
        , m_velocity
        , m_u_lagrange
        , m_u_dual_lagrange
        , m_phi_lagrange
        , m_phi_dual_lagrange);
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_COMPUTEVARIABLESFORREMAP_DISABLED)
    std::shared_ptr<MahycoComputeVariablesForRemapExecutionContext> ctx(
        new MahycoComputeVariablesForRemapExecutionContext("ComputeVariablesForRemapExecutionContext"
            , &vars));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_COMPUTEVARIABLESFORREMAP_DISABLED)
    SciHook::trigger(COMPUTEVARIABLESFORREMAP_BEFORE, ctx);
    this->computeVariablesForRemap(vars);
    SciHook::trigger(COMPUTEVARIABLESFORREMAP_AFTER, ctx);
    #else
    this->computeVariablesForRemap(vars);
    #endif
  }

  /*!
   \dot
     digraph computeFaceQuantitesForRemapGraph
     {
       compound="true";
       edge [arrowsize="0.5", fontsize="8"];
       node [shape="box", fontname="Arial", fontsize="10"];
       {
         rank=same;
         computeFaceQuantitesForRemap [style="rounded, filled", fillcolor="gray"];
         inVars [shape="record", label="cell_coord | node_coord | face_normal | velocity | velocity_n"];
         inVars -> computeFaceQuantitesForRemap;
         outVars [shape="record", label="face_coord | face_length_lagrange | face_normal_velocity"];
         computeFaceQuantitesForRemap -> outVars;
       }
   
     }
   \enddot
   Cette méthode construit les variables et appelle MahycoModule::computeFaceQuantitesForRemap.
  */
  void computeFaceQuantitesForRemap()
  {
    MahycoComputeFaceQuantitesForRemapVars vars(m_cell_coord
        , m_node_coord
        , m_face_normal
        , m_velocity
        , m_velocity_n
        , m_face_coord
        , m_face_length_lagrange
        , m_face_normal_velocity);
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_COMPUTEFACEQUANTITESFORREMAP_DISABLED)
    std::shared_ptr<MahycoComputeFaceQuantitesForRemapExecutionContext> ctx(
        new MahycoComputeFaceQuantitesForRemapExecutionContext("ComputeFaceQuantitesForRemapExecutionContext"
            , &vars));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_MAHYCO_DISABLED) && not defined(SCIHOOK_MAHYCO_COMPUTEFACEQUANTITESFORREMAP_DISABLED)
    SciHook::trigger(COMPUTEFACEQUANTITESFORREMAP_BEFORE, ctx);
    this->computeFaceQuantitesForRemap(vars);
    SciHook::trigger(COMPUTEFACEQUANTITESFORREMAP_AFTER, ctx);
    #else
    this->computeFaceQuantitesForRemap(vars);
    #endif
  }


 public:  // ***** METHODES ABSTRAITES
  virtual void accBuild(MahycoAccBuildVars& vars) = 0;
  virtual void checkOptions(MahycoCheckOptionsVars& vars) = 0;
  virtual void initCartesianMesh(MahycoInitCartesianMeshVars& vars) = 0;
  virtual void allocCqs(MahycoAllocCqsVars& vars) = 0;
  virtual void initDtIni(MahycoInitDtIniVars& vars) = 0;
  virtual void initHydroVar(MahycoInitHydroVarVars& vars) = 0;
  virtual void hydroStartInitEnvAndMat(MahycoHydroStartInitEnvAndMatVars& vars) = 0;
  virtual void initEnvForAcc(MahycoInitEnvForAccVars& vars) = 0;
  virtual void computeGeometricValuesIni(MahycoComputeGeometricValuesIniVars& vars) = 0;
  virtual void prepareFaceGroupForBc(MahycoPrepareFaceGroupForBcVars& vars) = 0;
  virtual void initBoundaryConditionsForAcc(MahycoInitBoundaryConditionsForAccVars& vars) = 0;
  virtual void setSyncVarVers(MahycoSetSyncVarVersVars& vars) = 0;
  virtual void computeCellMass(MahycoComputeCellMassVars& vars) = 0;
  virtual void computeNodeMass(MahycoComputeNodeMassVars& vars) = 0;
  virtual void continueForMultiMat(MahycoContinueForMultiMatVars& vars) = 0;
  virtual void continueForIterationDt(MahycoContinueForIterationDtVars& vars) = 0;
  virtual void saveValuesAtN(MahycoSaveValuesAtNVars& vars) = 0;
  virtual void updateVelocity(MahycoUpdateVelocityVars& vars) = 0;
  virtual void applyBoundaryCondition(MahycoApplyBoundaryConditionVars& vars) = 0;
  virtual void updatePosition(MahycoUpdatePositionVars& vars) = 0;
  virtual void computeGeometricValues(MahycoComputeGeometricValuesVars& vars) = 0;
  virtual void updateDensity(MahycoUpdateDensityVars& vars) = 0;
  virtual void computeArtificialViscosity(MahycoComputeArtificialViscosityVars& vars) = 0;
  virtual void updateEnergyAndPressure(MahycoUpdateEnergyAndPressureVars& vars) = 0;
  virtual void remap(MahycoRemapVars& vars) = 0;
  virtual void computeDeltaT(MahycoComputeDeltaTVars& vars) = 0;
  virtual void initGeometricValues(MahycoInitGeometricValuesVars& vars) = 0;
  virtual void computeGeometricValuesAux(MahycoComputeGeometricValuesAuxVars& vars) = 0;
  virtual void updateVelocityWithoutLagrange(MahycoUpdateVelocityWithoutLagrangeVars& vars) = 0;
  virtual void updateVelocityBackward(MahycoUpdateVelocityBackwardVars& vars) = 0;
  virtual void updateVelocityForward(MahycoUpdateVelocityForwardVars& vars) = 0;
  virtual void updateForceAndVelocity(MahycoUpdateForceAndVelocityVars& vars, const Real dt) = 0;
  virtual void updateEnergyAndPressurebyNewton(MahycoUpdateEnergyAndPressurebyNewtonVars& vars) = 0;
  virtual void updateEnergyAndPressureforGP(MahycoUpdateEnergyAndPressureforGPVars& vars) = 0;
  virtual void computeAveragePressure(MahycoComputeAveragePressureVars& vars) = 0;
  virtual void computeVariablesForRemap(MahycoComputeVariablesForRemapVars& vars) = 0;
  virtual void computeFaceQuantitesForRemap(MahycoComputeFaceQuantitesForRemapVars& vars) = 0;

 protected:  // ***** ATTRIBUTS
  IMeshMaterialMng* m_mesh_material_mng;
};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace Mahyco

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // MAHYCO___MAHYCOMODULEBASE_H
