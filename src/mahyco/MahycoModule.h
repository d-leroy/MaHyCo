#ifndef MAHYCO_MAHYCOMODULE_H
#define MAHYCO_MAHYCOMODULE_H

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#include "types_mahyco/Constants.h"
#include "mahyco/__MahycoModuleBase.h"


#include "arcane/ITimeLoopMng.h"
#include "arcane/IGhostLayerMng.h"
#include "arcane/Concurrency.h"
#include "arcane/VariableView.h"

#include "arcane/geometry/IGeometry.h"

#include "arcane/materials/CellToAllEnvCellConverter.h"

#include "arcane/utils/Simd.h"
#include "arcane/utils/SimdOperation.h"

//
#include "arcane/utils/List.h"
#include "arcane/utils/OStringStream.h"
#include "arcane/utils/ValueChecker.h"
#include "arcane/utils/StringBuilder.h"

#include "arcane/utils/Simd.h"
#include "arcane/utils/SimdOperation.h"

#include "arcane/IUnitTest.h"
#include "arcane/ITimeLoopMng.h"
#include "arcane/ITimeLoopService.h"
#include "arcane/ITimeLoop.h"
#include "arcane/TimeLoopEntryPointInfo.h"
#include "arcane/IMesh.h"
#include "arcane/IItemFamily.h"
#include "arcane/ItemPrinter.h"
#include "arcane/IParallelMng.h"
#include "arcane/IMeshModifier.h"
#include "arcane/IMeshUtilities.h"
#include "arcane/IMeshPartitioner.h"
#include "arcane/VariableDependInfo.h"

#include "arcane/Concurrency.h"
#include "arcane/VariableView.h"

#include "arcane/materials/IMeshMaterialMng.h"
#include "arcane/materials/IMeshMaterial.h"
#include "arcane/materials/IMeshEnvironment.h"
#include "arcane/materials/IMeshBlock.h"
#include "arcane/materials/MeshMaterialModifier.h"
#include "arcane/materials/MeshMaterialVariableRef.h"
#include "arcane/materials/MeshEnvironmentVariableRef.h"
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

#include "cartesian/interface/ICartesianMesh.h"
#include "cartesian/interface/CellDirectionMng.h"
#include "cartesian/interface/FaceDirectionMng.h"
#include "cartesian/interface/NodeDirectionMng.h"
#include "cartesian/interface/CartesianConnectivity.h"
//

#include "mahyco/MahycoUtils.h"

// Ajout pour accélérateur
#include "accenv/IAccEnv.h"
#include "accenv/SingletonIAccEnv.h"
#include "accenv/AcceleratorUtils.h"
//


// Pour les définitions, il faut finir par GCC car Clang et ICC définissent
// la macro __GNU__
// Pour CLANG, il n'y a pas encore d'équivalent au pragma ivdep.
// Celui qui s'en approche le plus est:
//   #pragma clang loop vectorize(enable)
// mais il ne force pas la vectorisation.
#ifdef __clang__
#  define PRAGMA_IVDEP_VALUE "clang loop vectorize(enable)"
#else
#  ifdef __INTEL_COMPILER
#    define PRAGMA_IVDEP_VALUE "ivdep"
#  else
#    ifdef __GNUC__
// S'assure qu'on compile avec la vectorisation même en '-O2'
#      pragma GCC optimize ("-ftree-vectorize")
#      define PRAGMA_IVDEP_VALUE "GCC ivdep"
#    endif
#  endif
#endif

//#undef PRAGMA_IVDEP_VALUE

#ifdef PRAGMA_IVDEP_VALUE
#define PRAGMA_IVDEP _Pragma(PRAGMA_IVDEP_VALUE)
#else
#define PRAGMA_IVDEP
#define PRAGMA_IVDEP_VALUE ""
#endif


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

