// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "numeric_integration.h"

double trapGridIntegration(int nstep, double step, const double* values) {
    double integral = 0.0;
    for(int i = 1; i < nstep; ++i) {
        integral += (values[i] + values[i-1]);
    }
    return integral * step / 2.0;
}
