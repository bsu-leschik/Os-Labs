#include <iostream>
#include "MatrixMultiplier.h"

std::mutex lock;
BufferedChannel<std::pair<int, int>> *cords;
std::vector<std::vector<int>> *out;
std::vector<std::thread> threads;

void multiplyBlocksAsync(const std::vector<std::vector<int>> &_a, const std::vector<std::vector<int>> &_b, int blockSize) {
    auto pair = cords->Recv();
    if (!pair.second) {
        return;
    }
    int line = pair.first.first;
    int row = pair.first.second;

    for (int i = line; i < std::min(line + blockSize, (int) _a.size(), [](int a, int b) { return a < b; }); ++i) {
        for (int j = row; j < std::min(row + blockSize, (int) _a.size(), [](int a, int b) { return a < b; }); ++j) {
            for (int k = 0; k < _a.size(); ++k) {
                lock.lock();
                (*out)[i][j] += _a[i][k] * _b[k][j];
                lock.unlock();
            }
        }
    }
    multiplyBlocksAsync(_a, _b, blockSize);

}

std::vector<std::vector<int>>
MatrixMultiplier::multiplyMatrices(std::vector<std::vector<int>> &_a, std::vector<std::vector<int>> &_b, int blockSize,
                                   int threadsAmount) {
    if (threadsAmount > 0) {
        cords = new BufferedChannel<std::pair<int, int>>(( (int) ((int) _a.size() / blockSize) + 1) * (_a.size() / blockSize + 1));
        initThreads(threadsAmount, _a, _b, blockSize);
    }
    out = new std::vector<std::vector<int>>(_a.size(), std::vector<int>(_a.size()));

    for (int line = 0; line < _a.size(); line += blockSize) {
        for (int row = 0; row < _a.size(); row += blockSize) {
            if (threadsAmount > 0) {
                cords->Send(std::pair(line, row));
            } else {
                multiplyBlocks(_a, _b, line, row, blockSize);
            }
        }
    }

    for (auto &item : threads){
        item.join();
    }

    delete cords;
    threads.clear();

    auto result = *out;
    delete out;
    return result;
}


void MatrixMultiplier::multiplyBlocks(std::vector<std::vector<int>> &_a, std::vector<std::vector<int>> &_b, int line,
                                      int row, int blockSize) {
    for (int i = line; i < std::min(line + blockSize, (int) _a.size(), [](int a, int b) { return a < b; }); ++i) {
        for (int j = row; j < std::min(row + blockSize, (int) _a.size(), [](int a, int b) { return a < b; }); ++j) {
            for (int k = 0; k < _a.size(); ++k) {
                lock.lock();
                (*out)[i][j] += _a[i][k] * _b[k][j];
                lock.unlock();
            }
        }
    }
}

void MatrixMultiplier::initThreads(int threadsCount, std::vector<std::vector<int>> &_a, std::vector<std::vector<int>> &_b, int blockSize) {
    while(threadsCount != 0){
        threads.emplace_back(multiplyBlocksAsync, std::cref(_a), std::cref(_b), blockSize);
        threadsCount--;
    }
}
