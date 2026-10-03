#include <bits/stdc++.h>
using namespace std;

class Base {
public:
    void Display() { cout << "Base Class Display Function" << endl; }
};
class Derived : public Base {
public:
    void Display() { cout << "Derived Class Display Function" << endl; }   // overrides
};

int main() {
    Derived d;
    d.Display();                    // Derived's version hides Base's
    d.Base::Display();              // still reachable using ::
    return 0;
}

/*
Output:
Derived Class Display Function
Base Class Display Function
*/
