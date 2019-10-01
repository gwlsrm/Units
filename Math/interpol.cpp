// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "interpol.h"

#include <cmath>
#include <stdexcept>

#include "math_lib.h"
#include "gwmatrix.h"
#include "sle.h"

using namespace std;

inline double get_x_log_state(double x, LogState x_or_y_log) {
    switch (x_or_y_log) {
    case LogState::lsNone:
    case LogState::lsYonly:
        return x;
    case LogState::lsXonly:
    case LogState::lsXYBoth:
        return log(x);
    default:
        return x;
    }
}

inline double get_y_log_state(double y, LogState x_or_y_log) {
    switch (x_or_y_log) {
    case LogState::lsNone:
    case LogState::lsXonly:
        return y;
    case LogState::lsYonly:
    case LogState::lsXYBoth:
        return log(y);
    default:
        return y;
    }
}

double interpol(int poly_degree, const std::vector<double>& xi, const std::vector<double>& yi,
                double x, LogState x_or_y_log)
{
    // input data check
    if (xi.size() != yi.size()) {
        throw invalid_argument("x and y arrays must be the same size");
    }
    if (xi.empty()) {
        throw invalid_argument("x must not be empty");
    }
    if (poly_degree+1 > static_cast<int>(xi.size())) { // decrease polynom degree
        poly_degree = static_cast<int>(xi.size()) - 1;
    }
    if (poly_degree < 0) {
        throw invalid_argument("Polynom degree is less than zero");
    }

    // for odd numbers low bound Xi is: Xi<=X<Xi+1. If X<=X0: Xi = X0. And equal points to the right and to the left
    // for even numbers found the closest Xi to X and equal points to the right and to the left
    int li = 0;
    if (odd(poly_degree)) {
        auto low_it = lower_bound(begin(xi), end(xi), x);
        if (low_it != xi.begin()) {
            --low_it;
        }
        li = static_cast<int>(low_it - begin(xi));
    } else {
        auto low_it = lower_bound(begin(xi), end(xi), x);
        if (low_it != xi.begin()) {
            if (low_it == end(xi)) --low_it;
            if (x - *prev(low_it) < fabs(*low_it - x)) {
                --low_it;
            }
        }
        li = static_cast<int>(low_it - begin(xi));
    }
    // step to the left for center polynom
    li -= poly_degree / 2;
    li = li < 0 ? 0 : li;
    if (li + poly_degree + 1 > int(xi.size())) {
        li = int(xi.size()) - 1 - poly_degree;
    }

    // fill matrix and vectors for SLE(SLAU)
    DoubleMatrix a(poly_degree + 1);
    vector<double> b(poly_degree + 1);
    for (int i = 0; i <= poly_degree; ++i) {
        a(i, 0) = 1;
        for (int j=1; j <= poly_degree; ++j) {
            a[i][j] = a[i][j-1] * get_x_log_state(xi[li + i], x_or_y_log);
        }
        b[i] = get_y_log_state(yi.at(li+i), x_or_y_log);
    }

    // solving SLE (SLAU)
    vector<double> coeffs = gauss(a, b);
    double y = poly(get_x_log_state(x, x_or_y_log), coeffs);
    if (x_or_y_log == LogState::lsYonly || x_or_y_log == LogState::lsXYBoth) {
        y = exp(y);
    }
    return y;
}
