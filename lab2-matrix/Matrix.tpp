#include "Matrix.h"

template <typename T>
Matrix<T>::Matrix(std::vector<std::vector<T>> matrix) {
    _matrix = std::move(matrix);
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &m2) {
    Matrix result = Matrix<T>();

    for (int i = 0; i < this->_matrix.size(); i++){
        std::vector<int> line;
        for (int j = 0; j < this->_matrix.size(); ++j) {
            line.push_back(Matrix<T>::multiplyLineAndRow(this->_matrix[i], m2.getRow(j)));
        }
        result.addLine(line);
    }
    return result;
}

template <typename T>
int Matrix<T>::getSize() const{
    return _matrix.size();
}

template <typename T>
void Matrix<T>::addLine(const std::vector<T> &row) {
    _matrix.push_back(row);
}

template <typename T>
int Matrix<T>::multiplyLineAndRow(const std::vector<T>& line,const std::vector<T>& row) {
    int element = 0;
    for (int j = 0; j < line.size(); ++j) {
        element += line[j] * row[j];
    }
    return element;
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const Matrix<T>& m) {
    for (int i = 0; i < m.getSize(); ++i) {
        for (int j = 0; j < m.getSize(); ++j) {
            out << m.getElement(i, j) << " ";
        }
        std::cout << std::endl;
    }
    return out;
}

template <typename T>
std::vector<T> Matrix<T>::getRow(int i) const {
    std::vector<int> result;
    for (auto & line : _matrix) {
        result.push_back(line[i]);
    }
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &m2) {
    Matrix result = Matrix<T>();
    for (int i = 0; i < this->getSize(); ++i) {
        std::vector<int> line;
        for (int j = 0; j < this->getSize(); ++j) {
            line.push_back(this->getElement(i,j) + m2.getElement(i, j));
        }
        result.addLine(line);
    }
    return result;
}

template <typename T>
Matrix<T>::Matrix(int size) {
    for (int i = 0; i < size; ++i) {
        std::vector<int> line;
        for (int j = 0; j < size; ++j) {
            line.push_back(0);
        }
        this->_matrix.push_back(line);
    }
}

template<typename T>
T Matrix<T>::getElement(int line, int row) const{
    return this->_matrix[line][row];
}

