#ifndef SOLID_MATRIX_H_INCLUDED
#define SOLID_MATRIX_H_INCLUDED

#include <vector>
#include <stdexcept>

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
  void reset(std::size_t num_rows, std::size_t num_cols) {
    num_rows_ = num_rows;
    num_cols_ = num_cols;
    data_.resize(num_rows_, num_cols_);
  }
  // access operators
  T operator()(std::size_t row, std::size_t col) const {
    std::size_t idx = num_cols_ * row + col;
    return data_[idx];
  }
  T& operator()(std::size_t row, std::size_t col) {
    std::size_t idx = num_cols_ * row + col;
    return data_[idx];
  }
  T at(std::size_t row, std::size_t col) const {
    if (row > num_rows_ || col > num_cols_) {
      throw std::out_of_range("index is out of range");
    }
    std::size_t idx = num_cols_ * row + col;
    return data_[idx];
  }
  T& at(std::size_t row, std::size_t col) {
    if (row > num_rows_ || col > num_cols_) {
      throw std::out_of_range("index is out of range");
    }
    std::size_t idx = num_cols_ * row + col;
    return data_[idx];
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


#endif // SOLID_MATRIX_H_INCLUDED
