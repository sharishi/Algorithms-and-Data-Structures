//
// Created by Vica on 03.04.2024.
//

#ifndef LAB5_RING_BUFFER_QUEUE_H
#define LAB5_RING_BUFFER_QUEUE_H
#include <iostream>
#include <array>
#include <span>
#include "../lists/singly_linked.h"
#include "../../untitled/info.h"

struct RoundQueue{
    std::span<City> buffer;
    size_t len;
    size_t currentIndex;
};
bool isEmpty(RoundQueue* queue){
    return queue->len ==0;
}
void enqueue(RoundQueue* queue, City city) {
    size_t capacity = queue->buffer.size();
    assert(capacity > queue->len);
    queue->buffer[queue->currentIndex] = city;
    queue->currentIndex = (queue->currentIndex + 1) % capacity;
    queue->len += 1;
}

City dequeue(RoundQueue* queue) {
    size_t capacity = queue->buffer.size();
    assert(!isEmpty(queue));
    size_t oldestIndex = (queue->currentIndex + capacity - queue->len) % capacity;
    City result = queue->buffer[oldestIndex];
    queue->len -= 1;
    return result;
}


#endif //LAB5_RING_BUFFER_QUEUE_H
