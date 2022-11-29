#ifndef OS_LABS_MATRIXMULTIPLIER_H
#define OS_LABS_MATRIXMULTIPLIER_H

#include <mutex>
#include <vector>
#include <algorithm>
#include <pthread.h>
#include <exception>

class MatrixMultiplier {
public:
    static std::vector<std::vector<int>> multiplyMatrices(std::vector<std::vector<int>>& _a, std::vector<std::vector<int>>& _b, int blockSize, bool async = true);
};


#endif //OS_LABS_MATRIXMULTIPLIER_H
