//
// Created by Jakub on 04.12.2023.
//

#include <chrono>
#include <iostream>
#include <random>
#include "TabuSearchImplementation.h"
#include <random>
#include <filesystem>
#include <fstream>

TabuSearchImplementation::TabuSearchImplementation() {

}

std::string TabuSearchImplementation::solve(std::vector<std::vector<int>> matrix, long long int timeLimit,
                                     int neighborTypeOperation) {
    std::vector<int> currentPath, nextPath, savePath;
    std::vector<std::vector<int>> tabuMatrix(matrix.size(), std::vector<int>(matrix.size(), 0));
    int iterations = 10 * matrix.size();
    int nextCost, currentCost;
    auto millisActualTime = std::chrono::high_resolution_clock::now();
    auto lastSaveTime = std::chrono::high_resolution_clock::now();

    int resetTabuCounter = 0;
    const int resetTabuInterval = 100;  // Co ile iteracji resetować część macierzy tabu

    while (true) {
        currentPath = generateRandomPath(matrix);
        nextPath = currentPath;
        currentCost = calculatePathCost(currentPath,matrix);

        for (int a = 0; a < iterations; a++) {
            currentPath = nextPath;
            nextCost = currentCost;
            savePath = currentPath;

            for (size_t i = 1; i < matrix.size(); i++) {
                for (size_t j = i + 1; j < matrix.size(); j++) {
                    if (neighborTypeOperation == 1) {
                        swap(i, j, currentPath);
                    } else if (neighborTypeOperation == 2) {
                        insert(i, j, currentPath);
                    } else if (neighborTypeOperation == 3) {
                        makeReverse(i, j, currentPath);
                    }

                    currentCost = calculatePathCost(currentPath,matrix);

                    auto currentTime2 = std::chrono::high_resolution_clock::now();
                    auto timeSinceLastSave = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime2 - lastSaveTime).count();

                    if (timeSinceLastSave >= 20000) {
                        // Zapisz aktualny czas i najlepsze rozwiązanie do pliku
                        long long currentExecutionTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime2 - millisActualTime).count();
                        saveBestPathToFile("tabuSave.txt",currentCost);
                        lastSaveTime = currentTime2;
                    }

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

                    currentPath = savePath;
                }
            }

            for (size_t x = 0; x < matrix.size(); x++) {
                for (size_t y = 0; y < matrix.size(); y++) {
                    if (tabuMatrix[x][y] > 0) {
                        tabuMatrix[x][y]--;
                    }
                }
            }

            // Resetowanie macierzy tabu co określoną liczbę iteracji
            if (resetTabuCounter >= resetTabuInterval) {
                for (size_t x = 0; x < matrix.size(); x++) {
                    for (size_t y = 0; y < matrix.size(); y++) {
                        if (rand() % 2) {  // 50% szans na reset wartości tabu
                            tabuMatrix[x][y] = 0;
                        }
                    }
                }
                resetTabuCounter = 0;
            }
            resetTabuCounter++;



            auto currentTime = std::chrono::high_resolution_clock::now();
            executionTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - millisActualTime).count();
            if (executionTime > timeLimit) {
                std::cout << bestCost << "\n";
                for (int j : bestPath) {
                    std::cout << j << " ";
                }
                std::cout << "0\n";
                std::cout << "Najlepsze rozwiązanie znaleziono w: " << bestSolutionTime << " ms\n";
                std::string result =  std::to_string(bestCost) + ";" + std::to_string(bestSolutionTime);
                return result;
            }


        }
    }
}
void TabuSearchImplementation::swap(int i, int j, std::vector<int>& path) {
    int temp = path[i];
    path[i] = path[j];
    path[j] = temp;
}
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

std::vector<int> TabuSearchImplementation::generateRandomPath(std::vector<std::vector<int>>& matrix) {
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
int TabuSearchImplementation::calculatePathCost(const std::vector<int>& path, std::vector<std::vector<int>>& matrix) {
    int cost = 0;
    for (size_t i = 0; i < path.size() - 1; i++) {
        cost += matrix[path[i]][path[i + 1]];
    }
    cost += matrix[path.back()][path[0]];
    return cost;
}

// Funkcja testująca losowe ścieżki
void TabuSearchImplementation::random(std::vector<std::vector<int>>& matrix) {
    std::chrono::high_resolution_clock::time_point millisActualTime;
    millisActualTime = std::chrono::high_resolution_clock::now();
    std::vector<int> currentPath;
    int currentCost;
    while (true) {
        currentPath = generateRandomPath(matrix);
        currentCost = calculatePathCost(currentPath,matrix);
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

void TabuSearchImplementation::saveBestPathToFile(const std::string& fileName, int currentCost) {
    std::filesystem::path projectPath = std::filesystem::current_path();
    projectPath = projectPath.parent_path(); // Uzyskanie ścieżki do katalogu nadrzędnego
    std::string filePath = projectPath.string() + "\\PEA_2\\data\\" + fileName;
    std::cout << filePath;
    std::ofstream outFile(filePath, std::ios::app);

    if (outFile.is_open()) {
        outFile << bestCost << ";" << bestSolutionTime << "\n";
        outFile.close();
    } else {
        std::cerr << "Unable to open file: " << fileName << "\n";
    }
}

std::vector<int> TabuSearchImplementation::generateGreedyPath(std::vector<std::vector<int>>& matrix) {
    std::vector<int> path;
    std::vector<bool> visited(matrix.size(), false);

    int currentCity = 0; // starting city
    path.push_back(currentCity);
    visited[currentCity] = true;

    for (size_t i = 1; i < matrix.size(); ++i) {
        int closestCity = -1;
        int closestDistance = INT_MAX;

        for (size_t j = 0; j < matrix.size(); ++j) {
            if (!visited[j] && matrix[currentCity][j] < closestDistance) {
                closestDistance = matrix[currentCity][j];
                closestCity = j;
            }
        }

        path.push_back(closestCity);
        visited[closestCity] = true;
        currentCity = closestCity;
    }

    return path;
}