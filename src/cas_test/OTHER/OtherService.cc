#include "cas_test/OTHER/OtherService.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

namespace Cas_testOTHER {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

OtherService::
OtherService(const ServiceBuildInfo& bi)
: OtherServiceBase<OtherService>(bi)
{
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

OtherService::
~OtherService()
{
}
	

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void OtherService::
initMatMono(OtherInitMatMonoVars& vars, [[maybe_unused]] const Integer dim)
{
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void OtherService::
initVarMono(OtherInitVarMonoVars& vars, [[maybe_unused]] const Integer dim)
{
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void OtherService::
initMat(OtherInitMatVars& vars, [[maybe_unused]] const Integer dim)
{
  // rayon interne et externe
  double rb(0.5);
  ENUMERATE_CELL(icell,allCells()) {
    Cell cell = *icell;

    double r = vars.m_cell_coord[cell][0];
    vars.m_materiau[cell] = 0;
    
    if (r < rb) {
      // maille pure autre mat
    vars.m_materiau[cell] = 1;
    } 
  }
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

void OtherService::
initVar(OtherInitVarVars& vars, [[maybe_unused]] const Integer dim)
{
  // rayon interne et externe
  double rb(0.5);
        
  info() << " boucle sur les mailles";
  ENUMERATE_CELL(icell,allCells()) {
    Cell cell = *icell;
    // pseudo-viscosité 
    vars.m_pseudo_viscosity[cell] = 0.;
    // parametres maille
 
    // Air partout
    vars.m_density[cell] = 0.1;
    vars.m_pressure[cell] = 1.;
    vars.m_internal_energy[cell] = 1.;
    // bulle surchargera l'aire
    // centre de la bulle
    double r = vars.m_cell_coord[cell][0];
    if (r < rb) {
      // maille pure de bulle
      vars.m_density[cell] = 1.;
    } 
    vars.m_fracvol[cell] = 1.;
    vars.m_mass_fraction[cell] = 1.;
  }
  info() << " boucle sur les noeuds";
  ENUMERATE_NODE(inode, allNodes()){
    vars.m_velocity[inode] = {0.0, 0.0, 0.0};    
    //m_velocity[inode].x = 1.;  
    //m_velocity[inode].y = 1.;
    // sauvegarde des valeurs initiales mises dans m_velocity_n
    vars.m_velocity_n[inode] = vars.m_velocity[inode];
  }
  info() << " fin de boucle sur les noeuds";
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

ARCANE_REGISTER_SERVICE_OTHER(Other, OtherService);

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace Cas_testOTHER
