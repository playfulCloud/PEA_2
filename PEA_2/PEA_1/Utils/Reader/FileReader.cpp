//
// Created by Jakub on 27.10.2023.
//

#include "FileReader.h"
#include <fstream>
#include <iostream>
#include <filesystem>

Matrix FileReader::readFromFile() {
    std::cout << "Enter the name of file you want to read: ";
    std::string fileName;
    std::cin >> fileName;
    Matrix result;
    result.type = "Read from file";
    int numberOfCities;
    std::fstream file;
    std::filesystem::path projectPath = std::filesystem::current_path();
    projectPath = projectPath.parent_path(); // Uzyskanie ścieżki do katalogu nadrzędnego
    std::string filePath = projectPath.string() + "\\PEA_1\\data\\" + fileName;
    std::cout << filePath << std::endl;
    file.open(filePath, std::ios::in);

    if (!file.is_open()) {
        std::cout << "Cant read file properly" << std::endl;

    }

    if (!std::filesystem::exists(filePath)) {
        std::cout << "File does not exist" << std::endl;

    }

    file >> numberOfCities;
    if (file.fail()) {
        std::cout << "Failed to read number of cities" << std::endl;

    }

    result.numberOfCites = numberOfCities;

    result.matrixTable = new int *[numberOfCities];
    for (int i = 0; i < numberOfCities; ++i) {
        result.matrixTable[i] = new int[numberOfCities];
        for (int j = 0; j < numberOfCities; ++j) {
            file >> result.matrixTable[i][j];
            if (file.fail()) {
                std::cout << "Failed to read matrix element" << std::endl;
                return result;
            }
        }
    }

    file.close();
    std::cout << "Matrix read successfully!" << std::endl;
    return result;
}


