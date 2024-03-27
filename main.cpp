//
// Created by Vica on 21.03.2024.
//

#include <iostream>
#include <vector>
#include "info.h"
#include "searches/binary_search.h"
#include "searches/binary_tree.h"
#include "searches/fibonacci.h"
#include "searches/linear_search.h"
#include "lists/singly_linked.h"
#include "lists/double_linked.h"
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

    // LAB 1
    //..............................................................................................................
    std::cout << "LAB 1" << std::endl;
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
        std::cout << 'h';
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

    //LAB2
    //..............................................................................................................
    std::cout << "LAB 2" << std::endl;

    //Singly linked list
    LinkedList<City> cityList;

    for (auto iter = cities_read.rbegin(); iter != cities_read.rend(); ++iter) {
        cityList.insertAfter(nullptr, std::move(*iter));
    }
    // Поиск города по идентификатору
    FindNodeResult<City> result = cityList.find(1);
//    if (result.foundNode) {
//        std::cout << "Found City: " << result.foundNode->value.name.data() << std::endl;
//    } else {
//        std::cout << "City not found." << std::endl;
//    }

//    LinkedList<City>::Node *current = cityList.head;
//    while (current) {
//        std::cout << "City Name: " << current->value.name.data() << std::endl;
//        current = current->next;
//    }
//    // Удаление следующего узла
    cityList.removeAfter(nullptr);

//    std::cout << "After delete: " << std::endl;
    LinkedList<City>::Node *current2 = cityList.head;

    // Вывод списка городов
//    while (current2) {
//        std::cout << "City Name: " << current2->value.name.data() << std::endl;
//        current2 = current2->next;
//    }
    cityList.assertNoCycles();
//Создание doublelists
//    // Пример использования
    DoubleLinkedList<City> DoubleLinkedList;

    for (auto iter = cities_read.rbegin(); iter != cities_read.rend(); ++iter) {
        DoubleLinkedList.insertAfter(nullptr, std::move(*iter));
    }

//    // Поиск города по идентификатору
    Node<City>* result_double = DoubleLinkedList.find(2);
//
    if (result_double) {
        std::cout << "Found City: " << result_double->value.name.data() << std::endl;
    } else {
        std::cout << "City not foundyee." << std::endl;
    }
//    int length = 0;
//    Node<City>* current = DoubleLinkedList.head;
//
//    while (current != nullptr) {
//        ++length;
//        current = current->next;
//    }
//
//
//

//    std::cout << "Длина списка: " << length << std::endl;

// Удаление узла из списка
    DoubleLinkedList.remove_double(DoubleLinkedList.head);

//    int length2 = 0;
//    Node<City>* current3 = DoubleLinkedList.head;
//
//    while (current3 != nullptr) {
//        ++length2;
//        current3 = current3->next;
//    }
//
//    std::cout << "Длина списка: " << length2 << std::endl;

    DoubleLinkedList.assertNoCycles();

//Lab4
//....................................................................................................................


    return 0;
};



