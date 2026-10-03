#include <bits/stdc++.h>
using namespace std;

class Base {
public:
    Base() { cout << "Base Class Constructor" << endl; }
    ~Base() { cout << "Base Class Destructor" << endl; }
};
class Derived : public Base {
public:
    Derived() { cout << "Derived Class Constructor" << endl; }
    ~Derived() { cout << "Derived Class Destructor" << endl; }
};

int main() {
    Derived d;
    return 0;
}

/*
🧠 Build: parent first, then child.  Destroy: child first, then parent.

Output:
Base Class Constructor
Derived Class Constructor
Derived Class Destructor
Base Class Destructor
*/
