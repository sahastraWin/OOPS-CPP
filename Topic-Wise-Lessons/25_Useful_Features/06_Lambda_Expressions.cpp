#include <bits/stdc++.h>
using namespace std;

/* A template function that accepts any callable */
template <typename T>
void fun(T r) {
    r();
}

int main() {
    /*
       Syntax:  [ capture_list ] ( parameter_list ) -> return_type { body }
       Put ( ) right after } to call it immediately.
    */

    cout << "Function 1:" << endl;
    []() { cout << "Hello"; }();                 // no parameters

    cout << endl << "Function 2:" << endl;
    int z = [](int x, int y) { return x + y; }(30, 32);   // return type auto-detected
    cout << "Sum: " << z;

    cout << endl << "Function 3:" << endl;
    int x = 5, y = 6;
    auto F = [&x, &y]() {                        // & captures by REFERENCE -> can modify
        cout << ++x << " " << ++y << endl;
    };
    cout << "x & y : ";
    F();                                         // x = 6, y = 7 now

    cout << endl << "Function 4:" << endl;
    auto S = [x, y]() {                          // captures by VALUE -> read-only copies
        cout << "x * y: " << x * y << endl;
    };
    fun(S);                                      // pass lambda to another function

    /* Explicit return type */
    int total = [](int a, int b) -> int { return a + b; }(10, 5);
    cout << "Explicit return type: " << total << endl;
    return 0;
}

/*
Output:
Function 1:
Hello
Function 2:
Sum: 62
Function 3:
x & y : 6 7

Function 4:
x * y: 42
Explicit return type: 15
*/
