#ifndef CAS_TEST_RIDER___RIDERSERVICEBASE_H
#define CAS_TEST_RIDER___RIDERSERVICEBASE_H

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
#include "cas_test/RIDER/__RiderServiceVars.h"
#include "scihook/scihookdefs.h"
#include "cas_test/RIDER/Rider_axl.h"
#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_RIDER_DISABLED)
#include "cas_test/RIDER/__RiderServiceContexts.h"
#endif

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

using namespace Arcane;
namespace Cas_testRIDER {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

/*!
 * \brief Service Rider : classe de base. 
 * 
 */
template<class T>
class RiderServiceBase
: public ArcaneRiderObject
{
 #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_RIDER_DISABLED)
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
  explicit RiderServiceBase(const ServiceBuildInfo& bi)
  : ArcaneRiderObject(bi)
  {
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_RIDER_DISABLED)
    INITMATMONO_BEFORE = SciHook::register_base_event("RiderServiceBase.InitMatMono.Before");
    INITMATMONO_AFTER = SciHook::register_base_event("RiderServiceBase.InitMatMono.After");
    INITVARMONO_BEFORE = SciHook::register_base_event("RiderServiceBase.InitVarMono.Before");
    INITVARMONO_AFTER = SciHook::register_base_event("RiderServiceBase.InitVarMono.After");
    INITMAT_BEFORE = SciHook::register_base_event("RiderServiceBase.InitMat.Before");
    INITMAT_AFTER = SciHook::register_base_event("RiderServiceBase.InitMat.After");
    INITVAR_BEFORE = SciHook::register_base_event("RiderServiceBase.InitVar.Before");
    INITVAR_AFTER = SciHook::register_base_event("RiderServiceBase.InitVar.After");
    #endif
  }

  virtual ~RiderServiceBase()
  {
  }

 public:  // ***** ACCESSEURS
  Integer getCasTest() { return options()->getCasTest(); }
  bool getReverseOption() { return options()->getReverseOption(); }
  Real getParametre() { return options()->getParametre(); }
  const String getImplName() const { return "RiderService"; }

 public:  // ***** METHODES CONCRETES
  /*!
   Cette méthode construit les variables et appelle RiderService::initMatMono.
  */
  void initMatMono(const Integer dim) override
  {
    RiderInitMatMonoVars vars;
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_RIDER_DISABLED) && not defined(SCIHOOK_CAS_TEST_RIDER_INITMATMONO_DISABLED)
    std::shared_ptr<RiderInitMatMonoExecutionContext> ctx(
        new RiderInitMatMonoExecutionContext("InitMatMonoExecutionContext"
            , dim));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_RIDER_DISABLED) && not defined(SCIHOOK_CAS_TEST_RIDER_INITMATMONO_DISABLED)
    SciHook::trigger(INITMATMONO_BEFORE, ctx);
    this->initMatMono(vars, dim);
    SciHook::trigger(INITMATMONO_AFTER, ctx);
    #else
    this->initMatMono(vars, dim);
    #endif
  }

  /*!
   Cette méthode construit les variables et appelle RiderService::initVarMono.
  */
  void initVarMono(const Integer dim) override
  {
    RiderInitVarMonoVars vars;
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_RIDER_DISABLED) && not defined(SCIHOOK_CAS_TEST_RIDER_INITVARMONO_DISABLED)
    std::shared_ptr<RiderInitVarMonoExecutionContext> ctx(
        new RiderInitVarMonoExecutionContext("InitVarMonoExecutionContext"
            , dim));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_RIDER_DISABLED) && not defined(SCIHOOK_CAS_TEST_RIDER_INITVARMONO_DISABLED)
    SciHook::trigger(INITVARMONO_BEFORE, ctx);
    this->initVarMono(vars, dim);
    SciHook::trigger(INITVARMONO_AFTER, ctx);
    #else
    this->initVarMono(vars, dim);
    #endif
  }

  /*!
   Cette méthode construit les variables et appelle RiderService::initMat.
  */
  void initMat(const Integer dim) override
  {
    RiderInitMatVars vars;
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_RIDER_DISABLED) && not defined(SCIHOOK_CAS_TEST_RIDER_INITMAT_DISABLED)
    std::shared_ptr<RiderInitMatExecutionContext> ctx(
        new RiderInitMatExecutionContext("InitMatExecutionContext"
            , dim));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_RIDER_DISABLED) && not defined(SCIHOOK_CAS_TEST_RIDER_INITMAT_DISABLED)
    SciHook::trigger(INITMAT_BEFORE, ctx);
    this->initMat(vars, dim);
    SciHook::trigger(INITMAT_AFTER, ctx);
    #else
    this->initMat(vars, dim);
    #endif
  }

  /*!
   Cette méthode construit les variables et appelle RiderService::initVar.
  */
  void initVar(const Integer dim) override
  {
    RiderInitVarVars vars;
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_RIDER_DISABLED) && not defined(SCIHOOK_CAS_TEST_RIDER_INITVAR_DISABLED)
    std::shared_ptr<RiderInitVarExecutionContext> ctx(
        new RiderInitVarExecutionContext("InitVarExecutionContext"
            , dim));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_RIDER_DISABLED) && not defined(SCIHOOK_CAS_TEST_RIDER_INITVAR_DISABLED)
    SciHook::trigger(INITVAR_BEFORE, ctx);
    this->initVar(vars, dim);
    SciHook::trigger(INITVAR_AFTER, ctx);
    #else
    this->initVar(vars, dim);
    #endif
  }


 public:  // ***** METHODES ABSTRAITES
  virtual void initMatMono(RiderInitMatMonoVars& vars, const Integer dim) = 0;
  virtual void initVarMono(RiderInitVarMonoVars& vars, const Integer dim) = 0;
  virtual void initMat(RiderInitMatVars& vars, const Integer dim) = 0;
  virtual void initVar(RiderInitVarVars& vars, const Integer dim) = 0;

 protected:  // ***** ATTRIBUTS
};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace Cas_testRIDER

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // CAS_TEST_RIDER___RIDERSERVICEBASE_H
