//
// Created by Jakub on 27.10.2023.
//

#ifndef PEA_1_FILEREADER_H
#define PEA_1_FILEREADER_H


#include <string>
#include "../CityMatrix/AdjacencyMatrix.h"

class FileReader {
public:
    std::vector<std::vector<int>> readFromFile();
};


#endif //PEA_1_FILEREADER_H
