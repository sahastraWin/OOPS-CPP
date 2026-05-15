/*
    QUESTION:
    Write a C++ program demonstrating a GLOBAL FRIEND FUNCTION (non-member friend).
    Class A has a private member 'a'.
    A non-member function show(A&) is declared as a friend of A, allowing it
    to access A's private data directly.
    Output: A's private value accessed via global friend function
*/

#include <bits/stdc++.h>
using namespace std;

class A
{
    int a;

public:
    A() { a = 30; }

    // Declare global function show() as a friend of class A
    friend void show(A &);
};

// Global function — NOT a member of A, but can access A's private data
void show(A &x)
{
    cout << "A's private member a = " << x.a << endl;
}

int main()
{
    A obj;
    show(obj);  // called like a regular function, not obj.show()

    return 0;
}

/*
    INTUITION:
    - GLOBAL FRIEND FUNCTION: a free (non-member) function that is granted
      access to a class's private members.
    - Declaration inside the class: friend void show(A&) — this is just a
      GRANT OF FRIENDSHIP, not a member function definition.
    - Definition outside: void show(A &x) { ... } — regular global function.
    - Call syntax: show(obj) — NOT obj.show() (it's not a member!).
    - WHY useful? When a function naturally operates on a class but doesn't
      logically belong as a member (e.g., stream insertion operator<<).
    - The friend declaration can appear anywhere in the class (public, private,
      protected section) — access specifiers don't affect friendship.
    - Most common use: overloading << and >> operators for user-defined types.

    TIME COMPLEXITY:  O(1) — single member access and print.
    SPACE COMPLEXITY: O(1) — one int member.
*/
