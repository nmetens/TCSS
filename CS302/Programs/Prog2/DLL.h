#ifndef DLL_H 
#define  DLL_H
/* Author: Nathan Metens 907903839
 * Instructor: Karla Fant
 * Class: cs302-001
 */

// This is the '.h' file for the template Node
// and template DLL classes. All the methods
// for these classes are implemented in the
// DLL.tpp file.

#include <iostream>
#include <memory>

using std::unique_ptr;
using std::cout; using std::endl;

// This is the Node class. It has a typedef to
// simplify the code (node_ptr instead of Node<TYPE>*.
// This class has next and previous pointers to other
// Nodes and a TYPE data variable for Contestant objects.
// There are getters and setters for the next and prev
// pointers, as well as a getter for the data so that
// we don't need to implement compare functions for
// each of the overloaded operators in the Contestant
// hierarchy.
template<class TYPE>
class Node
{
	public:
		typedef Node<TYPE>* node_ptr;

		Node<TYPE>();
		Node<TYPE>(const TYPE &data);
		Node<TYPE>(const Node<TYPE> &source);
		~Node();
		
		void race(); // calls Contestant race method

		// getters:
		node_ptr &getNext();
		node_ptr &getPrev();
		TYPE &getData();
		
		// setters:
		void setNext(node_ptr &next);
		void setPrev(node_ptr &prev);

		void display() const;

	private:
		TYPE data;
		node_ptr next;
		node_ptr prev;
};

// This is the DLL class. There is also a typedef that
// is the same as in the Node class. This class has display,
// insert, remove, and insertionSort public wrapper methods
// and their respective recursive methods in the private section.
// There is a Node pointer that is the head of the list. I decided
// NOT to implement a tail pointer for this class.
template<class TYPE>
class DLL
{
	public:
		typedef Node<TYPE>* node_ptr;

		DLL();
		~DLL();

		// public wrappers:
		void display() const;
		int insert(TYPE &data); // pass by ref so cc doesn't
					// get called for the Horse objects
		int insert(TYPE* &); // for creating new
				     // Contestant objects
		int remove(TYPE data);
		void insertionSort();
		void deleteDLL();
		
		void race(); // wrapper method for racing
		void displayWinner() const;

	private:
		node_ptr head;	

		// private recursive methods:
		void display(node_ptr) const;
		void displayWinner(node_ptr) const;
		void deleteDLL(node_ptr &);
		int insert(TYPE &data, node_ptr &);
		int remove(TYPE data, node_ptr &);

		// insertion sort methods:
		void insertionSort(node_ptr &sorted, node_ptr curr);
		void insertInOrder(node_ptr &, TYPE data);
		
		// recursive race method that races each contestant:
		void race(node_ptr &);
};

#include "DLL.tpp"
#endif
