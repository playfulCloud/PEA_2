#include "DynamicProgramming_implementation.h"
#include <algorithm>
#include <iostream>
#include <valarray>
#include <chrono>


DynamicProgramming_implementation::DynamicProgramming_implementation(int **dist, int n) {
    size = n;
    visited_all_mask = (1 << n) - 1;
    for (int i = 0; i < size; i++) {
        std::vector<int> row;
        for (int j = 0; j < size; j++) {
            row.push_back(dist[i][j]);
        }
        matrix.push_back(row);
    }
    costs.resize(pow(2, size));
    paths.resize(pow(2, size));
    for (int i = 0; i < costs.size(); i++) {
        paths[i].resize(size);
        for (int j = 0; j < size; j++) {
            costs[i].push_back(-1);
        }
    }
}

int DynamicProgramming_implementation::solution(int **dist) {
    long long int time = 0;
    start = std::chrono::high_resolution_clock::now();
    int result_path_sum = this->tsp(1, 0, dist);
    stop = std::chrono::high_resolution_clock::now();
    time += std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();

//    std::cout << "Minimum cost: " << result_path_sum << std::endl;
//    std::vector<int> result_path = paths[1][0];
//    std::reverse(result_path.begin(), result_path.end());
//
//    std::cout << "Path taken: ";
//    for (int i = 0; i < size; i++) {
//        std::cout << "->" << result_path[i] << ' ';
//    }
//    std::cout << "-> 0" << std::endl;
//    std::cout << "time: " << time << "ns" << std::endl;

    return time;

    matrix.clear();
    paths.clear();
    costs.clear();
}

int DynamicProgramming_implementation::tsp(int mask, int pos, int **dist) {
    if (mask == visited_all_mask) {
        paths[mask][pos].push_back(pos);
        return dist[pos][0];
    }
    if (costs[mask][pos] != -1) {
        return costs[mask][pos];
    }

    int result = INT_MAX;
    int next_pos = -1;
    for (int i = 0; i < matrix.size(); i++) {
        if ((mask & (1 << i)) == 0) {
            int possible_result = dist[pos][i] + tsp(mask | (1 << i), i,
                                                     dist);
            if (possible_result < result) {
                result = possible_result;
                next_pos = i;
            }
        }
    }

    if (next_pos != -1) {
        paths[mask][pos] = paths[mask | (1 << next_pos)][next_pos];
        paths[mask][pos].push_back(pos);
    }
    costs[mask][pos] = result;
    return result;
}
