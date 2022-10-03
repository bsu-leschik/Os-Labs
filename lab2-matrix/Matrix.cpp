#include "Matrix.h"

Matrix::Matrix(std::vector<std::vector<int>> matrix) {
    _matrix = std::move(matrix);
}



Matrix operator*(const Matrix &m1, const Matrix &m2) {
    Matrix result = Matrix();

    for (int i = 0; i < m1._matrix.size(); i++){
        std::vector<int> line;
        for (int j = 0; j < m1._matrix.size(); ++j) {
            line.push_back(Matrix::multiplyLineAndRow(m1._matrix[i], m2.getRow(j)));
        }
        result.addLine(line);
    }
    return result;
}

int Matrix::getRows() {
    return _matrix.size();
}

void Matrix::addLine(const std::vector<int> &row) {
    _matrix.push_back(row);
}

int Matrix::multiplyLineAndRow(const std::vector<int>& line,const std::vector<int>& row) {
    int element = 0;
    for (int j = 0; j < line.size(); ++j) {
        element += line[j] * row[j];
    }
    return element;
}

std::ostream &operator<<(std::ostream &out, Matrix &m) {
    for (const auto &item : m._matrix){
        for (const auto &item : item){
            out << item << " ";
        }
        out << std::endl;
    }
    return out;
}

std::vector<int> Matrix::getRow(int i) const {
    std::vector<int> result;
    for (auto & line : _matrix) {
        result.push_back(line[i]);
    }
    return result;
}


