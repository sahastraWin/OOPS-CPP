#include <bits/stdc++.h>
using namespace std;

class Base {
public:
    int x = 1;
protected:
    int y = 2;
private:
    int z = 3;
public:
    int getZ() { return z; }
};

class PublicDerived : public Base {
public:
    int getY() { return y; }                 // y stays protected, usable inside
};
class ProtectedDerived : protected Base {
public:
    int getX() { return x; }                 // x became protected
    int getY() { return y; }
};
class PrivateDerived : private Base {
public:
    int getX() { return x; }                 // x became private
    int getY() { return y; }
};

int main() {
    PublicDerived pd;
    cout << "PublicDerived    -> x directly: " << pd.x << ", y via getter: " << pd.getY() << endl;

    ProtectedDerived pr;
    /* cout << pr.x;   ❌ ERROR: x is protected now */
    cout << "ProtectedDerived -> x via getter: " << pr.getX() << endl;

    PrivateDerived pv;
    /* cout << pv.x;   ❌ ERROR: x is private now */
    cout << "PrivateDerived   -> x via getter: " << pv.getX() << endl;
    return 0;
}

/*
📊 Cheat sheet (how Base members look inside the derived class):

| Base member | public inherit | protected inherit | private inherit |
|-------------|----------------|-------------------|-----------------|
| public x    | public         | protected         | private         |
| protected y | protected      | protected         | private         |
| private z   | NOT accessible | NOT accessible    | NOT accessible  |

Output:
PublicDerived    -> x directly: 1, y via getter: 2
ProtectedDerived -> x via getter: 1
PrivateDerived   -> x via getter: 1
*/
