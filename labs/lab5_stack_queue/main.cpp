
#include <iostream>
#include <vector>
#include "../../../untitled/info.h"
#include "../../stack_queue/dynamic_stack.h"
#include "../../stack_queue/linked_list_stack.h"


int main(){

    ErrorFlags flags;

    // Deserialize City
    std::vector<City> cities_read;
    try {
        cities_read = read_cities_from_csv("city.csv", flags);
    }
    catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    {
        DynamicStack stack{};

        for (auto &city: cities_read) {
            push(&stack, city);
        }

        // Получаем указатель на последний элемент и выводим информацию о нем
        City *lastCity = getLastElement(&stack);
        if (lastCity != nullptr) {
            std::cout << "Last element in the stack:\n";
            std::cout << "City ID: " << lastCity->id << std::endl;
            std::cout << "City Name: " << lastCity->name.data() << std::endl;
            // Добавьте вывод остальных полей города по аналогии
        } else {
            std::cout << "The stack is empty." << std::endl;
        }

        assert(pop(&stack).id == 40);
        assert(pop(&stack).id == 39);

        pop(&stack);
    }

    {
        LinkedListStack stack{};


        for (auto city: cities_read) {
            push(&stack, city);
        }
        printLinkedList(stack.cityList);

        City* lastCity = getLastElement(&stack);
        if (lastCity != nullptr) {
            std::cout << "Last element in the stack:\n";
            std::cout << "City ID: " << lastCity->id << std::endl;
            std::cout << "City Name: " << lastCity->name.data() << std::endl;
        } else {
            std::cout << "The stack is empty." << std::endl;
        }
        assert(lastCity != nullptr);
        assert(lastCity->id == 40);
        pop(&stack);

        assert(!isEmpty(&stack));
        printLinkedList(stack.cityList);
    }

    return 0;
}