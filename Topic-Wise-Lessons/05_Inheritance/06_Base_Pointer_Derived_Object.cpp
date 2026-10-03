#include <bits/stdc++.h>
using namespace std;

class Base {
public:
    void fun1() { cout << "fun1 of Base Class" << endl; }
};
class Derived : public Base {
public:
    void fun2() { cout << "fun2 of Derived Class" << endl; }
};

int main() {
    Derived d;
    Base *p = &d;                   // allowed: a Derived IS-A Base
    p->fun1();                      // OK: fun1 exists in Base
    /* p->fun2();   ❌ ERROR: 'class Base' has no member named 'fun2' */

    /* To reach fun2, cast the pointer back to Derived* */
    static_cast<Derived*>(p)->fun2();
    return 0;
}

/*
🧠 A pointer only "sees" the members of ITS OWN type (Base).

Output:
fun1 of Base Class
fun2 of Derived Class
*/
