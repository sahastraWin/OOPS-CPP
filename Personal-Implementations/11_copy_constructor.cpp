/*
    QUESTION:
    Write a C++ program demonstrating the COPY CONSTRUCTOR (default/implicit).
    Create a class 'Example' with a parameterized constructor.
    Create one object, then initialize a second object as a copy of the first.
    Both objects should display identical values.
    Output: Values of both objects displayed
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
        cout << "Im Constructor" << endl;
    }

    void Display()
    {
        cout << "Values: " << a << "\t" << b << endl;
    }
};

int main()
{
    Example Object(10, 20);          // parameterized constructor
    Example Object2 = Object;        // implicit copy constructor called

    Object.Display();
    Object2.Display();

    return 0;
}

/*
    INTUITION:
    - When you write: Example Object2 = Object;
      C++ automatically calls the COPY CONSTRUCTOR.
    - The DEFAULT COPY CONSTRUCTOR (provided by the compiler if you don't write one)
      performs a MEMBERWISE (shallow) copy: copies each member variable's value.
      So Object2.a = Object.a = 10, Object2.b = Object.b = 20.
    - Note: only "Im Constructor" prints once (for Object) — the copy constructor
      doesn't print because we didn't define a custom copy constructor.
    - Shallow copy works fine for plain data types (int, float).
    - For pointer members, you MUST write a custom copy constructor to do a
      DEEP COPY (copy pointed-to data, not just the pointer address).
    - Syntax equivalents for copy construction:
        Example Object2 = Object;      // copy initialization
        Example Object2(Object);       // direct copy construction

    TIME COMPLEXITY:  O(1) — constant-time memberwise copy.
    SPACE COMPLEXITY: O(1) — two objects, each with two int members.
*/
