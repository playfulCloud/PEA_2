//
// Created by Jakub on 27.10.2023.
//

#include <cstdio>
#include <iostream>
#include <chrono>
#include "BranchAndBound_Implementation.h"

void BranchAndBound_Implementation::copyToFinal(int *curr_path) {
    for (int i = 0; i < N; i++)
        final_path[i] = curr_path[i];
    final_path[N] = curr_path[0];
}

int BranchAndBound_Implementation::firstMin(int **adj, int i) {
    int min = INT_MAX;
    for (int k = 0; k < N; k++)
        if (adj[i][k] < min && i != k)
            min = adj[i][k];
    return min;
}

int BranchAndBound_Implementation::secondMin(int **adj, int i) {
    int first = INT_MAX, second = INT_MAX;
    for (int j = 0; j < N; j++) {
        if (i == j)
            continue;

        if (adj[i][j] <= first) {
            second = first;
            first = adj[i][j];
        } else if (adj[i][j] <= second &&
                   adj[i][j] != first)
            second = adj[i][j];
    }
    return second;
}


void BranchAndBound_Implementation::tsp_rec(int **adj, int curr_bound, int curr_weight,
                                            int level, int *curr_path) {
    if (level == N) {
        if (adj[curr_path[level - 1]][curr_path[0]] != 0) {
            int curr_res = curr_weight + adj[curr_path[level - 1]][curr_path[0]];
            if (curr_res < final_res) {
                copyToFinal(curr_path);
                final_res = curr_res;
            }
        }
        return;
    }
    for (int i = 0; i < N; i++) {
        if (adj[curr_path[level - 1]][i] != 0 &&
            visited[i] == false) {
            int temp = curr_bound;
            curr_weight += adj[curr_path[level - 1]][i];
            if (level == 1)
                curr_bound -= ((firstMin(adj, curr_path[level - 1]) + firstMin(adj, i)) / 2);
            else
                curr_bound -= ((secondMin(adj, curr_path[level - 1]) +
                                firstMin(adj, i)) / 2);
            if (curr_bound + curr_weight < final_res) {
                curr_path[level] = i;
                visited[i] = true;
                tsp_rec(adj, curr_bound, curr_weight, level + 1, curr_path);
            }
            curr_weight -= adj[curr_path[level - 1]][i];
            curr_bound = temp;
            for (int i = 0; i < N; i++) {
                visited[i] = false;
            }
            for (int j = 0; j <= level - 1; j++)
                visited[curr_path[j]] = true;
        }
    }
}


void BranchAndBound_Implementation::tsp(int **adj) {

    int curr_bound = 0;
    for (int i = 0; i < N; i++) {
        curr_path[i] = -1;
    }
    for (int i = 0; i < N; i++) {
        visited[i] = false;
    }
    for (int i = 0; i < N; i++)
        curr_bound += (firstMin(adj, i) +
                       secondMin(adj, i));

    curr_bound = (curr_bound & 1) ? curr_bound / 2 + 1 :
                 curr_bound / 2;
    visited[0] = true;
    curr_path[0] = 0;
    tsp_rec(adj, curr_bound, 0, 1, curr_path);
}

int BranchAndBound_Implementation::solution(int **dist) {
    long long int time = 0;
    start = std::chrono::high_resolution_clock::now();
    this->tsp(dist);
    stop = std::chrono::high_resolution_clock::now();
    time += std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();
//    std::cout << "Minimum cost: " << final_res << std::endl;
//    std::cout << "Path taken: ";
//    for (int i = 0; i <= N; i++) {
//        std::cout << "->" << final_path[i] << ' ';
//    }
//    std::cout << "-> 0" << std::endl;
//    std::cout << "time: " << time << "ns" << std::endl;

    return time;
}


BranchAndBound_Implementation::BranchAndBound_Implementation(int n) {
    this->final_path = new int[n + 1];
    this->visited = new bool[n];
    this->N = n;
    this->curr_path = new int[n + 1];
}
