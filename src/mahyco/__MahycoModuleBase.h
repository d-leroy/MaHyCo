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
#include "mahyco/__MahycoModuleVars.h"
#include "types_mahyco/__IMaterial.h"
#include "types_mahyco/__IEnvironment.h"
#include "cas_test/__IInitialisations.h"
#include "remap/__IRemap.h"
#include "types_mahyco/__IBoundaryCondition.h"
#include "arcane/geometry/IGeometryMng.h"
#include "mahyco/Mahyco_axl.h"
#include "mahyco/__MahycoModuleSciHookMacros.h"

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
 SCIHOOK_DECLARE_MAHYCO_MAHYCO_EVENTS

 public:  // ***** CONSTRUCTEUR & DESTRUCTEUR
  explicit MahycoModuleBase(const ModuleBuildInfo& bi)
  : ArcaneMahycoObject(bi)
  , m_mesh_material_mng(IMeshMaterialMng::getReference(bi.mesh()))
  {
    SCIHOOK_INITIALIZE_MAHYCO_MAHYCO_EVENTS
  }

  virtual ~MahycoModuleBase()
  {
  }

 public:  // ***** ACCESSEURS
  ConstArrayView< ::Types_mahyco::IMaterial* > getMaterial() { return options()->getMaterial(); }
  ConstArrayView< ::Types_mahyco::IEnvironment* > getEnvironment() { return options()->getEnvironment(); }
  ::Cas_test::IInitialisations* getCasModel() { return options()->getCasModel(); }
  ::Remap::IRemap* getRemapService() { return options()->getRemapService(); }
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
    SCIHOOK_TRIGGER_ACCBUILD_BEFORE
    this->accBuild(vars);
    SCIHOOK_TRIGGER_ACCBUILD_AFTER
  }

  /*!
    Vérification de la compatibilité des options 
   Cette méthode construit les variables et appelle MahycoModule::checkOptions.
  */
  void checkOptions()
  {
    MahycoCheckOptionsVars vars;
    SCIHOOK_TRIGGER_CHECKOPTIONS_BEFORE
    this->checkOptions(vars);
    SCIHOOK_TRIGGER_CHECKOPTIONS_AFTER
  }

  /*!
   Cette méthode construit les variables et appelle MahycoModule::initCartesianMesh.
  */
  void initCartesianMesh()
  {
    MahycoInitCartesianMeshVars vars;
    SCIHOOK_TRIGGER_INITCARTESIANMESH_BEFORE
    this->initCartesianMesh(vars);
    SCIHOOK_TRIGGER_INITCARTESIANMESH_AFTER
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
    SCIHOOK_TRIGGER_ALLOCCQS_BEFORE
    this->allocCqs(vars);
    SCIHOOK_TRIGGER_ALLOCCQS_AFTER
  }

  /*!
   Cette méthode construit les variables et appelle MahycoModule::initDtIni.
  */
  void initDtIni()
  {
    MahycoInitDtIniVars vars;
    SCIHOOK_TRIGGER_INITDTINI_BEFORE
    this->initDtIni(vars);
    SCIHOOK_TRIGGER_INITDTINI_AFTER
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
    SCIHOOK_TRIGGER_INITHYDROVAR_BEFORE
    this->initHydroVar(vars);
    SCIHOOK_TRIGGER_INITHYDROVAR_AFTER
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
    SCIHOOK_TRIGGER_HYDROSTARTINITENVANDMAT_BEFORE
    this->hydroStartInitEnvAndMat(vars);
    SCIHOOK_TRIGGER_HYDROSTARTINITENVANDMAT_AFTER
  }

  /*!
   Cette méthode construit les variables et appelle MahycoModule::initEnvForAcc.
  */
  void initEnvForAcc()
  {
    MahycoInitEnvForAccVars vars;
    SCIHOOK_TRIGGER_INITENVFORACC_BEFORE
    this->initEnvForAcc(vars);
    SCIHOOK_TRIGGER_INITENVFORACC_AFTER
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
    SCIHOOK_TRIGGER_COMPUTEGEOMETRICVALUESINI_BEFORE
    this->computeGeometricValuesIni(vars);
    SCIHOOK_TRIGGER_COMPUTEGEOMETRICVALUESINI_AFTER
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
    SCIHOOK_TRIGGER_PREPAREFACEGROUPFORBC_BEFORE
    this->prepareFaceGroupForBc(vars);
    SCIHOOK_TRIGGER_PREPAREFACEGROUPFORBC_AFTER
  }

  /*!
   Cette méthode construit les variables et appelle MahycoModule::initBoundaryConditionsForAcc.
  */
  void initBoundaryConditionsForAcc()
  {
    MahycoInitBoundaryConditionsForAccVars vars;
    SCIHOOK_TRIGGER_INITBOUNDARYCONDITIONSFORACC_BEFORE
    this->initBoundaryConditionsForAcc(vars);
    SCIHOOK_TRIGGER_INITBOUNDARYCONDITIONSFORACC_AFTER
  }

  /*!
   Cette méthode construit les variables et appelle MahycoModule::setSyncVarVers.
  */
  void setSyncVarVers()
  {
    MahycoSetSyncVarVersVars vars;
    SCIHOOK_TRIGGER_SETSYNCVARVERS_BEFORE
    this->setSyncVarVers(vars);
    SCIHOOK_TRIGGER_SETSYNCVARVERS_AFTER
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
    SCIHOOK_TRIGGER_COMPUTECELLMASS_BEFORE
    this->computeCellMass(vars);
    SCIHOOK_TRIGGER_COMPUTECELLMASS_AFTER
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
    SCIHOOK_TRIGGER_COMPUTENODEMASS_BEFORE
    this->computeNodeMass(vars);
    SCIHOOK_TRIGGER_COMPUTENODEMASS_AFTER
  }

  /*!
   Cette méthode construit les variables et appelle MahycoModule::continueForMultiMat.
  */
  void continueForMultiMat()
  {
    MahycoContinueForMultiMatVars vars;
    SCIHOOK_TRIGGER_CONTINUEFORMULTIMAT_BEFORE
    this->continueForMultiMat(vars);
    SCIHOOK_TRIGGER_CONTINUEFORMULTIMAT_AFTER
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
    SCIHOOK_TRIGGER_CONTINUEFORITERATIONDT_BEFORE
    this->continueForIterationDt(vars);
    SCIHOOK_TRIGGER_CONTINUEFORITERATIONDT_AFTER
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
    SCIHOOK_TRIGGER_SAVEVALUESATN_BEFORE
    this->saveValuesAtN(vars);
    SCIHOOK_TRIGGER_SAVEVALUESATN_AFTER
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
    SCIHOOK_TRIGGER_UPDATEVELOCITY_BEFORE
    this->updateVelocity(vars);
    SCIHOOK_TRIGGER_UPDATEVELOCITY_AFTER
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
    SCIHOOK_TRIGGER_APPLYBOUNDARYCONDITION_BEFORE
    this->applyBoundaryCondition(vars);
    SCIHOOK_TRIGGER_APPLYBOUNDARYCONDITION_AFTER
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
    SCIHOOK_TRIGGER_UPDATEPOSITION_BEFORE
    this->updatePosition(vars);
    SCIHOOK_TRIGGER_UPDATEPOSITION_AFTER
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
    SCIHOOK_TRIGGER_COMPUTEGEOMETRICVALUES_BEFORE
    this->computeGeometricValues(vars);
    SCIHOOK_TRIGGER_COMPUTEGEOMETRICVALUES_AFTER
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
    SCIHOOK_TRIGGER_UPDATEDENSITY_BEFORE
    this->updateDensity(vars);
    SCIHOOK_TRIGGER_UPDATEDENSITY_AFTER
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
    SCIHOOK_TRIGGER_COMPUTEARTIFICIALVISCOSITY_BEFORE
    this->computeArtificialViscosity(vars);
    SCIHOOK_TRIGGER_COMPUTEARTIFICIALVISCOSITY_AFTER
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
    SCIHOOK_TRIGGER_UPDATEENERGYANDPRESSURE_BEFORE
    this->updateEnergyAndPressure(vars);
    SCIHOOK_TRIGGER_UPDATEENERGYANDPRESSURE_AFTER
  }

  /*!
   \dot
     digraph remapGraph
     {
       compound="true";
       edge [arrowsize="0.5", fontsize="8"];
       node [shape="box", fontname="Arial", fontsize="10"];
       {
         rank=same;
         remap [style="rounded, filled", fillcolor="gray"];
         inVars [shape="record", label="fracvol"];
         inVars -> remap;
         outVars [shape="record", label="materiau | pseudo_viscosity_n | pressure_n | cell_volume_n | density_n | internal_energy_n | tau_density"];
         remap -> outVars;
       }

       subgraph clusterCalledFuncs
       {
         center="true";
         color="navy";
         MahycoModuleBase_computeVariablesForRemap [label="computeVariablesForRemap", color="navy", fontcolor="navy", style="rounded", URL="\ref Mahyco::MahycoModuleBase::computeVariablesForRemap"];
         MahycoModuleBase_computeFaceQuantitesForRemap [label="computeFaceQuantitesForRemap", color="navy", fontcolor="navy", style="rounded", URL="\ref Mahyco::MahycoModuleBase::computeFaceQuantitesForRemap"];
         MahycoModuleBase_computeAveragePressure [label="computeAveragePressure", color="navy", fontcolor="navy", style="rounded", URL="\ref Mahyco::MahycoModuleBase::computeAveragePressure"];
       }
       remap -> MahycoModuleBase_computeAveragePressure [lhead="clusterCalledFuncs", style="dashed", label=" call"];
     }
   \enddot
   Cette méthode construit les variables et appelle MahycoModule::remap.
  */
  void remap()
  {
    MahycoRemapVars vars(m_fracvol
        , m_materiau
        , m_pseudo_viscosity_n
        , m_pressure_n
        , m_cell_volume_n
        , m_density_n
        , m_internal_energy_n
        , m_tau_density);
    SCIHOOK_TRIGGER_REMAP_BEFORE
    this->remap(vars);
    SCIHOOK_TRIGGER_REMAP_AFTER
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
    SCIHOOK_TRIGGER_COMPUTEDELTAT_BEFORE
    this->computeDeltaT(vars);
    SCIHOOK_TRIGGER_COMPUTEDELTAT_AFTER
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
    SCIHOOK_TRIGGER_INITGEOMETRICVALUES_BEFORE
    this->initGeometricValues(vars);
    SCIHOOK_TRIGGER_INITGEOMETRICVALUES_AFTER
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
    SCIHOOK_TRIGGER_COMPUTEGEOMETRICVALUESAUX_BEFORE
    this->computeGeometricValuesAux(vars);
    SCIHOOK_TRIGGER_COMPUTEGEOMETRICVALUESAUX_AFTER
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
    SCIHOOK_TRIGGER_UPDATEVELOCITYWITHOUTLAGRANGE_BEFORE
    this->updateVelocityWithoutLagrange(vars);
    SCIHOOK_TRIGGER_UPDATEVELOCITYWITHOUTLAGRANGE_AFTER
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
    SCIHOOK_TRIGGER_UPDATEVELOCITYBACKWARD_BEFORE
    this->updateVelocityBackward(vars);
    SCIHOOK_TRIGGER_UPDATEVELOCITYBACKWARD_AFTER
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
    SCIHOOK_TRIGGER_UPDATEVELOCITYFORWARD_BEFORE
    this->updateVelocityForward(vars);
    SCIHOOK_TRIGGER_UPDATEVELOCITYFORWARD_AFTER
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
    SCIHOOK_TRIGGER_UPDATEFORCEANDVELOCITY_BEFORE
    this->updateForceAndVelocity(vars, dt);
    SCIHOOK_TRIGGER_UPDATEFORCEANDVELOCITY_AFTER
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
    SCIHOOK_TRIGGER_UPDATEENERGYANDPRESSUREBYNEWTON_BEFORE
    this->updateEnergyAndPressurebyNewton(vars);
    SCIHOOK_TRIGGER_UPDATEENERGYANDPRESSUREBYNEWTON_AFTER
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
    SCIHOOK_TRIGGER_UPDATEENERGYANDPRESSUREFORGP_BEFORE
    this->updateEnergyAndPressureforGP(vars);
    SCIHOOK_TRIGGER_UPDATEENERGYANDPRESSUREFORGP_AFTER
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
    SCIHOOK_TRIGGER_COMPUTEAVERAGEPRESSURE_BEFORE
    this->computeAveragePressure(vars);
    SCIHOOK_TRIGGER_COMPUTEAVERAGEPRESSURE_AFTER
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
    SCIHOOK_TRIGGER_COMPUTEVARIABLESFORREMAP_BEFORE
    this->computeVariablesForRemap(vars);
    SCIHOOK_TRIGGER_COMPUTEVARIABLESFORREMAP_AFTER
  }

  /*!
   \dot
     digraph computeVariablesForRemap_PBorn0Graph
     {
       compound="true";
       edge [arrowsize="0.5", fontsize="8"];
       node [shape="box", fontname="Arial", fontsize="10"];
       {
         rank=same;
         computeVariablesForRemap_PBorn0 [style="rounded, filled", fillcolor="gray"];
         inVars [shape="record", label="pseudo_viscosity | density | cell_volume | internal_energy | node_mass | velocity | u_lagrange"];
         inVars -> computeVariablesForRemap_PBorn0;
         outVars [shape="record", label="u_lagrange | u_dual_lagrange | phi_lagrange | phi_dual_lagrange"];
         computeVariablesForRemap_PBorn0 -> outVars;
       }

     }
   \enddot
   Cette méthode construit les variables et appelle MahycoModule::computeVariablesForRemap_PBorn0.
  */
  void computeVariablesForRemap_PBorn0()
  {
    MahycoComputeVariablesForRemap_PBorn0Vars vars(m_pseudo_viscosity
        , m_density
        , m_cell_volume
        , m_internal_energy
        , m_node_mass
        , m_velocity
        , m_u_lagrange
        , m_u_dual_lagrange
        , m_phi_lagrange
        , m_phi_dual_lagrange);
    SCIHOOK_TRIGGER_COMPUTEVARIABLESFORREMAP_PBORN0_BEFORE
    this->computeVariablesForRemap_PBorn0(vars);
    SCIHOOK_TRIGGER_COMPUTEVARIABLESFORREMAP_PBORN0_AFTER
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
    SCIHOOK_TRIGGER_COMPUTEFACEQUANTITESFORREMAP_BEFORE
    this->computeFaceQuantitesForRemap(vars);
    SCIHOOK_TRIGGER_COMPUTEFACEQUANTITESFORREMAP_AFTER
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
  virtual void computeVariablesForRemap_PBorn0(MahycoComputeVariablesForRemap_PBorn0Vars& vars) = 0;
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
