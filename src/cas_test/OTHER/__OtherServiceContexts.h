#ifndef CAS_TEST_OTHER___OTHERSERVICECONTEXTS_H
#define CAS_TEST_OTHER___OTHERSERVICECONTEXTS_H

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#include "arcane/ArcaneTypes.h"
#include "arcane/ItemTypes.h"
#include "arcane/Item.h"
#include "arcane/ItemVector.h"
#include "arcane/ItemVectorView.h"
#include "arcane/VariableTypes.h"
#include "arcane/utils/Array.h"
#include "SciHook.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

using namespace Arcane;
namespace Cas_testOTHER {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

//! Classe de contexte d'exécution pour initMatMono
struct OtherInitMatMonoExecutionContext final : SciHook::SciHookExecutionContext
{
  OtherInitMatMonoExecutionContext(std::string execution_context_name,
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
struct OtherInitVarMonoExecutionContext final : SciHook::SciHookExecutionContext
{
  OtherInitVarMonoExecutionContext(std::string execution_context_name,
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
struct OtherInitMatExecutionContext final : SciHook::SciHookExecutionContext
{
  OtherInitMatExecutionContext(std::string execution_context_name,
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
struct OtherInitVarExecutionContext final : SciHook::SciHookExecutionContext
{
  OtherInitVarExecutionContext(std::string execution_context_name,
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

}  // namespace Cas_testOTHER

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // CAS_TEST_OTHER___OTHERSERVICECONTEXTS_H
