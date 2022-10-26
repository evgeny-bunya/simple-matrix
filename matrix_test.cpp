#include <cassert>

#include "gtest/gtest.h"

#include "matrix.hpp"

TEST(Matrix, testCreation)
{
    const int rows = 2;
    const int columns = 5;
    const Matrix matrix_const(rows, columns);
    Matrix matrix_editable(rows, columns);
    for (int i = 0 ; i < rows ; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            EXPECT_DOUBLE_EQ(matrix_const[i][j], 0.0);
            EXPECT_DOUBLE_EQ(matrix_editable[i][j], 0.0);
        }
    }
}

TEST(Matrix, editableCheck)
{
    const int rows = 2;
    const int columns = 5;
    Matrix matrix_editable(rows, columns);
    for (int i = 0 ; i < rows ; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            EXPECT_DOUBLE_EQ(matrix_editable[i][j], 0.0);
            const double newValue = 1.5;
            matrix_editable[i][j] = newValue;
            EXPECT_DOUBLE_EQ(matrix_editable[i][j], newValue);
        }
    }
}

TEST(Matrix, exceptionCheck)
{
    const int rows = 3;
    const int columns = 2;
    Matrix matrix(rows, columns);
    EXPECT_THROW(matrix[rows][0], std::invalid_argument);
    EXPECT_THROW(matrix[0][columns], std::invalid_argument);
}