// WRITE A PROGRAM TO IMPLEMENT SINGLE LEVEL INHERITANCE
#include <iostream>
using namespace std;
class Animal
{
public:
    void eat()
    {
        cout << "Animal eats food\n";
    }
};
class Dog : public Animal
{
public:
    void sound()
    {
        cout << "Dog barks\n";
    }
};
int main()
{
    Dog d;
    d.eat();   // inherited method
    d.sound(); // method of dog class
    return 0;
}