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

TEST(Matrix, copy)
{
    const int rows = 2;
    const int columns = 5;
    Matrix matrix_original(rows, columns);
    matrix_original[0][0] = 2.0;
    Matrix newMatrix = matrix_original;
    EXPECT_DOUBLE_EQ(newMatrix[0][0], 2.0);
}

TEST(Matrix, move)
{
    const int rows = 2;
    const int columns = 5;
    Matrix matrix_original(rows, columns);
    matrix_original[0][0] = 2.0;
    Matrix newMatrix = std::move(matrix_original);
    EXPECT_DOUBLE_EQ(newMatrix[0][0], 2.0);
}

TEST(Matrix, concatenation)
{
    const int rows = 2;
    const int columns1 = 5;
    const int columns2 = 3;
    Matrix matrix1(rows, columns1);
    Matrix matrix2(rows, columns2);
    const double value1 = 5.5;
    const double value2 = -1.6;
    for (int i = 0 ; i < rows ; i++)
    {
        for (int j = 0; j < columns1; j++)
        {
            matrix1[i][j] = value1;
        }
        for (int j = 0; j < columns2; j++)
        {
            matrix2[i][j] = value2;
        }
    }
    matrix1 |= matrix2;
    for (int i = 0 ; i < rows ; i++)
    {
        for (int j = 0 ; j < columns1 + columns2 ; j++)
        {
            if (j < columns1)
                EXPECT_DOUBLE_EQ(matrix1[i][j], value1);
            else
                EXPECT_DOUBLE_EQ(matrix1[i][j], value2);
        }
    }
    Matrix matrix3 = matrix2 | matrix1;
    for (int i = 0 ; i < rows ; i++)
    {
        for (int j = 0 ; j < columns1 + 2 * columns2 ; j++)
        {
            if ((j < columns2) || (j >= columns1 + columns2))
                EXPECT_DOUBLE_EQ(matrix3[i][j], value2);
            else
                EXPECT_DOUBLE_EQ(matrix3[i][j], value1);
        }
    }
}

TEST(Matrix, sumAndSubtraction)
{
    const int rows = 2;
    const int columns = 5;
    Matrix matrix1(rows, columns);
    Matrix matrix2(rows, columns);
    const double value1 = 5.5;
    const double value2 = -1.6;
    for (int i = 0 ; i < rows ; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            matrix1[i][j] = value1;
            matrix2[i][j] = value2;
        }
    }
    matrix1 += matrix2;
    for (int i = 0 ; i < rows ; i++)
    {
        for (int j = 0 ; j < columns; j++)
        {
            EXPECT_DOUBLE_EQ(matrix1[i][j], value1 + value2);
        }
    }
    Matrix matrix3 = matrix1 + matrix2;
    for (int i = 0 ; i < rows ; i++)
    {
        for (int j = 0 ; j < columns ; j++)
        {
            EXPECT_DOUBLE_EQ(matrix3[i][j], value1 + 2 * value2);
        }
    }
    Matrix matrix4 = matrix3 - matrix2;
    for (int i = 0 ; i < rows ; i++)
    {
        for (int j = 0 ; j < columns ; j++)
        {
            EXPECT_DOUBLE_EQ(matrix4[i][j], value1 + value2);
        }
    }
}

TEST(Matrix, iteratorCheck)
{
    const int rows = 2;
    const int columns = 5;
    Matrix matrix(rows, columns);
    // checking prefix increment
    int index = 0;
    for (auto it = matrix.begin(); it != matrix.end() ; ++it)
    {
        *it = index;
        index++;
    }
    index = 0;
    for (int i = 0 ; i < rows ; i++)
    {
        for (int j = 0 ; j < columns ; j++)
        {
            EXPECT_DOUBLE_EQ(matrix[i][j], index);
            index++;
        }
    }
    // checking postfix increment
    index = 0;
    for (auto it = matrix.begin(); it != matrix.end() ; it++)
    {
        *it = index * 2;
        index++;
    }
    index = 0;
    for (int i = 0 ; i < rows ; i++)
    {
        for (int j = 0 ; j < columns ; j++)
        {
            EXPECT_DOUBLE_EQ(matrix[i][j], index * 2);
            index++;
        }
    }
    // check using of std::transform with custom iterators
    index = 0;
    std::transform(
            matrix.begin(),
            matrix.end(),
            matrix.begin(),
            [](double val) {return -val;});
    for (int i = 0 ; i < rows ; i++)
    {
        for (int j = 0 ; j < columns ; j++)
        {
            EXPECT_DOUBLE_EQ(matrix[i][j], -index * 2);
            index++;
        }
    }
    // const iterator check
    index = 0;
    const Matrix constMatrix = matrix;
    for (auto it = constMatrix.cbegin() ; it != constMatrix.cend() ; ++it)
    {
        EXPECT_DOUBLE_EQ(*it, -index * 2);
        index++;
    }
}

TEST(Matrix, exceptionCheck)
{
    const int rows = 3;
    const int columns = 2;
    Matrix matrix(rows, columns);
    EXPECT_THROW(matrix[rows][0], std::invalid_argument);
    EXPECT_THROW(matrix[0][columns], std::invalid_argument);
    // checking sum and subtraction with different size of matrices
    Matrix matrix1(2, 5);
    Matrix matrix2(3, 5);
    EXPECT_THROW(matrix1+=matrix2, std::invalid_argument);
    EXPECT_THROW(matrix1-=matrix2, std::invalid_argument);
    EXPECT_THROW(matrix1 + matrix2, std::invalid_argument);
    EXPECT_THROW(matrix1 - matrix2, std::invalid_argument);
    // checking concatenation with different height
    matrix1 = Matrix(2, 4);
    matrix2 = Matrix(3, 4);
    EXPECT_THROW(matrix1 |= matrix2, std::invalid_argument);
    EXPECT_THROW(matrix1 | matrix2, std::invalid_argument);
}