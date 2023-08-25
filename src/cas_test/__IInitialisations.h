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
#include "cas_test/__Test.h"

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
  virtual Test getCasTest() = 0;
  /*!  Option de retour arriere  */
  virtual bool getReverseOption() = 0;
  virtual bool hasReverseOption() const = 0;
  /*!  Parametre du cas test  */
  virtual Real getParameter() = 0;

 public:  // ***** METHODES ABSTRAITES
  /*!
  Cette méthode est implémentée dans :
  \li OtherServiceBase::initMatMono
  \li RiderServiceBase::initMatMono
  \li SodServiceBase::initMatMono
  \li SedovServiceBase::initMatMono
  */
  virtual void initMatMono(const Integer dim) = 0;
  /*!
  Cette méthode est implémentée dans :
  \li OtherServiceBase::initVarMono
  \li RiderServiceBase::initVarMono
  \li SodServiceBase::initVarMono
  \li SedovServiceBase::initVarMono
  */
  virtual void initVarMono(const Integer dim) = 0;
  /*!
  Cette méthode est implémentée dans :
  \li OtherServiceBase::initMat
  \li RiderServiceBase::initMat
  \li SodServiceBase::initMat
  \li SedovServiceBase::initMat
  */
  virtual void initMat(const Integer dim) = 0;
  /*!
  Cette méthode est implémentée dans :
  \li OtherServiceBase::initVar
  \li RiderServiceBase::initVar
  \li SodServiceBase::initVar
  \li SedovServiceBase::initVar
  */
  virtual void initVar(const Integer dim) = 0;
};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace Cas_test

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // CAS_TEST___IINITIALISATIONS_H
