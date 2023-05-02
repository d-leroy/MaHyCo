#ifndef CAS_TEST_SOD_SODSERVICE_H
#define CAS_TEST_SOD_SODSERVICE_H

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#include "cas_test/SOD/__SodServiceBase.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

namespace Cas_testSOD {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

/*!
 * \brief Service Sod : implémentation
 * 
 */
class SodService
: public SodServiceBase<SodService>
{
 public:
  explicit SodService(const ServiceBuildInfo& bi);
  ~SodService();

 public:
  void initMatMono(SodInitMatMonoVars& vars, const Integer dim) override;
  void initVarMono(SodInitVarMonoVars& vars, const Integer dim) override;
  void initMat(SodInitMatVars& vars, const Integer dim) override;
  void initVar(SodInitVarVars& vars, const Integer dim) override;
};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace Cas_testSOD

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // CAS_TEST_SOD_SODSERVICE_H
