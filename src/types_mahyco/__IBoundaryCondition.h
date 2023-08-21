#ifndef TYPES_MAHYCO___IBOUNDARYCONDITION_H
#define TYPES_MAHYCO___IBOUNDARYCONDITION_H

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#include "arcane/ArcaneTypes.h"
#include "arcane/ItemTypes.h"
#include "arcane/Item.h"
#include "arcane/ItemVector.h"
#include "arcane/ItemVectorView.h"
#include "arcane/VariableTypes.h"
#include "arcane/utils/Array.h"
#include "types_mahyco/__BoundaryConditionType.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

using namespace Arcane;
namespace Types_mahyco {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

/*!
 * \brief Interface représentant la structure BoundaryCondition
 * 
 */
class IBoundaryCondition
{
 public:
  IBoundaryCondition() {}
  virtual ~IBoundaryCondition() {}

 public:
  /*!  Type de condition aux limites  */
  virtual BoundaryConditionType getType() = 0;
  /*!  Surface sur laquelle s'applique la condition aux limites  */
  virtual String getSurface() = 0;
  /*!  Valeur de la composante à fixer  */
  virtual Real getValue() = 0;
};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

/*!
 * Classe représentant la structure BoundaryCondition
 * 
 */
class BoundaryCondition
: public IBoundaryCondition
{
 public:  // ***** CONSTRUCTEUR & DESTRUCTEUR
  BoundaryCondition()
  : m_type(BoundaryConditionType())
  , m_surface(String())
  , m_value(Real())
  {}
  virtual ~BoundaryCondition() {}

 public:  // ***** ACCESSEURS
  BoundaryConditionType getType() override { return m_type; }
  void setType(BoundaryConditionType value) { m_type = value ; }

  String getSurface() override { return m_surface; }
  void setSurface(String value) { m_surface = value ; }

  Real getValue() override { return m_value; }
  void setValue(Real value) { m_value = value ; }

 protected:  // ***** ATTRIBUTS
  BoundaryConditionType m_type;
  String m_surface;
  Real m_value;
};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace Types_mahyco

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // TYPES_MAHYCO___IBOUNDARYCONDITION_H
