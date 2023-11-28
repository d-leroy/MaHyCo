#ifndef REMAP_ALE___REMAPALESERVICEVARS_H
#define REMAP_ALE___REMAPALESERVICEVARS_H

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
namespace RemapAle {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

//! Classe de variable pour appliRemap
struct RemapALEAppliRemapVars final
{
  RemapALEAppliRemapVars()
  {}
};

//! Classe de variable pour resizeRemapVariables
struct RemapALEResizeRemapVariablesVars final
{
  RemapALEResizeRemapVariablesVars()
  {}
};

//! Classe de variable pour synchronizeUremap
struct RemapALESynchronizeUremapVars final
{
  RemapALESynchronizeUremapVars()
  {}
};

//! Classe de variable pour remapVariables
struct RemapALERemapVariablesVars final
{
  RemapALERemapVariablesVars()
  {}
};


/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace RemapAle

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // REMAP_ALE___REMAPALESERVICEVARS_H
