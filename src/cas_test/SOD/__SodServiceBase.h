#ifndef CAS_TEST_SOD___SODSERVICEBASE_H
#define CAS_TEST_SOD___SODSERVICEBASE_H

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
#include "cas_test/SOD/__SodServiceVars.h"
#include "cas_test/SOD/Sod_axl.h"
#include "cas_test/SOD/__SodServiceSciHookMacros.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

using namespace Arcane;
using namespace Arcane::Materials;
namespace Cas_testSOD {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

/*!
 * \brief Service Sod : classe de base. 
 * 
 */
template<class T>
class SodServiceBase
: public ArcaneSodObject
{
 SCIHOOK_DECLARE_CAS_TEST_SOD_SOD_EVENTS

 public:  // ***** CONSTRUCTEUR & DESTRUCTEUR
  explicit SodServiceBase(const ServiceBuildInfo& bi)
  : ArcaneSodObject(bi)
  , m_mesh_material_mng(IMeshMaterialMng::getReference(bi.mesh()))
  {
    SCIHOOK_INITIALIZE_CAS_TEST_SOD_SOD_EVENTS
  }

  virtual ~SodServiceBase()
  {
  }

 public:  // ***** ACCESSEURS
  ::Cas_test::Test getCasTest() { return options()->getCasTest(); }
  bool getReverseOption() { return options()->getReverseOption(); }
  bool hasReverseOption() const { return options()->hasReverseOption(); }
  Real getParameter() { return options()->getParameter(); }
  const String getImplName() const { return "SodService"; }
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
   Cette méthode construit les variables et appelle SodService::initMatMono.
  */
  void initMatMono(const Integer dim) override
  {
    SodInitMatMonoVars vars(m_materiau);
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
         inVars [shape="record", label="cell_coord | velocity"];
         inVars -> initVarMono;
         outVars [shape="record", label="density | pressure | fracvol | mass_fraction | velocity"];
         initVarMono -> outVars;
       }

     }
   \enddot
   Cette méthode construit les variables et appelle SodService::initVarMono.
  */
  void initVarMono(const Integer dim) override
  {
    SodInitVarMonoVars vars(m_cell_coord
        , m_density
        , m_pressure
        , m_fracvol
        , m_mass_fraction
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
         inVars [shape="record", label="cell_coord"];
         inVars -> initMat;
         outVars [shape="record", label="materiau"];
         initMat -> outVars;
       }

     }
   \enddot
   Cette méthode construit les variables et appelle SodService::initMat.
  */
  void initMat(const Integer dim) override
  {
    SodInitMatVars vars(m_cell_coord
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
         outVars [shape="record", label="density | pressure | fracvol | mass_fraction | velocity"];
         initVar -> outVars;
       }

     }
   \enddot
   Cette méthode construit les variables et appelle SodService::initVar.
  */
  void initVar(const Integer dim) override
  {
    SodInitVarVars vars(m_cell_coord
        , m_density
        , m_pressure
        , m_fracvol
        , m_mass_fraction
        , m_velocity);
    SCIHOOK_TRIGGER_INITVAR_BEFORE
    this->initVar(vars, dim);
    SCIHOOK_TRIGGER_INITVAR_AFTER
  }


 public:  // ***** METHODES ABSTRAITES
  virtual void initMatMono(SodInitMatMonoVars& vars, const Integer dim) = 0;
  virtual void initVarMono(SodInitVarMonoVars& vars, const Integer dim) = 0;
  virtual void initMat(SodInitMatVars& vars, const Integer dim) = 0;
  virtual void initVar(SodInitVarVars& vars, const Integer dim) = 0;

 protected:  // ***** ATTRIBUTS
  IMeshMaterialMng* m_mesh_material_mng;
};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace Cas_testSOD

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // CAS_TEST_SOD___SODSERVICEBASE_H
