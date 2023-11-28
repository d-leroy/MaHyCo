#ifndef EOS_STIFFENEDGAS_STIFFENEDGASSERVICE_H
#define EOS_STIFFENEDGAS_STIFFENEDGASSERVICE_H

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#include "eos/stiffenedgas/__StiffenedGasServiceBase.h"
#include "arcane/materials/CellToAllEnvCellConverter.h"
#include "arcane/materials/ComponentSimd.h"
#include "arcane/materials/EnvCellVector.h"
#include "arcane/materials/IMeshBlock.h"
#include "arcane/materials/IMeshEnvironment.h"
#include "arcane/materials/IMeshMaterial.h"
#include "arcane/materials/IMeshMaterialMng.h"
#include "arcane/materials/MatCellVector.h"
#include "arcane/materials/MatConcurrency.h"
#include "arcane/materials/MaterialVariableBuildInfo.h"
#include "arcane/materials/MeshBlockBuildInfo.h"
#include "arcane/materials/MeshEnvironmentBuildInfo.h"
#include "arcane/materials/MeshEnvironmentVariableRef.h"
#include "arcane/materials/MeshMaterialIndirectModifier.h"
#include "arcane/materials/MeshMaterialModifier.h"
#include "arcane/materials/MeshMaterialVariableDependInfo.h"
#include "arcane/materials/MeshMaterialVariableRef.h"
#include "arcane/materials/MeshMaterialVariableSynchronizerList.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

namespace EosStiffenedgas {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

/*!
 * \brief Service StiffenedGas : implémentation
 * 
 */
class StiffenedGasService
: public StiffenedGasServiceBase<StiffenedGasService>
{
 public:
  explicit StiffenedGasService(const ServiceBuildInfo& bi);
  ~StiffenedGasService();

 public:
  void initEOS(StiffenedGasInitEOSVars& vars, ::Arcane::Materials::IMeshEnvironment* env) override;
  void applyOneCellEOS(StiffenedGasApplyOneCellEOSVars& vars, const ::Arcane::Materials::IMeshEnvironment* env, const EnvCell ev) override;
};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace EosStiffenedgas

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // EOS_STIFFENEDGAS_STIFFENEDGASSERVICE_H
