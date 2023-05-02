#ifndef CAS_TEST_OTHER___OTHERSERVICEBASE_H
#define CAS_TEST_OTHER___OTHERSERVICEBASE_H

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
#include "cas_test/OTHER/__OtherServiceVars.h"
#include "scihook/scihookdefs.h"
#include "cas_test/OTHER/Other_axl.h"
#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_OTHER_DISABLED)
#include "cas_test/OTHER/__OtherServiceContexts.h"
#endif

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

using namespace Arcane;
namespace Cas_testOTHER {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

/*!
 * \brief Service Other : classe de base. 
 * 
 */
template<class T>
class OtherServiceBase
: public ArcaneOtherObject
{
 #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_OTHER_DISABLED)
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
  explicit OtherServiceBase(const ServiceBuildInfo& bi)
  : ArcaneOtherObject(bi)
  {
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_OTHER_DISABLED)
    INITMATMONO_BEFORE = SciHook::register_base_event("OtherServiceBase.InitMatMono.Before");
    INITMATMONO_AFTER = SciHook::register_base_event("OtherServiceBase.InitMatMono.After");
    INITVARMONO_BEFORE = SciHook::register_base_event("OtherServiceBase.InitVarMono.Before");
    INITVARMONO_AFTER = SciHook::register_base_event("OtherServiceBase.InitVarMono.After");
    INITMAT_BEFORE = SciHook::register_base_event("OtherServiceBase.InitMat.Before");
    INITMAT_AFTER = SciHook::register_base_event("OtherServiceBase.InitMat.After");
    INITVAR_BEFORE = SciHook::register_base_event("OtherServiceBase.InitVar.Before");
    INITVAR_AFTER = SciHook::register_base_event("OtherServiceBase.InitVar.After");
    #endif
  }

  virtual ~OtherServiceBase()
  {
  }

 public:  // ***** ACCESSEURS
  Integer getCasTest() { return options()->getCasTest(); }
  bool getReverseOption() { return options()->getReverseOption(); }
  Real getParametre() { return options()->getParametre(); }
  const String getImplName() const { return "OtherService"; }

 public:  // ***** METHODES CONCRETES
  /*!
   Cette méthode construit les variables et appelle OtherService::initMatMono.
  */
  void initMatMono(const Integer dim) override
  {
    OtherInitMatMonoVars vars;
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_OTHER_DISABLED) && not defined(SCIHOOK_CAS_TEST_OTHER_INITMATMONO_DISABLED)
    std::shared_ptr<OtherInitMatMonoExecutionContext> ctx(
        new OtherInitMatMonoExecutionContext("InitMatMonoExecutionContext"
            , dim));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_OTHER_DISABLED) && not defined(SCIHOOK_CAS_TEST_OTHER_INITMATMONO_DISABLED)
    SciHook::trigger(INITMATMONO_BEFORE, ctx);
    this->initMatMono(vars, dim);
    SciHook::trigger(INITMATMONO_AFTER, ctx);
    #else
    this->initMatMono(vars, dim);
    #endif
  }

  /*!
   Cette méthode construit les variables et appelle OtherService::initVarMono.
  */
  void initVarMono(const Integer dim) override
  {
    OtherInitVarMonoVars vars;
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_OTHER_DISABLED) && not defined(SCIHOOK_CAS_TEST_OTHER_INITVARMONO_DISABLED)
    std::shared_ptr<OtherInitVarMonoExecutionContext> ctx(
        new OtherInitVarMonoExecutionContext("InitVarMonoExecutionContext"
            , dim));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_OTHER_DISABLED) && not defined(SCIHOOK_CAS_TEST_OTHER_INITVARMONO_DISABLED)
    SciHook::trigger(INITVARMONO_BEFORE, ctx);
    this->initVarMono(vars, dim);
    SciHook::trigger(INITVARMONO_AFTER, ctx);
    #else
    this->initVarMono(vars, dim);
    #endif
  }

  /*!
   Cette méthode construit les variables et appelle OtherService::initMat.
  */
  void initMat(const Integer dim) override
  {
    OtherInitMatVars vars;
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_OTHER_DISABLED) && not defined(SCIHOOK_CAS_TEST_OTHER_INITMAT_DISABLED)
    std::shared_ptr<OtherInitMatExecutionContext> ctx(
        new OtherInitMatExecutionContext("InitMatExecutionContext"
            , dim));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_OTHER_DISABLED) && not defined(SCIHOOK_CAS_TEST_OTHER_INITMAT_DISABLED)
    SciHook::trigger(INITMAT_BEFORE, ctx);
    this->initMat(vars, dim);
    SciHook::trigger(INITMAT_AFTER, ctx);
    #else
    this->initMat(vars, dim);
    #endif
  }

  /*!
   Cette méthode construit les variables et appelle OtherService::initVar.
  */
  void initVar(const Integer dim) override
  {
    OtherInitVarVars vars;
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_OTHER_DISABLED) && not defined(SCIHOOK_CAS_TEST_OTHER_INITVAR_DISABLED)
    std::shared_ptr<OtherInitVarExecutionContext> ctx(
        new OtherInitVarExecutionContext("InitVarExecutionContext"
            , dim));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_OTHER_DISABLED) && not defined(SCIHOOK_CAS_TEST_OTHER_INITVAR_DISABLED)
    SciHook::trigger(INITVAR_BEFORE, ctx);
    this->initVar(vars, dim);
    SciHook::trigger(INITVAR_AFTER, ctx);
    #else
    this->initVar(vars, dim);
    #endif
  }


 public:  // ***** METHODES ABSTRAITES
  virtual void initMatMono(OtherInitMatMonoVars& vars, const Integer dim) = 0;
  virtual void initVarMono(OtherInitVarMonoVars& vars, const Integer dim) = 0;
  virtual void initMat(OtherInitMatVars& vars, const Integer dim) = 0;
  virtual void initVar(OtherInitVarVars& vars, const Integer dim) = 0;

 protected:  // ***** ATTRIBUTS
};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace Cas_testOTHER

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // CAS_TEST_OTHER___OTHERSERVICEBASE_H
