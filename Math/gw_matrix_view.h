#pragma once

#include <iostream>
#include <stdexcept>


namespace gwmath {

// MatrixView -- not owning wrapper for memory with matrix interface
template <typename T>
class MatrixView {
public:
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
  const T* operator[](std::size_t idx) const {return data_ + idx * col_count_;}
  std::size_t getRowCount() const { return row_count_;}
  std::size_t getColCount() const { return col_count_;}
private:
  T* data_;
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


// realization
template <typename T>
MatrixView<T>::MatrixView(std::size_t row_count, std::size_t col_count, T* data)
  : data_(data)
  , row_count_(row_count)
  , col_count_(col_count)
{}

// operators
template <typename T>
std::ostream& operator<<(std::ostream& out, const MatrixView<T>& m) {
  out << m.getNumRows() << " " << m.getNumColumns() << '\n';
  for (int row = 0; row < m.getNumRows(); ++row) {
    if (row > 0) {
      out << '\n';
    }
    for (int col = 0; col < m.getNumColumns(); ++col) {
      if (col > 0) {
        out << ' ';
      }
      out << m(row, col);
    }
  }
  return out;
}

template <typename T>
bool operator==(const MatrixView<T>& lhs, const MatrixView<T>& rhs) {
  if (lhs.getNumRows() != rhs.getNumRows() || lhs.getNumColumns() != rhs.getNumColumns()) {
    return false;
  }
  for (int ri = 0; ri < lhs.getNumRows(); ++ri) {
    for (int ci = 0; ci < lhs.getNumColumns(); ++ci) {
      if (lhs(ri, ci) != rhs(ri, ci)) return false;
    }
  }
  return true;
}

}  // namespace gwmath
