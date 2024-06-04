#ifndef MATRIX_H
#define MATRIX_H

#include <array>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

class Matrix {
public:
    /*constructors , destructor*/
    Matrix(std::vector<std::vector<double>>);
    Matrix(const Matrix&);
    Matrix(size_t, size_t, bool = 0);
    // Matrix(std::unique_ptr<std::unique_ptr<double[]>[]> data, size_t m, size_t n);
    Matrix();
    Matrix(Matrix&& matrix);
    ~Matrix();

    /*Matrix Functions*/
    std::array<size_t, 2> getSize();
    double det();
    Matrix T();
    Matrix inv();
    void show() const;

    Matrix delCol(size_t);
    Matrix col_mat(size_t);
    void save(const char*);
    Matrix load(const char*);

    /*Operator over loading*/
    Matrix operator+(const Matrix&) const;
    Matrix operator-(const Matrix&) const;
    Matrix operator*(const Matrix&) const;
    Matrix& operator=(const Matrix& m);
    Matrix& operator=(Matrix&& m);
    Matrix& operator+=(const Matrix& m);
    Matrix& operator*=(const Matrix& m);
    Matrix& operator*=(double num);
    Matrix& operator/=(double num);
    Matrix& operator-=(const Matrix& m);

    double* operator[](size_t);
    const double* operator[](size_t) const;
    // Matrix operator()(const Matrix&);

private:
    size_t row;
    size_t col;
    double** mat;
    void allocspace();
    Matrix getMinor(size_t, size_t);
    Matrix getMinor_inv(size_t, size_t);
    double det_inv();
};

#endif