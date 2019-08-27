// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "sle_tests.h"
#include "sle.h"
#include <vector>
#include "gwmatrix.h"
#include "math_lib.h"
#include "test_runner.h"
#include "Container_output.h"

using namespace std;

void TestAllSle() {
    TestRunner tr;
    RUN_TEST(tr, TestGaussianElimination);
    RUN_TEST(tr, TestCholeckyElimination);
}

void TestGaussianElimination() {
    {
        // x = 2.3; y = 4.2;
        DoubleMatrix a =
            {{1, 0},
             {0, 1}};
        vector<double> b{2.3, 4.2};
        vector<double> res{2.3, 4.2};
        ASSERT_EQUAL(gauss(a, b), res);
    }
    {
        // x = 2.3; y = 4.2;
        DoubleMatrix a =
            {{2, 3},
             {3, 5}};
        vector<double> b{3, 5};
        vector<double> res{0, 1};
        ASSERT_EQUAL(gauss(a, b), res);
    }
}

void TestCholeckyElimination() {
    {
        // x = 2.3; y = 4.2;
        DoubleMatrix a =
            {{1, 0},
             {0, 1}};
        vector<double> b{2.3, 4.2};
        vector<double> res{2.3, 4.2};
        ASSERT_EQUAL(chol(a, b), res);
    }
    {
        // x = 2.3; y = 4.2;
        DoubleMatrix a =
            {{2, 3},
             {3, 5}};
        vector<double> b{3, 5};
        vector<double> res{0, 1};
        vector<double> ch = chol(a, b);
        for (double& v : ch) {
            v = roundTo(v, -6);
        }
        ASSERT_EQUAL(ch, res);
    }
}
