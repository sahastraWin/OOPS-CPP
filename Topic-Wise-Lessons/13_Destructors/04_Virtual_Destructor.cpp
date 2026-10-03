#include <bits/stdc++.h>
using namespace std;

/* ----- ✅ A) virtual destructor ----- */
class Base {
public:
    Base() { cout << "Base Class Constructor" << endl; }
    virtual ~Base() { cout << "Base Class Destructor" << endl; }
};
class Derived : public Base {
public:
    Derived() { cout << "Derived Class Constructor" << endl; }
    ~Derived() { cout << "Derived Class Destructor" << endl; }
};

/* ----- ✅ B) pure virtual destructor (still needs a body!) ----- */
class Abstract {
public:
    Abstract() { cout << "Abstract Constructor" << endl; }
    virtual ~Abstract() = 0;
};
Abstract::~Abstract() { cout << "Abstract Destructor" << endl; }

class Concrete : public Abstract {
public:
    Concrete() { cout << "Concrete Constructor" << endl; }
    ~Concrete() { cout << "Concrete Destructor" << endl; }
};

int main() {
    cout << "--- A) virtual destructor ---" << endl;
    Base *p = new Derived();
    delete p;

    cout << "--- B) pure virtual destructor ---" << endl;
    Abstract *a = new Concrete();
    delete a;
    return 0;
}

/*
⚠️ If Base's destructor is NOT virtual, then  delete p;  (p is Base*, object is Derived)
only runs ~Base() and skips ~Derived(). That is undefined behaviour and leaks memory.
Rule: if a class has virtual functions or is meant to be a base class,
make its destructor virtual.

Output:
--- A) virtual destructor ---
Base Class Constructor
Derived Class Constructor
Derived Class Destructor
Base Class Destructor
--- B) pure virtual destructor ---
Abstract Constructor
Concrete Constructor
Concrete Destructor
Abstract Destructor
*/
