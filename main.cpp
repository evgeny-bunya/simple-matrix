#include "matrix.hpp"
#include <iostream>

int main(int argc, char** argv)
{
    const int rows = 2;
    const int columns = 5;
    Matrix matrix(rows, columns);
    matrix.print();
    std::cout << "======== init======" << std::endl;
    int index = 0;
    for (auto& val : matrix)
    {
        index++;
        val = index;
    }
    std::cout << "======== index ======" << std::endl;
    matrix[1][1] = 90;
    matrix.print();
    std::cout << "======== concatenation ======" << std::endl;
    Matrix matrix2(rows, 3);
    Matrix matrixConcat = matrix | matrix2;
    matrixConcat.print();

    std::cout << "======== per-element sum ======" << std::endl;
    Matrix matrixSum = matrix + matrix;
    matrixSum.print();
    std::cout << "======== copy ======" << std::endl;
    Matrix matrixCopy(matrix);
    matrixCopy.print();
    std::cout << "original matrix" << std::endl;
    matrix.print();
    std::cout << "======== move ======" << std::endl;
    Matrix matrixMove(std::move(matrix));
    matrixMove.print();
    std::cout << "original matrix" << std::endl;
    matrix.print();
    return 0;
}
