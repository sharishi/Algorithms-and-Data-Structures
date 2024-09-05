//
// Created by Vica on 27.03.2024.
//

#ifndef LAB4_STACK_H
#define LAB4_STACK_H

#include<iostream>
#include<vector>
#include<cassert>
#include "../../untitled/info.h"

struct DynamicStack{
    std::vector<City> underlyingArray;
};

bool isEmpty(const DynamicStack* stack){
    return stack->underlyingArray.empty();
}

void push(DynamicStack* stack, const City& city){
    stack->underlyingArray.push_back(city);
}

City pop(DynamicStack* stack){
//    assert(!isEmpty(stack));
    City lastCity = stack->underlyingArray.back();
    stack->underlyingArray.pop_back();
    return lastCity;
}

City* getLastElement(DynamicStack* stack) {
    if (stack->underlyingArray.empty()) {
        return nullptr;
    } else {
        return &stack->underlyingArray.back(); // Возвращает указатель на последний элемент.
    }
}
#endif //LAB4_STACK_H
