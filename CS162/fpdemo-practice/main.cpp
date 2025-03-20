/* This is the main program that uses the functions
 * in the node header file to build a linear linked
 * list, perform operations on it, and display the
 * result.
 */

#include "node.h"
#include <iostream>
using namespace std;

int main() {

    node * head = nullptr;
    build(head);
    display(head);




    display(head);
    
    return 0;
}
