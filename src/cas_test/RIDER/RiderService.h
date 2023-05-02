#ifndef CAS_TEST_RIDER_RIDERSERVICE_H
#define CAS_TEST_RIDER_RIDERSERVICE_H

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#include "cas_test/RIDER/__RiderServiceBase.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

namespace Cas_testRIDER {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

/*!
 * \brief Service Rider : implémentation
 * 
 */
class RiderService
: public RiderServiceBase<RiderService>
{
 public:
  explicit RiderService(const ServiceBuildInfo& bi);
  ~RiderService();

 public:
  void initMatMono(RiderInitMatMonoVars& vars, const Integer dim) override;
  void initVarMono(RiderInitVarMonoVars& vars, const Integer dim) override;
  void initMat(RiderInitMatVars& vars, const Integer dim) override;
  void initVar(RiderInitVarVars& vars, const Integer dim) override;
};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace Cas_testRIDER

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // CAS_TEST_RIDER_RIDERSERVICE_H
