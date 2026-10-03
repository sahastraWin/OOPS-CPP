#include <bits/stdc++.h>
using namespace std;

class Complex {
private:
    int real, img;
public:
    Complex(int r = 0, int i = 0) {
        real = r;
        img = i;
    }
    void display() {
        cout << real << " + i" << img << endl;
    }
    friend Complex operator+(Complex c1, Complex c2);   // not a member, but can see private data
};

Complex operator+(Complex c1, Complex c2) {
    Complex temp;
    temp.real = c1.real + c2.real;
    temp.img = c1.img + c2.img;
    return temp;
}

int main() {
    Complex c1(5, 3), c2(10, 6), c3;
    c3 = c1 + c2;
    // Same thing written explicitly:  c3 = operator+(c1, c2);
    c3.display();
    return 0;
}

/*
Output:
15 + i9
*/
