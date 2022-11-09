#include "MatrixMultiplier.h"

std::mutex lock;

std::vector<std::vector<int>> a;
std::vector<std::vector<int>> b;
int blockSize;
std::vector<std::vector<int>> out;

DWORD WINAPI multiplyBlocks(LPVOID args);
HANDLE* vectorToArray(std::vector<HANDLE> threads);

std::vector<std::vector<int>> MatrixMultiplier::multiplyMatrices(std::vector<std::vector<int>>& _a, std::vector<std::vector<int>>& _b, int _blockSize, bool async) {

    a = _a;
    b = _b;
    blockSize = _blockSize;

    out = std::vector<std::vector<int>>(_a.size(), std::vector<int>(_a.size()));

    std::vector<HANDLE> threads;

    for (int line = 0; line < a.size(); line += blockSize) {
        for (int row = 0; row < a.size(); row += blockSize) {
            int* args = new int[2];
            args[0] = line;
            args[1] = row;

            if (async) {
                DWORD i;
                threads.push_back(CreateThread(NULL, 0, multiplyBlocks, args, 0, &i));
                if (i == NULL){
                    ExitProcess(3);
                }
            }
            else {
                multiplyBlocks(args);
            }
        }
    }
    if (async) {
        WaitForMultipleObjects(threads.size(), vectorToArray(threads) , TRUE, INFINITE);

        for (auto &item: threads){
            CloseHandle(item);
        }
    }
    return out;
}

HANDLE* vectorToArray(std::vector<HANDLE> threads){
    auto* array = new HANDLE[threads.size()];

    for (int i = 0; i < threads.size(); i++) {
        array[i] = threads[i];
    }
    return array;
}


DWORD WINAPI multiplyBlocks(LPVOID args) {
    int* nums = static_cast<int *>(args);
    int line = nums[0];
    int row = nums[1];

    for (int i = line; i < min(line + blockSize, (int)a.size()); ++i) {
        for (int j = row; j < min(row + blockSize, (int) a.size()); ++j) {
            for (int k = 0; k < a.size(); ++k) {
                lock.lock();
                out[i][j] += a[i][k] * b[k][j];
                lock.unlock();
            }
        }
    }
    delete nums;
    return 0;
}
