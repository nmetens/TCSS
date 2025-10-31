/* Author: Nathan Metens 907903839
 * Instructor: Karla Fant
 * Class: cs302-001
 */

/* This is the .h file for the Contestant hierarchy.
 * There will be four classes total: Contestant (base class);
 * Cyclist, Horse, and ElectricWitch are all derived from 
 * Contestant. Each class has a specific set of jobs (moveing 
 * throught the race, collecting items, etc.) which are described below.
 * Each class has it's own set of overloaded operators. The 
 * Contestant base class will contain a pointer to a node in a DLL
 * which will be the position of each Contestant in the race.
 */

#include <iostream>
#include <vector>
#include <array>
#include <list>
#include <string>

using std::istream;
using std::ostream;
using std::vector;
using std::string;
using std::array;
using std::list;

static constexpr int SPELLS{2}; // The witch class can only have 2 spells.

/* Each Contestant will have a name, a max speed, and
 * a backpack to collect items in the DLL obstacle course
 * race. A distanceTraveled data member keeps trck of how
 * far the contestant goes, which is used later to identify
 * the winner of a race.

 * Contestant objects can move their position
 * forward and backwards in the DLL, as well as collect
 * items. The overloaded addition operators work to add
 * to the speed of a contestant object. The rest work with
 * the name of the contestant.
 */
class Contestant
{
	public:
		Contestant(const char* name = nullptr, int speed = 25);
		Contestant(const Contestant &);
		~Contestant();

		// Job of each Contestant:
		int moveForward(int amount = 1);
		int moveBackward(int amount = 1);
		bool collectItem(string category);

		// Operator overloading:
		Contestant &operator = (const Contestant &);

		friend ostream &operator << (ostream &, const Contestant &);

		friend bool operator == (const Contestant &, const char* name);
		friend bool operator == (const char* name, const Contestant &);
		friend bool operator == (const Contestant &, const Contestant &);

		friend bool operator != (const Contestant &, const char* name);
		friend bool operator != (const char* name, const Contestant &);
		friend bool operator != (const Contestant &, const Contestant &);

		Contestant &operator += (int distance);
		Contestant &operator -= (int disatance);

	protected:
		char* contestantName;
		int maxSpeed;
		int distanceTraveled;
		vector<string> backpack;
		
		// proteted mothods:
		Contestant &copyContestant(const Contestant &);
};

// Each horse obj is assigned a random breed:
enum class horseBreed
{ // 5 horse breeds:
	Thoroughbred,
	Appaloosa,
	Azteca,
	Andalusian,
	Morgan
};

/* Each Horse object "is a" Contestant and has a breed, 
 * and a wagerAmount. Each Horse object can gallop, jump
 * over obstacles, and avoid obstacles. These methods will
 * call the moveForward and moveBackward methods of its 
 * base class. The overloaded operators work with the wager
 * of each Horse object.
 */
// Since this class dynamic memory, it must incorporate an
// assignment op, a copy constructor, and a destructor...
class Horse: public Contestant
{
	public:
		Horse(const char* name = nullptr, 
	              const char* breed = nullptr, 
		      int wagerAmount = 0);
		Horse(const Horse &);
		~Horse();

		void race(); // random events through the race

		// The jobs of this class:
		int gallop();
		int jump();
		int avoid();

		// Overloaded operator methods:
		Horse &operator = (const Horse &);

		friend ostream &operator << (ostream &, const Horse &);

		friend bool operator == (const Horse &, const Horse &);
		friend bool operator == (int wager, const Horse &);
		friend bool operator == (const Horse &, int wager); 
	
		friend bool operator != (const Horse &, const Horse &);
		friend bool operator != (int wager, const Horse &);
		friend bool operator != (const Horse &, int wager); 

		friend Horse operator + (const Horse &, const Horse &);
		friend Horse operator + (const Horse &, int wager);
		friend Horse operator + (int wager,  const Horse &);
	
		friend Horse operator - (const Horse &, const Horse &);
		friend Horse operator - (const Horse &, int wager);
		friend Horse operator - (int wager,  const Horse &);

		Horse &operator += (const Horse &);
		Horse &operator += (int wager);

		Horse &operator -= (const Horse &);
		Horse &operator -= (int wager);

