//
// Created by Jakub on 27.10.2023.
//

#ifndef PEA_1_MENU_H
#define PEA_1_MENU_H



#include "../Reader/FileReader.h"
#include "../../Algorithms/TabuSearch/TabuSearchImplementation.h"
#include "../../Algorithms/SimulatedAnnealing/SimulatedAnnealing.h"


class Menu {
public:
    Menu();
    void displayMenu();
    void displayAlgorithms(std::vector<std::vector<int>> graph);
    FileReader *fileReader;
    TabuSearchImplementation *tabuSearchImplementation;
    SimulatedAnnealing *simulatedAnnealing;
    std::vector<std::vector<int>> graph;
    void doTests(int num_cities, std::string file, int number_of_tests);
};


#endif //PEA_1_MENU_H
