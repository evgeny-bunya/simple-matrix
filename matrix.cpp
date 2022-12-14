#include "matrix.hpp"
#include <iostream>

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

size_t Matrix::MatrixRow::getLength() const {return data.size();}

void Matrix::MatrixRow::print() const
{
    for (double value : data)
    {
        std::cout << value << " ";
    }
    std::cout << std::endl;
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

size_t Matrix::getHeight() const {return data.size();}
size_t Matrix::getWidth() const
{
    if (!data.empty())
    {
        return data[0].getLength();
    }
    else
    {
        return 0;
    }
}

void Matrix::print()
{
    for (const auto& row : data)
    {
        row.print();
    }
}

Matrix::MatrixIterator Matrix::begin()
{
    return MatrixIterator::begin(*this);
}

Matrix::MatrixIterator Matrix::end()
{
    return MatrixIterator::end(*this);
}

Matrix::ConstMatrixIterator Matrix::cbegin() const
{
    return ConstMatrixIterator::begin(*this);
}

Matrix::ConstMatrixIterator Matrix::cend() const
{
    return ConstMatrixIterator::end(*this);
}