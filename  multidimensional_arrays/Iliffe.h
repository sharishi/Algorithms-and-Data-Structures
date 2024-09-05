//
// Created by Vica on 15.04.2024.
//

#ifndef LAB6_EXAMPLE_H
#define LAB6_EXAMPLE_H

#include <cstddef>
#include <span>
#include <iostream>
#include <cassert>

struct Iliffe {
    void *arr;
    size_t num_dim;
    size_t *dim_size;


};

void* create_arr_at_level(std::span<size_t> dim_size, size_t current_dim_index, int *current_elem) {
    const size_t current_dim_size = dim_size[current_dim_index];
    if (current_dim_index == dim_size.size() - 1) {
        int* const result = new int[current_dim_size];
        for (size_t i = 0; i < current_dim_size; i++) {
            result[i] = (*current_elem);
            (*current_elem)++;
        }
        return result;
    } else {
        void** const arr = new void*[current_dim_size];
        size_t nex_dim_ind = current_dim_index + 1;
        for (size_t i = 0; i < current_dim_size; i++) {
            void* const new_arr = create_arr_at_level(dim_size, nex_dim_ind, current_elem);
            arr[i] = new_arr;


        }

        return arr;
    }
}

Iliffe create_iliffe(std::span<size_t> dim_sizes) {
    size_t *dim_size_copy = new size_t[dim_sizes.size()];
    for (size_t i = 0; i < dim_sizes.size(); i++) {
        dim_size_copy[i] = dim_sizes[i];
    }

    int count = 0;
    void *arr = create_arr_at_level(dim_sizes, 0, &count);
    std::cout << "Count is: " << count << std::endl;

    return {
            arr, dim_sizes.size(), dim_size_copy
    };

}
int* element_at_index(Iliffe* iliffe, std::span<size_t> indices){
    assert(indices.size() == iliffe->num_dim);
    void* current_arr = iliffe->arr;
    for (size_t i = 0; i < indices.size() - 1; i++) {
        size_t index = indices[i];
        assert(index < iliffe->dim_size[i]);
        void** arr_of_pointers = static_cast<void**>(current_arr);
        current_arr = arr_of_pointers[index];
    }
    {
        int* last_level_array = static_cast<int*>(current_arr);
        size_t index = indices[indices.size() - 1];
        assert(index < iliffe->dim_size[indices.size() - 1]);

        return &last_level_array[index];

    }
}
void delete_ilifee_arr(void* arr, std::span<size_t> dim_sizes, size_t current_dim_index){

    if(current_dim_index == dim_sizes.size() - 1){
        int* numbers = (int*) arr;
        delete[] numbers;
    }else{
        void** pointer_arr = (void**) arr;
        const size_t current_dim_size = dim_sizes[current_dim_index];
        const size_t next_dim_index = current_dim_index + 1;
        for (size_t i = 0; i < current_dim_size ; i++) {
            delete_ilifee_arr(pointer_arr[i], dim_sizes, next_dim_index);
        }
        delete[] pointer_arr;
    }

}
void delete_ilifee(Iliffe* iliffe){
    delete_ilifee_arr(iliffe->arr, {iliffe->dim_size, iliffe->num_dim}, 0);
    delete[] iliffe->dim_size;

}
#endif //LAB6_EXAMPLE_H
