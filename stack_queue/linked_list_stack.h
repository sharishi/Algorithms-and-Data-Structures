//
// Created by Vica on 28.03.2024.
//

#ifndef LAB5_LINKED_LIST_STACK_H
#define LAB5_LINKED_LIST_STACK_H
#include<iostream>
#include "../lists/singly_linked.h"
#include "../../untitled/info.h"

struct LinkedListStack{
    LinkedList<City> cityList;
};

void push(LinkedListStack* stack,City& city){
    stack->cityList.addToStart(std::move(city));
}
bool isEmpty( LinkedListStack* stack){
    return stack->cityList.isEmpty(stack->cityList.head);
}
City* getLastElement(LinkedListStack* stack){
    return stack->cityList.getFirstElement(nullptr);
}

void pop(LinkedListStack* stack){
    stack->cityList.pop(nullptr);
}
void printLinkedList(const LinkedList<City>& list) {
    typename LinkedList<City>::Node* current = list.head;
    while (current != nullptr) {
        std::cout <<  " " << current->value.id << " ";
        current = current->next;
    }
    std::cout << std::endl;
}


#endif //LAB5_LINKED_LIST_STACK_H
