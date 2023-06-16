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
#include "cas_test/__IInitialisations.h"
#include "cas_test/SEDOV/__SedovServiceVars.h"
#include "scihook/scihookdefs.h"
#include "cas_test/SEDOV/Sedov_axl.h"
#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_SEDOV_DISABLED)
#include "cas_test/SEDOV/__SedovServiceContexts.h"
#endif

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

using namespace Arcane;
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
 #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_SEDOV_DISABLED)
 private:
  size_t INITMATMONO_BEFORE;
  size_t INITMATMONO_AFTER;
  size_t INITVARMONO_BEFORE;
  size_t INITVARMONO_AFTER;
  size_t INITMAT_BEFORE;
  size_t INITMAT_AFTER;
  size_t INITVAR_BEFORE;
  size_t INITVAR_AFTER;
 #endif
 public:  // ***** CONSTRUCTEUR & DESTRUCTEUR
  explicit SedovServiceBase(const ServiceBuildInfo& bi)
  : ArcaneSedovObject(bi)
  {
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_SEDOV_DISABLED)
    INITMATMONO_BEFORE = SciHook::register_base_event("SedovServiceBase.InitMatMono.Before");
    INITMATMONO_AFTER = SciHook::register_base_event("SedovServiceBase.InitMatMono.After");
    INITVARMONO_BEFORE = SciHook::register_base_event("SedovServiceBase.InitVarMono.Before");
    INITVARMONO_AFTER = SciHook::register_base_event("SedovServiceBase.InitVarMono.After");
    INITMAT_BEFORE = SciHook::register_base_event("SedovServiceBase.InitMat.Before");
    INITMAT_AFTER = SciHook::register_base_event("SedovServiceBase.InitMat.After");
    INITVAR_BEFORE = SciHook::register_base_event("SedovServiceBase.InitVar.Before");
    INITVAR_AFTER = SciHook::register_base_event("SedovServiceBase.InitVar.After");
    #endif
  }

  virtual ~SedovServiceBase()
  {
  }

 public:  // ***** ACCESSEURS
  Integer getCasTest() { return options()->getCasTest(); }
  bool getReverseOption() { return options()->getReverseOption(); }
  bool hasReverseOption() const { return options()->hasReverseOption(); }
  Real getParameter() { return options()->getParameter(); }
  const String getImplName() const { return "SedovService"; }

 public:  // ***** METHODES CONCRETES
  /*!
   Cette méthode construit les variables et appelle SedovService::initMatMono.
  */
  void initMatMono(const Integer dim) override
  {
    SedovInitMatMonoVars vars;
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_SEDOV_DISABLED) && not defined(SCIHOOK_CAS_TEST_SEDOV_INITMATMONO_DISABLED)
    std::shared_ptr<SedovInitMatMonoExecutionContext> ctx(
        new SedovInitMatMonoExecutionContext("InitMatMonoExecutionContext"
            , dim));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_SEDOV_DISABLED) && not defined(SCIHOOK_CAS_TEST_SEDOV_INITMATMONO_DISABLED)
    SciHook::trigger(INITMATMONO_BEFORE, ctx);
    this->initMatMono(vars, dim);
    SciHook::trigger(INITMATMONO_AFTER, ctx);
    #else
    this->initMatMono(vars, dim);
    #endif
  }

  /*!
   Cette méthode construit les variables et appelle SedovService::initVarMono.
  */
  void initVarMono(const Integer dim) override
  {
    SedovInitVarMonoVars vars;
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_SEDOV_DISABLED) && not defined(SCIHOOK_CAS_TEST_SEDOV_INITVARMONO_DISABLED)
    std::shared_ptr<SedovInitVarMonoExecutionContext> ctx(
        new SedovInitVarMonoExecutionContext("InitVarMonoExecutionContext"
            , dim));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_SEDOV_DISABLED) && not defined(SCIHOOK_CAS_TEST_SEDOV_INITVARMONO_DISABLED)
    SciHook::trigger(INITVARMONO_BEFORE, ctx);
    this->initVarMono(vars, dim);
    SciHook::trigger(INITVARMONO_AFTER, ctx);
    #else
    this->initVarMono(vars, dim);
    #endif
  }

  /*!
   Cette méthode construit les variables et appelle SedovService::initMat.
  */
  void initMat(const Integer dim) override
  {
    SedovInitMatVars vars;
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_SEDOV_DISABLED) && not defined(SCIHOOK_CAS_TEST_SEDOV_INITMAT_DISABLED)
    std::shared_ptr<SedovInitMatExecutionContext> ctx(
        new SedovInitMatExecutionContext("InitMatExecutionContext"
            , dim));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_SEDOV_DISABLED) && not defined(SCIHOOK_CAS_TEST_SEDOV_INITMAT_DISABLED)
    SciHook::trigger(INITMAT_BEFORE, ctx);
    this->initMat(vars, dim);
    SciHook::trigger(INITMAT_AFTER, ctx);
    #else
    this->initMat(vars, dim);
    #endif
  }

  /*!
   Cette méthode construit les variables et appelle SedovService::initVar.
  */
  void initVar(const Integer dim) override
  {
    SedovInitVarVars vars;
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_SEDOV_DISABLED) && not defined(SCIHOOK_CAS_TEST_SEDOV_INITVAR_DISABLED)
    std::shared_ptr<SedovInitVarExecutionContext> ctx(
        new SedovInitVarExecutionContext("InitVarExecutionContext"
            , dim));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_SEDOV_DISABLED) && not defined(SCIHOOK_CAS_TEST_SEDOV_INITVAR_DISABLED)
    SciHook::trigger(INITVAR_BEFORE, ctx);
    this->initVar(vars, dim);
    SciHook::trigger(INITVAR_AFTER, ctx);
    #else
    this->initVar(vars, dim);
    #endif
  }


 public:  // ***** METHODES ABSTRAITES
  virtual void initMatMono(SedovInitMatMonoVars& vars, const Integer dim) = 0;
  virtual void initVarMono(SedovInitVarMonoVars& vars, const Integer dim) = 0;
  virtual void initMat(SedovInitMatVars& vars, const Integer dim) = 0;
  virtual void initVar(SedovInitVarVars& vars, const Integer dim) = 0;

 protected:  // ***** ATTRIBUTS
};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace Cas_testSEDOV

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // CAS_TEST_SEDOV___SEDOVSERVICEBASE_H
