#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <vector>
#include <iostream>

#include "math_lib.h"

using namespace std;

TEST_SUITE("math_lib_test_suite") {

    TEST_CASE("test_factorial") {
        // integer
        CHECK(factorial(0) == 1);
        CHECK(factorial(1) == 1);
        CHECK(factorial(2) == 2);
        CHECK(factorial(3) == 6);
        CHECK(factorial(10) == 3628800);
        CHECK(factorial(-1) == 1);
        // double
        CHECK(factorial(0.5) == 1);
        CHECK(factorial(1.5) == 1.5);
        CHECK(factorial(2.5) == 3.75);
    }

    TEST_CASE("test_round_to") {
        CHECK(roundTo(125, 1) == 130);
        CHECK(roundTo(125, 2) == 100);
        CHECK(roundTo(125.456, 1) == 130);
        CHECK(roundTo(125.456, 0) == 125);
        CHECK(roundTo(125.456, -1) == doctest::Approx(125.5).epsilon(0.000001));
        // less one
        CHECK(roundTo(0.416, 1) == 0);
        CHECK(roundTo(0.416, 0) == 0);
        CHECK(roundTo(0.416, -1) == doctest::Approx(0.4).epsilon(0.000001));
    }

    TEST_CASE("test_odd") {
        CHECK(!odd(2));
        CHECK(odd(1));
        CHECK(odd(3));
        CHECK(!odd(0));
        CHECK(odd(-1));
    }

    TEST_CASE("test_average_1") {
        // contract: double average(double x, double y);
        CHECK(average(2, 4) == 3);
        CHECK(average(2, 5) == 3.5);
        CHECK(average(0, 1) == 0.5);
        CHECK(average(-1, 1) == 0);
        CHECK(average(2.5, 0.5) == 1.5);
    }

    TEST_CASE("test_average_2") {
        // contract: double average(const std::vector<double>& vals);
        CHECK(average({2, 4}) == 3);
        CHECK(average({2, 5}) == 3.5);
        CHECK(average({0, 1}) == 0.5);
        CHECK(average({-1, 1}) == 0);
        CHECK(average({2.5, 0.5}) == 1.5);
        CHECK(average({-2, 2, 3}) == 1);
    }

    TEST_CASE("test_average_3") {
        // contract: void average(const std::vector<double>& vals, double &mean, double &err);
        {
            const vector<double> input {4, 5, 7, 2};
            double mean, err;
            average(input, mean, err);
            CHECK(mean == doctest::Approx(4.5).epsilon(0.000001));
            CHECK(err == doctest::Approx(1.04083299973307).epsilon(0.000001));
        }
        {
            const vector<double> input {2, 5};
            double mean, err;
            average(input, mean, err);
            CHECK(mean == doctest::Approx(3.5).epsilon(0.000001));
            CHECK(err == doctest::Approx(1.5).epsilon(0.000001));
        }
    }

    TEST_CASE("test_sqr_add") {
        // contract: double sqrAdd(const std::vector<double>& vals);
        CHECK(sqrAdd({3, 4}) == doctest::Approx(5).epsilon(0.000001));
        CHECK(sqrAdd({3, 4, 5}) == doctest::Approx(sqrt(50)).epsilon(0.000001));
        CHECK(sqrAdd({7.1, 3.2, 78.5, 0.56}) == doctest::Approx(78.8873475279781).epsilon(0.000001));
    }

    TEST_CASE("test_poly") {
        // f(x) = 2*x^2 + x + 3.5
        const vector<double> coeffs = {3.5, 1, 2};
        CHECK(poly(0, coeffs) == 3.5);
        CHECK(poly(1, coeffs) == 6.5);
        CHECK(poly(-1, coeffs) == 4.5);
    }

    TEST_CASE("test_calculate_pdf") {
        // weights: 1, 1, 1, 1 => pdf: 0.25, 0.5, 0.75, 1 and sum = 4
        {
            vector<double> weights = {1, 1, 1, 1};
            auto sum = calculate_pdf(weights);
            CHECK(sum == 4);
            const vector<double> res = {0.25, 0.5, 0.75, 1};
            CHECK(weights == res);
        }
        {
            vector<double> weights = {1};
            auto sum = calculate_pdf(weights);
            CHECK(sum == 1);
            const vector<double> res = {1};
            CHECK(weights == res);
        }
        {
            vector<double> weights = {0.5, 2, 1};
            auto sum = calculate_pdf(weights);
            CHECK(sum == 3.5);
            const vector<double> res = {5./35, 25./35, 1};
            CHECK(weights == res);
        }
        // test with predicate: e.g. cont with struct a.weight
        {
            struct Tmp {double weight = 0;};
            vector<Tmp> weights = {Tmp{0.5}, Tmp{2}, Tmp{1}};
            vector<double> res;
            auto sum = calculate_pdf(weights, [](const Tmp& t){ return t.weight;}, res);
            CHECK(sum == 3.5);
            const vector<double> expected = {5./35, 25./35, 1};
            CHECK(res == expected);
        }
    }

}
