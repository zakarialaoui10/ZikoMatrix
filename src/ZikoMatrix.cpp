#include "ZikoMatrix.h"

// Constructor that takes the number of rows and columns
Matrix::Matrix(int numRows, int numCols) {
  rows = numRows;
  cols = numCols;
  data = new float*[rows];
  for (int i = 0; i < rows; i++) {
    data[i] = new float[cols];
    for (int j = 0; j < cols; j++) {
      data[i][j] = 0;
    }
  }
}

// Constructor that takes a 2D array
Matrix::Matrix(float** array, int numRows, int numCols) {
  rows = numRows;
  cols = numCols;
  data = new float*[rows];
  for (int i = 0; i < rows; i++) {
    data[i] = new float[cols];
    for (int j = 0; j < cols; j++) {
      data[i][j] = array[i][j];
    }
  }
}

// Destructor
Matrix::~Matrix() {
  for (int i = 0; i < rows; i++) {
    delete[] data[i];
  }
  delete[] data;
}

// Get the number of rows in the matrix
int Matrix::getRows() const {
  return rows;
}

// Get the number of columns in the matrix
int Matrix::getCols() const {
  return cols;
}

// Get the element at the specified row and column
float Matrix::get(int row, int col) const {
  return data[row][col];
}

// Set the element at the specified row and column
void Matrix::set(int row, int col, float value) {
  data[row][col] = value;
}

// Multiply this matrix by another matrix
Matrix Matrix::multiply(const Matrix& other) const {
  if (cols != other.rows) {
    // Error: matrices cannot be multiplied
    return Matrix(0, 0);
  }
  Matrix result(rows, other.cols);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < other.cols; j++) {
      float sum = 0;
      for (int k = 0; k < cols; k++) {
        sum += data[i][k] * other.data[k][j];
      }
      result.data[i][j] = sum;
    }
 
