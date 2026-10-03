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

    /* 🔹 c2 + c1 is the same as c2.operator+(c1) */
    Complex operator+(Complex c) {
        Complex temp;
        temp.real = real + c.real;
        temp.img = img + c.img;
        return temp;
    }
    Complex operator-(Complex c) {
        Complex temp;
        temp.real = real - c.real;
        temp.img = img - c.img;
        return temp;
    }
};

int main() {
    Complex c1(5, 3), c2(10, 5), c3, c4;
    c3 = c2 + c1;
    c4 = c2 - c1;
    c3.display();
    c4.display();
    return 0;
}

/*
Output:
15 + i8
5 + i2
*/
