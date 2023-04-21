#include "eos/stiffenedgas/StiffenedGasService.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

namespace EosStiffenedgas
{

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

StiffenedGasService::
    StiffenedGasService(const ServiceBuildInfo &bi)
    : StiffenedGasServiceBase<StiffenedGasService>(bi)
{
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

StiffenedGasService::
    ~StiffenedGasService()
{
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void StiffenedGasService::
    initEOS(StiffenedGasInitEOSVars &vars, ::Arcane::Materials::IMeshEnvironment *env)
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

void StiffenedGasService::
    applyEOS(StiffenedGasApplyEOSVars &vars, ::Arcane::Materials::IMeshEnvironment *env)
{
    // Calcul de la pression et de la vitesse du son
    Real limit_tension = getTensionLimitCst();
    Real adiabatic_cst = getAdiabaticCst();
    ENUMERATE_ENVCELL(ienvcell,env)
    {
        EnvCell envcell = *ienvcell;
        Real internal_energy = vars.m_internal_energy[envcell];
        Real density = vars.m_density[envcell];
        Real pressure = ((adiabatic_cst - 1.) * density * internal_energy) - (adiabatic_cst * limit_tension);
        vars.m_pressure[envcell] = pressure;
        vars.m_sound_speed[envcell] = sqrt((adiabatic_cst/density)*(pressure+limit_tension));
        vars.m_dpde[envcell] = (adiabatic_cst - 1.) * density;
    }
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void StiffenedGasService::
    applyOneCellEOS(StiffenedGasApplyOneCellEOSVars &vars, const ::Arcane::Materials::IMeshEnvironment *env, const EnvCell ev)
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

ARCANE_REGISTER_SERVICE_STIFFENEDGAS(StiffenedGas, StiffenedGasService);

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

} // namespace EosStiffenedgas
