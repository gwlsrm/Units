// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "gwmatrix.h"

#include <algorithm>
#include <stdexcept>

using namespace std;

DoubleMatrix::DoubleMatrix(int num_rows, int num_columns)
{
    reset(num_rows, num_columns);
}

void DoubleMatrix::reset(int num_rows, int num_columns)
{
    if (num_rows < 0) {
      throw out_of_range("num_rows must be >= 0");
    }
    if (num_columns < 0) {
      throw out_of_range("num_columns must be >= 0");
    }

    row_count = num_rows;
    col_count = num_columns;
    mElements.assign(row_count, vector<double>(col_count));
}

DoubleMatrix::DoubleMatrix(const std::initializer_list<std::initializer_list<double>>& lst)
{
    size_t row_num = lst.size();
    reset(row_num, 0);
    size_t i = 0;
    for (const auto& row : lst) {
        mElements[i++] = row;
    }
    if (row_num > 0) col_count = mElements[0].size();
}


double DoubleMatrix::at(size_t row, size_t col) const
{
    return mElements.at(row).at(col);
}

double& DoubleMatrix::at(size_t row, size_t col)
{
    return mElements.at(row).at(col);
}

double DoubleMatrix::determinant() const
{
    if (!isSquare()) throw -1;
    // TODO: code must be here
    return 0;
}

DoubleMatrix operator+(const DoubleMatrix& one, const DoubleMatrix& two) {
  if (one.getRowCount() != two.getRowCount()) {
    throw invalid_argument("Mismatched number of rows");
  }

  if (one.getColCount() != two.getColCount()) {
    throw invalid_argument("Mismatched number of columns");
  }

  DoubleMatrix result(one.getRowCount(), one.getColCount());
  for (size_t row = 0; row < result.getRowCount(); ++row) {
    for (size_t column = 0; column < result.getColCount(); ++column) {
      result(row, column) = one(row, column) + two(row, column);
    }
  }

  return result;
}

bool operator==(const DoubleMatrix& lhs, const DoubleMatrix& rhs) {
    if (lhs.getRowCount() != rhs.getRowCount() || lhs.getColCount() != rhs.getColCount()) {
        return false;
    }
    for (size_t row = 0; row < lhs.getRowCount(); ++row) {
        for (size_t column = 0; column < lhs.getColCount(); ++column) {
            if (lhs(row, column) != rhs(row, column)) return false;
        }
    }
    return true;
}

std::istream& operator>>(std::istream& in, DoubleMatrix& matrix) {
  int num_rows, num_columns;
  in >> num_rows >> num_columns;

  matrix.reset(num_rows, num_columns);
  for (int row = 0; row < num_rows; ++row) {
    for (int column = 0; column < num_columns; ++column) {
      in >> matrix(row, column);
    }
  }
    return in;
}

std::ostream& operator<<(std::ostream& out, const DoubleMatrix& matrix) {
    //out << matrix.getRowCount() << " " << matrix.getColCount() << endl;

    for (size_t row = 0; row < matrix.getRowCount(); ++row) {
        for (size_t column = 0; column < matrix.getColCount(); ++column) {
            if (column > 0) {
                out << " ";
            }
            out << matrix.at(row, column);
        }
        out << '\n';
    }
    return out;
}
