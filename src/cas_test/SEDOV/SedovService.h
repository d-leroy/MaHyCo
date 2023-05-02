#ifndef CAS_TEST_SEDOV_SEDOVSERVICE_H
#define CAS_TEST_SEDOV_SEDOVSERVICE_H

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#include "cas_test/SEDOV/__SedovServiceBase.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

namespace Cas_testSEDOV {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

/*!
 * \brief Service Sedov : implémentation
 * 
 */
class SedovService
: public SedovServiceBase<SedovService>
{
 public:
  explicit SedovService(const ServiceBuildInfo& bi);
  ~SedovService();

 public:
  void initMatMono(SedovInitMatMonoVars& vars, const Integer dim) override;
  void initVarMono(SedovInitVarMonoVars& vars, const Integer dim) override;
  void initMat(SedovInitMatVars& vars, const Integer dim) override;
  void initVar(SedovInitVarVars& vars, const Integer dim) override;
};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace Cas_testSEDOV

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // CAS_TEST_SEDOV_SEDOVSERVICE_H
