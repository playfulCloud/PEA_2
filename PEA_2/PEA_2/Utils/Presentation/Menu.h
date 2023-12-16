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


    void
    doTests2(std::vector<std::vector<int>> graph, std::string fileToWrite, int type, int timeLimit, double temperature,
             double coolingRate);



    void doAllGeometricTests(std::vector<std::vector<int>> graph, std::string fileToWrite, int type, int timeLimit);

    void doAllLinearTests(std::vector<std::vector<int>> graph, std::string fileToWrite, int type, int timeLimit,
                          double temperature);



    void doAllLogarythmicTests(std::vector<std::vector<int>> graph, std::string fileToWrite, int type, int timeLimit,
                               double temperature, int epochs);
};


#endif //PEA_1_MENU_H
