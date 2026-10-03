#include <bits/stdc++.h>
using namespace std;

class Base {
public:
    Base() { cout << "Non-param Base" << endl; }
    Base(int x) { cout << "Param of Base " << x << endl; }
};

class Derived : public Base {
public:
    Derived() { cout << "Non-Param Derived" << endl; }
    Derived(int y) { cout << "Param of Derived " << y << endl; }
    Derived(int x, int y) : Base(x) {        // explicitly choose Base(int)
        cout << "Param of Derived " << y << endl;
    }
};

int main() {
    cout << "--- d1 ---" << endl;
    Derived d1;
    cout << "--- d2 ---" << endl;
    Derived d2(7);
    cout << "--- d3 ---" << endl;
    Derived d3(5, 10);
    return 0;
}

/*
🧠 Rule: if you do NOT name a parent constructor, the compiler silently calls
the parent's DEFAULT constructor. Use  : Base(x)  to pick a different one.

Output:
--- d1 ---
Non-param Base
Non-Param Derived
--- d2 ---
Non-param Base
Param of Derived 7
--- d3 ---
Param of Base 5
Param of Derived 10
*/
