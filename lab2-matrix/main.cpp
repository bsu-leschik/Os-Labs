#include <vector>
#include "Matrix.h"
#include <iostream>

int main(){
    std::vector<int> line = std::vector<int>({7, 11, 92, 3, 5});
    std::vector<int> line1 = std::vector<int>({6, 47, 1, 52, 94});
    std::vector<int> line2 = std::vector<int>({4, 43, 87, 36, 22});
    std::vector<int> line3 = std::vector<int>({8, 45, 98, 67, 23});
    std::vector<int> line4 = std::vector<int>({90, 13, 23, 76, 56});
    std::vector<std::vector<int>> matrix = std::vector<std::vector<int>>({line, line1, line2, line3, line4});

    std::vector<int> line5 = std::vector<int>({78, 87, 74, 35, 59});
    std::vector<int> line6 = std::vector<int>({93, 60, 30, 29, 54});
    std::vector<int> line7 = std::vector<int>({62, 95, 83, 1, 48});
    std::vector<int> line8 = std::vector<int>({12, 73, 70, 24, 86});
    std::vector<int> line9 = std::vector<int>({7, 12, 43, 5, 95});
    std::vector<std::vector<int>> matrix1 = std::vector<std::vector<int>>({line5, line6, line7, line8, line9});

    Matrix m = Matrix(matrix);
    Matrix m1 = Matrix(matrix1);

    Matrix res = m * m1;

    std::cout << res;
    return 0;
}