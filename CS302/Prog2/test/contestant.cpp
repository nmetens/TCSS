/* Author: Nathan Metens 907903839
 * Instructor: Karla Fant
 * Class: cs302-001
 */

// This is the implementation of the core hierarchy of
// contestants. Inside each method that deals with inputing
// important data, there is carefull error checking. If data is
// of improper type, an exception is thrown. Each exception object
// can be found in the error.h file.
// The first section is the implementation of the base class "Contestant",
// and the following sections are the derived classes in the same order
// they are created in the contestant.h file.

static constexpr int BREEDS{5}; // there are only 5 horse breeds
static constexpr int SPECIALTY{4}; // there are only 4 cyclist specialties 

#include "contestant.h"
#include "error.h"
#include "rand.h" // random num generator func
#include <cstdlib> // srand() and rand()
#include <ctime>   // time()
#include <cstring>
#include <iostream>
#include <fstream>
#include <list>

using std::cin;
using std::endl;
using std::cout;
using std::ifstream;
using std::list;
using std::advance;

/****************************************************************/
/************* Contestant Class Implementation ******************/
/****************************************************************/

/* This constructor takes a name and a speed. The backpack is 
 * empty to begin the race.
 * If the client creates an object without a name, the default
 * constructor will prompt the client for the information:
 */
Contestant::Contestant(const char* name, int speed):
	contestantName(nullptr), maxSpeed(speed), 
	distanceTraveled(0), backpack({})
{
	if (!name)
	{ // check that the name is not empty:
	// if no name provided, use one at random from Name.txt:

	
		char input[50];
		cout << "What is the Contestant's name: ";
		cin >> input;
		//cin.getline(input, 50);
		cin.clear();

		if (strlen(input) < 2)
		{ // check for bad name input:
			bad_name e;
			e.name = new char[strlen(input) + 1];
			strcpy(e.name, input);
			throw(e); // throw bad name exception	
		}

		// copy the name:
		contestantName = new char[strlen(input) + 1];
		strcpy(contestantName, input);
	} else {
		contestantName = new char[strlen(name) + 1];
		strcpy(contestantName, name);
	}

	if (speed < 1 || speed > 50) 
	{ // check for bad speed input:
		bad_speed e;
		e.speed = speed;
		throw(e); // throw bad speed exception
	}
}

// Copy constructor calls the private copyContestant method:
Contestant::Contestant(const Contestant &contestant):
	contestantName(nullptr), maxSpeed(25), 
	distanceTraveled(0), backpack({})
{
	*this = copyContestant(contestant);
}

// Assignment Op calls the private copyContestant method:
Contestant &Contestant::operator = (const Contestant &contestant)
{
	return copyContestant(contestant);
}

Contestant::~Contestant()
{
	if (contestantName)
	{ // check for previous allocation:
		delete [] contestantName;
		contestantName = nullptr;
	}
	maxSpeed = 0;
	distanceTraveled = 0;
	backpack.clear();
}

// Private copy method that copies a contestant. Used by both
// the assignment operator and copy constructor because the 
// process is the same:
Contestant &Contestant::copyContestant(const Contestant &contestant)
{
	if (this != &contestant) // check self assignment
	{
		if (contestantName)
			delete [] contestantName; // deallocate current memory
						  // deep copy the data:
		contestantName = new char[strlen(contestant.contestantName) + 1];
		strcpy(contestantName, contestant.contestantName);

		maxSpeed = contestant.maxSpeed;
		distanceTraveled = contestant.distanceTraveled;
		backpack.assign(contestant.backpack.begin(), 
				contestant.backpack.end());
	}
	return *this; // return current object
}

// Public method that moves the contestant object
// forward in the DLL race obstacle course:
int Contestant::moveForward(int amount)
{
	// for cyclists, they can move farther if they
	// have a higher FTP:
	*this += 2*amount;
	return 0;
}

