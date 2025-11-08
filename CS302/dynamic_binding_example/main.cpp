#include "dynamic.h"
#include <iostream>
#include <array>
using namespace std;

int main() {

    cout << "*****************************" << endl;

    Animal * dog = new Dog();
    Animal * cat = new Cat();

    //Dog dog(5);
    dog->sound();

    //Cat cat(6.0);
    cat->sound();

    cout << "*******************************" << endl;
    //########################################

    array<Animal *, 5> animals;

    char animal;
    for (int i = 0; i < 5; ++i) {
        cout << "What animal do you want to adopt? (cat/dog): ";
        cin >> animal;

        if (animal == 'd') {
            animals[i] = new Dog();
        } 
        else if (animal == 'c') {
            animals[i] = new Cat();
        } 
        else {
            cout << "Default animal is cat" << endl;
        }
    }

    for (Animal * animal: animals) {
        cout << "**************" << endl;
        animal->sound();
    }

    //##########################################
    cout << "*****************************" << endl;
    cout << "Downcasting example using RTTI:" << endl;
    cout << "*****" << endl;
    // Downcasting example:
    Animal * base_ptr = new Dog(150, "woof", 59);
    //Animal * base_ptr = new Cat;

    Cat * c_ptr = dynamic_cast<Cat *> (base_ptr);
    Dog * d_ptr = dynamic_cast<Dog *> (base_ptr);

    if (c_ptr) {
        // This function IS virtual in the base:
        c_ptr->sound();
    }
    else if (d_ptr) {
        // Call a function NOT in the BASE:
        // THIS is RTTI:
        int bite = d_ptr->get_biteforce();
        cout << "The biteforce: " << bite << endl;
    }
    else {
        cout << "Both casts failed\n";
    }

    return 0;
}
