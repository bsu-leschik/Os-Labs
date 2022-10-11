#ifndef LIBRARIES_MATRIX_H
#define LIBRARIES_MATRIX_H

#include <iostream>
#include <vector>
#include <thread>
#include <exception>
#include <mutex>

template<typename T>
class Matrix {
private:
    std::vector<std::vector<T>> _matrix;
    static std::mutex _lock;
    static std::vector<std::thread> threads;

    void multiplyLineAndRow(const std::vector<T>& line,const std::vector<T>& row, T& out);

    Matrix<T> getBlock(int leftUpLine, int leftUpRow, int size);

public:

    void multiplyElements(const T& a, const T& b, T& out);

    Matrix() = default;

    explicit Matrix(std::vector<std::vector<T>> matrix);

    explicit Matrix(int size);

    Matrix(Matrix&& matrix) noexcept = default;

    Matrix(const Matrix<T> &matrix);

    Matrix<Matrix> divideMatrix(int blockSize);

    [[nodiscard]] int getSize() const;

    [[nodiscard]] int getRows() const;

    [[nodiscard]] std::vector<T> getRow(int i) const;

    void addLine(const std::vector<T>& row);

    T& getElement(int line, int row) const;

    Matrix<T> operator*(const Matrix<T>& m2);

    Matrix<T> operator+(const Matrix<T>& m2);
};

template<typename T>
std::ostream& operator<<(std::ostream& out, const Matrix<T>& m);

#include "Matrix.tpp"
#endif //LIBRARIES_MATRIX_H
