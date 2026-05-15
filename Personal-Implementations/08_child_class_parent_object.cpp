/*
    Question:
    Demonstrate calling and printing child class methods using a parent class object.
    Show:
    1. Without virtual — parent's method is called (static binding)
    2. With virtual — child's method is called (dynamic binding / polymorphism)
    3. Using pointer and reference of parent type to hold child object

    Intuition:
    In C++ inheritance, a parent class pointer/reference CAN hold a child object.
    This is called upcasting — treating a child as its parent type.

    BUT there's a crucial difference:
    - WITHOUT virtual keyword: the method called depends on the POINTER TYPE (compile-time)
      → This is called Static Binding / Early Binding
      → Even if pointer holds a child, parent's method is called

    - WITH virtual keyword: the method called depends on the ACTUAL OBJECT TYPE (runtime)
      → This is called Dynamic Binding / Late Binding / Runtime Polymorphism
      → If pointer holds a child, child's method is called ✓

    Think of it like: You have a variable labeled "Employee" but it actually points to a "Manager".
    - Without virtual: calls Employee's work() method (ignores actual type)
    - With virtual:    calls Manager's work() method (respects actual type)

    Time Complexity:  O(1) — all method calls are constant
    Space Complexity: O(1) — fixed number of objects
*/

#include <bits/stdc++.h>
using namespace std;

// -------------------------------------------------------
// EXAMPLE 1: WITHOUT virtual (Static Binding)
// -------------------------------------------------------
class Shape
{
public:
    void draw()
    {
        cout << "  Shape::draw() — drawing a generic shape" << endl;
    }
    void info()
    {
        cout << "  Shape::info() — I am a Shape" << endl;
    }
};

class Circle : public Shape
{
public:
    void draw()
    {
        cout << "  Circle::draw() — drawing a circle ⬤" << endl;
    }
    void info()
    {
        cout << "  Circle::info() — I am a Circle" << endl;
    }
    void circleOnly()
    {
        cout << "  Circle::circleOnly() — only Circle has this" << endl;
    }
};

// -------------------------------------------------------
// EXAMPLE 2: WITH virtual (Dynamic Binding / Polymorphism)
// -------------------------------------------------------
class Animal
{
public:
    virtual void sound()
    {
        cout << "  Animal::sound() — generic animal sound" << endl;
    }
    virtual void breathe()
    {
        cout << "  Animal::breathe() — breathes air" << endl;
    }
    void eat()
    {
        // non-virtual — always calls Animal's version
        cout << "  Animal::eat() — eats food (non-virtual)" << endl;
    }
    virtual ~Animal() {} // virtual destructor — best practice with virtual methods
};

class Dog : public Animal
{
public:
    void sound() override
    { // override keyword makes it explicit
        cout << "  Dog::sound() — Woof! Woof!" << endl;
    }
    void breathe() override
    {
        cout << "  Dog::breathe() — breathes with nose and mouth" << endl;
    }
    void eat()
    {
        // non-virtual override — won't be called via parent pointer
        cout << "  Dog::eat() — eats kibble (non-virtual, won't be called via parent ptr)" << endl;
    }
    void fetch()
    {
        cout << "  Dog::fetch() — fetches the ball! (Dog-specific method)" << endl;
    }
};

class Cat : public Animal
{
public:
    void sound() override
    {
        cout << "  Cat::sound() — Meow!" << endl;
    }
};

// -------------------------------------------------------
// MAIN
// -------------------------------------------------------
int main()
{

    // -------------------------------------------
    // Part 1: Without virtual — Static Binding
    // -------------------------------------------
    cout << "=== Part 1: Without virtual (Static Binding) ===" << endl;

    Shape *shapePtr = new Circle(); // parent pointer holding child object

    cout << "Calling draw() via Shape* (pointing to Circle):" << endl;
    shapePtr->draw(); // calls Shape::draw() — NOT Circle::draw() (no virtual!)
    shapePtr->info(); // calls Shape::info()

    cout << endl;
    cout << "Calling draw() on actual Circle object:" << endl;
    Circle c;
    c.draw(); // calls Circle::draw() (direct object, correct)
    c.info();

    delete shapePtr;
    cout << endl;

    // -------------------------------------------
    // Part 2: With virtual — Dynamic Binding
    // -------------------------------------------
    cout << "=== Part 2: With virtual (Dynamic Binding) ===" << endl;

    Animal *animalPtr = new Dog(); // parent pointer holding Dog object

    cout << "Calling sound() via Animal* (pointing to Dog):" << endl;
    animalPtr->sound();   // calls Dog::sound() — virtual dispatches correctly!
    animalPtr->breathe(); // calls Dog::breathe() — virtual works!
    animalPtr->eat();     // calls Animal::eat() — non-virtual, so parent's version

    delete animalPtr;
    cout << endl;

    // -------------------------------------------
    // Part 3: Polymorphism with array of parent pointers
    // -------------------------------------------
    cout << "=== Part 3: Polymorphism — Array of Parent Pointers ===" << endl;
    Animal *animals[3];
    animals[0] = new Animal();
    animals[1] = new Dog();
    animals[2] = new Cat();

    for (int i = 0; i < 3; i++)
    {
        animals[i]->sound(); // calls the ACTUAL object's method (virtual dispatch)
    }

    for (int i = 0; i < 3; i++)
        delete animals[i];
    cout << endl;

    // -------------------------------------------
    // Part 4: Using parent REFERENCE to child object
    // -------------------------------------------
    cout << "=== Part 4: Parent Reference to Child ===" << endl;
    Dog myDog;
    Animal &animalRef = myDog; // parent reference to child object
    animalRef.sound();         // calls Dog::sound() via virtual dispatch
    animalRef.eat();           // calls Animal::eat() (non-virtual)

    cout << endl;

    // -------------------------------------------
    // Part 5: Accessing child-specific method
    // -------------------------------------------
    cout << "=== Part 5: Accessing Child-Specific Method ===" << endl;
    Animal *ptr = new Dog();
    // ptr->fetch();   // ERROR! Animal* doesn't know about fetch()
    Dog *dogPtr = dynamic_cast<Dog *>(ptr); // downcast safely
    if (dogPtr != nullptr)
    {
        dogPtr->fetch(); // NOW we can call Dog-specific method
    }
    delete ptr;

    return 0;
}

/*
    Time Complexity:  O(1) — all method calls and operations are constant time
    Space Complexity: O(1) — fixed number of objects created on heap (small constant)
*/
