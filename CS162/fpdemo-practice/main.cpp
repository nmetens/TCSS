/* This is the main program that uses the functions
 * in the node header file to build a linear linked
 * list, perform operations on it, and display the
 * result.
 */

#include "node.h"
#include <iostream>
using namespace std;

int main() {

    // Building and displaying the list:
    node * head = nullptr;
    build(head);
    display(head);

    // ***************************** // 
    // Practice functions here:

    last_same_as_first(head);
    int sum = add_sum_to_last(head);
    cout << "The sum of the list is: " << sum << endl;


    // ***************************** // 

    // Final display to see our work on the original list:
    display(head);
    
    return 0;
}
