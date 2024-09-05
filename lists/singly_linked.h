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
    size_t size;

    LinkedList() : head(nullptr), tail(nullptr), size(0) {}

    ~LinkedList() {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    Node* insertAfter(Node* node, T&& value) {
        Node* newNode = new Node{std::move(value), nullptr};
        if (node == nullptr) {
            if (!head) {
                head = newNode;
                tail = newNode;
            } else {
                newNode->next = head;
                head = newNode;
            }
        } else {
            if (node->next == nullptr) {
                node->next = newNode;
                tail = newNode;
            } else {
                newNode->next = node->next;
                node->next = newNode;
            }
        }
        ++size;
        return newNode;
    }

    Node* addToStart(T&& value) {
        Node* newNode = new Node{std::move(value), nullptr};
        if (!head) {
            head = newNode;
            tail = newNode;
        } else {
            newNode->next = head;
            head = newNode;
        }
        ++size;
        return newNode;
    }
    Node* addToEnd(T&& value) {
        Node* newNode = new Node{std::move(value), nullptr};
        if (!head) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        ++size;
        return newNode;
    }

    City* getLastElement(Node* node) {
        if (node == nullptr) {
            if (head != nullptr) {
                Node* temp = head;
                while (temp->next != nullptr) {
                    temp = temp->next;
                }
                return &(temp->value); // Возвращаем указатель на последний элемент
            }
        } else if (node->next != nullptr) {
            Node* temp = node->next;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            return &(temp->value); // Возвращаем указатель на последний элемент
        }
        return nullptr; // Если список пуст или node указывает на последний элемент
    }



    void pop(Node* node) {
        if (node == nullptr) {
            if (head != nullptr) {
                Node* temp = head;
                head = head->next;
                delete temp;
                --size;
            }
        } else if (node->next != nullptr) {
            Node* temp = node->next;
            node->next = temp->next;
            if (temp == tail) {
                tail = node;
            }
            delete temp;
            --size;
        }
    }
    City* getFirstElement(Node* node) {
        if (head != nullptr) {
            Node* temp = head;
            head = head->next;
            City* firstCity = &(temp->value); // Получаем указатель на значение первого элемента
            delete temp; // Освобождаем память, занимаемую узлом (но не сам объект City)
            --size;
            return firstCity;
        }
        return nullptr; // Если список пуст
    }


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

    void assertNoCycles() {
        Node* current = head;
        size_t length = 0;

        while (current) {
            ++length;
            current = current->next;
        }

        assert(length == size && "Cycle detected in the linked list!");
    }
    bool isEmpty(const typename LinkedList<T>::Node* head) {
        return head == nullptr;
    }

};


#define ASDC_SINGLY_LINKED_H

#endif //ASDC_SINGLY_LINKED_H
