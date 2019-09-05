#ifndef SLE_H_INCLUDED
#define SLE_H_INCLUDED

#include <vector>
#include "gwmatrix.h"

/**@file
    @brief solve linear equations
*/

/// solve linear equations by Gauss method
std::vector<double> gauss(const DoubleMatrix& a, std::vector<double> b);
/// solve linear equations by Cholesky method
std::vector<double> chol(const DoubleMatrix& a, const std::vector<double>& b);

#endif // SLE_H_INCLUDED
