#include "eos/perfectgas/PerfectGasAccWithSupportService.h"
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

PerfectGasAccWithSupportService::
PerfectGasAccWithSupportService(const ServiceBuildInfo& bi)
: PerfectGasAccWithSupportServiceBase<PerfectGasAccWithSupportService>(bi)
{
    m_acc_env = ServiceBuilder<IAccEnv>(subDomain()).getSingleton();
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

PerfectGasAccWithSupportService::
~PerfectGasAccWithSupportService()
{
}

/*---------------------------------------------------------------------------*/
/* Formule PerfectGas pour calculer unitairement pression, vitesse du son et dp/de */
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

ARCCORE_HOST_DEVICE inline
void PerfectGasAccWithSupportApplyEOSWithSupportViews::
apply(ComponentItemLocalId iid) const
{
    this->inout_pressure[iid]    = (this->in_adiabatic_cst - 1.) * this->in_density[iid] * this->in_internal_energy[iid];
    this->out_sound_speed[iid] = sqrt(this->in_adiabatic_cst * this->inout_pressure[iid] / this->in_density[iid]);
    this->out_dpde[iid]        = (this->in_adiabatic_cst - 1.) * this->in_density[iid];
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void PerfectGasAccWithSupportService::
initEOS(PerfectGasAccWithSupportInitEOSVars& vars, ::Arcane::Materials::IMeshEnvironment* env)
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

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void PerfectGasAccWithSupportService::
applyEOS(PerfectGasAccWithSupportApplyEOSVars& vars, ::Arcane::Materials::IMeshEnvironment* env)
{
    Arcane::Timer::Action p4gpu_function_timer(subDomain(), "PerfectGasAccWithSupport::applyEOS");
    PerfectGasAccWithSupportServiceBase<PerfectGasAccWithSupportService>::applyEOSWithSupport(env->envView(), env);
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void PerfectGasAccWithSupportService::
applyOneCellEOS(PerfectGasAccWithSupportApplyOneCellEOSVars& vars, const ::Arcane::Materials::IMeshEnvironment* env, const EnvCell ev)
{
    Real adiabatic_cst = getAdiabaticCst();
    // Calcul de la pression et de la vitesse du son
    if (vars.m_density[ev] == 0.) info() << ev.globalCell().localId() << " densité nulle";
    compute_pressure_sndspd_PG(adiabatic_cst,
        vars.m_density[ev], vars.m_internal_energy[ev],
        vars.m_pressure[ev], vars.m_sound_speed[ev], m_dpde[ev]);
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

ARCANE_REGISTER_SERVICE_PERFECTGASACCWITHSUPPORT(PerfectGasAccWithSupport, PerfectGasAccWithSupportService);

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace EosPerfectgas
