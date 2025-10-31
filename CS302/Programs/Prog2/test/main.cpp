/* Author: Nathan Metens 907903839
 * Instructor: Karla Fant
 * Class: cs302-001
 */

// This is the main "client" file, where the Race class
// methods are called to create a DLL of contestants
// and race those contestants, and finally, determine the
// results. This is where the try and catch block of 
// the exception handling is implemented.

#include "race.h"
#include "error.h"
#include <iostream>

using std::cerr;
using std::cout;
using std::endl;

int main()
{
	try
	{
		// This class and its methods 
		// are found in the race.h file:
		Race myRace; // create a race
		myRace.setUpContestants(); // set up and race the contestants, determining the winner
	
		// Catch blocks for all possible input errors when creating and racing the contestants:
	} catch (bad_speed e) {
		cerr << "\033[1;31m" << "Error: " << "\033[0m" << "Speed must be between 1 and 50, recieved: '" << "\033[1;33m" << e.speed <<  "\033[0m" << "'" << endl;
	} catch (bad_name e) {
		cerr << "\033[1;31m" << "Error: " << "\033[0m" << "Name must be at least two characters, recieved: '" << "\033[1;33m" << e.name << "\033[0m" << "'" << endl;
	} catch (bad_horse_breed e) {
		cerr << "\033[1;31m" << "Error: " << "\033[0m" << "Horse Breed must be valid, recieved: '" << "\033[1;33m" << e.breed << "\033[0m" << "'" << endl;
		cout << "Valid Horse Breeds: Thoroughbred, Appaloosa, Azteca, Andalusian, Morgan" << endl;
	} catch (bad_wager e) {
		cerr << "\033[1;31m" << "Error: " << "\033[0m" << "Wager Must be a positive bet, recieved: '" << "\033[1;33m" << e.wager << "\033[0m" << "'" << endl;
	} catch (bad_energy e) {
		cerr << "\033[1;31m" << "Error: " << "\033[0m" << "Energy must be between 0 and 100%, recieved: '" << "\033[1;33m" << e.energy << "\033[0m" << "'" << endl;
	} catch (bad_charge e) {
		cerr << "\033[1;31m" << "Error: " << "\033[0m" << "Charge must be between 0 and 100%, recieved: '" << "\033[1;33m" << e.charge << "\033[0m" << "'" << endl;
	} catch (bad_contestant e) {
		cerr << "\033[1;31m" << "Error: " << "\033[0m" << "Can only have between 2 and 8 contestants, recieved: '" << "\033[1;33m" << e.contestants << "\033[0m" << "'" << endl;
	} catch (bad_contestant_type e) {
		cerr << "\033[1;31m" << "Error: " << "\033[0m" << "The contestant types are (1) ElectricWitch, (2) Cyclist, (3) Horse, recieved: '" << "\033[1;33m" << e.type << "\033[0m" << "'" << endl;
	}

	return 0;
}
