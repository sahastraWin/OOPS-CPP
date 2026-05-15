/*
    QUESTION:
    Write a C++ program demonstrating the COPY CONSTRUCTOR with output
    showing both objects display the same values after copying.
    Create an object, copy it, and verify both have identical data.
    Output: Both objects show "Values: 10  20"
*/

#include <bits/stdc++.h>
using namespace std;

class Example
{
    int a, b;

public:
    Example(int x, int y)
    {
        a = x;
        b = y;
        cout << "Parameterized Constructor called" << endl;
    }

    // Explicit copy constructor
    Example(const Example &obj)
    {
        a = obj.a;
        b = obj.b;
        cout << "Copy Constructor called" << endl;
    }

    void Display()
    {
        cout << "Values: " << a << "\t" << b << endl;
    }
};

int main()
{
    Example Object(10, 20);       // parameterized constructor
    Example Object2 = Object;     // copy constructor

    Object.Display();
    Object2.Display();

    return 0;
}

/*
    INTUITION:
    - This version defines an EXPLICIT copy constructor vs. the compiler-generated one.
    - The explicit copy constructor: Example(const Example &obj)
        - Takes a CONST REFERENCE to the source object (prevents modification and copying).
        - Copies each member manually: a = obj.a, b = obj.b.
    - When is the copy constructor called?
        1. Example Object2 = Object;         // copy initialization
        2. Example Object2(Object);          // direct copy construction
        3. Passing by value: func(Object)    // function call copies the arg
        4. Returning by value: return Object // function returns a copy
    - Custom copy constructors are needed when the class has POINTER MEMBERS
      (to avoid two objects pointing to the same memory — shallow vs deep copy).
    - Here, with simple int members, the explicit copy constructor does the same
      thing as the compiler-generated one — but it PRINTS a message for visibility.

    TIME COMPLEXITY:  O(1) — constant-time member copying.
    SPACE COMPLEXITY: O(1) — two objects, each with two ints.
*/
