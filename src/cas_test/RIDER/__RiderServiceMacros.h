#ifndef CAS_TEST_RIDER___RIDERSERVICEMACROS_H
#define CAS_TEST_RIDER___RIDERSERVICEMACROS_H

#include "scihook/scihookdefs.h"
#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_RIDER_RIDER_DISABLED)
#include "SciHook.h"
#include "cas_test/RIDER/__RiderServiceContexts.h"
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_RIDER_RIDER_DISABLED)
#define SCIHOOK_DECLARE_CAS_TEST_RIDER_RIDER_EVENTS \
private:\
 size_t INITMATMONO_BEFORE;\
 size_t INITMATMONO_AFTER;\
 size_t INITVARMONO_BEFORE;\
 size_t INITVARMONO_AFTER;\
 size_t INITMAT_BEFORE;\
 size_t INITMAT_AFTER;\
 size_t INITVAR_BEFORE;\
 size_t INITVAR_AFTER;
#define SCIHOOK_INITIALIZE_CAS_TEST_RIDER_RIDER_EVENTS \
INITMATMONO_BEFORE = SciHook::register_base_event("Rider.InitMatMono.Before");\
INITMATMONO_AFTER = SciHook::register_base_event("Rider.InitMatMono.After");\
INITVARMONO_BEFORE = SciHook::register_base_event("Rider.InitVarMono.Before");\
INITVARMONO_AFTER = SciHook::register_base_event("Rider.InitVarMono.After");\
INITMAT_BEFORE = SciHook::register_base_event("Rider.InitMat.Before");\
INITMAT_AFTER = SciHook::register_base_event("Rider.InitMat.After");\
INITVAR_BEFORE = SciHook::register_base_event("Rider.InitVar.Before");\
INITVAR_AFTER = SciHook::register_base_event("Rider.InitVar.After");
#else
#define SCIHOOK_DECLARE_CAS_TEST_RIDER_RIDER_EVENTS
#define SCIHOOK_INITIALIZE_CAS_TEST_RIDER_RIDER_EVENTS
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_RIDER_RIDER_DISABLED) && not defined(SCIHOOK_CAS_TEST_RIDER_RIDER_INITMATMONO_DISABLED)
#define SCIHOOK_TRIGGER_INITMATMONO_BEFORE \
std::shared_ptr<RiderInitMatMonoExecutionContext> ctx(new RiderInitMatMonoExecutionContext("InitMatMonoExecutionContext", &vars, dim));\
SciHook::trigger(INITMATMONO_BEFORE, ctx);
#define SCIHOOK_TRIGGER_INITMATMONO_AFTER SciHook::trigger(INITMATMONO_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_INITMATMONO_BEFORE
#define SCIHOOK_TRIGGER_INITMATMONO_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_RIDER_RIDER_DISABLED) && not defined(SCIHOOK_CAS_TEST_RIDER_RIDER_INITVARMONO_DISABLED)
#define SCIHOOK_TRIGGER_INITVARMONO_BEFORE \
std::shared_ptr<RiderInitVarMonoExecutionContext> ctx(new RiderInitVarMonoExecutionContext("InitVarMonoExecutionContext", &vars, dim));\
SciHook::trigger(INITVARMONO_BEFORE, ctx);
#define SCIHOOK_TRIGGER_INITVARMONO_AFTER SciHook::trigger(INITVARMONO_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_INITVARMONO_BEFORE
#define SCIHOOK_TRIGGER_INITVARMONO_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_RIDER_RIDER_DISABLED) && not defined(SCIHOOK_CAS_TEST_RIDER_RIDER_INITMAT_DISABLED)
#define SCIHOOK_TRIGGER_INITMAT_BEFORE \
std::shared_ptr<RiderInitMatExecutionContext> ctx(new RiderInitMatExecutionContext("InitMatExecutionContext", &vars, dim));\
SciHook::trigger(INITMAT_BEFORE, ctx);
#define SCIHOOK_TRIGGER_INITMAT_AFTER SciHook::trigger(INITMAT_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_INITMAT_BEFORE
#define SCIHOOK_TRIGGER_INITMAT_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_CAS_TEST_RIDER_RIDER_DISABLED) && not defined(SCIHOOK_CAS_TEST_RIDER_RIDER_INITVAR_DISABLED)
#define SCIHOOK_TRIGGER_INITVAR_BEFORE \
std::shared_ptr<RiderInitVarExecutionContext> ctx(new RiderInitVarExecutionContext("InitVarExecutionContext", &vars, dim));\
SciHook::trigger(INITVAR_BEFORE, ctx);
#define SCIHOOK_TRIGGER_INITVAR_AFTER SciHook::trigger(INITVAR_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_INITVAR_BEFORE
#define SCIHOOK_TRIGGER_INITVAR_AFTER
#endif

#endif // CAS_TEST_RIDER___RIDERSERVICEMACROS_H
