/*
 * ============================================================
 *  TOPIC: Classes and Objects in C++
 * ============================================================
 *
 * Covered here:
 *   1. Class declaration & definition
 *   2. Access specifiers (public / private / protected)
 *   3. Struct vs Class
 *   4. Scope Resolution Operator (::)
 *   5. Inline Functions
 *   6. The "this" Pointer
 *   7. Types of member functions (Accessor, Mutator, etc.)
 */

#include <iostream>
#include <string>
using namespace std;

/* ══════════════════════════════════════════════════════════
   1. BASIC CLASS DEFINITION
   ══════════════════════════════════════════════════════════ */

class Student
{
    /*
     * ╔══════════════════════════════════════════════════════╗
     *  INTERVIEW MUST-KNOW: Access Specifiers
     *
     *  private   -> accessible only within the class (DEFAULT in class)
     *  protected -> accessible within class + derived classes
     *  public    -> accessible from anywhere
     *
     *  In STRUCT everything is public by default.
     *  In CLASS  everything is private by default.
     * ╚══════════════════════════════════════════════════════╝
     */
private:
    int rollNo;
    string name;
    double cgpa;

public:
    /* ── CONSTRUCTOR ── */
    Student(int r, string n, double c) : rollNo(r), name(n), cgpa(c) {}

    /* ── ACCESSOR (Getter) ──
     * Read-only access to private data.
     * Marked const so they don't modify the object.
     *
     * ╔══════════════════════════════════════════════════════╗
     *  INTERVIEW TIP: Always mark getters as 'const' member
     *  functions. This allows them to be called on const objects.
     * ╚══════════════════════════════════════════════════════╝
     */
    int getRollNo() const { return rollNo; }
    string getName() const { return name; }
    double getCGPA() const { return cgpa; }

    /* ── MUTATOR (Setter) ──
     * Controlled modification of private data.
     */
    void setName(string n) { name = n; }
    void setCGPA(double c)
    {
        if (c >= 0.0 && c <= 10.0) // validation before setting
            cgpa = c;
        else
            cout << "Invalid CGPA value!\n";
    }

    /* ── FACILITATOR ── performs some operation */
    void display() const
    {
        cout << "Roll: " << rollNo
             << " | Name: " << name
             << " | CGPA: " << cgpa << "\n";
    }

    /* ── ENQUIRY / INSPECTOR ── returns a bool about object state */
    bool isDistinction() const { return cgpa >= 9.0; }
};

/* ══════════════════════════════════════════════════════════
   2. SCOPE RESOLUTION OPERATOR (::)
      - Defining member functions OUTSIDE the class
   ══════════════════════════════════════════════════════════

   ╔══════════════════════════════════════════════════════════╗
    INTERVIEW TIP: Uses of :: operator
    1. Define function outside class
    2. Access global variable when local var has same name
    3. Access static data members
    4. Resolve ambiguity in multiple inheritance
    5. Refer to a nested class
   ╚══════════════════════════════════════════════════════════╝
*/

class Rectangle
{
private:
    double length, width;

public:
    Rectangle(double l, double w); // declared inside
    double area() const;           // declared inside
    double perimeter() const;      // declared inside
    void display() const;          // declared inside
};

/* Definitions OUTSIDE the class using :: */
Rectangle::Rectangle(double l, double w) : length(l), width(w) {}

double Rectangle::area() const
{
    return length * width;
}

double Rectangle::perimeter() const
{
    return 2 * (length + width);
}

void Rectangle::display() const
{
    cout << "Rectangle(" << length << " x " << width << ")"
         << " Area=" << area()
         << " Perimeter=" << perimeter() << "\n";
}

/* ══════════════════════════════════════════════════════════
   3. INLINE FUNCTIONS
   ══════════════════════════════════════════════════════════

   ╔══════════════════════════════════════════════════════════╗
    INTERVIEW MUST-KNOW: Inline functions
    - Compiler places a COPY of the function code at each
      call site (avoids function call overhead).
    - It is a REQUEST, not a command. Compiler may IGNORE it.
    - Compiler WILL NOT inline if:
        * Function has a loop
        * Function has static variables
        * Function is recursive
        * Return type is not void (some compilers)
        * Function has switch/goto
    - Functions defined INSIDE a class are implicitly inline.
   ╚══════════════════════════════════════════════════════════╝
*/

class MathUtils
{
public:
    /* Implicitly inline (defined inside class body) */
    int square(int x) { return x * x; }

    /* Explicitly inline (defined outside with 'inline' keyword) */
    inline int cube(int x);
};

inline int MathUtils::cube(int x)
{
    return x * x * x;
}

