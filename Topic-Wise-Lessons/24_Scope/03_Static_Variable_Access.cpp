#include <bits/stdc++.h>
using namespace std;

class Test {
    static int x;                   // private static
public:
    static int y;                   // public static
    void func(int x) {
        cout << "Value of static x is " << Test::x << endl;   // class x
        cout << "Value of local x is " << x << endl;          // parameter x
    }
};

/* Static members MUST be defined outside the class */
int Test::x = 1;
int Test::y = 2;

int main() {
    Test obj;
    int x = 3;
    obj.func(x);
    cout << "Test::y = " << Test::y << endl;   // no object needed
    return 0;
}

/*
Output:
Value of static x is 1
Value of local x is 3
Test::y = 2
*/
