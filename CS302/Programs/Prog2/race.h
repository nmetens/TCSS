/* Author: Nathan Metens 907903839
 * Instructor: Karla Fant
 * Class: cs302-001
 */

#include "contestant.h"
#include "DLL.h"
#include <vector>
#include <string>
using std::vector;
using std::string;

// This is the main method for racing all of the contestants.
// This class has a vector of names that is extracted from the
// 'Names.txt' file. Each random contestant in the DLL are given
// a name from this file.
// This class also contains a DLL for each contestant type. They
// are all empty until a user picks which contestant they want to
// race. 
// There are also methods to race the contestants, and rank them
// in a certain order to determine the winner:
class Race
{
	public:
		Race();
		~Race();
		
		// Client methods:
		void setUpContestants();
		template <class TYPE>
		void raceContestants(DLL<TYPE> &list);
	
		template <class TYPE>
		void determineWinner(DLL<TYPE> &list);

		private:
		// create empty lists of each Contestant:
		DLL<ElectricWitch> eList;
		DLL<Cyclist> cList;
		DLL<Horse> hList;

		// hold the names for each contestant in Names.txt
		vector<string> names;	
	
		// methods used by the race class
		// to set up Contestants:
		void setNames(const string &category);
		void resetNames();
		int randomNumber(int min, int max);
};
