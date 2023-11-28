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
#include "remap/ale/__RemapALEServiceSciHookMacros.h"

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
 SCIHOOK_DECLARE_REMAP_ALE_REMAPALE_EVENTS

 public:  // ***** CONSTRUCTEUR & DESTRUCTEUR
  explicit RemapALEServiceBase(const ServiceBuildInfo& bi)
  : ArcaneRemapALEObject(bi)
  {
    SCIHOOK_INITIALIZE_REMAP_ALE_REMAPALE_EVENTS
  }

  virtual ~RemapALEServiceBase()
  {
  }

 public:  // ***** ACCESSEURS
  Integer getOrdreProjection() { return options()->getOrdreProjection(); }
  Real getThreshold() { return options()->getThreshold(); }
  Real getArithmeticThreshold() { return options()->getArithmeticThreshold(); }
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
  /*!
   Cette méthode construit les variables et appelle RemapALEService::appliRemap.
  */
  void appliRemap(const Integer dimension, const Integer withDualProjection, const Integer nb_vars_to_project, const Integer nb_env) override
  {
    RemapALEAppliRemapVars vars;
    SCIHOOK_TRIGGER_REMAP_ALE_REMAPALE_APPLIREMAP_BEFORE
    this->appliRemap(vars, dimension, withDualProjection, nb_vars_to_project, nb_env);
    SCIHOOK_TRIGGER_REMAP_ALE_REMAPALE_APPLIREMAP_AFTER
  }

  /*!
   Cette méthode construit les variables et appelle RemapALEService::resizeRemapVariables.
  */
  void resizeRemapVariables(const Integer nb_vars_to_project, const Integer nb_env) override
  {
    RemapALEResizeRemapVariablesVars vars;
    SCIHOOK_TRIGGER_REMAP_ALE_REMAPALE_RESIZEREMAPVARIABLES_BEFORE
    this->resizeRemapVariables(vars, nb_vars_to_project, nb_env);
    SCIHOOK_TRIGGER_REMAP_ALE_REMAPALE_RESIZEREMAPVARIABLES_AFTER
  }

  /*!
   Cette méthode construit les variables et appelle RemapALEService::synchronizeUremap.
  */
  void synchronizeUremap() override
  {
    RemapALESynchronizeUremapVars vars;
    SCIHOOK_TRIGGER_REMAP_ALE_REMAPALE_SYNCHRONIZEUREMAP_BEFORE
    this->synchronizeUremap(vars);
    SCIHOOK_TRIGGER_REMAP_ALE_REMAPALE_SYNCHRONIZEUREMAP_AFTER
  }

  /*!
   Cette méthode construit les variables et appelle RemapALEService::remapVariables.
  */
  void remapVariables(const Integer dimension, const Integer withDualProjection, const Integer nb_vars_to_project, const Integer nb_env) override
  {
    RemapALERemapVariablesVars vars;
    SCIHOOK_TRIGGER_REMAP_ALE_REMAPALE_REMAPVARIABLES_BEFORE
    this->remapVariables(vars, dimension, withDualProjection, nb_vars_to_project, nb_env);
    SCIHOOK_TRIGGER_REMAP_ALE_REMAPALE_REMAPVARIABLES_AFTER
  }


 public:  // ***** METHODES ABSTRAITES
  virtual void appliRemap(RemapALEAppliRemapVars& vars, const Integer dimension, const Integer withDualProjection, const Integer nb_vars_to_project, const Integer nb_env) = 0;
  virtual void resizeRemapVariables(RemapALEResizeRemapVariablesVars& vars, const Integer nb_vars_to_project, const Integer nb_env) = 0;
  virtual void synchronizeUremap(RemapALESynchronizeUremapVars& vars) = 0;
  virtual void remapVariables(RemapALERemapVariablesVars& vars, const Integer dimension, const Integer withDualProjection, const Integer nb_vars_to_project, const Integer nb_env) = 0;

 protected:  // ***** ATTRIBUTS
};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace RemapAle

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // REMAP_ALE___REMAPALESERVICEBASE_H
