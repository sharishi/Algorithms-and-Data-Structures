//
// Created by Vica on 25.03.2024.
//
#include <iostream>
#include <array>
#include <string>
#include <cassert>

#ifndef ASDC_SINGLY_LINKED_H

template<typename T>
struct LinkedList;

template<typename T>
struct FindNodeResult {
    typename LinkedList<T>::Node* foundNode;
    typename LinkedList<T>::Node* previousNode;
};

template<typename T>
struct LinkedList {
    // Узел списка
    struct Node {
        T value;
        Node* next;
    };

    Node* head;
    Node* tail;
    size_t size; // текущее количество нодов в списке

    // Конструктор
    LinkedList() : head(nullptr), tail(nullptr), size(0) {}

    // Деструктор для освобождения памяти
    ~LinkedList() {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    // Вставка значения после указанного узла
    Node* insertAfter(Node* node, T&& value) {
        Node* newNode = new Node{std::move(value), nullptr};
        if (node == nullptr) { // Если узел не указан, вставляем в начало списка
            if (!head) {
                head = newNode;
                tail = newNode;
            } else {
                newNode->next = head;
                head = newNode;
            }
        } else { // Вставляем после указанного узла
            if (node->next == nullptr) {
                node->next = newNode;
                tail = newNode;
            } else {
                newNode->next = node->next;
                node->next = newNode;
            }
        }
        ++size; // увеличиваем размер списка
        return newNode;
    }

    // Удаление следующего узла после указанного узла
    void removeAfter(Node* node) {
        if (node == nullptr) { // Удаляем первый узел
            if (head != nullptr) {
                Node* temp = head;
                head = head->next;
                delete temp;
                --size; // уменьшаем размер списка
            }
        } else if (node->next != nullptr) { // Удаляем следующий узел после указанного узла
            Node* temp = node->next;
            node->next = temp->next;
            if (temp == tail) {
                tail = node;
            }
            delete temp;
            --size; // уменьшаем размер списка
        }
    }

    // Поиск узла с заданным значением
    FindNodeResult<T> find(int value) {
        FindNodeResult<T> result{nullptr, nullptr};

        Node* current = head;
        while (current) {
            if (current->value.id == value) {
                result.foundNode = current;
                return result;
            }
            result.previousNode = current;
            current = current->next;
        }

        return result;
    }

    // Проверка наличия циклов в списке
    void assertNoCycles() {
        Node* current = head;
        size_t length = 0;

        while (current) {
            ++length;
            current = current->next;
        }

        assert(length == size && "Cycle detected in the linked list!");
    }
};


#define ASDC_SINGLY_LINKED_H

#endif //ASDC_SINGLY_LINKED_H
