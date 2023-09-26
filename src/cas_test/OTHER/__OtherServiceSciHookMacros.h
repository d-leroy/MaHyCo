#ifndef CAS_TEST_OTHER___OTHERSERVICESCIHOOKMACROS_H
#define CAS_TEST_OTHER___OTHERSERVICESCIHOOKMACROS_H

#include "scihook/scihookdefs.h"
#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_OTHER_OTHER_DISABLED)
#include "SciHook.h"
#include "cas_test/OTHER/__OtherServiceContexts.h"
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_OTHER_OTHER_DISABLED)
#define SCIHOOK_DECLARE_CAS_TEST_OTHER_OTHER_EVENTS \
private:\
 size_t INITMATMONO_BEFORE;\
 size_t INITMATMONO_AFTER;\
 size_t INITVARMONO_BEFORE;\
 size_t INITVARMONO_AFTER;\
 size_t INITMAT_BEFORE;\
 size_t INITMAT_AFTER;\
 size_t INITVAR_BEFORE;\
 size_t INITVAR_AFTER;
#define SCIHOOK_INITIALIZE_CAS_TEST_OTHER_OTHER_EVENTS \
INITMATMONO_BEFORE = SciHook::register_base_event("Other.InitMatMono.Before");\
INITMATMONO_AFTER = SciHook::register_base_event("Other.InitMatMono.After");\
INITVARMONO_BEFORE = SciHook::register_base_event("Other.InitVarMono.Before");\
INITVARMONO_AFTER = SciHook::register_base_event("Other.InitVarMono.After");\
INITMAT_BEFORE = SciHook::register_base_event("Other.InitMat.Before");\
INITMAT_AFTER = SciHook::register_base_event("Other.InitMat.After");\
INITVAR_BEFORE = SciHook::register_base_event("Other.InitVar.Before");\
INITVAR_AFTER = SciHook::register_base_event("Other.InitVar.After");
#else
#define SCIHOOK_DECLARE_CAS_TEST_OTHER_OTHER_EVENTS
#define SCIHOOK_INITIALIZE_CAS_TEST_OTHER_OTHER_EVENTS
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_OTHER_OTHER_DISABLED) && not defined(SCIHOOK_CAS_TEST_OTHER_OTHER_INITMATMONO_DISABLED)
#define SCIHOOK_TRIGGER_CAS_TEST_OTHER_OTHER_INITMATMONO_BEFORE \
std::shared_ptr<OtherInitMatMonoExecutionContext> ctx(new OtherInitMatMonoExecutionContext("InitMatMonoExecutionContext", dim));\
SciHook::trigger(INITMATMONO_BEFORE, ctx);
#define SCIHOOK_TRIGGER_CAS_TEST_OTHER_OTHER_INITMATMONO_AFTER SciHook::trigger(INITMATMONO_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_CAS_TEST_OTHER_OTHER_INITMATMONO_BEFORE
#define SCIHOOK_TRIGGER_CAS_TEST_OTHER_OTHER_INITMATMONO_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_OTHER_OTHER_DISABLED) && not defined(SCIHOOK_CAS_TEST_OTHER_OTHER_INITVARMONO_DISABLED)
#define SCIHOOK_TRIGGER_CAS_TEST_OTHER_OTHER_INITVARMONO_BEFORE \
std::shared_ptr<OtherInitVarMonoExecutionContext> ctx(new OtherInitVarMonoExecutionContext("InitVarMonoExecutionContext", dim));\
SciHook::trigger(INITVARMONO_BEFORE, ctx);
#define SCIHOOK_TRIGGER_CAS_TEST_OTHER_OTHER_INITVARMONO_AFTER SciHook::trigger(INITVARMONO_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_CAS_TEST_OTHER_OTHER_INITVARMONO_BEFORE
#define SCIHOOK_TRIGGER_CAS_TEST_OTHER_OTHER_INITVARMONO_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_OTHER_OTHER_DISABLED) && not defined(SCIHOOK_CAS_TEST_OTHER_OTHER_INITMAT_DISABLED)
#define SCIHOOK_TRIGGER_CAS_TEST_OTHER_OTHER_INITMAT_BEFORE \
std::shared_ptr<OtherInitMatExecutionContext> ctx(new OtherInitMatExecutionContext("InitMatExecutionContext", &vars, dim));\
SciHook::trigger(INITMAT_BEFORE, ctx);
#define SCIHOOK_TRIGGER_CAS_TEST_OTHER_OTHER_INITMAT_AFTER SciHook::trigger(INITMAT_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_CAS_TEST_OTHER_OTHER_INITMAT_BEFORE
#define SCIHOOK_TRIGGER_CAS_TEST_OTHER_OTHER_INITMAT_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_OTHER_OTHER_DISABLED) && not defined(SCIHOOK_CAS_TEST_OTHER_OTHER_INITVAR_DISABLED)
#define SCIHOOK_TRIGGER_CAS_TEST_OTHER_OTHER_INITVAR_BEFORE \
std::shared_ptr<OtherInitVarExecutionContext> ctx(new OtherInitVarExecutionContext("InitVarExecutionContext", &vars, dim));\
SciHook::trigger(INITVAR_BEFORE, ctx);
#define SCIHOOK_TRIGGER_CAS_TEST_OTHER_OTHER_INITVAR_AFTER SciHook::trigger(INITVAR_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_CAS_TEST_OTHER_OTHER_INITVAR_BEFORE
#define SCIHOOK_TRIGGER_CAS_TEST_OTHER_OTHER_INITVAR_AFTER
#endif

#endif // CAS_TEST_OTHER___OTHERSERVICESCIHOOKMACROS_H
