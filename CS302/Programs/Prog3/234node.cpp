// Author: Nathan Metens, 907903839
// Instructor: Karla Fant
// Class: cs302-001

#include "234node.h"

// This file implements the 234node.h methods, including
// the insertKey and findKey methods.

node::node(): numChildren(0), numKeys(0)
{
	keys = {nullptr, nullptr, nullptr};
	children.fill(nullptr);
}
node::node(dessert* &data): numChildren(0), numKeys(0)
{
	keys = {data, nullptr, nullptr}; // set the first key to data
	children.fill(nullptr);
}

node::~node()
{ // recursively visit each child and delete leaves:
	for (auto key: keys) {
		if (key) delete key;
		key = nullptr;
	}
	for (auto child_ptr: children) {
		child_ptr = nullptr;
	}
	numChildren = 0;
}

// Insert a new key into the keys vector. Insert only 
// when there is space (2 keys or less):
void node::insertKey(dessert* &key) {
	// can only have 3 keys per node
	if (numKeys == 3) return; 

	// loop through the keys, starting at largest key 
	// and check the key with the incomming key to 
	// determine where it belongs in the vector:
	int key_index = numKeys-1;
	while (key_index >= 0) {
		if (key > keys[key_index]) { // insert key
			keys[key_index +1] = key;
			return;
		}
		--key_index;
	}
}

// Search the keys vector to the matching key and return
// the index that the key is located:
int node::findKey(dessert* key) const {
	int key_index = 0;
	// search for the key in the keys vector:
	while (key_index != numKeys) {
		if (key == keys[key_index]) { // found key	
			return key_index;	
		}
		++key_index;
	}	
	return -1; // key not found (return invalid index)
}

