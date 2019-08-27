#ifndef GWMATRIX_H_INCLUDED
#define GWMATRIX_H_INCLUDED

#include <vector>
#include <iostream>
#include <initializer_list>

class DoubleMatrix
{
public:
    using matrix_iterator = std::vector<std::vector<double>>::iterator;
    using matrix_const_iterator = std::vector<std::vector<double>>::const_iterator;
    // ctors
    DoubleMatrix() = default;
    DoubleMatrix(int num_rows, int num_columns); // constructor for matrix
    explicit DoubleMatrix(int sze) : DoubleMatrix(sze, sze) {};
    DoubleMatrix(const std::initializer_list<std::initializer_list<double>>& lst);
    void reset(int num_rows, int num_columns);
    // access operators
    double operator()(size_t row, size_t col) const {return mElements[row][col];}
    double& operator()(size_t row, size_t col) {return mElements[row][col];}
    double at(size_t row, size_t col) const;
    double& at(size_t row, size_t col);
    const std::vector<double>& operator[](size_t row) const {return mElements[row];}
    std::vector<double>& operator[](size_t row) {return mElements[row];}
    matrix_iterator begin() {return mElements.begin();}
    matrix_iterator end() {return mElements.end();}
    matrix_const_iterator begin() const {return mElements.begin();}
    matrix_const_iterator end() const {return mElements.end();}
    // getters
    size_t getRowCount() const {return row_count;}
    size_t getColCount() const {return col_count;}
    // methods
    bool isSquare() const {return row_count == col_count;}
    double determinant() const;
private:
    size_t row_count = 0;
    size_t col_count = 0;
    std::vector<std::vector<double>> mElements;
};

// operations with matrix
DoubleMatrix operator+(const DoubleMatrix& one, const DoubleMatrix& two);
bool operator==(const DoubleMatrix& lhs, const DoubleMatrix& rhs);
std::istream& operator>>(std::istream& in, DoubleMatrix& matrix);
std::ostream& operator<<(std::ostream& out, const DoubleMatrix& matrix);


#endif // GWMATRIX_H_INCLUDED
