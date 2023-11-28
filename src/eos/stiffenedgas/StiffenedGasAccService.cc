#include "eos/stiffenedgas/StiffenedGasAccService.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

namespace EosStiffenedgas
{

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

StiffenedGasAccService::
    StiffenedGasAccService(const ServiceBuildInfo &bi)
    : StiffenedGasAccServiceBase<StiffenedGasAccService>(bi)
{
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

StiffenedGasAccService::
    ~StiffenedGasAccService()
{
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void StiffenedGasAccService::
    initEOS(StiffenedGasAccInitEOSVars &vars, ::Arcane::Materials::IMeshEnvironment *env)
{
    // Initialise l'énergie et la vitesse du son
    Real limit_tension = getTensionLimitCst();
    Real adiabatic_cst = getAdiabaticCst();
    ENUMERATE_ENVCELL(ienvcell,env)
    {
        EnvCell envcell = *ienvcell;
        Real pressure = vars.m_pressure[envcell];
        Real density = vars.m_density[envcell];
        vars.m_internal_energy[envcell] = (pressure + (adiabatic_cst * limit_tension)) / ((adiabatic_cst - 1.) * density);
        vars.m_sound_speed[envcell] = sqrt((adiabatic_cst / density) * (pressure + limit_tension));
    }
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

ARCCORE_HOST_DEVICE inline
void StiffenedGasAccApplyEOSWithSupportViews::
apply(ComponentItemLocalId iid) const
{
    Real internal_energy = this->in_internal_energy[iid];
    Real density = this->in_density[iid];
    Real pressure = ((this->in_adiabatic_cst - 1.) * this->in_density[iid] * this->in_internal_energy[iid]) - (this->in_adiabatic_cst * this->in_tension_limit_cst);
    this->out_pressure[iid] = pressure;
    this->out_sound_speed[iid] = sqrt((this->in_adiabatic_cst/density)*(pressure+this->in_tension_limit_cst));
    this->out_dpde[iid] = (this->in_adiabatic_cst - 1.) * density;
}

void StiffenedGasAccService::
applyEOS(StiffenedGasAccApplyEOSVars& vars, ::Arcane::Materials::IMeshEnvironment* env)
{
    StiffenedGasAccServiceBase<StiffenedGasAccService>::applyEOSWithSupport(env->envView(), env);
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void StiffenedGasAccService::
    applyOneCellEOS(StiffenedGasAccApplyOneCellEOSVars &vars, const ::Arcane::Materials::IMeshEnvironment *env, const EnvCell ev)
{
    // Calcul de la pression et de la vitesse du son
    Real limit_tension = getTensionLimitCst();
    Real adiabatic_cst = getAdiabaticCst();
    Real internal_energy = vars.m_internal_energy[ev];
    Real density = vars.m_density[ev];
    Real pressure = ((adiabatic_cst - 1.) * density * internal_energy) - (adiabatic_cst * limit_tension);
    vars.m_pressure[ev] = pressure;
    vars.m_sound_speed[ev] = sqrt((adiabatic_cst/density)*(pressure+limit_tension));
    vars.m_dpde[ev] = (adiabatic_cst - 1.) * density;
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

ARCANE_REGISTER_SERVICE_STIFFENEDGASACC(StiffenedGasAcc, StiffenedGasAccService);

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

} // namespace EosStiffenedgas
