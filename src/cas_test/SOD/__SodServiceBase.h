#ifndef CAS_TEST_SOD___SODSERVICEBASE_H
#define CAS_TEST_SOD___SODSERVICEBASE_H

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
#include "cas_test/SOD/__SodServiceVars.h"
#include "scihook/scihookdefs.h"
#include "cas_test/SOD/Sod_axl.h"
#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_SOD_DISABLED)
#include "cas_test/SOD/__SodServiceContexts.h"
#endif

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

using namespace Arcane;
namespace Cas_testSOD {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

/*!
 * \brief Service Sod : classe de base. 
 * 
 */
template<class T>
class SodServiceBase
: public ArcaneSodObject
{
 #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_SOD_DISABLED)
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
  explicit SodServiceBase(const ServiceBuildInfo& bi)
  : ArcaneSodObject(bi)
  {
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_SOD_DISABLED)
    INITMATMONO_BEFORE = SciHook::register_base_event("SodServiceBase.InitMatMono.Before");
    INITMATMONO_AFTER = SciHook::register_base_event("SodServiceBase.InitMatMono.After");
    INITVARMONO_BEFORE = SciHook::register_base_event("SodServiceBase.InitVarMono.Before");
    INITVARMONO_AFTER = SciHook::register_base_event("SodServiceBase.InitVarMono.After");
    INITMAT_BEFORE = SciHook::register_base_event("SodServiceBase.InitMat.Before");
    INITMAT_AFTER = SciHook::register_base_event("SodServiceBase.InitMat.After");
    INITVAR_BEFORE = SciHook::register_base_event("SodServiceBase.InitVar.Before");
    INITVAR_AFTER = SciHook::register_base_event("SodServiceBase.InitVar.After");
    #endif
  }

  virtual ~SodServiceBase()
  {
  }

 public:  // ***** ACCESSEURS
  Integer getCasTest() { return options()->getCasTest(); }
  bool getReverseOption() { return options()->getReverseOption(); }
  Real getParametre() { return options()->getParametre(); }
  const String getImplName() const { return "SodService"; }

 public:  // ***** METHODES CONCRETES
  /*!
   Cette méthode construit les variables et appelle SodService::initMatMono.
  */
  void initMatMono(const Integer dim) override
  {
    SodInitMatMonoVars vars;
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_SOD_DISABLED) && not defined(SCIHOOK_CAS_TEST_SOD_INITMATMONO_DISABLED)
    std::shared_ptr<SodInitMatMonoExecutionContext> ctx(
        new SodInitMatMonoExecutionContext("InitMatMonoExecutionContext"
            , dim));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_SOD_DISABLED) && not defined(SCIHOOK_CAS_TEST_SOD_INITMATMONO_DISABLED)
    SciHook::trigger(INITMATMONO_BEFORE, ctx);
    this->initMatMono(vars, dim);
    SciHook::trigger(INITMATMONO_AFTER, ctx);
    #else
    this->initMatMono(vars, dim);
    #endif
  }

  /*!
   Cette méthode construit les variables et appelle SodService::initVarMono.
  */
  void initVarMono(const Integer dim) override
  {
    SodInitVarMonoVars vars;
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_SOD_DISABLED) && not defined(SCIHOOK_CAS_TEST_SOD_INITVARMONO_DISABLED)
    std::shared_ptr<SodInitVarMonoExecutionContext> ctx(
        new SodInitVarMonoExecutionContext("InitVarMonoExecutionContext"
            , dim));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_SOD_DISABLED) && not defined(SCIHOOK_CAS_TEST_SOD_INITVARMONO_DISABLED)
    SciHook::trigger(INITVARMONO_BEFORE, ctx);
    this->initVarMono(vars, dim);
    SciHook::trigger(INITVARMONO_AFTER, ctx);
    #else
    this->initVarMono(vars, dim);
    #endif
  }

  /*!
   Cette méthode construit les variables et appelle SodService::initMat.
  */
  void initMat(const Integer dim) override
  {
    SodInitMatVars vars;
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_SOD_DISABLED) && not defined(SCIHOOK_CAS_TEST_SOD_INITMAT_DISABLED)
    std::shared_ptr<SodInitMatExecutionContext> ctx(
        new SodInitMatExecutionContext("InitMatExecutionContext"
            , dim));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_SOD_DISABLED) && not defined(SCIHOOK_CAS_TEST_SOD_INITMAT_DISABLED)
    SciHook::trigger(INITMAT_BEFORE, ctx);
    this->initMat(vars, dim);
    SciHook::trigger(INITMAT_AFTER, ctx);
    #else
    this->initMat(vars, dim);
    #endif
  }

  /*!
   Cette méthode construit les variables et appelle SodService::initVar.
  */
  void initVar(const Integer dim) override
  {
    SodInitVarVars vars;
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_SOD_DISABLED) && not defined(SCIHOOK_CAS_TEST_SOD_INITVAR_DISABLED)
    std::shared_ptr<SodInitVarExecutionContext> ctx(
        new SodInitVarExecutionContext("InitVarExecutionContext"
            , dim));
    #endif
    #if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_SOD_DISABLED) && not defined(SCIHOOK_CAS_TEST_SOD_INITVAR_DISABLED)
    SciHook::trigger(INITVAR_BEFORE, ctx);
    this->initVar(vars, dim);
    SciHook::trigger(INITVAR_AFTER, ctx);
    #else
    this->initVar(vars, dim);
    #endif
  }


 public:  // ***** METHODES ABSTRAITES
  virtual void initMatMono(SodInitMatMonoVars& vars, const Integer dim) = 0;
  virtual void initVarMono(SodInitVarMonoVars& vars, const Integer dim) = 0;
  virtual void initMat(SodInitMatVars& vars, const Integer dim) = 0;
  virtual void initVar(SodInitVarVars& vars, const Integer dim) = 0;

 protected:  // ***** ATTRIBUTS
};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace Cas_testSOD

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // CAS_TEST_SOD___SODSERVICEBASE_H