// Public method that moves the contestant object
// backward in the DLL race obstacle course:
int Contestant::moveBackward(int amount)
{
	*this -= 1*amount;
	return 0;
}

// The compound addition and subtraction operators
// determine how far a contestant gets to move
// forward or beackwards depending on an obstacle:
Contestant &Contestant::operator += (int distance)
{
	distanceTraveled += distance;
	return *this;
}
Contestant &Contestant::operator -= (int disatance)
{
	distanceTraveled -= disatance;
	return *this;
}


// Public method to collect a random item in the 
// category (ElectricWitch items, Cyclist items, Horse
// items) and add it to the backpack of that contestant:
bool Contestant::collectItem(string category)
{
	ifstream file("items.txt");
	string item; // the current item in the catgegory
	list<string> items; // list of all items
			    // in the category
	bool inCategory = false;

	while (std::getline(file, item))
	{
		// go unitl we get to the correct	
		// category in the file:
		if (item == category)
		{
			inCategory = true;
			continue;
		}
		// add each item to list of items:
		if (inCategory && !item.empty())
			items.push_back(item);
		// exit loop if end of category reached:
		else if (inCategory && item.empty())
			break;
	}

	// select a random item from the list and add
	// it to the backpack:
	int randomItem = randomNumber(0, items.size()-1);
	pause(50);
	auto it = items.begin(); // list iterator positioned at start
	advance(it, randomItem); // go to random item in list
	backpack.push_back(*it); // collect random item in backpack
	
	return 0;
}

// Extraction operator outputs all data:
ostream &operator << (ostream & out, const Contestant &contestant)
{
	out << "\nContestantName: " << contestant.contestantName;
	out << "\nDistance Traveled: " << contestant.distanceTraveled << " miles";
	out << 	"\nMaxSpeed: " << contestant.maxSpeed << "mph";
	out << 	"\nBackpack: ";
	if (contestant.backpack.empty())
		out << "empty";
	else { // use the vector iterator to display contents:
		for (auto iter = contestant.backpack.begin(); 
				iter != contestant.backpack.end(); ++iter)
			out << *iter << ", ";	
	}
	return out;
}

// Equality check between a contestant and a char* name:
bool operator == (const Contestant &con, const char* name)
{
	return strcmp(con.contestantName, name) == 0;
}

// Equality check between a char* name and a contestant object:
bool operator == (const char* name, const Contestant &con)
{
	return strcmp(con.contestantName, name) == 0;
}

// Equality check between two contestant objects' names:
bool operator == (const Contestant &con1, const Contestant &con2)
{
	return strcmp(con1.contestantName, con2.contestantName) == 0;
};

// Inequality check between a contestant object and a char*:
bool operator != (const Contestant &con, const char* name)
{
	return strcmp(con.contestantName, name) != 0;
}

// Inequality check between a char* and a contestant object:
bool operator != (const char* name, const Contestant &con)
{
	return strcmp(con.contestantName, name) != 0;
}

// Inequality check between two contestant objects' names:
bool operator != (const Contestant &con1, const Contestant &con2)
{
	return strcmp(con1.contestantName, con2.contestantName) != 0;
}

/****************************************************************/
/***************** Horse Class Implementation *******************/
/****************************************************************/

