#include <bits/stdc++.h>
using namespace std;

class Demo {
public:
    int x = 10, y = 20;
    void Display() const {                       // const function: cannot modify members
        /* x++;   ❌ ERROR: increment of member 'Demo::x' in read-only object */
        cout << "Demo: " << x << " " << y << endl;
    }
};

int main() {
    /* 1) const variable */
    const int a = 10;
    /* a++;   ❌ ERROR: read-only variable */

    int x = 10, y = 30;

    /* 2) pointer to const:  value is locked, address can change */
    const int *p1 = &x;
    p1 = &y;                                     // ✅ allowed
    /* ++*p1;   ❌ not allowed */

    /* 3) const pointer:  address is locked, value can change */
    int * const p2 = &x;
    ++*p2;                                       // ✅ allowed (x becomes 11)
    /* p2 = &y;   ❌ not allowed */

    /* 4) const pointer to const: both locked */
    const int * const p3 = &y;

    cout << "a = " << a << endl;
    cout << "*p1 = " << *p1 << endl;
    cout << "*p2 = " << *p2 << endl;
    cout << "*p3 = " << *p3 << endl;

    Demo d;
    d.Display();
    return 0;
}

/*
🧠 Trick: read the declaration from RIGHT to LEFT.
const int * p        -> p is a pointer to an int that is const
int * const p        -> p is a const pointer to an int

Output:
a = 10
*p1 = 30
*p2 = 11
*p3 = 30
Demo: 10 20
*/
