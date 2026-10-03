#include <bits/stdc++.h>
using namespace std;

/* 🔒 1) final on a METHOD: children cannot override it */
class Parent {
public:
    virtual void show() final {
        cout << "Parent::show (cannot be overridden)" << endl;
    }
};
class Child : public Parent {
public:
    /* void show() {}   ❌ ERROR: overriding final function 'Parent::show()' */
    void other() { cout << "Child::other works fine" << endl; }
};

/* 🔒 2) final on a CLASS: nobody can inherit from it */
class Locked final {
public:
    void hello() { cout << "Locked::hello" << endl; }
};
/* class Try : public Locked {};   ❌ ERROR: cannot derive from 'final' base 'Locked' */

int main() {
    Child c;
    c.show();
    c.other();
    Locked l;
    l.hello();
    return 0;
}

/*
Output:
Parent::show (cannot be overridden)
Child::other works fine
Locked::hello
*/
