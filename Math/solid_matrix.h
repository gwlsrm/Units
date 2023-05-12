#pragma once
#ifndef SOLID_MATRIX_H_INCLUDED
#define SOLID_MATRIX_H_INCLUDED

#include <vector>
#include <stdexcept>
#include <iostream>

/**
  @brief matrix for POD types: int, double, etc

  Solid matrix (it uses single piece of memory)
*/
template <typename T>
class Matrix {
public:
  // ctors, dtors
  Matrix() = default;
  Matrix(std::size_t num_rows, std::size_t num_cols) {reset(num_rows, num_cols);}
  explicit Matrix(std::size_t sze) : Matrix(sze, sze) {};
  /// Changes matrix size
  void reset(std::size_t num_rows, std::size_t num_cols);
  // access operators
  T operator()(std::size_t row, std::size_t col) const {
    return data_[num_cols_ * row + col];
  }
  T& operator()(std::size_t row, std::size_t col) {
    return data_[num_cols_ * row + col];
  }
  T at(std::size_t row, std::size_t col) const {
    return data_.at(num_cols_ * row + col);
  }
  T& at(std::size_t row, std::size_t col) {
    return data_.at(num_cols_ * row + col);
  }
  const T* operator[](std::size_t row) const {
    return data_.data() + row*num_cols_;
  }
  T* operator[](std::size_t row) {
    return data_.data() + row*num_cols_;
  }
  // getters
  std::size_t getRowCount() const {return num_rows_;}
  std::size_t getColCount() const {return num_cols_;}
  bool isSquare() const {return num_rows_ == num_cols_;}
private:
  std::size_t num_rows_ = 0;
  std::size_t num_cols_ = 0;
  std::vector<T> data_;
};

template <typename T>
void Matrix<T>::reset(std::size_t num_rows, std::size_t num_cols) {
    num_rows_ = num_rows;
    num_cols_ = num_cols;
    data_.resize(num_rows_ * num_cols_, T{});
}

// operators
template  <typename T>
std::ostream& operator<<(std::ostream& out, const Matrix<T>& m) {
  out << m.getRowCount() << " " << m.getColCount() << '\n';
  for (std::size_t row = 0; row < m.getRowCount(); ++row) {
    if (row > 0) {
      out << '\n';
    }
    for (std::size_t col = 0; col < m.getColCount(); ++col) {
      if (col > 0) {
        out << ' ';
      }
      out << m(row, col);
    }
  }
  return out;
}

template  <typename T>
bool operator==(const Matrix<T>& lhs, const Matrix<T>& rhs) {
  if (lhs.getRowCount() != rhs.getRowCount() || lhs.getColCount() != rhs.getColCount()) {
    return false;
  }
  for (std::size_t ri = 0; ri < lhs.getRowCount(); ++ri) {
    for (std::size_t ci = 0; ci < lhs.getColCount(); ++ci) {
      if (lhs.at(ri, ci) != rhs.at(ri, ci)) return false;
    }
  }
  return true;
}

template  <typename T>
Matrix<T> operator+(const Matrix<T>& lhs, const Matrix<T>& rhs) {
  if (lhs.getRowCount() != rhs.getRowCount() || lhs.getColCount() != rhs.getColCount()) {
    throw std::invalid_argument("Exception: different matrices sizes");
  }
  Matrix<T> res(lhs.getRowCount(), lhs.getColCount());
  for (int ri = 0; ri < lhs.getRowCount(); ++ri) {
    for (int ci = 0; ci < lhs.getColCount(); ++ci) {
      res(ri, ci) = lhs(ri, ci) + rhs(ri, ci);
    }
  }
  return res;
}


#endif // SOLID_MATRIX_H_INCLUDED
