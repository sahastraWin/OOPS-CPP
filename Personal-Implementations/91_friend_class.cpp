/*
    QUESTION:
    Write a C++ program demonstrating a FRIEND CLASS.
    Class A has a private member 'a'.
    Class B is declared as a friend of A, granting it full access to A's private members.
    B's method show() accesses A's private 'a' directly.
    Output: Value of A's private member accessed through friend class B
*/

#include <bits/stdc++.h>
using namespace std;

class A
{
    int a;

public:
    A() { a = 10; }

    friend class B;   // B has full access to A's private members
};

class B
{
public:
    void show(A &x)
    {
        cout << "A's private member a = " << x.a << endl;
    }
};

int main()
{
    A objA;
    B objB;
    objB.show(objA);

    return 0;
}

/*
    INTUITION:
    - FRIEND CLASS: declaring 'friend class B' inside A grants ALL of B's methods
      access to ALL of A's private and protected members.
    - Without 'friend class B': B::show() would fail to compile since x.a is private.
    - With 'friend class B': B::show() can access x.a directly.
    - DIFFERENCE from friend function:
        Friend function: one specific function gets access.
        Friend class: ALL methods of the class get access.
    - The friendship is ONE-WAY and NON-TRANSITIVE:
        B is friend of A → B can access A's privates.
        A is NOT friend of B (unless declared explicitly).
        C is NOT friend of A just because B is.
    - Use sparingly — friendship breaks encapsulation when overused.

    TIME COMPLEXITY:  O(1) — single member access and print.
    SPACE COMPLEXITY: O(1) — one int member.
*/
