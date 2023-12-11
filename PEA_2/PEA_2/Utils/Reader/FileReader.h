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

    std::vector<std::vector<int>> readFromFile2(std::string fileName);
};


#endif //PEA_1_FILEREADER_H
