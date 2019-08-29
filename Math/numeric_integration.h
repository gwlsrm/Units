#ifndef NUMERIC_INTEGRATION_H_INCLUDED
#define NUMERIC_INTEGRATION_H_INCLUDED

#include <cmath>
#include <utility>
#include <functional>

/// main fucntional type for numeric integration functions
using FuncTyped2d = std::function<double(double)>;

/// rectangle integration in center of rectangle
double aveIntegration(const FuncTyped2d& f, double a, double b, double EPS = 1e-6);
double aveIntegration(const FuncTyped2d& f, double a, double b, int num_intervals);
/// trapezoid integration
//double trapIntegration(const FuncTyped2d& f, double a, double b, double EPS = 1e-6);
double trapIntegration(const FuncTyped2d& f, double a, double b, int num_intervals);
/// trapezoid adaptive midpoint (variable step)
double trapIntegrationAdaptive(const FuncTyped2d& f, double a, double b, int num_intervals, double eps = 1e-6);



template <typename FuncType>
double aveIntegration2(FuncType f, double a, double b, double EPS = 1e-6) {
    /**
        numeric integral calulation int{from a, to b} {f(double)} using average value on grid
        R = h^2/24 |b - a| == EPS
        Int = h * Sum(f((xh+1 - xh) /2))
    */
    if (a == b) return 0;
    if (a > b) {
        using std::swap;
        swap(a, b);
    }
    //constexpr int N = 4618;
    int N = (b - a) / sqrt(24.0 * EPS / (b - a)); // incorrect estimation (need f'(b) - f'(a))
    double h = (b - a) / N;
    double integral(0);
    for (int i = 0; i < N; ++i) { //for (double x = a + h/2; x < b; x += h) {
        double x = a + h*(0.5 + i);
        integral += f(x);
    }
    return integral * h;
}

double trapGridIntegration(int nstep, double step, const double* values);

#endif // NUMERIC_INTEGRATION_H_INCLUDED
