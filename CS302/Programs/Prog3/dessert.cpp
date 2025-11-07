// Author: Nathan Metens, 907903839
// Instructor: Karla Fant
// Class: cs302-001

#include "dessert.h"
#include "error.h"
#include "rand.h"
#include <vector>
#include <fstream>

using std::string;
using std::cout;
using std::endl;
using std::cin;
using std::ifstream;
using std::vector;

/************************************************************************/
/**************** IceCreamDessert Class Implementation ******************/
/************************************************************************/

IceCreamDessert::IceCreamDessert()
{
	flavor = "Vanilla";
	price = 4.99; // base price for just ice cream
	orderID = 0;
	rating = 0.0;
	review = "none";
}

IceCreamDessert::~IceCreamDessert()
{
	flavor = "none";
	price = 0.0;
	orderID = 0;
	rating = 0.0;
	review = "none";
}

// Base class placeOrder method takes a flavor number from the menu
// and assigns the flavor (string) variable to the corresponding
// ice cream flavor. The ID is used to keep track of each order in the
// data structure:
float IceCreamDessert::placeOrder(int flavorNum, int id)
{
	// assign the flavorNum to its corresponding flavor:
	switch (flavorNum) {
		case 1: 
			flavor = "Vanilla";
			break;
		case 2: 
			flavor = "Chocolate";
			break;
		case 3:
			flavor = "Peanut Butter";
			break;
		case 4:
			flavor = "Cheese Cake";
			break;
		case 5:
			flavor = "Snicker Doodle";
			break;
		case 6:
			flavor = "Cookie Dough";
			break;
		default: // throw bad flavorNum:
			string errorMessage = "Recieved improper flavor number: " + std::to_string(flavorNum);
			Error e(exceptionType::bad_flavorNum, errorMessage);
			throw(e);
			break;
	}

	// assign the orderID and check for bad id variable:
	if (id < 1)
	{
		string errorMessage = "Recieved orderID < 0: " + id;
		Error e(exceptionType::bad_orderID, errorMessage);
		throw(e); // throw bad id exception
	} else orderID = id; // good ID value

	return price;	
}

bool IceCreamDessert::cancelOrder(int orderID)
{
	return true;
}

// Used to rate the dessert. The method takes the review as an argument
// and assigns the this->review variable to the client review. The method
// also prompts the user for a 0-5 star rating, which is saved in the
// class variable:
int IceCreamDessert::writeReview(string review)
{
	this->review = review;
	cout << "How would you rate your dessert? (0-5): ";
	float rating;	
	cin >> rating;
	cin.ignore(100, '\n'); cin.clear();
	if (rating < 0 || rating > 5)
	{ // check rating and throw exception if bad input:
		string errorMsg = "You gave a rating that was outside of the 0-5 scale: " + std::to_string(rating); 
		Error e(exceptionType::bad_rating, errorMsg);
		throw e;
	} else this->rating = rating;
	return 1;
}

// Displays the ice cream flavors in a menu fashion. All derived classes
// call this base class method to start the order because these are
// the ice cream flavors for each derived dessert:
void IceCreamDessert::menu() const
{
	cout << "Dessert Menu: (all flavors are $" << price << ")" << endl;
	cout << "\t(1) Vanilla\n\t(2) Chocolate\n\t(3) Peanut Butter\n\t(4) Cheese Cake\n\t(5) Snicker Doodle\n\t(6) Cookie Dough" << endl;
}

// This method takes a vector and adds all the toppings and fillings 
// from the toppings_fillings.txt file to the vector reference:
void IceCreamDessert::setToppingsFillings(vector<string> &top_fill)
{
	// get all the toppings in the .txt file to display:
	ifstream toppingsFile("toppings_fillings.txt");
	string topping_or_filling; // each topping in the file

	// go through the file and push each topping into the vector:
	while (getline(toppingsFile, topping_or_filling)) top_fill.push_back(topping_or_filling);
	toppingsFile.close();
}

// Returns the orderID of the dessert. This ID is used to order the
// desserts in the 234Tree:
int IceCreamDessert::getOrderID() const { return orderID; }

