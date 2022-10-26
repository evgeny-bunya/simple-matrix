/*
 * simple matrix class with concatenation and sum support
 *
 * operator | is concatenation C = (A | B)
 * operator + is per-element summary C = A + B
 * operator - is per-element subtraction C = A - B
 * custom iterator support
 * copy and move ctors are default (since we are storing std::vector only)
 */
#pragma once
#include <vector>

class Matrix
{
    class MatrixRow
    {
    public:
        MatrixRow(int length);
        double operator[](int id) const;
        double& operator[](int id);
        size_t getLength();
        MatrixRow& operator|=(const MatrixRow& right);
        MatrixRow& operator+=(const MatrixRow& right);
        MatrixRow& operator-=(const MatrixRow& right);
    private:
        std::vector<double> data;
    };

    class MatrixIterator
    {
    public:
        static MatrixIterator begin(Matrix& matrix) { return MatrixIterator(matrix, 0, 0);}
        static MatrixIterator end(Matrix& matrix) { return MatrixIterator(matrix, matrix.data.size(), 0);}
        double& operator*() const;
        double* operator->() const;
        MatrixIterator& operator++();
        MatrixIterator operator++(int);
        friend bool operator==(const MatrixIterator& left, const MatrixIterator& right)
        {
            return (&left.matrixRef == &right.matrixRef) &&
                (left.rowId == right.rowId) &&
                (left.columnId == right.columnId);
        }
        friend bool operator!=(const MatrixIterator& left, const MatrixIterator& right)
        {
            return !operator==(left, right);
        }
    private:
        MatrixIterator(Matrix& matrix, size_t rowIndex, size_t columnIndex);
        Matrix& matrixRef;
        size_t rowId;
        size_t columnId;
    };
public:
    Matrix(int rows, int columns);
    const MatrixRow& operator[](int id) const;
    MatrixRow& operator[](int id);
    Matrix& operator|=(const Matrix& right);
    Matrix& operator+=(const Matrix& right);
    Matrix& operator-=(const Matrix& right);
    friend Matrix operator|(Matrix left, const Matrix& right);
    friend Matrix operator+(Matrix left, const Matrix& right);
    friend Matrix operator-(Matrix left, const Matrix& right);
    size_t getHeight();
    size_t getWidth();
    MatrixIterator begin();
    MatrixIterator end();
private:
    std::vector<MatrixRow> data;
};