// The Horse default constructor assigns a client chosen breed
// and wager for each horse object, or a random horse breed if none
// is provided. Carefull checking of the data is executed:
Horse::Horse(const char* name, const char* br, int wager): 
	Contestant(name), breed(nullptr), wagerAmount(wager)
{
	if (br)
	{ // allocate memory for the breed:
		breed = new char[strlen(br) + 1];
		strcpy(breed, br);

		// check if the breed is a valid type:
		if (strcmp(breed, "Thoroughbred") != 0 && 
				strcmp(breed, "Appaloosa") != 0 &&
				strcmp(breed, "Azteca") != 0 &&
				strcmp(breed, "Andalusian") != 0 &&
				strcmp(breed, "Morgan") != 0)
		{
			bad_horse_breed e;
			e.breed = new char[strlen(breed) + 1];
			strcpy(e.breed, breed);
			throw(e); // throw a bad breed exception
		}
	} else { // pick random breed if not provided by the client:
		//srand(time(nullptr));
		//int randomBreed = rand() % BREEDS;
		int randomBreed = randomNumber(0, 4);
		pause(50);

		switch (randomBreed) 
		{
			case 0:
				breed = new char[strlen("Thoroughbred") + 1];
				strcpy(breed, "Thoroughbred");
				break;
			case 1:
				breed = new char[strlen("Appaloosa") + 1];
				strcpy(breed, "Appaloosa");
				break;
			case 2:
				breed = new char[strlen("Azteca") + 1];
				strcpy(breed, "Azteca");
				break;
			case 3:
				breed = new char[strlen("Andalusian") + 1];
				strcpy(breed, "Andalusian");
				break;
			case 4:
				breed = new char[strlen("Morgan") + 1];
				strcpy(breed, "Morgan");
				break;
		}
	}

	if (wagerAmount < 0)
	{ // check that the wager is a positive number
		bad_wager e;
		e.wager = wagerAmount;
		throw(e); // throw a bad wager exception
	}
}

// Copy constructor calls the Contestant copy constructor 
// in the initialization list:
Horse::Horse(const Horse &horse): 
	Contestant(horse), breed(nullptr), wagerAmount(0)
{
	*this = copyHorse(horse);
}

// Assignment operator calls the copyHorse private method:
Horse &Horse::operator = (const Horse &horse)
{
	static_cast<Contestant &> (*this) = horse;
	return copyHorse(horse);
}

// This private method is used by both the copy and 
// assignment operator:
Horse &Horse::copyHorse(const Horse &horse)
{
	if (this != &horse)
	{
		if (breed)
			delete [] breed;
		breed = new char[strlen(horse.breed) + 1];
		strcpy(breed, horse.breed);
		wagerAmount = horse.wagerAmount;
	}
	return *this;
}

// Deallocate breed memory and set wager to 0:
Horse::~Horse()
{
	if (breed)
	{
		delete [] breed;
		breed = nullptr;
	}	
	wagerAmount = 0;
}

// The race method that produces random
// events for each Horse object:
void Horse::race()
{
	int randomEvent = randomNumber(0, 10);
	int totalEvents = 100;
	for (int i = 0; i < totalEvents; ++i)
	{
		if (randomEvent < 4)
		{
			gallop();
		} else if (randomEvent >= 4 &&
				randomEvent < 6)
		{
			avoid();
		} else if (randomEvent >= 6 &&
				randomEvent <= 8)
		{
			jump();
		} else collectItem("Horse Items:");
		randomEvent = randomNumber(0, 10);
	}
}

// Moves the horse forward a certain distance
// by calling the parent method:
int Horse::gallop()
{
	moveForward(5);
	return 1;
}

// There is an obstacle that the horse must
// jump over. The Horse has a chance to fail the
// jump. If they succeed however, they increase their
// wagerAmount because the fans like this horse:
int Horse::jump()
{
	int failChance = randomNumber(0, 10);
	if (failChance == 8 || failChance == 1)
		moveBackward(2);
	else *this = 100 + *this; // fans increase total wager
	return this->wagerAmount;
}

// If the horse decides to avoid an obstacle (could be
// a fence to jump, or a hoop to go through), the fans
// get mad and remove their bet on this horse for 
// not entertaining them. The horse however gets to move 
// forward faster by not risking a fail:
int Horse::avoid()
{
	moveForward(10);
	if (this->wagerAmount - 100 > 0) *this = *this - 100;
	return 0;
}

