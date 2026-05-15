/*
    Question:
    Explain and demonstrate the Scope Resolution Operator (::) in C++.
    Show all its usages:
    1. Accessing global variable when local variable has the same name
    2. Defining class member functions outside the class
    3. Accessing static class members
    4. Using with namespaces
    5. In inheritance — calling parent class methods

    Intuition:
    The :: operator is like a "GPS address" — it tells the compiler EXACTLY
    where to find something when the name is ambiguous.
    It says: "Look in THIS specific namespace/class, not the local one."

    Think of it like a full address:
    - Without :: → looks in local scope first (like using just "Market Street")
    - With ::    → looks in specified scope (like "Mumbai::Market Street" — precise)

    Without :: → compiler picks the closest (innermost) scope
    With ::    → you explicitly say which scope to access

    Time Complexity:  O(1) — all demonstrations are constant time
    Space Complexity: O(1) — no extra data structures
*/

#include <bits/stdc++.h>
using namespace std;

// -------------------------------------------------------
// USAGE 1: Global variable with same name as local
// -------------------------------------------------------
int value = 1000; // global variable named 'value'

// -------------------------------------------------------
// USAGE 4: Custom namespace
// -------------------------------------------------------
namespace MathUtils
{
    int PI = 3;
    void showPI()
    {
        cout << "MathUtils::PI = " << PI << endl;
    }
}

namespace Physics
{
    int PI = 31416; // different PI in different namespace
    void showPI()
    {
        cout << "Physics::PI = " << PI << endl;
    }
}

// -------------------------------------------------------
// USAGE 2 & 3: Class with static member and outside definition
// -------------------------------------------------------
class Counter
{
public:
    static int count; // static class member — shared by all objects
    int id;

    // DECLARATION inside class
    Counter(int id);
    void show();

    static void showCount(); // static method declaration
};

// Static member INITIALIZATION — must be outside class with ::
int Counter::count = 0;

// DEFINITION outside class using :: operator
Counter::Counter(int id)
{
    this->id = id;
    Counter::count++; // using :: to access static member (optional here, but explicit)
}

void Counter::show()
{
    cout << "  Object id = " << id
         << " | Total Count = " << Counter::count << endl;
}

void Counter::showCount()
{
    cout << "  Static count = " << Counter::count << endl;
}

// -------------------------------------------------------
// USAGE 5: Inheritance — calling parent method using ::
// -------------------------------------------------------
class Animal
{
public:
    void speak()
    {
        cout << "  Animal::speak() — generic animal sound" << endl;
    }
};

class Dog : public Animal
{
public:
    void speak()
    {
        cout << "  Dog::speak() — Woof!" << endl;
        Animal::speak(); // explicitly calling PARENT's version using ::
    }
};

// -------------------------------------------------------
// MAIN
// -------------------------------------------------------
int main()
{

    // -------------------------------------------
    // Usage 1: Global vs Local with same name
    // -------------------------------------------
    cout << "=== Usage 1: Global vs Local Variable ===" << endl;
    int value = 500;                              // local variable — same name as global
    cout << "Local  value = " << value << endl;   // picks local
    cout << "Global value = " << ::value << endl; // :: forces global access
    cout << endl;

    // -------------------------------------------
    // Usage 2: Class member function defined outside
    // -------------------------------------------
    cout << "=== Usage 2: Member Functions Defined Outside Class ===" << endl;
    Counter c1(1);
    c1.show();
    Counter c2(2);
    c2.show();
    Counter c3(3);
    c3.show();
    cout << endl;

    // -------------------------------------------
    // Usage 3: Static member access via ::
    // -------------------------------------------
    cout << "=== Usage 3: Static Member via Scope Resolution ===" << endl;
    Counter::showCount(); // calling static method via class name and ::
    cout << "Counter::count = " << Counter::count << endl;
    cout << endl;

    // -------------------------------------------
    // Usage 4: Namespace with ::
    // -------------------------------------------
    cout << "=== Usage 4: Namespace with :: ===" << endl;
    MathUtils::showPI();
    Physics::showPI();
    cout << "MathUtils::PI = " << MathUtils::PI << endl;
    cout << "Physics::PI   = " << Physics::PI << endl;
    cout << endl;

    // -------------------------------------------
    // Usage 5: Calling parent method in inheritance
    // -------------------------------------------
    cout << "=== Usage 5: Parent Method via :: in Inheritance ===" << endl;
    Dog d;
    d.speak(); // calls Dog::speak which internally calls Animal::speak via ::

    return 0;
}

/*
    Time Complexity:  O(1) — all operations are constant time
    Space Complexity: O(1) — a few objects and variables, no dynamic allocation
*/
