#ifndef CAS_TEST_SOD___SODSERVICESCIHOOKMACROS_H
#define CAS_TEST_SOD___SODSERVICESCIHOOKMACROS_H

#include "scihook/scihookdefs.h"
#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_SOD_SOD_DISABLED)
#include "SciHook.h"
#include "cas_test/SOD/__SodServiceContexts.h"
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_SOD_SOD_DISABLED)
#define SCIHOOK_DECLARE_CAS_TEST_SOD_SOD_EVENTS \
private:\
 size_t INITMATMONO_BEFORE;\
 size_t INITMATMONO_AFTER;\
 size_t INITVARMONO_BEFORE;\
 size_t INITVARMONO_AFTER;\
 size_t INITMAT_BEFORE;\
 size_t INITMAT_AFTER;\
 size_t INITVAR_BEFORE;\
 size_t INITVAR_AFTER;
#define SCIHOOK_INITIALIZE_CAS_TEST_SOD_SOD_EVENTS \
INITMATMONO_BEFORE = SciHook::register_base_event("Sod.InitMatMono.Before");\
INITMATMONO_AFTER = SciHook::register_base_event("Sod.InitMatMono.After");\
INITVARMONO_BEFORE = SciHook::register_base_event("Sod.InitVarMono.Before");\
INITVARMONO_AFTER = SciHook::register_base_event("Sod.InitVarMono.After");\
INITMAT_BEFORE = SciHook::register_base_event("Sod.InitMat.Before");\
INITMAT_AFTER = SciHook::register_base_event("Sod.InitMat.After");\
INITVAR_BEFORE = SciHook::register_base_event("Sod.InitVar.Before");\
INITVAR_AFTER = SciHook::register_base_event("Sod.InitVar.After");
#else
#define SCIHOOK_DECLARE_CAS_TEST_SOD_SOD_EVENTS
#define SCIHOOK_INITIALIZE_CAS_TEST_SOD_SOD_EVENTS
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_SOD_SOD_DISABLED) && not defined(SCIHOOK_CAS_TEST_SOD_SOD_INITMATMONO_DISABLED)
#define SCIHOOK_TRIGGER_INITMATMONO_BEFORE \
std::shared_ptr<SodInitMatMonoExecutionContext> ctx(new SodInitMatMonoExecutionContext("InitMatMonoExecutionContext", &vars, dim));\
SciHook::trigger(INITMATMONO_BEFORE, ctx);
#define SCIHOOK_TRIGGER_INITMATMONO_AFTER SciHook::trigger(INITMATMONO_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_INITMATMONO_BEFORE
#define SCIHOOK_TRIGGER_INITMATMONO_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_SOD_SOD_DISABLED) && not defined(SCIHOOK_CAS_TEST_SOD_SOD_INITVARMONO_DISABLED)
#define SCIHOOK_TRIGGER_INITVARMONO_BEFORE \
std::shared_ptr<SodInitVarMonoExecutionContext> ctx(new SodInitVarMonoExecutionContext("InitVarMonoExecutionContext", &vars, dim));\
SciHook::trigger(INITVARMONO_BEFORE, ctx);
#define SCIHOOK_TRIGGER_INITVARMONO_AFTER SciHook::trigger(INITVARMONO_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_INITVARMONO_BEFORE
#define SCIHOOK_TRIGGER_INITVARMONO_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_SOD_SOD_DISABLED) && not defined(SCIHOOK_CAS_TEST_SOD_SOD_INITMAT_DISABLED)
#define SCIHOOK_TRIGGER_INITMAT_BEFORE \
std::shared_ptr<SodInitMatExecutionContext> ctx(new SodInitMatExecutionContext("InitMatExecutionContext", &vars, dim));\
SciHook::trigger(INITMAT_BEFORE, ctx);
#define SCIHOOK_TRIGGER_INITMAT_AFTER SciHook::trigger(INITMAT_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_INITMAT_BEFORE
#define SCIHOOK_TRIGGER_INITMAT_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_SOD_SOD_DISABLED) && not defined(SCIHOOK_CAS_TEST_SOD_SOD_INITVAR_DISABLED)
#define SCIHOOK_TRIGGER_INITVAR_BEFORE \
std::shared_ptr<SodInitVarExecutionContext> ctx(new SodInitVarExecutionContext("InitVarExecutionContext", &vars, dim));\
SciHook::trigger(INITVAR_BEFORE, ctx);
#define SCIHOOK_TRIGGER_INITVAR_AFTER SciHook::trigger(INITVAR_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_INITVAR_BEFORE
#define SCIHOOK_TRIGGER_INITVAR_AFTER
#endif

#endif // CAS_TEST_SOD___SODSERVICESCIHOOKMACROS_H
