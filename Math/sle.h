#ifndef SLE_H_INCLUDED
#define SLE_H_INCLUDED

#include <vector>
#include "gwmatrix.h"

std::vector<double> gauss(const DoubleMatrix& a, std::vector<double> b);
std::vector<double> chol(const DoubleMatrix& a, const std::vector<double>& b);

#endif // SLE_H_INCLUDED
