#ifndef EOS___IEQUATIONOFSTATE_H
#define EOS___IEQUATIONOFSTATE_H

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#include "arcane/ArcaneTypes.h"
#include "arcane/ItemTypes.h"
#include "arcane/Item.h"
#include "arcane/ItemVector.h"
#include "arcane/ItemVectorView.h"
#include "arcane/VariableTypes.h"
#include "arcane/utils/Array.h"
#include "arcane/materials/ComponentItemVector.h"
#include "arcane/materials/ComponentItemVectorView.h"
#include "arcane/materials/MeshEnvironmentVariableRef.h"
#include "arcane/materials/MeshMaterialVariableRef.h"
#include "arcane/materials/IMeshMaterialMng.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

using namespace Arcane;
using namespace Arcane::Materials;
namespace Eos {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

/*!
 * \brief Interface EquationOfState
 * 
 */
class IEquationOfState
{
 public:  // ***** CONSTRUCTEUR & DESTRUCTEUR
  IEquationOfState() {}
  virtual ~IEquationOfState() {}

 public:  // ***** ACCESSEURS ABSTRAITS
  virtual const String getImplName() const = 0;
  /*!  Définition de la constante adiabatique  */
  virtual Real getAdiabaticCst() = 0;

 public:  // ***** METHODES ABSTRAITES
  /*!
  Cette méthode est implémentée dans :
  \li StiffenedGasServiceBase::initEOS
  \li PerfectGasServiceBase::initEOS
   Initialise l'équation d'état au groupe de mailles passé en argument
   et calcule la vitesse du son et l'énergie interne. 
  */
  virtual void initEOS(::Arcane::Materials::IMeshEnvironment* env) = 0;
  /*!
  Cette méthode est implémentée dans :
  \li StiffenedGasServiceBase::applyEOS
  \li PerfectGasServiceBase::applyEOS
   Applique l'équation d'état au groupe de mailles passé en argument
   et calcule la vitesse du son et la pression. 
  */
  virtual void applyEOS(::Arcane::Materials::IMeshEnvironment* env) = 0;
  /*!
  Cette méthode est implémentée dans :
  \li StiffenedGasServiceBase::applyOneCellEOS
  \li PerfectGasServiceBase::applyOneCellEOS
   Applique l'équation d'état au groupe de mailles passé en argument
   et calcule la vitesse du son et la pression pour une cellule
  */
  virtual void applyOneCellEOS(const ::Arcane::Materials::IMeshEnvironment* env, const EnvCell ev) = 0;
};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace Eos

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // EOS___IEQUATIONOFSTATE_H
