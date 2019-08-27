#ifndef LEASTSQUARES_H_INCLUDED
#define LEASTSQUARES_H_INCLUDED

#include <vector>

// Least squares method for straight proportion: y = a * x
void ols_StraightLineProp(const std::vector<double>& xi, const std::vector<double>& yi, double& a, double& da);
// polynomial y = a * x + b
bool ols_poly(const std::vector<double>& xi, const std::vector<double>& yi, int degree, std::vector<double>& coeffs);


#endif // LEASTSQUARES_H_INCLUDED
