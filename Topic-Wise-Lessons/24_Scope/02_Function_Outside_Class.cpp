#include <bits/stdc++.h>
using namespace std;

class A {
private:
    int a, b;
public:
    A(int x, int y) { a = x; b = y; }
    int Multiplication();           // only the declaration here
};

/* 🔹 ClassName::function tells the compiler this belongs to class A */
int A::Multiplication() {
    return a * b;
}

int main() {
    A obj(5, 6);
    cout << "The Multiplication is : " << obj.Multiplication() << endl;
    return 0;
}

/*
Output:
The Multiplication is : 30
*/
