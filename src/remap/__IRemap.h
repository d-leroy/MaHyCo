#ifndef REMAP___IREMAP_H
#define REMAP___IREMAP_H

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#include "arcane/ArcaneTypes.h"
#include "arcane/ItemTypes.h"
#include "arcane/Item.h"
#include "arcane/ItemVector.h"
#include "arcane/ItemVectorView.h"
#include "arcane/VariableTypes.h"
#include "arcane/utils/Array.h"
#include "types_mahyco/__Limiteur.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

using namespace Arcane;
namespace Remap {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

/*!
 * \brief Interface Remap
 * 
 */
class IRemap
{
 public:  // ***** CONSTRUCTEUR & DESTRUCTEUR
  IRemap() {}
  virtual ~IRemap() {}

 public:  // ***** ACCESSEURS ABSTRAITS
  virtual const String getImplName() const = 0;
  /*!  Définition de la valeur limite des petites fractions et autres  */
  virtual Integer getOrdreProjection() = 0;
  /*!  Définition de la valeur limite des petites fractions et autres  */
  virtual Real getThreshold() = 0;
  virtual Real getArithmeticThreshold() = 0;
  /*!  projection type Euler (retour sur maillage initial)  */
  virtual bool getIsEulerScheme() = 0;
  /*!  Conservation de l energie totale lors de la projection  */
  virtual bool getConservationEnergieTotale() = 0;
  /*!  projection pente borne en volume dans les mailles mixtes et en masse dans les mailles pures  */
  virtual bool getProjectionPenteBorneMixte() = 0;
  /*!  identifiant du limiteur pour les mailles mixtes  */
  virtual ::Types_mahyco::Limiteur getProjectionLimiteurId() = 0;
  /*!  identifiant du limiteur pour les mailles pures  */
  virtual ::Types_mahyco::Limiteur getProjectionLimiteurPureId() = 0;
  /*!  projection avec l'algorithme pente-borne  */
  virtual bool getProjectionPenteBorne() = 0;
  /*!  projection avec l'algorithme pente-borne en evitant l'artefact de debar avec la valeur moyenne (1) ou valeur aux mailles (2)  */
  virtual Integer getProjectionPenteBorneDebarFix() = 0;

 public:  // ***** METHODES ABSTRAITES
  /*!
  Cette méthode est implémentée dans :
  \li RemapALEServiceBase::appliRemap
  \li RemapADIServiceBase::appliRemap
  main du remap
  */
  virtual void appliRemap(const Integer dimension, const Integer withDualProjection, const Integer nb_vars_to_project, const Integer nb_env) = 0;
  /*!
  Cette méthode est implémentée dans :
  \li RemapALEServiceBase::resizeRemapVariables
  \li RemapADIServiceBase::resizeRemapVariables
  resize les variables du remap
  */
  virtual void resizeRemapVariables(const Integer nb_vars_to_project, const Integer nb_env) = 0;
  /*!
  Cette méthode est implémentée dans :
  \li RemapALEServiceBase::synchronizeUremap
  \li RemapADIServiceBase::synchronizeUremap
  synchronisation des valeurs aux cellules 
  */
  virtual void synchronizeUremap() = 0;
  /*!
  Cette méthode est implémentée dans :
  \li RemapALEServiceBase::remapVariables
  \li RemapADIServiceBase::remapVariables
  fonction final de la projection
  */
  virtual void remapVariables(const Integer dimension, const Integer withDualProjection, const Integer nb_vars_to_project, const Integer nb_env) = 0;
};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace Remap

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // REMAP___IREMAP_H
