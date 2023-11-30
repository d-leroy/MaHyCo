#include "eos/perfectgas/PerfectGasWithSupportService.h"
#include "arcane/VariableView.h"
#include "arcane/ServiceBuilder.h"
#include "arcane/ISubDomain.h"
#include "arcane/ITimeStats.h"
#include "arcane/Timer.h"

#include <accenv/IAccEnv.h>

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
using namespace Arcane;
using namespace Arcane::Materials;
namespace EosPerfectgas {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

PerfectGasWithSupportService::
PerfectGasWithSupportService(const ServiceBuildInfo& bi)
: PerfectGasWithSupportServiceBase<PerfectGasWithSupportService>(bi)
{
    m_acc_env = ServiceBuilder<IAccEnv>(subDomain()).getSingleton();
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

PerfectGasWithSupportService::
~PerfectGasWithSupportService()
{
}

/*---------------------------------------------------------------------------*/
/* Formule PerfectGasWithSupport pour calculer unitairement pression, vitesse du son et dp/de */
/* Cette formule est appelée dans applyEOS(...) et applyOneCellEOS(...)      */
/*---------------------------------------------------------------------------*/
ARCCORE_HOST_DEVICE inline void compute_pressure_sndspd_PG(Real adiabatic_cst,
    Real density, Real internal_energy,
    Real& pressure, Real& sound_speed, Real& dpde) 
{
  pressure = (adiabatic_cst - 1.) * density * internal_energy;
  sound_speed = sqrt(adiabatic_cst * pressure / density);
  dpde = (adiabatic_cst - 1.) * density;
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void PerfectGasWithSupportService::
initEOS(PerfectGasWithSupportInitEOSVars& vars, ::Arcane::Materials::IMeshEnvironment* env)
{
    Real adiabatic_cst = getAdiabaticCst();
    // Initialise l'énergie et la vitesse du son
    ENUMERATE_ENVCELL(ienvcell,env)
    {
        EnvCell envcell = *ienvcell;
        Real pressure = vars.m_pressure[envcell];
        Real density = vars.m_density[envcell];
        vars.m_internal_energy[envcell] = pressure / ((adiabatic_cst - 1.) * density);
        vars.m_sound_speed[envcell] = sqrt(adiabatic_cst * pressure / density);
    }
}


void PerfectGasWithSupportService::
applyEOSWithSupport(const EnvCell envcell, PerfectGasWithSupportApplyEOSWithSupportVars& vars, ::Arcane::Materials::IMeshEnvironment* env)
{
    if (vars.m_density[envcell] == 0.) info() << envcell.globalCell().localId() << " densité nulle";
    // TODO: include in vars
    // Real adiabatic_cst = getAdiabaticCst();
    compute_pressure_sndspd_PG(1.4, vars.m_density[envcell], vars.m_internal_energy[envcell], vars.m_pressure[envcell], vars.m_sound_speed[envcell], vars.m_dpde[envcell]);
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void PerfectGasWithSupportService::
applyEOS(PerfectGasWithSupportApplyEOSVars& vars, ::Arcane::Materials::IMeshEnvironment* env)
{
    Arcane::Timer::Action p4gpu_function_timer(subDomain(), "PerfectGasWithSupport::applyEOS");
    PerfectGasWithSupportServiceBase<PerfectGasWithSupportService>::applyEOSWithSupport(env->envView(), env);
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void PerfectGasWithSupportService::
applyOneCellEOS(PerfectGasWithSupportApplyOneCellEOSVars& vars, const ::Arcane::Materials::IMeshEnvironment* env, const EnvCell ev)
{
    Real adiabatic_cst = getAdiabaticCst();
    // Calcul de la pression et de la vitesse du son
    Real internal_energy = vars.m_internal_energy[ev];
    Real density = vars.m_density[ev];
    if (density == 0.) info() << ev.globalCell().localId() << " densité " << density;
    Real pressure = (adiabatic_cst - 1.) * density * internal_energy;
    vars.m_pressure[ev] = pressure;
    vars.m_sound_speed[ev] = sqrt(adiabatic_cst * pressure / density);
    vars.m_dpde[ev] = (adiabatic_cst - 1.) * density;
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

ARCANE_REGISTER_SERVICE_PERFECTGASWITHSUPPORT(PerfectGasWithSupport, PerfectGasWithSupportService);

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace EosPerfectgas
