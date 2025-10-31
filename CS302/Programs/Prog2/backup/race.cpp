/* Author: Nathan Metens 907903839
 * Instructor: Karla Fant
 * Class: cs302-001
 */

// This is the "main" program .cpp file implementation.
// It's purpose is to organize all the races and keep the
// main.cpp file small. The main.cpp file will call the
// methods described here. The methods are to race each of
// DLL of contestants of the User's choosing.

#include "race.h"
#include "error.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <string>
// For random number generator:
#include <random>
#include <chrono> // high-resolution clock
#include <thread> // for pausing execution

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::array;
using std::unique_ptr;

// Default constructor sets names
// vector to empty vector:
Race::Race(): names({}) {}

// Clear the vector:
Race::~Race() { 
	eList.deleteDLL();
	cList.deleteDLL();
	hList.deleteDLL();
	resetNames(); 
}

// Loop through the Names.txt file in the
// correct category and store each name of
// that category in the names vector:
void Race::setNames(const string &category)
{
	if (!names.empty()) names.clear();
	ifstream file("Names.txt");
	string line;
	bool inCategory = false;

	while (std::getline(file, line))
	{
		// go unitl we get to the correct	
		// category in the file:
		if (line == category)
		{
			inCategory = true;
			continue;
		}
		// add each name to names vector:
		if (inCategory && !line.empty())
			names.push_back(line);
		// exit loop if end of category reached:
		else if (inCategory && line.empty())
			break;
	}
}

// Empty the vector to be ready for another
// category of names:
void Race::resetNames() { names.clear(); }

// This method creates a random number on every call.
// I had problems before where creating an array of
// random numbers generated the same number multiple times
// becuase the seed was based on seconds instead of milliseconds.
// This method solved that issue. An array of random numbers
// will have a different random number for each index.
// This method returns a random number between min and max:
int Race::randomNumber(int min, int max)
{
	// get the current time using high-resolution clock
	auto currentTime = std::chrono::high_resolution_clock::now();
	auto timeSinceEpoch = currentTime.time_since_epoch();
	auto seed = std::chrono::duration_cast<std::chrono::milliseconds>(timeSinceEpoch).count();

	// seed the random number generator with the current time
	std::mt19937 gen(static_cast<unsigned int>(seed));

	// define a uniform distribution
	std::uniform_int_distribution<> dis(min, max); // generate numbers between min and max

	int randomNumber = dis(gen); // call the random seed
	return randomNumber;
}

