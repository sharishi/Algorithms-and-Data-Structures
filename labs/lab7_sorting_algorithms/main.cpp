//
// Created by Vica on 03.04.2024.
//

#include <iostream>
#include <array>
#include <algorithm>
#include <random>
#include <functional>
#include "../../../untitled/info.h"
#include "../../sorting_algorithms/sorting_stats.h"
#include "../../sorting_algorithms/heap_sort.h"
#include "../../sorting_algorithms/selection_sort.h"
#include "../../sorting_algorithms/insertion_sort.h"
#include "../../sorting_algorithms/quick_sort.h"


int main() {

    std::vector<double> executionTimes;


    std::vector<City> cities;
    try {
        ErrorFlags flags;
        cities = read_cities_from_csv("data1.csv", flags);
    }
    catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    std::random_device rd;
    std::mt19937 g(rd());

    auto begin = cities.begin();
    auto end = cities.end();

    std::shuffle(begin, end, g);


    performSort(cities, heapSort, "Heap Sort", executionTimes);
    performSort(cities, selectionSort, "Selection Sort", executionTimes);
    performSort(cities, insertionSort, "Insertion Sort", executionTimes);
    performSort(cities, quickSort, "Quick Sort", executionTimes);

    double totalExecutionTime = std::accumulate(executionTimes.begin(), executionTimes.end(), 0.0);
    double averageExecutionTime = totalExecutionTime / static_cast<double>(executionTimes.size());

    std::cout << "Total Execution Time: " << totalExecutionTime << " seconds" << std::endl;
    std::cout << "Average Execution Time: " << averageExecutionTime << " seconds" << std::endl;


    return 0;
};