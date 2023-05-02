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
  Real getThreshold() { return options()->getThreshold(); }
  Real getVolumCriteria() { return options()->getVolumCriteria(); }
  Real getAngleCriteria() { return options()->getAngleCriteria(); }
  Integer getNbIterationWinslow() { return options()->getNbIterationWinslow(); }
  bool getIsEulerScheme() { return options()->getIsEulerScheme(); }
  Integer getOrdreProjection() { return options()->getOrdreProjection(); }
  bool getConservationEnergieTotale() { return options()->getConservationEnergieTotale(); }
  bool getProjectionPenteBorneMixte() { return options()->getProjectionPenteBorneMixte(); }
  Integer getProjectionLimiteurId() { return options()->getProjectionLimiteurId(); }
  Integer getProjectionLimiteurPureId() { return options()->getProjectionLimiteurPureId(); }
  bool getProjectionPenteBorne() { return options()->getProjectionPenteBorne(); }
  Integer getProjectionPenteBorneDebarFix() { return options()->getProjectionPenteBorneDebarFix(); }
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