/************************************************************************/
/******************** Waffle Class Implementation ***********************/
/************************************************************************/

Waffle::Waffle(): type(WaffleType::none)
{ toppings.fill("none"); }

Waffle::~Waffle()
{
	type = WaffleType::none;
	// set each topping to empty string
	for (auto topping: toppings)
		topping = "";
	toppings = {}; // clear all emtpy elems
	tip = 0;
}

// Place order method for the Waffle class first calls the base class
// placeOrder method, then it asks the user to select a waffle type,
// and TOPPINGS number of toppings for their dessert. Exception handling
// is used for all user input to ensure proper variables are set:
float Waffle::placeOrder(int flavorNum, int ID)
{
	// call the base method to set the flavor:
	IceCreamDessert::placeOrder(flavorNum, ID);	

	// ask the user to select a type:
	int typeID = 0;
	while (typeID != 1 && typeID != 2)
	{ // only set the waffle type if correct input is provided:
		cout << "Select a Waffle Type:\n\t(1) Liege $4\n\t(2) Brussels $3\n\t(3) What's the difference?\n";
		cin >> typeID;
		cin.clear();
		cin.ignore(100, '\n'); // clear's buffer if input is incorrect

		if (typeID != 1 && typeID != 2 && typeID != 3)
		{ // create exception to notify user of input error:
			string errorMsg = "You did not select a valid option. Recieved: ";
			errorMsg += std::to_string(typeID) + ". Try again...\n";
			Error e(exceptionType::bad_waffle_type, errorMsg);
			cout << e.what() << endl;
		}
		if (typeID == 3) 	
		{
			cout << "\n";
			info(); // display info if user asks
		}
	}

	// recieved a valid type:
	if (typeID == 1)
	{
		type = WaffleType::Liege;
		price += 4; // add to the total price
	}
	else if (typeID == 2)
	{
		type = WaffleType::Brussels;
		price += 3;
	}

	vector<string> allToppings; // empty toppings vector
	// get the toppings for the waffle:
	setToppingsFillings(allToppings); // base class method

	// ask the user to select toppings:
	cout << "Select up to " << TOPPINGS << " toppings:" << endl;
	int topping_number = 1;
	for (auto topping = allToppings.begin(); 
			topping != allToppings.end(); ++topping)
	{ // display toppings vector:
		// each topping costs $0.99
		cout << "\t(" << topping_number << ") " << *topping << " $0.99\n";
		++topping_number;	
	}

	int numToppings = allToppings.size();
	cout << "\t(" << numToppings + 1 << ") Surprize me!" << endl;
	cout << "\t(-1) No more toppings (Place Order)" << endl;

	// user selected toppings, which are added to the array of 
	// toppings:
	int choice = 0; int toppings_count = 0;
	while (toppings_count != TOPPINGS && choice != -1)
	{
		cout << "You have " << TOPPINGS - toppings_count << " toppings left: ";
		cin >> choice;
		cin.clear(); cin.ignore(100, '\n');

		if (choice != -1 && choice >= 1 && choice <= numToppings+1)
		{ // error checking on choice input:
			if (choice == int(numToppings+1))
			{ // add a random topping
				int randTopping = randomNumber(0, numToppings-1);
				toppings[toppings_count] = allToppings.at(randTopping);
			} 
			else if (choice != -1)
			{
				toppings.at(toppings_count) = allToppings.at(choice-1); 
			}
			++toppings_count;
			price += 0.99; // add one dollar to the price
		} else if (choice != -1) { // create object of Error class and throw exception:
			string errorMsg = "(" + std::to_string(choice) + ") is not one of the topping options. Try again...";
			Error e(exceptionType::bad_topping, errorMsg);
			cout << e.what() << endl;
		}
	}

	return price;
}

// Call base method to display menu:
void Waffle::menu() const { IceCreamDessert::menu(); }

