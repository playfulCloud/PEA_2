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
                std::vector<std::vector<int>> graph = fileReader->readFromFile2("ftv55.atsp");

//
//                graph = fileReader->readFromFile2("ftv170.atsp");
//
//                doAllLogarythmicTests(graph,"sa2_3.txt",3,240000,80,500);


                graph = fileReader->readFromFile2("rbg358.atsp");

//                doAllGeometricTests(graph,"sa3_1.txt",1,360000);
                doAllLinearTests(graph,"sa3_2.txt",2,360000,50);
                doAllLogarythmicTests(graph,"sa3_3.txt",3,360000,10,500);



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

                tabuSearchImplementation = new TabuSearchImplementation();
                tabuSearchImplementation->solve(graph,timeLimit,neighbor);
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
                std::vector<int> path = simulatedAnnealing->simulatedAnnealing(graph,10,0.99,500 ,coolingScheme,timeLimit);
//                simulatedAnnealing->displaySolution(path,graph);
                break;
        }
    }
}


//void Menu::doTests1(std::vector<std::vector<int>> graph,std::string fileToWrite, int type, int timeLimit) {
//    std::filesystem::path projectPath = std::filesystem::current_path();
//    projectPath = projectPath.parent_path(); // Uzyskanie ścieżki do katalogu nadrzędnego
//    std::string filePath = projectPath.string() + "\\PEA_2\\data\\" + fileToWrite;
//    std::cout << filePath;
//    std::ofstream fileStream(filePath);
//
//    for (int i = 0; i < 10; i++) {
//        if (fileStream.is_open()) {
//            tabuSearchImplementation = new TabuSearchImplementation();
//            std::string answer = tabuSearchImplementation->solve(graph, timeLimit*1000, type);
//            fileStream << answer + "\n";
//            std::cout << "skonczony" << std::endl;
//        } else {
//            std::cerr << "Error opening file: " << fileToWrite << std::endl;
//        }
//    }
//}


void Menu::doAllGeometricTests(std::vector<std::vector<int>> graph,std::string fileToWrite, int type, int timeLimit) {
    std::filesystem::path projectPath = std::filesystem::current_path();
    projectPath = projectPath.parent_path(); // Uzyskanie ścieżki do katalogu nadrzędnego
    std::string filePath = projectPath.string() + "\\PEA_2\\data\\" + fileToWrite;
    std::cout << filePath;
    std::ofstream fileStream(filePath);

    for (int i = 0; i < 10; i++) {
        if (fileStream.is_open()) {
            simulatedAnnealing = new SimulatedAnnealing();
            std::string answer = simulatedAnnealing->simulatedAnnealingForTesting(graph,80,0.99,1000 ,type,timeLimit);
            fileStream << answer + "\n";
            std::cout << "skonczony" << std::endl;
            delete simulatedAnnealing;
        } else {
            std::cerr << "Error opening file: " << fileToWrite << std::endl;
        }
    }
}

void Menu::doAllLinearTests(std::vector<std::vector<int>> graph,std::string fileToWrite, int type, int timeLimit,double temperature) {
    std::filesystem::path projectPath = std::filesystem::current_path();
    projectPath = projectPath.parent_path(); // Uzyskanie ścieżki do katalogu nadrzędnego
    std::string filePath = projectPath.string() + "\\PEA_2\\data\\" + fileToWrite;
    std::cout << filePath;
    std::ofstream fileStream(filePath);

    for (int i = 0; i < 10; i++) {
        if (fileStream.is_open()) {
            simulatedAnnealing = new SimulatedAnnealing();
            std::string answer = simulatedAnnealing->simulatedAnnealingForTesting(graph,temperature,0.99,9000 ,type,timeLimit);
            fileStream << answer + "\n";
            std::cout << "skonczony" << std::endl;
            delete simulatedAnnealing;
        } else {
            std::cerr << "Error opening file: " << fileToWrite << std::endl;
        }
    }
}

void Menu::doAllLogarythmicTests(std::vector<std::vector<int>> graph,std::string fileToWrite, int type, int timeLimit,double temperature, int epochs) {
    std::filesystem::path projectPath = std::filesystem::current_path();
    projectPath = projectPath.parent_path(); // Uzyskanie ścieżki do katalogu nadrzędnego
    std::string filePath = projectPath.string() + "\\PEA_2\\data\\" + fileToWrite;
    std::cout << filePath;
    std::ofstream fileStream(filePath);

    for (int i = 0; i < 10; i++) {
        if (fileStream.is_open()) {
            simulatedAnnealing = new SimulatedAnnealing();
            std::string answer = simulatedAnnealing->simulatedAnnealingForTesting(graph,temperature,0.99,epochs ,type,timeLimit);
            fileStream << answer + "\n";
            std::cout << "skonczony" << std::endl;
            delete simulatedAnnealing;
        } else {
            std::cerr << "Error opening file: " << fileToWrite << std::endl;
        }
    }
}




