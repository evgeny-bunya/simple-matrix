/*
 * simple matrix class with concatenation and sum support
 */
#pragma once
#include <vector>

class Matrix
{
public:
    Matrix(int rows, int columns);
    class MatrixRow
    {
    public:
        MatrixRow(int length);
        double operator[](int id) const;
        double& operator[](int id);
        MatrixRow& operator|=(const MatrixRow& right);
        MatrixRow& operator+=(const MatrixRow& right);
        MatrixRow& operator-=(const MatrixRow& right);
    private:
        std::vector<double> data;
    };
    const MatrixRow& operator[](int id) const;
    MatrixRow& operator[](int id);
    Matrix& operator|=(const Matrix& right);
    Matrix& operator+=(const Matrix& right);
    Matrix& operator-=(const Matrix& right);
    friend Matrix operator|(Matrix left, const Matrix& right);
    friend Matrix operator+(Matrix left, const Matrix& right);
    friend Matrix operator-(Matrix left, const Matrix& right);
private:
    std::vector<MatrixRow> data;
};



