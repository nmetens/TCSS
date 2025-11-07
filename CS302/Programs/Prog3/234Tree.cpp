// Author: Nathan Metens, 907903839
// Instructor: Karla Fant
// Class: cs302-001

#include "234Tree.h"
#include <iostream>
using std::cout;

// This is the BTree implementation file where all the
// methods are created.

BTree::BTree(): root(nullptr) {}
// Destructor calls deleteTree method below it:
BTree::~BTree() { if (root) deleteTree(root); }
// Delete all the nodes in the tree recursively calling
// the method with all the children in each node. Used
// by the destructor:
void BTree::deleteTree(node* &curr)
{	
	if (!curr) return;
	for (auto child: curr->children) // traverse children
		deleteTree(child);
	for (auto key: curr->keys) // delete all keys
		if (key) delete key;
	delete curr; // delete current leaf
}

// Check if there is a tree, if so, recusively traverse
// each node and display all non-null keys:
void BTree::display() const { if (root) display(root); }
void BTree::display(node* curr) const
{
	if (!curr) return;
	for (int i = 0; i < curr->numKeys; ++i) 
	{
		// recursively traverse each child pointer:
		display(curr->children[i]);
		if (curr->keys[i] != nullptr) // print non-zero keys
		{
			curr->keys[i]->display();
			cout << "\n";
		}
	}
	display(curr->children[curr->numKeys]);
}

// Wrapper insert method. Checks if the root is null. If so
// create a new one, otherwise recursively insert:
void BTree::insert(dessert* &data) 
{ 
	// When there is no tree, no root, we start here:
	if (!root) // no root
	{ // create the first node
		root = new node(data);
		++root->numKeys;
		return;
	}
	insert(data, root, root); // we already have a root
}
// This was the hard part. I comment liberally in order
// to explain my thoughts through this method, as well as
// so that I can remember why I did certain things the way
// I did:
void BTree::insert(dessert* &data, node* &parent, node* &curr)
{
	// When the current Node is a leaf that is not filled,
	// we first fill the keys in order before a split:
	if (curr->numChildren == 0 && curr->numKeys < 3) 
	// the node is NOT filled yet:
	{ // this method ensures the keys remain in order.
		// start comparing keys from right to left:
		int key_i = curr->numKeys -1; // key index
		// go until first key in node
		while (key_i >= 0 && data->getOrderID() < curr->keys[key_i]->getOrderID()) 
		{
			// compare the incoming data to each
			// key in the keys array:
			if (data < curr->keys[key_i])
			{ // if the incoming data is smaller
				// than the key, move the key
				// up to the next index.
				curr->keys[key_i + 1] = curr->keys[key_i];
			}
			--key_i; // move from right to left
		}
		// insert the data at the correct position
		// that keeps the current node's keys
		// in order (ascending order):
		curr->keys[key_i + 1] = data;	
		// update the numKeys:
		++curr->numKeys;
		return; 
	}
	// When a node is full and we try to add a new key,
	// we must perform a split:
	if (curr->numKeys == 3 && curr->numChildren == 0) // the node is full and it is a leaf.
	{
		// first we find where the data "should" go
		// if there was enough space:
		bool inserted = false;
		for (int i=0; i<int(curr->keys.size()) && !inserted; ++i)
		{ // put all 4 keys in order:
			if (data->getOrderID() < curr->keys[i]->getOrderID())
			{
				curr->keys.insert(curr->keys.begin() + i, data);
				inserted = true;
			}
			else if (i + 1 == static_cast<int>(curr->keys.size())) 
			{ // reached end of keys
				curr->keys.push_back(data);
				inserted = true;
			}
		}
		// once we have all the keys in order, it's
		// time to split the node:
		dessert* middleKey = curr->keys[1]; // {0, 1, 2, 3}

		if (parent == curr) 
		{ 
			// the root is being split:
			node* newRoot = new node(middleKey);
			delete curr->keys[1];
			curr->keys[1] = nullptr; // reset key that was moved
			newRoot->numKeys = 1;

			// add the two bigger keys to the right node:
			node* rightChild = new node(curr->keys[2]);
			delete curr->keys[2];
			curr->keys[2] = nullptr; // reset the key
			rightChild->keys[1] = curr->keys[3];
			delete curr->keys[3];
			curr->keys[3] = nullptr; // reset the key
			rightChild->numKeys = 2;
			curr->numKeys -= 2;
		
			// now connect the nodes:
			newRoot->children[0] = curr;
			curr->keys.pop_back(); // remove the extra key
			newRoot->children[1] = rightChild;
			curr = newRoot; // update the current root
			curr->numChildren = 2;
			return;
		} // another node is being split:
		else if (parent != curr && parent->numKeys < 3) 
		{ 
			// there's space for the split node in parent
			parent->insertKey(middleKey);
			++parent->numKeys;
			// find where the middle key is inserted:
			int middleKeyIndex = parent->findKey(middleKey);
			// now add a right node to the middle key and populate its larger values:
			parent->children[middleKeyIndex + 1] = new node(curr->keys[2]);
			++parent->children[middleKeyIndex + 1]->numKeys; // increment right node key num
			parent->children[middleKeyIndex + 1]->insertKey(curr->keys[3]); // add largest
			++parent->children[middleKeyIndex + 1]->numKeys; // increment right node key num

			++parent->numChildren; // right node adds a child to parent next pointers
		
			// clear the current node of the moved values caused by the split:
			curr->keys.pop_back(); // remove the added 4th key before the split
			for (int i=1; i <curr->numKeys+1; ++i) 
			{
				if (curr->keys[i]) delete curr->keys[i];
				curr->keys[i] = nullptr;
				--curr->numKeys;
			}
			return;
		}
	}
	else { // we haven't reached a leaf node, recrusively
		// traverse down the tree until we find the
		// correct spot for the incomming data:
		
		// the data is larger than the biggest key:
		if (data >= curr->keys[curr->numKeys-1])
			// pass the current node (parent) and the child node
			return insert(data, curr, curr->children[curr->numKeys]); 
		else {
			// if the data is node larger than the
			// biggest key in the current node,
			// then compare it with the smaller
			// nodes:
			for (int i=0; i < curr->numKeys; ++i)
			{
				if (data < curr->keys[i]) 
					return insert(data, curr, curr->children[i]);		
			}
		}
	}
}
