//
// Created by Vica on 21.03.2024.
//
#ifndef ASDC_BINARY_SEARCH_H
#define ASDC_BINARY_SEARCH_H
#include<iostream>
#include <vector>
#include "../info.h"

City* binary_search(std::vector<City>& cities, size_t search_id) {
    size_t start = 0;
    size_t end = cities.size();

    while (start < end) {
        size_t current = (end + start) / 2;

        if (cities[current].id == search_id) {
            return &cities[current];
        }
        else if (cities[current].id < search_id) {
            start = current + 1;
        }
        else {
            end = current;
        }
    }

    return nullptr; // Return nullptr if the element is not found
}

#endif //ASDC_BINARY_SEARCH_H
