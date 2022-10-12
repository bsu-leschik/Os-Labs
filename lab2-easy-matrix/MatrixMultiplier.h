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
    static std::mutex _lock;

    static void multiplyBlocks(std::vector<std::vector<int>>& _a, std::vector<std::vector<int>>& _b, int line, int row, int blockSize, std::vector<std::vector<int>>& out);
public:
    MatrixMultiplier(const std::vector<std::vector<int>>& a, const std::vector<std::vector<int>>& b);
    static std::vector<std::vector<int>> multiplyMatrices(std::vector<std::vector<int>>& _a, std::vector<std::vector<int>>& _b, int blockSize, bool async = true);
};


#endif //OS_LABS_MATRIXMULTIPLIER_H
