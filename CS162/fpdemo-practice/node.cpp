/* This is the implementation file for all
 * the functions in the node.h file.
 */

#include "node.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

// Build the linear linked list.
void build(node * &head) {

    srand(time(nullptr)); // Create the random seed.

    // Initialize a random linear linked list (LLL) length between 5 and 15:
    int length = rand() % 15 + 5;

    // Create the first node in the list:
    head = new node;
    head -> data = rand() % 50 + 1;
    head -> next = nullptr;

    // Pointer used to travel the list and add new nodes:
    node * current = head;

    for (int i = 0; i < length; ++i) {
        // Create a new node:
        current -> next = new node;

        // Become the newly created node:
        current = current -> next;

        // Initialize the new node's data:
        current -> data = rand() % 50 + 1; // Random number between 1 and 50.
        current -> next = nullptr;
    }
}

// Display the list.
void display(node * head) {
    // Iterative solution first:
    cout << "****" << endl;
    cout << "The current list:\n";
    while (head) {
        cout << head -> data;
        if (head -> next != nullptr) cout << " -> ";
        head = head -> next;
    }
    cout << "\n****" << endl;
}
