#ifndef MATRIX_H
#define MATRIX_H

class Matrix {
  private:
    float** data;
    int rows;
    int cols;

  public:
    // Constructor that takes the number of rows and columns
    Matrix(int numRows, int numCols);

    // Constructor that takes a 2D array
    Matrix(float** array, int numRows, int numCols);

    // Destructor
    ~Matrix();

    // Get the number of rows in the matrix
    int getRows() const;

    // Get the number of columns in the matrix
    int getCols() const;

    // Get the element at the specified row and column
    float get(int row, int col) const;

    // Set the element at the specified row and column
    void set(int row, int col, float value);

    // Multiply this matrix by another matrix
    Matrix multiply(const Matrix& other) const;

    // Horizontally stack two matrices
    Matrix hstack(const Matrix& other) const;

    // Vertically stack two matrices
    Matrix vstack(const Matrix& other) const;
};

#endif
