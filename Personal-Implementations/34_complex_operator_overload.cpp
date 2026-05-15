/*
    QUESTION:
    Write a C++ program to add and subtract COMPLEX NUMBERS using operator overloading.
    Create class 'Complex' with real part a and imaginary part b.
    Overload + and - operators to add/subtract complex numbers.
    Input: Two complex numbers (a+bi and c+di)
    Output: Their sum and difference in the form a+bi
*/

#include <bits/stdc++.h>
using namespace std;

class Complex
{
    int a, b;

public:
    void getvalue()
    {
        cout << "Enter real and imaginary parts: ";
        cin >> a >> b;
    }

    Complex operator+(Complex ob)
    {
        Complex t;
        t.a = a + ob.a;
        t.b = b + ob.b;
        return t;
    }

    Complex operator-(Complex ob)
    {
        Complex t;
        t.a = a - ob.a;
        t.b = b - ob.b;
        return t;
    }

    void display()
    {
        cout << a << " + " << b << "i" << endl;
    }
};

int main()
{
    Complex obj1, obj2, res1, res2;

    cout << "Enter first complex number:" << endl;
    obj1.getvalue();

    cout << "Enter second complex number:" << endl;
    obj2.getvalue();

    res1 = obj1 + obj2;
    res2 = obj1 - obj2;

    cout << "Sum:        ";
    res1.display();

    cout << "Difference: ";
    res2.display();

    return 0;
}

/*
    INTUITION:
    - Complex numbers: (a + bi) + (c + di) = (a+c) + (b+d)i
                       (a + bi) - (c + di) = (a-c) + (b-d)i
    - By overloading both + and -, we can write obj1 + obj2 and obj1 - obj2
      just as we would with built-in numeric types.
    - Each operator function:
        - 'this' → obj1 (left operand)
        - 'ob'   → obj2 (right operand)
        - Returns a new Complex object with the computed result.
    - The temp object 't' is created, filled, and returned by value.
    - This demonstrates that a class can overload MULTIPLE operators.
    - Note: operator+(ob) takes ob by VALUE (copy) — could also use const reference.

    TIME COMPLEXITY:  O(1) — two additions/subtractions per operation.
    SPACE COMPLEXITY: O(1) — one temporary Complex object per operation.
*/
