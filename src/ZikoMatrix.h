#ifndef MATRIX_H
#define MATRIX_H
template<typename T>
class Matrix {
  private:
    int rows;
    int cols;
    T** data;

  public:
    Matrix(int r, int c);
    Matrix(T** arr, int r, int c);
    ~Matrix();
};
#endif
