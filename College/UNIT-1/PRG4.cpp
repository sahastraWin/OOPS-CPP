// Program to implement polymorphism
#include <bits/stdc++.h>
using namespace std;
class Animal
{
public:
    virtual void sound()
    {
        cout << "Animal makes a sound \n";
    }
};
class Dog : public Animal
{
public:
    void sound() override
    {
        cout << "Dog Barks\n";
    }
};
class Cat : public Animal
{
public:
    void sound() override
    {
        cout << "Cat Meows\n";
    }
};
int main()
{
    Animal *a1 = new Dog();
    /*
    These lines create pointers to the base class Animal but instantiate objects of the derived classes Dog and Cat.
    This demonstrates polymorphism, where a base class pointer can point to objects of derived classes.
    */
    Animal *a2 = new Cat();
    a1->sound();
    a2->sound();
    delete a1;
    /*
    These lines deallocate the memory occupied by the Dog and Cat objects, respectively. It's important to call delete on objects created with new to avoid memory leaks.
    */
    delete a2;

    return 0;
}
