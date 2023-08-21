#ifndef EOS_STIFFENEDGAS___STIFFENEDGASSERVICEMACROS_H
#define EOS_STIFFENEDGAS___STIFFENEDGASSERVICEMACROS_H

#include "scihook/scihookdefs.h"
#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_EOS_STIFFENEDGAS_STIFFENEDGAS_DISABLED)
#include "SciHook.h"
#include "eos/stiffenedgas/__StiffenedGasServiceContexts.h"
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_EOS_STIFFENEDGAS_STIFFENEDGAS_DISABLED)
#define SCIHOOK_DECLARE_EOS_STIFFENEDGAS_STIFFENEDGAS_EVENTS \
private:\
 size_t INITEOS_BEFORE;\
 size_t INITEOS_AFTER;\
 size_t APPLYEOS_BEFORE;\
 size_t APPLYEOS_AFTER;\
 size_t APPLYONECELLEOS_BEFORE;\
 size_t APPLYONECELLEOS_AFTER;
#define SCIHOOK_INITIALIZE_EOS_STIFFENEDGAS_STIFFENEDGAS_EVENTS \
INITEOS_BEFORE = SciHook::register_base_event("StiffenedGas.InitEOS.Before");\
INITEOS_AFTER = SciHook::register_base_event("StiffenedGas.InitEOS.After");\
APPLYEOS_BEFORE = SciHook::register_base_event("StiffenedGas.ApplyEOS.Before");\
APPLYEOS_AFTER = SciHook::register_base_event("StiffenedGas.ApplyEOS.After");\
APPLYONECELLEOS_BEFORE = SciHook::register_base_event("StiffenedGas.ApplyOneCellEOS.Before");\
APPLYONECELLEOS_AFTER = SciHook::register_base_event("StiffenedGas.ApplyOneCellEOS.After");
#else
#define SCIHOOK_DECLARE_EOS_STIFFENEDGAS_STIFFENEDGAS_EVENTS
#define SCIHOOK_INITIALIZE_EOS_STIFFENEDGAS_STIFFENEDGAS_EVENTS
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_EOS_STIFFENEDGAS_STIFFENEDGAS_DISABLED) && not defined(SCIHOOK_EOS_STIFFENEDGAS_STIFFENEDGAS_INITEOS_DISABLED)
#define SCIHOOK_TRIGGER_INITEOS_BEFORE \
std::shared_ptr<StiffenedGasInitEOSExecutionContext> ctx(new StiffenedGasInitEOSExecutionContext("InitEOSExecutionContext", &vars, env));\
SciHook::trigger(INITEOS_BEFORE, ctx);
#define SCIHOOK_TRIGGER_INITEOS_AFTER SciHook::trigger(INITEOS_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_INITEOS_BEFORE
#define SCIHOOK_TRIGGER_INITEOS_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_EOS_STIFFENEDGAS_STIFFENEDGAS_DISABLED) && not defined(SCIHOOK_EOS_STIFFENEDGAS_STIFFENEDGAS_APPLYEOS_DISABLED)
#define SCIHOOK_TRIGGER_APPLYEOS_BEFORE \
std::shared_ptr<StiffenedGasApplyEOSExecutionContext> ctx(new StiffenedGasApplyEOSExecutionContext("ApplyEOSExecutionContext", &vars, env));\
SciHook::trigger(APPLYEOS_BEFORE, ctx);
#define SCIHOOK_TRIGGER_APPLYEOS_AFTER SciHook::trigger(APPLYEOS_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_APPLYEOS_BEFORE
#define SCIHOOK_TRIGGER_APPLYEOS_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_EOS_STIFFENEDGAS_STIFFENEDGAS_DISABLED) && not defined(SCIHOOK_EOS_STIFFENEDGAS_STIFFENEDGAS_APPLYONECELLEOS_DISABLED)
#define SCIHOOK_TRIGGER_APPLYONECELLEOS_BEFORE \
std::shared_ptr<StiffenedGasApplyOneCellEOSExecutionContext> ctx(new StiffenedGasApplyOneCellEOSExecutionContext("ApplyOneCellEOSExecutionContext", &vars, env, ev));\
SciHook::trigger(APPLYONECELLEOS_BEFORE, ctx);
#define SCIHOOK_TRIGGER_APPLYONECELLEOS_AFTER SciHook::trigger(APPLYONECELLEOS_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_APPLYONECELLEOS_BEFORE
#define SCIHOOK_TRIGGER_APPLYONECELLEOS_AFTER
#endif

#endif // EOS_STIFFENEDGAS___STIFFENEDGASSERVICEMACROS_H
