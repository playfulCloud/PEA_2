//
// Created by Jakub on 02.11.2023.
//

#ifndef PEA_1_GENERATOR_H
#define PEA_1_GENERATOR_H


#include "../CityMatrix/Matrix.h"

class Generator {
public:
    Matrix generateRandomMatrix();

    Matrix generateRandomSymetricMatrix(int num_cities);
};


#endif //PEA_1_GENERATOR_H
