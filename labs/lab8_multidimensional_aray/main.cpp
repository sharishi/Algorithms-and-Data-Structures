//
// Created by Vica on 15.04.2024.
//
#include <iostream>
#include <array>
#include <cstddef>
#include <span>
#include <cassert>
#include <array>
#include "../../ multidimensional_arrays/Iliffe.h"
#include "../../ multidimensional_arrays/linearly_arranged.h"


int main() {
    {
        std::array<size_t, 3> indices{3, 4, 5};
        Iliffe arr = create_iliffe(indices);

        {
            std::array<size_t, 3> i{0, 1, 2};
            int *element = element_at_index(&arr, i);
            std::cout << *element;
        }
        delete_ilifee(&arr);
    }
    {
        std::array<size_t, 3> dimensions{3, 4, 5};
        LinearArray arr = create_linear_array(dimensions);

        std::cout << arr.dimensions.size() << std::endl;
        for(size_t d: arr.dimensions){
            std::cout << d << std::endl;
        }

        std::span linear_memory = get_linear_memory(&arr);
        for (size_t i = 0; i < linear_memory.size(); i++) {
            linear_memory[i] = i;
        }
        for (size_t x = 0; x < dimensions[0]; x++) {
            for (size_t y = 0; y < dimensions[1]; y++) {
                std::cout << "(";
                for (size_t z = 0; z < dimensions[2]; z++) {
                    std::array indices = {x, y, z};
                    int* element = get_element_at_index(&arr, indices);
                    std::cout << *element;
                    if(z != dimensions[2] - 1){
                        std::cout << ", ";
                    }
                }
                std::cout << ")";

            }
            std::cout << "\n";
        }

    }
    {
        std::array<size_t, 3> dimensions{ 3, 4, 5 };
        LinearArray arr = create_linear_array(dimensions);

        std::span linearMemory = get_linear_memory(&arr);
        for (size_t i = 0; i < linearMemory.size(); i++)
        {
            linearMemory[i] = i;
        }

        iterate(dimensions, [&](std::span<size_t> indices){
            int x = *get_element_at_index(&arr, indices);
            std::cout << x << ", ";
        });
        std::cout << std::endl;
        for (size_t i0 = 0; i0 < dimensions[2]; i0++)
        {
            for (size_t i1 = 0; i1 < dimensions[1]; i1++)
            {
                std::cout << "(";
                for (size_t i2 = 0; i2 < dimensions[0]; i2++)
                {
                    std::array indices = {i2, i1, i0};
                    int* element = get_element_at_index(&arr, indices);
                    std::cout << *element;
                    if (i2 != dimensions[0] - 1)
                    {
                        std::cout << ", ";
                    }
                }
                std::cout << ")";
            }
            std::cout << "\n";
        }
    }
    return 0;
}
