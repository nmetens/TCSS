/* This is the header file that contains the node struct
 * and the function prototypes for the linear linked list.
 */

struct node {
    int data;
    node * next;
};

// The build and display methods are already provided 
// for you and are usually in the "*.o" file, but you 
// can access them in the "build.cpp" file.

// Build the linear linked list.
void build(node * &head);

// Display the list.
void display(node * head);

// Below are the practice methods that will help you
// prepare for the final proficiency demo:

/* 
 * 1. Add a new node to the end of a LLL with the same value as the first node
 * 2. Sum all of the data in a LLL and add a new node to the end with this value
 * 3. Remove the first node that isn't a 2
 * 4. Remove the last node
 * 5. Remove the last node but only if it isn't the same as the first
 * 6. Move the first node and put it at the end of the list
 * 7. Swap the data in the first and last nodes
 * 8. Swap the first and last NODEs
 */

// 1. Add a new node to the end of a LLL with the same value as the first node
void last_same_as_first(node * &head);

// 2. Sum all of the data in a LLL and add a new node to the end with this value
int add_sum_to_last(node * &head);
