/*
 * simple matrix class with concatenation and sum support
 */
#pragma once
#include <vector>

class Matrix
{
public:
    Matrix(int rows, int columns);
    Matrix(const Matrix&);
    Matrix(Matrix&&);
    class MatrixRow
    {
    public:
        MatrixRow(int length);
        double operator[](int id) const;
        double& operator[](int id);
    private:
        std::vector<double> data;
    };
    const MatrixRow& operator[](int id) const;
    MatrixRow& operator[](int id);
private:
    std::vector<MatrixRow> data;
};

