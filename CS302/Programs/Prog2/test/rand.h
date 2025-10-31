/* Author: Nathan Metens 907903839
 * Instructor: Karla Fant
 * Class: cs302-001
 */

// This file holds a random number method and a pause
// method to halt execution to ensure that each execution
// of the random method is unique.

// For random number generator:
#include <random>
#include <chrono> // high-resolution clock
#include <memory>
#include <thread> // for pausing execution

// Return a random number between the min and max values given:
int randomNumber(int min, int max)
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

// Pause execution to ensure randomness:
void pause(int time = 100)
{ std::this_thread::sleep_for(std::chrono::milliseconds(time)); }
