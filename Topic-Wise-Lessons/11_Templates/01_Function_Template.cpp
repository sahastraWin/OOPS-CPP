#include <bits/stdc++.h>
using namespace std;

/* One function works for ANY pair of types */
template <class T, class R>
void Add(T x, R y) {
    cout << x + y << endl;
}

int main() {
    Add(4, 24);                      // int + int
    Add(25.7f, 67.6f);               // float + float
    Add(14, 25.5);                   // int + double
    Add(25.7f, 45);                  // float + int
    return 0;
}

/*
Output:
28
93.3
39.5
70.7
*/
