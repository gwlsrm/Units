// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "gwMatrixTests.h"
#include "gwmatrix.h"
#include "test_runner.h"

using namespace std;

void TestAllMatrix() {
    TestRunner tr;
    RUN_TEST(tr, TestConstructor);
    RUN_TEST(tr, TestAt);
}


void TestConstructor() {
    {
        DoubleMatrix m1, m2(0, 0);
        ASSERT_EQUAL(m1, m2);
    }
    {
        DoubleMatrix m1;
        ASSERT_EQUAL(m1.getRowCount(), 0u);
        ASSERT_EQUAL(m1.getColCount(), 0u);
    }
    {
        DoubleMatrix m1(10, 11);
        ASSERT_EQUAL(m1.getRowCount(), 10u);
        ASSERT_EQUAL(m1.getColCount(), 11u);
    }
    {
        DoubleMatrix m1(10, 10);
        ASSERT_EQUAL(m1.getRowCount(), 10u);
        ASSERT_EQUAL(m1.getColCount(), 10u);
    }
    {
        try {
            DoubleMatrix m1(-1, 10);
        } catch (out_of_range& e) {
            cerr << "OK TestConstructor: " << e.what() << endl;
        }
    }
    {
        DoubleMatrix m1{{1.2, 2.3}};
        ASSERT_EQUAL(m1.getRowCount(), 1u);
        ASSERT_EQUAL(m1.getColCount(), 2u);
        DoubleMatrix res(1, 2);
        res[0][0] = 1.2;
        res[0][1] = 2.3;
        ASSERT_EQUAL(m1, res);
    }
    {
        DoubleMatrix m1{{1.2, 2.3}, {2, 4}};
        ASSERT_EQUAL(m1.getRowCount(), 2u);
        ASSERT_EQUAL(m1.getColCount(), 2u);
        DoubleMatrix res(2, 2);
        res.at(0, 0) = 1.2;
        res.at(0, 1) = 2.3;
        res.at(1, 0) = 2;
        res.at(1, 1) = 4;
        ASSERT_EQUAL(m1, res);
    }
}

void TestAt() {
    {
        DoubleMatrix m1;
        try {
            m1.at(0,0);
        } catch (out_of_range& e) {
            cerr << "OK TestAt: " << e.what() << endl;
        }
    }
    {
        DoubleMatrix m(1, 1);
        m.at(0,0) = 100;
        ASSERT_EQUAL(m.at(0,0), 100);
    }
    {
        DoubleMatrix m(1, 2);
        m.at(0,0) = 1;
        m.at(0,1) = 2;
        ASSERT_EQUAL(m.at(0,0), 1);
        ASSERT_EQUAL(m.at(0,1), 2);
    }
}
