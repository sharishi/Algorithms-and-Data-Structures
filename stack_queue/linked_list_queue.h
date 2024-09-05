//
// Created by Vica on 02.04.2024.
//

#ifndef LAB5_LINKED_LIST_QUEUE_H
#define LAB5_LINKED_LIST_QUEUE_H
#include "iostream"
#include "../../untitled/info.h"
#include "../lists/singly_linked.h"
struct Queue{
    LinkedList<City> list;
};

void enqueue(Queue* queue, City& city){
    queue->list.addToEnd(std::move(city));
}
City* dequeue(Queue* queue){
    City* city = queue->list.getLastElement(nullptr);
    queue->list.pop(nullptr);
    return city;
}
bool isEmpty(Queue* queue){
    return queue->list.isEmpty(queue->list.head);
}

City* front(Queue* queue){
    return queue->list.getFirstElement(queue->list.head);
}
#endif //LAB5_LINKED_LIST_QUEUE_H
