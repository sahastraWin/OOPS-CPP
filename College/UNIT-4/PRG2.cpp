// POLYMORPHISM: run-time
#include <iostream>
using namespace std;

class Animal
{
public:
    virtual void makeSound()
    {
        cout << "Animal makes a sound" << endl;
    }
};

class Dog : public Animal
{
public:
    void makeSound() override
    {
        cout << "Dog Barks" << endl;
    }
};
class Cat : public Animal
{
public:
    void makeSound() override
    {
        cout << "Cat Meows" << endl;
    }
};
int main()
{
    Animal *animalPtr;
    Dog d;
    Cat c;
    animalPtr = &d;
    animalPtr->makeSound(); // calling dog's sound

    animalPtr = &c;
    animalPtr->makeSound(); // calling cat's sound

    return 0;
}
