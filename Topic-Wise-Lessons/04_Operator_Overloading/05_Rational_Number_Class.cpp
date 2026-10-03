#include <bits/stdc++.h>
using namespace std;

class Rational {
private:
    int p;      // numerator
    int q;      // denominator
public:
    Rational() { p = 1; q = 1; }                          // default
    Rational(int p, int q) { this->p = p; this->q = q; }  // parameterized
    Rational(const Rational &r) { p = r.p; q = r.q; }     // copy

    int getP() { return p; }
    int getQ() { return q; }
    void setP(int p) { this->p = p; }
    void setQ(int q) { this->q = q; }

    /* a/b + c/d = (a*d + b*c) / (b*d) */
    Rational operator+(Rational r) {
        Rational t;
        t.p = this->p * r.q + this->q * r.p;
        t.q = this->q * r.q;
        return t;
    }
    friend ostream& operator<<(ostream &os, const Rational &r);
};

ostream& operator<<(ostream &os, const Rational &r) {
    os << r.p << "/" << r.q;
    return os;
}

int main() {
    Rational r1(3, 4), r2(2, 5), r3;
    r3 = r1 + r2;
    cout << "Sum of " << r1 << " and " << r2 << " is " << r3 << endl;
    return 0;
}

/*
Output:
Sum of 3/4 and 2/5 is 23/20
*/
