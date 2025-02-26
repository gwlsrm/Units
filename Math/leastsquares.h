#pragma once
#ifndef LEASTSQUARES_H_INCLUDED
#define LEASTSQUARES_H_INCLUDED

#include <vector>

/**@file
    @brief least squares method
*/

namespace gwmath {

/// Least squares method for straight proportion: y = a * x
void ols_StraightLineProp(const std::vector<double>& xi, const std::vector<double>& yi,
                          double& a, double& da);
/// Least squares method for polynomial dependence y = Sum (a_i * x^i)
bool ols_poly(const std::vector<double>& xi, const std::vector<double>& yi,
              int degree, std::vector<double>& coeffs);

}  // namespace gwmath

#endif // LEASTSQUARES_H_INCLUDED
