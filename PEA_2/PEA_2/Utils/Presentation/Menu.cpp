//
// Created by Jakub on 27.10.2023.
//

#include <iostream>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include "Menu.h"

Menu::Menu(){

}


void Menu::displayMenu() {
    std::cout << "=========================== Effective algorithm design 2 ===========================" << std::endl;
    int gate = 0;
    while (gate != 4) {
        std::cout << "Choose what do you want to do: " << std::endl;
        std::cout << "1 - Read data from ATSP File" << std::endl;
        std::cout << "2 - Choose algorithm with read data" << std::endl;
        std::cout << "3 - Tests" << std::endl;
        std::cout << "4 - Exit" << std::endl;
        std::cin >> gate;
        switch (gate) {
            case 1:
                graph = fileReader->readFromFile();
                break;
            case 2:
                displayAlgorithms(graph);
                break;
            case 3:

                break;
        }
    }
}


void Menu::displayAlgorithms(std::vector<std::vector<int>> graph) {
    std::cout << "=========================== Algorithms menu ===========================" << std::endl;
    int gate = 0;
    while (gate != 3) {
        std::cout << "Choose what do you want to do: " << std::endl;
        std::cout << "1 - Tabu Search" << std::endl;
        std::cout << "2 - Simulated annealing" << std::endl;
        std::cout << "3 - Exit" << std::endl;
        std::cin >> gate;
        switch (gate) {
            case 1:
                int neighbor;
                int timeLimit;
                std::cout << "Please enter the neighbor type: " << std::endl;
                std::cout << "1 - Swap " << std::endl;
                std::cout << "2 - Insert " << std::endl;
                std::cout << "3 - Inverse " << std::endl;
                std::cin >> neighbor;

                std::cout << "Neighbor accepted! " << std::endl;
                std::cout << "" << std::endl;
                std::cout << "" << std::endl;

                std::cout << "Please enter the s time limit: " << std::endl;
                std::cin >> timeLimit;
                timeLimit = timeLimit*1000;

                tabuSearchImplementation = new TabuSearchImplementation(graph,timeLimit,neighbor);
                tabuSearchImplementation->solve();
                break;
            case 2:
                int coolingScheme;

                std::cout << "Please enter the Cooling scheme: " << std::endl;
                std::cout << "1 - Geometrical  " << std::endl;
                std::cout << "2 - Linear " << std::endl;
                std::cout << "3 - Logarithmic " << std::endl;
                std::cin >> coolingScheme;

                std::cout << "Please enter the s time limit: " << std::endl;
                std::cin >> timeLimit;
                timeLimit = timeLimit*1000;

                simulatedAnnealing = new SimulatedAnnealing();
                std::vector<int> path = simulatedAnnealing->simulatedAnnealing(graph,10000,0.999,1,timeLimit);
                simulatedAnnealing->displayResult(path,graph);
                break;
        }
    }
}


void Menu::doTests(int num_cities, std::string file, int number_of_tests) {

    std::filesystem::path projectPath = std::filesystem::current_path();
    projectPath = projectPath.parent_path(); // Uzyskanie ścieżki do katalogu nadrzędnego
    std::string filePath = projectPath.string() + "\\PEA_2\\data\\" + file;
    std::cout << filePath;

    std::ofstream fileStream(filePath);

    long long int tabu = 0;
    long long int sa = 0;

    for(int i = 0; i < number_of_tests; i++){

    }

    if (fileStream.is_open()) {
        fileStream << "Tabu: \n";
        fileStream << tabu/number_of_tests << "\n";
        fileStream << "Sa: \n";
        fileStream << sa/number_of_tests << "\n";
    } else {
        std::cerr << "Error opening file: " << file << std::endl;
    }
    std::cout << "Test with num_cites: " << num_cities << " done!" << std::endl;
}




