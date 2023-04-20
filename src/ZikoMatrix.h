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
void reshape(int new_rows, int new_cols) {
        if (new_rows * new_cols != _rows * _cols){
          #if defined(ARDUINO)
          Serial.println("Invalid size");
          return;
          #else
          throw std::out_of_range("Invalid size");
          #endif  
        }
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
        _rows = new_rows;
        _cols = new_cols;
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
void slice(int r0,int c0, int r1, int c1) {
        int new_rows = r1 - r0;
        int new_cols = c1 - c0;
        // Check if the slice range is within bounds
        if (r0 < 0 || r0 >= _rows ||
            r1 < r0 || r1 > _rows ||
            c0 < 0 || c0 >= _cols ||
            c1 < c0 || c1 > _cols) {
            // Handle out of bounds error
            #if defined(ARDUINO)
            Serial.println("Invalid slice range");
            return;
            #else
            throw std::out_of_range("Invalid slice range");
            #endif
        }
        T temp[new_rows][new_cols];
        //Copy
        for (int i = r0; i < r1; i++) {
            for (int j = c0; j < c1; j++)temp[i - r0][j - c0] = data[i][j];
        }
        //Overwrite
        for (int i = 0; i < new_rows; i++) {
            for (int j = 0; j < new_cols; j++)data[i][j] = temp[i][j];
        }
        _rows = new_rows;
        _cols = new_cols;
    }
  Matrix< rows, cols ,T > operator+(const Matrix<rows, cols , T >& other) const {
    Matrix< rows, cols , T > result = this->clone();
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        result.data[i][j] += other.data[i][j];
      }
    }
    return result;
  }
template<int new_cols>
    void hstack(const Matrix<rows, new_cols, T>& other) {
        Matrix<rows, cols+new_cols, T> result;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++)result.data[i][j] = data[i][j];
            for (int j = 0; j < new_cols; j++)result.data[i][j+cols] = other.data[i][j];
        }
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols+new_cols; j++)
                data[i][j] = result.data[i][j];
        }
        _cols += new_cols;
    }
 template<int new_rows>
    void vstack(const Matrix<new_rows, cols, T>& other) {
        Matrix<rows+new_rows, cols, T> result;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++)result[i][j] = data[i][j];
        }
        for (int i = 0; i < new_rows; i++) {
            for (int j = 0; j < cols; j++)result[i+rows][j] = other[i][j];
        }
        for (int i = 0; i < rows+new_rows; i++) {
            for (int j = 0; j < cols; j++)data[i][j] = result[i][j];
        }
        _rows += new_rows;
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
  bool isId(){
      if(!isSquare()||!isSym())return false;
      for(int i=0;i<_rows;i++){
          for(int j=0;j<_cols;j++){
              if(i==j&&data[i][j]!=1)return false;
              if(i!=j&&data[i][j]!=0)return false;
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
