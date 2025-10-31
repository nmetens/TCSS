/* Author: Nathan Metens 907903839
 * Instructor: Karla Fant
 * Class: cs302-001
 */

// This is the '.cpp' file but since we are working
// with templates, its a '.tpp' file instead. We 
// implement the template Node class and the template
// DLL class methods here.

/*********************************************/
/***** Node Class Implementation Below *******/
/*********************************************/

// Defualt node constructor setting all data to zero:
template <class TYPE>
Node<TYPE>::Node(): next(nullptr), prev(nullptr) {}

// Copy constructor:
template <class TYPE>
Node<TYPE>::Node(const Node<TYPE> &source):
	data(source.data), next(nullptr), prev(nullptr) {}

// Constructor that takes a data TYPE:
template <class TYPE>
Node<TYPE>::Node(const TYPE & data_to_add):
	data(data_to_add), next(nullptr), prev(nullptr) {}

// Destructor setting data to zero (null):
template <class TYPE>
Node<TYPE>::~Node()
{
	if (next) next = nullptr;
	if (prev) prev = nullptr;
	// the contestant destructor will be called
	// at the end of this Node's destructor scope.
}

// Calls the race method in the Contestant class:
template <class TYPE>
void Node<TYPE>::race() { data.race(); }

template <class TYPE>
Node<TYPE>* &Node<TYPE>::getNext()
{ return next; }

template <class TYPE>
Node<TYPE>* &Node<TYPE>::getPrev()
{ return prev; }

// Gets the data at the node, used later for 
// comparison with the Contestant operators:
template <class TYPE>
TYPE &Node<TYPE>::getData() { return data; }

template <class TYPE>
void Node<TYPE>::setNext(Node* &next)
{ this->next = next; }

template <class TYPE>
void Node<TYPE>::setPrev(Node* &prev)
{ this->prev = prev; }

// Display the data at the current node:
template <class TYPE>
void Node<TYPE>::display() const 
{ cout << data << endl; } // calls << operator on Contestant

/*********************************************/
/***** DLL Class Implementation Below ********/
/*********************************************/

// Defualt constructor:
template <class TYPE>
DLL<TYPE>::DLL(): head(nullptr) {}

// Destructor checks if there is a DLL,
// if so, calls the deleteDLL method (below):
template <class TYPE> // Wrapper for removeDLL method.
DLL<TYPE>::~DLL() { if (head) deleteDLL(head); }

// Public wrapper for deleting the DLL:
template <class TYPE>
void DLL<TYPE>::deleteDLL() { deleteDLL(head); }

// Recursive removal of the entire DLL:
template <class TYPE>
void DLL<TYPE>::deleteDLL(node_ptr &head)
{
	if (!head) return;
	node_ptr temp = head->getNext();
	delete head;
	head = temp;
	deleteDLL(head);
}

// Wrapper method for display all method:
template <class TYPE>
void DLL<TYPE>::display() const { display(head); }

// Recursive display:
template <class TYPE>
void DLL<TYPE>::display(node_ptr curr) const 
{
	if (!curr) return; // reached end of DLL
	curr->display();
	display(curr->getNext());
}

// Insert the data into the DLL (wrapper):
template <class TYPE>
int DLL<TYPE>::insert(TYPE &data) { return insert(data, head); }

// Recursive insert data:
template <class TYPE>
int DLL<TYPE>::insert(TYPE &data, node_ptr &curr)
{
	if (!curr)
	{ // there is no list yet, create the first node:
		curr = new Node<TYPE>(data);
		return 1;
	}
	if (!curr->getNext())
	{ // we are at the last node in the list:
		node_ptr newNode = new Node<TYPE>(data);
		newNode->setPrev(curr);
		curr->setNext(newNode);
		return 1;
	}
	return insert(data, curr->getNext());
}

template <class TYPE>
int insert(TYPE* &data)
{
	return 1;
}

// Wrapper for search and remove
// recursive method that removes
// all nodes of TYPE data in DLL:
template <class TYPE>
int DLL<TYPE>::remove(TYPE data)
{ return remove(data, head); }

// Recursive remove method that
// removes all occurrances of data
// and returns the number of deleted
// items:
template <class TYPE>
int DLL<TYPE>::remove(TYPE data, node_ptr &curr)
{
	if (!curr) return 0; // no list, or reached end
	if (curr->getData() == data) // found match
	{
		// hold onto next and previous nodes:
		node_ptr prevNode = curr->getPrev();
		node_ptr nextNode = curr->getNext();

		delete curr;
	
		// update connections around the deleted node:
		if (prevNode) prevNode->setNext(nextNode);
		if (nextNode) nextNode->setPrev(prevNode);			
		curr = nextNode;
		return remove(data, curr) + 1;
	}
	return remove(data, curr->getNext());
}

// This method sorts the DLL using the Insertion Sort
// algorithm. We run through the unsorted DLL and sort
// each node in a new sorted list, then update the head
// of the unsorted DLL to point to the newly sorted DLL:
template <class TYPE>
void DLL<TYPE>::insertionSort() // wrapper method
{
	if (!head) return; // nothing to sort	
	
	// initialize the sorted list:
	node_ptr sortedList = nullptr;
	// sort the list recursively:
	insertionSort(sortedList, head);
	// remove the unsorted list
	deleteDLL(head); 
	// update head to newly sorted list:
	head = sortedList; 
}

// Method that races each contestant in the DLL:
template <class TYPE>
void DLL<TYPE>::race() // wrapper
{
	race(head);		
}

// Recursive race method:
template <class TYPE>
void DLL<TYPE>::race(node_ptr &curr)
{
	if (!curr) return;
	curr->race();
	race(curr->getNext());	
}

// Display the Contestant at the end of the
// list (wrapper);
template <class TYPE>
void DLL<TYPE>::displayWinner() const
{
	if (!head) return;
	return displayWinner(head);
}

// Recursive method to go to end of DLL to display
// contestant who traveled the longest distance:
template <class TYPE>
void DLL<TYPE>::displayWinner(node_ptr curr) const
{
	if (!curr) return;
	if (!curr->getNext())
	{	 
		cout << curr->getData();
		return;
	}
	return displayWinner(curr->getNext());
}

// This is the recursive method that takes the data
// of each node in the unsorted DLL and passes it to 
// the 'insertInOrder()' method (below), where the data
// is inserted into the new DLL in correct order:
template <class TYPE>
void DLL<TYPE>::insertionSort(node_ptr &sorted, node_ptr curr)
{
	if (!curr) return; // no list or reached end
	insertInOrder(sorted, curr->getData());
	return insertionSort(sorted, curr->getNext());
}

// This method traverses the sorted DLL and places
// the incoming data into a new node that is sorted.
// The new node is properly connected using the next
// and previous pointers:
template <class TYPE>
void DLL<TYPE>::insertInOrder(node_ptr &curr, TYPE data)
{
	if (!curr) 
	{ // no list, create first ordered node:
		curr = new Node<TYPE>(data);
		return;
	}
	if (!curr->getNext() && data > curr->getData())
	{ // reached last node in DLL:
		node_ptr newNode = new Node<TYPE>(data);
		// update connections:
		curr->setNext(newNode);
		newNode->setPrev(curr);	
		return;
	}
	if (data < curr->getData())
	{ // data to insert is smaller than first node:
		node_ptr newNode = new Node<TYPE>(data);
		// update connections:
		newNode->setNext(curr); 
		newNode->setPrev(curr->getPrev()); 
		curr->setPrev(newNode);
		curr = newNode;
		return;
	}
	return insertInOrder(curr->getNext(), data);
}
