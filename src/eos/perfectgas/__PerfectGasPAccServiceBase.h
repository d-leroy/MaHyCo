#ifndef EOS_PERFECTGAS___PERFECTGASPACCSERVICEBASE_H
#define EOS_PERFECTGAS___PERFECTGASPACCSERVICEBASE_H

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
#include "eos/__IEquationOfState.h"
#include "eos/perfectgas/__PerfectGasPAccServiceVars.h"
#include "eos/perfectgas/PerfectGasPAcc_axl.h"
#include "eos/perfectgas/__PerfectGasPAccServiceSciHookMacros.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

using namespace Arcane;
using namespace Arcane::Materials;
namespace EosPerfectgas {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

/*!
 * \brief Service PerfectGasPAcc : classe de base. 
 * 
 */
template<class T>
class PerfectGasPAccServiceBase
: public ArcanePerfectGasPAccObject
{
 SCIHOOK_DECLARE_EOS_PERFECTGAS_PERFECTGASPACC_EVENTS

 public:  // ***** CONSTRUCTEUR & DESTRUCTEUR
  explicit PerfectGasPAccServiceBase(const ServiceBuildInfo& bi)
  : ArcanePerfectGasPAccObject(bi)
  , m_mesh_material_mng(IMeshMaterialMng::getReference(bi.mesh()))
  {
    SCIHOOK_INITIALIZE_EOS_PERFECTGAS_PERFECTGASPACC_EVENTS
  }

  virtual ~PerfectGasPAccServiceBase()
  {
  }

 public:  // ***** ACCESSEURS
  Real getAdiabaticCst() { return options()->getAdiabaticCst(); }
  Real getLimitTension() { return options()->getLimitTension(); }
  bool hasLimitTension() const { return options()->hasLimitTension(); }
  const String getImplName() const { return "PerfectGasPAccService"; }
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
   Cette méthode construit les variables et appelle PerfectGasPAccService::initEOS.
  */
  void initEOS(::Arcane::Materials::IMeshEnvironment* env) override
  {
    PerfectGasPAccInitEOSVars vars(m_pressure
        , m_density
        , m_internal_energy
        , m_sound_speed);
    SCIHOOK_TRIGGER_EOS_PERFECTGAS_PERFECTGASPACC_INITEOS_BEFORE
    this->initEOS(vars, env);
    SCIHOOK_TRIGGER_EOS_PERFECTGAS_PERFECTGASPACC_INITEOS_AFTER
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
         inVars [shape="record", label="density | internal_energy | pressure"];
         inVars -> applyEOS;
         outVars [shape="record", label="pressure | sound_speed | dpde"];
         applyEOS -> outVars;
       }

     }
   \enddot
   Cette méthode construit les variables et appelle PerfectGasPAccService::applyEOS.
  */
  void applyEOS(::Arcane::Materials::IMeshEnvironment* env) override
  {
    PerfectGasPAccApplyEOSVars vars(m_density
        , m_internal_energy
        , m_pressure
        , m_sound_speed
        , m_dpde);
    SCIHOOK_TRIGGER_EOS_PERFECTGAS_PERFECTGASPACC_APPLYEOS_BEFORE
    this->applyEOS(vars, env);
    SCIHOOK_TRIGGER_EOS_PERFECTGAS_PERFECTGASPACC_APPLYEOS_AFTER
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
   Cette méthode construit les variables et appelle PerfectGasPAccService::applyOneCellEOS.
  */
  void applyOneCellEOS(const ::Arcane::Materials::IMeshEnvironment* env, const EnvCell ev) override
  {
    PerfectGasPAccApplyOneCellEOSVars vars(m_density
        , m_internal_energy
        , m_pressure
        , m_sound_speed
        , m_dpde);
    SCIHOOK_TRIGGER_EOS_PERFECTGAS_PERFECTGASPACC_APPLYONECELLEOS_BEFORE
    this->applyOneCellEOS(vars, env, ev);
    SCIHOOK_TRIGGER_EOS_PERFECTGAS_PERFECTGASPACC_APPLYONECELLEOS_AFTER
  }


 public:  // ***** METHODES ABSTRAITES
  virtual void initEOS(PerfectGasPAccInitEOSVars& vars, ::Arcane::Materials::IMeshEnvironment* env) = 0;
  virtual void applyEOS(PerfectGasPAccApplyEOSVars& vars, ::Arcane::Materials::IMeshEnvironment* env) = 0;
  virtual void applyOneCellEOS(PerfectGasPAccApplyOneCellEOSVars& vars, const ::Arcane::Materials::IMeshEnvironment* env, const EnvCell ev) = 0;

 protected:  // ***** ATTRIBUTS
  IMeshMaterialMng* m_mesh_material_mng;
};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace EosPerfectgas

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // EOS_PERFECTGAS___PERFECTGASPACCSERVICEBASE_H
