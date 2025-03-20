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

// 3. Remove the first node that isn't a 2
int remove_non_two(node * &head) {
    
    /* Case 1: There is no list (empty list) */
    if (head == nullptr) return 0;

    node * current = head; // Initialize a traversal pointer.
    node * previous = head; // Initialize a previous pointer to be the node behind current.

    // Travel the list untile either we reach the end, or the data at the current node is 2:
    while (current != nullptr && current -> data == 2) {
        previous = current; // Keep previous one node behind current.
        current = current -> next; // Traverse current to the next node.
    }

    /* Case 2: List is all 2's */
    // Now check that current is not nullptr (the first option after exiting the loop:
    if (!current) return 0; // We reached the end and every item in the list was a 2 (not likely, but possible).

    /* Case 3: The first node's data is non_two, here, both previous and current are pointing to the same node (the first one) */
    if (previous == current) {
        // We need to make head  equal to the current node's next node:
        head = current -> next;
        int data = current -> data; // Grab the current node's data.
        delete current; // Delete the non_two node.
        return data; // Return the non_two data. This return will end the function, no code after this will execute.
    }

    /* Case 4: The first non_two is somewhere in the middle */
    // Since we are not at the end of the list, we remove the current node since it has a non-2 value:
    int data = current -> data; // Hold onto the data at the current node (not a two).

    previous -> next = current -> next; // Connect the previous node's next to be the node after current (could be nullptr).
    delete current; // Remove the current node.
    return data; // Return the data that current had.
}

// 4. Remove the last node
int remove_last(node * &head);

// 5. Remove the last node but only if it isn't the same as the first
int remove_last_if_not_first(node * &head);

// 6. Move the first node and put it at the end of the list
int remove_first_place_at_last(node * &head);

// 7. Swap the data in the first and last nodes
int swap_first_last_data(node * &head);

// 8. Swap the first and last NODEs
int swap_first_and_last_node(node * &head);
