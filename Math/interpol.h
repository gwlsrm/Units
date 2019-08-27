#ifndef INTERPOL_H_INCLUDED
#define INTERPOL_H_INCLUDED

#include <vector>

enum class LogState {lsNone, lsXonly, lsYonly, lsXYBoth};

double interpol(int poly_degree, const std::vector<double>& xi, const std::vector<double>& yi,
                double x, LogState x_or_y_log);


#endif // INTERPOL_H_INCLUDED
