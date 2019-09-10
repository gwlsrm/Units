#include "gw_triangle_matrix.h"

#include <stdexcept>

using namespace std;

void TriangleMatrix::reset(int new_size)
{
  int capacity = new_size * (new_size - 1) / 2;
  data_.resize(capacity);
}

int TriangleMatrix::calc_idx(int r, int c) const
{
  // sum of all rows before (upper) r and + column index
  if (r < c) {swap(r, c);}
  return (r - 1) * r / 2 + c;
}


double& TriangleMatrix::operator()(size_t row, size_t col)
{
  int i = calc_idx(row, col);
  return data_[i];
}

double TriangleMatrix::operator()(size_t row, size_t col) const
{
  int i = calc_idx(row, col);
  return data_[i];
}

double& TriangleMatrix::at(size_t row, size_t col)
{
  int i = calc_idx(row, col);
  if (i < size_) {
    return data_[i];
  } else {
    throw out_of_range(string("indexes ") + to_string(row) + ", " + to_string(col)
                      + " are out of range");
  }
}

double TriangleMatrix::at(size_t row, size_t col) const
{
  int i = calc_idx(row, col);
  if (i < size_) {
    return data_[i];
  } else {
    throw out_of_range(string("indexes ") + to_string(row) + ", " + to_string(col)
                      + " are out of range");
  }
}
