#include "MatrixMultiplier.h"

MatrixMultiplier::MatrixMultiplier(const std::vector<std::vector<int>>& a,const std::vector<std::vector<int>>& b) {
    if (a.size() < 5 || b.size() < 5){
        throw std::logic_error("matrix is too small");
    }
    this->_a = a;
    this->_b = b;
    this->_temp = std::vector<std::vector<int>>(a.size(), std::vector<int>(a.size()));
}

std::vector<std::vector<int>> MatrixMultiplier::multiplyMatrices(int blockSize, bool async) {

    _temp = std::vector<std::vector<int>>(_a.size(), std::vector<int>(_a.size()));
    std::vector<std::thread> threads;
    for (int line = 0; line < _a.size(); line += blockSize) {
        for (int row = 0; row < _a.size(); row += blockSize) {
            if (async) {
                threads.emplace_back([&]() { this->multiplyBlocks(line, row, blockSize); });
            }
            else {
                this->multiplyBlocks(line, row, blockSize);
            }
        }
    }
    if (async) {
        for (auto &thread: threads) {
            thread.join();
        }
    }
    return _temp;
}


void MatrixMultiplier::multiplyBlocks(int line, int row, int blockSize) {
    for (int i = line; i < std::min(line + blockSize, (int)_a.size(), [](int a, int b) {return a < b;}); ++i) {
        for (int j = row; j < std::min(row + blockSize, (int)_a.size(), [](int a, int b) {return a < b;}); ++j) {
            for (int k = 0; k < _a.size(); ++k) {
                _lock.lock();
                _temp[i][j] += _a[i][k] * _b[k][j];
                _lock.unlock();
            }
        }
    }
}

int MatrixMultiplier::getSize() {
    return _a.size();
}
