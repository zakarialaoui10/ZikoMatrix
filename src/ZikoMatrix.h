/*
  Author : Zakaria Elalaoui
  Github Repo : https://github.com/zakarialaoui10/ZikoMatrix/
*/
#ifndef MATRIX_H
#define MATRIX_H
#if defined(ARDUINO)
#include <Arduino.h>
#else
#include <iostream>
#endif
#include"utils.h"
template <int rows, int cols=rows, typename T=int>
class Matrix {
public:
    int _rows = rows;
    int _cols = cols;
    T** data;
    
public:
    Matrix() {
        data = new T*[rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new T[cols];
            for (int j = 0; j < cols; j++) {
                data[i][j] = 0;
            }
        }
    }
    
    Matrix(T (*arr)[cols]) {
        data = new T*[rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new T[cols];
            for (int j = 0; j < cols; j++) {
                data[i][j] = arr[i][j];
            }
        }
    }
    
    Matrix(const T (&arr)[rows * cols]) {
        data = new T*[rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new T[cols];
            for (int j = 0; j < cols; j++) {
                data[i][j] = arr[i * cols + j];
            }
        }
    }
     Matrix(const Matrix& other) {
        data = new T*[rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new T[cols];
            for (int j = 0; j < cols; j++) {
                data[i][j] = other.data[i][j];
            }
        }
    }
    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            for (int i = 0; i < rows; i++) {
                delete[] data[i];
            }
            delete[] data;
            
            data = new T*[rows];
            for (int i = 0; i < rows; i++) {
                data[i] = new T[cols];
                for (int j = 0; j < cols; j++) {
                    data[i][j] = other.data[i][j];
                }
            }
        }
        return *this;
    }
    
    ~Matrix() {
        for (int i = 0; i < rows; i++) {
            delete[] data[i];
        }
        delete[] data;
    }
  Matrix<rows, cols , T> clone() const {
    Matrix< rows, cols , T > result = *this;
    return result;
  }
  T* operator[](int i) {
    return data[i];
  }

  T& operator()(int i, int j) {
    return data[i][j];
  }
  const T& operator()(int i, int j) const {
    return data[i][j];
  }
  T& at(int i,int j){
      if(i<0)i=_rows+i;
      if(j<0)j=_cols+j;
      return data[i][j];
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
   static Matrix<rows, cols,T> Zeros() {
    T arr[rows][cols] = {};
    return Matrix<rows, cols , T>(arr);
  }
  static Matrix<rows, cols , T> Ones() {
    int arr[rows][cols] = {};
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        arr[i][j] = 1;
      }
    }
    return Matrix<rows, cols , T>(arr);
  }
  static Matrix<rows, cols , T> Nums(T num) {
    T arr[rows][cols] = {};
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        arr[i][j] = num;
      }
    }
    return Matrix<rows, cols , T>(arr);
  }
  static Matrix<rows, cols , int> Rands(T min=0,T max=10) {
    T arr[rows][cols] = {};
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        #if defined(ARDUINO)
        arr[i][j] = random(min,max);
        #endif
      }
    }
    return Matrix<rows, cols , T>(arr);
  }
   static Matrix<rows, cols , int> Rands(int max=10) {
    T arr[rows][cols] = {};
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        #if defined(ARDUINO)
        arr[i][j] = random(max);
        #endif
      }
    }
    return Matrix<rows, cols , T>(arr);
  }
