#ifndef ERROR_H
#define ERROR_H

// Author: Nathan Metens, 907903839
// Instructor: Karla Fant
// Class: cs302-001

// This is the .h file for the error class
// that deals with exception handling.

#include <iostream>
#include <string>

using std::string;

// Enumeration of all possible erroneous 
// situations that may be encountered when
// creating objects of the Dessert hierarchy:
enum class exceptionType {
	bad_flavor,
	bad_flavorNum,
	bad_orderID,
	bad_waffle_type,
	bad_topping,
	bad_filling,
	bad_input, // if user inputs string instead of int
	bad_rating,
	bad_size,
	bad_length,
	bad_dessert,
	bad_tip
};

// Error handling class for exceptions that may occur when creating
// objects of the Dessert hierarchy. There is a constructor, and
// a private message, which is displayed using the what() method,
// similar to how the std::except class might work:
class Error
{
	public:
		Error(exceptionType type, const string &message);
		const string what() const;
		~Error();
	
	private:
		string errorMessage;
};

#endif // ERROR_H
