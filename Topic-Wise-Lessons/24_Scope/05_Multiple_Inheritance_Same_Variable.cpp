#include <bits/stdc++.h>
using namespace std;

class A {
protected:
    int x;
public:
    A() { x = 10; }
};

class B {
protected:
    int x;
public:
    B() { x = 20; }
};

class C : public A, public B {
public:
    void fun() {
        /* cout << x;   ❌ ERROR: ambiguous (A::x or B::x?) */
        cout << "A's x is " << A::x << endl;     // :: picks the parent
        cout << "B's x is " << B::x << endl;
    }
};

int main() {
    C c;
    c.fun();
    return 0;
}

/*
Output:
A's x is 10
B's x is 20
*/
