#ifndef EOS_STIFFENEDGAS___STIFFENEDGASSERVICEBASE_H
#define EOS_STIFFENEDGAS___STIFFENEDGASSERVICEBASE_H

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
#include "eos/stiffenedgas/__StiffenedGasServiceVars.h"
#include "eos/stiffenedgas/__StiffenedGasServiceViews.h"
#include "eos/stiffenedgas/StiffenedGas_axl.h"
#include "eos/stiffenedgas/__StiffenedGasServiceSciHookMacros.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

using namespace Arcane;
using namespace Arcane::Materials;
namespace EosStiffenedgas {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

/*!
 * \brief Service StiffenedGas : classe de base. 
 * 
 */
template<class T>
class StiffenedGasServiceBase
: public ArcaneStiffenedGasObject
{
 SCIHOOK_DECLARE_EOS_STIFFENEDGAS_STIFFENEDGAS_EVENTS

 public:  // ***** CONSTRUCTEUR & DESTRUCTEUR
  explicit StiffenedGasServiceBase(const ServiceBuildInfo& bi)
  : ArcaneStiffenedGasObject(bi)
  , m_mesh_material_mng(IMeshMaterialMng::getReference(bi.mesh()))
  , m_acc_env(SingletonIAccEnv::accEnv(subDomain()))
  {
    SCIHOOK_INITIALIZE_EOS_STIFFENEDGAS_STIFFENEDGAS_EVENTS
  }

  virtual ~StiffenedGasServiceBase()
  {
  }

 public:  // ***** ACCESSEURS
  Real getAdiabaticCst() { return options()->getAdiabaticCst(); }
  Real getTensionLimitCst() { return options()->getTensionLimitCst(); }
  bool hasTensionLimitCst() const { return options()->hasTensionLimitCst(); }
  const String getImplName() const { return "StiffenedGasService"; }
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
   Cette méthode construit les variables et appelle StiffenedGasService::initEOS.
  */
  void initEOS(::Arcane::Materials::IMeshEnvironment* env) override
  {
    StiffenedGasInitEOSVars vars(m_pressure
        , m_density
        , m_internal_energy
        , m_sound_speed);
    SCIHOOK_TRIGGER_EOS_STIFFENEDGAS_STIFFENEDGAS_INITEOS_BEFORE
    this->initEOS(vars, env);
    SCIHOOK_TRIGGER_EOS_STIFFENEDGAS_STIFFENEDGAS_INITEOS_AFTER
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
         inVars [shape="record", label="internal_energy | density | tension_limit_cst | adiabatic_cst"];
         inVars -> applyEOS;
         outVars [shape="record", label="pressure | sound_speed | dpde"];
         applyEOS -> outVars;
       }

     }
   \enddot
   Cette méthode construit les variables et appelle StiffenedGasService::applyEOS.
  */
  void applyEOS(const EnvCellVectorView items, ::Arcane::Materials::IMeshEnvironment* env) override
  {
    auto queue = getAccEnv()->newQueue();
    auto command = makeCommand(queue);
    StiffenedGasApplyEOSViews acc_context(ax::viewIn(command, m_internal_energy),
        ax::viewIn(command, m_internal_energy.globalVariable()),
        ax::viewIn(command, m_density),
        ax::viewIn(command, m_density.globalVariable()),
        getTensionLimitCst(),
        getAdiabaticCst(),
        ax::viewOut(command, m_pressure),
        ax::viewOut(command, m_pressure.globalVariable()),
        ax::viewOut(command, m_sound_speed),
        ax::viewOut(command, m_sound_speed.globalVariable()),
        ax::viewOut(command, m_dpde),
        ax::viewOut(command, m_dpde.globalVariable()));
    SCIHOOK_TRIGGER_EOS_STIFFENEDGAS_STIFFENEDGAS_APPLYEOS_BEFORE
    command << RUNCOMMAND_MAT_ENUMERATE(EnvCell, iid, items) {
      acc_context.apply(iid);
    };
    SCIHOOK_TRIGGER_EOS_STIFFENEDGAS_STIFFENEDGAS_APPLYEOS_AFTER
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
   Cette méthode construit les variables et appelle StiffenedGasService::applyOneCellEOS.
  */
  void applyOneCellEOS(const ::Arcane::Materials::IMeshEnvironment* env, const EnvCell ev) override
  {
    StiffenedGasApplyOneCellEOSVars vars(m_internal_energy
        , m_density
        , m_pressure
        , m_sound_speed
        , m_dpde);
    SCIHOOK_TRIGGER_EOS_STIFFENEDGAS_STIFFENEDGAS_APPLYONECELLEOS_BEFORE
    this->applyOneCellEOS(vars, env, ev);
    SCIHOOK_TRIGGER_EOS_STIFFENEDGAS_STIFFENEDGAS_APPLYONECELLEOS_AFTER
  }


 public:  // ***** METHODES ABSTRAITES
  virtual void initEOS(StiffenedGasInitEOSVars& vars, ::Arcane::Materials::IMeshEnvironment* env) = 0;
  virtual void applyOneCellEOS(StiffenedGasApplyOneCellEOSVars& vars, const ::Arcane::Materials::IMeshEnvironment* env, const EnvCell ev) = 0;

 protected:  // ***** ATTRIBUTS
  IMeshMaterialMng* m_mesh_material_mng;
  IAccEnv* m_acc_env;
};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace EosStiffenedgas

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // EOS_STIFFENEDGAS___STIFFENEDGASSERVICEBASE_H
