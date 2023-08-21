#ifndef CAS_TEST_OTHER___OTHERSERVICEBASE_H
#define CAS_TEST_OTHER___OTHERSERVICEBASE_H

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
#include "cas_test/__IInitialisations.h"
#include "cas_test/OTHER/__OtherServiceVars.h"
#include "cas_test/OTHER/Other_axl.h"
#include "cas_test/OTHER/__OtherServiceSciHookMacros.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

using namespace Arcane;
using namespace Arcane::Materials;
namespace Cas_testOTHER {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

/*!
 * \brief Service Other : classe de base. 
 * 
 */
template<class T>
class OtherServiceBase
: public ArcaneOtherObject
{
 SCIHOOK_DECLARE_CAS_TEST_OTHER_OTHER_EVENTS

 public:  // ***** CONSTRUCTEUR & DESTRUCTEUR
  explicit OtherServiceBase(const ServiceBuildInfo& bi)
  : ArcaneOtherObject(bi)
  , m_mesh_material_mng(IMeshMaterialMng::getReference(bi.mesh()))
  {
    SCIHOOK_INITIALIZE_CAS_TEST_OTHER_OTHER_EVENTS
  }

  virtual ~OtherServiceBase()
  {
  }

 public:  // ***** ACCESSEURS
  ::Cas_test::Test getCasTest() { return options()->getCasTest(); }
  bool getReverseOption() { return options()->getReverseOption(); }
  bool hasReverseOption() const { return options()->hasReverseOption(); }
  Real getParameter() { return options()->getParameter(); }
  const String getImplName() const { return "OtherService"; }
  IMeshMaterialMng* getMeshMaterialMng() const { return m_mesh_material_mng; }

 public:  // ***** METHODES CONCRETES
  /*!
   Cette méthode construit les variables et appelle OtherService::initMatMono.
  */
  void initMatMono(const Integer dim) override
  {
    OtherInitMatMonoVars vars;
    SCIHOOK_TRIGGER_INITMATMONO_BEFORE
    this->initMatMono(vars, dim);
    SCIHOOK_TRIGGER_INITMATMONO_AFTER
  }

  /*!
   Cette méthode construit les variables et appelle OtherService::initVarMono.
  */
  void initVarMono(const Integer dim) override
  {
    OtherInitVarMonoVars vars;
    SCIHOOK_TRIGGER_INITVARMONO_BEFORE
    this->initVarMono(vars, dim);
    SCIHOOK_TRIGGER_INITVARMONO_AFTER
  }

  /*!
   \dot
     digraph initMatGraph
     {
       compound="true";
       edge [arrowsize="0.5", fontsize="8"];
       node [shape="box", fontname="Arial", fontsize="10"];
       {
         rank=same;
         initMat [style="rounded, filled", fillcolor="gray"];
         inVars [shape="record", label="cell_coord"];
         inVars -> initMat;
         outVars [shape="record", label="materiau"];
         initMat -> outVars;
       }

     }
   \enddot
   Cette méthode construit les variables et appelle OtherService::initMat.
  */
  void initMat(const Integer dim) override
  {
    OtherInitMatVars vars(m_cell_coord
        , m_materiau);
    SCIHOOK_TRIGGER_INITMAT_BEFORE
    this->initMat(vars, dim);
    SCIHOOK_TRIGGER_INITMAT_AFTER
  }

  /*!
   \dot
     digraph initVarGraph
     {
       compound="true";
       edge [arrowsize="0.5", fontsize="8"];
       node [shape="box", fontname="Arial", fontsize="10"];
       {
         rank=same;
         initVar [style="rounded, filled", fillcolor="gray"];
         inVars [shape="record", label="cell_coord | velocity"];
         inVars -> initVar;
         outVars [shape="record", label="pseudo_viscosity | density | pressure | internal_energy | fracvol | mass_fraction | velocity_n | velocity"];
         initVar -> outVars;
       }

     }
   \enddot
   Cette méthode construit les variables et appelle OtherService::initVar.
  */
  void initVar(const Integer dim) override
  {
    OtherInitVarVars vars(m_cell_coord
        , m_pseudo_viscosity
        , m_density
        , m_pressure
        , m_internal_energy
        , m_fracvol
        , m_mass_fraction
        , m_velocity_n
        , m_velocity);
    SCIHOOK_TRIGGER_INITVAR_BEFORE
    this->initVar(vars, dim);
    SCIHOOK_TRIGGER_INITVAR_AFTER
  }


 public:  // ***** METHODES ABSTRAITES
  virtual void initMatMono(OtherInitMatMonoVars& vars, const Integer dim) = 0;
  virtual void initVarMono(OtherInitVarMonoVars& vars, const Integer dim) = 0;
  virtual void initMat(OtherInitMatVars& vars, const Integer dim) = 0;
  virtual void initVar(OtherInitVarVars& vars, const Integer dim) = 0;

 protected:  // ***** ATTRIBUTS
  IMeshMaterialMng* m_mesh_material_mng;
};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace Cas_testOTHER

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // CAS_TEST_OTHER___OTHERSERVICEBASE_H
