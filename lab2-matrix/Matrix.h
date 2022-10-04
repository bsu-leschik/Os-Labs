#ifndef LIBRARIES_MATRIX_H
#define LIBRARIES_MATRIX_H

#include <iostream>
#include <vector>

template<typename T>
class Matrix {
private:
    std::vector<std::vector<T>> _matrix;

    static int multiplyLineAndRow(const std::vector<T>& line,const std::vector<T>& row);
public:
    Matrix() = default;

    explicit Matrix(std::vector<std::vector<T>> matrix);

    explicit Matrix(int size);

    [[nodiscard]] int getSize() const;

    [[nodiscard]] std::vector<T> getRow(int i) const;

    void addLine(const std::vector<T>& row);

    T getElement(int line, int row) const;

    Matrix<T> operator*(const Matrix<T>& m2);

    Matrix<T> operator+(const Matrix<T>& m2);
};

template<typename T>
std::ostream& operator<<(std::ostream& out, const Matrix<T>& m);

#include "Matrix.tpp"
#endif //LIBRARIES_MATRIX_H
