#ifndef REMAP_ALE___REMAPALESERVICECONTEXTS_H
#define REMAP_ALE___REMAPALESERVICECONTEXTS_H

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#include "arcane/ArcaneTypes.h"
#include "arcane/ItemTypes.h"
#include "arcane/Item.h"
#include "arcane/ItemVector.h"
#include "arcane/ItemVectorView.h"
#include "arcane/VariableTypes.h"
#include "arcane/utils/Array.h"
#include "scihook/scihookdefs.h"
#include "SciHook.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_ALE_DISABLED)

using namespace Arcane;
namespace RemapAle {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace RemapAle

#endif // defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_ALE_DISABLED)

#endif  // REMAP_ALE___REMAPALESERVICECONTEXTS_H
