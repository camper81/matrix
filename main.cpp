#include <iostream>
#include <iomanip>
#include "matrix.h"

int main() {
    Matrix<int, -1> main_matrix;
    const int n = 10;
    // fill main diagonal
    for(int i = 0; i < n; i++) {
        main_matrix[i][i] = i;
    }

    // fill counter diagonal
    for(int i = n - 1; i >= 0; i--) {
        main_matrix[i][n - i - 1] = i;
    }
    std::cout << "Matrix:" << std::endl;
    for(int i = 1; i < n - 1; ++i) {
        for(int j = 1; j < n - 1; ++j) {
            std::cout << std::setw(2)<< main_matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Matrix cells: " << main_matrix.size() << std::endl;

    std::cout << std::endl;
    std::cout << "Matrix elements:" << std::endl;
    for(auto elem: main_matrix)
    {
        int i, j, value;
        std::tie(i, j, value) = elem;
        std::cout << "matrix[" << i << "][" << j << "] = " << value << std::endl;
    }
    std::cout << "done" << std::endl;

    return 0;
}