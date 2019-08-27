#ifndef GWALGORITHM_H_INCLUDED
#define GWALGORITHM_H_INCLUDED

#include <vector>

// find
int find_dbl_vector(const std::vector<double>& vctr, double value, double tolerance = 0.001);

std::vector<double> generateRange(double init_value, double end_value, double step);

#endif // GWALGORITHM_H_INCLUDED
