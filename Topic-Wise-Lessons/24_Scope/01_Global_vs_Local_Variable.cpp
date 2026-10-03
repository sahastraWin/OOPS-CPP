#include <bits/stdc++.h>
using namespace std;

int x = 4;                          // global

int main() {
    int x = 10;                     // local (hides the global one)
    cout << "Value of global x is " << ::x << endl;   // ::x -> global
    cout << "Value of local x is " << x << endl;
    return 0;
}

/*
Output:
Value of global x is 4
Value of local x is 10
*/
