#ifndef EOS_PERFECTGAS___PERFECTGASSERVICEBASE_H
#define EOS_PERFECTGAS___PERFECTGASSERVICEBASE_H

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
#include "eos/perfectgas/__PerfectGasServiceVars.h"
#include "eos/perfectgas/__PerfectGasServiceViews.h"
#include "eos/perfectgas/PerfectGas_axl.h"
#include "eos/perfectgas/__PerfectGasServiceSciHookMacros.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

using namespace Arcane;
using namespace Arcane::Materials;
namespace EosPerfectgas {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

/*!
 * \brief Service PerfectGas : classe de base. 
 * 
 */
template<class T>
class PerfectGasServiceBase
: public ArcanePerfectGasObject
{
 SCIHOOK_DECLARE_EOS_PERFECTGAS_PERFECTGAS_EVENTS

 public:  // ***** CONSTRUCTEUR & DESTRUCTEUR
  explicit PerfectGasServiceBase(const ServiceBuildInfo& bi)
  : ArcanePerfectGasObject(bi)
  , m_mesh_material_mng(IMeshMaterialMng::getReference(bi.mesh()))
  , m_acc_env(SingletonIAccEnv::accEnv(subDomain()))
  {
    SCIHOOK_INITIALIZE_EOS_PERFECTGAS_PERFECTGAS_EVENTS
  }

  virtual ~PerfectGasServiceBase()
  {
  }

 public:  // ***** ACCESSEURS
  Real getAdiabaticCst() { return options()->getAdiabaticCst(); }
  Real getLimitTension() { return options()->getLimitTension(); }
  bool hasLimitTension() const { return options()->hasLimitTension(); }
  const String getImplName() const { return "PerfectGasService"; }
  IMeshMaterialMng* getMeshMaterialMng() const { return m_mesh_material_mng; }
  IAccEnv* getAccEnv() const { return m_acc_env; }

 public:  // ***** METHODES CONCRETES
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
   Cette méthode construit les variables et appelle PerfectGasService::initEOS.
  */
  void initEOS(::Arcane::Materials::IMeshEnvironment* env) override
  {
    PerfectGasInitEOSVars vars(m_pressure
        , m_density
        , m_internal_energy
        , m_sound_speed);
    SCIHOOK_TRIGGER_EOS_PERFECTGAS_PERFECTGAS_INITEOS_BEFORE
    this->initEOS(vars, env);
    SCIHOOK_TRIGGER_EOS_PERFECTGAS_PERFECTGAS_INITEOS_AFTER
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
         inVars [shape="record", label="density | internal_energy | adiabatic_cst | pressure"];
         inVars -> applyEOS;
         outVars [shape="record", label="pressure | sound_speed | dpde"];
         applyEOS -> outVars;
       }

     }
   \enddot
   Cette méthode construit les variables et appelle PerfectGasService::applyEOS.
  */
  void applyEOS(const EnvCellVectorView items, ::Arcane::Materials::IMeshEnvironment* env) override
  {
    auto queue = getAccEnv()->newQueue();
    auto command = makeCommand(queue);
    PerfectGasApplyEOSViews acc_context(ax::viewIn(command, m_density),
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
    SCIHOOK_TRIGGER_EOS_PERFECTGAS_PERFECTGAS_APPLYEOS_BEFORE
    command << RUNCOMMAND_MAT_ENUMERATE(EnvCell, iid, items) {
      acc_context.apply(iid);
    };
    SCIHOOK_TRIGGER_EOS_PERFECTGAS_PERFECTGAS_APPLYEOS_AFTER
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
   Cette méthode construit les variables et appelle PerfectGasService::applyOneCellEOS.
  */
  void applyOneCellEOS(const ::Arcane::Materials::IMeshEnvironment* env, const EnvCell ev) override
  {
    PerfectGasApplyOneCellEOSVars vars(m_density
        , m_internal_energy
        , m_pressure
        , m_sound_speed
        , m_dpde);
    SCIHOOK_TRIGGER_EOS_PERFECTGAS_PERFECTGAS_APPLYONECELLEOS_BEFORE
    this->applyOneCellEOS(vars, env, ev);
    SCIHOOK_TRIGGER_EOS_PERFECTGAS_PERFECTGAS_APPLYONECELLEOS_AFTER
  }


 public:  // ***** METHODES ABSTRAITES
  virtual void initEOS(PerfectGasInitEOSVars& vars, ::Arcane::Materials::IMeshEnvironment* env) = 0;
  virtual void applyOneCellEOS(PerfectGasApplyOneCellEOSVars& vars, const ::Arcane::Materials::IMeshEnvironment* env, const EnvCell ev) = 0;

 protected:  // ***** ATTRIBUTS
  IMeshMaterialMng* m_mesh_material_mng;
  IAccEnv* m_acc_env;
};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace EosPerfectgas

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // EOS_PERFECTGAS___PERFECTGASSERVICEBASE_H
