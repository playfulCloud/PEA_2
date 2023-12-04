//
// Created by Jakub on 27.10.2023.
//

#include <iostream>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include "Menu.h"

/*TODO
 * 1. Wczytywanie danych z pliku.
 * 2. Wygenerowanie losowych danych.
 * 3. Wyświetlenie ostatnio wczytanych daynch.
 * 4. Wyświetlenie ostatnio wygenerowanych danych.
 * 5. Uruchomienie algorytmu dla wygenerowanych danych bądź wczytanych danych.
 * Wyświetlenie Wynik: Długość ścieżki: X  Ciąg Wierzchołków: X-Y-Z Czas Wykonywania: X.XXms
 * */



void Menu::displayMenu() {
    std::cout << "=========================== Effective algorithm design ===========================" << std::endl;
    int gate = 0;
    while (gate != 8) {
        std::cout << "Choose what do you want to do: " << std::endl;
        std::cout << "1 - Read data from file" << std::endl;
        std::cout << "2 - Generate random data" << std::endl;
        std::cout << "3 - Display read data" << std::endl;
        std::cout << "4 - Display randomly generated data" << std::endl;
        std::cout << "5 - Choose algorithm with read data" << std::endl;
        std::cout << "6 - Choose algorithm with randomly generated data" << std::endl;
        std::cout << "7 - Tests" << std::endl;
        std::cout << "8 - Exit" << std::endl;
        std::cin >> gate;
        switch (gate) {
            case 1:
                graph = fileReader->readFromFile();
                graph.displayMatrixTable();
                break;
            case 2:
                randomGraph = generator->generateRandomMatrix();
                randomGraph.displayMatrixTable();
                break;
            case 3:
                graph.displayMatrixTable();
                break;
            case 4:
                randomGraph.displayMatrixTable();
                break;
            case 5:
                displayAlgorithms(graph);
                break;
            case 6:
                displayAlgorithms(randomGraph);
                break;
            case 7:
//                doTests(6,"answer6.txt");
//                doTests(7,"answer7.txt");
//                doTests(8,"answer8.txt");
//                doTests(9,"answer9.txt");
//                doTests(10,"answer10.txt");
//                doTests(11,"answer11.txt");
                doTests(12,"answer12.txt");
//                doTests(13,"answer13.txt");
//                doTests(14,"answer14.txt");
//                doTests(15,"answer15.txt");
                break;

        }
    }
}


void Menu::displayAlgorithms(Matrix matrix) {
    std::cout << "=========================== Algorithms menu ===========================" << std::endl;
    std::cout << "Matrix: " + matrix.type << std::endl;
    int gate = 0;
    while (gate != 5) {
        std::cout << "Choose what do you want to do: " << std::endl;
        std::cout << "1 - Brute Force" << std::endl;
        std::cout << "2 - Branch and Bound v1" << std::endl;
        std::cout << "4 - Dynamic Programming" << std::endl;
        std::cout << "5 - Exit" << std::endl;
        std::cin >> gate;
        switch (gate) {
            case 1:
                bruteForceImplementation->tsp(matrix.matrixTable, matrix.numberOfCites);
                break;
            case 2:
                branchAndBoundImplementation = new BranchAndBound_Implementation(matrix.numberOfCites);
                branchAndBoundImplementation->solution(matrix.matrixTable);
                break;
            case 3:
                break;
            case 4:
                dynamicProgrammingImplementation = new DynamicProgramming_implementation(matrix.matrixTable,matrix.numberOfCites);
                dynamicProgrammingImplementation->solution(matrix.matrixTable);
                break;

        }
    }
}


void Menu::doTests(int num_cities, std::string file) {

    std::filesystem::path projectPath = std::filesystem::current_path();
    projectPath = projectPath.parent_path(); // Uzyskanie ścieżki do katalogu nadrzędnego
    std::string filePath = projectPath.string() + "\\PEA_1\\data\\" + file;
    std::cout << filePath;

    std::ofstream fileStream(filePath);

    long long int brute = 0;
    long long int dynamic = 0;
    long long int branch = 0;

    for(int i = 0; i < 20; i++){
        Matrix matrix = generator->generateRandomSymetricMatrix(num_cities);

        brute += bruteForceImplementation->tsp(matrix.matrixTable,matrix.numberOfCites);

        dynamicProgrammingImplementation = new DynamicProgramming_implementation(matrix.matrixTable,matrix.numberOfCites);
        dynamic += dynamicProgrammingImplementation->solution(matrix.matrixTable);

        branchAndBoundImplementation = new BranchAndBound_Implementation(matrix.numberOfCites);
        branch += branchAndBoundImplementation->solution(matrix.matrixTable);

    }

    if (fileStream.is_open()) {
        fileStream << "Brute: \n";
        fileStream << brute/20 << "\n";
        fileStream << "dynamic: \n";
        fileStream << dynamic/20 << "\n";
        fileStream << "branch: \n";
        fileStream << branch/20 << "\n";
    } else {
        std::cerr << "Error opening file: " << file << std::endl;
    }
    std::cout << "Test with num_cites: " << num_cities << " done!" << std::endl;
}




