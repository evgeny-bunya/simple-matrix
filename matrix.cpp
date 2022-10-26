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

Matrix::MatrixRow& Matrix::MatrixRow::operator|=(const Matrix::MatrixRow& right)
{
    this->data.insert(this->data.end(), right.data.begin(), right.data.end());
    return *this;
}

Matrix::MatrixRow& Matrix::MatrixRow::operator+=(const Matrix::MatrixRow& right)
{
    if (this->data.size() != right.data.size())
    {
        throw std::invalid_argument("number of columns are different");
    }
    for (int i = 0 ; i < this->data.size() ; i++)
    {
        this->data[i] += right.data[i];
    }
    return *this;
}

Matrix::MatrixRow& Matrix::MatrixRow::operator-=(const Matrix::MatrixRow& right)
{
    if (this->data.size() != right.data.size())
    {
        throw std::invalid_argument("number of columns are different");
    }
    for (int i = 0 ; i < this->data.size() ; i++)
    {
        this->data[i] -= right.data[i];
    }
    return *this;
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

Matrix& Matrix::operator|=(const Matrix& right)
{
    if (this->data.size() != right.data.size())
    {
        throw std::invalid_argument("matrices have different height!");
    }
    for (unsigned int i = 0 ; i < this->data.size() ; i++)
    {
        this->data[i] |= right.data[i];
    }
    return *this;
}

Matrix& Matrix::operator+=(const Matrix& right)
{
    if (this->data.size() != right.data.size())
    {
        throw std::invalid_argument("matrices have different number rows!");
    }
    for (unsigned int i = 0 ; i < this->data.size() ; i++)
    {
        this->data[i] += right.data[i];
    }
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& right)
{
    if (this->data.size() != right.data.size())
    {
        throw std::invalid_argument("matrices have different number rows!");
    }
    for (unsigned int i = 0 ; i < this->data.size() ; i++)
    {
        this->data[i] -= right.data[i];
    }
    return *this;
}

Matrix operator|(Matrix left, const Matrix& right)
{
    left |= right;
    return left;
}
Matrix operator+(Matrix left, const Matrix& right)
{
    left += right;
    return left;
}
Matrix operator-(Matrix left, const Matrix& right)
{
    left -= right;
    return left;
}

