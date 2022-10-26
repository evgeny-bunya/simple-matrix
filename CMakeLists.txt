cmake_minimum_required(VERSION 3.10)
project(simple-matrix CXX)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(googletest)

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-Wall -pedantic")
endif()

set(GTEST_ROOT "googletest")

add_library(matrix_lib
            matrix.hpp
            matrix.cpp
            matrix_iterators.cpp)

add_executable(${PROJECT_NAME}
               main.cpp)

include_directories(googletest/include)

add_executable(matrix_test
               matrix_test.cpp)
target_link_libraries(matrix_test matrix_lib gtest_main)

enable_testing()
add_test(matrix_test matrix_test)
