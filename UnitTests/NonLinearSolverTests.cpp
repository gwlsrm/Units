// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "NonLinearSolverTests.h"
#include "test_runner.h"
#include "profile.h"
#include "nonlinearsolver.h"
#include "math_lib.h"

using namespace std;

void TestAllNonLinearSolver() {
    TestRunner tr;
    RUN_TEST(tr, TestGetRootNewton);
    //TestGetRootNewtonDuration();
}

void TestGetRootNewton() {
    {
        const double EPS = 1e-6;
        auto f = [](double x){ return x * x;};
        auto fdiff = [](double x){ return 2 * x;};
        if (!approximatelyEqual(getRootNewton(f, fdiff, 1, EPS), 0, EPS)) {
            cout << getRootNewton(f, fdiff, 1, EPS) << endl;
        }
        ASSERT(approximatelyEqual(getRootNewton(f, fdiff, 1, EPS), 0, EPS));
    }
    {
        const double EPS = 1e-6;
        auto f = [](double x){ return x * x * x;};
        auto fdiff = [](double x){ return 3 * x * x;};
        if (!approximatelyEqual(getRootNewton(f, fdiff, 1, EPS), 0, EPS)) {
            cout << getRootNewton(f, fdiff, 1, EPS) << endl;
        }
        ASSERT(approximatelyEqual(getRootNewton(f, fdiff, 1, EPS), 0, EPS));
    }
}

void TestGetRootNewtonDuration() {
    const double EPS = 1e-6;
    constexpr int N = 1'000'000;
    auto f = [](double x){ return x * x;};
    auto fdiff = [](double x){ return 2 * x;};
    {   LOG_DURATION("Newton method");
        double value = 0;
        for (int i = 0; i < N; ++i) {
            value += getRootNewton(f, fdiff, 1, EPS, 100);
        }
        cout << value << '\n';
    }
    {   LOG_DURATION("Newton simple method");
        double value = 0;
        for (int i = 0; i < N; ++i) {
            value += getRootNewtonSimple(f, fdiff, 1, EPS);
        }
        cout << value << '\n';
    }
}


