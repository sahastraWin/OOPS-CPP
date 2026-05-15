/*
    QUESTION:
    Write a C++ program demonstrating UNARY OPERATOR OVERLOADING (++ and --).
    Create class 'Complex' with real part a and imaginary part b.
    Overload prefix ++ to increment both parts by 1.
    Overload prefix -- to decrement both parts by 1.
    Input: Two integers (real and imaginary parts)
    Output: Complex number after ++ and after --
*/

#include <bits/stdc++.h>
using namespace std;

class Complex
{
    int a, b;

public:
    void getvalue()
    {
        cout << "Enter two numbers (real imaginary): ";
        cin >> a >> b;
    }

    void operator++()
    {
        ++a;
        ++b;
    }

    void operator--()
    {
        --a;
        --b;
    }

    void display()
    {
        cout << a << " + " << b << "i" << endl;
    }
};

int main()
{
    Complex obj;
    obj.getvalue();

    ++obj;
    cout << "After ++: ";
    obj.display();

    --obj;
    cout << "After --: ";
    obj.display();

    return 0;
}

/*
    INTUITION:
    - UNARY OPERATORS take only ONE operand: ++ and -- modify the object itself.
    - void operator++() takes no parameters (the single operand is 'this' object).
    - ++obj is syntactic sugar for obj.operator++().
    - Unlike binary operators (which return a new object), unary ++ and -- here
      modify the object IN PLACE (they are void return type).
    - This is the PREFIX form: ++obj increments then uses.
      For POSTFIX form (obj++), the signature is operator++(int) with a dummy int param.
    - Real-world: iterator classes in STL (like vector::iterator) overload ++ to
      advance the iterator to the next element.

    TIME COMPLEXITY:  O(1) — two increments/decrements.
    SPACE COMPLEXITY: O(1) — modifies object in place, no extra memory.
*/
