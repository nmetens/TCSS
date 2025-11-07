#ifndef NODE234_H
#define NODE234_H

// Author: Nathan Metens, 907903839
// Instructor: Karla Fant
// Class: cs302-001

#include "dessert.h"
#include <array>
#include <vector>
using std::array;
using std::vector;

// This is the node class for the 234 Tree. The node class
// has a default constructor that can initialize a new node
// with a key. Each node has a method to insert a new key in
// order with the other keys and find a key.
// The keys are stored in a vector and the next "child" ptrs
// are stored in an array:
class node
{
	public: 
		typedef IceCreamDessert dessert;

		// All the data is public for the 234node
		// class because the 234Tree class handles all
		// of data publicly:
		node();
		node(dessert* &data);
		~node();

		// main node methods:
		void insertKey(dessert* &key);
		int findKey(dessert* key) const;

		// the data for each node is a pointer to a
		// dessert base class to allow for upcasting:
		vector<dessert*> keys; // holds the nodes data
		// holds the nodes next ptrs:
		array<node*, 4> children; 
		
		// keep track of the number of keys and ptrs:
		int numChildren; // maximum 4
		int numKeys; // maximum 3
};

#endif //NODE234_H
