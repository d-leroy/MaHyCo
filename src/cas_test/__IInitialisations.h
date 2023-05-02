#ifndef CAS_TEST___IINITIALISATIONS_H
#define CAS_TEST___IINITIALISATIONS_H

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
namespace Cas_test {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

/*!
 * \brief Interface Initialisations
 * 
 */
class IInitialisations
{
 public:  // ***** CONSTRUCTEUR & DESTRUCTEUR
  IInitialisations() {}
  virtual ~IInitialisations() {}

 public:  // ***** ACCESSEURS ABSTRAITS
  virtual const String getImplName() const = 0;
  /*!  Numéro du cas test  */
  virtual Integer getCasTest() = 0;
  /*!  Option de retour arriere  */
  virtual bool getReverseOption() = 0;
  /*!  Parametre du cas test  */
  virtual Real getParametre() = 0;

 public:  // ***** METHODES ABSTRAITES
  /*!
  Cette méthode est implémentée dans :
  \li SedovServiceBase::initMatMono
  \li OtherServiceBase::initMatMono
  \li RiderServiceBase::initMatMono
  \li SodServiceBase::initMatMono
  */
  virtual void initMatMono(const Integer dim) = 0;
  /*!
  Cette méthode est implémentée dans :
  \li SedovServiceBase::initVarMono
  \li OtherServiceBase::initVarMono
  \li RiderServiceBase::initVarMono
  \li SodServiceBase::initVarMono
  */
  virtual void initVarMono(const Integer dim) = 0;
  /*!
  Cette méthode est implémentée dans :
  \li SedovServiceBase::initMat
  \li OtherServiceBase::initMat
  \li RiderServiceBase::initMat
  \li SodServiceBase::initMat
  */
  virtual void initMat(const Integer dim) = 0;
  /*!
  Cette méthode est implémentée dans :
  \li SedovServiceBase::initVar
  \li OtherServiceBase::initVar
  \li RiderServiceBase::initVar
  \li SodServiceBase::initVar
  */
  virtual void initVar(const Integer dim) = 0;
};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace Cas_test

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // CAS_TEST___IINITIALISATIONS_H
