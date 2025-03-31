#pragma once
#ifndef NONLINEARSOLVER_H_INCLUDED
#define NONLINEARSOLVER_H_INCLUDED

#include <cmath>

/**@file
    @brief Newton methods of solving non-linear equaton
*/

namespace gwmath
{

/** \brief Newton method of solving non-linear equaton.

    Newton method of solving non-linear equaton.
    You must set function double f(double) and derivative function double f'(double)
    EPS -- absolute epsilon f(x) < EPS and if root == 0: x < EPS
    REL_EPS -- relative epsilon: |x - root| < REL_EPS * x
*/
template <typename FuncType1, typename FuncType2>
double getRootNewton(FuncType1 f, FuncType2 fdiff, double x0, double EPS = 1e-6, double REL_EPS = 0.001) {
    // find 3 iteration for epsilon calculation
    if (f(x0) == 0) {return x0;}
    double xm2 = x0;
    double xm1 = x0 - f(x0) / fdiff(x0);
    if (f(xm1) == 0) {return xm1;}
    double x = xm1 - f(xm1) / fdiff(xm1);
    if (f(x) == 0) {return x;}
    // calculate q - denominator of geometric rogression, p -- multiplicity of root
    double q = (x - xm1) / (xm1 - xm2);
    //double p = 1.0 / (1.0 - q);
    //double diff = fabs(q * p * (x - xm1));
    q /= (1.0 - q);
    double diff = fabs(q * (x - xm1));

    // Newton method
    while (fabs(f(x)) > EPS || (diff > REL_EPS * fabs(x) && diff > EPS)) {
        xm2 = xm1;
        xm1 = x;
        x -= f(x) / fdiff(x);
        q = (x - xm1) / (xm1 - xm2);
        //p = 1.0 / (1.0 - q);
        //diff = fabs(q * p * (x - xm1));
        q /= (1.0 - q);
        diff = fabs(q * (x - xm1));
    }
    return x;
}

/** \brief Newton method of solving non-linear equaton.

    Newton method of solving non-linear equaton. maybe faster about 10-30%
    You must set function double f(double) and derivative function double f'(double)
    EPS -- absolute epsilon f(x) < EPS and if root == 0: x < EPS
    REL_EPS -- relative epsilon: |x - root| < REL_EPS * x
*/
template <typename FuncType1, typename FuncType2>
double getRootNewtonSimple(FuncType1 f, FuncType2 fdiff, double x0, double EPS = 1e-6) {
    double x(x0);
    while (fabs(f(x)) > EPS) {
        x -= f(x) / fdiff(x);
    }
    return x;
}

} // namespace gwmath

#endif // NONLINEARSOLVER_H_INCLUDED
