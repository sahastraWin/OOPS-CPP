#include <bits/stdc++.h>
using namespace std;

int main() {
    float x = 32.2;
    decltype(x) z = 67.8;            // z gets the same type as x (float)

    cout << x << endl;
    cout << z << endl;
    return 0;
}

/*
Output:
32.2
67.8
*/
