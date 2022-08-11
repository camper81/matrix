cmake_minimum_required(VERSION 3.20)

project(matrix)

add_executable(matrix main.cpp)

set_target_properties(matrix PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
        )

