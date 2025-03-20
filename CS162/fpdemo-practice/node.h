/* This is the header file that contains the node struct
 * and the function prototypes for the linear linked list.
 */

struct node {
    int data;
    node * next;
};

// Build the linear linked list.
void build(node * &head);

// Display the list.
void display(node * head);
