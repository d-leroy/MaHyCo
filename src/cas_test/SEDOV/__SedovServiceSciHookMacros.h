#ifndef CAS_TEST_SEDOV___SEDOVSERVICESCIHOOKMACROS_H
#define CAS_TEST_SEDOV___SEDOVSERVICESCIHOOKMACROS_H

#include "scihook/scihookdefs.h"
#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_SEDOV_SEDOV_DISABLED)
#include "SciHook.h"
#include "cas_test/SEDOV/__SedovServiceContexts.h"
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_SEDOV_SEDOV_DISABLED)
#define SCIHOOK_DECLARE_CAS_TEST_SEDOV_SEDOV_EVENTS \
private:\
 size_t INITMATMONO_BEFORE;\
 size_t INITMATMONO_AFTER;\
 size_t INITVARMONO_BEFORE;\
 size_t INITVARMONO_AFTER;\
 size_t INITMAT_BEFORE;\
 size_t INITMAT_AFTER;\
 size_t INITVAR_BEFORE;\
 size_t INITVAR_AFTER;
#define SCIHOOK_INITIALIZE_CAS_TEST_SEDOV_SEDOV_EVENTS \
INITMATMONO_BEFORE = SciHook::register_base_event("Sedov.InitMatMono.Before");\
INITMATMONO_AFTER = SciHook::register_base_event("Sedov.InitMatMono.After");\
INITVARMONO_BEFORE = SciHook::register_base_event("Sedov.InitVarMono.Before");\
INITVARMONO_AFTER = SciHook::register_base_event("Sedov.InitVarMono.After");\
INITMAT_BEFORE = SciHook::register_base_event("Sedov.InitMat.Before");\
INITMAT_AFTER = SciHook::register_base_event("Sedov.InitMat.After");\
INITVAR_BEFORE = SciHook::register_base_event("Sedov.InitVar.Before");\
INITVAR_AFTER = SciHook::register_base_event("Sedov.InitVar.After");
#else
#define SCIHOOK_DECLARE_CAS_TEST_SEDOV_SEDOV_EVENTS
#define SCIHOOK_INITIALIZE_CAS_TEST_SEDOV_SEDOV_EVENTS
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_SEDOV_SEDOV_DISABLED) && not defined(SCIHOOK_CAS_TEST_SEDOV_SEDOV_INITMATMONO_DISABLED)
#define SCIHOOK_TRIGGER_CAS_TEST_SEDOV_SEDOV_INITMATMONO_BEFORE \
std::shared_ptr<SedovInitMatMonoExecutionContext> ctx(new SedovInitMatMonoExecutionContext("InitMatMonoExecutionContext", &vars, dim));\
SciHook::trigger(INITMATMONO_BEFORE, ctx);
#define SCIHOOK_TRIGGER_CAS_TEST_SEDOV_SEDOV_INITMATMONO_AFTER SciHook::trigger(INITMATMONO_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_CAS_TEST_SEDOV_SEDOV_INITMATMONO_BEFORE
#define SCIHOOK_TRIGGER_CAS_TEST_SEDOV_SEDOV_INITMATMONO_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_SEDOV_SEDOV_DISABLED) && not defined(SCIHOOK_CAS_TEST_SEDOV_SEDOV_INITVARMONO_DISABLED)
#define SCIHOOK_TRIGGER_CAS_TEST_SEDOV_SEDOV_INITVARMONO_BEFORE \
std::shared_ptr<SedovInitVarMonoExecutionContext> ctx(new SedovInitVarMonoExecutionContext("InitVarMonoExecutionContext", &vars, dim));\
SciHook::trigger(INITVARMONO_BEFORE, ctx);
#define SCIHOOK_TRIGGER_CAS_TEST_SEDOV_SEDOV_INITVARMONO_AFTER SciHook::trigger(INITVARMONO_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_CAS_TEST_SEDOV_SEDOV_INITVARMONO_BEFORE
#define SCIHOOK_TRIGGER_CAS_TEST_SEDOV_SEDOV_INITVARMONO_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_SEDOV_SEDOV_DISABLED) && not defined(SCIHOOK_CAS_TEST_SEDOV_SEDOV_INITMAT_DISABLED)
#define SCIHOOK_TRIGGER_CAS_TEST_SEDOV_SEDOV_INITMAT_BEFORE \
std::shared_ptr<SedovInitMatExecutionContext> ctx(new SedovInitMatExecutionContext("InitMatExecutionContext", &vars, dim));\
SciHook::trigger(INITMAT_BEFORE, ctx);
#define SCIHOOK_TRIGGER_CAS_TEST_SEDOV_SEDOV_INITMAT_AFTER SciHook::trigger(INITMAT_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_CAS_TEST_SEDOV_SEDOV_INITMAT_BEFORE
#define SCIHOOK_TRIGGER_CAS_TEST_SEDOV_SEDOV_INITMAT_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_SEDOV_SEDOV_DISABLED) && not defined(SCIHOOK_CAS_TEST_SEDOV_SEDOV_INITVAR_DISABLED)
#define SCIHOOK_TRIGGER_CAS_TEST_SEDOV_SEDOV_INITVAR_BEFORE \
std::shared_ptr<SedovInitVarExecutionContext> ctx(new SedovInitVarExecutionContext("InitVarExecutionContext", &vars, dim));\
SciHook::trigger(INITVAR_BEFORE, ctx);
#define SCIHOOK_TRIGGER_CAS_TEST_SEDOV_SEDOV_INITVAR_AFTER SciHook::trigger(INITVAR_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_CAS_TEST_SEDOV_SEDOV_INITVAR_BEFORE
#define SCIHOOK_TRIGGER_CAS_TEST_SEDOV_SEDOV_INITVAR_AFTER
#endif

#endif // CAS_TEST_SEDOV___SEDOVSERVICESCIHOOKMACROS_H
