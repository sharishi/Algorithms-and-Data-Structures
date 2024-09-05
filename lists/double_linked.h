//
// Created by Vica on 25.03.2024.
//

#ifndef ASDC_DOUBLE_LINKED_H
#define ASDC_DOUBLE_LINKED_H
#include <iostream>
#include <cassert>

template<typename T>
struct DoubleLinkedList;


template<typename T>
struct Node {
    T value;
    Node* prev;
    Node* next;
};


template<typename T>
struct DoubleLinkedList {
    Node<T>* head;
    Node<T>* tail;


    DoubleLinkedList() : head(nullptr), tail(nullptr) {}

    ~DoubleLinkedList() {
        Node<T>* current = head;
        while (current) {
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
    }

    Node<T>* insertAfter(Node<T>* node, T value) {
        Node<T>* newNode = new Node<T>{std::move(value), nullptr, nullptr};
        if (node == nullptr) { // Если узел не указан, вставляем в начало списка
            if (!head) {
                head = newNode;
                tail = newNode;
            } else {
                newNode->next = head;
                head->prev = newNode;
                head = newNode;
            }
        } else {
            newNode->next = node->next;
            newNode->prev = node;
            if (node->next)
                node->next->prev = newNode;
            else
                tail = newNode;
            node->next = newNode;
        }
        return newNode;
    }


    Node<T>* insertBefore(Node<T>* node, T value) {
        if (node == nullptr) {
            return insertAfter(tail, value);
        } else if (node->prev == nullptr) {
            Node<T>* newNode = new Node<T>{std::move(value), nullptr, node};
            node->prev = newNode;
            head = newNode;
            return newNode;
        } else {
            return insertAfter(node->prev, value);
        }
    }

    Node<T>* find(int value) {
        Node<T>* current = head;
        while (current) {
            if (current->value.id == value) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    void remove_double(Node<T>* node) {
        if (node == nullptr)
            return;

        if (node->prev)
            node->prev->next = node->next;
        else
            head = node->next;

        if (node->next)
            node->next->prev = node->prev;
        else
            tail = node->prev;

        delete node;
    }

    void assertNoCycles() {
        Node<T>* current = head;
        size_t length = 0;

        while (current) {
            ++length;
            current = current->next;
        }

        assert(length > 0 && "Empty list!");
    }
};


#endif //ASDC_DOUBLE_LINKED_H
