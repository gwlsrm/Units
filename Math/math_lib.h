//---------------------------------------------------------------------------
#pragma once

#include <cmath>
#include <vector>
#include <algorithm>
#include <cfloat>

constexpr int MAX_LOG_DOUBLE = 300;

// mathematic
inline double sqr(double value) { return pow(value, 2); }
double factorial(double n);
double roundTo(double f, int n);    // rounds to 10^n, can be negative: n=-2 => to 0.01
inline bool odd(int n) {return static_cast<bool>(n % 2);}
double sqrAdd(const std::vector<double>& vals);
int gcd (int a, int b); // greatest common divisor
int squareEquationSolver(double a, double b, double c, double& x1, double& x2); // solves square equation and returns number of roots
// calculates polynomial value: 1) coeffs: 0, 1, .. n, 2) coeffs: n, n-1, ..., 1, 0 (reverse)
double poly(double x, const std::vector<double>& coeffs);
double poly_reverse(double x, const std::vector<double>& coeffs);
// return true, if difference between a and b is less than absEpsilon or relEpsilon
bool approximatelyEqual(double a, double b, double absEpsilon = 1e-16, double relEpsilon = 1e-8);
inline bool isDblZero(double a, double absEpsilon = 1e-16) {return fabs(a) <= absEpsilon;}
inline bool inRange(double value, double amin, double amax) {return value >= amin && value <= amax;}
// min and max
bool minParabola(double x1, double x2, double x3, double y1, double y2, double y3,
                 double& x0);
bool minParabola(double x1, double x2, double x3, double y1, double y2, double y3,
                 double& a, double& b, double& c);
bool local_min(const std::vector<double>& x_arr, const std::vector<double>& chi, double& x);
// statistic
double average(double x, double y);
double average(const std::vector<double>& vals);
void average(const std::vector<double>& vals, double& mean, double& err);
void weightedMean(const std::vector<double>& vals, const std::vector<double>& errors,
                  double &wMean, double &wError);
void weightedMeanWeights(const std::vector<double>& vals, const std::vector<double>& weights,
                  double &wMean, double &wError);
inline double weightCalculation(double err) {return isDblZero(err) ? 0 : 1 / sqr(err);}
std::vector<double> weightsCalculation(const std::vector<double>& err_arr);
inline double linear_interpol(double x1, double x2, double y1, double y2, double x) {
    double w = (x - x1) / (x2 - x1);
    return (1 - w) * y1 + w * y2;
}

// errors
double errorFromPropValue(double a, double da, double b); // if b = k*a; rel. errors are equal: db = da / a * b (returns db)
inline double relErrorFromAbs(double a, double da) {return isDblZero(a) ? 1.0 : da / a;}

// histogram
std::vector<double> recalc_histo(const std::vector<double> &init_histo, int newChNum);

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

template <typename Container>
double calculate_pdf(Container& cont) {
/**
    Calculates probabilities distribution on array (container) Sum = 1, next num will be not less than previous.
    Integral of PDF (en.wikipedia.org/wiki/Probability_density_function)
    cont -- container of double like vector or std::array
*/
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

// for random
template <typename T, typename U>
inline double get_random_for_range(T rand_value, T max_rnd_value, U upper_b, U shift = 0) {
    return static_cast<double>(upper_b) * rand_value / max_rnd_value + shift;
}

// convolution
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
