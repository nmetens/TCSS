#include <iostream>
using namespace std;

int main() {
    
    // Create a pointer to an int:
    int number = 5;
    int * ptr = &number;

    // number is an integer data type, and it holds the value 5:
    cout << "number: " << number << endl; // number: 5

    // What is the address of number?
    cout << "&number: " << &number << endl; // The address in memory of number, something like this: 0x16fd2b4b8

    // ptr is a "pointer to an integer", and it holds the address of number:
    cout << "ptr: " << ptr << endl; // number: 0x16fd2b4b8

    // What is the address of ptr? Remember, ptr is also a variable, so it must be stored in memory too.
    // The value that ptr holds in its memory location is the memory address of number, while number holds the 
    // value 10.
    cout << "&ptr: " << &ptr << endl; // Address in memory of ptr, something like this: 0x16f80f4b0

    // Change the value of number through derefencing the pointer: (BECOME the variable at the address)
    *ptr += 5; // We are now changing the value of number through the pointer.

    /** "*ptr" == "number" ** These two are the same value, doing "*ptr += 5" is the same as doing "number += 5" */

    cout << "number: " << number << endl; // number: 10
    cout << "*ptr: " << *ptr << endl; // *ptr: 10

    // Pointers can point to any PRIMITIVE data type: char, int, bool, double, float.
    // Pointers can also point to ANY USER CREATED DATA TYPE!

    // If you create a struct or a class, pointers can also point to those types.

    struct node {
        int data;
    };

    // Create an object of the data type "node":
    node myNode;

    // Change the data inside myNode:
    myNode.data = 5; // Using the direct member access operator "." to access variables inside a struct.

    cout << "myNode.data: " << myNode.data << endl; // myNode.data: 5

    // Now create a pointer to a node, that holds the address of the variable myNode:
    node * node_ptr = &myNode;

    cout << "(*node_ptr).data: " << (*node_ptr).data << endl; // What will this be? 


    return 0;
}
