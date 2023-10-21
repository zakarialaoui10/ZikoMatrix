#ifndef ZIKOMATRIX_H
#define ZIKOMATRIX_H

#if defined(ARDUINO)
#include <Arduino.h>
#else
#include <iostream>
#endif

#include "utils.h" // Make sure to include this file if it contains utility functions used in the Matrix class.

template <int rows, int cols = rows, typename T = int>
class Matrix {
public:
    int _rows = rows;
    int _cols = cols;
    T** data;

    Matrix();
    Matrix(T (*arr)[cols]);
    Matrix(const T (&arr)[rows * cols]);
    Matrix(const Matrix& other);
    Matrix& operator=(const Matrix& other);
    ~Matrix();
    Matrix<rows, cols, T> clone() const;
    T* operator[](int i);
    T& operator()(int i, int j);
    const T& operator()(int i, int j) const;
    T& at(int i, int j);
    static Matrix<rows, cols> id();
    static Matrix<rows, cols, T> Zeros();
    static Matrix<rows, cols, T> Ones();
    static Matrix<rows, cols, T> Nums(T num);
    static Matrix<rows, cols, int> Rands(T min = 0, T max = 10);
    static Matrix<rows, cols, int> Rands(int max = 10);
    Matrix<rows, cols, T>& deleteRow(int index);
    Matrix<rows, cols, T>& deleteCol(int index);
    Matrix<rows, cols, T>& comatrice();
    Matrix<rows, cols, T>& inv();
    double det();
    Matrix<rows, cols, T>& reshape(int new_rows, int new_cols);
    void transpose();
    template <int subRows, int subCols>
    Matrix<subRows, subCols, T> slice(int startRow, int startCol) const;
    void slice(int r0, int c0, int r1, int c1);
    template <typename Func>
    Matrix<rows, cols, T>& foreach(Func func);
    Matrix<rows, cols, T> operator+(const Matrix<rows, cols, T>& other) const;
    Matrix<rows, cols, T> operator+(T x) const;
    Matrix<rows, cols, T> operator-(const Matrix<rows, cols, T>& other) const;
    Matrix<rows, cols, T> operator-(T x) const;
    template <int cols2>
    Matrix<rows, cols, T> operator*(const Matrix<rows, cols2, T>& other) const;
    Matrix<rows, cols, T> operator*(T x) const;
    Matrix<rows, cols, T> operator/(T x) const;
    Matrix<rows, cols, T> operator%(int x) const;
    Matrix<rows, cols, T>& operator+=(const Matrix<rows, cols, T>& other);
    Matrix<rows, cols, T>& operator+=(T x);
    Matrix<rows, cols, T>& operator-=(const Matrix<rows, cols, T>& other);
    Matrix<rows, cols, T>& operator-=(T x);
    template <int cols2>
    Matrix<rows, cols, T>& operator*=(const Matrix<rows, cols2, T>& other);
    Matrix<rows, cols, T>& operator*=(T x);
    Matrix<rows, cols, T>& operator^=(int n);
    Matrix<rows, cols, T>& operator/=(T x);
    Matrix<rows, cols, int>& operator%=(int x);
    template <int new_cols>
    Matrix<rows, cols + new_cols, T> hstack(const Matrix<rows, new_cols, T>& other);
    template <int new_cols>
    Matrix<rows, cols + new_cols, T> hqueue(const Matrix<rows, new_cols, T>& other);
    template <int new_rows>
    Matrix<rows + new_rows, cols, T> vstack(const Matrix<new_rows, cols, T>& other);
    template <int new_rows>
    Matrix<rows + new_rows, cols, T> vqueue(const Matrix<new_rows, cols, T>& other);
    bool isSquare();
    bool isSym();
    bool isAntiSym();
    bool isDiag();
    bool isId();
    bool isZeros();
    bool isOnes();
    bool isOrtho();
    bool isInv();
    Matrix<rows, cols, T>& clamp(T min, T max);
    Matrix<rows, cols, T>& lerp(T min, T max);
    Matrix<rows, cols, T>& norm(T min, T max);
    Matrix<rows, cols, T>& map(T a1, T b1, T a2, T b2);
    int count(T n);
    Matrix<rows, cols, T>& print();
};

#endif // ZIKOMATRIX_H
