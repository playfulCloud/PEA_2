//
// Created by Jakub on 04.12.2023.
//

#include "SimulatedAnnealing.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <random>


int SimulatedAnnealing::calculateTotalCost(const std::vector<int>& path, const std::vector<std::vector<int>>& costMatrix) {
    int totalCost = 0;
    for (size_t i = 0; i < path.size() - 1; ++i) {
        totalCost += costMatrix[path[i]][path[i + 1]];
    }
    // Adding the cost of returning to the starting city
    totalCost += costMatrix[path.back()][path.front()];
    return totalCost;
}

// Funkcja generująca nową ścieżkę poprzez zamianę dwóch losowych miast
std::vector<int> SimulatedAnnealing::generateNewPath(std::vector<int> currentPath) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution<> dist(0, currentPath.size() - 1);

    int index1 = dist(g);
    int index2 = dist(g);
    while (index1 == index2) {
        index2 = dist(g);
    }

    std::reverse(currentPath.begin() + std::min(index1, index2), currentPath.begin() + std::max(index1, index2) + 1);
    return currentPath;
}

// Główna funkcja symulowanego wyżarzania
std::vector<int> SimulatedAnnealing::simulatedAnnealing(const std::vector<std::vector<int>>& costMatrix, double temperature, double coolingRate,int coolingScheme, int maxDuration) {
    std::random_device rd;
    std::mt19937 g(rd());
    int numCities = costMatrix.size();

    // Inicjalizacja początkowej ścieżki
    std::vector<int> currentPath(numCities);
    for (int i = 0; i < numCities; ++i) {
        currentPath[i] = i;
    }
    std::shuffle(currentPath.begin(), currentPath.end(), g);

    std::vector<int> bestPath = currentPath;
    int bestCost = calculateTotalCost(currentPath, costMatrix);

    int iteration = 0; // Dla schematu logarytmicznego
    double linearStep = 5; // Wartość zm

    auto startTime = std::chrono::high_resolution_clock::now();

    while (temperature > 0.5) {
        std::vector<int> newPath = generateNewPath(currentPath);
        int currentCost = calculateTotalCost(currentPath, costMatrix);
        int newCost = calculateTotalCost(newPath, costMatrix);

        auto currentTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds >(currentTime - startTime).count();

        if (duration > maxDuration) {
            std::cout << "Maksymalny czas wykonania przekroczony. Przerywanie..." << std::endl;
            break;
        }

        // Akceptacja nowej ścieżki
        if (newCost < currentCost || (exp((currentCost - newCost) / temperature) > ((double)rand() / RAND_MAX))) {
            currentPath = newPath;
        }

        if (newCost < bestCost) {
            bestPath = newPath;
            bestCost = newCost;
        }

        switch (coolingScheme) {
            case 1: // Geometryczne
                temperature *= coolingRate;
                break;
            case 2: // Liniowe
                temperature -= temperature *coolingRate;
                break;
            case 3: // Logarytmiczne
                temperature = temperature / ( log(2 + iteration));
                iteration++;
                break;
            default:
                // Domyślnie użyjemy schładzania geometrycznego
                temperature *= coolingRate;
        };
    }
    auto endTime = std::chrono::high_resolution_clock::now();
    auto totalDuration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
//    std::cout << "Całkowity czas wykonania: " << totalDuration << " ms" << std::endl;

    displayFinalTemperatureInfo(temperature);
    return bestPath;
}

void SimulatedAnnealing::displayResult(std::vector<int> bestPath, std::vector<std::vector<int>>costMatrix) {
//    double temperature = 10000;
//    double coolingRate = 0.999;


    std::cout << "Best path: ";
    for (int city : bestPath) {
        std::cout << city << " ";
    }
    std::cout << bestPath[0];
    std::cout << "\nprice: " << calculateTotalCost(bestPath, costMatrix) << std::endl;

}

void SimulatedAnnealing::displayFinalTemperatureInfo(double temperature) {
    std::cout << "Final Temperature (Tk): " << temperature << std::endl;
    std::cout << "Value of exp(-1/Tk): " << std::exp(-1 / temperature) << std::endl;
}

std::string SimulatedAnnealing::resultForTest(int totalDuration,std::vector<int> bestPath, std::vector<std::vector<int>>costMatrix ){
   std::string result =  std::to_string(calculateTotalCost(bestPath,costMatrix)) + ";" + std::to_string(totalDuration)  ;
    return result;
}

// Główna funkcja symulowanego wyżarzania
std::string SimulatedAnnealing::simulatedAnnealing2(const std::vector<std::vector<int>>& costMatrix, double temperature, double coolingRate,int coolingScheme, int maxDuration) {
    srand(time(nullptr));
    int numCities = costMatrix.size();

    // Inicjalizacja początkowej ścieżki
    std::vector<int> currentPath(numCities);
    for (int i = 0; i < numCities; ++i) {
        currentPath[i] = i;
    }
    std::random_shuffle(currentPath.begin(), currentPath.end());

    std::vector<int> bestPath = currentPath;
    int bestCost = calculateTotalCost(currentPath, costMatrix);

    int iteration = 0; // Dla schematu logarytmicznego
    double linearStep = 0.001488888;

    auto startTime = std::chrono::high_resolution_clock::now();

    while (temperature > 0.5 ) {
        std::vector<int> newPath = generateNewPath(currentPath);
        int currentCost = calculateTotalCost(currentPath, costMatrix);
        int newCost = calculateTotalCost(newPath, costMatrix);

        auto currentTime = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds >(currentTime - startTime).count();

        if (duration > maxDuration) {
            std::cout << "Maksymalny czas wykonania przekroczony. Przerywanie..." << std::endl;
            break;
        }

        // Akceptacja nowej ścieżki
        if (newCost < currentCost || (exp((currentCost - newCost) / temperature) > ((double)rand() / RAND_MAX))) {
            currentPath = newPath;
        }

        if (newCost < bestCost) {
            bestPath = newPath;
            bestCost = newCost;
        }

        switch (coolingScheme) {
            case 1: // Geometryczne
                temperature *= coolingRate;
                break;
            case 2: // Liniowe

                temperature -= linearStep;
                break;
            case 3: // Logarytmiczne
                temperature = temperature / ( log(2 + iteration));
                iteration++;
                break;
            default:
                // Domyślnie użyjemy schładzania geometrycznego
                temperature *= coolingRate;
        };
    }
    auto endTime = std::chrono::high_resolution_clock::now();
    auto totalDuration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
//    std::cout << "Całkowity czas wykonania: " << totalDuration << " ms" << std::endl;

    displayFinalTemperatureInfo(temperature);
    return resultForTest(totalDuration,bestPath,costMatrix);
}



