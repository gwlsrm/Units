// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "NumericIntegrationTests.h"
#include "numeric_integration.h"
#include "test_runner.h"
#include "profile.h"
#include "math_lib.h"
#include <cmath>
#include <iostream>

using namespace std;

void TestAllNumericIntegration() {
    TestRunner tr;
    RUN_TEST(tr, TestAveIntegration);
}

void TestAveIntegration() {
    {
        constexpr double EPS = 1e-6;
        auto f = [](double x){return 1.0 / sqrt(x);}; // 1 / sqrt(x) => I = 2 * sqrt(x)
        double res = aveIntegration(f, 1, 9, EPS);    // Int from 1 to 9: 2 * (sqrt(9) - sqrt(1)) = 4
        ASSERT_VALUE(approximatelyEqual(res, 4.0, EPS), res - 4.0, 0);
    }
    {
        auto f = [](double x){return 1.0 / sqrt(x);}; // 1 / sqrt(x) => I = 2 * sqrt(x)
        double res1 = aveIntegration(f, 1, 9, 20);    // Int from 1 to 9: 2 * (sqrt(9) - sqrt(1)) = 4
        double res2 = trapIntegration(f, 1, 9, 20);
        double res3 = trapIntegrationAdaptive(f, 1, 9, 20);
        cerr << "AveInt  = " << res1 << ", true res = 4, diff = " << res1 - 4.0 << " rel.diff = " << (res1/4.0 - 1)*100 << " %" << endl;
        cerr << "TrapInt = " << res2 << ", true res = 4, diff = " << res2 - 4.0 << " rel.diff = " << (res2/4.0 - 1)*100 << " %" << endl;
        cerr << "AdTrInt = " << res3 << ", true res = 4, diff = " << res3 - 4.0 << " rel.diff = " << (res3/4.0 - 1)*100 << " %" << endl;
    }
}

