#include "matrix.hpp"

Matrix::MatrixRow::MatrixRow(int length) {
    data.resize(length);
}
double Matrix::MatrixRow::operator[](int id) const
{
    if (id >= data.size())
    {
        throw std::invalid_argument("id is more than column length");
    }
    return data[id];
}
double &Matrix::MatrixRow::operator[](int id)
{
    if (id >= data.size())
    {
        throw std::invalid_argument("id is more than column length");
    }
    return data[id];
}

Matrix::Matrix(int rows, int columns) {
    if (rows > 0 && columns > 0)
    {
        data.reserve(rows);
        for (int i = 0 ; i < rows ; i++)
        {
            data.emplace_back(columns);
        }
    }
}

const Matrix::MatrixRow &Matrix::operator[](int id) const
{
    if (id >= data.size())
    {
        throw std::invalid_argument("id is more than row length");
    }
    return data[id];
}

Matrix::MatrixRow& Matrix::operator[](int id)
{
    if (id >= data.size())
    {
        throw std::invalid_argument("id is more than row length");
    }
    return data[id];
}


