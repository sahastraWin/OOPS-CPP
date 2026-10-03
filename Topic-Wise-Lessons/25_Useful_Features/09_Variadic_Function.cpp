#include <bits/stdc++.h>
using namespace std;

/* n = how many numbers follow;  ... = the numbers themselves */
int sum(int n, ...) {
    va_list args;
    va_start(args, n);                           // start reading after 'n'
    int s = 0;
    for (int i = 0; i < n; i++) {
        int x = va_arg(args, int);               // take the next int
        s += x;
    }
    va_end(args);                                // always clean up
    return s;
}

int main() {
    cout << sum(3, 12, 24, 36) << endl;
    cout << sum(7, 13, 26, 39, 52, 65, 78, 81) << endl;
    return 0;
}

/*
⚠️ The function cannot know how many values you passed, so you must tell it (here: n).

Output:
72
354
*/