// Output the Horse object data and the Contestant name
// and speed as well by calling the parent method:
ostream &operator << (ostream & out, const Horse &horse)
{
	out << static_cast<const Contestant &> (horse); // use << on base
	out << "\nBreed: " << horse.breed;
	out << "\nWager: " << horse.wagerAmount;
	return out;
}

// Equality operation comparing two Horse objects:
bool operator == (const Horse &h1, const Horse &h2)
{
	return h1.wagerAmount == h2.wagerAmount;
}

// Equality operatioin comparing a wager and a Horse obj
bool operator == (int wager, const Horse &h)
{
	return wager == h.wagerAmount;
}

// Equality check between a Horse obj and an wager:
bool operator == (const Horse &h, int wager)
{
	return h.wagerAmount == wager;
}

// Inequality check between a two Horse objects wagers:
bool operator != (const Horse &h1, const Horse &h2)
{
	return h1.wagerAmount != h2.wagerAmount;
}

// Inequality between a wager amount and a horse obj:
bool operator != (int wager, const Horse &h)
{
	return wager != h.wagerAmount;
}

// Inequality between a horse obj and a wager:
bool operator != (const Horse &h, int wager)
{
	return h.wagerAmount != wager;
}

// Addition of two Horse objects' wager amounts:
Horse operator + (const Horse &h1, const Horse &h2)
{
	Horse temp;
	temp.wagerAmount = h1.wagerAmount + h2.wagerAmount;
	return temp;
}

// Adding a horse's wager with an integer wager:
Horse operator + (const Horse &h, int wager)
{
	Horse temp;
	temp.wagerAmount = h.wagerAmount + wager;
	return temp;
}

// Add a wager to a horse wager:
Horse operator + (int wager, const Horse &h)
{
	// initialize the temp to h to avoid calling
	// the copy constructor!!!!
	Horse temp(h);
	temp.wagerAmount = wager + h.wagerAmount;
	return temp;
}

// Addition of two Horse objects' wager amounts:
Horse operator - (const Horse &h1, const Horse &h2)
{
	Horse temp;
	temp.wagerAmount = h1.wagerAmount - h2.wagerAmount;

	if (temp.wagerAmount < 0)
	{ // check for negative wager
		bad_wager e;
		e.wager = temp.wagerAmount;
		throw(e);
	}
	return temp;
}

// Adding a horse's wager with an integer wager:
Horse operator - (const Horse &h, int wager)
{
	Horse temp(h);
	temp.wagerAmount = h.wagerAmount - wager;

	if (temp.wagerAmount < 0)
	{ // check for negative wager
		bad_wager e;
		e.wager = temp.wagerAmount;
		throw(e);
	}
	return temp;
}

// Add a wager to a horse wager:
Horse operator - (int wager, const Horse &h)
{
	Horse temp(h); // CAUSED MAJOR PROBLEMS UNTIL FIXED
	temp.wagerAmount = wager - h.wagerAmount;

	if (temp.wagerAmount < 0)
	{ // check for negative wager
		bad_wager e;
		e.wager = temp.wagerAmount;
		throw(e);
	}
	return temp;
}

// Compound assignment that adds another 
// objects wager to the current object's wager:
Horse &Horse::operator += (const Horse &h)
{
	this->wagerAmount += h.wagerAmount;
	return *this;
}

// Compound assignment that adds an integer
// wager to the current object's wager amount:
Horse &Horse::operator += (int wager)
{
	this->wagerAmount += wager;
	return *this;
}

// Compound subtraction that subtracts one
// Horse objects wager from the current one:
Horse &Horse::operator -= (const Horse &h)
{
	this->wagerAmount -= h.wagerAmount;

	if ((*this).wagerAmount < 0)
	{ // check for negative wager
		bad_wager e;
		e.wager = this->wagerAmount;
		throw(e); // throw negative wager exceoption
	}

	return *this;
}

