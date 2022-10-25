#include <cassert>

#include "gtest/gtest.h"

#include "matrix.hpp"

TEST(Matrix, testCreation)
{
    const int rows = 2;
    const int columns = 5;
    Matrix matrix(rows, columns);
    for (int i = 0 ; i < rows ; i++)
        for (int j = 0 ; j < columns ; j++)
            EXPECT_DOUBLE_EQ(matrix[i][j], 0.0);
}

TEST(Matrix, exceptionCheck)
{
    const int rows = 2;
    const int columns = 5;
    Matrix matrix(rows, columns);
    EXPECT_THROW(matrix[rows][0], std::invalid_argument);
    EXPECT_THROW(matrix[0][columns], std::invalid_argument);
}