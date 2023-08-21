#include "cas_test/RIDER/RiderService.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

namespace Cas_testRIDER {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

RiderService::
RiderService(const ServiceBuildInfo& bi)
: RiderServiceBase<RiderService>(bi)
{
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

RiderService::
~RiderService()
{
}
	

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void RiderService::
initMatMono(RiderInitMatMonoVars& vars, [[maybe_unused]] const Integer dim)
{
  ENUMERATE_CELL(icell,allCells()) {
    Cell cell = *icell;
    vars.m_materiau[cell] = 0;
  }
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void RiderService::
initVarMono(RiderInitVarMonoVars& vars, [[maybe_unused]] const Integer dim)
{
  Real3 Xb;
  if (getCasTest() < Cas_test::Test::MonoRiderRotation) 
          Xb = {0.20, 0.20, 0.};
      else
          Xb = {0.50, 0.75, 0.};
  Real3 cc = {0.5, 0.5, 0.};
  // rayon interne et externe
  double rb(0.15);
        
  ENUMERATE_CELL(icell,allCells()) {
    Cell cell = *icell;
    // pseudo-viscosité 
    vars.m_pseudo_viscosity[cell] = 0.;
    // parametres maille
    Real rmin(10.), rmax(0.);
    ENUMERATE_NODE(inode, cell.nodes()) {
      Real rnode = std::sqrt((vars.m_node_coord[inode][0] - Xb[0]) *
                                       (vars.m_node_coord[inode][0] - Xb[0]) +
                                   (vars.m_node_coord[inode][1] - Xb[1]) *
                                       (vars.m_node_coord[inode][1] - Xb[1]));
      rmin = std::min(rmin, rnode);
      rmax = std::max(rmax, rnode);
    }
    // Air partout
    vars.m_density[cell] = 0.;
    vars.m_pressure[cell] = 0.;
    // bulle surchargera l'aire

    if (rmax < rb) {
      // maille pure de bulle
      vars.m_density[cell] = 1.;
      vars.m_pressure[cell] = 0.;
    } else if ((rmax >= rb) && (rmin < rb)) {
      double frac_b = (rb - rmin) / (rmax - rmin);
      vars.m_density[cell] = frac_b;
      vars.m_pressure[cell] = 0.;
    }
    vars.m_fracvol[cell] = 1.;
    vars.m_mass_fraction[cell] = 1.;
  }
  ENUMERATE_NODE(inode, allNodes()){
    vars.m_velocity[inode] = {0.0, 0.0, 0.0};    
    if ( getCasTest() == Cas_test::Test::MonoRiderTx) vars.m_velocity[inode].x = 1.;
    if ( getCasTest() == Cas_test::Test::MonoRiderTy) vars.m_velocity[inode].y = 1.;
    if ( getCasTest() == Cas_test::Test::MonoRiderT45) vars.m_velocity[inode] = {1.0, 1.0, 0.0};  
    if ( getCasTest() == Cas_test::Test::MonoRiderRotation) {
      Real3 dd  = vars.m_node_coord[inode] - cc;
      double theta = std::atan2(dd[1], dd[0]);
      double r = std::sqrt(dd[0] * dd[0] + dd[1] * dd[1]);
      double omega = 4. * Pi;
      vars.m_velocity[inode].x = -r * omega * std::sin(omega * 0. + theta);
      vars.m_velocity[inode].y = r * omega * std::cos(omega * 0. + theta);
    }
    if ( getCasTest() == Cas_test::Test::MonoRiderVortex || 
        getCasTest() == Cas_test::Test::MonoRiderVortexTimeReverse) {
      Real3 dd = vars.m_node_coord[inode];
      vars.m_velocity[inode].x =
          -2. * std::cos(Pi * dd[1]) * std::sin(Pi * dd[1]) *
          std::sin(Pi * dd[0]) * std::sin(Pi * dd[0]);
      vars.m_velocity[inode].y =
          2. * std::cos(Pi * dd[0]) * std::sin(Pi * dd[0]) *
          std::sin(Pi * dd[1]) * std::sin(Pi * dd[1]);
    }
    if ( getCasTest() == Cas_test::Test::MonoRiderDeformation || 
        getCasTest() == Cas_test::Test::MonoRiderDeformationTimeReverse) {
         Real3 dd = vars.m_node_coord[inode] + cc;
          vars.m_velocity[inode].x =
              std::sin(4. * Pi * dd[0]) * std::sin(4. * Pi * dd[1]);
          vars.m_velocity[inode].y  =
              std::cos(4. * Pi * dd[0]) * std::cos(4. * Pi * dd[1]);
        }
    // sauvegarde des valeurs initiales mises dans vars.m_velocity_n
    vars.m_velocity_n[inode] = vars.m_velocity[inode];
  }
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void RiderService::
initMat(RiderInitMatVars& vars, [[maybe_unused]] const Integer dim)
{
  if (getCasTest() >= Cas_test::Test::MonoRiderTx && getCasTest() <= Cas_test::Test::MonoRiderDeformationTimeReverse)  {
    RiderServiceBase<RiderService>::initMatMono(dim);
    return;
  } 
  Real3 Xb;
  if (getCasTest() < Cas_test::Test::RiderRotation)
          Xb = {0.20, 0.20, 0.};
      else
          Xb = {0.50, 0.75, 0.};
  // rayon interne et externe
  double rb(0.15);
  ENUMERATE_CELL(icell,allCells()) {
    Cell cell = *icell;
    Real rmin(10.), rmax(0.);
    ENUMERATE_NODE(inode, cell.nodes()) {
      Real rnode = std::sqrt((vars.m_node_coord[inode][0] - Xb[0]) *
                                (vars.m_node_coord[inode][0] - Xb[0]) +
                                   (vars.m_node_coord[inode][1] - Xb[1]) *
                                       (vars.m_node_coord[inode][1] - Xb[1]));
      rmin = std::min(rmin, rnode);
      rmax = std::max(rmax, rnode);
    }
    
    // Air partout
    vars.m_materiau[cell] = 0;
    // bulle surchargera l'aire
    
    if (rmax < rb) {
      // maille pure de bulle
    vars.m_materiau[cell] = 1;
    } else if ((rmax >= rb) && (rmin < rb)) {
      double frac_b = (rb - rmin) / (rmax - rmin);
      vars.m_materiau[cell] = frac_b;
    }
  }
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void RiderService::
initVar(RiderInitVarVars& vars, [[maybe_unused]] const Integer dim)
{
  if (getCasTest() >= Cas_test::Test::MonoRiderTx && getCasTest() <= Cas_test::Test::MonoRiderDeformationTimeReverse)  {
    RiderServiceBase<RiderService>::initVarMono(dim);
    return;
  } 
  Real3 Xb;
  if (getCasTest() < Cas_test::Test::RiderRotation) 
          Xb = {0.20, 0.20, 0.};
      else
          Xb = {0.50, 0.75, 0.};

  CellToAllEnvCellConverter all_env_cell_converter(getMeshMaterialMng());
  Real3 cc = {0.5, 0.5, 0.};
  // rayon interne et externe
  double rb(0.15);
        
  ENUMERATE_CELL(icell,allCells()) {
    Cell cell = *icell;
    // pseudo-viscosité 
    vars.m_pseudo_viscosity[cell] = 0.;
    // parametres maille
    Real rmin(10.), rmax(0.);
    ENUMERATE_NODE(inode, cell.nodes()) {
      Real rnode = std::sqrt((vars.m_node_coord[inode][0] - Xb[0]) *
                                       (vars.m_node_coord[inode][0] - Xb[0]) +
                                   (vars.m_node_coord[inode][1] - Xb[1]) *
                                       (vars.m_node_coord[inode][1] - Xb[1]));
      rmin = std::min(rmin, rnode);
      rmax = std::max(rmax, rnode);
    }
    // Air partout
    vars.m_density[cell] = 0.;
    vars.m_pressure[cell] = 0.;
    vars.m_fracvol[cell] = 1.;
    vars.m_mass_fraction[cell] = 1.;
    // bulle surchargera l'aire
    
    if (rmax < rb) {
      // maille pure de bulle
      vars.m_density[cell] = 1.;
      vars.m_pressure[cell] = 0.;
      vars.m_fracvol[cell] = 1.;
      vars.m_mass_fraction[cell] = 1.;
    } else if ((rmax >= rb) && (rmin < rb)) {
      // cas des cellules mailles mixtes
      double frac_b = (rb - rmin) / (rmax - rmin);
      AllEnvCell all_env_cell = all_env_cell_converter[cell];
      ENUMERATE_CELL_ENVCELL(ienvcell, all_env_cell) {
        EnvCell ev = *ienvcell;
        if (ev.environmentId() == 0) {
          vars.m_density[ev] = 1.;
          vars.m_fracvol[ev] = frac_b;
          vars.m_mass_fraction[ev] = frac_b;
          vars.m_pseudo_viscosity[ev] = 0.;
        }
        if (ev.environmentId() == 1) {
          vars.m_density[ev] = 0.;
          vars.m_fracvol[ev] = 1-frac_b;
          vars.m_mass_fraction[ev] = 1-frac_b;
          vars.m_pseudo_viscosity[ev] = 0.;
        }
        vars.m_pressure[ev] = 0.;
      }
      vars.m_density[cell] = frac_b;
      vars.m_pressure[cell] = 0.;
    }
  }
  ENUMERATE_NODE(inode, allNodes()){
    vars.m_velocity[inode] = {0.0, 0.0, 0.0};    
    if ( getCasTest() == Cas_test::Test::RiderTx) vars.m_velocity[inode].x = 1.;
    if ( getCasTest() == Cas_test::Test::RiderTy) vars.m_velocity[inode].y = 1.;
    if ( getCasTest() == Cas_test::Test::RiderT45) vars.m_velocity[inode] = {1.0, 1.0, 0.0};  
    if ( getCasTest() == Cas_test::Test::RiderRotation) {
      Real3 dd  = vars.m_node_coord[inode] - cc;
      double theta = std::atan2(dd[1], dd[0]);
      double r = std::sqrt(dd[0] * dd[0] + dd[1] * dd[1]);
      double omega = 4. * Pi;
      vars.m_velocity[inode].x = -r * omega * std::sin(omega * 0. + theta);
      vars.m_velocity[inode].y = r * omega * std::cos(omega * 0. + theta);
    }
    if ( getCasTest() == Cas_test::Test::RiderVortex || 
        getCasTest() == Cas_test::Test::RiderVortexTimeReverse) {
      Real3 dd = vars.m_node_coord[inode];
      vars.m_velocity[inode].x =
          -2. * std::cos(Pi * dd[1]) * std::sin(Pi * dd[1]) *
          std::sin(Pi * dd[0]) * std::sin(Pi * dd[0]);
      vars.m_velocity[inode].y =
          2. * std::cos(Pi * dd[0]) * std::sin(Pi * dd[0]) *
          std::sin(Pi * dd[1]) * std::sin(Pi * dd[1]);
    }
    if ( getCasTest() == Cas_test::Test::RiderDeformation || 
        getCasTest() == Cas_test::Test::RiderDeformationTimeReverse) {
         Real3 dd = vars.m_node_coord[inode] + cc;
          vars.m_velocity[inode].x =
              std::sin(4. * Pi * dd[0]) * std::sin(4. * Pi * dd[1]);
          vars.m_velocity[inode].y  =
              std::cos(4. * Pi * dd[0]) * std::cos(4. * Pi * dd[1]);
    }
    // sauvegarde des valeurs initiales mises dans vars.m_velocity_n
    vars.m_velocity_n[inode] = vars.m_velocity[inode];
  }
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

ARCANE_REGISTER_SERVICE_RIDER(Rider, RiderService);

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace Cas_testRIDER
