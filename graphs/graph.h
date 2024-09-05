//
// Created by Vica on 27.03.2024.
//

#ifndef ASDC_GRAPH_H
#define ASDC_GRAPH_H

#include <array>
#include <queue>
#include <stack>

static inline const int MAX_NEIGHBOR_COUNT = 3;
struct Node_Graph {
    bool visited;
    int value;
    std::array<Node_Graph *, MAX_NEIGHBOR_COUNT> neighbors;
};

Node_Graph *createGraph() {
    Node_Graph *node1 = new Node_Graph;
    node1->value = 1;
    node1->visited = false;


    Node_Graph *node2 = new Node_Graph;
    node2->value = 2;
    node2->neighbors = {};
    node2->visited = false;

    Node_Graph *node3 = new Node_Graph;
    node3->value = 3;
    node3->neighbors = {};
    node3->visited = false;

    Node_Graph *node4 = new Node_Graph;
    node4->value = 4;
    node4->visited = false;

    node1->neighbors[0] = node2;
    node1->neighbors[1] = node3;
    node1->neighbors[2] = node4;

    node2->neighbors[0] = node1;
    node2->neighbors[1] = node3;

    node3->neighbors[0] = node1;
    node3->neighbors[1] = node2;
    node3->neighbors[2] = node4;

    node4->neighbors[0] = node1;
    node4->neighbors[1] = node3;
    node4->neighbors[2] = nullptr;

    return node1;
}
void resetVisitedFlags(Node_Graph *node) {
    if (node == nullptr) return;
    node->visited = false;

    for (Node_Graph *neighbor : node->neighbors) {
        if (neighbor != nullptr && neighbor->visited) {
            resetVisitedFlags(neighbor);
        }
    }
}

void bfs(Node_Graph *node) {
    if (node == nullptr) return;
    resetVisitedFlags(node);
    std::queue<Node_Graph *> q;
    node->visited = true;
    q.push(node);

    while (!q.empty()) {
        Node_Graph *current = q.front();
        q.pop();
        std::cout << current->value << " ";

        for (Node_Graph *neighbor: current->neighbors) {
            if (neighbor != nullptr && !neighbor->visited) {
                neighbor->visited = true;
                q.push(neighbor);
            }
        }
    }
    std::cout << std::endl;
}

void dfs(Node_Graph *node) {
    if (node == nullptr) return;
    resetVisitedFlags(node);
    std::stack<Node_Graph *> stack;
    stack.push(node);

    while (!stack.empty()) {
        Node_Graph *currentNode = stack.top();
        stack.pop();

        if (!(currentNode->visited)) {
            std::cout << currentNode->value << " ";
            currentNode->visited = true;

            for (Node_Graph *neighbor: currentNode->neighbors) {
                if (neighbor != nullptr && currentNode->visited) {
                    stack.push(neighbor);
                }
            }
        }
    }
}


int sumNeighborValues(Node_Graph *node) {
    int sum = 0;
    for (Node_Graph *neighbor: node->neighbors) {
        if (neighbor != nullptr) {
            sum += neighbor->value;
        }
    }
    return sum;
}

void free_memory(Node_Graph *node) {
    delete node->neighbors[0];
    delete node->neighbors[1];
    delete node->neighbors[2];
    delete node;
}

void printNeighborsValue(Node_Graph *node) {
    for (size_t i = 0; i < MAX_NEIGHBOR_COUNT; i++) {
        Node_Graph *neighbor = node->neighbors[i];
        if (neighbor != nullptr) {
            std::cout << neighbor->value << " ";
        }
    }
    std::cout << std::endl;

}

#endif //ASDC_GRAPH_H
