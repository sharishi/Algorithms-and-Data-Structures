//
// Created by Vica on 21.03.2024.
//

#ifndef ASDC_LINEAR_SEARCH_H
#define ASDC_LINEAR_SEARCH_H
#include<iostream>
#include <vector>
#include "../info.h"
#include <vector>


City* linear_search(
        std::vector<City>& cities, size_t search_id)
{
    for (auto& city : cities)
    {
        if (city.id == search_id)
        {
            return &city;
        }
    }
    return NULL;
}
#endif //ASDC_LINEAR_SEARCH_H