// Compound subtraction, subtracting an integer
// wager from the current objects wager amount:
Horse &Horse::operator -= (int wager)
{
	(*this).wagerAmount -= wager;

	if (this->wagerAmount < 0)
	{ // check for negative wager
		bad_wager e;
		e.wager = (*this).wagerAmount;
		throw(e);
	}

	return *this;
}

// Less than operator comparing two Horse objects wagers:
bool operator < (const Horse &h1, const Horse &h2)
{
	return h1.wagerAmount < h2.wagerAmount;
}

// Less than comparing integer with horse obj wager:
bool operator < (int wager, const Horse &h)
{
	return wager < h.wagerAmount;
}

// checks: Horse obj < int wager:
bool operator < (const Horse &h, int wager)
{
	return h.wagerAmount < wager;
}

// checks: horse obj1 wager <= obj2 wager:
bool operator <= (const Horse &h1, const Horse &h2)
{
	return h1.wagerAmount <= h2.wagerAmount;
}

// checks: int <= obj:
bool operator <= (int wager, const Horse &h)
{
	return wager <= h.wagerAmount;
}

// checks: obj <= wager:
bool operator <= (const Horse &h, int wager)
{
	return h.wagerAmount <= wager;
}

// checks: obj1 wager > obj2 wager
bool operator > (const Horse &h1, const Horse &h2)
{
	return h1.wagerAmount > h2.wagerAmount;
}

// checks: int wager > obj wager
bool operator > (int wager, const Horse &h)
{
	return wager > h.wagerAmount;
}

// checks: obj wager > wager
bool operator > (const Horse &h, int wager)
{
	return h.wagerAmount > wager;
}

// checks: obj1 wager >= obj2 wager
bool operator >= (const Horse &h1, const Horse &h2)
{
	return h1.wagerAmount >= h2.wagerAmount;
}

// checks: wager >= obj wager
bool operator >= (int wager, const Horse &h)
{
	return wager >= h.wagerAmount;
}

// checks: obj wager >= wager
bool operator >= (const Horse &h, int wager)
{
	return h.wagerAmount >= wager;
}

/****************************************************************/
/**************** Cyclist Class Implementation ******************/
/****************************************************************/

Cyclist::Cyclist(const char* name, string specialty_type, int power, int energy): 
	Contestant(name), FTP_power(power), Energy(energy), specialty(Specialty::none)
{
	
	if (FTP_power == 200) // default
	{ // create a random one:
		FTP_power = randomNumber(200, 400);
	}

	// Error handling:
	if (power < 60 || power > 800)
	{ // check for bad power input
		bad_power e;
		e.power = power;
		throw(e); // throw bad power exception
	}

	if (energy <= 0 || energy > 100)
	{ // check that the energy is sufficient
		bad_energy e;
		e.energy = energy;
		throw(e); // throw bad energy exception
	}

	if (specialty_type != "none" &&
			specialty_type != "sprinter" &&
			specialty_type != "climber" &&
			specialty_type != "TT")
	{ // check that the specialty is one of the types:
		bad_specialty e;
		e.specialty = specialty_type;
		throw(e); // throw bad specialty exception
	}

	if (specialty_type == "none") // default specialty
	{ // assign one at random:
		specialty_type = "random"; // assigned below...
	}
	
	// pause the execution briefly so that the random
	// numbers are different. For some reason, they are still
	// the same:
	pause(200);

	// assign the specialty if it is one of the types:
	if (specialty_type == "none")
		specialty = Specialty::none;
	else if (specialty_type == "sprinter")
		specialty = Specialty::sprinter;
	else if (specialty_type == "climber")
		specialty = Specialty::climber;
	else if (specialty_type == "TT")
		specialty = Specialty::TT;
	else { // assign a random specialty otherwise:
		//srand(time(nullptr));
		//int randomSpecialty = rand() % SPECIALTY;
		int randomSpecialty = randomNumber(0, SPECIALTY);

		switch (randomSpecialty) 
		{
			case 0:
				specialty = Specialty::none;
				break;
			case 1:
				specialty = Specialty::sprinter;
				break;
			case 2:
				specialty = Specialty::climber;
				break;
			case 3:
				specialty = Specialty::TT;
				break;
		}
	}
}

