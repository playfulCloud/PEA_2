//
// Created by Jakub on 02.11.2023.
//

#ifndef PEA_1_MATRIX_H
#define PEA_1_MATRIX_H
#include <string>
#include <vector>

class AdjacencyMatrix {

public:
    std::vector<std::vector<double>> matrix;
    AdjacencyMatrix(int size) : matrix(size, std::vector<double>(size, 0.0)) {};
    int numberOfCites;
    void displayMatrixTable();
    std::string type;
};


#endif //PEA_1_MATRIX_H
