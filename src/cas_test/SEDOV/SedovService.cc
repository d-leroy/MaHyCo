#include "cas_test/SEDOV/SedovService.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

namespace Cas_testSEDOV {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

SedovService::
SedovService(const ServiceBuildInfo& bi)
: SedovServiceBase<SedovService>(bi)
{
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

SedovService::
~SedovService()
{
}
	

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void SedovService::
initMatMono(SedovInitMatMonoVars& vars, [[maybe_unused]] const Integer dim)
{
  ENUMERATE_CELL(icell,allCells()) {
    Cell cell = *icell;
    vars.m_materiau[cell] = 0;
  }
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void SedovService::
initVarMono(SedovInitVarMonoVars& vars, [[maybe_unused]] const Integer dim)
{
  Real3 Xb={0.0, 0.0, 0.};
  Real rhoInit = 1.;
  Real e1 = 0.244816e-5;
  Real total_energy_deposit = 0.244816;
  Real rmin(1.e-10);  // depot sur 1 maille
  Real rnode(0.);
  
    
  ENUMERATE_CELL(icell,allCells()) {
    Cell cell = *icell;
    bool isCenterCell = false;  
    vars.m_internal_energy[cell] = e1;
    vars.m_density[cell] = rhoInit;
    vars.m_fracvol[cell] = 1.;
    vars.m_mass_fraction[cell] = 1.;
    vars.m_pressure[cell] = 0.4 * rhoInit * e1;
    Real vol = vars.m_cell_volume[cell]; 
    ENUMERATE_NODE(inode, cell.nodes()) {
        if (dim == 3) rnode = std::sqrt((vars.m_node_coord[inode].x - Xb.x) *
                                       (vars.m_node_coord[inode].x- Xb.x) +
                                   (vars.m_node_coord[inode].y- Xb.y) *
                                       (vars.m_node_coord[inode].y - Xb.y)+
                                   (vars.m_node_coord[inode].z- Xb.z) *
                                       (vars.m_node_coord[inode].z - Xb.z));
        else rnode = std::sqrt((vars.m_node_coord[inode].x - Xb.x) *
                                       (vars.m_node_coord[inode].x- Xb.x) +
                                   (vars.m_node_coord[inode].y- Xb.y) *
                                       (vars.m_node_coord[inode].y - Xb.y));
      if (rnode < rmin) isCenterCell = true;
    }
    if (isCenterCell) { 
      info() << rmin << " cell " << cell.localId();
      vars.m_internal_energy[cell] += total_energy_deposit / vol;
      vars.m_pressure[cell] = 0.4 * rhoInit * vars.m_internal_energy[cell];
    }
  }
  ENUMERATE_NODE(inode, allNodes()){
    vars.m_velocity[inode] = {0.0, 0.0, 0.0};
  }
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void SedovService::
initMat(SedovInitMatVars& vars, [[maybe_unused]] const Integer dim)
{
  if (getCasTest() == Cas_test::Test::Sedov) {
    SedovServiceBase<SedovService>::initMatMono(dim);
    return;
  }

  Real3 Xb={0.0, 0.0, 0.};
  ENUMERATE_CELL(icell,allCells()) {
    Cell cell = *icell;
    Real rmin(1.e-10);  // depot sur 1 maille
    bool isCenterCell = false;  
    vars.m_materiau[cell] = 0;
    ENUMERATE_NODE(inode, cell.nodes()) {
      Real rnode = std::sqrt((vars.m_node_coord[inode].x - Xb.x) *
                                       (vars.m_node_coord[inode].x- Xb.x) +
                                   (vars.m_node_coord[inode].y- Xb.y) *
                                       (vars.m_node_coord[inode].y - Xb.y)+
                                   (vars.m_node_coord[inode].z- Xb.z) *
                                       (vars.m_node_coord[inode].z - Xb.z));
      if (rnode < rmin) isCenterCell = true;
    }
    if (isCenterCell) {
      vars.m_materiau[cell] = 1;
    }
  }
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void SedovService::
initVar(SedovInitVarVars& vars, [[maybe_unused]] const Integer dim)
{
  if (getCasTest() == Cas_test::Test::Sedov) {
    SedovServiceBase<SedovService>::initVarMono(dim);
    return;
  }

  Real3 Xb={0.0, 0.0, 0.};
  Real rhoInit = 1.;
  Real e1 = 0.244816e-5;
  Real total_energy_deposit = 0.244816;
  Real rmin(1.e-10);  // depot sur 1 maille
  Real rnode(0.);
  
  ENUMERATE_CELL(icell,allCells()) {
    Cell cell = *icell;
    bool isCenterCell = false;  
    vars.m_internal_energy[cell] = e1;
    vars.m_density[cell] = rhoInit;
    vars.m_fracvol[cell] = 1.;
    vars.m_mass_fraction[cell] = 1.;
    vars.m_pressure[cell] = 0.4 * rhoInit * e1;
    Real vol = vars.m_cell_volume[cell];
    ENUMERATE_NODE(inode, cell.nodes()) {
        if (dim == 3) rnode = std::sqrt((vars.m_node_coord[inode].x - Xb.x) *
                                       (vars.m_node_coord[inode].x- Xb.x) +
                                   (vars.m_node_coord[inode].y- Xb.y) *
                                       (vars.m_node_coord[inode].y - Xb.y)+
                                   (vars.m_node_coord[inode].z- Xb.z) *
                                       (vars.m_node_coord[inode].z - Xb.z));
        else rnode = std::sqrt((vars.m_node_coord[inode].x - Xb.x) *
                                       (vars.m_node_coord[inode].x- Xb.x) +
                                   (vars.m_node_coord[inode].y- Xb.y) *
                                       (vars.m_node_coord[inode].y - Xb.y));
      
      if (rnode < rmin) isCenterCell = true;
    }
    if (isCenterCell) { 
      vars.m_internal_energy[cell] += total_energy_deposit / vol;
      vars.m_pressure[cell] = 0.4 * rhoInit * vars.m_internal_energy[cell];
    }
  }
  ENUMERATE_NODE(inode, allNodes()){
    vars.m_velocity[inode] = {0.0, 0.0, 0.0};
  }
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

ARCANE_REGISTER_SERVICE_SEDOV(Sedov, SedovService);

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace Cas_testSEDOV
