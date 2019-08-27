// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "leastsquaresTests.h"
#include "leastsquares.h"
#include "math_lib.h"
#include "test_runner.h"

using namespace std;

void TestAllLeastSquares() {
    TestRunner tr;
    RUN_TEST(tr, TestOLSPoly);
}


void TestOLSPoly() {
    {
    vector<double> xi = {1, 2};
    vector<double> yi = {1, 2};
    vector<double> res;
    ols_poly(xi, yi, 1, res);
    for (double& v : res) {
        v = roundTo(v, -6);
    }
    vector<double> needed = {0, 1};
    ASSERT_EQUAL(res, needed);
    }
    {
    vector<double> xi = {1};
    vector<double> yi = {10};
    vector<double> res;
    ols_poly(xi, yi, 0, res);
    for (double& v : res) {
        v = roundTo(v, -6);
    }
    vector<double> needed = {10};
    ASSERT_EQUAL(res, needed);
    }
}
