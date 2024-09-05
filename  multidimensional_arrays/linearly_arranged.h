//
// Created by Vica on 17.04.2024.
//
//row merger
#ifndef LAB8_LINEARLY_ARRANGED_H
#define LAB8_LINEARLY_ARRANGED_H
#include <span>
#include <cassert>
struct LinearArray{
    std::span<size_t> dimensions;
    int* firstElement;
};
size_t compute_total_size(std::span<size_t> dimensions){
    size_t total_size = 1;
    for(size_t d: dimensions){
        total_size *= d;
    }
    return total_size;
}
LinearArray create_linear_array(std::span<size_t> dimensions){
    size_t total_size = compute_total_size(dimensions);
    int* memory = new int[total_size];
    return {dimensions, memory};
}

int* get_element_at_index(LinearArray* arr, std::span<size_t> indices){
    assert(arr->dimensions.size() == indices.size());
    for (size_t i = 0; i < indices.size(); i++) {
        assert(indices[i] < arr->dimensions[i]);

    }
#if false
    size_t index = indices[indices.size() - 1];
    for (size_t i = indices.size() - 1; i >= 1; i--) {

        size_t index_at_dim = indices[i - 1];
        index *= arr->dimensions[i - 1];
        index += index_at_dim;
    }
#else
    size_t index = indices[0];
    for (size_t i = 1; i < indices.size(); i++) {

        size_t index_at_dim = indices[i];
        index *= arr->dimensions[i];
        index += index_at_dim;
    }
#endif

    return &arr->firstElement[index];
}

std::span<int> get_linear_memory(LinearArray* arr){
    size_t total_size = compute_total_size(arr->dimensions);
    return {arr->firstElement, total_size};
}

template <typename Func>
void iterate(std::span<size_t> dimensionSizes, Func func)
{
    size_t* indicesMemory = new size_t[dimensionSizes.size()];
    for (size_t i = 0; i < dimensionSizes.size(); i++)
    {
        indicesMemory[i] = 0;
    }

    std::span<size_t> indices{ indicesMemory, dimensionSizes.size() };

    while (true)
    {
        func(indices);

        size_t i = 0;
        for (; i < indices.size(); i++)
        {
            indices[i] += 1;
            if (indices[i] == dimensionSizes[i])
            {
                indices[i] = 0;
            }
            else
            {
                break;
            }
        }

        if (i == indices.size())
        {
            break;
        }
    }

    delete[] indicesMemory;
}
#endif //LAB8_LINEARLY_ARRANGED_H
