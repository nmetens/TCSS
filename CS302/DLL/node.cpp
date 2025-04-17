#include "node.h"
#include <iostream>

node::node(): data(0), next(nullptr), previous(nullptr) {}

node::node(int data): data(data), next(nullptr), previous(nullptr) {}

node::~node() {
    data = 0;
    next = previous = nullptr;
}

void node::display() {
    std::cout << data;
}

int node::getData() {
    return data;
}

node * &node::getNext() {
    return next;
}

node * &node::getPrev() {
    return previous;
}

void node::setNext(node * &next) {
    this->next = next;
}

void node::setPrev(node * &previous) {
    this->previous = previous;
}
