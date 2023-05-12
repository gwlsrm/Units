#pragma once
#ifndef GWSOLIDMATRIX_H_INCLUDED
#define GWSOLIDMATRIX_H_INCLUDED

#include <vector>
#include <stdexcept>
#include <iostream>

class MatrixSolid {
public:
  MatrixSolid() = default;
  MatrixSolid(int row_count, int col_count) {reset(row_count, col_count);}
  void reset(int row_count, int col_count);
  // getters
  int at(int row_idx, int col_idx) const { return data_.at(row_idx * col_count_ + col_idx);}
  int& at(int row_idx, int col_idx) { return data_.at(row_idx * col_count_ + col_idx);}
  int getNumRows() const { return row_count_;}
  int getNumColumns() const { return col_count_;}
private:
  std::vector<int> data_;
  int row_count_ = 0, col_count_ = 0;
};

// operators
std::istream& operator>>(std::istream& in, MatrixSolid& m);
std::ostream& operator<<(std::ostream& out, const MatrixSolid& m);
bool operator==(const MatrixSolid& lhs, const MatrixSolid& rhs);
MatrixSolid operator+(const MatrixSolid& lhs, const MatrixSolid& rhs);

#endif // GWSOLIDMATRIX_H_INCLUDED
