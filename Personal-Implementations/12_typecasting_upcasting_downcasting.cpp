/*
    Question:
    Explain and demonstrate Typecasting in C++ in detail:
    1. Implicit Typecasting (Automatic / Widening)
    2. Explicit Typecasting (C-style and C++ style)
    3. Upcasting — converting child class pointer to parent class pointer (safe)
    4. Downcasting — converting parent class pointer to child class pointer
       a. static_cast (no runtime check — unsafe if wrong)
       b. dynamic_cast (runtime check — safe, returns nullptr if invalid)
    5. const_cast, reinterpret_cast (brief demo)

    Intuition:
    Think of classes like a family tree:
    - Parent (Animal) ← Child (Dog)

    UPCASTING (Child → Parent):
    Like saying "a Dog IS an Animal" — always safe.
    You can always treat a more specific thing as a more general one.
    A Dog can always fill the role of an Animal.

    DOWNCASTING (Parent → Child):
    Like saying "this Animal IS a Dog" — may not be true!
    A parent pointer might actually point to a Cat, not a Dog.
    So we must CHECK at runtime. dynamic_cast does this safely.
    static_cast trusts you blindly — wrong downcast = undefined behavior.

    Rule of thumb:
    - Upcast freely (implicit or explicit)
    - Downcast carefully (prefer dynamic_cast)

    Time Complexity:  O(1) — all casts are constant time
    Space Complexity: O(1) — no extra allocation
*/

#include <bits/stdc++.h>
using namespace std;

// -------------------------------------------------------
// Class hierarchy for Upcasting / Downcasting demo
// -------------------------------------------------------
class Animal
{
public:
    string name;
    Animal(string n) : name(n) {}
    virtual void speak()
    {
        cout << "  Animal [" << name << "] makes a sound" << endl;
    }
    virtual ~Animal() {}
};

class Dog : public Animal
{
public:
    Dog(string n) : Animal(n) {}
    void speak() override
    {
        cout << "  Dog [" << name << "] says: Woof!" << endl;
    }
    void fetch()
    {
        cout << "  Dog [" << name << "] fetches the ball!" << endl;
    }
};

class Cat : public Animal
{
public:
    Cat(string n) : Animal(n) {}
    void speak() override
    {
        cout << "  Cat [" << name << "] says: Meow!" << endl;
    }
    void purr()
    {
        cout << "  Cat [" << name << "] purrs..." << endl;
    }
};

