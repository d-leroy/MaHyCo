#ifndef REMAP_ALE___REMAPALESERVICEBINDINGS_H
#define REMAP_ALE___REMAPALESERVICEBINDINGS_H

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
#include "remap/ale/__RemapALEServiceContexts.h"
#include "SciHook.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

using namespace Arcane;
namespace RemapAle {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void bind_remap_ale_remapale(py::module __attribute__((unused)) &m)
{
  #if not defined(SCIHOOK_REMAP_ALE_REMAPALE_DISABLED)
  auto sub_remap_ale_remapale = m.def_submodule("remap_ale_remapale", "Bindings for RemapALE");
  #endif // not defined(SCIHOOK_REMAP_ALE_REMAPALE_DISABLED)
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace RemapAle

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // REMAP_ALE___REMAPALESERVICEBINDINGS_H
