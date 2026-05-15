/*
 * ============================================================
 *  TOPIC: Operator Overloading in C++
 * ============================================================
 *
 * Operator Overloading allows existing C++ operators to work
 * with user-defined types.
 *
 * Covered here:
 *   1. Overloading via Member Function
 *   2. Overloading via Friend Function
 *   3. Overloading << and >> (stream operators)
 *   4. Unary Operator Overloading
 *   5. Relational / Comparison Operator Overloading
 *   6. Real-world example: Rational Numbers
 *
 * ╔══════════════════════════════════════════════════════════╗
 *  INTERVIEW MUST-KNOW:
 *  Operators that CANNOT be overloaded:
 *    ::   (scope resolution)
 *    .    (member access)
 *    .*   (member pointer access)
 *    ?:   (ternary)
 *    sizeof, typeid, alignof
 *
 *  Operators that MUST be overloaded as MEMBER functions:
 *    =    (assignment)
 *    []   (subscript)
 *    ()   (function call)
 *    ->   (member access through pointer)
 *
 *  All others can be member OR non-member (friend) functions.
 *
 *  Friend function is preferred for SYMMETRIC operators (+, -, etc.)
 *  so that both operands can undergo implicit conversion.
 * ╚══════════════════════════════════════════════════════════╝
 */

#include <iostream>
#include <stdexcept>
using namespace std;

/* ══════════════════════════════════════════════════════════
   1. COMPLEX NUMBER — Member Function Overloading
   ══════════════════════════════════════════════════════════ */

class Complex
{
private:
    double real, imag;

public:
    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

    /* ── Overload + as member function ──
     * 'this' is the left operand; argument is the right operand.
     * Returns a NEW object (no mutation of operands).
     */
    Complex operator+(const Complex &rhs) const
    {
        return Complex(real + rhs.real, imag + rhs.imag);
    }

    /* ── Overload - ── */
    Complex operator-(const Complex &rhs) const
    {
        return Complex(real - rhs.real, imag - rhs.imag);
    }

    /* ── Overload * ── (complex multiplication) */
    Complex operator*(const Complex &rhs) const
    {
        return Complex(real * rhs.real - imag * rhs.imag,
                       real * rhs.imag + imag * rhs.real);
    }

    /* ── Unary negation ── */
    Complex operator-() const
    {
        return Complex(-real, -imag);
    }

    /* ── Overload == ── */
    bool operator==(const Complex &rhs) const
    {
        return (real == rhs.real) && (imag == rhs.imag);
    }

    /* ── Overload += ── */
    Complex &operator+=(const Complex &rhs)
    {
        real += rhs.real;
        imag += rhs.imag;
        return *this; // return reference for chaining
    }

    /*
     * ╔══════════════════════════════════════════════════════╗
     *  INTERVIEW TIP:
     *  Declare << and >> as FRIEND functions because:
     *  The LEFT operand is ostream/istream (not our class).
     *  Member function: left operand must be the class object.
     *  Friend function: no restriction on left operand.
     * ╚══════════════════════════════════════════════════════╝
     */
    friend ostream &operator<<(ostream &os, const Complex &c);
    friend istream &operator>>(istream &is, Complex &c);
};

/* ── Ostream overloading ── */
ostream &operator<<(ostream &os, const Complex &c)
{
    os << c.real;
    if (c.imag >= 0)
        os << " + " << c.imag << "i";
    else
        os << " - " << (-c.imag) << "i";
    return os; // MUST return os for chaining: cout << a << b;
}

/* ── Istream overloading ── */
istream &operator>>(istream &is, Complex &c)
{
    cout << "Enter real and imaginary parts: ";
    is >> c.real >> c.imag;
    return is;
}

/* ══════════════════════════════════════════════════════════
   2. RATIONAL NUMBER — Friend Function Overloading
   ══════════════════════════════════════════════════════════

   ╔══════════════════════════════════════════════════════════╗
    INTERVIEW TIP:
    Friend function overloading for + :
        friend Complex operator+(const Complex& a, const Complex& b);
    Allows: Complex + int  (int auto-converted to Complex via constructor)
            int + Complex  (symmetry — impossible with member function)
   ╚══════════════════════════════════════════════════════════╝
*/

class Rational
{
private:
    int num, den;

    /* GCD helper for reduction */
    static int gcd(int a, int b)
    {
        return b == 0 ? a : gcd(b, a % b);
    }

    void reduce()
    {
        if (den < 0)
        {
            num = -num;
            den = -den;
        }
        int g = gcd(abs(num), abs(den));
        num /= g;
        den /= g;
    }

public:
    Rational(int n = 0, int d = 1) : num(n), den(d)
    {
        if (d == 0)
            throw invalid_argument("Denominator cannot be 0");
        reduce();
    }

