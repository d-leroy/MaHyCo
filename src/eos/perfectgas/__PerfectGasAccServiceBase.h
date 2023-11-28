#ifndef EOS_PERFECTGAS___PERFECTGASACCSERVICEBASE_H
#define EOS_PERFECTGAS___PERFECTGASACCSERVICEBASE_H

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
#include "arcane/accelerator/RunCommandMaterialEnumerate.h"
#include "accenv/IAccEnv.h"
#include "accenv/SingletonIAccEnv.h"
#include "eos/__IEquationOfState.h"
#include "eos/perfectgas/__PerfectGasAccServiceVars.h"
#include "eos/perfectgas/__PerfectGasAccServiceViews.h"
#include "arcane/materials/IMeshEnvironment.h"
#include "eos/perfectgas/PerfectGasAcc_axl.h"
#include "eos/perfectgas/__PerfectGasAccServiceSciHookMacros.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

using namespace Arcane;
using namespace Arcane::Materials;
namespace EosPerfectgas {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

/*!
 * \brief Service PerfectGasAcc : classe de base. 
 * 
 */
template<class T>
class PerfectGasAccServiceBase
: public ArcanePerfectGasAccObject
{
 SCIHOOK_DECLARE_EOS_PERFECTGAS_PERFECTGASACC_EVENTS

 public:  // ***** CONSTRUCTEUR & DESTRUCTEUR
  explicit PerfectGasAccServiceBase(const ServiceBuildInfo& bi)
  : ArcanePerfectGasAccObject(bi)
  , m_mesh_material_mng(IMeshMaterialMng::getReference(bi.mesh()))
  , m_acc_env(SingletonIAccEnv::accEnv(subDomain()))
  {
    SCIHOOK_INITIALIZE_EOS_PERFECTGAS_PERFECTGASACC_EVENTS
  }

  virtual ~PerfectGasAccServiceBase()
  {
  }

 public:  // ***** ACCESSEURS
  Real getAdiabaticCst() { return options()->getAdiabaticCst(); }
  Real getLimitTension() { return options()->getLimitTension(); }
  bool hasLimitTension() const { return options()->hasLimitTension(); }
  const String getImplName() const { return "PerfectGasAccService"; }
  IMeshMaterialMng* getMeshMaterialMng() const { return m_mesh_material_mng; }
  IAccEnv* getAccEnv() const { return m_acc_env; }

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
   Cette méthode construit les variables et appelle PerfectGasAccService::applyEOSWithSupport.
  */
  void applyEOSWithSupport(const EnvCellVectorView items, ::Arcane::Materials::IMeshEnvironment* env)
  {
    auto queue = getAccEnv()->newQueue();
    auto command = makeCommand(queue);
    PerfectGasAccApplyEOSWithSupportViews acc_context(ax::viewIn(command, m_density),
        ax::viewIn(command, m_density.globalVariable()),
        ax::viewIn(command, m_internal_energy),
        ax::viewIn(command, m_internal_energy.globalVariable()),
        getAdiabaticCst(),
        ax::viewInOut(command, m_pressure),
        ax::viewInOut(command, m_pressure.globalVariable()),
        ax::viewOut(command, m_sound_speed),
        ax::viewOut(command, m_sound_speed.globalVariable()),
        ax::viewOut(command, m_dpde),
        ax::viewOut(command, m_dpde.globalVariable()));
    SCIHOOK_TRIGGER_EOS_PERFECTGAS_PERFECTGASACC_APPLYEOSWITHSUPPORT_BEFORE
    command << RUNCOMMAND_MAT_ENUMERATE(EnvCell, iid, items) {
      acc_context.apply(iid);
    };
    SCIHOOK_TRIGGER_EOS_PERFECTGAS_PERFECTGASACC_APPLYEOSWITHSUPPORT_AFTER
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
   Cette méthode construit les variables et appelle PerfectGasAccService::initEOS.
  */
  void initEOS(::Arcane::Materials::IMeshEnvironment* env) override
  {
    PerfectGasAccInitEOSVars vars(m_pressure
        , m_density
        , m_internal_energy
        , m_sound_speed);
    SCIHOOK_TRIGGER_EOS_PERFECTGAS_PERFECTGASACC_INITEOS_BEFORE
    this->initEOS(vars, env);
    SCIHOOK_TRIGGER_EOS_PERFECTGAS_PERFECTGASACC_INITEOS_AFTER
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
         PerfectGasAccServiceBase_applyEOSWithSupport [label="applyEOSWithSupport", color="navy", fontcolor="navy", style="rounded", URL="\ref EosPerfectgas::PerfectGasAccServiceBase::applyEOSWithSupport"];
       }
       applyEOS -> PerfectGasAccServiceBase_applyEOSWithSupport [lhead="clusterCalledFuncs", style="dashed", label=" call"];
     }
   \enddot
   Cette méthode construit les variables et appelle PerfectGasAccService::applyEOS.
  */
  void applyEOS(::Arcane::Materials::IMeshEnvironment* env) override
  {
    PerfectGasAccApplyEOSVars vars;
    SCIHOOK_TRIGGER_EOS_PERFECTGAS_PERFECTGASACC_APPLYEOS_BEFORE
    this->applyEOS(vars, env);
    SCIHOOK_TRIGGER_EOS_PERFECTGAS_PERFECTGASACC_APPLYEOS_AFTER
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
   Cette méthode construit les variables et appelle PerfectGasAccService::applyOneCellEOS.
  */
  void applyOneCellEOS(const ::Arcane::Materials::IMeshEnvironment* env, const EnvCell ev) override
  {
    PerfectGasAccApplyOneCellEOSVars vars(m_density
        , m_internal_energy
        , m_pressure
        , m_sound_speed
        , m_dpde);
    SCIHOOK_TRIGGER_EOS_PERFECTGAS_PERFECTGASACC_APPLYONECELLEOS_BEFORE
    this->applyOneCellEOS(vars, env, ev);
    SCIHOOK_TRIGGER_EOS_PERFECTGAS_PERFECTGASACC_APPLYONECELLEOS_AFTER
  }


 public:  // ***** METHODES ABSTRAITES
  virtual void initEOS(PerfectGasAccInitEOSVars& vars, ::Arcane::Materials::IMeshEnvironment* env) = 0;
  virtual void applyEOS(PerfectGasAccApplyEOSVars& vars, ::Arcane::Materials::IMeshEnvironment* env) = 0;
  virtual void applyOneCellEOS(PerfectGasAccApplyOneCellEOSVars& vars, const ::Arcane::Materials::IMeshEnvironment* env, const EnvCell ev) = 0;

 protected:  // ***** ATTRIBUTS
  IMeshMaterialMng* m_mesh_material_mng;
  IAccEnv* m_acc_env;
};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace EosPerfectgas

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // EOS_PERFECTGAS___PERFECTGASACCSERVICEBASE_H
