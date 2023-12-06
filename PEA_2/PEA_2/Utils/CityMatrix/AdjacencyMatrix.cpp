//
// Created by Jakub on 02.11.2023.
//

#include <iostream>
#include "AdjacencyMatrix.h"


void AdjacencyMatrix::displayMatrixTable() {
    for (int i = 0; i < this->numberOfCites; ++i) {
        for (int j = 0; j < this->numberOfCites; ++j) {
            std::cout << matrix[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

