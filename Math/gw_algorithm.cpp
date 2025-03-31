#include "gw_algorithm.h"

#include <cmath>


int findInDoubleVector(const std::vector<double>& vctr, double value, double tolerance) {
    for (size_t i = 0; i < vctr.size(); ++i) {
        if (std::fabs(vctr[i] - value) < tolerance) {
            return i;
        }
    }
    return -1;
}

std::vector<double> generateRange(double init_value, double end_value, double step) {
    int cnt = static_cast<int>(std::fabs((end_value - init_value) / step));
    std::vector<double> res(cnt);
    if (!cnt) return res;

    res[0] = init_value;
    for (int i = 1; i < cnt; ++i) {
        res[i] = res[i-1] + step;
    }
    return res;
}
