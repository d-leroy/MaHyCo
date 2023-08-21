#ifndef CAS_TEST_RIDER___RIDERSERVICEBASE_H
#define CAS_TEST_RIDER___RIDERSERVICEBASE_H

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
#include "cas_test/RIDER/__RiderServiceVars.h"
#include "cas_test/RIDER/Rider_axl.h"
#include "cas_test/RIDER/__RiderServiceSciHookMacros.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

using namespace Arcane;
using namespace Arcane::Materials;
namespace Cas_testRIDER {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

/*!
 * \brief Service Rider : classe de base. 
 * 
 */
template<class T>
class RiderServiceBase
: public ArcaneRiderObject
{
 SCIHOOK_DECLARE_CAS_TEST_RIDER_RIDER_EVENTS

 public:  // ***** CONSTRUCTEUR & DESTRUCTEUR
  explicit RiderServiceBase(const ServiceBuildInfo& bi)
  : ArcaneRiderObject(bi)
  , m_mesh_material_mng(IMeshMaterialMng::getReference(bi.mesh()))
  {
    SCIHOOK_INITIALIZE_CAS_TEST_RIDER_RIDER_EVENTS
  }

  virtual ~RiderServiceBase()
  {
  }

 public:  // ***** ACCESSEURS
  ::Cas_test::Test getCasTest() { return options()->getCasTest(); }
  bool getReverseOption() { return options()->getReverseOption(); }
  bool hasReverseOption() const { return options()->hasReverseOption(); }
  Real getParameter() { return options()->getParameter(); }
  const String getImplName() const { return "RiderService"; }
  IMeshMaterialMng* getMeshMaterialMng() const { return m_mesh_material_mng; }

 public:  // ***** METHODES CONCRETES
  /*!
   \dot
     digraph initMatMonoGraph
     {
       compound="true";
       edge [arrowsize="0.5", fontsize="8"];
       node [shape="box", fontname="Arial", fontsize="10"];
       {
         rank=same;
         initMatMono [style="rounded, filled", fillcolor="gray"];
         outVars [shape="record", label="materiau"];
         initMatMono -> outVars;
       }

     }
   \enddot
   Cette méthode construit les variables et appelle RiderService::initMatMono.
  */
  void initMatMono(const Integer dim) override
  {
    RiderInitMatMonoVars vars(m_materiau);
    SCIHOOK_TRIGGER_INITMATMONO_BEFORE
    this->initMatMono(vars, dim);
    SCIHOOK_TRIGGER_INITMATMONO_AFTER
  }

  /*!
   \dot
     digraph initVarMonoGraph
     {
       compound="true";
       edge [arrowsize="0.5", fontsize="8"];
       node [shape="box", fontname="Arial", fontsize="10"];
       {
         rank=same;
         initVarMono [style="rounded, filled", fillcolor="gray"];
         inVars [shape="record", label="node_coord | velocity"];
         inVars -> initVarMono;
         outVars [shape="record", label="pseudo_viscosity | density | pressure | fracvol | mass_fraction | velocity_n | velocity"];
         initVarMono -> outVars;
       }

     }
   \enddot
   Cette méthode construit les variables et appelle RiderService::initVarMono.
  */
  void initVarMono(const Integer dim) override
  {
    RiderInitVarMonoVars vars(m_node_coord
        , m_pseudo_viscosity
        , m_density
        , m_pressure
        , m_fracvol
        , m_mass_fraction
        , m_velocity_n
        , m_velocity);
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
         inVars [shape="record", label="node_coord"];
         inVars -> initMat;
         outVars [shape="record", label="materiau"];
         initMat -> outVars;
       }

     }
   \enddot
   Cette méthode construit les variables et appelle RiderService::initMat.
  */
  void initMat(const Integer dim) override
  {
    RiderInitMatVars vars(m_node_coord
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
         inVars [shape="record", label="node_coord | velocity"];
         inVars -> initVar;
         outVars [shape="record", label="pseudo_viscosity | density | pressure | fracvol | mass_fraction | velocity_n | velocity"];
         initVar -> outVars;
       }

     }
   \enddot
   Cette méthode construit les variables et appelle RiderService::initVar.
  */
  void initVar(const Integer dim) override
  {
    RiderInitVarVars vars(m_node_coord
        , m_pseudo_viscosity
        , m_density
        , m_pressure
        , m_fracvol
        , m_mass_fraction
        , m_velocity_n
        , m_velocity);
    SCIHOOK_TRIGGER_INITVAR_BEFORE
    this->initVar(vars, dim);
    SCIHOOK_TRIGGER_INITVAR_AFTER
  }


 public:  // ***** METHODES ABSTRAITES
  virtual void initMatMono(RiderInitMatMonoVars& vars, const Integer dim) = 0;
  virtual void initVarMono(RiderInitVarMonoVars& vars, const Integer dim) = 0;
  virtual void initMat(RiderInitMatVars& vars, const Integer dim) = 0;
  virtual void initVar(RiderInitVarVars& vars, const Integer dim) = 0;

 protected:  // ***** ATTRIBUTS
  IMeshMaterialMng* m_mesh_material_mng;
};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace Cas_testRIDER

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // CAS_TEST_RIDER___RIDERSERVICEBASE_H
