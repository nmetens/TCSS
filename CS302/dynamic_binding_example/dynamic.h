#include <string>
using namespace std;

class Animal {

    public:
        Animal(int weight, string noise);

        virtual void display() = 0;
        virtual void sound();

    protected:
        int weight;
        string noise;
};

class Dog: public Animal {
    public:
        Dog(int weight = 10, string noise = "woof", int biteforce = 0);

    // Self similar in the hierarchy:
        void display();
        void sound();

    // DIFFERENT FUNCTION:
        int get_biteforce();

    private:
        int biteforce;
};

class Cat: public Animal {
    public:
        Cat(int weight = 5, string noise = "meow", float jump_height = 0.0);

    // Self similar in the hierarchy:
        void display();
        void sound();

    private:
        float jump_height;
};
