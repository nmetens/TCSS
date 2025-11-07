// Author: Nathan Metens, 907903839
// Instructor: Karla Fant
// Class: cs302-001

// This is the implementation file for the error.h class 
// methods. The constructor takes an enum exception type
// and an error message string. The what() method displays
// the error message in color using the static excape codes:

#include "error.h"

using std::string;
using std::cerr;
using std::endl;

// Escape code colors used to display 
// colorful error messages:
static const string RED {"\033[31m"};
static const string GREEN {"\033[32m"};
static const string YELLOW {"\033[33m"};
static const string RESET {"\033[0m"};

// Error constructor takes the type of error, and a message 
// that is created at the exception in the implementation of the
// dessert hierarchy. This constructor creates the proper message
// format:
Error::Error(exceptionType type, const string &message)
{
	// Initialize the errorMessage with red:
	errorMessage = RED;
	// Assign the correct message to the exception:
	switch (type) {
		case exceptionType::bad_flavor:
			errorMessage += "FLAVOR ERROR: " + RESET + message;
			break;
		case exceptionType::bad_flavorNum:
			errorMessage  += "FLAVOR_NUM ERROR: " + RESET + message;
			break;
		case exceptionType::bad_orderID:
			errorMessage += "ORDER_ID ERROR: " + RESET + message;
			break;	
		case exceptionType::bad_waffle_type:
			errorMessage += "WAFFLE_TYPE ERROR: " + RESET + message;
			break;
		case exceptionType::bad_topping:
			errorMessage += "TOPPING ERROR: " + RESET + message;
			break;	
		case exceptionType::bad_input:
			errorMessage += "INVALID_INPUT ERROR: " + RESET + message;
			break;
		case exceptionType::bad_rating:
			errorMessage += "INVALID_RATING ERROR: " + RESET + message;
			break;
		case exceptionType::bad_filling:
			errorMessage += "FILLING ERROR: " + RESET + message;
			break;
		case exceptionType::bad_size:
			errorMessage += "BAD_SIZE ERROR: " + RESET + message;
			break;
		case exceptionType::bad_length:
			errorMessage += "BAD_LENGTH ERROR: " + RESET + message;	
			break;
		case exceptionType::bad_dessert:
			errorMessage += "BAD_DESSERT ERROR: " + RESET + message;
			break;
		case exceptionType::bad_tip:
			errorMessage += "BAD_TIP ERROR: " + RESET + message;	
			break;
		default:
			errorMessage += "UNIDENTIFIED ERROR: " + RESET + message;
			break;
	}
}

// Make errorMessage an empty string:
Error::~Error() { errorMessage = ""; }

// Return the error Message to display in a catch block:
const string Error::what() const { return errorMessage; }
