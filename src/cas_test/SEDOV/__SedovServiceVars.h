#ifndef CAS_TEST_SEDOV___SEDOVSERVICEVARS_H
#define CAS_TEST_SEDOV___SEDOVSERVICEVARS_H

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#include "arcane/ArcaneTypes.h"
#include "arcane/ItemTypes.h"
#include "arcane/Item.h"
#include "arcane/ItemVector.h"
#include "arcane/ItemVectorView.h"
#include "arcane/VariableTypes.h"
#include "arcane/utils/Array.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

using namespace Arcane;
namespace Cas_testSEDOV {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

//! Classe de variable pour initMatMono
struct SedovInitMatMonoVars final
{
  SedovInitMatMonoVars()
  {}
};

//! Classe de variable pour initVarMono
struct SedovInitVarMonoVars final
{
  SedovInitVarMonoVars()
  {}
};

//! Classe de variable pour initMat
struct SedovInitMatVars final
{
  SedovInitMatVars()
  {}
};

//! Classe de variable pour initVar
struct SedovInitVarVars final
{
  SedovInitVarVars()
  {}
};


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace Cas_testSEDOV

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // CAS_TEST_SEDOV___SEDOVSERVICEVARS_H
