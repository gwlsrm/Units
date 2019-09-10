// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "numeric_integration.h"

#include <cassert>

double aveIntegration(const FuncTyped2d& f, double a, double b, double EPS) {
    /**
        numeric integral calulation int{from a, to b} {f(double)} using average value on grid
        R = h^2/24 |b - a| == EPS
        Int = h * Sum(f((xh+1 - xh) /2))
    */
    //constexpr int N = 4618;
    int N = (b - a) / sqrt(24.0 * EPS / (b - a)); // incorrect estimation (need f'(b) - f'(a))
    return aveIntegration(f, a, b, N);
}

double aveIntegration(const FuncTyped2d& f, double a, double b, int num_intervals) {
    /**
        numeric integral calulation int{from a, to b} {f(double)} using average value on grid
        Int = h * Sum(f((xh+1 - xh) /2))
    */
    assert(num_intervals);
    if (a == b) return 0;
    if (a > b) {
        using std::swap;
        swap(a, b);
    }
    double h = (b - a) / num_intervals;
    double integral(0);
    double x = a + h / 2.0;
    for (int i = 0; i < num_intervals; ++i) { //for (double x = a + h/2; x < b; x += h) {
        integral += f(x);
        x += h;
    }
    return integral * h;
}

//double trapIntegration(const FuncTyped2d& f, double a, double b, double EPS) {
//
//}

double trapIntegration(const FuncTyped2d& f, double a, double b, int num_intervals) {
    /**
        numeric integral calulation int{from a, to b} {f(double)} using trapezoid area values on grid
    */
    assert(num_intervals);
    if (a == b) return 0;
    if (a > b) {
        using std::swap;
        swap(a, b);
    }
    double h = (b - a) / num_intervals;
    double integral(0);
    double x = a;
    for (int i = 0; i < num_intervals; ++i) {
        integral += (f(x) + f(x+h)) / 2;
        x += h;
    }
    return integral * h;
}

double trapGridIntegration(int nstep, double step, const double* values) {
    double integral = 0.0;
    for(int i = 1; i < nstep; ++i) {
        integral += (values[i] + values[i-1]);
    }
    return integral * step / 2.0;
}
