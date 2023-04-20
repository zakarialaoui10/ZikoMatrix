#ifndef MATRIX_H
#define MATRIX_H
#if defined(ARDUINO)
#include <Arduino.h>
#else
#include <iostream>
#endif
template <int rows = 0, int cols = rows , typename T=int>
class Matrix {
    public:
    int _rows=rows;
    int _cols=cols;
    T data[rows][cols]={};
    public:
    Matrix() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                data[i][j] = 0;
            }
        }
    }
    Matrix(T (*arr)[cols]) {
        for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
        data[i][j] = arr[i][j];
  }
    Matrix<rows, cols , T>(const T (&arr)[rows * cols]) {
        for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++)
        data[i][j] = arr[i * cols + j];
  }
  ~Matrix<rows,cols,T>() {
   
  }
  Matrix<rows, cols , T> clone() const {
    Matrix< rows, cols , T > result = *this;
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
   static Matrix<rows,cols>id(){
       int arr[rows][rows] = {};
       for (int i = 0; i < rows; i++) {
           for (int j = 0; j < rows; j++) {
               arr[i][j] = (i == j) ? 1 : 0;
           }
       }
       return Matrix<rows, rows , T>(arr);
   }
   static Matrix<rows, cols,T> zeros() {
    T arr[rows][cols] = {};
    return Matrix<rows, cols , T>(arr);
  }
  static Matrix<rows, cols , T> ones() {
    int arr[rows][cols] = {};
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        arr[i][j] = 1;
      }
    }
    return Matrix<rows, cols , T>(arr);
  }
double det(){
    if(rows==1)return data[0][0];
    if(rows==2)return data[0][0]*data[1][1]-data[0][1]*data[1][0];
    double determinant=0;
    for(int j=0;j<cols;j++){
        Matrix<rows-1,cols-1,T>submatrix;
        for(int i=1;i<rows;i++){
            for(int k=0;k<cols;k++){
                if(k<j)submatrix[i-1][k]=data[i][k];
                else if(k>j)submatrix[i-1][k-1]=data[i][k];
            }
        }
        //double subdet=submatrix.det();
        
    }
    return determinant;
}
bool reshape(int new_rows, int new_cols) {
        if (new_rows * new_cols != _rows * _cols)return false;
        // Copy data to temporary array
        T temp[_rows][_cols];
        for (int i = 0; i < _rows; i++) {
            for (int j = 0; j < _cols; j++) {
                temp[i][j] = data[i][j];
            }
        }
        // Fill new matrix with data from temporary array
        int count = 0;
        for (int i = 0; i < new_rows; i++) {
            for (int j = 0; j < new_cols; j++) {
                data[i][j] = temp[count / _cols][count % _cols];
                count++;
            }
        }
        // Update member variables
        _rows = new_rows;
        _cols = new_cols;
        return true;
    }  
  void transpose() {
      _cols=rows;
      _rows=cols;
  T temp[cols][rows];
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      temp[j][i] = data[i][j];
    }
  }
  // Copy the transpose matrix back to the original matrix
  for (int i = 0; i < _rows; i++) {
    for (int j = 0; j < _cols; j++) {
      data[i][j] = temp[i][j];
    }
  }
}
template <int subRows, int subCols>
Matrix<subRows, subCols, T> slice(int startRow, int startCol) const {
    Matrix<subRows, subCols, T> submatrix;
    for (int i = 0; i < subRows; i++) {
        for (int j = 0; j < subCols; j++) {
            submatrix(i, j) = data[i + startRow][j + startCol];
        }
    }
    return submatrix;
}
void slice(int r,int c,int i,int j){}
  Matrix< rows, cols ,T > operator+(const Matrix<rows, cols , T >& other) const {
    Matrix< rows, cols , T > result = this->clone();
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        result.data[i][j] += other.data[i][j];
      }
    }
    return result;
  }
  Matrix< rows, cols ,T > operator-(const Matrix<rows, cols , T >& other) const {
    Matrix< rows, cols , T > result = this->clone();
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        result.data[i][j] -= other.data[i][j];
      }
    }
    return result;
  }
  template <int other_cols>
Matrix<rows, cols + other_cols, T> hstack(const Matrix<rows, other_cols, T>& other) const {
    Matrix<rows, cols + other_cols, T> result;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result(i, j) = (*this)(i, j);
        }
        for (int j = 0; j < other_cols; j++) {
            result(i, cols + j) = other(i, j);
        }
    }
    return result;
}
template <int other_rows>
Matrix<rows + other_rows, cols, T> vstack(const Matrix<other_rows, cols, T>& other) const {
    Matrix<rows + other_rows, cols, T> result;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result(i, j) = (*this)(i, j);
        }
    }
    for (int i = 0; i < other_rows; i++) {
        for (int j = 0; j < cols; j++) {
            result(rows + i, j) = other(i, j);
        }
    }
    return result;
}

  Matrix< rows, cols , T >& operator+=(const Matrix< rows, cols , T >& other) {
    *this = *this + other;
    return *this;
  }
  Matrix< rows, cols , T >& operator-=(const Matrix< rows, cols , T >& other) {
    *this = *this - other;
    return *this;
  }
  bool isSquare(){
      return rows==cols;
  }
  bool isSym(){
      if(!isSquare())return false;
      for(int i=0;i<_rows;i++){
          for(int j=0;j<_cols;j++){
              if(data[i][j]!=data[j][i])return false;
          }
      }
      return true;
  }
  void print() const {
      #if defined(ARDUINO)
      for (int i = 0; i < _rows; i++) {
          for (int j = 0; j < _cols; j++) {
              Serial.print(data[i][j]);
              Serial.print(' ');
          }
          Serial.println();
      }
      #else
      for (int i = 0; i < _rows; i++) {
          for (int j = 0; j < _cols; j++) {
              std::cout << data[i][j] << ' ';
          }
          std::cout << '\n';
      }
      #endif
  }
};

#endif // MATRIX_H
