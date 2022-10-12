#ifndef OS_LABS_MATRIXMULTIPLIER_H
#define OS_LABS_MATRIXMULTIPLIER_H

#include <mutex>
#include <vector>
#include <algorithm>
#include <thread>
#include <exception>

class MatrixMultiplier {
private:
    std::vector<std::vector<int>> _a;
    std::vector<std::vector<int>> _b;
    std::mutex _lock;
    std::vector<std::vector<int>> _temp;

    void multiplyBlocks(int line, int row, int blockSize);
public:
    MatrixMultiplier(const std::vector<std::vector<int>>& a, const std::vector<std::vector<int>>& b);
    std::vector<std::vector<int>> multiplyMatrices(int blockSize, bool async = true);
    int getSize();
};


#endif //OS_LABS_MATRIXMULTIPLIER_H
