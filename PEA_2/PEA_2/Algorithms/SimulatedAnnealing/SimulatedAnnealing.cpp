#include <vector>
#include <iostream>
#include <cmath>
#include <random>
#include <algorithm>
#include <chrono>
#include "SimulatedAnnealing.h"
#include <fstream>
#include <filesystem>


int SimulatedAnnealing::calculatePathCost(const std::vector<int> &path, std::vector<std::vector<int>> matrix) {
    int cost = 0;
    for (size_t i = 0; i < path.size() - 1; i++) {
        cost += matrix[path[i]][path[i + 1]];
    }
    cost += matrix[path.back()][path[0]];
    return cost;
}

std::vector<int> SimulatedAnnealing::initializeTour(int n) {
    std::vector<int> tour(n);
    for (int i = 0; i < n; ++i) {
        tour[i] = i;
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(tour.begin() + 1, tour.end(), g);
    return tour;
}

std::vector<int>
SimulatedAnnealing::simulatedAnnealing(const std::vector<std::vector<int>> &cities, double initialTemperature,
                                       double coolingRate, int epochs, int coolingScheme, int timeLimit) {
    if (cities.empty()) {
        throw std::invalid_argument("Cities vector cannot be empty.");
    }

    int n = cities.size();
    std::vector<int> currentTour = initializeTour(n);
    std::vector<int> bestTour = currentTour;

    double currentLength = calculatePathCost(currentTour, cities);
    double bestLength = currentLength;
    double temperature = initialTemperature;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, n - 1);
    auto startTime = std::chrono::high_resolution_clock::now();
    int epochCounter = 0;
    while (temperature > 0.5) {

        for (int epoch = 0; epoch < epochs; ++epoch) {
            std::vector<int> newTour = currentTour;
            int pos1 = dis(gen);
            int pos2 = dis(gen);
            std::swap(newTour[pos1], newTour[pos2]);

            double newLength = calculatePathCost(newTour, cities);
            double deltaLength = newLength - currentLength;

            if (deltaLength < 0 || (std::generate_canonical<double, 10>(gen)) < std::exp(-deltaLength / temperature)) {
                currentTour = newTour;
                currentLength = newLength;

                if (currentLength < bestLength) {
                    bestTour = currentTour;
                    bestLength = currentLength;
                }
            }


        }
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto workTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();
        if (workTime > timeLimit) {
            std::cout << "Pogram zostal zakonczony przed czasem! " << std::endl;
            auto endTime = std::chrono::high_resolution_clock::now();
            auto executionTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
            std::cout << "Execution time: " << executionTime << std::endl;
            displaySolution(bestTour, cities);
            savePathToFile(bestTour, calculatePathCost(bestTour, cities), executionTime, "sciezki.txt", coolingScheme);
            return bestTour;
        }
        double linearStep = 0.40;

        switch (coolingScheme) {
            case 1:
                temperature *= coolingRate;
                break;
            case 2:
                temperature -= linearStep;
                break;
            case 3:
//                temperature = initialTemperature * exp(-coolingRate * epochCounter);
                temperature = initialTemperature / log(1 + epochCounter); // L
                epochCounter += 1;
//                std::cout << "pokaz: " << temperature << "epoki " <<  epochCounter <<std::endl;

                break;
            default:
                temperature *= coolingRate;
        }

    }
    auto endTime = std::chrono::high_resolution_clock::now();
    auto executionTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    std::cout << "Execution time: " << executionTime << std::endl;
    displaySolution(bestTour, cities);
    savePathToFile(bestTour, calculatePathCost(bestTour, cities), executionTime, "sciezki.txt", coolingScheme);
    return bestTour;
}

void SimulatedAnnealing::displaySolution(const std::vector<int> &tour, const std::vector<std::vector<int>> &cities) {
    std::cout << "Trasa: ";
    for (int city: tour) {
        std::cout << city << " ";
    }
    std::cout << std::endl;

    std::cout << "Długość trasy: " << calculatePathCost(tour, cities) << std::endl;
}


void SimulatedAnnealing::savePathToFile(const std::vector<int> &path, double pathCost, long long executionTime,
                                        const std::string &fileName, int coolingScheme) {
    std::filesystem::path projectPath = std::filesystem::current_path();
    projectPath = projectPath.parent_path(); // Uzyskanie ścieżki do katalogu nadrzędnego
    std::string filePath = projectPath.string() + "\\PEA_2\\data\\" + fileName;
    std::cout << filePath;
    std::ofstream file(filePath, std::ios::app);

    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file: " + fileName);
    }
    switch (coolingScheme) {
        case 1:
            file << "Cooling Scheme: ";
            file << "Geometrical";
            break;
        case 2:
            file << "Cooling Scheme: ";
            file << "Linear";
            break;
        case 3:
            file << "Cooling Scheme: ";
            file << "Logarythmical";
            break;

    }

    file << "\n";
    file << "Ścieżka:\n";
    for (int city: path) {
        file << city << " ";
    }
    file << path[0];
    file << "\nDługość ścieżki: " << pathCost << "\nCzas wykonania: " << executionTime << " ms\n";
    file.close();
}

