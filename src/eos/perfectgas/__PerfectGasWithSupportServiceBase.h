#ifndef EOS_PERFECTGAS___PERFECTGASWITHSUPPORTSERVICEBASE_H
#define EOS_PERFECTGAS___PERFECTGASWITHSUPPORTSERVICEBASE_H

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
#include "arcane/materials/MatConcurrency.h"
#include "eos/__IEquationOfState.h"
#include "eos/perfectgas/__PerfectGasWithSupportServiceVars.h"
#include "eos/perfectgas/PerfectgasTypeDeclarations.h"
#include "eos/perfectgas/PerfectGasWithSupport_axl.h"
#include "eos/perfectgas/__PerfectGasWithSupportServiceSciHookMacros.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

using namespace Arcane;
using namespace Arcane::Materials;
namespace EosPerfectgas {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

/*!
 * \brief Service PerfectGasWithSupport : classe de base. 
 * 
 */
template<class T>
class PerfectGasWithSupportServiceBase
: public ArcanePerfectGasWithSupportObject
{
 SCIHOOK_DECLARE_EOS_PERFECTGAS_PERFECTGASWITHSUPPORT_EVENTS

 public:  // ***** CONSTRUCTEUR & DESTRUCTEUR
  explicit PerfectGasWithSupportServiceBase(const ServiceBuildInfo& bi)
  : ArcanePerfectGasWithSupportObject(bi)
  , m_mesh_material_mng(IMeshMaterialMng::getReference(bi.mesh()))
  {
    SCIHOOK_INITIALIZE_EOS_PERFECTGAS_PERFECTGASWITHSUPPORT_EVENTS
  }

  virtual ~PerfectGasWithSupportServiceBase()
  {
  }

 public:  // ***** ACCESSEURS
  Real getAdiabaticCst() { return options()->getAdiabaticCst(); }
  Real getLimitTension() { return options()->getLimitTension(); }
  bool hasLimitTension() const { return options()->hasLimitTension(); }
  const String getImplName() const { return "PerfectGasWithSupportService"; }
  IMeshMaterialMng* getMeshMaterialMng() const { return m_mesh_material_mng; }

 public:  // ***** METHODES CONCRETES
  /*!
   \dot
     digraph applyEOSWithSupportGraph
     {
       compound="true";
       edge [arrowsize="0.5", fontsize="8"];
       node [shape="box", fontname="Arial", fontsize="10"];
       {
         rank=same;
         applyEOSWithSupport [style="rounded, filled", fillcolor="gray"];
         inVars [shape="record", label="density | internal_energy | adiabatic_cst | pressure"];
         inVars -> applyEOSWithSupport;
         outVars [shape="record", label="pressure | sound_speed | dpde"];
         applyEOSWithSupport -> outVars;
       }

     }
   \enddot
   Cette méthode construit les variables et appelle PerfectGasWithSupportService::applyEOSWithSupport.
  */
  void applyEOSWithSupport(const EnvCellVectorView items)
  {
    PerfectGasWithSupportApplyEOSWithSupportVars vars(m_density
        , m_internal_energy
        , getAdiabaticCst()
        , m_pressure
        , m_sound_speed
        , m_dpde);
    SCIHOOK_TRIGGER_EOS_PERFECTGAS_PERFECTGASWITHSUPPORT_APPLYEOSWITHSUPPORT_BEFORE
    T* t = static_cast<T*>(this);
    arcaneParallelForeach(items, [&](EnvCellVectorView sub_items)
    {
      ENUMERATE_ENVCELL (iitem, sub_items) {
        const EnvCell item = *iitem;
        t->applyEOSWithSupport(item, vars);
      }
    });
    SCIHOOK_TRIGGER_EOS_PERFECTGAS_PERFECTGASWITHSUPPORT_APPLYEOSWITHSUPPORT_AFTER
  }

  /*!
   \dot
     digraph initEOSGraph
     {
       compound="true";
       edge [arrowsize="0.5", fontsize="8"];
       node [shape="box", fontname="Arial", fontsize="10"];
       {
         rank=same;
         initEOS [style="rounded, filled", fillcolor="gray"];
         inVars [shape="record", label="pressure | density"];
         inVars -> initEOS;
         outVars [shape="record", label="internal_energy | sound_speed"];
         initEOS -> outVars;
       }

     }
   \enddot
   Cette méthode construit les variables et appelle PerfectGasWithSupportService::initEOS.
  */
  void initEOS(::Arcane::Materials::IMeshEnvironment* env) override
  {
    PerfectGasWithSupportInitEOSVars vars(m_pressure
        , m_density
        , m_internal_energy
        , m_sound_speed);
    SCIHOOK_TRIGGER_EOS_PERFECTGAS_PERFECTGASWITHSUPPORT_INITEOS_BEFORE
    this->initEOS(vars, env);
    SCIHOOK_TRIGGER_EOS_PERFECTGAS_PERFECTGASWITHSUPPORT_INITEOS_AFTER
  }

  /*!
   \dot
     digraph applyEOSGraph
     {
       compound="true";
       edge [arrowsize="0.5", fontsize="8"];
       node [shape="box", fontname="Arial", fontsize="10"];
       {
         rank=same;
         applyEOS [style="rounded, filled", fillcolor="gray"];
       }

       subgraph clusterCalledFuncs
       {
         center="true";
         color="navy";
         PerfectGasWithSupportServiceBase_applyEOSWithSupport [label="applyEOSWithSupport", color="navy", fontcolor="navy", style="rounded", URL="\ref EosPerfectgas::PerfectGasWithSupportServiceBase::applyEOSWithSupport"];
       }
       applyEOS -> PerfectGasWithSupportServiceBase_applyEOSWithSupport [lhead="clusterCalledFuncs", style="dashed", label=" call"];
     }
   \enddot
   Cette méthode construit les variables et appelle PerfectGasWithSupportService::applyEOS.
  */
  void applyEOS(::Arcane::Materials::IMeshEnvironment* env) override
  {
    PerfectGasWithSupportApplyEOSVars vars;
    SCIHOOK_TRIGGER_EOS_PERFECTGAS_PERFECTGASWITHSUPPORT_APPLYEOS_BEFORE
    this->applyEOS(vars, env);
    SCIHOOK_TRIGGER_EOS_PERFECTGAS_PERFECTGASWITHSUPPORT_APPLYEOS_AFTER
  }

  /*!
   \dot
     digraph applyOneCellEOSGraph
     {
       compound="true";
       edge [arrowsize="0.5", fontsize="8"];
       node [shape="box", fontname="Arial", fontsize="10"];
       {
         rank=same;
         applyOneCellEOS [style="rounded, filled", fillcolor="gray"];
         inVars [shape="record", label="density | internal_energy"];
         inVars -> applyOneCellEOS;
         outVars [shape="record", label="pressure | sound_speed | dpde"];
         applyOneCellEOS -> outVars;
       }

     }
   \enddot
   Cette méthode construit les variables et appelle PerfectGasWithSupportService::applyOneCellEOS.
  */
  void applyOneCellEOS(const ::Arcane::Materials::IMeshEnvironment* env, const EnvCell ev) override
  {
    PerfectGasWithSupportApplyOneCellEOSVars vars(m_density
        , m_internal_energy
        , m_pressure
        , m_sound_speed
        , m_dpde);
    SCIHOOK_TRIGGER_EOS_PERFECTGAS_PERFECTGASWITHSUPPORT_APPLYONECELLEOS_BEFORE
    this->applyOneCellEOS(vars, env, ev);
    SCIHOOK_TRIGGER_EOS_PERFECTGAS_PERFECTGASWITHSUPPORT_APPLYONECELLEOS_AFTER
  }


 public:  // ***** METHODES ABSTRAITES
  virtual void applyEOSWithSupport(const EnvCell envcell, PerfectGasWithSupportApplyEOSWithSupportVars& vars) = 0;
  virtual void initEOS(PerfectGasWithSupportInitEOSVars& vars, ::Arcane::Materials::IMeshEnvironment* env) = 0;
  virtual void applyEOS(PerfectGasWithSupportApplyEOSVars& vars, ::Arcane::Materials::IMeshEnvironment* env) = 0;
  virtual void applyOneCellEOS(PerfectGasWithSupportApplyOneCellEOSVars& vars, const ::Arcane::Materials::IMeshEnvironment* env, const EnvCell ev) = 0;

 protected:  // ***** ATTRIBUTS
  IMeshMaterialMng* m_mesh_material_mng;
};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace EosPerfectgas

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // EOS_PERFECTGAS___PERFECTGASWITHSUPPORTSERVICEBASE_H
