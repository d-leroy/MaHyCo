#include "eos/perfectgas/PerfectGasPAccService.h"
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

PerfectGasPAccService::
PerfectGasPAccService(const ServiceBuildInfo& bi)
: PerfectGasPAccServiceBase<PerfectGasPAccService>(bi)
{
    m_acc_env = ServiceBuilder<IAccEnv>(subDomain()).getSingleton();
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

PerfectGasPAccService::
~PerfectGasPAccService()
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

void PerfectGasPAccService::
initEOS(PerfectGasPAccInitEOSVars& vars, ::Arcane::Materials::IMeshEnvironment* env)
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

void PerfectGasPAccService::
applyEOS(PerfectGasPAccApplyEOSVars& vars, ::Arcane::Materials::IMeshEnvironment* env)
{
    Arcane::Timer::Action p4gpu_function_timer(subDomain(), "PerfectGasPAcc::applyEOS");
    Real adiabatic_cst = getAdiabaticCst();
    // Mailles pures
    auto queue_pur = m_acc_env->newQueue();
    queue_pur.setAsync(true);
    {
        auto command = makeCommand(queue_pur);

        // Nombre de mailles pures de l'environnement
        Integer nb_pur = env->pureEnvItems().nbItem();

        // Pour les mailles pures, valueIndexes() est la liste des ids locaux des mailles
        Span<const Int32> in_cell_id(env->pureEnvItems().valueIndexes());

        auto in_density         = ax::viewIn(command, vars.m_density.globalVariable());
        auto in_internal_energy = ax::viewIn(command, vars.m_internal_energy.globalVariable());

        auto out_pressure    = ax::viewOut(command, vars.m_pressure.globalVariable());
        auto out_sound_speed = ax::viewOut(command, vars.m_sound_speed.globalVariable());
        auto out_dpde        = ax::viewOut(command, vars.m_dpde.globalVariable());

        command << RUNCOMMAND_LOOP1(iter, nb_pur) {
        auto [ipur] = iter(); // ipur \in [0,nb_pur[
        CellLocalId cid(in_cell_id[ipur]); // accés indirect à la valeur de la maille

        Real pressure, sound_speed, dpde;

        compute_pressure_sndspd_PG(adiabatic_cst,
            in_density[cid], in_internal_energy[cid],
            pressure, sound_speed, dpde);

        out_pressure[cid] = pressure;
        out_sound_speed[cid] = sound_speed;
        out_dpde[cid] = dpde;

        }; // non-bloquant et asynchrone par rapport au CPU et autres queues
    }

    // Mailles mixtes
    auto queue_mix = m_acc_env->newQueue();
    queue_mix.setAsync(true);
    {
        auto command = makeCommand(queue_mix);

        // Pour les mailles impures (mixtes), liste des indices valides 
        Span<const Int32> in_imp_idx(env->impureEnvItems().valueIndexes());
        Integer nb_imp = in_imp_idx.size();

        Span<const Real> in_density         (envView(vars.m_density, env));
        Span<const Real> in_internal_energy (envView(vars.m_internal_energy, env));

        Span<Real> out_pressure    (envView(vars.m_pressure, env));
        Span<Real> out_sound_speed (envView(vars.m_sound_speed, env));
        Span<Real> out_dpde        (envView(vars.m_dpde, env));

        command << RUNCOMMAND_LOOP1(iter, nb_imp) {
        auto imix = in_imp_idx[iter()[0]]; // iter()[0] \in [0,nb_imp[

        compute_pressure_sndspd_PG(adiabatic_cst,
            in_density[imix], in_internal_energy[imix],
            out_pressure[imix], out_sound_speed[imix], out_dpde[imix]);

        }; // non-bloquant et asynchrone par rapport au CPU et autres queues
    }
    queue_pur.barrier();
    queue_mix.barrier();
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void PerfectGasPAccService::
applyOneCellEOS(PerfectGasPAccApplyOneCellEOSVars& vars, const ::Arcane::Materials::IMeshEnvironment* env, const EnvCell ev)
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

ARCANE_REGISTER_SERVICE_PERFECTGASPACC(PerfectGasPAcc, PerfectGasPAccService);

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace EosPerfectgas
