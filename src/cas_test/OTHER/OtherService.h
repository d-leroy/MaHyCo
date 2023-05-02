#ifndef CAS_TEST_OTHER_OTHERSERVICE_H
#define CAS_TEST_OTHER_OTHERSERVICE_H

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#include "cas_test/OTHER/__OtherServiceBase.h"

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

namespace Cas_testOTHER {

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

/*!
 * \brief Service Other : implémentation
 * 
 */
class OtherService
: public OtherServiceBase<OtherService>
{
 public:
  explicit OtherService(const ServiceBuildInfo& bi);
  ~OtherService();

 public:
  void initMatMono(OtherInitMatMonoVars& vars, const Integer dim) override;
  void initVarMono(OtherInitVarMonoVars& vars, const Integer dim) override;
  void initMat(OtherInitMatVars& vars, const Integer dim) override;
  void initVar(OtherInitVarVars& vars, const Integer dim) override;
};

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

}  // namespace Cas_testOTHER

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

#endif  // CAS_TEST_OTHER_OTHERSERVICE_H
