#ifndef REMAP_ALE___REMAPALESERVICEBASE_H
#define REMAP_ALE___REMAPALESERVICEBASE_H

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#include "arcane/ArcaneTypes.h"
#include "arcane/ItemTypes.h"
#include "arcane/Item.h"
#include "arcane/ItemVector.h"
#include "arcane/ItemVectorView.h"
#include "arcane/VariableTypes.h"
#include "arcane/utils/Array.h"
#include "remap/__IRemap.h"
#include "remap/ale/__RemapALEServiceVars.h"
#include "types_mahyco/__Limiteur.h"
#include "remap/ale/RemapALE_axl.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

using namespace Arcane;
namespace RemapAle {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

/*!
 * \brief Service RemapALE : classe de base. 
 * 
 */
template<class T>
class RemapALEServiceBase
: public ArcaneRemapALEObject
{
 #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_ALE_DISABLED)
 private:
 #endif
 public:  // ***** CONSTRUCTEUR & DESTRUCTEUR
  explicit RemapALEServiceBase(const ServiceBuildInfo& bi)
  : ArcaneRemapALEObject(bi)
  {
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_ALE_DISABLED)
    #endif
  }

  virtual ~RemapALEServiceBase()
  {
  }

 public:  // ***** ACCESSEURS
  Integer getOrdreProjection() { return options()->getOrdreProjection(); }
  Real getThreshold() { return options()->getThreshold(); }
  bool getIsEulerScheme() { return options()->getIsEulerScheme(); }
  bool getConservationEnergieTotale() { return options()->getConservationEnergieTotale(); }
  bool getProjectionPenteBorneMixte() { return options()->getProjectionPenteBorneMixte(); }
  ::Types_mahyco::Limiteur getProjectionLimiteurId() { return options()->getProjectionLimiteurId(); }
  ::Types_mahyco::Limiteur getProjectionLimiteurPureId() { return options()->getProjectionLimiteurPureId(); }
  bool getProjectionPenteBorne() { return options()->getProjectionPenteBorne(); }
  Integer getProjectionPenteBorneDebarFix() { return options()->getProjectionPenteBorneDebarFix(); }
  Real getVolumCriteria() { return options()->getVolumCriteria(); }
  Real getAngleCriteria() { return options()->getAngleCriteria(); }
  Integer getNbIterationWinslow() { return options()->getNbIterationWinslow(); }
  Integer getProjectionDual() { return options()->getProjectionDual(); }
  const String getImplName() const { return "RemapALEService"; }

 public:  // ***** METHODES CONCRETES

 public:  // ***** METHODES ABSTRAITES

 protected:  // ***** ATTRIBUTS
};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace RemapAle

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // REMAP_ALE___REMAPALESERVICEBASE_H
