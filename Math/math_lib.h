//---------------------------------------------------------------------------
#pragma once

#include <cmath>
#include <vector>
#include <algorithm>
#include <cfloat>

/**@file
    @brief Some mathematical tools: check double for zero, approximately compare, statistic functions etc
*/

constexpr int MAX_LOG_DOUBLE = 300;

// mathematic
/// sqr(x) -- the same as x^2, x**2
inline double sqr(double value) { return pow(value, 2); }
/// factorial of n (n!)
double factorial(double n);
/// rounds to 10^n, can be negative: n=-2 => to 0.01
double roundTo(double f, int n);
/// returns true if number is odd
inline bool odd(int n) {return static_cast<bool>(n % 2);}
/// return square sum of vector elements: sqrt(v[0]^2 + v[1]^2 + ...)
double sqrAdd(const std::vector<double>& vals);
/// greatest common divisor
int gcd (int a, int b);
/// solves square equation and returns number of roots
int squareEquationSolver(double a, double b, double c, double& x1, double& x2);
/// calculates polynomial value for x, coeffs: 0, 1, .. n
double poly(double x, const std::vector<double>& coeffs);
/// calculates polynomial value for x, coeffs: n, n-1, ..., 1, 0 (reverse)
double poly_reverse(double x, const std::vector<double>& coeffs);
/// return true, if difference between a and b is less than absEpsilon or relEpsilon
bool approximatelyEqual(double a, double b, double absEpsilon = 1e-16, double relEpsilon = 1e-8);
/// return true if value is approximately zero
inline bool isDblZero(double a, double absEpsilon = 1e-16) {return fabs(a) <= absEpsilon;}
/// return true if value is in range [amin, amax]
inline bool inRange(double value, double amin, double amax) {return value >= amin && value <= amax;}
/// builds parabola and finds minimum (x-value)
bool minParabola(double x1, double x2, double x3, double y1, double y2, double y3,
                 double& x0);
/// builds parabola and returns its coeffs
bool minParabola(double x1, double x2, double x3, double y1, double y2, double y3,
                 double& a, double& b, double& c);
/// finds minimum chi in array: {x, chi} using parabola approximation
bool local_min(const std::vector<double>& x_arr, const std::vector<double>& chi, double& x);
// statistic
/// return average value for x and y
double average(double x, double y);
/// return average value for vector
double average(const std::vector<double>& vals);
/// return average value and standard deviation for vector
void average(const std::vector<double>& vals, double& mean, double& err);
/// return weighted average value and standard deviation for vector of values and its uncertainties
void weightedMean(const std::vector<double>& vals, const std::vector<double>& errors,
                  double &wMean, double &wError);
/// return weighted average value and standard deviation for vector of values and its weights
void weightedMeanWeights(const std::vector<double>& vals, const std::vector<double>& weights,
                  double &wMean, double &wError);
/// weight calculation from uncertainty
inline double weightCalculation(double err) {return isDblZero(err) ? 0 : 1 / sqr(err);}
/// weight calculation from vector of uncertainties
std::vector<double> weightsCalculation(const std::vector<double>& err_arr);
/// linear interpolation
inline double linear_interpol(double x1, double x2, double y1, double y2, double x) {
    double w = (x - x1) / (x2 - x1);
    return (1 - w) * y1 + w * y2;
}

// errors
/// if b = k*a; rel. errors are equal: db = da / a * b (returns db)
double errorFromPropValue(double a, double da, double b);
/// calculates relative uncertainties from abs
inline double relErrorFromAbs(double a, double da) {return isDblZero(a) ? 1.0 : da / a;}

// histogram
//std::vector<double> recalc_histo(const std::vector<double> &init_histo, int newChNum);

template<class T>
void getWeighted(T b_it, T e_it) {
    double total(0.0);
    for (T it= b_it; it < e_it; ++it) {
        total += (*it);
    }
    for (T it= b_it; it < e_it; ++it) {
        *it = (*it) / total;
    }
}

/// Calculates probabilities distribution function
/**
    Calculates probabilities distribution on array (container) Sum = 1, next num will be not less than previous.
    Integral of PDF (en.wikipedia.org/wiki/Probability_density_function)
    cont -- container of double like vector or std::array
*/
template <typename Container>
double calculate_pdf(Container& cont) {
    // extreme cases
    if (cont.empty()) return 0;

    // calculate non-normilized probabilities
    for (std::size_t i = 1; i < cont.size(); ++i) {
        cont[i] += cont[i-1];
    }
    double sum = cont.back();
    // normalize probabilities
    if (sum < 1e-16) return sum;
    std::for_each(std::begin(cont), std::end(cont), [sum](auto& v){return v /= sum;});
//    for (auto& num : cont) {
//        num /= sum;
//    }
    return sum;
}

/// Calculates probabilities distribution function
/**
    Calculates probabilities distribution on array (container) Sum = 1, next num will be not less than previous.
    Integral of PDF (en.wikipedia.org/wiki/Probability_density_function)
    cont -- container of double like vector or std::array
    p -- predicate p(c[i]) must return probability
*/
template <typename Container, typename P>
double calculate_pdf(Container& cont, P p, std::vector<double>& pdf) {
    // extreme cases
    if (cont.empty()) return 0;

    pdf.resize(cont.size());
    // calculate non-normilized probabilities
    for (std::size_t i = 1; i < cont.size(); ++i) {
        pdf[i] = pdf[i-1] + p(cont[i]);
    }
    double sum = pdf.back();
    // normalize probabilities
    if (sum < 1e-16) return sum;
    std::for_each(std::begin(pdf), std::end(pdf), [sum](auto& v){return v /= sum;});
//    for (auto& num : cont) {
//        num /= sum;
//    }
    return sum;
}

// for random
template <typename T, typename U>
inline double get_random_for_range(T rand_value, T max_rnd_value, U upper_b, U shift = 0) {
    return static_cast<double>(upper_b) * rand_value / max_rnd_value + shift;
}

/// convolution of data with gaussian with variable sigma
template <typename Func> // Func = double (*sigma_func)(int)
void convolution_with_gauss(std::vector<double>& data, Func sigma_func) {
  constexpr int NSIGMA = 3;
  std::vector<double> orig_data{std::move(data)};
  data.resize(orig_data.size(), 0);

  for (int i = 0; i < static_cast<int>(orig_data.size()); ++i) {
      // get conv function parameters: gauss
      double sigma = sigma_func(i);
      double sigma_2x2 = !isDblZero(sigma) ? 2 * sqr(sigma) : 1.0 / FLT_MAX_EXP;
      // set convolution boundaries
      const int j1 = round(i - NSIGMA * sigma);
      const int j2 = round(i + NSIGMA * sigma);
      // convolution with gauss
      double norm = 0, r;
      for (int j = j1; j <= j2; ++j) {
          if (j < 0 || j >= int(orig_data.size())) {
              r = 0;
          } else {
              r = orig_data[j];
          }
          double gaus = exp(-sqr(i-j)/sigma_2x2);
          data[i] += r * gaus;
          norm += gaus;
      }

      if (!isDblZero(norm)) data[i] /= norm;
  }
}
