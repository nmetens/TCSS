
#include "DLL.h"
#include <iostream>

DList::DList(): head(nullptr), tail(nullptr) {}

DList::DList(const DList &src_list): head(nullptr), tail(nullptr) {

}

DList::~DList() {
    while (head) {
        node * temp = head->getNext();
        delete head;
        head = temp;
    }
}

void DList::display() {
    display(head);
    std::cout << "\n";
}

int DList::insert(int data) {
    if (!head) {
        head = new node(data);
        tail = head;
    } else {
        node * temp = new node(data);
        tail->getNext() = temp;
        temp->getPrev() = tail;
        tail = temp;
    }
    return 1;
}

void DList::display(node * head) {
    if (!head) return;
    head->display();
    std::cout << " ";
    display(head->getNext());
}

void DList::display_backwards() {
    display_backwards(tail);
    std::cout << "\n";
}

void DList::display_backwards(node * tail) {
    tail->display();
    std::cout << " ";
    display_backwards(tail->getPrev());
}
