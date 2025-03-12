#pragma once

#include <array>
#include <iostream>
#include <initializer_list>
#include <stdexcept>

#include "array_view.h"
#include "gw_matrix_view.h"

/**@file
    @brief contains class with double matrix
*/

namespace gwmath {

/**
  \brief matrix class with static array as data
*/
template <typename T, std::size_t N, std::size_t M>
class StaticMatrix : public MatrixView<T> {
public:
    // creates matrix num_rows * num_columns
    StaticMatrix();
    // creates matrix from list of lists
    StaticMatrix(const std::initializer_list<std::initializer_list<T>>& lst);
    StaticMatrix(const StaticMatrix<T, N, M>& other);
    StaticMatrix(StaticMatrix<T, N, M>&& other);
    StaticMatrix<T, N, M>& operator=(const StaticMatrix<T, N, M>& other);
    StaticMatrix<T, N, M>& operator=(StaticMatrix<T, N, M>&& other);
    static StaticMatrix<T, N, M> makeEye();
private:
    std::array<T, N*M> array_data_;
};

using StaticDoubleMatrix3x3 = StaticMatrix<double, 3, 3>;
using StaticDoubleVector3 = StaticMatrix<double, 3, 1>;

// operations with matrix
template <typename T, std::size_t N, std::size_t M>
StaticMatrix<T, N, M> operator+(const StaticMatrix<T, N, M>& lhs, const StaticMatrix<T, N, M>& rhs);
template <typename T, std::size_t N, std::size_t M>
StaticMatrix<T, N, M> operator-(const StaticMatrix<T, N, M>& lhs, const StaticMatrix<T, N, M>& rhs);
template <typename T, std::size_t N, std::size_t M>
StaticMatrix<T, N, M> operator*(const StaticMatrix<T, N, M>& matrix, const T& number);
template <typename T, std::size_t N, std::size_t M>
StaticMatrix<T, N, M> operator*(const StaticMatrix<T, N, M>& lhs, const StaticMatrix<T, N, M>& rhs);
template <typename T, std::size_t N, std::size_t M>
std::istream& operator>>(std::istream& in, StaticMatrix<T, N, M>& matrix);
template <typename T, std::size_t N, std::size_t M, std::size_t K>
StaticMatrix<T, N, K> dot(const StaticMatrix<T, N, M>& lhs, const StaticMatrix<T, M, K>& rhs);
template <typename T, std::size_t N>
StaticMatrix<T, N, N> transponse(const StaticMatrix<T, N, N>& matrix);


// realization
template <typename T, std::size_t N, std::size_t M>
StaticMatrix<T, N, M>::StaticMatrix()
  : MatrixView<T>(N, M, nullptr)
{
    MatrixView<T>::data_ = array_data_.data();
}

template <typename T, std::size_t N, std::size_t M>
StaticMatrix<T, N, M>::StaticMatrix(const std::initializer_list<std::initializer_list<T>>& lst)
{
    MatrixView<T>::row_count_ = lst.size();
    if (MatrixView<T>::row_count_ != N) {
        throw std::length_error("Static matrix has incorrect number of rows");
    }
    bool is_first = true;
    std::size_t i = 0;
    for (const auto& row : lst) {
        if (is_first) {
            MatrixView<T>::col_count_ = row.size();
            if (MatrixView<T>::col_count_ != M) {
                throw std::length_error("Static matrix has incorrect number of cols");
            }
            is_first = false;
        } else if (MatrixView<T>::col_count_ != row.size()) {
            throw std::length_error("All rows must have same length");
        }
        std::copy(row.begin(), row.end(), array_data_.begin() + i*M);
        i++;
    }

    MatrixView<T>::data_ = array_data_.data();
}

template <typename T, std::size_t N, std::size_t M>
StaticMatrix<T, N, M>::StaticMatrix(const StaticMatrix<T, N, M>& other)
    : MatrixView<T>(other.row_count_, other.col_count_, nullptr)
    , array_data_(other.array_data_)
{
    MatrixView<T>::data_ = array_data_.data();
}

template <typename T, std::size_t N, std::size_t M>
StaticMatrix<T, N, M>::StaticMatrix(StaticMatrix<T, N, M>&& other)
    : MatrixView<T>(other.row_count_, other.col_count_, nullptr)
    , array_data_(std::move(other.array_data_))
{
    MatrixView<T>::data_ = array_data_.data();
}

template <typename T, std::size_t N, std::size_t M>
StaticMatrix<T, N, M>& StaticMatrix<T, N, M>::operator=(const StaticMatrix<T, N, M>& other) {
    if (&other == this) {
        return *this;
    }
    array_data_ = other.array_data_;
    MatrixView<T>::row_count_ = other.row_count_;
    MatrixView<T>::col_count_ = other.col_count_;
    MatrixView<T>::data_ = array_data_.data();
    return *this;
}

template <typename T, std::size_t N, std::size_t M>
StaticMatrix<T, N, M>& StaticMatrix<T, N, M>::operator=(StaticMatrix<T, N, M>&& other) {
    if (&other == this) {
        return *this;
    }
    array_data_ = std::move(other.array_data_);
    MatrixView<T>::row_count_ = other.row_count_;
    MatrixView<T>::col_count_ = other.col_count_;
    MatrixView<T>::data_ = array_data_.data();
    return *this;
}

template <typename T, std::size_t N, std::size_t M>
StaticMatrix<T, N, M> StaticMatrix<T, N, M>::makeEye() {
    static_assert(N == M, "only for square matrices");
    StaticMatrix<T, N, M> m;
    for (std::size_t i = 0; i < N; ++i) {
        for (std::size_t j = 0; j < M; ++j) {
            m(i, j) = i == j ? 1 : 0;
        }
    }
    return m;
}

template <typename T, std::size_t N, std::size_t M>
StaticMatrix<T, N, M> operator+(const StaticMatrix<T, N, M>& lhs, const StaticMatrix<T, N, M>& rhs) {
    StaticMatrix<T, N, M> result;
    for (std::size_t row = 0; row < result.getRowCount(); ++row) {
        for (std::size_t column = 0; column < result.getColCount(); ++column) {
            result(row, column) = lhs(row, column) + rhs(row, column);
        }
    }

    return result;
}

template <typename T, std::size_t N, std::size_t M>
StaticMatrix<T, N, M> operator-(const StaticMatrix<T, N, M>& lhs, const StaticMatrix<T, N, M>& rhs) {
    StaticMatrix<T, N, M> result;
    for (std::size_t row = 0; row < result.getRowCount(); ++row) {
        for (std::size_t column = 0; column < result.getColCount(); ++column) {
            result(row, column) = lhs(row, column) - rhs(row, column);
        }
    }

    return result;
}

template <typename T, std::size_t N, std::size_t M>
StaticMatrix<T, N, M> operator*(const StaticMatrix<T, N, M>& matrix, const T& number) {
    StaticMatrix<T, N, M> result;
    for (std::size_t row = 0; row < result.getRowCount(); ++row) {
        for (std::size_t column = 0; column < result.getColCount(); ++column) {
            result(row, column) = matrix(row, column) * number;
        }
    }

    return result;
}

template <typename T, std::size_t N, std::size_t M>
StaticMatrix<T, N, M> operator*(const StaticMatrix<T, N, M>& lhs, const StaticMatrix<T, N, M>& rhs) {
    StaticMatrix<T, N, M> result;
    for (std::size_t row = 0; row < result.getRowCount(); ++row) {
        for (std::size_t column = 0; column < result.getColCount(); ++column) {
            result(row, column) = lhs(row, column) * rhs(row, column);
        }
    }

    return result;
}



template <typename T, std::size_t N, std::size_t M>
std::istream& operator>>(std::istream& in, StaticMatrix<T, N, M>& matrix) {
    std::size_t num_rows, num_columns;
    in >> num_rows >> num_columns;
    if (num_rows != N || num_columns != M) {
        throw std::length_error("incorrect matrix shape for >>");
    }

    for (std::size_t row = 0; row < num_rows; ++row) {
        for (std::size_t column = 0; column < num_columns; ++column) {
            in >> matrix(row, column);
        }
    }
    return in;
}


template <typename T, std::size_t N, std::size_t M, std::size_t K>
StaticMatrix<T, N, K> dot(const StaticMatrix<T, N, M>& lhs, const StaticMatrix<T, M, K>& rhs) {
    StaticMatrix<T, N, K> result;
    for (std::size_t row = 0; row < N; ++row) {
        for (std::size_t column = 0; column < K; ++column) {
            result(row, column) = 0 ;
            for (std::size_t i = 0; i < M; ++i) {
                result(row, column) += lhs(row, i) * rhs(i, column);
            }
        }
    }

    return result;
}

template <typename T, std::size_t N>
StaticMatrix<T, N, N> transponse(const StaticMatrix<T, N, N>& matrix) {
    StaticMatrix<T, N, N> res;
    for (std::size_t i = 0; i < N; ++i) {
        for (std::size_t j = 0; j < N; ++j) {
            res(j, i) = matrix(i, j);
        }
    }
    return res;
}


}  // namespace gwmath
