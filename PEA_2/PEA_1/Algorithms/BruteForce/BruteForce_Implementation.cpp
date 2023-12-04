//
// Created by Jakub on 27.10.2023.
//

#include <iostream>
#include "BruteForce_Implementation.h"


BruteForce_Implementation::BruteForce_Implementation(Matrix matrix){
    this->matrix = matrix;
}

int BruteForce_Implementation::routeLength(int **graph, int *route, int n) {
    int total = 0;
    for (int i = 0; i < n - 1; i++) {
        total += graph[route[i]][route[i + 1]];
    }
    total += graph[route[n - 1]][route[0]];
    return total;
}

int BruteForce_Implementation::tsp(int **graph, int n) {
    long long int time = 0;
    std::chrono::high_resolution_clock::time_point start;
    std::chrono::high_resolution_clock::time_point stop;
    start = std::chrono::high_resolution_clock::now();
    int *route = new int[n];
    for (int i = 0; i < n; i++) {
        route[i] = i;
    }
    double min_route_length = routeLength(graph, route, n);
    int *best_route = new int[n];
    copy(route, route + n, best_route);

    while (nextPermutation(route, n)) {
        double current_route_length = routeLength(graph, route, n);
        if (current_route_length < min_route_length) {
            min_route_length = current_route_length;
            copy(route, route + n, best_route);
        }
    }



    stop = std::chrono::high_resolution_clock::now();
    time += std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start).count();
//    std::cout << "Minimum cost: " << min_route_length << std::endl;
//
//    std::cout << "Path taken: ";
//    for (int i = 0; i < n; i++) {
//        std::cout << "-> "<< best_route[i] << " ";
//    }
//    std::cout << "-> 0" << std::endl;
//    std::cout << "time: " << time << "ns" << std::endl;


    delete[] route;
    delete[] best_route;
    return time;
}


bool BruteForce_Implementation::nextPermutation(int *route, int n) {
    int i = n - 1;
    while (i > 0 && route[i - 1] >= route[i]) {
        i--;
    }
    if (i <= 0) {
        return false;
    }
    int j = n - 1;
    while (route[j] <= route[i - 1]) {
        j--;
    }
    swap(route[i - 1], route[j]);
    reverse(route, i, n - 1);
    return true;
}

void BruteForce_Implementation::swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void BruteForce_Implementation::reverse(int *arr, int start, int end) {
    while (start < end) {
        swap(arr[start], arr[end]);
        start++;
        end--;
    }
}

void BruteForce_Implementation::copy(int *source, int *source_end, int *destination) {
    while (source != source_end) {
        *destination++ = *source++;
    }
}
