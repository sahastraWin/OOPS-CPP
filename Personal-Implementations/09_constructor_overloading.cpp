/*
    QUESTION:
    Write a C++ program demonstrating CONSTRUCTOR OVERLOADING.
    Create a class 'Example' with:
    - A default constructor that sets a=50, b=100
    - A parameterized constructor that takes x, y
    Create two objects: one using each constructor.
    Output: Both objects' values displayed
*/

#include <bits/stdc++.h>
using namespace std;

class Example
{
    int a, b;

public:
    // Default constructor
    Example()
    {
        a = 50;
        b = 100;
        cout << "Im Constructor (default)" << endl;
    }

    // Parameterized constructor
    Example(int x, int y)
    {
        a = x;
        b = y;
        cout << "Im Constructor (parameterized)" << endl;
    }

    void Display()
    {
        cout << "Values: " << a << "\t" << b << endl;
    }
};

int main()
{
    Example Object(10, 20);   // calls parameterized constructor
    Example Object2;           // calls default constructor

    Object.Display();
    Object2.Display();

    return 0;
}

/*
    INTUITION:
    - CONSTRUCTOR OVERLOADING means having multiple constructors with the same
      class name but different parameter lists (different signatures).
    - The compiler selects the correct constructor based on the arguments:
        Example Object(10, 20) → matches Example(int x, int y)
        Example Object2        → matches Example() (no args)
    - This is a form of POLYMORPHISM at the constructor level.
    - Overloading is resolved at COMPILE TIME (static dispatch) based on
      the number and types of arguments.
    - Real-world use: string class has many constructors (from char*, copy, etc.)

    TIME COMPLEXITY:  O(1) — constant-time object creation and display.
    SPACE COMPLEXITY: O(1) — two objects, each with two int members.
*/
