#include <bits/stdc++.h>
using namespace std;

int Division(int a, int b) {
    if (b == 0)
        throw 1;                                 // throw an int as the error code
    return a / b;
}

int main() {
    int x = 20;
    int divisors[] = {4, 0};                     // sample test cases

    for (int y : divisors) {
        try {
            int z = Division(x, y);              // risky code goes in try
            cout << x << " / " << y << " = " << z << endl;
        }
        catch (int e) {                          // runs only if an int is thrown
            cout << "Division by zero " << e << endl;
        }
    }
    cout << "Bye" << endl;
    return 0;
}

/*
Output:
20 / 4 = 5
Division by zero 1
Bye
*/
