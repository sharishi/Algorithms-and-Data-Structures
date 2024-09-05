//
// Created by Vica on 05.04.2024.
//

#ifndef LAB7_INSERTION_SORT_H
#define LAB7_INSERTION_SORT_H
#include <iostream>
#include <span>
#include "../../untitled/info.h"
#include "sorting_stats.h"

void insertionSort(std::span<City> arr, SortingStats& stats) {
    size_t sortedArraySize = 1;
    while (sortedArraySize < arr.size()) {
        ++stats.comparisons;
        City value = arr[sortedArraySize];
        size_t i = sortedArraySize;
        ++stats.swapsOrCopies;
        while (i > 0 && arr[i - 1].id > value.id) {
            stats.comparisons += 2;
            arr[i] = arr[i - 1];
            --i;
        }
        arr[i] = value;
        ++sortedArraySize;
    }
}


#endif //LAB7_INSERTION_SORT_H
