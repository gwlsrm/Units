#pragma once

#include <iostream>
#include <stdexcept>
#include <tuple>

#include "array_view.h"


namespace gwmath {

// MatrixView -- not owning wrapper for memory with matrix interface
template <typename T>
class MatrixView {
public:
    MatrixView() = default;
    MatrixView(std::size_t row_count, std::size_t col_count, T* data);
    // iterators
    auto begin() {return data_;}
    const auto begin() const {return data_;}
    auto end() {return data_ + row_count_ * col_count_;}
    const auto end() const {return data_ + row_count_ * col_count_;}
    // getters
    const T& operator()(std::size_t row, std::size_t col) const {
        return data_[calcIdx(row, col)];
    }
    T& operator()(std::size_t row, std::size_t col) {return data_[calcIdx(row, col)];}
    const T& at(std::size_t row_idx, std::size_t col_idx) const {
        if (row_idx >= row_count_ || col_idx >= col_count_) {
            throw std::out_of_range("row_idx or col_idx is out of range");
        }
        return data_[calcIdx(row_idx, col_idx)];
    }
    T& at(std::size_t row_idx, std::size_t col_idx) {
        if (row_idx >= row_count_ || col_idx >= col_count_) {
            throw std::out_of_range("row_idx or col_idx is out of range");
        }
        return data_[calcIdx(row_idx, col_idx)];
    }
    ArrayView<T> operator[](std::size_t row) {
    return ArrayView<T>(col_count_, data_ + row*col_count_);}
    ConstArrayView<T> operator[](std::size_t row) const {
    return ConstArrayView<T>(col_count_, data_ + row*col_count_);}
    T* data() { return data_.data();}
    const T* data() const { return data_.data();}

    std::size_t getRowCount() const { return row_count_;}
    std::size_t getColCount() const { return col_count_;}
    std::tuple<std::size_t, std::size_t> shape() const {return {row_count_, col_count_};}
    // methods
    bool isSquare() const {return row_count_ == col_count_;}

protected:
    T* data_ = nullptr;
    std::size_t row_count_ = 0;
    std::size_t col_count_ = 0;

    std::size_t calcIdx(std::size_t row, std::size_t col) const {
        return row * col_count_ + col;
    }
};
// operators
template<typename T>
std::ostream& operator<<(std::ostream& out, const MatrixView<T>& m);
template<typename T>
bool operator==(const MatrixView<T>& lhs, const MatrixView<T>& rhs);
template<typename T>
bool operator!=(const MatrixView<T>& lhs, const MatrixView<T>& rhs);


// realization
template <typename T>
MatrixView<T>::MatrixView(std::size_t row_count, std::size_t col_count, T* data)
  : data_(data)
  , row_count_(row_count)
  , col_count_(col_count)
{}

// operators
template <typename T>
std::ostream& operator<<(std::ostream& out, const MatrixView<T>& matrix) {
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
bool operator==(const MatrixView<T>& lhs, const MatrixView<T>& rhs) {
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
bool operator!=(const MatrixView<T>& lhs, const MatrixView<T>& rhs) {
    return !(lhs == rhs);
}


}  // namespace gwmath
