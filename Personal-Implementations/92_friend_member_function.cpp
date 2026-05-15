/*
    QUESTION:
    Write a C++ program demonstrating a FRIEND MEMBER FUNCTION.
    Class A has a method showB(B&) declared as a friend of class B.
    A::showB() can access B's private member 'b' directly.
    This shows that a single MEMBER FUNCTION of one class can be a friend
    of another class (more selective than a friend class).
    Output: B's private value accessed via A's friend member function
*/

#include <bits/stdc++.h>
using namespace std;

// Forward declaration needed since A references B before B is defined
class B;

class A
{
public:
    void showB(B &);  // declared here, defined after B
};

class B
{
    int b;

public:
    B() { b = 20; }

    // Only A::showB can access B's private members
    friend void A::showB(B &);
};

// Now we can define A::showB since B is fully defined
void A::showB(B &x)
{
    cout << "B's private member b = " << x.b << endl;
}

int main()
{
    A a;
    B x;
    a.showB(x);

    return 0;
}

/*
    INTUITION:
    - FRIEND MEMBER FUNCTION: more selective than friend class.
      Only A::showB() gets access to B's privates (not ALL of A's methods).
    - FORWARD DECLARATION 'class B;' is needed because A::showB(B&) references B
      before B is defined. Without it, the compiler doesn't know what B is.
    - ORDERING challenge:
        1. Declare class A (declare showB, but can't define it yet — B unknown).
        2. Fully define class B (now B is complete; can declare friend A::showB).
        3. Define A::showB() — now B is fully known, can access b.
    - This demonstrates the interdependency and forward declaration technique
      needed in some OOP designs.
    - GRANULARITY: friend function < friend member function < friend class (most permissive).

    TIME COMPLEXITY:  O(1) — single member access and print.
    SPACE COMPLEXITY: O(1) — one int member each in A (none) and B.
*/
