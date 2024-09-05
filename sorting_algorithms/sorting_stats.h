//
// Created by Vica on 18.04.2024.
//

#ifndef LAB7_SORTING_STATS_H
#define LAB7_SORTING_STATS_H
#include <iostream>
#include <chrono>
#include <span>

struct SortingStats {
    size_t comparisons = 0;
    size_t swapsOrCopies = 0;
};
void performSort(std::span<City> arr, std::function<void(std::span<City>, SortingStats&)> sortFunction, const std::string& sortName, std::vector<double>& executionTimes) {
    std::vector<City> vecArr(arr.begin(), arr.end());
    SortingStats stats;

    auto start = std::chrono::steady_clock::now();
    sortFunction(vecArr, stats);
    auto end = std::chrono::steady_clock::now();

    double duration = std::chrono::duration<double>(end - start).count();
    executionTimes.push_back(duration);

    std::cout << "Comparisons: " << stats.comparisons << std::endl;
    std::cout << "Swaps or Copies: " << stats.swapsOrCopies << std::endl;


    std::cout << sortName << " - Execution Time: " << duration << " seconds" << std::endl;

//    std::cout << sortName << ": ";
//    for(const auto& city : vecArr) {
//        std::cout << city.id << ", ";
//    }

    std::cout << std::endl << std::endl;
}
#endif //LAB7_SORTING_STATS_H
