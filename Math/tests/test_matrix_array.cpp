#define BOOST_TEST_MODULE math_test_module
#include <boost/test/unit_test.hpp>
#include <iostream>
#include <tuple>
#include <vector>

#include "array_view.h"
#include "gwmatrix.h"
#include "gw_static_matrix.h"

using namespace std;
using namespace gwmath;
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

BOOST_AUTO_TEST_SUITE(matrix_test_suite)

    // Double matrix
    BOOST_AUTO_TEST_CASE(test_matrix_empty_ctor) {
        Matrix<double> m;
        BOOST_TEST(m.getRowCount() == 0);
        BOOST_TEST(m.getColCount() == 0);
    }

    BOOST_AUTO_TEST_CASE(test_matrix_ctors) {
        Matrix<int> m(2, 3);
        BOOST_TEST(m.getRowCount() == 2u);
        BOOST_TEST(m.getColCount() == 3u);
    }

    BOOST_AUTO_TEST_CASE(test_matrix_ctor_init) {
        Matrix<int> m{{1, 2, 3}, {5, 6, 7}};
        BOOST_TEST(m.getRowCount() == 2u);
        BOOST_TEST(m.getColCount() == 3u);
        BOOST_TEST(m(0, 0) == 1);
        BOOST_TEST(m(0, 1) == 2);
        BOOST_TEST(m(0, 2) == 3);
        BOOST_TEST(m(1, 0) == 5);
        BOOST_TEST(m(1, 1) == 6);
        BOOST_TEST(m(1, 2) == 7);
    }

    BOOST_AUTO_TEST_CASE(test_matrix_copy_ctor) {
        Matrix<int> m{{1, 2, 3}, {5, 6, 7}};
        auto m2 = m;
        m(0, 1) = 42;
        BOOST_TEST(m2.getRowCount() == 2u);
        BOOST_TEST(m2.getColCount() == 3u);
        BOOST_TEST(m2(0, 0) == 1);
        BOOST_TEST(m2(0, 1) == 2);
        BOOST_TEST(m2(0, 2) == 3);
        BOOST_TEST(m2(1, 0) == 5);
        BOOST_TEST(m2(1, 1) == 6);
        BOOST_TEST(m2(1, 2) == 7);
    }

    BOOST_AUTO_TEST_CASE(test_matrix_access_operator) {
        Matrix<int> m{{1, 2, 3}, {5, 6, 7}};
        BOOST_TEST(m(0, 1) == 2);
        m(0, 1) = 42;
        BOOST_TEST(m(0, 1) == 42);
        m(1, 2) = -m(1, 2);
        BOOST_TEST(m(1, 2) == -7);
        Matrix<int> expected{{1, 42, 3}, {5, 6, -7}};
        BOOST_TEST(m == expected);
    }

    BOOST_AUTO_TEST_CASE(test_matrix_iteration) {
        Matrix<int> m{{1, 2, 3}, {4, 5, 6}};
        int i = 1;
        for (int v : m) {
            BOOST_TEST(v == i);
            ++i;
        }
    }

    BOOST_AUTO_TEST_CASE(test_matrix_row_read_access) {
        Matrix<int> m{{1, 2, 3}, {5, 6, 7}, {12, 13, 14}};
        auto row = m[1];
        vector<int> expected_row{5, 6, 7};
        ArrayView<int> expected(3, expected_row.data());
        BOOST_TEST(row.size() == 3u);
        BOOST_TEST(row == expected);
    }

    BOOST_AUTO_TEST_CASE(test_matrix_row_write_access) {
        Matrix<int> m{{1, 2, 3}, {5, 6, 7}, {12, 13, 14}};
        auto row = m[1];
        row[1] = 42;
        m[1][0] = 32;
        vector<int> expected_row{32, 42, 7};
        ArrayView<int> expected(3, expected_row.data());
        BOOST_TEST(row.size() == 3u);
        BOOST_TEST(row == expected);
    }

    // array view
    BOOST_AUTO_TEST_CASE(test_array_view_copy) {
        vector<int> v1{1, 2, 3, 4, 5};
        ArrayView<int> view1(v1.size(), v1.data());
        vector<int> v2{6, 7, 8, 9, 10};
        ArrayView<int> view2(v2.size(), v2.data());
        vector<int> v_expected{1, 2, 3, 4, 5};
        ArrayView<int> view_expected(v_expected.size(), v_expected.data());
        BOOST_TEST(v2 != v_expected);
        BOOST_TEST(!(view2 == view_expected));
        view2.copy_from(view1);
        BOOST_TEST(v2 == v_expected);
        BOOST_TEST(view2 == view_expected);
        v1.clear();
        BOOST_TEST(view2 == view_expected);
    }

    // static matrix
    BOOST_AUTO_TEST_CASE(test_static_matrix_empty_ctor) {
        StaticMatrix<double, 0, 0> m;
        BOOST_TEST(m.getRowCount() == 0);
        BOOST_TEST(m.getColCount() == 0);
    }

    BOOST_AUTO_TEST_CASE(test_static_matrix_ctors) {
        StaticMatrix<int, 2, 3> m;
        BOOST_TEST(m.getRowCount() == 2u);
        BOOST_TEST(m.getColCount() == 3u);
    }

    BOOST_AUTO_TEST_CASE(test_static_matrix_ctor_init) {
        StaticMatrix<int, 2, 3> m{{1, 2, 3}, {5, 6, 7}};
        BOOST_TEST(m.getRowCount() == 2u);
        BOOST_TEST(m.getColCount() == 3u);
        BOOST_TEST(m(0, 0) == 1);
        BOOST_TEST(m(0, 1) == 2);
        BOOST_TEST(m(0, 2) == 3);
        BOOST_TEST(m(1, 0) == 5);
        BOOST_TEST(m(1, 1) == 6);
        BOOST_TEST(m(1, 2) == 7);
    }

    BOOST_AUTO_TEST_CASE(test_static_matrix_copy_ctor) {
        StaticMatrix<int, 2, 3> m{{1, 2, 3}, {5, 6, 7}};
        auto m2 = m;
        m(0, 1) = 42;
        BOOST_TEST(m2.getRowCount() == 2u);
        BOOST_TEST(m2.getColCount() == 3u);
        BOOST_TEST(m2(0, 0) == 1);
        BOOST_TEST(m2(0, 1) == 2);
        BOOST_TEST(m2(0, 2) == 3);
        BOOST_TEST(m2(1, 0) == 5);
        BOOST_TEST(m2(1, 1) == 6);
        BOOST_TEST(m2(1, 2) == 7);
    }

    BOOST_AUTO_TEST_CASE(test_static_matrix_access_operator) {
        StaticMatrix<int, 2, 3> m{{1, 2, 3}, {5, 6, 7}};
        BOOST_TEST(m(0, 1) == 2);
        m(0, 1) = 42;
        BOOST_TEST(m(0, 1) == 42);
        m(1, 2) = -m(1, 2);
        BOOST_TEST(m(1, 2) == -7);
        StaticMatrix<int, 2, 3> expected{{1, 42, 3}, {5, 6, -7}};
        BOOST_TEST(m == expected);
    }

    BOOST_AUTO_TEST_CASE(test_static_matrix_iteration) {
        StaticMatrix<int, 2, 3> m{{1, 2, 3}, {4, 5, 6}};
        int i = 1;
        for (int v : m) {
            BOOST_TEST(v == i);
            ++i;
        }
    }

    BOOST_AUTO_TEST_CASE(test_static_matrix_row_read_access) {
        StaticMatrix<int, 3, 3> m{{1, 2, 3}, {5, 6, 7}, {12, 13, 14}};
        auto row = m[1];
        vector<int> expected_row{5, 6, 7};
        ArrayView<int> expected(3, expected_row.data());
        BOOST_TEST(row.size() == 3u);
        BOOST_TEST(row == expected);
    }

    BOOST_AUTO_TEST_CASE(test_static_matrix_row_write_access) {
        StaticMatrix<int, 3, 3> m{{1, 2, 3}, {5, 6, 7}, {12, 13, 14}};
        auto row = m[1];
        row[1] = 42;
        m[1][0] = 32;
        vector<int> expected_row{32, 42, 7};
        ArrayView<int> expected(3, expected_row.data());
        BOOST_TEST(row.size() == 3u);
        BOOST_TEST(row == expected);
    }

    BOOST_AUTO_TEST_CASE(test_static_matrix_dot) {
        StaticMatrix<int, 2, 3> a{{1, 2, 3}, {5, 6, 7}};
        StaticMatrix<int, 3, 2> b{{8, 9}, {-1, 10}, {3, -2}};
        StaticMatrix<int, 2, 2> expected{{15, 23}, {55, 91}};
        auto res = dot(a, b);
        BOOST_TEST(res == expected);
    }

    BOOST_AUTO_TEST_CASE(test_static_matrix_transpose) {
        StaticMatrix<int, 3, 3> a{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
        StaticMatrix<int, 3, 3> expected{{1, 4, 7}, {2, 5, 8}, {3, 6, 9}};
        auto res = transponse(a);
        BOOST_TEST(res == expected);
    }


BOOST_AUTO_TEST_SUITE_END()
