#include "eos/perfectgas/PerfectGasService.h"
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

PerfectGasService::
PerfectGasService(const ServiceBuildInfo& bi)
: PerfectGasServiceBase<PerfectGasService>(bi)
{
    m_acc_env = ServiceBuilder<IAccEnv>(subDomain()).getSingleton();
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

PerfectGasService::
~PerfectGasService()
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
void PerfectGasApplyEOSViews::
apply(ComponentItemLocalId iid) const
{
    this->inout_pressure[iid]    = (this->in_adiabatic_cst - 1.) * this->in_density[iid] * this->in_internal_energy[iid];
    this->out_sound_speed[iid] = sqrt(this->in_adiabatic_cst * this->inout_pressure[iid] / this->in_density[iid]);
    this->out_dpde[iid]        = (this->in_adiabatic_cst - 1.) * this->in_density[iid];
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void PerfectGasService::
initEOS(PerfectGasInitEOSVars& vars, ::Arcane::Materials::IMeshEnvironment* env)
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

#if 0
void PerfectGasService::
applyEOS(PerfectGasApplyEOSVars& vars, ::Arcane::Materials::IMeshEnvironment* env)
{
    Real adiabatic_cst = getAdiabaticCst();
    // Calcul de la pression et de la vitesse du son
#if 0
    ENUMERATE_ENVCELL(ienvcell,env)
    {
        EnvCell ev = *ienvcell;
        if (vars.m_density[ev] == 0.) info() << ev.globalCell().localId() << " densité nulle";
        compute_pressure_sndspd_PG(adiabatic_cst,
            vars.m_density[ev], vars.m_internal_energy[ev],
            vars.m_pressure[ev], vars.m_sound_speed[ev], vars.m_dpde[ev]);
    }
#elif 0
    Parallel::Foreach(env->envView(),[&](EnvItemVectorView view)
    {
        ENUMERATE_ENVCELL(ienvcell,view){
        compute_pressure_sndspd_PG(adiabatic_cst,
            vars.m_density[ienvcell], vars.m_internal_energy[ienvcell],
            vars.m_pressure[ienvcell], vars.m_sound_speed[ienvcell], vars.m_dpde[ienvcell]);
        }
    });
#else
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
#endif
}
#endif

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void PerfectGasService::
applyOneCellEOS(PerfectGasApplyOneCellEOSVars& vars, const ::Arcane::Materials::IMeshEnvironment* env, const EnvCell ev)
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

ARCANE_REGISTER_SERVICE_PERFECTGAS(PerfectGas, PerfectGasService);

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace EosPerfectgas
