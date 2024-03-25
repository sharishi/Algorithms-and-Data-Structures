//
// Created by Vica on 21.03.2024.
//
#ifndef ASDC_BINARY_TREE_H
#define ASDC_BINARY_TREE_H
#include <iostream>
#include <vector>
#include <array>
#include "../info.h"


using std::cout;
using std::endl;
using std::string;
using std::vector;
#pragma once

struct BSTreeNode {
    City city;
    struct BSTreeNode* left{};
    struct BSTreeNode* right{};
    BSTreeNode(const City& c) : city(c), left(nullptr), right(nullptr) {}
};

void insertNode(BSTreeNode*& root, const City& c) {
    if (root == nullptr) {
        root = new BSTreeNode(c);
    }
    else {
        if (c.id < root->city.id)
            insertNode(root->left, c);
        else
            insertNode(root->right, c);
    }
}

BSTreeNode* findNode(BSTreeNode* root, size_t cityId) {
    if (root == nullptr) return nullptr;

    if (cityId == root->city.id)
        return root;
    else if (cityId < root->city.id)
        return findNode(root->left, cityId);
    else
        return findNode(root->right, cityId);
}

void printNode(BSTreeNode* n) {
    if (n != nullptr) {
        std::cout << "City found: " << n->city.id << std::endl <<
                  "Name: " << n->city.name.data() << std::endl;
    }
    else {
        cout << "Not a valid node!" << endl;
    }
}

void deleteTree(BSTreeNode* root) {
    if (root == nullptr) return;

    deleteTree(root->left);
    deleteTree(root->right);

    delete root;
}


#endif //ASDC_BINARY_TREE_H
