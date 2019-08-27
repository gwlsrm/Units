// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "leastsquares.h"

#include <cmath>
#include <stdexcept>

#include "math_lib.h"
#include "gwmatrix.h"
#include "sle.h"
#include "container_output.h"

using namespace std;

void ols_StraightLineProp(const std::vector<double>& xi, const std::vector<double>& yi,
                          double& a, double& da) {
    /** Least squares method for straight proportion: y = a * x */
    if (xi.size() != yi.size() || xi.empty()) {
        throw runtime_error("ols_StraightLineProp error: xi is empty or different length for xi and yi");
    }

    double xx_ave = 0, xy_ave = 0;
    for (size_t i = 0; i < xi.size(); ++i) {
        xx_ave += xi[i] * xi[i];
        xy_ave += xi[i] * yi[i];
    }

    a = xy_ave / xx_ave;
    da = 0;
    if (xi.size() > 1) {
        for (size_t i = 0; i < xi.size(); ++i) {
            da += sqr(a * xi[i] - yi[i]);
        }
        da = sqrt(da / (xi.size() - 1));
    }
}

bool ols_poly(const std::vector<double>& xi, const std::vector<double>& yi, int degree, std::vector<double>& coeffs) {
    /**
    Least square method for polynomial dependence: y = Sum (a_i * x^i)
    */
    if (xi.size() != yi.size() || degree < 0 || int(xi.size()) < degree + 1) return false;

    /* creates matrices for least squares
     Aij= Sum(i) (x_i^j * x_i^k)
     Bk= Sum(i) (y_i * x_i^k)  */

    size_t m = degree + 1;
    vector<double> b(m);
    DoubleMatrix A(m, m);
    coeffs.resize(m);

    for (size_t k = 0; k < m; ++k) {
        b[k] = 0;
        for (size_t i = 0; i < xi.size(); ++i) {
            b[k] += yi[i] * pow(xi[i], k);
        }
        for (size_t j = 0; j < m; ++j) {
            A(j, k) = 0;
            for (size_t i = 0; i < xi.size(); ++i) {
                A(j, k) += pow(xi[i], j) * pow(xi[i], k);
            }
        }
    }
    coeffs = chol(A, b);
    return true;
}
