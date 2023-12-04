//
// Created by Jakub on 02.11.2023.
//

#ifndef PEA_1_MATRIX_H
#define PEA_1_MATRIX_H
#include <string>

class Matrix {
public:
    int** matrixTable;
    int numberOfCites;
    void displayMatrixTable();
    Matrix *matrix2;
    std::string type;
};


#endif //PEA_1_MATRIX_H
