//
// Created by Vica on 21.03.2024.
//

#include <iostream>
#include <vector>
#include "../../info.h"
#include "../../searches/binary_search.h"
#include "../../searches/binary_tree.h"
#include "../../searches/fibonacci.h"
#include "../../searches/linear_search.h"
#include <chrono>

template<typename Func, typename... Args>
std::pair<double, decltype(std::declval<Func>()(std::declval<Args>()...))>
measureTimeAndResult(Func &&func, Args &&... args) {
    auto start = std::chrono::high_resolution_clock::now();
    auto result = func(std::forward<Args>(args)...);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    return {duration.count(), result};
}

int main() {

    // LAB 2
    //..............................................................................................................
    std::cout << "LAB 2" << std::endl;
    ErrorFlags flags;
    FILE *file = fopen("city.csv", "a");
    if (file == nullptr) {
        std::cerr << "Error: Unable to open file for writing." << std::endl;
        return 1;
    }
    // New City add
    std::vector<City> cities = {
            {9,  "Paris",        52,   "Gallo-Romans",      "France",    48.8566f,  2.3522f,   EUROPE},
            {10, "Buenos Aires", 1536, "Spanish explorers", "Argentina", -34.6118f, -58.4173f, SOUTHAMERICA},

    };

    // Validate each city
    for (auto &city: cities) {
        validateAndFillCity(city, flags);
    }

    // Serialize City
    for (auto &city: cities) {
        serialize_city(&city, file, flags);
        fprintf(file, "\n");
    }

    fflush(file);
    fclose(file);

    // Deserialize City
    std::vector<City> cities_read;
    try {
        cities_read = read_cities_from_csv("city.csv", flags);
    }
    catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    // We enter the constant identifier we want to find
    size_t search_id = 4;

    auto result_binary_search = measureTimeAndResult(binary_search, cities_read, search_id);
    auto result_linear_search = measureTimeAndResult(linear_search, cities_read, search_id);
    //Binary search
    std::cout << "Binary search: " << std::endl;
    print_output(result_binary_search, search_id);
    //Linear search
    std::cout << "Linear search: " << std::endl;
    print_output(result_linear_search, search_id);
    //Fibonacci search
    std::cout << "Fibonacci search: " << std::endl;
    auto result_fibonacci_search = measureTimeAndResult(fibonacciSearch, cities_read, search_id, cities_read.size());
    double time_fibonacci_search = result_fibonacci_search.first;
    int ind_from_fibonacci_search = result_fibonacci_search.second;
    City *ptr_to_city = &cities_read[ind_from_fibonacci_search];
    print_output({time_fibonacci_search, ptr_to_city}, search_id);
    //Binary Tree search
    std::cout << "Binary Tree Search: " << std::endl;
    BSTreeNode *root = nullptr;
    for (const auto &city: cities_read) {
        insertNode(root, city);
    }
    auto result_bt_search = measureTimeAndResult(findNode, root, search_id);
    double time_bt_search = result_bt_search.first;
    BSTreeNode *city_from_bt_search = result_bt_search.second;
    printNode(city_from_bt_search);
    std::cout << "Time: " << time_bt_search << std::endl << std::endl;

    deleteTree(root);



    return 0;
};



