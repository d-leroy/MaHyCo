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
#include "arcane/materials/IMeshEnvironment.h"
#include "eos/__IEquationOfState.h"
#include "eos/stiffenedgas/__StiffenedGasServiceVars.h"
#include "scihook/scihookdefs.h"
#include "eos/stiffenedgas/StiffenedGas_axl.h"
#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_EOS_STIFFENEDGAS_DISABLED)
#include "eos/stiffenedgas/__StiffenedGasServiceContexts.h"
#endif

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
 #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_EOS_STIFFENEDGAS_DISABLED)
 private:
  size_t INITEOS_BEFORE;
  size_t INITEOS_AFTER;
  size_t APPLYEOS_BEFORE;
  size_t APPLYEOS_AFTER;
  size_t APPLYONECELLEOS_BEFORE;
  size_t APPLYONECELLEOS_AFTER;
 #endif
 public:  // ***** CONSTRUCTEUR & DESTRUCTEUR
  explicit StiffenedGasServiceBase(const ServiceBuildInfo& bi)
  : ArcaneStiffenedGasObject(bi)
  , m_mesh_material_mng(IMeshMaterialMng::getReference(bi.mesh()))
  {
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_EOS_STIFFENEDGAS_DISABLED)
    INITEOS_BEFORE = SciHook::register_base_event("StiffenedGasServiceBase.InitEOS.Before");
    INITEOS_AFTER = SciHook::register_base_event("StiffenedGasServiceBase.InitEOS.After");
    APPLYEOS_BEFORE = SciHook::register_base_event("StiffenedGasServiceBase.ApplyEOS.Before");
    APPLYEOS_AFTER = SciHook::register_base_event("StiffenedGasServiceBase.ApplyEOS.After");
    APPLYONECELLEOS_BEFORE = SciHook::register_base_event("StiffenedGasServiceBase.ApplyOneCellEOS.Before");
    APPLYONECELLEOS_AFTER = SciHook::register_base_event("StiffenedGasServiceBase.ApplyOneCellEOS.After");
    #endif
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
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_EOS_STIFFENEDGAS_DISABLED) && not defined(SCIHOOK_EOS_STIFFENEDGAS_INITEOS_DISABLED)
    std::shared_ptr<StiffenedGasInitEOSExecutionContext> ctx(
        new StiffenedGasInitEOSExecutionContext("InitEOSExecutionContext"
            , &vars
            , env));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_EOS_STIFFENEDGAS_DISABLED) && not defined(SCIHOOK_EOS_STIFFENEDGAS_INITEOS_DISABLED)
    SciHook::trigger(INITEOS_BEFORE, ctx);
    this->initEOS(vars, env);
    SciHook::trigger(INITEOS_AFTER, ctx);
    #else
    this->initEOS(vars, env);
    #endif
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
         inVars [shape="record", label="internal_energy | density"];
         inVars -> applyEOS;
         outVars [shape="record", label="pressure | sound_speed | dpde"];
         applyEOS -> outVars;
       }
   
     }
   \enddot
   Cette méthode construit les variables et appelle StiffenedGasService::applyEOS.
  */
  void applyEOS(::Arcane::Materials::IMeshEnvironment* env) override
  {
    StiffenedGasApplyEOSVars vars(m_internal_energy
        , m_density
        , m_pressure
        , m_sound_speed
        , m_dpde);
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_EOS_STIFFENEDGAS_DISABLED) && not defined(SCIHOOK_EOS_STIFFENEDGAS_APPLYEOS_DISABLED)
    std::shared_ptr<StiffenedGasApplyEOSExecutionContext> ctx(
        new StiffenedGasApplyEOSExecutionContext("ApplyEOSExecutionContext"
            , &vars
            , env));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_EOS_STIFFENEDGAS_DISABLED) && not defined(SCIHOOK_EOS_STIFFENEDGAS_APPLYEOS_DISABLED)
    SciHook::trigger(APPLYEOS_BEFORE, ctx);
    this->applyEOS(vars, env);
    SciHook::trigger(APPLYEOS_AFTER, ctx);
    #else
    this->applyEOS(vars, env);
    #endif
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
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_EOS_STIFFENEDGAS_DISABLED) && not defined(SCIHOOK_EOS_STIFFENEDGAS_APPLYONECELLEOS_DISABLED)
    std::shared_ptr<StiffenedGasApplyOneCellEOSExecutionContext> ctx(
        new StiffenedGasApplyOneCellEOSExecutionContext("ApplyOneCellEOSExecutionContext"
            , &vars
            , env
            , ev));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_EOS_STIFFENEDGAS_DISABLED) && not defined(SCIHOOK_EOS_STIFFENEDGAS_APPLYONECELLEOS_DISABLED)
    SciHook::trigger(APPLYONECELLEOS_BEFORE, ctx);
    this->applyOneCellEOS(vars, env, ev);
    SciHook::trigger(APPLYONECELLEOS_AFTER, ctx);
    #else
    this->applyOneCellEOS(vars, env, ev);
    #endif
  }


 public:  // ***** METHODES ABSTRAITES
  virtual void initEOS(StiffenedGasInitEOSVars& vars, ::Arcane::Materials::IMeshEnvironment* env) = 0;
  virtual void applyEOS(StiffenedGasApplyEOSVars& vars, ::Arcane::Materials::IMeshEnvironment* env) = 0;
  virtual void applyOneCellEOS(StiffenedGasApplyOneCellEOSVars& vars, const ::Arcane::Materials::IMeshEnvironment* env, const EnvCell ev) = 0;

 protected:  // ***** ATTRIBUTS
  IMeshMaterialMng* m_mesh_material_mng;
};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace EosStiffenedgas

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // EOS_STIFFENEDGAS___STIFFENEDGASSERVICEBASE_H
