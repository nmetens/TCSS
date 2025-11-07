#include "dynamic.h"
#include <iostream>
using namespace std;

Animal::Animal(int weight, string noise) {
    this->weight = weight;
    this->noise = noise;
}

void Animal::display() {
   cout << "Weight: " << weight << endl;
   cout << "Noise: " << noise << endl;
}

void Animal::sound() {
    cout << "Base class sound!" << endl;
    //cout << noise << endl;
}

//#############################

Dog::Dog(int weight, string noise, int biteforce): Animal(weight, noise), biteforce(biteforce) {}

void Dog::display() {
    cout << "Biteforce: " << biteforce << endl;
}

void Dog::sound() {
    cout << noise << endl;
}

//#############################

Cat::Cat(int weight, string noise, float jump_height): Animal(weight, noise), jump_height(jump_height) {}

void Cat::display() {
    cout << "Jump height: " << jump_height << endl;
}

void Cat::sound() {
    Animal::sound(); // UPCASTING
    cout << noise << endl;
}

