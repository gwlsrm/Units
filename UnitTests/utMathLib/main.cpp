// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <iostream>
#include "MathLibTests.h"
#include "gwMatrixTests.h"
#include "sle_tests.h"
#include "NonLinearSolverTests.h"
#include "NumericIntegrationTests.h"
#include "leastsquaresTests.h"

using namespace std;

void TestAll() {
    // mathlib
    TestAllMathLib();
    // matrix
    TestAllMatrix();
    // sle
    TestAllSle();
    // non-linear solver
    TestAllNonLinearSolver();
    // least squares
    TestAllLeastSquares();
    // Integral calculation
    TestAllNumericIntegration();
}

int main()
{
    TestAll();
    cout << "All math tests is done" << endl;
    return 0;
}
