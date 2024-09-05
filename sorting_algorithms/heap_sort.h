//
// Created by Vica on 03.04.2024.
//

#ifndef LAB6_HEAP_SORT_H
#define LAB6_HEAP_SORT_H

#include <iostream>
#include <span>
#include <array>
#include <span>
#include "../../untitled/info.h"
#include "sorting_stats.h"

void heapify(std::span<City> arr, size_t parentIndex, SortingStats& stats) {
    while (true) {
        size_t leftIndex = parentIndex * 2 + 1;
        size_t rightIndex = parentIndex * 2 + 2;
        size_t indexOfLargest = parentIndex;
        ++stats.swapsOrCopies;

        if (leftIndex < arr.size()) {
            ++stats.comparisons;
            int largest = arr[indexOfLargest].id;
            int left = arr[leftIndex].id;
            if (largest > left) {
                ++stats.comparisons;
                indexOfLargest = leftIndex;
                ++stats.swapsOrCopies;
            }
        }
        if (rightIndex < arr.size()) {
            ++stats.comparisons;
            int largest = arr[indexOfLargest].id;
            int right = arr[rightIndex].id;
            if (largest > right) {
                ++stats.comparisons;
                indexOfLargest = rightIndex;
                ++stats.swapsOrCopies;
            }
        }
        if (indexOfLargest == parentIndex) {
            return;
        }

        City largest = arr[indexOfLargest];
        arr[indexOfLargest] = arr[parentIndex];
        arr[parentIndex] = largest;
        ++stats.swapsOrCopies;

        parentIndex = indexOfLargest;
    }
}

void heapSort(std::span<City> arr, SortingStats& stats) {
    for (size_t i = (arr.size() / 2) + 1; i >= 1; i--) {
        heapify(arr, i - 1, stats);
    }
    for (size_t i = 0; i < arr.size(); i++) {
        City root = arr[0];
        size_t currentLast = arr.size() - i - 1;


        arr[0] = arr[currentLast];
        arr[currentLast] = root;
        ++stats.swapsOrCopies;

        size_t newLen = currentLast;
        std::span<City> heapArr{ arr.data(), newLen };
        heapify(arr, 0, stats);
    }
}


#endif //LAB6_HEAP_SORT_H
