#ifndef EOS_PERFECTGAS_PERFECTGASNACCSERVICE_H
#define EOS_PERFECTGAS_PERFECTGASNACCSERVICE_H

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#include "eos/perfectgas/__PerfectGasNAccServiceBase.h"
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
#include "arcane/accelerator/RunCommandMaterialEnumerate.h"
#include "arcane/accelerator/VariableViews.h"
#include "arcane/accelerator/MaterialVariableViews.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
using namespace Arcane;
using namespace Arcane::Materials;

class IAccEnv;

namespace EosPerfectgas {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

/*!
 * \brief Service PerfectGasNAcc : implémentation
 * 
 */
class PerfectGasNAccService
: public PerfectGasNAccServiceBase<PerfectGasNAccService>
{
 public:
  explicit PerfectGasNAccService(const ServiceBuildInfo& bi);
  ~PerfectGasNAccService();

 public:
  void initEOS(PerfectGasNAccInitEOSVars& vars, ::Arcane::Materials::IMeshEnvironment* env) override;
  void applyEOS(PerfectGasNAccApplyEOSVars& vars, ::Arcane::Materials::IMeshEnvironment* env) override;
  void applyOneCellEOS(PerfectGasNAccApplyOneCellEOSVars& vars, const ::Arcane::Materials::IMeshEnvironment* env, const EnvCell ev) override;

 private:
  // Pour l'utilisation des accélérateurs
  IAccEnv* m_acc_env=nullptr;
};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace EosPerfectgas

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // EOS_PERFECTGAS_PERFECTGASNACCSERVICE_H
