#ifndef INTERPOL_H_INCLUDED
#define INTERPOL_H_INCLUDED

#include <vector>

/** @file
    @brief polynomial interpolation functions
*/

/// interpolation modes
enum class LogState {
    lsNone,     ///< all scales are linear
    lsXonly,    ///< x-scale is logarithmic
    lsYonly,    ///< y-scale is logarithmic
    lsXYBoth    ///< both scales are logarithmic
};

/// interpolates grid function (xi, yi) with poly and returns value in x
double interpol(int poly_degree, const std::vector<double>& xi, const std::vector<double>& yi,
                double x, LogState x_or_y_log);
double interpol(int poly_degree, std::size_t array_size, const double* xi, const double* yi,
                double x, LogState x_or_y_log);


#endif // INTERPOL_H_INCLUDED
