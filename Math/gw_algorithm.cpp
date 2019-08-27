// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "gw_algorithm.h"

#include <cmath>

using namespace std;

int find_dbl_vector(const std::vector<double>& vctr, double value, double tolerance) {
    for (size_t i = 0; i < vctr.size(); ++i) {
        if (fabs(vctr[i] - value) < tolerance) {
            return i;
        }
    }
    return -1;
}

std::vector<double> generateRange(double init_value, double end_value, double step) {
    int cnt = static_cast<int>(fabs((end_value - init_value) / step));
    vector<double> res(cnt);
    if (!cnt) return res;

    res[0] = init_value;
    for (int i = 1; i < cnt; ++i) {
        res[i] = res[i-1] + step;
    }
    return res;
}
