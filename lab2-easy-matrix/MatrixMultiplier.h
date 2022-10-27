#ifndef OS_LABS_MATRIXMULTIPLIER_H
#define OS_LABS_MATRIXMULTIPLIER_H

#include "../lab3/BufferedChannel.h"
#include <mutex>
#include <vector>
#include <algorithm>
#include <thread>
#include <exception>

class MatrixMultiplier {
private:
    static void multiplyBlocks(std::vector<std::vector<int>> &_a, std::vector<std::vector<int>> &_b, int line, int row,
                               int blockSize);

    static void initThreads(int threadsCount, std::vector<std::vector<int>> &_a, std::vector<std::vector<int>> &_b, int blockSize);

public:
    static std::vector<std::vector<int>>
    multiplyMatrices(std::vector<std::vector<int>> &_a, std::vector<std::vector<int>> &_b, int blockSize,
                     int threadsAmount = 0);
};


#endif //OS_LABS_MATRIXMULTIPLIER_H
