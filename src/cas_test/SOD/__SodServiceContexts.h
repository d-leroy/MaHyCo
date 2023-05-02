#ifndef CAS_TEST_SOD___SODSERVICECONTEXTS_H
#define CAS_TEST_SOD___SODSERVICECONTEXTS_H

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
namespace Cas_testSOD {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

//! Classe de contexte d'exécution pour initMatMono
struct SodInitMatMonoExecutionContext final : SciHook::SciHookExecutionContext
{
  SodInitMatMonoExecutionContext(std::string execution_context_name,
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
struct SodInitVarMonoExecutionContext final : SciHook::SciHookExecutionContext
{
  SodInitVarMonoExecutionContext(std::string execution_context_name,
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
struct SodInitMatExecutionContext final : SciHook::SciHookExecutionContext
{
  SodInitMatExecutionContext(std::string execution_context_name,
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
struct SodInitVarExecutionContext final : SciHook::SciHookExecutionContext
{
  SodInitVarExecutionContext(std::string execution_context_name,
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

}  // namespace Cas_testSOD

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // CAS_TEST_SOD___SODSERVICECONTEXTS_H