// -------------------------------------------------------
// MAIN
// -------------------------------------------------------
int main()
{

    // -------------------------------------------
    // Part 1: Primitive Implicit Typecasting
    // -------------------------------------------
    cout << "=== Part 1: Implicit Typecasting (Widening) ===" << endl;
    int i = 42;
    double d = i; // int → double (widening, automatic, no data loss)
    cout << "int i = " << i << endl;
    cout << "double d = i → " << d << endl;

    char ch = 'A';
    int ascii = ch; // char → int (gets ASCII value)
    cout << "char ch = '" << ch << "', int ascii = " << ascii << endl;
    cout << endl;

    // -------------------------------------------
    // Part 2: Explicit Typecasting (Narrowing)
    // -------------------------------------------
    cout << "=== Part 2: Explicit Typecasting (Narrowing) ===" << endl;
    double pi = 3.14159;
    int truncated = (int)pi;             // C-style cast — truncates decimal
    int cppStyle = static_cast<int>(pi); // C++ style — same result

    cout << "double pi = " << pi << endl;
    cout << "(int)pi (C-style)         = " << truncated << " (decimal truncated)" << endl;
    cout << "static_cast<int>(pi)      = " << cppStyle << endl;
    cout << endl;

    // Integer division vs float division
    int x = 7, y = 2;
    double result1 = x / y;                      // integer division → 3.0
    double result2 = (double)x / y;              // cast first → 3.5
    double result3 = static_cast<double>(x) / y; // C++ style → 3.5
    cout << "7 / 2 (int division)      = " << result1 << endl;
    cout << "(double)7 / 2             = " << result2 << endl;
    cout << "static_cast<double>(7)/2  = " << result3 << endl;
    cout << endl;

    // -------------------------------------------
    // Part 3: UPCASTING — Child to Parent (Always Safe)
    // -------------------------------------------
    cout << "=== Part 3: UPCASTING (Child → Parent) ===" << endl;

    Dog dog("Buddy");
    Cat cat("Whiskers");

    // Implicit upcast — no cast needed, always safe
    Animal *animalPtr1 = &dog; // Dog* → Animal* (implicit upcast)
    Animal *animalPtr2 = &cat; // Cat* → Animal* (implicit upcast)

    cout << "Implicit upcast — Animal* pointing to Dog:" << endl;
    animalPtr1->speak(); // calls Dog::speak() via virtual dispatch

    cout << "Implicit upcast — Animal* pointing to Cat:" << endl;
    animalPtr2->speak(); // calls Cat::speak()

    // Explicit upcast — same result, just more verbose
    Animal *explicitUpcast = static_cast<Animal *>(&dog);
    cout << "Explicit upcast using static_cast:" << endl;
    explicitUpcast->speak();

    cout << endl;

    // -------------------------------------------
    // Part 4: DOWNCASTING — Parent to Child
    // -------------------------------------------
    cout << "=== Part 4: DOWNCASTING (Parent → Child) ===" << endl;

    Animal *ptr = new Dog("Max"); // parent pointer holds a Dog

    // 4a: static_cast downcast — NO runtime check, trusts you!
    cout << "--- static_cast downcast (unsafe, no runtime check) ---" << endl;
    Dog *dogPtr1 = static_cast<Dog *>(ptr); // works IF ptr truly points to a Dog
    dogPtr1->speak();
    dogPtr1->fetch();
    cout << "Works! But dangerous if ptr was actually a Cat — undefined behavior!" << endl;
    cout << endl;

    // 4b: dynamic_cast downcast — WITH runtime check (safe!)
    cout << "--- dynamic_cast downcast (safe, with runtime check) ---" << endl;
    Dog *dogPtr2 = dynamic_cast<Dog *>(ptr); // checks at runtime if ptr is really a Dog
    if (dogPtr2 != nullptr)
    {
        cout << "dynamic_cast succeeded! ptr is actually a Dog." << endl;
        dogPtr2->fetch();
    }
    else
    {
        cout << "dynamic_cast failed! ptr is NOT a Dog." << endl;
    }
    cout << endl;

    // 4c: dynamic_cast FAILING (wrong type)
    cout << "--- dynamic_cast failing on wrong type ---" << endl;
    Animal *catPtr = new Cat("Luna");
    Dog *wrongDog = dynamic_cast<Dog *>(catPtr); // catPtr points to Cat, not Dog
    if (wrongDog != nullptr)
    {
        cout << "dynamic_cast succeeded!" << endl;
    }
    else
    {
        cout << "dynamic_cast returned nullptr — catPtr is NOT a Dog (it's a Cat)" << endl;
        cout << "Safe! No crash, we just get nullptr." << endl;
    }
    cout << endl;

    // -------------------------------------------
    // Part 5: const_cast
    // -------------------------------------------
    cout << "=== Part 5: const_cast ===" << endl;
    const int constVal = 10;
    int *modifiable = const_cast<int *>(&constVal); // removes const qualifier
    *modifiable = 20;                               // modifying — technically undefined behavior for truly const vars
    cout << "constVal = " << constVal << " | *modifiable = " << *modifiable << endl;
    cout << "Note: Modifying truly const data via const_cast is undefined behavior!" << endl;
    cout << endl;

    // -------------------------------------------
    // Part 6: reinterpret_cast
    // -------------------------------------------
    cout << "=== Part 6: reinterpret_cast ===" << endl;
    int num = 65;
    char *charPtr = reinterpret_cast<char *>(&num); // treats int memory as char
    cout << "int num = " << num << " | As char = " << *charPtr << endl;
    cout << "Note: reinterpret_cast is the most dangerous cast — use sparingly!" << endl;

    delete ptr;
    delete catPtr;
    return 0;
}

/*
    Time Complexity:  O(1) — all typecasts and operations are constant time
                     dynamic_cast: O(depth of inheritance hierarchy) — typically O(1)
    Space Complexity: O(1) — no extra data structures created
*/
