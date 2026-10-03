#include <bits/stdc++.h>
using namespace std;

/* ❌ WITHOUT virtual */
class Base1 {
public:
    void Display() { cout << "Display of Base" << endl; }
};
class Derived1 : public Base1 {
public:
    void Display() { cout << "Display of Derived" << endl; }
};

/* ✅ WITH virtual */
class Base2 {
public:
    virtual void Display() { cout << "Display of Base" << endl; }
};
class Derived2 : public Base2 {
public:
    void Display() override { cout << "Display of Derived" << endl; }
};

int main() {
    Derived1 d1;
    Base1 *p1 = &d1;
    cout << "Without virtual: ";
    p1->Display();                  // decided by the POINTER type

    Derived2 d2;
    Base2 *p2 = &d2;
    cout << "With virtual:    ";
    p2->Display();                  // decided by the OBJECT type
    return 0;
}

/*
Output:
Without virtual: Display of Base
With virtual:    Display of Derived
*/