// No dynamic memory, so just set all
// variables to zero equivalent:
Cyclist::~Cyclist()
{
	FTP_power = 0;
	Energy = 0;
	specialty = Specialty::none;
}

// Output the base class' info, along with the cyclist info:
ostream &operator << (ostream &out, const Cyclist &cyc)
{
	out << static_cast<const Contestant &> (cyc); // call base class
	out << "\nFTP: " << cyc.FTP_power;
	out << "\nSpecialty: " << cyc.getSpecialty(); // get string
	out << "\nEnergy: " << cyc.Energy << "%";
	return out;
}

// Insertion operator to assign the specialy:
istream &operator >> (istream &in, Cyclist &cyc)
{
	string special;
	in >> special;
	cyc.setSpecialty(special);
	return in;	
}

// Sets the special ability of the cyclist:
void Cyclist::setSpecialty(string special)
{
	if (special == "sprinter")
		specialty = Specialty::sprinter;
	else if (special == "climber")
		specialty = Specialty::climber;
	else if (special == "TT")
		specialty = Specialty::TT;
	else if (special == "none")
		specialty = Specialty::none;
}

// This method converts the enum Specialty type to a 
// string and returns it. Allows for outputting the specialty
// in the '<<' overloaded operator method...
string Cyclist::getSpecialty() const
{
	if (specialty == Specialty::TT) return "TT";
	else if (specialty == Specialty::sprinter) return "sprinter";
	else if (specialty == Specialty::climber) return "climber";
	return "none";
}

bool Cyclist::operator > (const Cyclist &cyc) const
{
	return this->distanceTraveled > cyc.distanceTraveled;
}
bool Cyclist::operator < (const Cyclist &cyc) const
{
	return this->distanceTraveled < cyc.distanceTraveled;
}

// Race method that produces random events on each Cyclist
// object:
void Cyclist::race()
{
	int randomEvent = randomNumber(0, 10);
	int totalRandEvents = 100;
	for (int i = 0; i < totalRandEvents; ++i)
	{
		if (randomEvent <= 3) // advance forwards
		{ // the greater the power, the greater the distance...
			moveForward(FTP_power/100);
			pedal();
		} else if (randomEvent >3 &&
				randomEvent < 5)
		{ // attack, with a chance of crashing:
			attack();
		} else if (randomEvent >= 5 &&
				randomEvent <= 8)
			refuel();
		else collectItem("Cyclist Snacks:");
		// create a new random event each time:
		randomEvent = randomNumber(0, 10);
	}
}

// The cyclist moves forward and uses a little bit of energy:
int Cyclist::pedal()
{
	if (Energy - 5 > 0)
		*this -= 5; // decrease energy using op overloading
	return Energy;
}

// The cyclist takes a chance and uses more energy to travel a
// greater distance. They have a chance og crashing, which sets
// them back:
int Cyclist::attack()
{
	if (Energy - 20 > 0)
		*this -= 20; // attacking decreases energy faster
	int crash = randomNumber(0, 10);
	if (crash == 3 || crash == 7)
		moveBackward(5);
	return Energy;
}

// If the cyclist is out of enery, they need to refuel by using
// snacks they collected in their backpack:
int Cyclist::refuel()
{
	if (!backpack.empty())
	{
		backpack.pop_back(); // eat the snack in the backpack
		// increase the energy by eating the snack:
		if (Energy + 10 <= 100) *this += 10;
	}
	return Energy;
}
	
