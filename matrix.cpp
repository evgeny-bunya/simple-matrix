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

size_t Matrix::MatrixRow::getLength() {return data.size();}

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

size_t Matrix::getHeight() {return data.size();}
size_t Matrix::getWidth()
{
    if (data.size() > 0)
    {
        return data[0].getLength();
    }
    else
    {
        return 0;
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

Matrix::MatrixIterator::MatrixIterator(Matrix& matrix, size_t rowIndex, size_t columnIndex):
   matrixRef(matrix), rowId(rowIndex), columnId(columnIndex)
{
}

double& Matrix::MatrixIterator::operator*() const
{
    return matrixRef[rowId][columnId];
}
double* Matrix::MatrixIterator::operator->() const
{
    return &matrixRef[rowId][columnId];
}

Matrix::MatrixIterator& Matrix::MatrixIterator::operator++()
{
    columnId++;
    if (columnId >= matrixRef.getWidth())
    {
        columnId = 0;
        rowId++;
    }
    return *this;
}

Matrix::MatrixIterator Matrix::MatrixIterator::operator++(int)
{
    MatrixIterator it(*this);
    ++(*this);
    return it;
}