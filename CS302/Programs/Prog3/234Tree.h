#ifndef TREE234_H
#define TREE234_H

// Author: Nathan Metens, 907903839
// Instructor: Karla Fant
// Class: cs302-001

#include "234node.h"

// This is the 234Tree (BTree) class header file. The methods
// for this class are the basic insert, display, and delete
// all methods. The private data consists of a pointer to
// a 234node and the recursive methods.

class BTree // Balanced Tree
{
	public:
		typedef IceCreamDessert dessert;

		BTree();
		~BTree();

		// wrapper methods for:
		void insert(dessert* &data);
		void display() const;
	
	private:
		node* root;

		// recursive methods for insert,
		// display, and delete:
		void insert(dessert* &data, node* &parent, node* &curr);
		void deleteTree(node* &curr);
		void display(node* curr) const;
};

#endif // TREE234_H
