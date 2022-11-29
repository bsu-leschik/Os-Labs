#include "MatrixMultiplier.h"

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

std::vector<std::vector<int>> a;
std::vector<std::vector<int>> b;
int blockSize;
std::vector<std::vector<int>> out;

static void *multiplyBlocks(void* args);

std::vector<std::vector<int>> MatrixMultiplier::multiplyMatrices(std::vector<std::vector<int>>& _a, std::vector<std::vector<int>>& _b, int _blockSize, bool async) {

    a = _a;
    b = _b;
    blockSize = _blockSize;

    out = std::vector<std::vector<int>>(_a.size(), std::vector<int>(_a.size()));

    std::vector<pthread_t> threads;
    pthread_attr_t attr;

    if (async) {
        pthread_mutex_init(&lock, NULL);
        pthread_attr_init(&attr);
    }

    for (int line = 0; line < a.size(); line += blockSize) {
        for (int row = 0; row < a.size(); row += blockSize) {
            int* args = new int[2];
            args[0] = line;
            args[1] = row;

            if (async) {
                threads.emplace_back();
                pthread_create(&threads.back(), &attr, &multiplyBlocks, args);
            }
            else {
                multiplyBlocks(args);
            }
        }
    }
    if (async) {
        for (pthread_t &thread: threads) {
            pthread_join(thread, nullptr);
        }
    }
    return out;
}


void *multiplyBlocks(void* args) {
    int* nums = static_cast<int *>(args);
    int line = nums[0];
    int row = nums[1];

    for (int i = line; i < std::min(line + blockSize, (int)a.size(), [](int a1, int b1) {return a1 < b1;}); ++i) {
        for (int j = row; j < std::min(row + blockSize, (int)a.size(), [](int a2, int b2) {return a2 < b2;}); ++j) {
            for (int k = 0; k < a.size(); ++k) {
                pthread_mutex_lock(&lock);
                out[i][j] += a[i][k] * b[k][j];
                pthread_mutex_unlock(&lock);
            }
        }
    }
    delete nums;
}
