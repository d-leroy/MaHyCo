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
