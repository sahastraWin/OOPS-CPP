#include <bits/stdc++.h>
using namespace std;

class Rectangle {
private:
    int length, breadth;
public:
    Rectangle(int l, int b) {
        if (l < 0 || b < 0) {
            throw 1;                             // refuse to build an invalid object
        } else {
            length = l;
            breadth = b;
        }
    }
    void Display() {
        cout << "Length: " << length << " Breadth: " << breadth << endl;
    }
};

int main() {
    try {
        Rectangle r2(10, 5);
        r2.Display();
        Rectangle r1(10, -5);                    // throws here
        r1.Display();                            // never reached
    }
    catch (int num) {
        cout << "Rectangle Object Creation Failed" << endl;
    }
    return 0;
}

/*
Output:
Length: 10 Breadth: 5
Rectangle Object Creation Failed
*/
