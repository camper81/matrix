//
// Created by BELICKYANMA_DESKTOP on 16.08.2022.
//
#include <gtest/gtest.h>
#include <iostream>
#include <iomanip>
#include "matrix.h"

TEST(MatrixTest, empty_test) {
    Matrix<int, -1> matrix;
    ASSERT_EQ(matrix.size(), 0); // все ячейки свободны
}

TEST(MatrixTest, default_element_test) {
    Matrix<int, -1> matrix;
    auto a = matrix[0][0];
    ASSERT_EQ(a, -1);
}
TEST(MatrixTest, one_element_test) {
    Matrix<int, -1> matrix;
    ASSERT_EQ(matrix.size(), 0);
    matrix[100][100] = 314;
    ASSERT_EQ(matrix[100][100], 314);
    ASSERT_EQ(matrix.size(), 1);
}
TEST(MatrixTest, output_test) {
    Matrix<int, -1> matrix;
    matrix[100][100] = 314;
    // выведется одна строка
    // 100100314
    std::stringstream sstr;
    std::stringstream except{"100100314\n"};
    for(auto c : matrix)
    {
        int x;
        int y;
        int v;
        std::tie(x, y, v) = c;
        sstr << x << y << v << std::endl;
    }
    ASSERT_EQ(sstr.str(), except.str());
}