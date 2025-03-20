/* This is the implementation file for the build
 * and display methods. These functions usually are
 * hidden inside the "*.o" file but are here to give
 * you an idea of how they are implemented.
 */

#include "node.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

// Build the linear linked list.
void build(node * &head) { // Passing by reference, we have the real head.

    srand(time(nullptr)); // Create the random seed.

    // Initialize a random linear linked list (LLL) length between 5 and 15:
    int length = rand() % 15 + 5;

    // Create the first node in the list:
    head = new node;
    head -> data = rand() % 50 + 1;
    head -> next = nullptr;

    // Pointer used to travel the list and add new nodes since
    // we want to keep head pointing to the front of the list:
    node * current = head; // Never change head, create a helper pointer to do the work.

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
void display(node * head) { // Passing by "value", this head is a copy of the real head.
    // Iterative solution first:
    cout << "****" << endl;
    cout << "The current list:\n";

    while (head) {
        // Display the number:
        cout << head -> data;
        if (head -> next != nullptr) cout << " -> ";

        // Traverse the list with the copy of head.
        head = head -> next;
    }

    cout << "\n****" << endl;
}
