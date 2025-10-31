/* Author: Nathan Metens 907903839
 * Instructor: Karla Fant
 * Class: cs302-001
 */

// This is the error object file.
// Each struct holds a different error
// prone variable that will be thrown
// on exception and the client is
// responsible for catching each error
// object.

struct bad_speed
{
	int speed;
};

struct bad_name
{
	char* name;
};

struct bad_horse_breed
{
	char* breed;
};

struct bad_wager
{
	int wager;
};

struct bad_power
{
	int power;
};

struct bad_energy
{
	int energy;
};

struct bad_specialty
{
	string specialty;
};

struct bad_charge
{
	int charge;
};

struct bad_contestant
{
	int contestants;
};

struct bad_contestant_type
{
	int type;
};

struct error
{
	// Contestant errors:
	int speed;
	char* name;
	// Horse errors:
	char* breed;
	int wager;
	// Cyclist errors:
	int power;
	int energy;
	string specialty;
	// ElectricWitch errors:
	int charge;
	// race.h errors:
	int contestants; // number of contestants
	int type; // comtestant type
};
