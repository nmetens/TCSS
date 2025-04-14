#include "node.h" 
#include <iostream>

node::node(): data(0), next(nullptr) {}

node::node(const node &src_node): data(src_node.data), next(nullptr) {}

// Insert data
node::node(int data): data(data), next(nullptr) {} 

node::~node() {
    data = 0;
    next = nullptr;
}

void node::display() {
    std::cout << data;
}

int node::getData() {
    return data;
}

node *& node::getNext() {
    return next;
}

void node::setNext(node * &next) {
    this->next = next;    
}