// This method is used to control the energy level of the
// cyclist object. After an attack, the energy goes down
// significanlty (10%). This operator is overloaded to only
// deal with integers. 
Cyclist &Cyclist::operator -= (int perc_dec)
{
	if (Energy - perc_dec <= 0 || perc_dec < 0)
	{ // check that the energy is sufficient
		bad_energy e;
		e.energy = Energy - perc_dec;
		throw(e); // throw bad energy exception
	}

	Energy -= perc_dec;
	return *this;
}

// Same as the -=, except adds to the total energy. This
// method is used in the refuel method so that the Cyclist
// object gains more energy through the race.
Cyclist &Cyclist::operator += (int perc_inc)
{
	if (Energy + perc_inc > 100 || perc_inc < 0)
	{ // check that the energy is sufficient
		bad_energy e;
		e.energy = Energy + perc_inc;
		throw(e); // throw bad energy exception
	}

	Energy += perc_inc;
	return *this;	
}

// Greater than op checks that the Cyclists'
// energy is greater than a certain percentage:
bool Cyclist::operator > (int percentage) const
{
	return Energy > percentage;
}

// checks: Energy < %:
bool Cyclist::operator < (int percentage) const
{
	return Energy < percentage;
}

// checks: Energy >= %:
bool Cyclist::operator >= (int percentage) const
{
	return Energy >= percentage;
}

// checks: Energy <= percentage:
bool Cyclist::operator <= (int percentage) const
{
	return Energy <= percentage;
}

// checks: % > Energy:
bool operator > (int percentage, const Cyclist &c)
{
	return percentage > c.Energy;
}

bool operator < (int percentage, const Cyclist &c)
{
	return percentage < c.Energy;
}

bool operator >= (int percentage, const Cyclist &c)
{
	return percentage >= c.Energy;
}

bool operator <= (int percentage, const Cyclist &c)
{
	return percentage <= c.Energy;
}

// checks: Energy == %:
bool operator == (const Cyclist &c, int percentage)
{
	return c.Energy == percentage;
}

// checks: % == Energy:
bool operator == (int percentage, const Cyclist &c)
{
	return percentage == c.Energy;
}

// Not equal member function comparing
// cyclists' energy and %:
bool operator != (const Cyclist &c, int percentage)
{
	return c.Energy != percentage;
}

// Not equal comparison between % and cyclists' energy:
bool operator != (int percentage, const Cyclist &c)
{
	return percentage != c.Energy;
}

/****************************************************************/
/************ ElectricWitch Class Implementation ****************/
/****************************************************************/

// Set all variables to default value. Call the base class constructor
// with a char* name to deal with the dynamic memory:
ElectricWitch::ElectricWitch(const char* name): 
	Contestant(name), wand({}), broomBattery(100)
{
	// give each witch's wand random spells:
	chargeWand();		
}

// Clear the spells from the vector and set battery to zero:
ElectricWitch::~ElectricWitch()
{
	wand.clear(); // remove all spells
	broomBattery = 0;
}

// Charge the array (wand) so that the witch can cast spells
// on obstacles encountered in the race:
void ElectricWitch::chargeWand()
{
	ifstream file("items.txt");
	string spell; // the current spell in the category
	//vector<string> spells; // list of all spell
	bool inCategory = false;

	while (std::getline(file, spell))
	{
		// go unitl we get to the correct	
		// category in the file:
		if (spell == "ElectricWitch Spells:")
		{
			inCategory = true;
			continue;
		}
		// add each item to list of items:
		if (inCategory && !spell.empty())
			wand.push_back(spell);
		// exit loop if end of category reached:
		else if (inCategory && spell.empty())
			break;
	}
	
	// keep only a select couple spells randomly:
	while (wand.size() != 2)
		wand.erase(wand.begin() + randomNumber(0, wand.size()));
}

