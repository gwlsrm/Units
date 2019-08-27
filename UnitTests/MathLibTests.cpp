// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "MathLibTests.h"

#include <cmath>
#include <numeric>

#include "test_runner.h"
#include "math_lib.h"

using namespace std;

void TestAllMathLib() {
    TestRunner tr;
    RUN_TEST(tr, TestFactorial);
    RUN_TEST(tr, TestRoundTo);
    RUN_TEST(tr, TestOdd);
    RUN_TEST(tr, TestSqrAdd);
    RUN_TEST(tr, TestPoly);
    RUN_TEST(tr, TestAverage1);
    RUN_TEST(tr, TestAverage2);
    RUN_TEST(tr, TestAverage3);
    RUN_TEST(tr, TestConvolutionWithGauss);
}

void TestFactorial() {
    // integer
    ASSERT_EQUAL(factorial(0), 1);
    ASSERT_EQUAL(factorial(1), 1);
    ASSERT_EQUAL(factorial(2), 2);
    ASSERT_EQUAL(factorial(3), 6);
    ASSERT_EQUAL(factorial(10), 3628800);
    ASSERT_EQUAL(factorial(-1), 1);
    // double
    ASSERT_EQUAL(factorial(0.5), 1);
    ASSERT_EQUAL(factorial(1.5), 1.5);
    ASSERT_EQUAL(factorial(2.5), 3.75);
}

void TestRoundTo() {
    ASSERT_EQUAL(roundTo(125, 1), 130);
    ASSERT_EQUAL(roundTo(125, 2), 100);
    ASSERT_EQUAL(roundTo(125.456, 1), 130);
    ASSERT_EQUAL(roundTo(125.456, 0), 125);
    ASSERT_EQUAL(roundTo(125.456, -1), 125.5);
    // less one
    ASSERT_EQUAL(roundTo(0.416, 1), 0);
    ASSERT_EQUAL(roundTo(0.416, 0), 0);
    ASSERT_EQUAL(roundTo(0.416, -1), 0.4);
}

void TestOdd() {
    ASSERT(!odd(2));
    ASSERT(odd(1));
    ASSERT(odd(3));
    ASSERT(!odd(0));
    ASSERT(odd(-1));
}

void TestAverage1() {
    // contract: double average(double x, double y);
    ASSERT_EQUAL(average(2, 4), 3);
    ASSERT_EQUAL(average(2, 5), 3.5);
    ASSERT_EQUAL(average(0, 1), 0.5);
    ASSERT_EQUAL(average(-1, 1), 0);
    ASSERT_EQUAL(average(2.5, 0.5), 1.5);
}

void TestAverage2() {
    // contract: double average(const std::vector<double>& vals);
    ASSERT_EQUAL(average({2, 4}), 3);
    ASSERT_EQUAL(average({2, 5}), 3.5);
    ASSERT_EQUAL(average({0, 1}), 0.5);
    ASSERT_EQUAL(average({-1, 1}), 0);
    ASSERT_EQUAL(average({2.5, 0.5}), 1.5);
    ASSERT_EQUAL(average({-2, 2, 3}), 1);
}

void TestAverage3() {
    // contract: void average(const std::vector<double>& vals, double &mean, double &err);
    {vector<double> input {4, 5, 7, 2};
    double mean, err;
    average(input, mean, err);
    ASSERT_EQUAL(mean, 4.5);
    ASSERT(approximatelyEqual(err, 1.04083299973307));
    }
    {vector<double> input {2, 5};
    double mean, err;
    average(input, mean, err);
    ASSERT_EQUAL(mean, 3.5);
    ASSERT(approximatelyEqual(err, 1.5));
    }
}

void TestSqrAdd() {
    // contract: double sqrAdd(const std::vector<double>& vals);
    ASSERT_EQUAL(sqrAdd({3, 4}), 5);
    ASSERT(approximatelyEqual(sqrAdd({3, 4, 5}), sqrt(50)));
    ASSERT(approximatelyEqual(sqrAdd({7.1, 3.2, 78.5, 0.56}), 78.8873475279781));
}

void TestPoly() {
    {
        // f(x) = 2*x^2 + x + 3.5; f(0)
        vector<double> coeffs = {3.5, 1, 2};
        ASSERT_EQUAL(poly(0, coeffs), 3.5);
        ASSERT_EQUAL(poly(1, coeffs), 6.5);
        ASSERT_EQUAL(poly(-1, coeffs), 4.5);
    }
}

void TestConvolutionWithGauss() {
  // prepare data
  vector<double> data(10, 0);
  data[4] = 100;

  cout << data << endl;
  convolution_with_gauss(data, [](int i){return 1.0;});
  cout << data << endl;
  cout << accumulate(data.begin(), data.end(), 0.0) << endl;
}
