cmake_minimum_required(VERSION 3.20)

project(matrix)

add_executable(matrix main.cpp)

set_target_properties(matrix PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
        )

project(matrix_test)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL
        https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(matrix_test test.cpp)

target_include_directories(matrix_test PUBLIC ${gtest_SOURCE_DIR}/include)

target_link_libraries(matrix_test PRIVATE gtest_main)