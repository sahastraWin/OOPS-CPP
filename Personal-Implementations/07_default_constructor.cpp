/*
    QUESTION:
    Write a C++ program demonstrating a class with a DEFAULT CONSTRUCTOR.
    Create a class 'Example' with private members a and b.
    The default constructor initializes a=10, b=20 and prints a message.
    A Display() method prints the values.
    Output: Constructor message and "Values: 10  20"
*/

#include <bits/stdc++.h>
using namespace std;

class Example
{
    int a, b;

public:
    Example()
    {
        a = 10;
        b = 20;
        cout << "Im Constructor" << endl;
    }

    void Display()
    {
        cout << "Values: " << a << "\t" << b << endl;
    }
};

int main()
{
    Example Object;
    Object.Display();
    return 0;
}

/*
    INTUITION:
    - A CLASS bundles data (members) and behavior (methods) together.
    - A CONSTRUCTOR is a special method automatically called when an object
      is created. It has the same name as the class and no return type.
    - DEFAULT CONSTRUCTOR takes no parameters — it runs when you write:
        Example Object;  (no arguments)
    - Private members a, b are hidden from outside — only class methods access them.
    - Public methods (Display) provide controlled access to private data.
    - Encapsulation principle: data is private, interface is public.
    - When Object is created → Constructor runs → a=10, b=20 set automatically.

    TIME COMPLEXITY:  O(1) — object creation and display are constant time.
    SPACE COMPLEXITY: O(1) — one object with two int members.
*/
