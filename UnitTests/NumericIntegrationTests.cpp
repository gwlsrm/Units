// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "NumericIntegrationTests.h"
#include "numeric_integration.h"
#include "test_runner.h"
#include "profile.h"
#include "math_lib.h"
#include <cmath>

void TestAllNumericIntegration() {
    TestRunner tr;
    RUN_TEST(tr, TestAveIntegration);
}

void TestAveIntegration() {
    {
        constexpr double EPS = 1e-6;
        auto f = [](double x){return 1.0 / sqrt(x);};
        double res = aveIntegration(f, 1, 9, EPS);
        ASSERT_VALUE(approximatelyEqual(res, 4.0, EPS), res - 4.0, 0);
    }
}

