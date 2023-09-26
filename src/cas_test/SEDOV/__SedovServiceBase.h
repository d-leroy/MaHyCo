#ifndef CAS_TEST_SEDOV___SEDOVSERVICEBASE_H
#define CAS_TEST_SEDOV___SEDOVSERVICEBASE_H

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
#include "cas_test/SEDOV/__SedovServiceVars.h"
#include "cas_test/SEDOV/Sedov_axl.h"
#include "cas_test/SEDOV/__SedovServiceSciHookMacros.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

using namespace Arcane;
using namespace Arcane::Materials;
namespace Cas_testSEDOV {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

/*!
 * \brief Service Sedov : classe de base. 
 * 
 */
template<class T>
class SedovServiceBase
: public ArcaneSedovObject
{
 SCIHOOK_DECLARE_CAS_TEST_SEDOV_SEDOV_EVENTS

 public:  // ***** CONSTRUCTEUR & DESTRUCTEUR
  explicit SedovServiceBase(const ServiceBuildInfo& bi)
  : ArcaneSedovObject(bi)
  , m_mesh_material_mng(IMeshMaterialMng::getReference(bi.mesh()))
  {
    SCIHOOK_INITIALIZE_CAS_TEST_SEDOV_SEDOV_EVENTS
  }

  virtual ~SedovServiceBase()
  {
  }

 public:  // ***** ACCESSEURS
  ::Cas_test::Test getCasTest() { return options()->getCasTest(); }
  bool getReverseOption() { return options()->getReverseOption(); }
  bool hasReverseOption() const { return options()->hasReverseOption(); }
  Real getParameter() { return options()->getParameter(); }
  const String getImplName() const { return "SedovService"; }
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
   Cette méthode construit les variables et appelle SedovService::initMatMono.
  */
  void initMatMono(const Integer dim) override
  {
    SedovInitMatMonoVars vars(m_materiau);
    SCIHOOK_TRIGGER_CAS_TEST_SEDOV_SEDOV_INITMATMONO_BEFORE
    this->initMatMono(vars, dim);
    SCIHOOK_TRIGGER_CAS_TEST_SEDOV_SEDOV_INITMATMONO_AFTER
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
         inVars [shape="record", label="node_coord | cell_volume | internal_energy"];
         inVars -> initVarMono;
         outVars [shape="record", label="density | pressure | fracvol | mass_fraction | velocity | internal_energy"];
         initVarMono -> outVars;
       }

     }
   \enddot
   Cette méthode construit les variables et appelle SedovService::initVarMono.
  */
  void initVarMono(const Integer dim) override
  {
    SedovInitVarMonoVars vars(m_node_coord
        , m_cell_volume
        , m_density
        , m_pressure
        , m_fracvol
        , m_mass_fraction
        , m_velocity
        , m_internal_energy);
    SCIHOOK_TRIGGER_CAS_TEST_SEDOV_SEDOV_INITVARMONO_BEFORE
    this->initVarMono(vars, dim);
    SCIHOOK_TRIGGER_CAS_TEST_SEDOV_SEDOV_INITVARMONO_AFTER
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
   Cette méthode construit les variables et appelle SedovService::initMat.
  */
  void initMat(const Integer dim) override
  {
    SedovInitMatVars vars(m_node_coord
        , m_materiau);
    SCIHOOK_TRIGGER_CAS_TEST_SEDOV_SEDOV_INITMAT_BEFORE
    this->initMat(vars, dim);
    SCIHOOK_TRIGGER_CAS_TEST_SEDOV_SEDOV_INITMAT_AFTER
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
         inVars [shape="record", label="node_coord | cell_volume | internal_energy"];
         inVars -> initVar;
         outVars [shape="record", label="density | pressure | fracvol | mass_fraction | velocity | internal_energy"];
         initVar -> outVars;
       }

     }
   \enddot
   Cette méthode construit les variables et appelle SedovService::initVar.
  */
  void initVar(const Integer dim) override
  {
    SedovInitVarVars vars(m_node_coord
        , m_cell_volume
        , m_density
        , m_pressure
        , m_fracvol
        , m_mass_fraction
        , m_velocity
        , m_internal_energy);
    SCIHOOK_TRIGGER_CAS_TEST_SEDOV_SEDOV_INITVAR_BEFORE
    this->initVar(vars, dim);
    SCIHOOK_TRIGGER_CAS_TEST_SEDOV_SEDOV_INITVAR_AFTER
  }


 public:  // ***** METHODES ABSTRAITES
  virtual void initMatMono(SedovInitMatMonoVars& vars, const Integer dim) = 0;
  virtual void initVarMono(SedovInitVarMonoVars& vars, const Integer dim) = 0;
  virtual void initMat(SedovInitMatVars& vars, const Integer dim) = 0;
  virtual void initVar(SedovInitVarVars& vars, const Integer dim) = 0;

 protected:  // ***** ATTRIBUTS
  IMeshMaterialMng* m_mesh_material_mng;
};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace Cas_testSEDOV

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // CAS_TEST_SEDOV___SEDOVSERVICEBASE_H
