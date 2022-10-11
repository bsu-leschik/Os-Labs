#include "Matrix.h"


template <typename T>
Matrix<T>::Matrix(std::vector<std::vector<T>> matrix) {
    _matrix = matrix;
}

template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix<T> &m2) {
    Matrix result = Matrix<T>();

    for (int i = 0; i < this->getSize(); i++){
        std::vector<T> line;
        for (int j = 0; j < this->getSize(); ++j) {
            T element;
            Matrix<T>::multiplyLineAndRow(this->_matrix[i], m2.getRow(j), element);
            line.push_back(element);
        }
        result.addLine(line);
    }
    for (auto & thread : threads) {
        thread.join();
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
void Matrix<T>::multiplyLineAndRow(const std::vector<T>& line,const std::vector<T>& row, T& out) {
    int element = 0;
    for (int j = 0; j < line.size(); ++j) {
        //std::thread t(Matrix<T>::multiplyElements, std::cref(line[j]), std::cref(row[j]), std::ref(element));
        std::thread t([&](){this->multiplyElements(line[j], row[j], out);});
        //multiplyElements(line[j], row[j], element);
        threads.push_back(t);
    }
    out = element;
}

template <typename T>
std::ostream &operator<<(std::ostream &out, const Matrix<T>& m) {
    for (int i = 0; i < m.getSize(); ++i) {
        for (int j = 0; j < m.getRows(); ++j) {
            out << m.getElement(i, j) << " ";
        }
        std::cout << std::endl;
    }
    return out;
}

template <typename T>
std::vector<T> Matrix<T>::getRow(int i) const {
    std::vector<T> result;
    for (auto & line : _matrix) {
        result.push_back(line[i]);
    }
    return result;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix<T> &m2) {
    Matrix<T> result = Matrix<T>();
    for (int i = 0; i < this->getSize(); ++i) {
        std::vector<T> line;
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
        std::vector<T> line;
        for (int j = 0; j < size; ++j) {
            line.push_back(0);
        }
        this->_matrix.push_back(line);
    }
}

template<typename T>
T& Matrix<T>::getElement(int line, int row) const{
    T* SSN = new T(this->_matrix[line][row]);
    return *SSN;
}

template<typename T>
Matrix<Matrix<T>> Matrix<T>::divideMatrix(int blockSize) {
    if (this->getSize() < blockSize){
        throw std::logic_error("Block size cannot be more than matrix size");
    }

    Matrix<Matrix<T>> result = Matrix<Matrix<T>>();
    for (int i = 0; i < this->getSize(); i += blockSize) {
        std::vector<Matrix<T>> line;
        for (int j = 0; j < this->getSize(); j += blockSize) {
            line.push_back(getBlock(i, j, blockSize));
        }
        result.addLine(line);
    }
    return result;
}

template<typename T>
Matrix<T> Matrix<T>::getBlock(int leftUpLine, int leftUpRow, int size) {
    Matrix<T> result = Matrix<T>();

    for (int i = leftUpLine; i < leftUpLine + size && i < getSize(); i++) {
        std::vector<T> line;
        for (int j = leftUpRow; j < leftUpRow + size && j < getSize(); j++) {
            line.push_back(_matrix[i][j]);
        }
        result.addLine(line);
    }



    return result;
}

template<typename T>
int Matrix<T>::getRows() const {
    return _matrix[0].size();
}

template<typename T>
void Matrix<T>::multiplyElements(const T& a, const T& b, T& out) {
    _lock.lock();
    out += a * b;
    _lock.unlock();
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T> &matrix) {
    this->_matrix = matrix._matrix;
}
