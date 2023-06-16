#ifndef MAHYCO_MAHYCOUTILS_H
#define MAHYCO_MAHYCOUTILS_H

/**
 * Fonctions diverses
 **/

namespace Mahyco {

inline Real produit(Real A, Real B, Real C, Real D)
{
  return (A*B-C*D);
}
/*---------------------------------------------------------------------------*/
inline Real norme(Real E, Real F, Real G)
{
  return (sqrt((E*E)+(F*F)+(G*G)));
}

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

/** */
/* la fonction dont on cherche un zero */
/** */
inline double fvnr(double e, double p, [[maybe_unused]] double dpde,
        double en, double qnn1, double pn, double rn1, double rn) 
        {return e-en+0.5*(p+pn+2.*qnn1)*(1./rn1-1./rn);};

/** */
/* la derivee de f */
/** */
inline double fvnrderiv([[maybe_unused]] double e, double dpde, double rn1, double rn)
{return 1.+0.5*dpde*(1./rn1-1./rn);};

/** */
/* la fonction dont on cherche le zero */
/** */
inline double f(double e, double p,[[maybe_unused]] double dpde,
        double en,double qn, double pn, double cn1,
        double cn, double m, double qn1, double cdn, double cdon, double qnm1) 
    {return e-en+0.5*(p+qn1)*cn1/m +0.5*(pn+qn)*cn/m-0.25*(pn+qn)*cdn/m + 0.5*(qn1-qnm1)*cdon/m;};

/** */
/* la derivee de f */
/** */
inline double fderiv([[maybe_unused]] double e, [[maybe_unused]] double p, double dpde, double cn1, double m)
    {return 1.+0.5*dpde*cn1/m;};

}
#endif