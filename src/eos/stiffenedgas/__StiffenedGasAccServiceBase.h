#ifndef EOS_STIFFENEDGAS___STIFFENEDGASACCSERVICEBASE_H
#define EOS_STIFFENEDGAS___STIFFENEDGASACCSERVICEBASE_H

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
#include "eos/stiffenedgas/__StiffenedGasAccServiceVars.h"
#include "eos/stiffenedgas/__StiffenedGasAccServiceViews.h"
#include "eos/stiffenedgas/StiffenedgasTypeDeclarations.h"
#include "eos/stiffenedgas/StiffenedGasAcc_axl.h"
#include "eos/stiffenedgas/__StiffenedGasAccServiceSciHookMacros.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

using namespace Arcane;
using namespace Arcane::Materials;
namespace EosStiffenedgas {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

/*!
 * \brief Service StiffenedGasAcc : classe de base. 
 * 
 */
template<class T>
class StiffenedGasAccServiceBase
: public ArcaneStiffenedGasAccObject
{
 SCIHOOK_DECLARE_EOS_STIFFENEDGAS_STIFFENEDGASACC_EVENTS

 public:  // ***** CONSTRUCTEUR & DESTRUCTEUR
  explicit StiffenedGasAccServiceBase(const ServiceBuildInfo& bi)
  : ArcaneStiffenedGasAccObject(bi)
  , m_mesh_material_mng(IMeshMaterialMng::getReference(bi.mesh()))
  , m_acc_env(SingletonIAccEnv::accEnv(subDomain()))
  {
    SCIHOOK_INITIALIZE_EOS_STIFFENEDGAS_STIFFENEDGASACC_EVENTS
  }

  virtual ~StiffenedGasAccServiceBase()
  {
  }

 public:  // ***** ACCESSEURS
  Real getAdiabaticCst() { return options()->getAdiabaticCst(); }
  Real getTensionLimitCst() { return options()->getTensionLimitCst(); }
  bool hasTensionLimitCst() const { return options()->hasTensionLimitCst(); }
  const String getImplName() const { return "StiffenedGasAccService"; }
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
         inVars [shape="record", label="internal_energy | density | tension_limit_cst | adiabatic_cst"];
         inVars -> applyEOSWithSupport;
         outVars [shape="record", label="pressure | sound_speed | dpde"];
         applyEOSWithSupport -> outVars;
       }

     }
   \enddot
   Cette méthode construit les variables et appelle StiffenedGasAccService::applyEOSWithSupport.
  */
  void applyEOSWithSupport(const EnvCellVectorView items)
  {
    auto queue = getAccEnv()->newQueue();
    auto command = makeCommand(queue);
    StiffenedGasAccApplyEOSWithSupportViews acc_context(ax::viewIn(command, m_internal_energy),
        ax::viewIn(command, m_density),
        getTensionLimitCst(),
        getAdiabaticCst(),
        ax::viewOut(command, m_pressure),
        ax::viewOut(command, m_sound_speed),
        ax::viewOut(command, m_dpde));
    SCIHOOK_TRIGGER_EOS_STIFFENEDGAS_STIFFENEDGASACC_APPLYEOSWITHSUPPORT_BEFORE
    command << RUNCOMMAND_MAT_ENUMERATE(EnvAndGlobalCell, evgi, items) {
      auto [mvi, cid] = evgi();
      acc_context.apply(mvi, cid);
    };
    SCIHOOK_TRIGGER_EOS_STIFFENEDGAS_STIFFENEDGASACC_APPLYEOSWITHSUPPORT_AFTER
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
   Cette méthode construit les variables et appelle StiffenedGasAccService::initEOS.
  */
  void initEOS(::Arcane::Materials::IMeshEnvironment* env) override
  {
    StiffenedGasAccInitEOSVars vars(m_pressure
        , m_density
        , m_internal_energy
        , m_sound_speed);
    SCIHOOK_TRIGGER_EOS_STIFFENEDGAS_STIFFENEDGASACC_INITEOS_BEFORE
    this->initEOS(vars, env);
    SCIHOOK_TRIGGER_EOS_STIFFENEDGAS_STIFFENEDGASACC_INITEOS_AFTER
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
         StiffenedGasAccServiceBase_applyEOSWithSupport [label="applyEOSWithSupport", color="navy", fontcolor="navy", style="rounded", URL="\ref EosStiffenedgas::StiffenedGasAccServiceBase::applyEOSWithSupport"];
       }
       applyEOS -> StiffenedGasAccServiceBase_applyEOSWithSupport [lhead="clusterCalledFuncs", style="dashed", label=" call"];
     }
   \enddot
   Cette méthode construit les variables et appelle StiffenedGasAccService::applyEOS.
  */
  void applyEOS(::Arcane::Materials::IMeshEnvironment* env) override
  {
    StiffenedGasAccApplyEOSVars vars;
    SCIHOOK_TRIGGER_EOS_STIFFENEDGAS_STIFFENEDGASACC_APPLYEOS_BEFORE
    this->applyEOS(vars, env);
    SCIHOOK_TRIGGER_EOS_STIFFENEDGAS_STIFFENEDGASACC_APPLYEOS_AFTER
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
         inVars [shape="record", label="internal_energy | density"];
         inVars -> applyOneCellEOS;
         outVars [shape="record", label="pressure | sound_speed | dpde"];
         applyOneCellEOS -> outVars;
       }

     }
   \enddot
   Cette méthode construit les variables et appelle StiffenedGasAccService::applyOneCellEOS.
  */
  void applyOneCellEOS(const ::Arcane::Materials::IMeshEnvironment* env, const EnvCell ev) override
  {
    StiffenedGasAccApplyOneCellEOSVars vars(m_internal_energy
        , m_density
        , m_pressure
        , m_sound_speed
        , m_dpde);
    SCIHOOK_TRIGGER_EOS_STIFFENEDGAS_STIFFENEDGASACC_APPLYONECELLEOS_BEFORE
    this->applyOneCellEOS(vars, env, ev);
    SCIHOOK_TRIGGER_EOS_STIFFENEDGAS_STIFFENEDGASACC_APPLYONECELLEOS_AFTER
  }


 public:  // ***** METHODES ABSTRAITES
  virtual void initEOS(StiffenedGasAccInitEOSVars& vars, ::Arcane::Materials::IMeshEnvironment* env) = 0;
  virtual void applyEOS(StiffenedGasAccApplyEOSVars& vars, ::Arcane::Materials::IMeshEnvironment* env) = 0;
  virtual void applyOneCellEOS(StiffenedGasAccApplyOneCellEOSVars& vars, const ::Arcane::Materials::IMeshEnvironment* env, const EnvCell ev) = 0;

 protected:  // ***** ATTRIBUTS
  IMeshMaterialMng* m_mesh_material_mng;
  IAccEnv* m_acc_env;
};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace EosStiffenedgas

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // EOS_STIFFENEDGAS___STIFFENEDGASACCSERVICEBASE_H