// Display the difference between the Liege and Brussels Waffle types:
void Waffle::info() const
{
	cout << "Liege Waffle: a dough with pearl sugar inside. This waffle originiates in Liege, Belgium and is much thicker than the Brussels Waffle.\nBrussels Waffle: a batter that is much lighter and less sugary than the Liege Waffle. Better for toppings.\n" << endl;
}

bool Waffle::cancelOrder(int ID)
{
	if (orderID == ID) return true;
	return false;
}

// Send review to base class method:
int Waffle::writeReview(string review)
{
	IceCreamDessert::writeReview(review);
	return 1;
}

// Display this class's special display. Display's all the info about
// the dessert the client ordered:
void Waffle::display() const
{
	cout << "\033[33mOrder #" << orderID << ": \033[0m";
	switch (type) { // show the ice cream flavor and waffle selected:
		case WaffleType::Liege:
			cout << flavor << " Ice cream on a Liege Waffle ";
			break;
		case WaffleType::Brussels:
			cout << flavor << " Ice cream on a Brussels Waffle ";
			break;
		default:
			string errorMsg = "You did not select a valid waffle type.";
			Error e(exceptionType::bad_waffle_type, errorMsg);
			throw (e); break;
	}
	// show the toppings:
	cout << "topped with: ";
	int index = 0;
	for (auto topping: toppings)
	{
		if (topping != "none")
		{
			// reached last topping in array:
			if (index == TOPPINGS)
				cout << topping << " "; // no comma at the end
			else if (index+1 != TOPPINGS && toppings[index+1] == "none") 
				cout << topping << " "; // no comma at the end
			else cout << topping<< ", "; // comma separation
			++index;
		}
	}
	cout << "\033[32m Total Price: $" << price << "\033[0m" << endl;
}

// Add adds to the tip jar:
int Waffle::leaveTip(int amount)
{
	tip = amount;
	price += tip;		
	return amount;	
}

/************************************************************************/
/******************** Crepe Class Implementation ************************/
/************************************************************************/

Crepe::Crepe(): fillings({}), length(8) {}

Crepe::~Crepe()
{
	for (auto filling: fillings)
		filling = "none";	
	length = 0;
}

// Call the base class method first to set the string flavor variable
// before getting the detailed order for the Cepe. The Crepe fillings
// are the same as the Waffle toppings, except for this class, they are
// stored in a list:
float Crepe::placeOrder(int flavorNum, int ID)
{
	// use base to set up the flavor:
	IceCreamDessert::placeOrder(flavorNum, ID);

	int length_choice = 0;
	// ask the user for their length of choice:
	cout << "Select length of Crepe Dessert:\n\t(1) small 6 inch\t$2.99\n\t(2) medium 8 inch\t$3.99\n\t(3) large foot long (12 inch)\t$5.50\n";
	cin >> length_choice;
	cin.clear(); cin.ignore(100, '\n');
	
	// check input:
	if (length_choice != 1 && length_choice != 2 && length_choice != 3)
	{
		string errorMsg = "You didn't select a proper length.";
		Error e(exceptionType::bad_length, errorMsg);
		throw(e);
	}
		
	// reacieved good data, assign length variable:
	this->length = length_choice;

	// get the fillings from the file:
	vector<string> allFillings;
	setToppingsFillings(allFillings);

	// ask the user to select fillings
	cout << "Select up to " << FILLINGS << " fillings:" << endl;
	int filling_number = 1;
	for (auto filling = allFillings.begin(); 
			filling != allFillings.end(); ++filling)
	{
		// each filling costs $0.99
		cout << "\t(" << filling_number << ") " << *filling << " $0.99\n";
		++filling_number;	
	}

	int numFillings = allFillings.size();
	cout << "\t(" << numFillings+ 1 << ") Surprize me!" << endl;
	cout << "\t(-1) No more fillings (Place Order)" << endl;

	// get the user's choices:
	int choice = 0; int fillings_count = 0;
	while (fillings_count != FILLINGS && choice != -1)
	{
		cout << "You have " << FILLINGS - fillings_count << " fillings left: ";
		cin >> choice;
		cin.clear(); cin.ignore(100, '\n');

		if (choice != -1 && choice >= 1 && choice <= numFillings+1)
		{ // error checking on choice input:
			if (choice == int(numFillings+1))
			{ // add a random filling to the list of toppings:
				int randFilling = randomNumber(0, numFillings-1);
				fillings.push_back(allFillings.at(randFilling));
			} 
			else if (choice != -1)
				fillings.push_back(allFillings[choice-1]);
			++fillings_count;
			price += 0.99; // add one dollar to the price
		} else if (choice != -1) { // create object of Error class and display error message:
			string errorMsg = "(" + std::to_string(choice) + ") is not one of the filling options. Try again...";
			Error e(exceptionType::bad_filling, errorMsg);
			cout << e.what() << endl;
		}
	}

	return price;
}

