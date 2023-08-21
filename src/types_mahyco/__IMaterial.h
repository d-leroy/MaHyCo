#ifndef TYPES_MAHYCO___IMATERIAL_H
#define TYPES_MAHYCO___IMATERIAL_H

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
namespace Types_mahyco {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

/*!
 * \brief Interface représentant la structure Material
 * 
 */
class IMaterial
{
 public:
  IMaterial() {}
  virtual ~IMaterial() {}

 public:
  /*!  Nom du materiau  */
  virtual String getName() = 0;
};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

/*!
 * Classe représentant la structure Material
 * 
 */
class Material
: public IMaterial
{
 public:  // ***** CONSTRUCTEUR & DESTRUCTEUR
  Material()
  : m_name(String())
  {}
  virtual ~Material() {}

 public:  // ***** ACCESSEURS
  String getName() override { return m_name; }
  void setName(String value) { m_name = value ; }

 protected:  // ***** ATTRIBUTS
  String m_name;
};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace Types_mahyco

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // TYPES_MAHYCO___IMATERIAL_H
