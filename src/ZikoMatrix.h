#ifndef MATRIX_H
#define MATRIX_H

#if defined(ARDUINO)
#include <Arduino.h>
#else
#include <iostream>
#endif

template <typename T, int rows, int cols>
class Matrix {
private:
  T data[rows][cols];
public:
  Matrix(T (*arr)[cols]) {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        data[i][j] = arr[i][j];
      }
    }
  }
  
  Matrix< T, rows, cols >(const T (&arr)[rows * cols]) {
    for (size_t i = 0; i < rows; i++) {
      for (size_t j = 0; j < cols; j++) {
        data[i][j] = arr[i * cols + j];
      }
    }
  }

  Matrix< T, rows, cols > clone() const {
    Matrix< T, rows, cols > result = *this;
    return result;
  }

  T* operator[](int i) {
    return data[i];
  }

  T& operator()(int row, int col) {
    return data[row][col];
  }

  const T& operator()(int row, int col) const {
    return data[row][col];
  }

  Matrix< T, rows, cols > operator+(const Matrix< T, rows, cols >& other) const {
    Matrix< T, rows, cols > result = this->clone();
    result += other;
    return result;
  }

  Matrix< T, rows, cols > operator-(const Matrix< T, rows, cols >& other) const {
    Matrix< T, rows, cols > result = this->clone();
    result -= other;
    return result;
  }

  Matrix< T, rows, cols >& operator+=(const Matrix< T, rows, cols >& other) {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        data[i][j] += other.data[i][j];
      }
    }
    return *this;
  }

  Matrix< T, rows, cols >& operator-=(const Matrix< T, rows, cols >& other) {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        data[i][j] -= other.data[i][j];
      }
    }
    return *this;
  }
/* Matrix<T,rows, cols>& operator*=(const Matrix<T,rows, cols>& other) {
  Matrix<T,rows, cols> result = Matrix<T,rows, cols>
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      for (int k = 0; k < cols; k++) {
        result(i, j) += data[i][k] * other(k, j);
      }
    }
  }
  *this = result;
  return *this;
}
*/

  void print() const {
#if defined(ARDUINO)
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        Serial.print(data[i][j]);
        Serial.print(' ');
      }
      Serial.println();
    }
#else
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        std::cout << data[i][j] << ' ';
      }
      std::cout << '\n';
    }
#endif
  }
};

#endif // MATRIX_H
