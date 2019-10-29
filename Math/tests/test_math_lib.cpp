#define BOOST_TEST_MODULE math_test_module
#include <boost/test/unit_test.hpp>
#include <vector>
#include <iostream>

#include "math_lib.h"

using namespace std;
namespace tt = boost::test_tools;
namespace utf = boost::unit_test;

/*
template <typename T>
std::ostream& operator<<(std::ostream& out, std::vector<T> vec) {
    for (const auto& v : vec) {
        out << v << " ";
    }
    return out;
}
*/

BOOST_AUTO_TEST_SUITE(math_lib_test_suite)

    BOOST_AUTO_TEST_CASE(test_factorial) {
        // integer
        BOOST_TEST(factorial(0) == 1);
        BOOST_TEST(factorial(1) == 1);
        BOOST_TEST(factorial(2) == 2);
        BOOST_TEST(factorial(3) == 6);
        BOOST_TEST(factorial(10) == 3628800);
        BOOST_TEST(factorial(-1) == 1);
        // double
        BOOST_TEST(factorial(0.5) == 1);
        BOOST_TEST(factorial(1.5) == 1.5);
        BOOST_TEST(factorial(2.5) == 3.75);
    }

    BOOST_AUTO_TEST_CASE(test_round_to, * utf::tolerance(0.000001)) {
        BOOST_TEST(roundTo(125, 1) == 130);
        BOOST_TEST(roundTo(125, 2) == 100);
        BOOST_TEST(roundTo(125.456, 1) == 130);
        BOOST_TEST(roundTo(125.456, 0) == 125);
        BOOST_TEST(roundTo(125.456, -1) == 125.5);
        // less one
        BOOST_TEST(roundTo(0.416, 1) == 0);
        BOOST_TEST(roundTo(0.416, 0) == 0);
        BOOST_TEST(roundTo(0.416, -1) == 0.4);
    }

    BOOST_AUTO_TEST_CASE(test_odd) {
        BOOST_TEST(!odd(2));
        BOOST_TEST(odd(1));
        BOOST_TEST(odd(3));
        BOOST_TEST(!odd(0));
        BOOST_TEST(odd(-1));
    }

    BOOST_AUTO_TEST_CASE(test_average_1) {
        // contract: double average(double x, double y);
        BOOST_TEST(average(2, 4) == 3);
        BOOST_TEST(average(2, 5) == 3.5);
        BOOST_TEST(average(0, 1) == 0.5);
        BOOST_TEST(average(-1, 1) == 0);
        BOOST_TEST(average(2.5, 0.5) == 1.5);
    }

    BOOST_AUTO_TEST_CASE(test_average_2) {
        // contract: double average(const std::vector<double>& vals);
        BOOST_TEST(average({2, 4}) == 3);
        BOOST_TEST(average({2, 5}) == 3.5);
        BOOST_TEST(average({0, 1}) == 0.5);
        BOOST_TEST(average({-1, 1}) == 0);
        BOOST_TEST(average({2.5, 0.5}) == 1.5);
        BOOST_TEST(average({-2, 2, 3}) == 1);
    }

    BOOST_AUTO_TEST_CASE(test_average_3, * utf::tolerance(0.000001)) {
        // contract: void average(const std::vector<double>& vals, double &mean, double &err);
        {const vector<double> input {4, 5, 7, 2};
            double mean, err;
            average(input, mean, err);
            BOOST_TEST(mean == 4.5);
            BOOST_TEST(err == 1.04083299973307);
        }
        {const vector<double> input {2, 5};
            double mean, err;
            average(input, mean, err);
            BOOST_TEST(mean == 3.5);
            BOOST_TEST(err == 1.5);
        }
    }

    BOOST_AUTO_TEST_CASE(test_sqr_add, * utf::tolerance(0.000001)) {
        // contract: double sqrAdd(const std::vector<double>& vals);
        BOOST_TEST(sqrAdd({3, 4}) == 5);
        BOOST_TEST(sqrAdd({3, 4, 5}) == sqrt(50));
        BOOST_TEST(sqrAdd({7.1, 3.2, 78.5, 0.56}) == 78.8873475279781);
    }

    BOOST_AUTO_TEST_CASE(test_poly) {
        // f(x) = 2*x^2 + x + 3.5; f(0)
        const vector<double> coeffs = {3.5, 1, 2};
        BOOST_TEST(poly(0, coeffs) == 3.5);
        BOOST_TEST(poly(1, coeffs) == 6.5);
        BOOST_TEST(poly(-1, coeffs) == 4.5);
    }

    BOOST_AUTO_TEST_CASE(test_calculate_pdf) {
        // weights: 1, 1, 1, 1 => pdf: 0.25, 0.5, 0.75, 1 and sum = 4
        {
            vector<double> weights = {1, 1, 1, 1};
            auto sum = calculate_pdf(weights);
            BOOST_TEST(sum == 4);
            const vector<double> res = {0.25, 0.5, 0.75, 1};
            BOOST_TEST(weights == res);
        }
        {
            vector<double> weights = {1};
            auto sum = calculate_pdf(weights);
            BOOST_TEST(sum == 1);
            const vector<double> res = {1};
            BOOST_TEST(weights == res);
        }
        {
            vector<double> weights = {0.5, 2, 1};
            auto sum = calculate_pdf(weights);
            BOOST_TEST(sum == 3.5);
            const vector<double> res = {5./35, 25./35, 1};
            BOOST_TEST(weights == res);
        }
        // test with predicate: e.g. cont with struct a.weight:
        {
            struct Tmp {double weight = 0;};
            vector<Tmp> weights = {Tmp{0.5}, Tmp{2}, Tmp{1}};
            vector<double> res;
            auto sum = calculate_pdf(weights, [](const Tmp& t){ return t.weight;}, res);
            BOOST_TEST(sum == 3.5);
            const vector<double> expected = {5./35, 25./35, 1};
            BOOST_TEST(res == expected);
        }
    }

BOOST_AUTO_TEST_SUITE_END()