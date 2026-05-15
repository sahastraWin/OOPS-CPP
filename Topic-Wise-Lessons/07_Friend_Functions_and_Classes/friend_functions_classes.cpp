/*
 * ============================================================
 *  TOPIC: Friend Functions and Friend Classes in C++
 * ============================================================
 *
 * A 'friend' declaration grants a non-member function or another
 * class access to private and protected members of a class.
 *
 * ╔══════════════════════════════════════════════════════════╗
 *  INTERVIEW MUST-KNOW:
 *  1. Friend function is NOT a member function.
 *  2. Called like a regular function (no object.func() syntax).
 *  3. Uses object.member to access private data explicitly.
 *  4. Can be declared in private or public section of a class
 *     (convention: public section).
 *  5. Friendship is NOT mutual: if A is friend of B,
 *     B is NOT automatically a friend of A.
 *  6. Friendship is NOT inherited.
 *  7. Friendship is NOT transitive:
 *     if A is friend of B and B is friend of C,
 *     A is NOT automatically a friend of C.
 *  8. Use friends sparingly — they break encapsulation!
 *     Best use: operator overloading where left operand
 *     is not our class (e.g., ostream <<).
 * ╚══════════════════════════════════════════════════════════╝
 */

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

/* ══════════════════════════════════════════════════════════
   1. FRIEND FUNCTION — Basic example
   ══════════════════════════════════════════════════════════ */

class BankAccount
{
private:
    string owner;
    double balance;

public:
    BankAccount(string o, double b) : owner(o), balance(b) {}

    void deposit(double amount)
    {
        if (amount > 0)
            balance += amount;
    }

    void display() const
    {
        cout << "Account[" << owner << "]: $" << balance << "\n";
    }

    /*
     * Declare 'transfer' as friend so it can access both
     * accounts' private members directly.
     *
     * ╔══════════════════════════════════════════════════╗
     *  WHY FRIEND HERE?
     *  A member function can access 'this' object's private
     *  members easily, but cannot access ANOTHER object's
     *  private members unless there's a getter/setter.
     *  Friend function bypasses this restriction cleanly.
     * ╚══════════════════════════════════════════════════╝
     */
    friend void transfer(BankAccount &from, BankAccount &to, double amount);
    friend void printBalance(const BankAccount &acc);
};

/* Friend function definition — NOT preceded by BankAccount:: */
void transfer(BankAccount &from, BankAccount &to, double amount)
{
    if (amount > 0 && from.balance >= amount)
    {
        from.balance -= amount; // direct access to private members
        to.balance += amount;
        cout << "Transferred $" << amount
             << " from " << from.owner
             << " to " << to.owner << "\n";
    }
    else
    {
        cout << "Transfer failed: insufficient funds or invalid amount.\n";
    }
}

void printBalance(const BankAccount &acc)
{
    cout << acc.owner << " has $" << acc.balance << "\n";
}

/* ══════════════════════════════════════════════════════════
   2. FRIEND FUNCTION used for OPERATOR OVERLOADING
   (symmetric binary operators)
   ══════════════════════════════════════════════════════════

   ╔══════════════════════════════════════════════════════════╗
    INTERVIEW TIP:
    Friend is preferred for operator+ etc. because:
    Member: obj1 + obj2  → obj1.operator+(obj2)
            (left must be obj1, no implicit conversion on left)
    Friend: obj1 + obj2  → operator+(obj1, obj2)
            (both sides can undergo implicit conversion)
    Example: 3.0 + myObj  works with friend, not with member.
   ╚══════════════════════════════════════════════════════════╝
*/

class Vector3D
{
private:
    double x, y, z;

public:
    Vector3D(double a = 0, double b = 0, double c = 0)
        : x(a), y(b), z(c) {}

    double magnitude() const
    {
        return sqrt(x * x + y * y + z * z);
    }

    /* Friend binary operator */
    friend Vector3D operator+(const Vector3D &a, const Vector3D &b);
    friend Vector3D operator-(const Vector3D &a, const Vector3D &b);
    friend double dot(const Vector3D &a, const Vector3D &b);     // dot product
    friend Vector3D cross(const Vector3D &a, const Vector3D &b); // cross product
    friend ostream &operator<<(ostream &os, const Vector3D &v);
};

Vector3D operator+(const Vector3D &a, const Vector3D &b)
{
    return {a.x + b.x, a.y + b.y, a.z + b.z};
}
Vector3D operator-(const Vector3D &a, const Vector3D &b)
{
    return {a.x - b.x, a.y - b.y, a.z - b.z};
}
double dot(const Vector3D &a, const Vector3D &b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
Vector3D cross(const Vector3D &a, const Vector3D &b)
{
    return {a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x};
}
ostream &operator<<(ostream &os, const Vector3D &v)
{
    return os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}

/* ══════════════════════════════════════════════════════════
   3. FRIEND CLASS
   ══════════════════════════════════════════════════════════

   ╔══════════════════════════════════════════════════════════╗
    INTERVIEW MUST-KNOW:
    'friend class B' inside class A means:
    - ALL member functions of B can access private/protected
      members of A.
    - Typical use: tightly coupled helper classes,
      iterators, serializers, test fixtures.
   ╚══════════════════════════════════════════════════════════╝
*/

class Engine
{
private:
    int horsepower;
    double displacement; // litres
    bool running;

    Engine(int hp, double disp)
        : horsepower(hp), displacement(disp), running(false) {}

    void start() { running = true; }
    void stop() { running = false; }

    /* Only Car class can create/control Engine */
    friend class CarSystem;

public:
    bool isRunning() const { return running; }
};

class CarSystem
{
private:
    string name;
    Engine engine; // has-a Engine

public:
    CarSystem(string n, int hp, double disp)
        : name(n), engine(hp, disp) {} // can call Engine's private ctor

    void startCar()
    {
        engine.start(); // can call Engine's private method
        cout << name << " started. HP=" << engine.horsepower
             << " Running=" << engine.running << "\n";
    }

    void stopCar()
    {
        engine.stop();
        cout << name << " stopped.\n";
    }
};

/* ══════════════════════════════════════════════════════════
   MAIN
   ══════════════════════════════════════════════════════════ */
int main()
{
    cout << "===== Friend Functions and Classes =====\n\n";

    /* --- Friend Function (transfer) --- */
    cout << "--- 1. Friend Function (Bank Transfer) ---\n";
    BankAccount acc1("Alice", 1000.0);
    BankAccount acc2("Bob", 500.0);
    acc1.display();
    acc2.display();

    transfer(acc1, acc2, 300.0); // direct call, not acc1.transfer(...)
    printBalance(acc1);
    printBalance(acc2);

    transfer(acc2, acc1, 2000.0); // should fail

    /* --- Friend Function for Operator Overloading --- */
    cout << "\n--- 2. Friend Functions + Operator Overloading ---\n";
    Vector3D v1(1, 2, 3), v2(4, 5, 6);
    cout << "v1           = " << v1 << "\n";
    cout << "v2           = " << v2 << "\n";
    cout << "v1 + v2      = " << (v1 + v2) << "\n";
    cout << "v1 - v2      = " << (v1 - v2) << "\n";
    cout << "dot(v1, v2)  = " << dot(v1, v2) << "\n";
    cout << "cross(v1,v2) = " << cross(v1, v2) << "\n";
    cout << "|v1|         = " << v1.magnitude() << "\n";

    /* --- Friend Class --- */
    cout << "\n--- 3. Friend Class (CarSystem controls Engine) ---\n";
    CarSystem tesla("Tesla Model S", 670, 0.0);
    tesla.startCar();
    tesla.stopCar();

    return 0;
}
