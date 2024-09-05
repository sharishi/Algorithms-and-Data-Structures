//
// Created by Vica on 03.04.2024.
//

#ifndef LAB7_SELECTION_SORT_H
#define LAB7_SELECTION_SORT_H
#include <iostream>
#include <span>

#include "../../untitled/info.h"
#include "sorting_stats.h"

void selectionSort(std::span<City> arr, SortingStats& stats) {
    size_t currentIndex = 0;
    while (true) {

        if (currentIndex + 1 >= arr.size()) {
            ++stats.comparisons;
            return;
        }
        City minElement = arr[currentIndex];
        size_t minIndex = currentIndex;
        ++stats.swapsOrCopies;
        for (size_t i = currentIndex; i < arr.size(); i++) {
            if (arr[i].id < minElement.id) {
                ++stats.comparisons;
                minIndex = i;
                minElement = arr[i];
            }
        }
        arr[minIndex] = arr[currentIndex];
        arr[currentIndex] = minElement;
        ++stats.swapsOrCopies;

        currentIndex++;
    }
}

#endif //LAB7_SELECTION_SORT_H
