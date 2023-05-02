#ifndef CAS_TEST_SEDOV___SEDOVSERVICECONTEXTS_H
#define CAS_TEST_SEDOV___SEDOVSERVICECONTEXTS_H

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
namespace Cas_testSEDOV {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

//! Classe de contexte d'exécution pour initMatMono
struct SedovInitMatMonoExecutionContext final : SciHook::SciHookExecutionContext
{
  SedovInitMatMonoExecutionContext(std::string execution_context_name,
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
struct SedovInitVarMonoExecutionContext final : SciHook::SciHookExecutionContext
{
  SedovInitVarMonoExecutionContext(std::string execution_context_name,
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
struct SedovInitMatExecutionContext final : SciHook::SciHookExecutionContext
{
  SedovInitMatExecutionContext(std::string execution_context_name,
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
struct SedovInitVarExecutionContext final : SciHook::SciHookExecutionContext
{
  SedovInitVarExecutionContext(std::string execution_context_name,
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

}  // namespace Cas_testSEDOV

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // CAS_TEST_SEDOV___SEDOVSERVICECONTEXTS_H