/* ══════════════════════════════════════════════════════════
   4. THE "this" POINTER
   ══════════════════════════════════════════════════════════

   ╔══════════════════════════════════════════════════════════╗
    INTERVIEW MUST-KNOW: "this" pointer
    - Every non-static member function receives a hidden
      pointer 'this' pointing to the calling object.
    - 'this' is of type: ClassName* const (pointer is const)
    - Uses:
        1. Disambiguate when param name == member name
        2. Return the current object (*this) for chaining
        3. Pass current object to another function
    - Static functions do NOT have a 'this' pointer (they
      are not tied to any object).
   ╚══════════════════════════════════════════════════════════╝
*/

class Counter
{
private:
    int count;

public:
    Counter(int c = 0) : count(c) {}

    /* Use 'this' to disambiguate member vs parameter */
    void setCount(int count)
    {
        this->count = count; // this->count = member, count = param
    }

    /*
     * Return *this to enable METHOD CHAINING (fluent interface)
     * e.g., obj.increment().increment().display();
     */
    Counter &increment()
    {
        count++;
        return *this; // return reference to calling object
    }

    Counter &add(int val)
    {
        this->count += val;
        return *this;
    }

    void display() const
    {
        cout << "Count: " << count << "\n";
    }
};

/* ══════════════════════════════════════════════════════════
   5. STRUCT vs CLASS (side-by-side demo)
   ══════════════════════════════════════════════════════════

   ╔══════════════════════════════════════════════════════════╗
    INTERVIEW QUICK COMPARISON:
    ┌─────────────────────┬──────────────────────────────────┐
    │ struct              │ class                            │
    ├─────────────────────┼──────────────────────────────────┤
    │ Members public by   │ Members private by default       │
    │ default             │                                  │
    │ Cannot be inherited │ Can be inherited                 │
    │ (traditionally)     │                                  │
    │ No data hiding      │ Full data hiding via specifiers  │
    │ Only data members   │ Data + member functions          │
    │ (traditionally)     │                                  │
    └─────────────────────┴──────────────────────────────────┘
    In C++, struct CAN have functions & inheritance, but
    by CONVENTION structs are used for plain data aggregates.
   ╚══════════════════════════════════════════════════════════╝
*/

struct Point
{ // all public by default
    double x, y;
    void display()
    {
        cout << "(" << x << ", " << y << ")\n";
    }
};

class Circle
{ // all private by default
private:
    Point center;
    double radius;

public:
    Circle(double cx, double cy, double r)
        : center({cx, cy}), radius(r) {}
    double area() const { return 3.14159 * radius * radius; }
    void display() const
    {
        cout << "Circle center=(" << center.x << "," << center.y
             << ") radius=" << radius
             << " area=" << area() << "\n";
    }
};

/* ══════════════════════════════════════════════════════════
   GLOBAL vs LOCAL variable with ::
   ══════════════════════════════════════════════════════════ */
int globalValue = 100;

void scopeDemo()
{
    int globalValue = 999; // local shadows global
    cout << "Local  globalValue = " << globalValue << "\n";
    cout << "Global globalValue = " << ::globalValue << "\n"; // :: accesses global
}

/* ══════════════════════════════════════════════════════════
   MAIN
   ══════════════════════════════════════════════════════════ */
int main()
{
    cout << "===== Classes and Objects =====\n\n";

    /* --- Student class --- */
    cout << "--- Student (Accessor / Mutator / Facilitator / Enquiry) ---\n";
    Student s(101, "Sahastrajeet", 9.5);
    s.display();
    cout << "Distinction? " << (s.isDistinction() ? "Yes" : "No") << "\n";
    s.setCGPA(11.0); // invalid, guarded by mutator
    s.setCGPA(9.8);  // valid
    s.display();

    /* --- Rectangle (:: outside definition) --- */
    cout << "\n--- Rectangle (functions defined outside with ::) ---\n";
    Rectangle r(5.0, 3.0);
    r.display();

    /* --- Inline functions --- */
    cout << "\n--- Inline Functions ---\n";
    MathUtils mu;
    cout << "square(7) = " << mu.square(7) << "\n";
    cout << "cube(4)   = " << mu.cube(4) << "\n";

    /* --- this pointer & method chaining --- */
    cout << "\n--- this Pointer & Method Chaining ---\n";
    Counter c;
    c.setCount(5);
    c.increment().increment().add(10).display(); // chaining!

    /* --- Struct vs Class --- */
    cout << "\n--- Struct vs Class ---\n";
    Point p = {3.0, 4.0};
    p.display();
    Circle circ(0.0, 0.0, 7.0);
    circ.display();

    /* --- Scope resolution for global vs local --- */
    cout << "\n--- :: Scope Resolution (global vs local) ---\n";
    scopeDemo();

    return 0;
}
