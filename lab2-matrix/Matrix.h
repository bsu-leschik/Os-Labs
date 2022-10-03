#ifndef LIBRARIES_MATRIX_H
#define LIBRARIES_MATRIX_H

#include <iostream>
#include <vector>

class Matrix {
private:
    std::vector<std::vector<int>> _matrix;

    static int multiplyLineAndRow(const std::vector<int>& line,const std::vector<int>& row);
public:
    Matrix() = default;

    explicit Matrix(std::vector<std::vector<int>> matrix);

    int getRows();

    [[nodiscard]] std::vector<int> getRow(int i) const;

    void addLine(const std::vector<int>& row);

    friend Matrix operator*(const Matrix& m1, const Matrix& m2);

    friend std::ostream& operator<<(std::ostream& out, Matrix& m);

};


#endif //LIBRARIES_MATRIX_H
