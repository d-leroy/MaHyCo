#include "eos/perfectgas/PerfectGasAccService.h"
#include "arcane/VariableView.h"
#include "arcane/ServiceBuilder.h"

#include <accenv/IAccEnv.h>

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
using namespace Arcane;
using namespace Arcane::Materials;
namespace EosPerfectgas {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

PerfectGasAccService::
PerfectGasAccService(const ServiceBuildInfo& bi)
: PerfectGasAccServiceBase<PerfectGasAccService>(bi)
{
    m_acc_env = ServiceBuilder<IAccEnv>(subDomain()).getSingleton();
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

PerfectGasAccService::
~PerfectGasAccService()
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
void PerfectGasAccApplyEOSWithSupportViews::
apply(ComponentItemLocalId iid) const
{
    this->inout_pressure[iid]    = (this->in_adiabatic_cst - 1.) * this->in_density[iid] * this->in_internal_energy[iid];
    this->out_sound_speed[iid] = sqrt(this->in_adiabatic_cst * this->inout_pressure[iid] / this->in_density[iid]);
    this->out_dpde[iid]        = (this->in_adiabatic_cst - 1.) * this->in_density[iid];
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void PerfectGasAccService::
initEOS(PerfectGasAccInitEOSVars& vars, ::Arcane::Materials::IMeshEnvironment* env)
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

void PerfectGasAccService::
applyEOS(PerfectGasAccApplyEOSVars& vars, ::Arcane::Materials::IMeshEnvironment* env)
{
    PerfectGasAccServiceBase<PerfectGasAccService>::applyEOSWithSupport(env->envView(), env);
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void PerfectGasAccService::
applyOneCellEOS(PerfectGasAccApplyOneCellEOSVars& vars, const ::Arcane::Materials::IMeshEnvironment* env, const EnvCell ev)
{
    Real adiabatic_cst = getAdiabaticCst();
    // Calcul de la pression et de la vitesse du son
#if 0
    Real internal_energy = vars.m_internal_energy[ev];
    Real density = vars.m_density[ev];
    if (density == 0.) info() << ev.globalCell().localId() << " densité " << density;
    Real pressure = (adiabatic_cst - 1.) * density * internal_energy;
    vars.m_pressure[ev] = pressure;
    vars.m_sound_speed[ev] = sqrt(adiabatic_cst * pressure / density);
    vars.m_dpde[ev] = (adiabatic_cst - 1.) * density;
#else
    if (vars.m_density[ev] == 0.) info() << ev.globalCell().localId() << " densité nulle";
    compute_pressure_sndspd_PG(adiabatic_cst,
        vars.m_density[ev], vars.m_internal_energy[ev],
        vars.m_pressure[ev], vars.m_sound_speed[ev], m_dpde[ev]);
#endif
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

ARCANE_REGISTER_SERVICE_PERFECTGASACC(PerfectGasAcc, PerfectGasAccService);

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace EosPerfectgas
