//
// Created by Jakub on 04.12.2023.
//

#ifndef PEA_2_SIMULATEDANNEALING_H
#define PEA_2_SIMULATEDANNEALING_H


#include <vector>
#include <string>

class SimulatedAnnealing {

    int calculateTotalCost(const std::vector<int> &path, const std::vector<std::vector<int>> &costMatrix);

    std::vector<int> generateNewPath(std::vector<int> currentPath);

public:
    std::vector<int>
    simulatedAnnealing(const std::vector<std::vector<int>> &costMatrix, double temperature, double coolingRate,
                       int coolingScheme);

    void displayResult(std::vector<int> bestPath, std::vector<std::vector<int>> costMatrix);

    void displayFinalTemperatureInfo(double temperature);

    std::vector<int>
    simulatedAnnealing(const std::vector<std::vector<int>> &costMatrix, double temperature, double coolingRate,
                       int coolingScheme, int maxDuration);

    std::__cxx11::basic_string<char>
    resultForTest(int totalDuration, std::vector<int> bestPath, std::vector<std::vector<int>> costMatrix);

    std::string
    simulatedAnnealing2(const std::vector<std::vector<int>> &costMatrix, double temperature, double coolingRate,
                        int coolingScheme, int maxDuration);


    std::vector<int> generateNeighbor(const std::vector<int> &currentPath);


    std::vector<int> simulatedAnnealing3(const std::vector<std::vector<int>> &distances);

    double calculateCost2(const std::vector<std::vector<int>> &distances, const std::vector<int> &path);
};


#endif //PEA_2_SIMULATEDANNEALING_H