void deleteRow(int index) {
    for (int i = index+1; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            data[i-1][j] = data[i][j];
        }
    }
    _rows--;
}
void deleteCol(int index){
    for (int i = 0; i < rows; i++) {
        for (int j = index+1; j < cols; j++) {
            data[i][j-1] = data[i][j];
        }
    }
    _cols--;
}
void comatrice() {
    Matrix<rows, cols, T> temp = *this; // make a copy of the original matrix
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            Matrix<rows-1, cols-1, T> submatrix;
            int x = 0, y = 0;
            for (int r = 0; r < rows; r++) {
                if (r == i) continue;
                for (int c = 0; c < cols; c++) {
                    if (c == j) continue;
                    submatrix[x][y] = temp[r][c];
                    y++;
                }
                x++;
                y = 0;
            }
            int sign = ((i+j) % 2 == 0) ? 1 : -1;
            (*this)[i][j] = sign * submatrix.det();
        }
    }
}
void inv(){
    if(!isSquare()){}
    if(det()==0){}
    double determinant=det();
    comatrice();
    transpose();
    (*this)*=1/determinant;
    
}
double det(){
    if(_rows==1)return data[0][0];
    if(_rows==2)return data[0][0]*data[1][1]-data[0][1]*data[1][0];
    double determinant=0;
    double subdet=0;
    int sign=1;
    for(int i=0;i<rows;i++){
        Matrix<rows,cols,T>submatrix=this->clone();
        submatrix.deleteCol(i);
        submatrix.deleteRow(0);
        subdet=submatrix.det();
        determinant+=sign*(*this)[0][i]*subdet;
        sign*=-1;
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
    template <typename Func>
    void foreach(Func func) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++)data[i][j] = func(data[i][j]);
        }
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
  Matrix< rows, cols ,T > operator+(T x) const {
    Matrix< rows, cols , T > result = this->clone();
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        result[i][j] += x;
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
  Matrix< rows, cols ,T > operator-(T x) const {
    Matrix< rows, cols , T > result = this->clone();
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        result[i][j] -= x;
      }
    }
    return result;
  }
  template<int cols2>
  Matrix< rows, cols ,T > operator*(const Matrix<rows, cols2 , T >& other) const {
    Matrix< rows, cols , T > result = this->clone();
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols2; j++) {
            result(i, j) = 0;
            for (int k = 0; k < cols; k++) {
                result(i, j) += data[i][k] * other(k, j);
            }
        }
    }
    return result;
  }
  Matrix< rows, cols ,T > operator*(T x) const {
    Matrix< rows, cols , T > result = this->clone();
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        result[i][j] *= x;
      }
    }
    return result;
  }
  Matrix< rows, cols ,T > operator/(T x) const {
    Matrix< rows, cols , T > result = this->clone();
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        result[i][j] /= x;
      }
    }
    return result;
  }
  Matrix< rows, cols ,T > operator%(int x) const {
    Matrix< rows, cols , T > result = this->clone();
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        result[i][j] %= x;
      }
    }
    return result;
  }
  Matrix< rows, cols , T >& operator+=(const Matrix< rows, cols , T >& other) {
    *this = *this + other;
    return *this;
  }
  Matrix< rows, cols , T >& operator+=(T x) {
    *this = *this + x;
    return *this;
  }
  Matrix< rows, cols , T >& operator-=(const Matrix< rows, cols , T >& other) {
    *this = *this - other;
    return *this;
  }
  Matrix< rows, cols , T >& operator-=(T x) {
    *this = *this - x;
    return *this;
  }
  Matrix< rows, cols , T >& operator*=(T x) {
    *this = *this * x;
    return *this;
  }
  Matrix< rows, cols , T >& operator/=(T x) {
    *this = *this / x;
    return *this;
  }
  Matrix< rows, cols , int >& operator%=(int x) {
    *this = *this % x;
    return *this;
  }
  template<int cols2>
  void hstack(const Matrix<rows, cols2, T>& other) {
        T** new_data = new T*[rows];
        for (int i = 0; i < rows; i++) {
            new_data[i] = new T[cols + other._cols];
            for (int j = 0; j < cols; j++) {
                new_data[i][j] = data[i][j];
            }
            for (int j = 0; j < other._cols; j++) {
                new_data[i][cols + j] = other.data[i][j];
            }
        }
        
        for (int i = 0; i < rows; i++) {
            delete[] data[i];
        }
        delete[] data;
        
        data = new_data;
        _cols += other._cols;
    }
  /*
  template<int new_cols>
    void hstack(const Matrix<rows, new_cols, T>& other) {
       Matrix<rows, cols+new_cols, T> result;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++)result.data[i][j] = data[i][j];
            for (int j = 0; j < new_cols; j++)result.data[i][j+cols] = other.data[i][j];
        }
        _cols += new_cols;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols+new_cols; j++)
                data[i][j] = result.data[i][j];
        }
        
    }*/
/*  template <typename Matrix, typename... Matrices>
void hstack(const Matrix& matrix, const Matrices&... matrices) {
    hstack(matrix);
    hstack(matrices...);
}
*/
 template<int new_rows>
void vstack(Matrix<new_rows, cols, T>& other) {
    transpose();
    other.transpose();
    hstack(other);
    transpose();
    _rows += new_rows;
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
  bool isAntiSym(){
      if(!isSquare())return false;
      for(int i=0;i<_rows;i++){
          for(int j=0;j<_cols;j++){
              if(data[i][j]!=-data[j][i])return false;
          }
      }
      return true;
  }
  bool isDiag(){
      if(!isSquare()||!isSym())return false;
      for(int i=0;i<_rows;i++){
          for(int j=0;j<_cols;j++){
              if(i!=j&&data[i][j]!=0)return false;
          }
      }
      return true;
  }
  bool isId(){
      if(!isDiag())return false;
      for(int i=0;i<_rows;i++){
          for(int j=0;j<_cols;j++){
              if(i==j&&data[i][j]!=1)return false;
          }
      }
      return true;
  }
  bool isZeros(){
      for(int i=0;i<_rows;i++){
          for(int j=0;j<_cols;j++){
              if(data[i][j]!=0)return false;
          }
      }
      return true;
  }
  bool isOnes(){
      for(int i=0;i<_rows;i++){
          for(int j=0;j<_cols;j++){
              if(data[i][j]!=1)return false;
          }
      }
      return true;
  }
  bool isOrtho(){
      if(!isDiag())return false;
      return false; // To Do 
  }
  bool isInv(){
      return det()!=0;
  }
  void clamp(T min,T max){
    for(int i=0;i<_rows;i++){
        for(int j=0;j<_cols;j++)
        data[i][j]=_clamp(data[i][j],min,max);
    }
  }
  void lerp(T min,T max){
    for(int i=0;i<_rows;i++){
        for(int j=0;j<_cols;j++)
        data[i][j]=_lerp(data[i][j],min,max);
    }
  }
  void norm(T min,T max){
    for(int i=0;i<_rows;i++){
        for(int j=0;j<_cols;j++)
        data[i][j]=_norm(data[i][j],min,max);
    }
  }
  void map(T a1,T b1,T a2,T b2){
    for(int i=0;i<_rows;i++){
        for(int j=0;j<_cols;j++)
        data[i][j]=_map(data[i][j],a1,b1,a2,b2);
    }
  }
  int count(T n){
      int c=0;
      for(int i=0;i<_rows;i++){
        for(int j=0;j<_cols;j++)
        if(data[i][j]==n)c++;
    }
    return c;
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
      std::cout<<"\n";
      #endif
  }
};

#endif // MATRIX_H
