#ifndef REMAP_ALE___REMAPALESERVICESCIHOOKMACROS_H
#define REMAP_ALE___REMAPALESERVICESCIHOOKMACROS_H

#include "scihook/scihookdefs.h"
#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_ALE_REMAPALE_DISABLED)
#include "SciHook.h"
#include "remap/ale/__RemapALEServiceContexts.h"
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_ALE_REMAPALE_DISABLED)
#define SCIHOOK_DECLARE_REMAP_ALE_REMAPALE_EVENTS \
private:\
 size_t APPLIREMAP_BEFORE;\
 size_t APPLIREMAP_AFTER;\
 size_t RESIZEREMAPVARIABLES_BEFORE;\
 size_t RESIZEREMAPVARIABLES_AFTER;\
 size_t SYNCHRONIZEUREMAP_BEFORE;\
 size_t SYNCHRONIZEUREMAP_AFTER;\
 size_t REMAPVARIABLES_BEFORE;\
 size_t REMAPVARIABLES_AFTER;
#define SCIHOOK_INITIALIZE_REMAP_ALE_REMAPALE_EVENTS \
APPLIREMAP_BEFORE = SciHook::register_base_event("RemapALE.AppliRemap.Before");\
APPLIREMAP_AFTER = SciHook::register_base_event("RemapALE.AppliRemap.After");\
RESIZEREMAPVARIABLES_BEFORE = SciHook::register_base_event("RemapALE.ResizeRemapVariables.Before");\
RESIZEREMAPVARIABLES_AFTER = SciHook::register_base_event("RemapALE.ResizeRemapVariables.After");\
SYNCHRONIZEUREMAP_BEFORE = SciHook::register_base_event("RemapALE.SynchronizeUremap.Before");\
SYNCHRONIZEUREMAP_AFTER = SciHook::register_base_event("RemapALE.SynchronizeUremap.After");\
REMAPVARIABLES_BEFORE = SciHook::register_base_event("RemapALE.RemapVariables.Before");\
REMAPVARIABLES_AFTER = SciHook::register_base_event("RemapALE.RemapVariables.After");
#else
#define SCIHOOK_DECLARE_REMAP_ALE_REMAPALE_EVENTS
#define SCIHOOK_INITIALIZE_REMAP_ALE_REMAPALE_EVENTS
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_ALE_REMAPALE_DISABLED) && not defined(SCIHOOK_REMAP_ALE_REMAPALE_APPLIREMAP_DISABLED)
#define SCIHOOK_TRIGGER_REMAP_ALE_REMAPALE_APPLIREMAP_BEFORE \
std::shared_ptr<RemapALEAppliRemapExecutionContext> ctx(new RemapALEAppliRemapExecutionContext("AppliRemapExecutionContext", dimension, withDualProjection, nb_vars_to_project, nb_env));\
SciHook::trigger(APPLIREMAP_BEFORE, ctx);
#define SCIHOOK_TRIGGER_REMAP_ALE_REMAPALE_APPLIREMAP_AFTER SciHook::trigger(APPLIREMAP_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_REMAP_ALE_REMAPALE_APPLIREMAP_BEFORE
#define SCIHOOK_TRIGGER_REMAP_ALE_REMAPALE_APPLIREMAP_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_ALE_REMAPALE_DISABLED) && not defined(SCIHOOK_REMAP_ALE_REMAPALE_RESIZEREMAPVARIABLES_DISABLED)
#define SCIHOOK_TRIGGER_REMAP_ALE_REMAPALE_RESIZEREMAPVARIABLES_BEFORE \
std::shared_ptr<RemapALEResizeRemapVariablesExecutionContext> ctx(new RemapALEResizeRemapVariablesExecutionContext("ResizeRemapVariablesExecutionContext", nb_vars_to_project, nb_env));\
SciHook::trigger(RESIZEREMAPVARIABLES_BEFORE, ctx);
#define SCIHOOK_TRIGGER_REMAP_ALE_REMAPALE_RESIZEREMAPVARIABLES_AFTER SciHook::trigger(RESIZEREMAPVARIABLES_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_REMAP_ALE_REMAPALE_RESIZEREMAPVARIABLES_BEFORE
#define SCIHOOK_TRIGGER_REMAP_ALE_REMAPALE_RESIZEREMAPVARIABLES_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_ALE_REMAPALE_DISABLED) && not defined(SCIHOOK_REMAP_ALE_REMAPALE_SYNCHRONIZEUREMAP_DISABLED)
#define SCIHOOK_TRIGGER_REMAP_ALE_REMAPALE_SYNCHRONIZEUREMAP_BEFORE \
std::shared_ptr<SciHook::SciHookExecutionContext> ctx(new SciHook::SciHookExecutionContext("SynchronizeUremapExecutionContext"));\
SciHook::trigger(SYNCHRONIZEUREMAP_BEFORE, ctx);
#define SCIHOOK_TRIGGER_REMAP_ALE_REMAPALE_SYNCHRONIZEUREMAP_AFTER SciHook::trigger(SYNCHRONIZEUREMAP_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_REMAP_ALE_REMAPALE_SYNCHRONIZEUREMAP_BEFORE
#define SCIHOOK_TRIGGER_REMAP_ALE_REMAPALE_SYNCHRONIZEUREMAP_AFTER
#endif

#if defined(SCIHOOK_ENABLED) && not defined(SCIHOOK_REMAP_ALE_REMAPALE_DISABLED) && not defined(SCIHOOK_REMAP_ALE_REMAPALE_REMAPVARIABLES_DISABLED)
#define SCIHOOK_TRIGGER_REMAP_ALE_REMAPALE_REMAPVARIABLES_BEFORE \
std::shared_ptr<RemapALERemapVariablesExecutionContext> ctx(new RemapALERemapVariablesExecutionContext("RemapVariablesExecutionContext", dimension, withDualProjection, nb_vars_to_project, nb_env));\
SciHook::trigger(REMAPVARIABLES_BEFORE, ctx);
#define SCIHOOK_TRIGGER_REMAP_ALE_REMAPALE_REMAPVARIABLES_AFTER SciHook::trigger(REMAPVARIABLES_AFTER, ctx);
#else
#define SCIHOOK_TRIGGER_REMAP_ALE_REMAPALE_REMAPVARIABLES_BEFORE
#define SCIHOOK_TRIGGER_REMAP_ALE_REMAPALE_REMAPVARIABLES_AFTER
#endif

#endif // REMAP_ALE___REMAPALESERVICESCIHOOKMACROS_H