		friend bool operator < (const Horse &, const Horse &);
		friend bool operator < (int wager, const Horse &);
		friend bool operator < (const Horse &, int wager);
	
		friend bool operator <= (const Horse &, const Horse &);
		friend bool operator <= (int wager, const Horse &);
		friend bool operator <= (const Horse &, int wager);
	
		friend bool operator > (const Horse &, const Horse &);
		friend bool operator > (int wager, const Horse &);
		friend bool operator > (const Horse &, int wager);
	
		friend bool operator >= (const Horse &, const Horse &);
		friend bool operator >= (int wager, const Horse &);
		friend bool operator >= (const Horse &, int wager);
	
	private:
		char* breed;
		int wagerAmount; // how much money the horse obj accumulates

		Horse &copyHorse(const Horse &); // used in assign op and
						 // copy consturctor
};

// Each Cyclist object has a certain 
// ability:
enum class Specialty
{
	none,
	sprinter,
	climber,
	TT // time trialist
};

// This is the cyclist class. Each cyclist object will have a 
// specialty, Energy (which depleates when they pedal and attack, 
// as well as refills when they refuel using snacks collected in the
// backpack (parent data), and an FTP (power output). Each cyclist's
// speed in the race is influenced by their FTP and random events that
// occur in the race() method, the insertion operator is used to get
// a cyclists special ability:
class Cyclist: public Contestant
{
	public:
		Cyclist(const char* name = nullptr,
			string specialty = "none",
			int power = 200,
			int Energy = 100); // changes throughout race
		~Cyclist();

		void race(); // random events while racing

		// Jobs:
		int pedal();
		int attack();
		int refuel();

		// Operator overloading
		friend ostream &operator << (ostream &, const Cyclist &);
		// Used witht the setSpecialty() method:
		friend istream &operator >> (istream &, Cyclist &);
		
		Cyclist &operator -= (int percentage_decreased);
		Cyclist &operator += (int percentage_decreased);

		// member relational operators:
		bool operator > (int percentage) const;
		bool operator < (int percentage) const;
		bool operator >= (int percentage) const;
		bool operator <= (int percentage) const;

		bool operator > (const Cyclist &) const;
		bool operator < (const Cyclist &) const;

		// friend relational operators:
		friend bool operator > (int percentage, const Cyclist &);
		friend bool operator < (int percentage, const Cyclist &);
		friend bool operator >= (int percentage, const Cyclist &);
		friend bool operator <= (int percentage, const Cyclist &);

		friend bool operator == (const Cyclist &, int percentage);
		friend bool operator == (int percentage, const Cyclist &);

		friend bool operator != (const Cyclist &, int percentage);
		friend bool operator != (int percentage, const Cyclist &);

		
	private:
		int FTP_power; // Functional Threshold Power (FTP)
		int Energy;
		Specialty specialty; // enum class above...
	
		string getSpecialty() const; // returns specialty as string obj
		void setSpecialty(string special); // sets specialty
};

// This is the ElectricWitch class. It has methods to fly(), castSpell(),
// chargeBroom(), and chargeWand(). The wand is a vector that stores spells
// for the witch to cast on obstacles. The race method is what generates
// random events for the witch objects to overcome. Since there is no
// dynamic memory in this class, there is no need for a copy constructor,
// nor an assignment operator. The witch's stamina is determined by the
// broomstick batert level, it is an electric witch after all:
class ElectricWitch: public Contestant
{
	public:
		ElectricWitch(const char* name = nullptr);
		~ElectricWitch();

		void race(); // random events while the witch races

		// Jobs:
		int fly();
		int castSpell();
		int chargeBroom();
		void chargeWand();
	
		// Operator Overloading:
		friend ostream &operator << (ostream &, const ElectricWitch &);
		friend istream &operator >> (istream &, ElectricWitch &);

		friend bool operator == (const ElectricWitch &, const ElectricWitch &);
		friend bool operator != (const ElectricWitch &, const ElectricWitch &);

		// used to charge the broomBattery:
		ElectricWitch &operator += (int charge);
		ElectricWitch &operator -= (int charge);

		bool operator > (const ElectricWitch &);
		bool operator < (const ElectricWitch &);

	private:
		vector<string> wand; // holds spells
		int broomBattery;
};