// This is the method that sets up each DLL of contestants to race.
// This method also calls all the other methods of the race class.
// This method prompts the user and displays the results of each
// race (the winners):
void Race::setUpContestants()
{
	// ask the user for the type of contestant object they
	// want to race:
	int contestantType = 0;
	cout << "Which Contestant would you like to race? (1) ElectricWitch, (2) Cyclist, (3) Horse: ";
	cin >> contestantType;	
	cin.clear();
	cout << endl;

	// Make sure the user inputs a correct
	// contestant type:
	if (contestantType != 1 && 
			contestantType != 2 &&
			contestantType != 3)
	{
		bad_contestant_type e;
		e.type = contestantType;
		throw(e); // throw bad contestant type
	}

	int numberOfContestants = 0;
	cout << "How many Contestants do you want to Race (2- 8)? (0) for a random amount: ";
	cin >> numberOfContestants;
	cin.clear();
	cout << endl;

	if ((numberOfContestants < 2 && numberOfContestants != 0) 
		|| numberOfContestants > 8)
	{ // check for expected total contestants:
		bad_contestant e;
		e.contestants = numberOfContestants;
		throw e; // throw exception 
	}

	if (numberOfContestants == 0) 
	{ // generate a random number of contestants:
		numberOfContestants = randomNumber(2, 8);
		cout << "Randomly generated " << numberOfContestants << " Contestants." << endl;
	}

	// create an array of random contestants of the given type:
	if (contestantType == 1) // ElectricWitch Contestants
	{
		setNames("ElectricWitch Names:");
		// Turn each ElectricWitch name into a constant
		// char* and pass it into the DLL:
		for (int i=0; i < numberOfContestants; ++i)
		{	
			ElectricWitch newWitch(names[i].c_str());
			eList.insert(newWitch);	
		}


		// let the user add their own contestants:
		string addContestants = "y";
		do {
			cout << "Do you want to add another Contestants? ('y', 'Y', 'n', 'N'): ";
			cin >> addContestants;
			cin.clear();
			if (addContestants == "y" ||
				addContestants == "Y" ||
				addContestants == "yes" ||
				addContestants == "Yes")
			{
				ElectricWitch userWitch;
				eList.insert(userWitch);
			}
		} while (addContestants == "y" || addContestants == "Y" ||
				addContestants == "yes" || addContestants == "Yes");

		cout << "Here are all the Contestants. They are ready to Race!" << endl;
		eList.display();
		
		raceContestants(eList);

		system("clear");
		cout << "\nHere are the results:" << endl;
		determineWinner(eList);
		eList.display();

		// show winner (greatest distance travelled):
		cout << "\033[1;32m"; // winner message displayed in green
		cout << "\nThe WINNER of the ElectricWitch Race is: " << "\033[0m" << endl;
		cout << "\033[1;33m"; // winner is displayed in yellow:
		eList.displayWinner();	
		cout << "\033[0m" << endl;
	

	}
	else if (contestantType == 2) // Cyclist Contestants
	{
		system("clear");
		setNames("Cyclist Names:");
		for (int i=0; i < numberOfContestants; ++i)
		{
			Cyclist newCyclist(names[i].c_str());
			cList.insert(newCyclist);
		}

		cList.display();

		string addContestants;
		cout << "Do you want to add another Contestants? ('y', 'Y', 'n', 'N'): ";
		//getline(cin, addContestants);
		cin >> addContestants;
		cin.clear();

		if (addContestants == "y" || addContestants == "Y" ||
				addContestants == "yes" || addContestants == "Yes")
		{
			Cyclist userCyclist;
			cout << "Enter a specialty for the Cyclist ('sprinter', 'TT', 'climber', 'none') : ";
			// using insertion operator overloading method:
			cin >> userCyclist;
			cList.insert(userCyclist);
		}
		
		system("clear");
		cout << "The Cyclists are at the start line and ready to race..." << endl;		
		cList.display();	
		
		
		cout << "\nThe Race has begun..." << endl;
		cList.race(); // begin the race
		determineWinner(cList); // rank the contestants in order of overall
					// distance traveled to determine winner
		
		cout << "\nHere are the results: " << endl;
		cList.display(); // show results

		// show winner (greatest distance travelled):
		cout << "\033[1;32m"; // winner message displayed in green
		cout << "\nThe WINNER of the Bycicle Race is: " << "\033[0m" << endl;
		cout << "\033[1;33m"; // winner is displayed in yellow:
		cList.displayWinner();	
		cout << "\033[0m" << endl;
	}
	else if (contestantType == 3) // Horse Contestants
	{
		setNames("Horse Names:");
		for (int i=0; i< numberOfContestants; ++i)
		{
			Horse newHorse(names[i].c_str());
			hList.insert(newHorse);
		}

		hList.display();

		string addContestants;
		cout << "Do you want to add one more Contestants? ('y', 'Y', 'n', 'N'): ";
		cin >> addContestants;
		cin.clear();

		if (addContestants == "y" || addContestants == "Y" ||
				addContestants == "yes" || addContestants == "Yes")
		{
			Horse userHorse;
			hList.insert(userHorse);	
		}
		cout << "The Horses are gathered at the starting line..." << endl;
		hList.display();

		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		system("clear");
		
		cout << "\nAnd they're off, galloping away..." << endl;
		hList.race();
		
		cout << "\nThe results are in: " << endl;
		determineWinner(hList);
		hList.display();

		// show winner (highest bid (wagerAmount)):
		cout << "\033[1;32m"; // winner message displayed in green
		cout << "\nThe Horse that has the HIGHEST WAGER is: " << "\033[0m" << endl;
		cout << "\033[1;33m"; // winner is displayed in yellow:
		hList.displayWinner();	
		cout << "\033[0m" << endl;
	}
}

// Recursively call the race method on each Contestant in the
// DLL to produce random events that determine how far each
// contestant travels in the race:
template <class TYPE>
void Race::raceContestants(DLL<TYPE> &list)
{
	list.race();
}

// Rank the Contestants in order of their distance
// traveled to dertermine the winner of the race:
template <class TYPE>
void Race::determineWinner(DLL<TYPE> &list)
{
	list.insertionSort(); // call insertion sort method on DLL
}