namespace Mahyco {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

/*!
 * \brief Module Mahyco : implémentation
 * 
 */
class MahycoModule
: public MahycoModuleBase<MahycoModule>
{
 public:
  explicit MahycoModule(const ModuleBuildInfo& bi);
  ~MahycoModule();


  // les paramètres pour appliquer les conditions aux limites sur des noeuds de bord
  struct BoundaryCondition
  {
    NodeGroup nodes; //!< le groupe de noeuds sur lequel s'applique la CL
    NodeVectorView boundary_nodes; //!< vue relative à ce groupe de noeuds
    Real value; //!< la valeur appliquée à la composante de vitesse
    Types_mahyco::BoundaryConditionType type; //!< le type de CL
  };

 protected:
  //! Pour l'utilisation des accélérateurs
  IAccEnv* m_acc_env=nullptr;

 private:
 
  /**
   * Calcule les résultantes aux noeuds d'une maille hexaédrique.
   * La méthode utilisée est celle du découpage en quatre triangles.
   * Méthode appelée par le point d'entrée \c computeGeometricValues()
   */
  ARCCORE_HOST_DEVICE inline void computeCQs(Real3 node_coord[8], Real3 face_coord[6], Span<Real3> out_cqs);
  
  // inline void computeCQsSimd(SimdReal3 node_coord[8],SimdReal3 face_coord[6],SimdReal3 cqs[8]);

  /** Construit le maillage cartésien et les managers par direction
   */
  CartesianInterface::ICartesianMesh* _initCartMesh();

  /**
   * Calcul d'un pas de temps à partir des grandeurs hydrodynamiques
   * et affectation d'informations sur la maille qui fait le pas de temps
   *
   * \return Valeur du pas de temps hydro
   */
  template<typename DtCellInfoType>
  Real computeHydroDeltaT(DtCellInfoType &dt_cell_info);

  /* variables membre */
  // CartesianInterface:: = Arcane:: ou Cartesian::
  CartesianInterface::ICartesianMesh* m_cartesian_mesh;
  Integer m_nb_vars_to_project;
  Integer m_nb_env;
  Integer my_rank;
  Integer m_dimension;

  UniqueArray<BoundaryCondition> m_boundary_conditions;

  // Va contenir eosModel()->getAdiabaticCst(env), accessible à la fois sur CPU et GPU
  NumArray<Real,MD_Dim1> m_adiabatic_cst_env;

 public:
  void accBuild(MahycoAccBuildVars& vars) override;
  void checkOptions(MahycoCheckOptionsVars& vars) override;
  void applyBoundaryCondition(MahycoApplyBoundaryConditionVars& vars) override;
  void allocCqs(MahycoAllocCqsVars& vars) override;
  void initDtIni(MahycoInitDtIniVars& vars) override;
  void initCartesianMesh(MahycoInitCartesianMeshVars& vars) override;
  void initHydroVar(MahycoInitHydroVarVars& vars) override;
  void hydroStartInitEnvAndMat(MahycoHydroStartInitEnvAndMatVars& vars) override;
  void initEnvForAcc(MahycoInitEnvForAccVars& vars) override;
  void computeGeometricValuesIni(MahycoComputeGeometricValuesIniVars& vars) override;
  void prepareFaceGroupForBc(MahycoPrepareFaceGroupForBcVars& vars) override;
  void initBoundaryConditionsForAcc(MahycoInitBoundaryConditionsForAccVars& vars) override;
  void setSyncVarVers(MahycoSetSyncVarVersVars& vars) override;
  void computeCellMass(MahycoComputeCellMassVars& vars) override;
  void computeNodeMass(MahycoComputeNodeMassVars& vars) override;
  void continueForMultiMat(MahycoContinueForMultiMatVars& vars) override;
  void continueForIterationDt(MahycoContinueForIterationDtVars& vars) override;
  void saveValuesAtN(MahycoSaveValuesAtNVars& vars) override;
  void updateVelocity(MahycoUpdateVelocityVars& vars) override;
  void updatePosition(MahycoUpdatePositionVars& vars) override;
  void computeGeometricValues(MahycoComputeGeometricValuesVars& vars) override;
  void updateDensity(MahycoUpdateDensityVars& vars) override;
  void computeArtificialViscosity(MahycoComputeArtificialViscosityVars& vars) override;
  void updateEnergyAndPressure(MahycoUpdateEnergyAndPressureVars& vars) override;
  void remap(MahycoRemapVars& vars) override;
  void computeDeltaT(MahycoComputeDeltaTVars& vars) override;
  void initGeometricValues(MahycoInitGeometricValuesVars& vars) override;
  void computeGeometricValuesAux(MahycoComputeGeometricValuesAuxVars& vars) override;
  void updateVelocityWithoutLagrange(MahycoUpdateVelocityWithoutLagrangeVars& vars) override;
  void updateVelocityBackward(MahycoUpdateVelocityBackwardVars& vars) override;
  void updateVelocityForward(MahycoUpdateVelocityForwardVars& vars) override;
  void updateForceAndVelocity(MahycoUpdateForceAndVelocityVars& vars, const Real dt) override;
  void updateEnergyAndPressurebyNewton(MahycoUpdateEnergyAndPressurebyNewtonVars& vars) override;
  void updateEnergyAndPressureforGP(MahycoUpdateEnergyAndPressureforGPVars& vars) override;
  void computeAveragePressure(MahycoComputeAveragePressureVars& vars) override;
  void computeVariablesForRemap(MahycoComputeVariablesForRemapVars& vars) override;
  void computeVariablesForRemapPBorn0(MahycoComputeVariablesForRemapPBorn0Vars& vars) override;
  void computeFaceQuantitesForRemap(MahycoComputeFaceQuantitesForRemapVars& vars) override;
};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace Mahyco

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // MAHYCO_MAHYCOMODULE_H
