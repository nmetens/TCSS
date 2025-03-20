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

    last_same_as_first(head); // 1

    int sum = add_sum_to_last(head); // 2
    cout << "The sum of the list is: " << sum << endl;

    int non_two = remove_non_two(head); // 3
    cout << "The non_two node had data: " << non_two << endl;

    // ***************************** // 

    // Final display to see our work on the original list:
    display(head);
    
    return 0;
}
