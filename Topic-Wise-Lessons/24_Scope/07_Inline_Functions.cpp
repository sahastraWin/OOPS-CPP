#include <bits/stdc++.h>
using namespace std;

class Operation {
    int a, b;
public:
    void get(int x, int y);
    void sum();
    void difference();
};

/* 🔹 inline asks the compiler to paste the body at the call site
      (saves function-call overhead for tiny functions). */
inline void Operation::get(int x, int y) {
    a = x;
    b = y;
}
inline void Operation::sum() {
    cout << "Addition of two numbers: " << a + b << "\n";
}
inline void Operation::difference() {
    cout << "Difference of two numbers: " << a - b << "\n";
}

int main() {
    cout << "Program using inline function\n";
    Operation s;
    s.get(20, 10);
    s.sum();
    s.difference();
    return 0;
}

/*
Output:
Program using inline function
Addition of two numbers: 30
Difference of two numbers: 10
*/
