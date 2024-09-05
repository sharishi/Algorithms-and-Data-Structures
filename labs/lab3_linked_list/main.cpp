//
// Created by Vica on 27.03.2024.
//
//
// Created by Vica on 27.03.2024.
//
//
// Created by Vica on 21.03.2024.
//

#include <iostream>
#include <vector>
#include "../../../untitled/info.h"
#include "../../lists/singly_linked.h"
#include "../../lists/double_linked.h"

int main() {

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

    std::cout << "LAB 3" << std::endl;

    //Singly linked list
    LinkedList<City> cityList;

    // Вставка городов
    for (auto iter = cities_read.rbegin(); iter != cities_read.rend(); ++iter) {
        cityList.insertAfter(nullptr, std::move(*iter));
    }
    // Поиск города по идентификатору
    {
        FindNodeResult<City> result = cityList.find(1);
        assert(result.foundNode != nullptr);
    }

    //   Вывод списка городов (пример)
//    LinkedList<City>::Node *current = cityList.head;
//    while (current) {
//        std::cout << "City Name: " << current->value.name.data() << std::endl;
//        current = current->next;
//    }

//    // Удаление следующего узла
    City lastRemovedCity = cityList.getLastElement(nullptr);
//    std::cout << "lastRemovedCity 3:" << lastRemovedCity.id <<  std::endl;

//    std::cout << "After delete: " << std::endl;
    LinkedList<City>::Node *current2 = cityList.head;

    // Вывод списка городов
//    while (current2) {
//        std::cout << "City Name: " << current2->value.name.data() << std::endl;
//        current2 = current2->next;
//    }
    cityList.assertNoCycles();

//    // Пример использования
    DoubleLinkedList<City> DoubleLinkedList;

    for (auto& iter : cities_read) {
        DoubleLinkedList.insertAfter(nullptr, std::move(iter));
    }

//    // Поиск города по идентификатору
    Node<City>* result = DoubleLinkedList.find(2);
//
//    // Вывод найденного города (пример)
    if (result) {
        std::cout << "Found City: " << result->value.name.data() << std::endl;
    } else {
        std::cout << "City not found." << std::endl;
    }

//    std::cout << "Длина списка: " << length << std::endl;
//    // Удаление узла из списка
    DoubleLinkedList.remove_double(DoubleLinkedList.head);

//// Печатаем длину списка
//    std::cout << "Длина списка: " << length2 << std::endl;

//    // Проверка наличия циклов
    DoubleLinkedList.assertNoCycles();

};