std::string
SimulatedAnnealing::simulatedAnnealingForTesting(const std::vector<std::vector<int>> &cities, double initialTemperature,
                                                 double coolingRate, int epochs, int coolingScheme, int timeLimit) {
    if (cities.empty()) {
        throw std::invalid_argument("Cities vector cannot be empty.");
    }

    int n = cities.size();
    std::vector<int> currentTour = initializeTour(n);
    std::vector<int> bestTour = currentTour;

    double currentLength = calculatePathCost(currentTour, cities);
    double bestLength = currentLength;
    double temperature = initialTemperature;
    long long timeToSubtract = 0;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, n - 1);
    auto startTime = std::chrono::high_resolution_clock::now();
    int epochCounter = 0;
    while (temperature > 0.5) {
        for (int epoch = 0; epoch < epochs; ++epoch) {
            std::vector<int> newTour = currentTour;
            int pos1 = dis(gen);
            int pos2 = dis(gen);
            std::swap(newTour[pos1], newTour[pos2]);

            double newLength = calculatePathCost(newTour, cities);
            double deltaLength = newLength - currentLength;

            if (deltaLength < 0 || (std::generate_canonical<double, 10>(gen)) < std::exp(-deltaLength / temperature)) {
                currentTour = newTour;
                currentLength = newLength;

                if (currentLength < bestLength) {
                    bestTour = currentTour;
                    bestLength = currentLength;
                }
            }


        }
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto workTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();
//        if(epochCounter % 100 == 0){
//            timeToSubtract += writeCurrentBestSolutionAndTimeToFile(cities,bestTour,workTime,"bestTime.txt",timeLimit,coolingScheme,epochs);
//        }
        if (workTime > timeLimit+timeToSubtract) {
            std::cout << "Pogram zostal zakonczony przed czasem! " << std::endl;
            auto endTime = std::chrono::high_resolution_clock::now();
            auto executionTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
            std::cout << "Execution time: " << executionTime << std::endl;
            int result = calculatePathCost(bestTour, cities);
            displaySolution(bestTour, cities);
            savePathToFile(bestTour, result, executionTime, "sciezki.txt", coolingScheme);
            std::string finalResult;
            finalResult.append(std::to_string(result));
            finalResult.append(";");
            finalResult.append(std::to_string(executionTime));
            return finalResult;
        }
        double linearStep = 0.2;
//        if(timeLimit == 3600000){
//            linearStep = 0.32;
//        }

        switch (coolingScheme) {
            case 1:
                temperature *= coolingRate;
                break;
            case 2:
                temperature -= linearStep;
                break;
            case 3:
//                temperature = initialTemperature * exp(-coolingRate * epochCounter);
                temperature = initialTemperature / log(1 + epochCounter); // L
                epochCounter += 1;
//                std::cout << "pokaz: " << temperature << "epoki " <<  epochCounter <<std::endl;

                break;
            default:
                temperature *= coolingRate;
        }

    }
    auto endTime = std::chrono::high_resolution_clock::now();
    auto executionTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
    std::cout << "Execution time: " << executionTime << std::endl;
    displaySolution(bestTour, cities);
    savePathToFile(bestTour, calculatePathCost(bestTour, cities), executionTime, "sciezki.txt", coolingScheme);
    int result = calculatePathCost(bestTour, cities);
    std::string finalResult;
    finalResult.append(std::to_string(result));
    finalResult.append(";");
    finalResult.append(std::to_string(executionTime));
    return finalResult;
}

long long SimulatedAnnealing::writeCurrentBestSolutionAndTimeToFile(const std::vector<std::vector<int>> &cities,const std::vector<int> &path,
                                                               long long int executionTime,
                                                               const std::string &fileName, int timeLimit, int coolingScheme, int epochs) {

    auto startTime = std::chrono::high_resolution_clock::now();
    std::filesystem::path projectPath = std::filesystem::current_path();
    projectPath = projectPath.parent_path(); // Uzyskanie ścieżki do katalogu nadrzędnego
    std::string filePath = projectPath.string() + "\\PEA_2\\data\\" + fileName;
    std::cout << filePath;
    std::ofstream file(filePath, std::ios::app);

    int pathValue = calculatePathCost(path,cities);

    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file: " + fileName);
    }

    if(epochs == 0){
        switch (coolingScheme) {
            case 1:
                file << "Cooling Scheme: ";
                file << "Geometrical";
                file << "\n";
                file << "Time Limit: ";
                file << timeLimit;
                file << "\n";
                break;
            case 2:
                file << "Cooling Scheme: ";
                file << "Linear";
                file << "\n";
                file << "Time Limit: ";
                file << timeLimit;
                file << "\n";
                break;
            case 3:
                file << "Cooling Scheme: ";
                file << "Logarythmical";
                file << "\n";
                file << "Time Limit: ";
                file << timeLimit;
                file << "\n";
                break;

        }

    }

    file << pathValue;
    file << ";";
    file << executionTime;


    file.close();
    auto endTime = std::chrono::high_resolution_clock::now();
    auto workTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

    return workTime;
}
