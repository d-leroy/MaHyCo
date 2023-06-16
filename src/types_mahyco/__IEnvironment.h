#ifndef TYPES_MAHYCO___IENVIRONMENT_H
#define TYPES_MAHYCO___IENVIRONMENT_H

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#include "arcane/ArcaneTypes.h"
#include "arcane/ItemTypes.h"
#include "arcane/Item.h"
#include "arcane/ItemVector.h"
#include "arcane/ItemVectorView.h"
#include "arcane/VariableTypes.h"
#include "arcane/utils/Array.h"
#include "eos/__IEquationOfState.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

using namespace Arcane;
namespace Types_mahyco {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

/*!
 * \brief Interface représentant la structure Environment
 * 
 */
class IEnvironment
{
 public:
  IEnvironment() {}
  virtual ~IEnvironment() {}

 public:
  /*!  Nom du milieu  */
  virtual String getName() = 0;
  /*!  Nom du materiau  */
  virtual ConstArrayView< String > getMaterial() = 0;
  /*!  Service d'equation d'état  */
  virtual ::Eos::IEquationOfState* getEosModel() = 0;
};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

/*!
 * Classe représentant la structure Environment
 * 
 */
class Environment
: public IEnvironment
{
 public:  // ***** CONSTRUCTEUR & DESTRUCTEUR
  Environment()
  : m_name(String())
  , m_material(UniqueArray< String >())
  , m_EosModel(0)
  {}
  virtual ~Environment() {}

 public:  // ***** ACCESSEURS
  String getName() override { return m_name; }
  void setName(String value) { m_name = value; }

  ConstArrayView< String > getMaterial() override { return m_material; }
  void setMaterial(Array< String >& value) { m_material = value; }

  ::Eos::IEquationOfState* getEosModel() override { return m_EosModel; }
  void setEosModel(::Eos::IEquationOfState* value) { m_EosModel = value; }

 protected:  // ***** ATTRIBUTS
  String m_name;
  UniqueArray< String > m_material;
  ::Eos::IEquationOfState* m_EosModel;
};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace Types_mahyco

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // TYPES_MAHYCO___IENVIRONMENT_H
