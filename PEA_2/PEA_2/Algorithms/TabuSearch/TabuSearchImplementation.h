//
// Created by Jakub on 04.12.2023.
//

#ifndef PEA_2_TABUSEARCHIMPLEMENTATION_H
#define PEA_2_TABUSEARCHIMPLEMENTATION_H


#include <vector>

class TabuSearchImplementation {
public:
    TabuSearchImplementation();

    TabuSearchImplementation(std::vector<std::vector<int>> matrix, long long int timeLimit, int neighborTypeOperation);

    long millisActualTime;
    long executionTime;
    long bestSolutionTime;
    std::vector<std::vector<int>> matrix;
    std::vector<int> bestPath;
    int bestCost = INT_MAX;
    long long int timeLimit;
    int neighborTypeOperation;

    void makeReverse(int i, int j, std::vector<int> &path);

    void swap(int i, int j, std::vector<int> &path);

    void insert(int i, int j, std::vector<int> &path);

    void insertv2(int i, int j, std::vector<int> &path);


   std::string solve(std::vector<std::vector<int>> matrix, long long int timeLimit, int neighborTypeOperation);

    std::vector<int> generateRandomPath(std::vector<std::vector<int>> &matrix);

    int calculatePathCost(const std::vector<int> &path, std::vector<std::vector<int>> &matrix);

    void random(std::vector<std::vector<int>> &matrix);

    void saveBestPathToFile(const std::string &filename,int currentCost);

    std::vector<int> generateGreedyPath(std::vector<std::vector<int>> &matrix);
};


#endif //PEA_2_TABUSEARCHIMPLEMENTATION_H
