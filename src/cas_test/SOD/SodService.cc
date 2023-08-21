#include "cas_test/SOD/SodService.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

namespace Cas_testSOD {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

SodService::
SodService(const ServiceBuildInfo& bi)
: SodServiceBase<SodService>(bi)
{
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

SodService::
~SodService()
{
}
	

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void SodService::
initMatMono(SodInitMatMonoVars& vars, [[maybe_unused]] const Integer dim)
{
  ENUMERATE_CELL(icell, allCells()) {
    Cell cell = *icell;
    vars.m_materiau[cell] = 0.;
  }
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void SodService::
initVarMono(SodInitVarMonoVars& vars, [[maybe_unused]] const Integer dim)
{
  // mise à zero puis initialisation des fractions de masses et volumes
  vars.m_mass_fraction.fill(0.0);
  vars.m_fracvol.fill(0.0);
  ENUMERATE_CELL(icell, allCells()) {
    Cell cell = *icell;
    double r(0.);
    double pInit;
    double rhoInit;
    if (getCasTest() == Cas_test::Test::SodCaseX) r = vars.m_cell_coord[cell].x;
    if (getCasTest() == Cas_test::Test::SodCaseY) r = vars.m_cell_coord[cell].y;
    if (getCasTest() == Cas_test::Test::SodCaseZ) r = vars.m_cell_coord[cell].z;
    if (r < 0.5) {
      pInit = 1.0;
      rhoInit = 1.0;
    } else {
      pInit = 0.1;
      rhoInit = 0.125;
    }
    vars.m_density[cell] = rhoInit;
    vars.m_pressure[cell] = pInit;
    vars.m_fracvol[cell] = 1.;
    vars.m_mass_fraction[cell] = 1.;
  }
  ENUMERATE_NODE(inode, allNodes()){
    vars.m_velocity[inode] = {0.0, 0.0, 0.0};
  }
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void SodService::
initMat(SodInitMatVars& vars, [[maybe_unused]] const Integer dim)
{
  if (getCasTest() == Cas_test::Test::SodCaseX ||
       getCasTest() == Cas_test::Test::SodCaseY ||
       getCasTest() == Cas_test::Test::SodCaseZ) {
        SodServiceBase<SodService>::initMatMono(dim);
        return;
  }
  ENUMERATE_CELL(icell, allCells()) {
    Cell cell = *icell;
    double r(0.);
    if (getCasTest() == Cas_test::Test::BiSodCaseX) r = vars.m_cell_coord[cell].x;
    if (getCasTest() == Cas_test::Test::BiSodCaseY) r = vars.m_cell_coord[cell].y;
    if (getCasTest() == Cas_test::Test::BiSodCaseZ) r = vars.m_cell_coord[cell].z;
    if (getCasTest() == Cas_test::Test::BiSodSph) 
    {
      const Real x = vars.m_cell_coord[cell].x;
      const Real y = vars.m_cell_coord[cell].y;
      const Real z = vars.m_cell_coord[cell].z;
      r = std::sqrt(x*x + y*y + z*z);
    }
    if (r < 0.5) {
      vars.m_materiau[cell] = 0.;
      // vars.m_materiau[cell] = 0.9;
    } else {
      vars.m_materiau[cell] = 1.;
      // vars.m_materiau[cell] = 0.1;
    }
  }
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void SodService::
initVar(SodInitVarVars& vars, [[maybe_unused]] const Integer dim)
{
  if (getCasTest() == Cas_test::Test::SodCaseX ||
       getCasTest() == Cas_test::Test::SodCaseY ||
       getCasTest() == Cas_test::Test::SodCaseZ) {
        SodServiceBase<SodService>::initVarMono(dim);
        return;
 }
 
 // mise à zero puis initialisation des fractions de masses et volumes
 vars.m_mass_fraction.fill(0.0);
 vars.m_fracvol.fill(0.0);
 CellToAllEnvCellConverter all_env_cell_converter(IMeshMaterialMng::getReference(mesh()));
 ENUMERATE_CELL(icell,allCells()) {
    Cell cell = *icell;
    AllEnvCell all_env_cell = all_env_cell_converter[cell]; 
    double r(0.);
    if (getCasTest() == Cas_test::Test::BiSodCaseX) r = vars.m_cell_coord[cell].x;
    if (getCasTest() == Cas_test::Test::BiSodCaseY) r = vars.m_cell_coord[cell].y;
    if (getCasTest() == Cas_test::Test::BiSodCaseZ) r = vars.m_cell_coord[cell].z;
    if (getCasTest() == Cas_test::Test::BiSodSph) 
    {
      const Real x = vars.m_cell_coord[cell].x;
      const Real y = vars.m_cell_coord[cell].y;
      const Real z = vars.m_cell_coord[cell].z;
      r = std::sqrt(x*x + y*y + z*z);
    }
    if (r < 0.5) {
      vars.m_density[cell] = 1.0;
      vars.m_pressure[cell] = 1.0;
      vars.m_fracvol[cell] = 1.;
      vars.m_mass_fraction[cell] = 1.;
      if (all_env_cell.nbEnvironment() !=1) {
        ENUMERATE_CELL_ENVCELL(ienvcell,all_env_cell) {
          EnvCell ev = *ienvcell;  
          // Integer index_env = ev.environmentId();  
            vars.m_density[ev] = 1.0;
            vars.m_pressure[ev] = 1.0;
            // ajout mailles mixtes partouts
            // vars.m_fracvol[ev] = 0.5 * (1-index_env) + 0.5 * index_env;
            // vars.m_mass_fraction[ev] = 0.5 * (1-index_env) + 0.5 * index_env;
            
        }
      }
    } else {
      vars.m_density[cell] = 0.125;
      vars.m_pressure[cell] = 0.1;
      vars.m_fracvol[cell] = 1.;
      vars.m_mass_fraction[cell] = 1.;
      if (all_env_cell.nbEnvironment() !=1) {
        ENUMERATE_CELL_ENVCELL(ienvcell,all_env_cell) {
          EnvCell ev = *ienvcell;  
          // Integer index_env = ev.environmentId();  
            vars.m_density[ev] = 0.125;
            vars.m_pressure[ev] = 0.1;
            // ajout mailles mixtes partouts
            // vars.m_fracvol[ev] = 0.5 * index_env + 0.5 * (1-index_env);
            // vars.m_mass_fraction[ev] = 0.5 * index_env + 0.5 * (1-index_env);
        }
      }
    }
  }
  ENUMERATE_NODE(inode, allNodes()){
    vars.m_velocity[inode] = {0.0, 0.0, 0.0};
  }
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

ARCANE_REGISTER_SERVICE_SOD(Sod, SodService);

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace Cas_testSOD
