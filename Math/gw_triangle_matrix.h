#pragma once
#ifndef GW_TRIANGLE_MATRIX_H_INCLUDED
#define GW_TRIANGLE_MATRIX_H_INCLUDED

#include <vector>

/**
    \brief Work with symetric (triangle) matrix. It can save 50% of memory
*/
class TriangleMatrix { // only square can be
public:
  // ctror and dtor
  TriangleMatrix() = default;
  explicit TriangleMatrix(int new_size) {reset(new_size);}
  //
  void reset(int new_size);
  // getters
  double operator()(size_t row, size_t col) const;
  double& operator()(size_t row, size_t col);
  double at(size_t row, size_t col) const;
  double& at(size_t row, size_t col);
  std::size_t size() const {return size_;}
  std::size_t getRowCount() const {return size_;}
  std::size_t getColCount() const {return size_;}
private:
  int size_{0};
  std::vector<double> data_;
  // methods
  int calc_idx(int r, int c) const;
};

#endif // GW_TRIANGLE_MATRIX_H_INCLUDED
