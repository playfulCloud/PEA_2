//
// Created by Jakub on 04.12.2023.
//

#include <chrono>
#include <iostream>
#include <random>
#include "TabuSearchImplementation.h"
#include <random>

TabuSearchImplementation::TabuSearchImplementation(std::vector<std::vector<int>> matrix, long long int timeLimit,
                                                   int neighborTypeOperation) {
    this->matrix = matrix;
    this->timeLimit = timeLimit;
    this->neighborTypeOperation = neighborTypeOperation;
}

void TabuSearchImplementation::solve() {
    std::vector<int> currentPath;
    std::vector<int> nextPath;
    std::vector<std::vector<int>> tabuMatrix(matrix.size(), std::vector<int>(matrix.size(), 0));
    int iterations = 10 * matrix.size(); // liczba iteracji to 10 krotność liczby miast
    int nextCost;
    int currentCost;
    std::vector<int> savePath;
    bestCost = INT_MAX;
    auto millisActualTime = std::chrono::high_resolution_clock::now();

    while (true) {
        currentPath = generateRandomPath();
        nextPath = currentPath;
        currentCost = calculatePathCost(currentPath);
        for (int a = 0; a < iterations; a++) {
            currentPath = nextPath; // kopiowanie wektorów
            nextCost = currentCost;
            savePath = currentPath; // zachowanie ścieżki
            for (size_t i = 1; i < matrix.size(); i++) {
                for (size_t j = i + 1; j < matrix.size(); j++) {
                    if (neighborTypeOperation == 1) {
                        swap(i, j, currentPath);
                    } else if (neighborTypeOperation == 2) {
                        insertv2(i, j, currentPath);
                    } else if (neighborTypeOperation == 3) {
                        makeReverse(i, j, currentPath);
                    }
                    currentCost = calculatePathCost(currentPath);

                    if (currentCost < bestCost) {
                        bestPath = currentPath;
                        bestCost = currentCost;
                        bestSolutionTime = std::chrono::duration_cast<std::chrono::milliseconds>(
                                std::chrono::high_resolution_clock::now() - millisActualTime).count();
                        if (tabuMatrix[i][j] == 0) {
                            nextCost = currentCost;
                            nextPath = currentPath;
                        }
                    }
                    if (currentCost < nextCost && tabuMatrix[i][j] < a) {
                        nextCost = currentCost;
                        nextPath = currentPath;
                        tabuMatrix[i][j] += matrix.size();
                    }
                    currentPath = savePath; // przywrócenie ścieżki
                }
            }

            for (size_t x = 0; x < matrix.size(); x++) {
                for (size_t y = 0; y < matrix.size(); y++) {
                    if (tabuMatrix[x][y] > 0) {
                        tabuMatrix[x][y]--;
                    }
                }
            }

            auto currentTime =  std::chrono::high_resolution_clock::now();
            executionTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - millisActualTime).count();
            if (executionTime > timeLimit) {
                std::cout << bestCost << "\n";
                for (int j : bestPath) {
                    std::cout << j << " ";
                }
                std::cout << "0\n";
                std::cout << "Najlepsze rozwiązanie znaleziono w: " << bestSolutionTime << " ms\n";
                return;
            }
        }
    }
}
void TabuSearchImplementation::swap(int i, int j, std::vector<int>& path) {
    int temp = path[i];
    path[i] = path[j];
    path[j] = temp;
}

// Przykładowa implementacja metody makeReverse
void  TabuSearchImplementation::makeReverse(int i, int j, std::vector<int>& path) {
    while (i < j) {
        int temp = path[i];
        path[i] = path[j];
        path[j] = temp;
        i++;
        j--;
    }
}

// Przykładowa implementacja metody insert (jeśli jest błędna, to zależnie od zamierzonej poprawki)
void TabuSearchImplementation::insert(int i, int j, std::vector<int>& path) {
    int temp = path[i];
    path[i] = path[j];
    for (int k = i; k < j; ++k) {
        path[k] = path[k + 1];
    }
    path[j] = temp;
}


void TabuSearchImplementation::insertv2(int i, int j, std::vector<int>& path) {
    std::vector<int> tempTab(path.size());
    int x;
    for (x = 0; x < i; x++) {
        tempTab[x] = path[x];
    }
    tempTab[i] = path[j];
    for (x = i + 1; x <= j; x++) {
        tempTab[x] = path[x - 1];
    }
    for (; x < path.size(); x++) {
        tempTab[x] = path[x];
    }
    path = tempTab; // kopiowanie wektora
}

std::vector<int> TabuSearchImplementation::generateRandomPath() {
    std::vector<int> randomPath(matrix.size());
    for (size_t i = 0; i < matrix.size(); i++) {
        randomPath[i] = i;
    }
    std::mt19937 rand(std::random_device{}());
    for (size_t i = 1; i < randomPath.size(); i++) {
        std::uniform_int_distribution<int> dist(1, randomPath.size() - 1);
        int randomIndexToSwap = dist(rand);
        std::swap(randomPath[i], randomPath[randomIndexToSwap]);
    }
    return randomPath;
}

// Funkcja obliczająca koszt ścieżki
int TabuSearchImplementation::calculatePathCost(const std::vector<int>& path) {
    int cost = 0;
    for (size_t i = 0; i < path.size() - 1; i++) {
        cost += matrix[path[i]][path[i + 1]];
    }
    cost += matrix[path.back()][path[0]];
    return cost;
}

// Funkcja testująca losowe ścieżki
void TabuSearchImplementation::random() {
    std::chrono::high_resolution_clock::time_point millisActualTime;
    millisActualTime = std::chrono::high_resolution_clock::now();
    std::vector<int> currentPath;
    int currentCost;
    while (true) {
        currentPath = generateRandomPath();
        currentCost = calculatePathCost(currentPath);
        if (currentCost < bestCost) {
            bestPath = currentPath;
            bestCost = currentCost;
        }
        auto currentTime = std::chrono::high_resolution_clock::now();
        executionTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - millisActualTime).count();
        if (executionTime > timeLimit) {
            std::cout << bestCost << "\n";
            for (int j : bestPath) {
                std::cout << j << " ";
            }
            std::cout << "0\n";
            std::cout << "Najlepsze rozwiązanie znaleziono w: " << bestSolutionTime << " ms\n";
            return;
        }
    }
}
