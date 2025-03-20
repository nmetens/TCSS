/* This is the implementation file for all
 * the functions in the node.h file.
 */

#include "node.h"
#include <iostream>

using namespace std;

// 1. Add a new node to the end of a LLL with the same value as the first node
void last_same_as_first(node * &head) { // Pass head by reference since we are changing the list (adding to it).

    if (head == nullptr) return; // Case 1: No list.

    // Since we have a list, we have at least one node, so we can create a pointer for traversal.
    node * current = head; 

    // Travel the list until we are the last node.
    while (current -> next) 
        current = current -> next;

    // We have reached the last node, now we create a new node and add whatever data is at the head:
    current -> next = new node; // Create new node (the last node).
    current = current -> next; // Become the last node.
    current -> data = head -> data; // Copy the head's data into the last node's data.
    current -> next = nullptr; // End the list with the last node pointing to null.
}

// 2. Sum all of the data in a LLL and add a new node to the end with this value
int add_sum_to_last(node * &head) { // Return the sum.

    // Iterative solution:
    int sum = 0; // Create a sum.

    if (head == nullptr) return sum; // Case 1: No list, nothing to sum, return sum == 0.

    node * current = head; // Create the traveling pointer.

    // Traverse the entire list, adding the data at each node to the total sum:
    while (current -> next) {
        sum += current -> data; // Add the data at each node to the sum.
        current = current -> next; // Become the next node.
    }

    // We reached the last node.
    current -> next = new node; // Create a new last node.
    current = current -> next; // Become the last node.
    current -> data = sum; // Make the data equal to the sum of all the nodes in the list.
    current -> next = nullptr; // Terminate the list.

    return sum; // Return the sum.
}
