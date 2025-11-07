// Author: Nathan Metens, 907903839
// Instructor: Karla Fant
// Class: cs302-001

// This is the main client program. The entire program is inside
// a try block because the core dessert hierarchy uses 
// exception handling to ensure the user provides correct
// input. The 234 Tree is also initialized here. The use of
// unique pointers is for the pointer to the base class.
// This base class unique pointer is initialized to a derived
// class dessert object chosen by the user. That unique 
// pointer is then passed into the insertion method of the
// 234 tree where raw pointers are used for the rest of the
// implementation.

#include "dessert.h"
#include "error.h"
#include "234Tree.h"
#include <memory>

using std::cout;
using std::cin;
using std::endl;
using std::unique_ptr;

int main()
{

	// Try block for possible errors when creating objects of
	// the IceCreamDessert hierarchy:
	try { 
		// create the 234 Tree object that will store all
		// of the desserts that are ordered:
		BTree tree;

		int orderID = 1; // keep track of all the order IDs
		// ask each user to select a dessert, stop when asked:
		int dessertChoice = 4;
		while (dessertChoice != 0) 
		{
			// chose the dessert:
			cout << "Select a Dessert (1) Waffle (2) Crepe (3) MilkShake | (4) Display Desserts Ordered (0) EXIT: ";	
			cin >> dessertChoice;
			cin.clear(); cin.ignore(100, '\n');

			// check erroneous input:
			if (dessertChoice != 0 &&dessertChoice != 1 && 
				dessertChoice != 2 && dessertChoice != 3 && dessertChoice != 4)
			{
				string errorMsg = "You didn't select a Dessert on the Menu.";
				Error e(exceptionType::bad_dessert, errorMsg);
				throw(e);
			}

			// display the 234 Tree desserts by orderID:
			if (dessertChoice == 4) tree.display();

			// create a new dessert:
			else if (dessertChoice != 0)
			{ // customer did not choose EXIT

				// create an object of the dessert hierarchy to display the menu:
				Waffle obj;
				obj.menu();

				// start the order:
				int flavor;
				cout << "Enter a flavor: "; 
				cin >> flavor;
				cin.clear();

				// create the correct dessert obj, and use the base class
				// ptr to access the derived dessert obj:
				if (dessertChoice == 1) 
				{
					// Use of unique pointers:
					unique_ptr<IceCreamDessert> d_ptr(new Waffle); // create new derived obj
					d_ptr->placeOrder(flavor, orderID); // use base ptr to access
				
					int tip_amount = 0;
					cout << "\nPlease enter a tip amount: ";
					cin >> tip_amount; cin.ignore(100, '\n'); cin.clear();	
					if (tip_amount < 0)
					{
						string errorMsg = "Invalid tip.";
						Error e(exceptionType::bad_tip, errorMsg);
						throw(e);
					}
					// Use of RTTI for a method in the derived class that is NOT defined in the base
					// convert a base class pointer to a derived class pointer:
					Waffle* waffle_ptr = dynamic_cast<Waffle*>(d_ptr.release()); // convert unique to raw
					// check that the conversion was successfull and call the derived method that is
					// not defined in the base class:
					if (waffle_ptr) waffle_ptr->leaveTip(tip_amount);
					
					IceCreamDessert* dessert = waffle_ptr;
					tree.insert(dessert); // pass in the base pointer by ref to 234 tree
				}
				else if (dessertChoice == 2)
				{
					unique_ptr<IceCreamDessert> dessert(new Crepe);
					dessert->placeOrder(flavor, orderID); // use orderID 

					IceCreamDessert* d_ptr = dessert.release();
					tree.insert(d_ptr);
				}
				else if (dessertChoice == 3)
				{
					unique_ptr<IceCreamDessert> dessert(new MilkShake);
					dessert->placeOrder(flavor, orderID);

					IceCreamDessert* d_ptr = dessert.release();
					tree.insert(d_ptr); // convert back to raw pointer for 234 tree insert
				}
			}
			++orderID; // onto the next order
		}

		// Single catch block catches all errors and displays
		// unique message:
	} catch (Error e) { cout << e.what() << endl; }

	return 0;
}
