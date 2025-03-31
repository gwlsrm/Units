#include "math_lib.h"

#include <ctime>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <random>

double factorial1(double n)
{
  if (n <= 1) return 1.0;
  return n * factorial(n-1);
}

double factorial_ber(double N)
{
  double Factor = 1.0;
  if (N <= 1) return Factor;
  for (double TN = 2.0; TN <= N; TN++) Factor *= TN;
  return Factor;
}

double factorial(double n)
{
  if (n <= 1) return 1.0;
  double res = 1.0;
  for (; n > 1.0; --n) {
    res *= n;
  }
  return res;
}

int gcd (int a, int b) {
    return b ? gcd(b, a % b) : a;
}

double roundTo(double f, int n) {
    double mult = std::pow(10.0, n);
#ifndef __BORLANDC__
    return round(f / mult) * mult;
#else
    return int(f / mult) * mult;
#endif
}

bool approximatelyEqual(double a, double b, double absEpsilon, double relEpsilon)
{
    // absolute epsilon and difference for numbers close to 0
    double diff = fabs(a - b);
    if (diff <= absEpsilon)
        return true;

    // Knuth algorithm for relative difference
    return diff <= ((fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * relEpsilon);
}

int squareEquationSolver(double a, double b, double c, double& x1, double& x2) {
    // not equation
    if (isDblZero(a) && isDblZero(b)) {
        return 0;
	}

	// linear
	if (isDblZero(a)) {
        x1 = - c / b;
        return 1;
	}

	// square
	double discr = b*b - 4*a*c;
	if (discr < 0) return 0;
	discr = sqrt(discr);
	if (!isDblZero(discr)) {
        x1 = (-b + discr) / (2*a);
        x2 = (-b - discr) / (2*a);
		return 2;
	} else {
	    x1 = -b / (2*a);
	    return 1;
	}
}

double average(double x, double y)
{
    return (x + y)/2;
}

double poly(double x, const std::vector<double>& coeffs) {
    /** Horner's method of calculating polynomial*/
    if (coeffs.empty()) {throw std::runtime_error("Coeffs array must not be empty");}
    double res = coeffs.back();
    for (int i = static_cast<int>(coeffs.size())-2; i >=0; --i) {
        res = res * x + coeffs[i];
    }
    return res;
}

double poly(double x, const double* coeffs, int coeffs_sze) {
    /** Horner's method of calculating polynomial*/
    if (coeffs_sze <= 0) {throw std::runtime_error("Coeffs array must not be empty");}
    double res = coeffs[coeffs_sze-1];
    for (int i = coeffs_sze-2; i >=0; --i) {
        res = res * x + coeffs[i];
    }
    return res;
}

double poly_reverse(double x, const std::vector<double>& coeffs) {
    if (coeffs.empty()) {throw std::runtime_error("Coeffs array must not be empty");}
    double res = coeffs.front();
    for (size_t i = 1; i < coeffs.size(); ++i) {
        res = res * x + coeffs[i];
    }
    return res;
}

double average(const std::vector<double>& vals)
{
    if (vals.size() == 0) return 0;
    return static_cast<double>(accumulate(vals.begin(), vals.end(), 0.0)) / vals.size();
}

void average(const std::vector<double>& vals, double& mean, double& err)
{
    err = 0;
    if (vals.size() == 0) return;
    mean = average(vals);
    if (vals.size() <= 1) return; // stdev can be calculated for 2 or more values
	err = accumulate(vals.begin(), vals.end(), 0.0, [mean](double lhs, double rhs){
                  return lhs + (rhs - mean)*(rhs - mean);
                  });
    err = sqrt(err / vals.size() / (vals.size()-1));
}

void weightedMean(const std::vector<double>& vals, const std::vector<double>& errors, double& wMean, double& wError)
{
    weightedMeanWeights(vals, weightsCalculation(errors), wMean, wError);
}

void weightedMeanWeights(const std::vector<double>& vals, const std::vector<double>& weights,
                  double &wMean, double &wError) {
    wMean = 0; wError = 0;
    if (vals.empty() || weights.empty() || vals.size() != weights.size()) return;
    /**{FORMULA: <x> = Sum(wi*xi)/Sum(wi), Error= 1/Sum(wi)}*/
    double weightSum(0);
    for (size_t i = 0; i < vals.size(); ++i) {
        wMean += vals[i] * weights[i];
        weightSum += weights[i];
    }
    if (isDblZero(weightSum)) return;
    wMean /= weightSum;
    wError = sqrt(1.0 / weightSum);

    // calculate standard deviation
    /**FORMULA for stdev: dA = sqrt(Sum(wi*(A_ave - Ai)^2)) / sqrt((n-1)*Sum(wi))*/
    if (vals.size() > 1) { // stdev can be calculated for 2 or more values
        double stdev = 0;
        for (size_t i = 0; i < vals.size(); ++i) {
            stdev += weights[i] * sqr(vals[i] - wMean);
        }
        stdev = sqrt(stdev / weightSum / (vals.size()-1));
        wError = std::max(wError, stdev);
    }

    // second run for removing bad points
    constexpr int NSIGMA = 10;
    double threshold = NSIGMA * wError;
    double oldMean = wMean;
    wMean = 0;
    weightSum = 0;
    for (size_t i = 0; i < vals.size(); ++i) {
        if (fabs(vals[i] - oldMean) <= threshold) {
            wMean += vals[i] * weights[i];
            weightSum += weights[i];
        }
    }
    if (isDblZero(weightSum)) {
        wMean = oldMean;
        return;
    }
    wMean /= weightSum;
    wError = sqrt(1.0 / weightSum);

    // calculate standard deviation
    if (vals.size() < 2) { // stdev can be calculated for 2 or more values
        return;
    }
    {
        double stdev = 0;
        size_t counter(0);
        for (size_t i = 0; i < vals.size(); ++i) {
            if (fabs(vals[i] - oldMean) <= threshold) {
                stdev += weights[i] * sqr(vals[i] - wMean);
                ++counter;
            }
        }
        if (counter > 1) {
            stdev = sqrt(stdev / weightSum / (vals.size()-1));
        } else {
            stdev = 0;
        }
        wError = std::max(wError, stdev);
    }
}

std::vector<double> weightsCalculation(const std::vector<double>& err_arr) {
    std::vector<double> w(err_arr.size());
    for (size_t i = 0; i < err_arr.size(); ++i) {
        w[i] = !isDblZero(err_arr[i]) ? 1. / sqr(err_arr[i]) : 0;
    }
    return w;
}

double sqrAdd(const std::vector<double>& vals)
{
    if (vals.size() == 0) return 0;
    double res = accumulate(vals.begin(), vals.end(), 0.0, [](double lhs, double rhs){
                            return lhs + rhs * rhs;
                });
	return sqrt(res);
}

bool minParabola(double x1, double x2, double x3, double y1, double y2, double y3, double& x0)
{
    // change coordinates (x -> z, y -> r) to have (0,0) in second point:
    // r = y - y2, z = x - x2
    double z1 = x1 - x2;
    double z2 = x3 - x2;
    double r1 = y1 - y2;
    double r2 = y3 - y2;
    // coeffs calculation for y = a*x^2 + b*x (simply 2 linear equations)
    double a = z2*z1*(z2 - z1);
    if (isDblZero(a)) return false;
    a = (r2*z1 - r1*z2) / a;
    double b = (r1 - a*z1*z1) / z1; // x1 != 0 from z2*z1*(z2 - z1) check
    if (isDblZero(a)) return false; // it's not a parabola
    // vertex calculation from dy/dx=0: 0 = 2*a*x0 + b
    // and go to initial coordinates: +x2
    x0 = -b/(2*a) + x2;
    return true;
}

bool minParabola(double x1, double x2, double x3, double y1, double y2, double y3,
                 double& a, double& b, double& c)
{
    // change coordinates (x -> z, y -> r) to have (0,0) in second point:
    // r = y - y2, z = x - x2
    double z1 = x1 - x2;
    double z2 = x3 - x2;
    double r1 = y1 - y2;
    double r2 = y3 - y2;
    // coeffs calculation for y = a*x^2 + b*x (simply 2 linear equations)
    a = z2*z1*(z2 - z1);
    if (isDblZero(a)) return false;
    a = (r2*z1 - r1*z2) / a;
    b = (r1 - a*z1*z1) / z1; // x1 != 0 from z2*z1*(z2 - z1) check
    // revert coordinates to x, y
    b = b - 2*a*x2;
    c = a*x2*x2 - b*x2 + y2;
    return true;
}

bool local_min(const std::vector<double>& x_arr, const std::vector<double>& chi, double& x) {
    auto it = min_element(chi.begin(), chi.end());
    if (it == begin(chi) || next(it) == end(chi)) return false;

    int i = it - begin(chi);
    return minParabola(x_arr.at(i-1), x_arr.at(i), x_arr.at(i+1), *prev(it), *it, *next(it), x);
}

double errorFromPropValue(double a, double da, double b) {
    /**if b = k*a; rel. errors are equal: db = da / a * b (returns db)*/
    if (!isDblZero(a)) {
        return da / a * b;
    } else {
        return 0;
    }
}
