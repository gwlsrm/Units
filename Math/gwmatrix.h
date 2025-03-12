#pragma once
#ifndef GWMATRIX_H_INCLUDED
#define GWMATRIX_H_INCLUDED

#include <iostream>
#include <initializer_list>
#include <stdexcept>
#include <vector>

#include "array_view.h"
#include "gw_matrix_view.h"

/**@file
    @brief contains class with double matrix
*/

namespace gwmath {

/**
  \brief matrix class
*/
template <typename T>
class Matrix : public MatrixView<T> {
public:
    // creates matrix num_rows * num_columns
    Matrix(std::size_t row_count = 0, std::size_t col_count = 0);
    // creates matrix from list of lists
    Matrix(const std::initializer_list<std::initializer_list<T>>& lst);
    Matrix(const Matrix<T>& other);
    Matrix(Matrix<T>&& other);
    Matrix<T>& operator=(const Matrix<T>& other);
    Matrix<T>& operator=(Matrix<T>&& other);

    // reset matrix size (no garantee about its values)
    void reset(std::size_t row_count, std::size_t col_count);

private:
    std::vector<T> vector_data_;
};

using DoubleMatrix = Matrix<double>;

// operations with matrix
template <typename T>
Matrix<T> operator+(const Matrix<T>& lhs, const Matrix<T>& rhs);
template <typename T>
Matrix<T> operator-(const Matrix<T>& lhs, const Matrix<T>& rhs);
template <typename T>
std::istream& operator>>(std::istream& in, Matrix<T>& matrix);


// realization
template <typename T>
Matrix<T>::Matrix(std::size_t row_count, std::size_t col_count)
  : MatrixView<T>(row_count, col_count, nullptr)
  , vector_data_(row_count * col_count)
{
    MatrixView<T>::data_ = vector_data_.data();
}

template <typename T>
Matrix<T>::Matrix(const std::initializer_list<std::initializer_list<T>>& lst)
{
    MatrixView<T>::row_count_ = lst.size();
    bool is_first = true;
    for (const auto& row : lst) {
        if (is_first) {
            MatrixView<T>::col_count_ = row.size();
            is_first = false;
        } else if (MatrixView<T>::col_count_ != row.size()) {
            throw std::length_error("All rows must have same length");
        }
        vector_data_.insert(vector_data_.end(), row);
    }
    MatrixView<T>::data_ = vector_data_.data();
}

template <typename T>
Matrix<T>::Matrix(const Matrix<T>& other)
    : MatrixView<T>(other.row_count_, other.col_count_, nullptr)
    , vector_data_(other.vector_data_)
{
    MatrixView<T>::data_ = vector_data_.data();
}

template <typename T>
Matrix<T>::Matrix(Matrix<T>&& other)
    : MatrixView<T>(other.row_count_, other.col_count_, nullptr)
    , vector_data_(std::move(other.vector_data_))
{
    MatrixView<T>::data_ = vector_data_.data();
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other) {
    if (&other == this) {
        return *this;
    }
    vector_data_ = other.vector_data_;
    MatrixView<T>::row_count_ = other.row_count_;
    MatrixView<T>::col_count_ = other.col_count_;
    MatrixView<T>::data_ = vector_data_.data();
    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator=(Matrix<T>&& other) {
    if (&other == this) {
        return *this;
    }
    vector_data_ = std::move(other.vector_data_);
    MatrixView<T>::row_count_ = other.row_count_;
    MatrixView<T>::col_count_ = other.col_count_;
    MatrixView<T>::data_ = vector_data_.data();
    return *this;
}

template <typename T>
void Matrix<T>::reset(std::size_t row_count, std::size_t col_count) {
    MatrixView<T>::row_count_ = row_count;
    MatrixView<T>::col_count_ = col_count;
    vector_data_.resize(MatrixView<T>::row_count_ * MatrixView<T>::col_count_);
    MatrixView<T>::data_ = vector_data_.data();
}


template <typename T>
Matrix<T> operator+(const Matrix<T>& lhs, const Matrix<T>& rhs) {
    if (lhs.shape() != rhs.shape()) {
        throw std::invalid_argument("Matrices must have the same shape");
    }

    Matrix result(lhs.getRowCount(), lhs.getColCount());
    for (std::size_t row = 0; row < result.getRowCount(); ++row) {
        for (std::size_t column = 0; column < result.getColCount(); ++column) {
            result(row, column) = lhs(row, column) + rhs(row, column);
        }
    }

    return result;
}

template <typename T>
Matrix<T> operator-(const Matrix<T>& lhs, const Matrix<T>& rhs) {
    if (lhs.shape() != rhs.shape()) {
        throw std::invalid_argument("Matrices must have the same shape");
    }

    Matrix result(lhs.getRowCount(), lhs.getColCount());
    for (std::size_t row = 0; row < result.getRowCount(); ++row) {
        for (std::size_t column = 0; column < result.getColCount(); ++column) {
            result(row, column) = lhs(row, column) - rhs(row, column);
        }
    }

    return result;
}

template <typename T>
std::istream& operator>>(std::istream& in, Matrix<T>& matrix) {
    std::size_t num_rows, num_columns;
    in >> num_rows >> num_columns;

    matrix.reset(num_rows, num_columns);
    for (std::size_t row = 0; row < num_rows; ++row) {
        for (std::size_t column = 0; column < num_columns; ++column) {
            in >> matrix(row, column);
        }
    }
    return in;
}


}  // namespace gwmath

#endif // GWMATRIX_H_INCLUDED
