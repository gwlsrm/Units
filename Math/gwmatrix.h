#pragma once
#ifndef GWMATRIX_H_INCLUDED
#define GWMATRIX_H_INCLUDED

#include <iostream>
#include <initializer_list>
#include <stdexcept>
#include <tuple>
#include <vector>

#include "array_view.h"

/**@file
    @brief contains class with double matrix
*/

namespace gwmath {

/**
  \brief matrix class, that can store doubles

  DoubleMatrix is realized with vector of vector of double.
  It can chage its size, get rows, columns and cells
*/
template <typename T>
class Matrix {
public:
    using matrix_iterator = typename std::vector<T>::iterator;
    using matrix_const_iterator = typename std::vector<T>::const_iterator;
    // ctors
    // creates empty matrix
    Matrix() = default;
    // creates matrix num_rows * num_columns
    Matrix(std::size_t row_count, std::size_t col_count);
    // creates matrix from list of lists
    Matrix(const std::initializer_list<std::initializer_list<T>>& lst);
    // reset matrix size (no garantee about its values)
    void reset(std::size_t row_count, std::size_t col_count);
    // access operators
    const T& operator()(std::size_t row, std::size_t col) const {return data_[calcIdx(row, col)];}
    T& operator()(std::size_t row, std::size_t col) {return data_[calcIdx(row, col)];}
    const T& at(std::size_t row, std::size_t col) const {return data_.at(calcIdx(row, col));}
    T& at(std::size_t row, std::size_t col) {return data_.at(calcIdx(row, col));}
    ArrayView<T> operator[](std::size_t row) {
        return ArrayView<T>(col_count_, data_.data() + row*col_count_);}
    ConstArrayView<T> operator[](std::size_t row) const {
        return ConstArrayView<T>(col_count_, data_.data() + row*col_count_);}
    matrix_iterator begin() {return data_.begin();}
    matrix_iterator end() {return data_.end();}
    matrix_const_iterator begin() const {return data_.begin();}
    matrix_const_iterator end() const {return data_.end();}
    // getters
    std::size_t getRowCount() const {return row_count_;}
    std::size_t getColCount() const {return col_count_;}
    std::tuple<std::size_t, std::size_t> shape() const {return {row_count_, col_count_};}
    T* data() { return data_.data();}
    const T* data() const { return data_.data();}
    // methods
    bool isSquare() const {return row_count_ == col_count_;}
private:
    std::size_t row_count_ = 0;
    std::size_t col_count_ = 0;
    std::vector<T> data_;

    // calculates internal index in solid memory (data_)
    std::size_t calcIdx(std::size_t row, std::size_t col) const {return row * col_count_ + col;}
};

using DoubleMatrix = Matrix<double>;

// operations with matrix
DoubleMatrix operator+(const DoubleMatrix& lhs, const DoubleMatrix& rhs);
DoubleMatrix operator-(const DoubleMatrix& lhs, const DoubleMatrix& rhs);
bool operator==(const DoubleMatrix& lhs, const DoubleMatrix& rhs);
std::istream& operator>>(std::istream& in, DoubleMatrix& matrix);
std::ostream& operator<<(std::ostream& out, const DoubleMatrix& matrix);


// realization
template <typename T>
Matrix<T>::Matrix(std::size_t row_count, std::size_t col_count)
  : row_count_(row_count)
  , col_count_(col_count)
  , data_(row_count * col_count)
{}

template <typename T>
Matrix<T>::Matrix(const std::initializer_list<std::initializer_list<T>>& lst)
{
    row_count_ = lst.size();
    bool is_first = true;
    for (const auto& row : lst) {
        if (is_first) {
            col_count_ = row.size();
            is_first = false;
        } else if (col_count_ != row.size()) {
            throw std::length_error("All rows must have same length");
        }
        data_.insert(data_.end(), row);
    }
}

template <typename T>
void Matrix<T>::reset(std::size_t row_count, std::size_t col_count) {
    row_count_ = row_count;
    col_count_ = col_count;
    data_.resize(row_count_ * col_count_);
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
bool operator==(const Matrix<T>& lhs, const Matrix<T>& rhs) {
    if (lhs.shape() != rhs.shape()) {
        return false;
    }
    for (std::size_t row = 0; row < lhs.getRowCount(); ++row) {
        for (std::size_t column = 0; column < lhs.getColCount(); ++column) {
            if (lhs(row, column) != rhs(row, column)) return false;
        }
    }
    return true;
}

template <typename T>
std::ostream& operator<<(std::ostream& out, const Matrix<T>& matrix) {
    out << "[\n";
    for (std::size_t row = 0; row < matrix.getRowCount(); ++row) {
        out << " [";
        for (std::size_t column = 0; column < matrix.getColCount(); ++column) {
            if (column > 0) {
                out << ", ";
            }
            out << matrix.at(row, column);
        }
        out << "],\n";
    }
    out << "]";
    return out;
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
