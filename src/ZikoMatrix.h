#ifndef MATRIX_H
#define MATRIX_H
#if defined(ARDUINO) #include <Arduino.h>
#else #include <iostream>
#endif

template < int rows, int cols >
  class Matrix {
    private: int data[rows][cols];
    public: Matrix(int( * arr)[cols]) {
      for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
          data[i][j] = arr[i][j];
        }
      }
    }
    Matrix < rows,
    cols > (const int( & arr)[rows * cols]) {
      for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < cols; j++) {
          data[i][j] = arr[i * cols + j];
        }
      }
    }
    Matrix < rows,
    cols > clone() const {
      Matrix < rows, cols > result = * this;
      return result;
    }
    int * operator[](int i) {
      return data[i];
    }
    int & operator()(int row, int col) {
      return data[row][col];
    }

    const int & operator()(int row, int col) const {
      return data[row][col];
    }
    Matrix < rows,
    cols > operator + (const Matrix < rows, cols > & other) const {
      Matrix < rows, cols > result = this -> clone();
      result += other;
      return result;
    }
    Matrix < rows,
    cols > & operator += (const Matrix < rows, cols > & other) {
      for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
          data[i][j] += other.data[i][j];
        }
      }
      return * this;
    }

    Matrix < rows,
    cols > & operator -= (const Matrix < rows, cols > & other) {
      for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
          data[i][j] -= other.data[i][j];
        }
      }
      return * this;
    }
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
