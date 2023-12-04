//
// Created by Jakub on 27.10.2023.
//

#ifndef PEA_1_DYNAMICPROGRAMMING_IMPLEMENTATION_H
#define PEA_1_DYNAMICPROGRAMMING_IMPLEMENTATION_H

#define INF INT_MAX

#include <vector>
#include <chrono>
#include "../../Utils/CityMatrix/Matrix.h"

class DynamicProgramming_implementation {
public:
    DynamicProgramming_implementation(int **dist, int n);
    int result;
    int size;
    std::vector<std::vector<int>> matrix;
    std::vector<std::vector<std::vector<int>>> paths;
    std::vector<std::vector<int>> costs;
    int visited_all_mask;
    int tsp(int mask, int vertex, int **dist);
    int solution(int **dist);
    std::chrono::high_resolution_clock::time_point start;
    std::chrono::high_resolution_clock::time_point stop;
};


#endif //PEA_1_DYNAMICPROGRAMMING_IMPLEMENTATION_H
