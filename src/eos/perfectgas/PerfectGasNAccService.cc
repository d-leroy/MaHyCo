#include "eos/perfectgas/PerfectGasNAccService.h"
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
namespace ax = Arcane::Accelerator;
namespace EosPerfectgas {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

PerfectGasNAccService::
PerfectGasNAccService(const ServiceBuildInfo& bi)
: PerfectGasNAccServiceBase<PerfectGasNAccService>(bi)
{
    m_acc_env = ServiceBuilder<IAccEnv>(subDomain()).getSingleton();
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

PerfectGasNAccService::
~PerfectGasNAccService()
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

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void PerfectGasNAccService::
initEOS(PerfectGasNAccInitEOSVars& vars, ::Arcane::Materials::IMeshEnvironment* env)
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

void PerfectGasNAccService::
applyEOS(PerfectGasNAccApplyEOSVars& vars, ::Arcane::Materials::IMeshEnvironment* env)
{
    Arcane::Timer::Action p4gpu_function_timer(subDomain(), "PerfectGasNAcc::applyEOS");
    auto queue = m_acc_env->newQueue();
    auto command = makeCommand(queue);
    auto in_density = ax::viewIn(command, m_density);
    auto in_internal_energy = ax::viewIn(command, m_internal_energy);
    auto in_adiabatic_cst = getAdiabaticCst();
    auto inout_pressure = ax::viewInOut(command, m_pressure);
    auto out_sound_speed = ax::viewOut(command, m_sound_speed);
    auto out_dpde = ax::viewOut(command, m_dpde);
    command << RUNCOMMAND_MAT_ENUMERATE(EnvCell, iid, env->envView()) {
        inout_pressure[iid] = (in_adiabatic_cst - 1.) * in_density[iid] * in_internal_energy[iid];
        out_sound_speed[iid] = sqrt(in_adiabatic_cst * inout_pressure[iid] / in_density[iid]);
        out_dpde[iid] = (in_adiabatic_cst - 1.) * in_density[iid];
    };
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void PerfectGasNAccService::
applyOneCellEOS(PerfectGasNAccApplyOneCellEOSVars& vars, const ::Arcane::Materials::IMeshEnvironment* env, const EnvCell ev)
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

ARCANE_REGISTER_SERVICE_PERFECTGASNACC(PerfectGasNAcc, PerfectGasNAccService);

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace EosPerfectgas
