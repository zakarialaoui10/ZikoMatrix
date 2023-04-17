#ifndef MATRIX_H
#define MATRIX_H
template <int rows, int cols>
class Matrix {
private:
  int data[rows][cols];
public:
  Matrix(int (*arr)[cols]) {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        data[i][j] = arr[i][j];
      }
    }
  }
  int* operator[](int i) {
    return data[i];
  }
  int& operator()(int row, int col) {
    return data[row][col];
  }

  const int& operator()(int row, int col) const {
    return data[row][col];
  }

  Matrix<rows, cols>& operator+=(const Matrix<rows, cols>& other) {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        data[i][j] += other.data[i][j];
      }
    }
    return *this;
  }

  Matrix<rows, cols>& operator-=(const Matrix<rows, cols>& other) {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        data[i][j] -= other.data[i][j];
      }
    }
    return *this;
  }
};
#endif // MATRIX_H
