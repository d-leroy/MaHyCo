#ifndef EOS_PERFECTGAS___PERFECTGASSERVICEMACROS_H
#define EOS_PERFECTGAS___PERFECTGASSERVICEMACROS_H

#include "scihook/scihookdefs.h"
#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGAS_DISABLED)
#include "SciHook.h"
#include "eos/perfectgas/__PerfectGasServiceContexts.h"
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGAS_DISABLED)
#define SCIHOOK_DECLARE_EOS_PERFECTGAS_PERFECTGAS_EVENTS \
private:\
 size_t INITEOS_BEFORE;\
 size_t INITEOS_AFTER;\
 size_t APPLYEOS_BEFORE;\
 size_t APPLYEOS_AFTER;\
 size_t APPLYONECELLEOS_BEFORE;\
 size_t APPLYONECELLEOS_AFTER;
#define SCIHOOK_INITIALIZE_EOS_PERFECTGAS_PERFECTGAS_EVENTS \
INITEOS_BEFORE = SciHook::register_base_event("PerfectGas.InitEOS.Before");\
INITEOS_AFTER = SciHook::register_base_event("PerfectGas.InitEOS.After");\
APPLYEOS_BEFORE = SciHook::register_base_event("PerfectGas.ApplyEOS.Before");\
APPLYEOS_AFTER = SciHook::register_base_event("PerfectGas.ApplyEOS.After");\
APPLYONECELLEOS_BEFORE = SciHook::register_base_event("PerfectGas.ApplyOneCellEOS.Before");\
APPLYONECELLEOS_AFTER = SciHook::register_base_event("PerfectGas.ApplyOneCellEOS.After");
#else
#define SCIHOOK_DECLARE_EOS_PERFECTGAS_PERFECTGAS_EVENTS
#define SCIHOOK_INITIALIZE_EOS_PERFECTGAS_PERFECTGAS_EVENTS
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGAS_DISABLED) && not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGAS_INITEOS_DISABLED)
#define SCIHOOK_TRIGGER_INITEOS_BEFORE \
std::shared_ptr<PerfectGasInitEOSExecutionContext> ctx(new PerfectGasInitEOSExecutionContext("InitEOSExecutionContext", &vars, env));\
SciHook::trigger(INITEOS_BEFORE, ctx);
#define SCIHOOK_TRIGGER_INITEOS_AFTER SciHook::trigger(INITEOS_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_INITEOS_BEFORE
#define SCIHOOK_TRIGGER_INITEOS_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGAS_DISABLED) && not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGAS_APPLYEOS_DISABLED)
#define SCIHOOK_TRIGGER_APPLYEOS_BEFORE \
std::shared_ptr<PerfectGasApplyEOSExecutionContext> ctx(new PerfectGasApplyEOSExecutionContext("ApplyEOSExecutionContext", &vars, env));\
SciHook::trigger(APPLYEOS_BEFORE, ctx);
#define SCIHOOK_TRIGGER_APPLYEOS_AFTER SciHook::trigger(APPLYEOS_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_APPLYEOS_BEFORE
#define SCIHOOK_TRIGGER_APPLYEOS_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGAS_DISABLED) && not defined(SCIHOOK_EOS_PERFECTGAS_PERFECTGAS_APPLYONECELLEOS_DISABLED)
#define SCIHOOK_TRIGGER_APPLYONECELLEOS_BEFORE \
std::shared_ptr<PerfectGasApplyOneCellEOSExecutionContext> ctx(new PerfectGasApplyOneCellEOSExecutionContext("ApplyOneCellEOSExecutionContext", &vars, env, ev));\
SciHook::trigger(APPLYONECELLEOS_BEFORE, ctx);
#define SCIHOOK_TRIGGER_APPLYONECELLEOS_AFTER SciHook::trigger(APPLYONECELLEOS_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_APPLYONECELLEOS_BEFORE
#define SCIHOOK_TRIGGER_APPLYONECELLEOS_AFTER
#endif

#endif // EOS_PERFECTGAS___PERFECTGASSERVICEMACROS_H
