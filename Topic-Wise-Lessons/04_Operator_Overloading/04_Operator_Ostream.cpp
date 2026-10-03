#include <bits/stdc++.h>
using namespace std;

class Complex {
private:
    int real, img;
public:
    Complex(int r, int i) {
        real = r;
        img = i;
    }
    /* cout << c1 has cout on the LEFT, so it cannot be a member function.
       We make it a friend and return the stream to allow chaining. */
    friend ostream& operator<<(ostream &out, const Complex &c);
};

ostream& operator<<(ostream &out, const Complex &c) {
    out << c.real << " + i" << c.img << endl;
    return out;
}

int main() {
    Complex c1(4, 6), c2(1, 2);
    cout << c1;                     // 4 + i6
    operator<<(cout, c1);           // same thing, written explicitly
    cout << c1 << c2;               // chaining works because we return out
    return 0;
}

/*
Output:
4 + i6
4 + i6
4 + i6
1 + i2
*/
