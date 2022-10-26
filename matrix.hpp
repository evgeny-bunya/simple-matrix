/*
 * simple matrix class with concatenation and sum support
 *
 * operator | is concatenation C = (A | B)
 * operator + is per-element summary C = A + B
 * operator - is per-element subtraction C = A - B
 * operator [] are supported
 * custom iterators are supported
 * copy and move ctors are default (since we are storing std::vector only)
 */
#pragma once
#include <vector>

class Matrix
{
    class MatrixRow
    {
    public:
        explicit MatrixRow(int length);
        double operator[](int id) const;
        double& operator[](int id);
        size_t getLength() const;
        MatrixRow& operator|=(const MatrixRow& right);
        MatrixRow& operator+=(const MatrixRow& right);
        MatrixRow& operator-=(const MatrixRow& right);
        void print() const;
    private:
        std::vector<double> data;
    };

    class MatrixIterator
    {
    public:
        static MatrixIterator begin(Matrix& matrix) { return {matrix, 0, 0};}
        static MatrixIterator end(Matrix& matrix) { return {matrix, matrix.data.size(), 0};}
        double& operator*() const;
        double* operator->() const;
        MatrixIterator& operator++();
        const MatrixIterator operator++(int);
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

    class ConstMatrixIterator
    {
    public:
        static ConstMatrixIterator begin(const Matrix& matrix) { return {matrix, 0, 0};}
        static ConstMatrixIterator end(const Matrix& matrix) { return {matrix, matrix.data.size(), 0};}
        double operator*() const;
        ConstMatrixIterator& operator++();
        const ConstMatrixIterator operator++(int);
        friend bool operator==(const ConstMatrixIterator& left, const ConstMatrixIterator& right)
        {
            return (&left.matrixRef == &right.matrixRef) &&
                   (left.rowId == right.rowId) &&
                   (left.columnId == right.columnId);
        }
        friend bool operator!=(const ConstMatrixIterator& left, const ConstMatrixIterator& right)
        {
            return !operator==(left, right);
        }
    private:
        ConstMatrixIterator(const Matrix& matrix, size_t rowIndex, size_t columnIndex);
        const Matrix& matrixRef;
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
    size_t getHeight() const;
    size_t getWidth() const;
    MatrixIterator begin();
    MatrixIterator end();
    ConstMatrixIterator cbegin() const;
    ConstMatrixIterator cend() const;
    void print();
private:
    std::vector<MatrixRow> data;
};




