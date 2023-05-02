#ifndef MAHYCO_MAHYCOMODULE_H
#define MAHYCO_MAHYCOMODULE_H

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#include "mahyco/__MahycoModuleBase.h"

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

 public:
  void allocCqs(MahycoAllocCqsVars& vars) override;
  void initDtIni(MahycoInitDtIniVars& vars) override;
  void initHydroVar(MahycoInitHydroVarVars& vars) override;
  void computeGeometricValuesIni(MahycoComputeGeometricValuesIniVars& vars) override;
  void prepareFaceGroupForBc(MahycoPrepareFaceGroupForBcVars& vars) override;
  void computeCellMass(MahycoComputeCellMassVars& vars) override;
  void computeNodeMass(MahycoComputeNodeMassVars& vars) override;
  void continueForIterationDt(MahycoContinueForIterationDtVars& vars) override;
  void saveValuesAtN(MahycoSaveValuesAtNVars& vars) override;
  void updateVelocity(MahycoUpdateVelocityVars& vars) override;
  void updatePosition(MahycoUpdatePositionVars& vars) override;
  void computeGeometricValues(MahycoComputeGeometricValuesVars& vars) override;
  void updateDensity(MahycoUpdateDensityVars& vars) override;
  void computeArtificialViscosity(MahycoComputeArtificialViscosityVars& vars) override;
  void updateEnergyAndPressure(MahycoUpdateEnergyAndPressureVars& vars) override;
  void computeDeltaT(MahycoComputeDeltaTVars& vars) override;
  void initGeometricValues(MahycoInitGeometricValuesVars& vars) override;
  void computeGeometricValuesAux(MahycoComputeGeometricValuesAuxVars& vars) override;
  void updateVelocityWithoutLagrange(MahycoUpdateVelocityWithoutLagrangeVars& vars) override;
  void updateForceAndVelocity(MahycoUpdateForceAndVelocityVars& vars) override;
  void updateEnergyAndPressurebyNewton(MahycoUpdateEnergyAndPressurebyNewtonVars& vars) override;
  void updateEnergyAndPressureforGP(MahycoUpdateEnergyAndPressureforGPVars& vars) override;
  void computeAveragePressure(MahycoComputeAveragePressureVars& vars) override;
  Real computeHydroDeltaT(MahycoComputeHydroDeltaTVars& vars) override;
};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace Mahyco

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // MAHYCO_MAHYCOMODULE_H