bool Crepe::cancelOrder(int ID)
{
	return true;
}

// Review calls base class method:
int Crepe::writeReview(string review)
{
	IceCreamDessert::writeReview(review);
	return 1;
}

// Crepe display method displays the Ice cream flavor, length of
// the crepe, fillings, and the price of the order:
void Crepe::display() const
{
	// determin the size:
	string size;
	if (length == 1)
		size = "6 inch";
	else if (length == 2)
		size = "8 inch";
	else size = "Foot long";

	// print order in reciept manner:
	cout << "\033[33mOrder #" << orderID << ":\033[0m " + size + " " + flavor + " Ice Cream Crepe filled with: ";
	for (list<string>::const_iterator it = fillings.begin();
		it != fillings.end(); ++it)
		cout << *it << ", ";
	
	cout << "\033[32mTotal Price: $" << price << "\033[0m" << endl; 
}

// Display the menu from the base class:
void Crepe::menu() const { IceCreamDessert::menu(); }

/************************************************************************/
/****************** MilkShake Class Implementation **********************/
/************************************************************************/

MilkShake::MilkShake(): size(8), boost("none") {}

MilkShake::~MilkShake()
{
	size = 0;
	boost = "none";
}

// Get the flavor from the base class method, then get the size and 
// set the price for the milkshake: 
float MilkShake::placeOrder(int flavorNum, int ID)
{
	// choose flavor from base class method:
	IceCreamDessert::placeOrder(flavorNum, ID);

	int size;
	cout << "Pick a size:\n\t(1) small 8oz\t$3.99\n\t(2) medium 16oz\t$4.99\n\t(3) large 24oz\t$5.99\n\t(4) Xlarge 32oz\t$6.99\n";
	cin >> size;
	cin.clear(); cin.ignore(100, '\n');
	if (size < 1 || size > 4)
	{ // create bad_size exception
		string errorMsg = "You didn't select a proper size: " + std::to_string(size);
		Error e(exceptionType::bad_size, errorMsg);
		throw(e); // throw bad size exception with proper error message
	}
	
	// assign the size and price:
	this->size = size;
	
	switch (size) {
		case 1:
			price = 3.99;
			break;	
		case 2:
			price = 4.99;
			break;
		case 3:
			price = 5.99;
			break;
		case 4:
			price = 6.99;
			break;
		default:
			string errorMsg = "You didn't select a proper size: " + std::to_string(size);
			Error e(exceptionType::bad_size, errorMsg);
			throw(e); // throw bad size exception with proper error message
			break;
	}
	return price;
}

bool MilkShake::cancelOrder(int ID)
{
	return true;
}

// Call base review method:
int MilkShake::writeReview(string review)
{
	IceCreamDessert::writeReview(review);
	return 1;
}

// Display the base menu method:
void MilkShake::menu() const { IceCreamDessert::menu(); }

// Display the flavor, size, and price of the milkshake:
void MilkShake::display() const
{
	string Size = "";
	switch (size) {
	case 1:
		Size = "Small";
		break;	
	case 2:
		Size = "Medium";
		break;
	case 3:
		Size = "Large";
		break;
	case 4:
		Size = "XLarge";
		break;
	}

	cout << "\033[33mOrder #" << orderID << ":\033[0m " + Size + " " << flavor << " Ice Cream Milk Shake \033[32mTotal Price: $" << price << "\033[0m" << endl; 
}
	
