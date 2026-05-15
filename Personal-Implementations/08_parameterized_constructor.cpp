/*
    QUESTION:
    Write a C++ program demonstrating a PARAMETERIZED CONSTRUCTOR.
    Create a class 'Example' with private members a and b.
    The constructor accepts two integers x and y to initialize a and b.
    A Display() method prints the values.
    Input: Values passed directly at object creation: Example Object(10, 20)
    Output: Constructor message and "Values: 10  20"
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
    Example Object(10, 20);
    Object.Display();
    return 0;
}

/*
    INTUITION:
    - A PARAMETERIZED CONSTRUCTOR accepts arguments, enabling different objects
      to be initialized with different values at creation time.
    - Syntax: Example Object(10, 20) → calls Example(int x, int y) with x=10, y=20.
    - This is more flexible than a default constructor which always sets the same values.
    - The parameters are local to the constructor; x and y are copied into a and b.
    - Key advantage: objects can be initialized in ONE step rather than creating
      then calling a setter method.
    - If only parameterized constructor exists, you MUST provide arguments —
      Example Object; alone would be a compile error.

    TIME COMPLEXITY:  O(1) — object creation and display are constant time.
    SPACE COMPLEXITY: O(1) — one object with two int members.
*/
