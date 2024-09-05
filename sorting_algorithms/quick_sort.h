//
// Created by Vica on 10.04.2024.
//

#ifndef LAB7_QUICK_SORT_H
#define LAB7_QUICK_SORT_H
#include <iostream>
#include <span>
#include <span>
#include <algorithm>
#include "../../untitled/info.h"
#include "sorting_stats.h"

void quickSort(std::span<City> arr, SortingStats& stats) {
    if (arr.size() <= 1) {
        ++stats.comparisons;
        return;
    }

    size_t pivotIndex = 0;
    size_t smallerThanPivotIndex = pivotIndex + 1;
    size_t currentIndex = smallerThanPivotIndex;
    ++stats.swapsOrCopies;
    int pivot = arr[pivotIndex].id;

    while (currentIndex < arr.size()) {
        ++stats.comparisons;
        int currentElement = arr[currentIndex].id;
        if (currentElement < pivot) {
            ++stats.comparisons;
            std::swap(arr[currentIndex], arr[smallerThanPivotIndex]);
            ++stats.swapsOrCopies;
            ++smallerThanPivotIndex;
        }
        ++currentIndex;
    }

    std::swap(arr[pivotIndex], arr[smallerThanPivotIndex - 1]);
    ++stats.swapsOrCopies;

    std::span<City> left{arr.data(), smallerThanPivotIndex - 1};
    std::span<City> right{arr.data() + smallerThanPivotIndex, arr.size() - smallerThanPivotIndex};

    quickSort(left, stats);
    quickSort(right, stats);
}

#endif //LAB7_QUICK_SORT_H