// This is the racing method that creates random roadblocks,
// collectables, and other events that the contestant can 
// encounter during the race.
void ElectricWitch::race()
{ // each contestant encounters a certain number of events:
	cout << "Racing ElectricWitch..." << endl;
	
	int randomEvent = randomNumber(0, 10);
	//srand(time(nullptr));
	//int randomEvent = rand() % 10;

	for (int event = 0; event < 100; ++event)
	{
		if (randomEvent <= 3  )
		{ // advance forward in the race
			moveForward();
			fly();
		} else if (randomEvent >= 4 &&
				randomEvent < 6)
		{ // cast a spell on an obstacle
			castSpell();
		}
		else if (randomEvent >=6 && 
				randomEvent <=8)
		{ // recharge the broom
			chargeBroom();
		}
		else 
		{ // collect an item in this category
			collectItem("ElectricWitch Items:");
		} 
		// generate a new random number:
		randomEvent = randomNumber(0, 10);
	}
}

// Move the witch forward through the race
// obstacle course:
int ElectricWitch::fly()
{
	// flying forward depleates the 
	// broomBattery by 10%:
	if (broomBattery - 10 > 0)
		*this -= 10;
	// if battery is low, charge it:
	else chargeBroom();
	return 1;		
}

// The witch faces an obstacle and must cast one of here spells
// in order to destroy the enemy. If the obstacle survives, the
// witch must retreat:
int ElectricWitch::castSpell()
{
	int obstacleSurvival = randomNumber(0, 100);
	if (obstacleSurvival < 50)
	{ // call parent method to update distance traveled backward:
		moveBackward();
		return 0;
	}
	return 1;
}

// Recharge the broom stick so that
// the witch can continue forward:
int ElectricWitch::chargeBroom()
{
	// the broom can only be charged 5%
	// at a time:
	if (broomBattery + 5 <= 100)
		*this += 5;
	// if fully charged, fly forward:
	else fly(); 
	return 1;
}

// Overloading the extraction operator to display the base
// class data and the ElectricWitch data:
ostream &operator << (ostream &out, const ElectricWitch &w)
{
	out << static_cast<const Contestant &> (w);
	
	out << "\nSpells Casted: ";
	for (const string &spell : w.wand)
		out << "'" << spell << "', ";
	out << "\nBroomStick Battery: " << w.broomBattery << "%";
	return out;
}

// The insertion operator is used to insert a new spell
// into the wand vector:
istream &operator >> (istream &input, ElectricWitch &w)
{
	string new_spell;
	input >> new_spell;
	for (auto spell : w.wand)
	w.wand.push_back(new_spell);
	return input;
}

// This relation operator calls the base class of both ElectricWitch
// objects and compares them. If the names are the same, the result is true.
bool operator == (const ElectricWitch &w1, const ElectricWitch &w2)
{
	return static_cast<const Contestant &> (w1) == 
		static_cast<const Contestant &> (w2);
}

// Checks if the Contestant names of both ElectricWitch objects
// are the same:
bool operator != (const ElectricWitch &w1, const ElectricWitch &w2)
{
	return static_cast<const Contestant &> (w1) !=
		static_cast<const Contestant &> (w2);
}

// This is compound addition that increases the broomstick battery:
ElectricWitch &ElectricWitch::operator += (int charge)
{
	if (broomBattery + charge > 100 || charge < 0)
	{
		bad_charge e;
		e.charge = charge;
		throw(e);
	}

	broomBattery += charge;
	return *this;
}

// Compound subtration decreases the broomstick barrtery:
ElectricWitch &ElectricWitch::operator -= (int charge)
{
	if (broomBattery - charge < 0 || charge < 0)
	{
		bad_charge e;
		e.charge = charge;
		throw(e);
	}

	broomBattery -= charge;
	return *this;
}

// Checks the distance between this witch and 
// the compared witch (argument):
bool ElectricWitch::operator > (const ElectricWitch &w)
{
	return this->distanceTraveled > w.distanceTraveled;
}

// Checks this witch and the compared witch
// if this witch is smaller than the other:
bool ElectricWitch::operator < (const ElectricWitch &w)
{
	return this->distanceTraveled < w.distanceTraveled;
}
