#include "Matrix.h"
template<typename T>
Matrix<T>::Matrix(int r, int c) {
    rows = r;
    cols = c;
    data = new T*[rows];
    for(int i = 0; i < rows; i++) {
        data[i] = new T[cols];
        for(int j = 0; j < cols; j++) {
            data[i][j] = T();
        }
    }
}
template<typename T>
Matrix<T>::Matrix(T** arr, int r, int c) {
    rows = r;
    cols = c;
    data = new T*[rows];
    for(int i = 0; i < rows; i++) {
        data[i] = new T[cols];
        for(int j = 0; j < cols; j++) {
            data[i][j] = arr[i][j];
        }
    }
}
template<typename T>
Matrix<T>::~Matrix() {
    for(int i = 0; i < rows; i++) {
        delete[] data[i];
    }
    delete[] data;
}
