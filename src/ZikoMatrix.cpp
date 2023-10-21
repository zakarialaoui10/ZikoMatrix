#include "ZikoMatrix.h"

template <int rows, int cols, typename T>
Matrix<rows, cols, T>::Matrix() {
    data = new T*[rows];
    for (int i = 0; i < rows; i++) {
        data[i] = new T[cols];
        for (int j = 0; j < cols; j++) {
            data[i][j] = 0;
        }
    }
}

template <int rows, int cols, typename T>
Matrix<rows, cols, T>::Matrix(T (*arr)[cols]) {
    data = new T*[rows];
    for (int i = 0; i < rows; i++) {
        data[i] = new T[cols];
        for (int j = 0; j < cols; j++) {
            data[i][j] = arr[i][j];
        }
    }
}

template <int rows, int cols, typename T>
Matrix<rows, cols, T>::Matrix(const T (&arr)[rows * cols]) {
    data = new T*[rows];
    for (int i = 0; i < rows; i++) {
        data[i] = new T[cols];
        for (int j = 0; j < cols; j++) {
            data[i][j] = arr[i * cols + j];
        }
    }
}

template <int rows, int cols, typename T>
Matrix<rows, cols, T>::Matrix(const Matrix& other) {
    data = new T*[rows];
    for (int i = 0; i < rows; i++) {
        data[i] = new T[cols];
        for (int j = 0; j < cols; j++) {
            data[i][j] = other.data[i][j];
        }
    }
}

template <int rows, int cols, typename T>
Matrix<rows, cols, T>& Matrix<rows, cols, T>::operator=(const Matrix& other) {
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

template <int rows, int cols, typename T>
Matrix<rows, cols, T>::~Matrix() {
    for (int i = 0; i < rows; i++) {
        delete[] data[i];
    }
    delete[] data;
}

template <int rows, int cols, typename T>
Matrix<rows, cols, T> Matrix<rows, cols, T>::clone() const {
    Matrix<rows, cols, T> result = *this;
    return result;
}
