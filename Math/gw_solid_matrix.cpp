#include "gw_solid_matrix.h"

using namespace std;

void MatrixSolid::reset(int row_count, int col_count) {
  if (row_count < 0 || col_count < 0) {
    throw std::out_of_range("Exception: negative size");
  }
  row_count_ = row_count;
  col_count_ = col_count;
  data_.assign(row_count * col_count, 0);
}

// operators
std::istream& operator>>(std::istream& in, MatrixSolid& m) {
  int num_rows, num_cols;
  in >> num_rows >> num_cols;
  m.reset(num_rows, num_cols);
  for (int row = 0; row < m.getNumRows(); ++row) {
    for (int col = 0; col < m.getNumColumns(); ++col) {
      in >> m.at(row, col);
    }
  }
  return in;
}

std::ostream& operator<<(std::ostream& out, const MatrixSolid& m) {
  out << m.getNumRows() << " " << m.getNumColumns() << '\n';
  for (int row = 0; row < m.getNumRows(); ++row) {
    if (row > 0) {
      out << '\n';
    }
    for (int col = 0; col < m.getNumColumns(); ++col) {
      if (col > 0) {
        out << ' ';
      }
      out << m.at(row, col);
    }
  }
  return out;
}

bool operator==(const MatrixSolid& lhs, const MatrixSolid& rhs) {
  if (lhs.getNumRows() != rhs.getNumRows() || lhs.getNumColumns() != rhs.getNumColumns()) {
    return false;
  }
  for (int ri = 0; ri < lhs.getNumRows(); ++ri) {
    for (int ci = 0; ci < lhs.getNumColumns(); ++ci) {
      if (lhs.at(ri, ci) != rhs.at(ri, ci)) return false;
    }
  }
  return true;
}

MatrixSolid operator+(const MatrixSolid& lhs, const MatrixSolid& rhs) {
  if (lhs.getNumRows() != rhs.getNumRows() || lhs.getNumColumns() != rhs.getNumColumns()) {
    throw std::invalid_argument("Exception: different matrices sizes");
  }
  MatrixSolid res(lhs.getNumRows(), lhs.getNumColumns());
  for (int ri = 0; ri < lhs.getNumRows(); ++ri) {
    for (int ci = 0; ci < lhs.getNumColumns(); ++ci) {
      res.at(ri, ci) = lhs.at(ri, ci) + rhs.at(ri, ci);
    }
  }
  return res;
}
