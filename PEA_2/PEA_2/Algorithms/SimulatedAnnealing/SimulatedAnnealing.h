//
// Created by Jakub on 04.12.2023.
//

#ifndef PEA_2_SIMULATEDANNEALING_H
#define PEA_2_SIMULATEDANNEALING_H


#include <vector>
#include <string>

class SimulatedAnnealing {



public:

    std::vector<int> initializeTour(int n);



    void displaySolution(const std::vector<int> &tour, const std::vector<std::vector<int>> &cities);



    int calculatePathCost(const std::vector<int> &path, std::vector<std::vector<int>> matrix);

    std::vector<int>
    simulatedAnnealing(const std::vector<std::vector<int>> &cities, double initialTemperature, double coolingRate,
                       int epochs, int coolingScheme, int timeLimit);


    void
    savePathToFile(const std::vector<int> &path, double pathCost, long long int executionTime,
                   const std::string &fileName,
                   int coolingScheme);

    std::string
    simulatedAnnealingForTesting(const std::vector<std::vector<int>> &cities, double initialTemperature,
                                 double coolingRate,
                                 int epochs, int coolingScheme, int timeLimit);

    long long int
    writeCurrentBestSolutionAndTimeToFile(const std::vector<std::vector<int>> &cities, const std::vector<int> &path,
                                          long long int executionTime, const std::string &fileName, int timeLimit,
                                          int coolingScheme, int epochs);


};


#endif //PEA_2_SIMULATEDANNEALING_H
