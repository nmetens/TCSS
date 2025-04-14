
#include "LLL.h"
#include <iostream>

List::List(): head(nullptr) {}

List::List(const List &src_list): head(nullptr) {

}

List::~List() {
    while (head) {
        node * temp = head->getNext();
        delete head;
        head = temp;
    }
}

void List::display() {
    display(head); 
    std::cout << "\n";
}

void List::display(node * head) {
    if (!head) return;
    head->display();
    std::cout << " ";
    display(head->getNext());
}

int List::insert(int data) {
    return insert(data, head); 
}

int List::insert(int data, node * &head) {
    if (!head) {
        head = new node(data);
        return 0;
    }
    return 1 + insert(data, head->getNext());
}
