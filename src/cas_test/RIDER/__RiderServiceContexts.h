#ifndef CAS_TEST_RIDER___RIDERSERVICECONTEXTS_H
#define CAS_TEST_RIDER___RIDERSERVICECONTEXTS_H

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#include "arcane/ArcaneTypes.h"
#include "arcane/ItemTypes.h"
#include "arcane/Item.h"
#include "arcane/ItemVector.h"
#include "arcane/ItemVectorView.h"
#include "arcane/VariableTypes.h"
#include "arcane/utils/Array.h"
#include "scihook/SciHook.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

using namespace Arcane;
namespace Cas_testRIDER {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

//! Classe de contexte d'exécution pour initMatMono
struct RiderInitMatMonoExecutionContext final : SciHook::SciHookExecutionContext
{
  RiderInitMatMonoExecutionContext(std::string execution_context_name,
      const Integer dim)
  : SciHookExecutionContext(execution_context_name)
  , dim(dim)
  {}
  
  const Integer dim;

  const pybind11::object get_dim() const {
    return pybind11::cast(dim);
  }
};

//! Classe de contexte d'exécution pour initVarMono
struct RiderInitVarMonoExecutionContext final : SciHook::SciHookExecutionContext
{
  RiderInitVarMonoExecutionContext(std::string execution_context_name,
      const Integer dim)
  : SciHookExecutionContext(execution_context_name)
  , dim(dim)
  {}
  
  const Integer dim;

  const pybind11::object get_dim() const {
    return pybind11::cast(dim);
  }
};

//! Classe de contexte d'exécution pour initMat
struct RiderInitMatExecutionContext final : SciHook::SciHookExecutionContext
{
  RiderInitMatExecutionContext(std::string execution_context_name,
      const Integer dim)
  : SciHookExecutionContext(execution_context_name)
  , dim(dim)
  {}
  
  const Integer dim;

  const pybind11::object get_dim() const {
    return pybind11::cast(dim);
  }
};

//! Classe de contexte d'exécution pour initVar
struct RiderInitVarExecutionContext final : SciHook::SciHookExecutionContext
{
  RiderInitVarExecutionContext(std::string execution_context_name,
      const Integer dim)
  : SciHookExecutionContext(execution_context_name)
  , dim(dim)
  {}
  
  const Integer dim;

  const pybind11::object get_dim() const {
    return pybind11::cast(dim);
  }
};


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace Cas_testRIDER

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // CAS_TEST_RIDER___RIDERSERVICECONTEXTS_H
