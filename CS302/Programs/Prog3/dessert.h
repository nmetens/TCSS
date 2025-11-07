#ifndef DESSERT_H
#define DESSERT_H

// Author: Nathan Metens, 907903839
// Instructor: Karla Fant
// Class: cs302-001

// This is the .h file for the dessert hierarchy.
// The base class is the IceCreamDessert class, which
// is an abstract base class (ABC) as it has one pure
// virtual method (display) and is the virtual hub in
// the hierarchy for its derived classes: Waffle, Crepe,
// and MilkShake. All the methods in the base class are
// the same in the derived classes for dynamic binding.
// The Waffle class is the only class with a different method
// to allow for RTTI (leaveTip()).

#include <string>
#include <array>
#include <list>
#include <vector>

using std::string; // used in all classes
using std::array; // used in Waffle class
using std::list; // used in Crepe class
using std::vector; // used to get toppings_fillings.txt

static const int TOPPINGS{4}; // Total toppings allowed per order
static const int FILLINGS{3}; // Total fillings allowed for Crepe Objects

// This is the base class. It has a virtual destructor, and 4
// virtual methods to allow for dynamic binding. These 4 virtaul
// methods are the same for all the derived classes (same return
// type, same name, and same signature). This base class keeps track
// of all the similar data within the hierarchy. Each derived class
// is an IceCreamDessert plus more, they all have a flavor, price,
// orderID, and a rating.
class IceCreamDessert // ABC
{
	public:	
		IceCreamDessert();
		virtual ~IceCreamDessert();

		// Similar Methods:
		virtual float placeOrder(int flavorNum, int ID);
		virtual bool cancelOrder(int ID);
		virtual int writeReview(string review);
		virtual void menu() const;
		virtual void display() const = 0; // pure virtual
		int getOrderID() const;

	protected:
		string flavor; // flavors are in flavors.txt
		float price;
		int orderID; // used to organize each object
		float rating; // used in writeReview method
		string review;

		void setToppingsFillings(vector<string> &);
};

enum class WaffleType { none, Liege = 1, Brussels };

// This is the Waffle derived class. It has all the same
// methods that are declared virtual in the IceCreamDessert
// base class, plus it had a 'leaveTip()' method to allow for
// RTTI. There are two types of waffles, as shown in the enum 
// above. This class has a tip variable and an array that holds
// a total of TOPPINGS toppings (TOPPINGS is a constant varaible
// declared above):
class Waffle: public IceCreamDessert
{
	public:
		Waffle();
		~Waffle();	
	
		// Similar methods to allow for dynamic binding:
		float placeOrder(int flavorNum, int ID);
		bool cancelOrder(int ID);
		int writeReview(string review);
		void menu() const;
		void display() const;
	
		// Separate method not similar in base class:
		int leaveTip(int amount); // RTTI
	
	private:
		WaffleType type;
		// toppings are found in the toppings&fillings.txt file:
		array<string, TOPPINGS> toppings; // TOPPINGS init above
		int tip;

		void info() const; // used in placeOrderMethod
};

// This is another derived IceCreamDessert class. This class has all
// the same methods as the ABC. It's data consists of an STL list
// of fillings for each Crepe object, as well as the length of the 
// crepe (similar to foot long and 6inch at Subway):
class Crepe: public IceCreamDessert
{
	public:
		Crepe();
		~Crepe();

		// Self similar methods as the IceCreamDessert base:
		float placeOrder(int flavorNum, int ID);
		bool cancelOrder(int ID);
		int writeReview(string review);
		void menu() const;
		void display() const;

	private:
		list<string> fillings; // fillings are same as
				       // toppings for the waffle class
		int length;
};

// This is an IceCreamDessert class plus more. It methods are the same
// as the Base class, but handle it's own data: size (8oz milk shake,
// 16oz milk shake, and the largest size; 24oz milk shake), and a boost
// like protein, vitamins, antioxidants, etc.(much like at Jamba Juice):
class MilkShake: public IceCreamDessert
{
	public:
		MilkShake();
		~MilkShake();

		// Same signature methods as in ABC:
		float placeOrder(int flavorNum, int ID);
		bool cancelOrder(int ID);
		int writeReview(string review);
		void menu() const;
		void display() const;
	
	private:
		int size;
		string boost;
};

#endif // DESSERT_H
