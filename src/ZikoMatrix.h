#ifndef MATRIX_H
#define MATRIX_H
template<typename T>
class Matrix {
public:
    int rows;
    int cols;
    T** data;

public:
    Matrix(int r, int c) {
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

    // Getter for accessing individual elements
    T& operator()(int i, int j) {
        return data[i][j];
    }
    // Setter for modifying individual elements
    void set(int i, int j, T value) {
        data[i][j] = value;
    }
    // rest of the Matrix class implementation...
};

#endif
