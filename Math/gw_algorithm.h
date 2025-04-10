#pragma once
#ifndef GWALGORITHM_H_INCLUDED
#define GWALGORITHM_H_INCLUDED

#include <vector>

/**\file
    @brief additional algorithms like search in vector with tolerance and range
*/

namespace gwmath {

/// finds value in vector<double> with tolerance
int findInDoubleVector(const std::vector<double>& vctr, double value, double tolerance = 0.001);

/// generate range from init_value to end_value with step
std::vector<double> generateRange(double init_value, double end_value, double step);

} // namespace gwmath

#endif // GWALGORITHM_H_INCLUDED
