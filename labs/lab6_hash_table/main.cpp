//
// Created by Vica on 03.04.2024.
//
#include <iostream>
#include <cassert>
#include "../../hash_table/hash_table.h"

int main() {
    std::vector<City> cities;
    try {
        ErrorFlags flags;
        cities = read_cities_from_csv("city.csv", flags);
    }
    catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    AssociativeArray arr = create_hash_table(5, dumbHashFunc);

    for (const auto& city : cities) {
        AddOrGetElementResult result = addOrGetElement(&arr, city.name.data());
        if (result.added) {
            *(result.city) = city;
        } else {
            std::cerr << "City " << city.name.data() << " already exists" << std::endl;
        }
    }

    {
        City* city = get_element(&arr, "London");
        assert(city != nullptr);
        remove_node_by_key(&arr, "Paris");
    }

    free_associative_array(&arr);

    std::cout << "It works";
}
