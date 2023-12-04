//
// Created by Jakub on 27.10.2023.
//

#ifndef PEA_1_BRUTEFORCE_IMPLEMENTATION_H
#define PEA_1_BRUTEFORCE_IMPLEMENTATION_H


#include <chrono>
#include "../../Utils/CityMatrix/Matrix.h"

class BruteForce_Implementation {
public:
    BruteForce_Implementation(Matrix matrix);
    int routeLength(int** graph, int* route, int n);
    int min_route_length;
    int* best_route;
    int tsp(int** graph, int n);
    bool nextPermutation(int* route, int n);
    void copy(int *source, int *source_end, int *destination);
    void reverse(int* arr, int start, int end);
    void swap(int& a, int& b);
//    std::chrono::high_resolution_clock::time_point start;
//    std::chrono::high_resolution_clock::time_point stop;
    Matrix matrix;

    void solution(int **graph, int n);
};


#endif //PEA_1_BRUTEFORCE_IMPLEMENTATION_H
