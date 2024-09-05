//
// Created by Vica on 10.04.2024.
//
#ifndef LAB7_HASH_TABLE_H
#define LAB7_HASH_TABLE_H
#include <string>
#include <array>
#include <cassert>
#include <memory>
#include"../../untitled/info.h"

inline static const float LIMIT = 0.8;
inline static const int MINSIZE = 5;

struct BucketNode {
    std::string_view key;
    City city;
    BucketNode* next;
};

using HashFunc = size_t(*)(std::string_view key);

struct AssociativeArray {
    BucketNode** buckets;
    HashFunc hashFunc;
    int capacity;
    int elements_count;
};

struct AddOrGetElementResult {
    City* city;
    bool added;
};

void resize(AssociativeArray* arr);

size_t compute_index_key(AssociativeArray* arr, std::string_view key) {
    size_t hash = arr->hashFunc(key);
    size_t index = hash % arr->capacity;
    return index;
}

AddOrGetElementResult addOrGetElement(AssociativeArray* arr, std::string_view key) {
    if (arr->capacity == 0
        || static_cast<float>(arr->elements_count) / static_cast<float>(arr->capacity) > LIMIT)
    {
        resize(arr);
    }
    size_t index = compute_index_key(arr, key);
    BucketNode** currentNode = &arr->buckets[index];
    while (true) {
        if ((*currentNode) == nullptr) {
            BucketNode* node = new BucketNode;
            node->key = key;
            node->next = nullptr;
            *currentNode = node;

            arr->elements_count++;

            return { &node->city, true };
        }
        else if ((*currentNode)->key == key) {
            City* cityAddress = &(*currentNode)->city;

            arr->elements_count++;

            return { cityAddress, false };
        }
        else {
            currentNode = &(*currentNode)->next;
        }
    }
}

City* get_element(AssociativeArray* arr, std::string_view key) {
    size_t index = compute_index_key(arr, key);
    BucketNode* currentNode = arr->buckets[index];
    while (currentNode != nullptr) {
        if (currentNode->key == key) {
            return &currentNode->city;
        }
        currentNode = currentNode->next;
    }
    return nullptr;
}

size_t dumbHashFunc(std::string_view key) {
    if (key.empty()) {
        return 0;
    }
    uint8_t firstLetter = key[0];
    uint8_t positionInAlphabet = firstLetter - static_cast<uint8_t>('a');
    return static_cast<size_t>(positionInAlphabet);
}

AssociativeArray create_hash_table(int capacity, HashFunc func) {
    AssociativeArray arr;
    arr.buckets = new BucketNode * [capacity];
    for (int i = 0; i < capacity; i++) {
        arr.buckets[i] = nullptr;
    }
    arr.hashFunc = func;
    arr.capacity = capacity;
    arr.elements_count = 0;
    return arr;
}

bool remove_node_by_key(AssociativeArray* arr, std::string_view key) {
    size_t index = compute_index_key(arr, key);

    BucketNode** tempNodeForRemove = &arr->buckets[index];
    while (*tempNodeForRemove != nullptr) {
        if ((*tempNodeForRemove)->key == key) {
            *tempNodeForRemove = (*tempNodeForRemove)->next;
            delete *tempNodeForRemove;
            return true;
        }
        tempNodeForRemove = &(*tempNodeForRemove)->next;
    }
    return false;
}

void free_associative_array(AssociativeArray* arr) {
    if (arr == nullptr || arr->elements_count == 0 || arr->buckets == nullptr)
        return;
    for (int i = 0; i < arr->elements_count; ++i) {
        BucketNode* currentNode = arr->buckets[i];
        while (currentNode != nullptr) {
            BucketNode* nodeToDelete = currentNode;
            currentNode = currentNode->next;
            delete nodeToDelete;
        }
    }
    delete[] arr->buckets;
    arr->buckets = nullptr;
}

void copy_elements_in_new_hashtable(AssociativeArray* arr, AssociativeArray* newArr) {
    for (int i = 0; i < arr->capacity; i++) {
        BucketNode* node = arr->buckets[i];
        while (node != nullptr) {
            auto result = addOrGetElement(newArr, arr->buckets[i]->key);
            *result.city = arr->buckets[i]->city;

            node = node->next;
        }
    }
}

void resize(AssociativeArray* arr) {
    int newCapacity = arr->capacity * 2;
    if (newCapacity < MINSIZE) {
        newCapacity = MINSIZE;
    }
    AssociativeArray newArray = create_hash_table(newCapacity, arr->hashFunc);
    copy_elements_in_new_hashtable(arr, &newArray);

    free_associative_array(arr);
    *arr = newArray;
}

#endif //LAB7_HASH_TABLE_H
