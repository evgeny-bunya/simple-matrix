#include "matrix.hpp"

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

const Matrix::MatrixIterator Matrix::MatrixIterator::operator++(int)
{
    MatrixIterator it(*this);
    ++(*this);
    return it;
}

Matrix::ConstMatrixIterator::ConstMatrixIterator(const Matrix& matrix, size_t rowIndex, size_t columnIndex):
        matrixRef(matrix), rowId(rowIndex), columnId(columnIndex)
{
}

double Matrix::ConstMatrixIterator::operator*() const
{
    return matrixRef[rowId][columnId];
}

Matrix::ConstMatrixIterator& Matrix::ConstMatrixIterator::operator++()
{
    columnId++;
    if (columnId >= matrixRef.getWidth())
    {
        columnId = 0;
        rowId++;
    }
    return *this;
}

const Matrix::ConstMatrixIterator Matrix::ConstMatrixIterator::operator++(int)
{
    ConstMatrixIterator it(*this);
    ++(*this);
    return it;
}