    /* Friend overloads — both operands explicit, supports symmetry */
    friend Rational operator+(const Rational &a, const Rational &b);
    friend Rational operator-(const Rational &a, const Rational &b);
    friend Rational operator*(const Rational &a, const Rational &b);
    friend Rational operator/(const Rational &a, const Rational &b);
    friend bool operator==(const Rational &a, const Rational &b);
    friend bool operator<(const Rational &a, const Rational &b);
    friend ostream &operator<<(ostream &os, const Rational &r);
};

Rational operator+(const Rational &a, const Rational &b)
{
    return Rational(a.num * b.den + b.num * a.den, a.den * b.den);
}
Rational operator-(const Rational &a, const Rational &b)
{
    return Rational(a.num * b.den - b.num * a.den, a.den * b.den);
}
Rational operator*(const Rational &a, const Rational &b)
{
    return Rational(a.num * b.num, a.den * b.den);
}
Rational operator/(const Rational &a, const Rational &b)
{
    return Rational(a.num * b.den, a.den * b.num);
}
bool operator==(const Rational &a, const Rational &b)
{
    return (a.num == b.num) && (a.den == b.den);
}
bool operator<(const Rational &a, const Rational &b)
{
    return a.num * b.den < b.num * a.den;
}
ostream &operator<<(ostream &os, const Rational &r)
{
    if (r.den == 1)
        os << r.num;
    else
        os << r.num << "/" << r.den;
    return os;
}

/* ══════════════════════════════════════════════════════════
   3. VECTOR2D — Unary + Subscript overloading
   ══════════════════════════════════════════════════════════ */

class Vector2D
{
private:
    double coords[2]; // x = [0], y = [1]

public:
    Vector2D(double x = 0, double y = 0)
    {
        coords[0] = x;
        coords[1] = y;
    }

    /*
     * ╔══════════════════════════════════════════════════════╗
     *  INTERVIEW TIP: operator[] must be a member function.
     *  Provide both const and non-const versions.
     * ╚══════════════════════════════════════════════════════╝
     */
    double &operator[](int idx)
    {
        if (idx < 0 || idx > 1)
            throw out_of_range("Index out of range");
        return coords[idx];
    }
    const double &operator[](int idx) const
    {
        if (idx < 0 || idx > 1)
            throw out_of_range("Index out of range");
        return coords[idx];
    }

    /* Prefix ++: increment then return */
    Vector2D &operator++()
    {
        ++coords[0];
        ++coords[1];
        return *this;
    }

    /* Postfix ++: return original, then increment
     * The dummy int parameter distinguishes postfix from prefix.
     */
    Vector2D operator++(int)
    {
        Vector2D temp = *this;
        ++(*this);
        return temp;
    }

    friend ostream &operator<<(ostream &os, const Vector2D &v)
    {
        return os << "(" << v.coords[0] << ", " << v.coords[1] << ")";
    }
};

/* ══════════════════════════════════════════════════════════
   MAIN
   ══════════════════════════════════════════════════════════ */
int main()
{
    cout << "===== Operator Overloading =====\n\n";

    /* --- Complex Numbers --- */
    cout << "--- Complex Number (Member Function Overloading) ---\n";
    Complex c1(3, 4), c2(1, -2);
    cout << "c1 = " << c1 << "\n";
    cout << "c2 = " << c2 << "\n";
    cout << "c1 + c2 = " << (c1 + c2) << "\n";
    cout << "c1 - c2 = " << (c1 - c2) << "\n";
    cout << "c1 * c2 = " << (c1 * c2) << "\n";
    cout << "-c1     = " << (-c1) << "\n";
    cout << "c1 == c2? " << (c1 == c2 ? "Yes" : "No") << "\n";
    c1 += c2;
    cout << "c1 after += c2: " << c1 << "\n";

    /* --- Rational Numbers --- */
    cout << "\n--- Rational Numbers (Friend Function Overloading) ---\n";
    Rational r1(1, 2), r2(1, 3);
    cout << "r1 = " << r1 << "\n";
    cout << "r2 = " << r2 << "\n";
    cout << "r1 + r2 = " << (r1 + r2) << "\n";
    cout << "r1 - r2 = " << (r1 - r2) << "\n";
    cout << "r1 * r2 = " << (r1 * r2) << "\n";
    cout << "r1 / r2 = " << (r1 / r2) << "\n";
    cout << "r1 < r2? " << (r1 < r2 ? "Yes" : "No") << "\n";

    /* --- Vector2D --- */
    cout << "\n--- Vector2D (Subscript + Prefix/Postfix ++) ---\n";
    Vector2D v(3.0, 4.0);
    cout << "v    = " << v << "\n";
    cout << "v[0] = " << v[0] << ", v[1] = " << v[1] << "\n";
    v[0] = 10.0;
    cout << "After v[0]=10: " << v << "\n";

    Vector2D v2 = v++;
    cout << "v2 (postfix++ old val) = " << v2 << "\n";
    cout << "v  (after postfix++)   = " << v << "\n";

    ++v;
    cout << "v  (after prefix++)    = " << v << "\n";

    return 0;
}
