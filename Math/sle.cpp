#include "sle.h"

#include <algorithm>
#include <cmath>
#include <stdexcept>

#include "math_lib.h"

namespace gwmath {

std::vector<double> gauss(const DoubleMatrix& a, std::vector<double> b) {
    /**Gaussian elimination*/
    if (!a.isSquare()) {
        throw std::invalid_argument("The matrix must be square");
    }
    size_t m = a.getColCount();
    // check if only one equation
    if (m == 1) {
        if (!isDblZero(a(0,0))) {
            return {b[0] / a(0,0)};
        } else {
            return {};
        }
    }
    DoubleMatrix c = a;
    // transform to triagonal -- direct movement
    /*  find maximal and move it to the i-th place
        substract i-th line from all lines: i-th line -> 0
    */;
    for (size_t i=0; i < m-1; ++i) { // for every column
        for (size_t j = i+1; j < m; ++j) { // for i-th column looking only rows from i+1
            if (!isDblZero(c(i,i))) {
                c(j,i) = - c(j,i) / c(i,i);
            } else {
                std::vector<double> temp_vec(m);
                ArrayView<double> temp_vec_view(m, temp_vec.data());
                for (size_t k=i+1; k < m; ++k) {
                    if (!isDblZero(c(k,i))) {
                        temp_vec_view.copyFrom(c[k]);
                        c[k].copyFrom(c[i]);
                        c[i].copyFrom(temp_vec_view);
                        c(i,i) = -c(i,i);
                    }
                }
                c(j,i) = -c(j,i) / c(i,i);
            }

            for (size_t k = i+1; k < m; ++k) {
                c(j,k) += c(j,i) * c(i,k);
            }
            b[j] += c(j,i) * b[i];
        }
    }

    // direct movement
    /*x[i] = 1/a[i,i]*(b[i] - Sum(a[i,j]*x[j]))*/
    std::vector<double> x(m);
    for (int i = static_cast<int>(m)-1; i >= 0; --i) {
        x[i] = b[i];
        for (size_t j = i+1; j < m; ++j) {
            x[i] -= c(i,j) * x[j];
        }
        x[i] /= c(i,i);
    }
    return x;
}

std::vector<double> chol(const DoubleMatrix& a, const std::vector<double>& b) {
    size_t m = b.size();
    DoubleMatrix l(m, m);

    // finding  diagonal matrix -- l
    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < m; ++j) {
            if (j < i) {
                l(i, j) = 1 / l(j, j) * a(i, j);
                for (size_t k = 0; k < j; ++k) {
                    l(i, j) -= 1 / l(j, j) * l(i, k) * l(j, k);
                }
            } else if (i == j) {
                l(i, i) = a(i, i);
                for (size_t k = 0; k < i; ++k) {
                    l(i, i) -= l(i, k) * l(i, k);
                }
                l(i, i) = sqrt(l(i, i));
            }
        }
    }

    // solving system l * y = b
    std::vector<double> y(m);
    for (size_t i = 0; i < m; ++i) {
        y[i] = b[i] / l(i, i);
        for (size_t k = 0; k < i; ++k) {
            y[i] -= 1/l(i, i) * l(i, k) * y[k]; // yi = bi/Lii - 1/Lii*Sum(k=1 to i-1)(Lik*yk)
        }
    }

    // solving system l_transp * x = y (back)
    std::vector<double> x(m);
    for (int i = int(m)-1; i >= 0; --i) {
        x[i] = y[i] / l(i, i);
        for (int k = int(m)-1; k > i; --k) {
            x[i] -= 1/l(i, i) * l(k, i) * x[k];
        }
    }
    return x;
}


}  // namespace gwmath
