#include <bits/stdc++.h>
using namespace std;

class Test {
private:
    int x = 15, y = 30, z;
public:
    Test(int a, int b) {
        x = a;
        y = b;
    }

    /* 🔹 Delegation: this constructor CALLS the other one first */
    Test() : Test(35, 75) {
        z = 10;
    }

    void Display() {
        cout << "x : " << x << ", y : " << y << ", z : " << z << endl;
    }
};

int main() {
    Test obj;
    obj.Display();
    return 0;
}

/*
Output:
x : 35, y : 75, z : 10
*/
