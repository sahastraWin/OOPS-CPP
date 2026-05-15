/*
 * ============================================================
 *  TOPIC: Polymorphism in C++
 * ============================================================
 *
 * Polymorphism = "many forms"
 *
 * Types:
 *   A) Compile-Time (Static) Polymorphism
 *      - Function Overloading
 *      - Operator Overloading (see 04_Operator_Overloading)
 *      - Template (see 11_Templates)
 *
 *   B) Runtime (Dynamic) Polymorphism
 *      - Function Overriding + Virtual Functions
 *
 * Covered here:
 *   1. Function Overloading (Compile-Time)
 *   2. Function Overriding
 *   3. Virtual Functions + vTable/vPtr mechanism
 *   4. Pure Virtual Functions
 *   5. Abstract Classes
 *   6. Runtime Polymorphism demo (base ptr → derived obj)
 *
 * ╔══════════════════════════════════════════════════════════╗
 *  INTERVIEW MUST-KNOW: Virtual Function Mechanism
 *  - Every class with virtual functions has a VTABLE
 *    (virtual dispatch table) — a static array of function pointers.
 *  - Every object of such a class has a hidden VPTR
 *    (virtual pointer) pointing to the class's vtable.
 *  - When you call a virtual function through a base pointer,
 *    the runtime uses vptr → vtable → correct function.
 *  - This causes a small overhead (one indirection).
 *  - Virtual functions CANNOT be static (no object = no vptr).
 *  - Virtual functions CAN be friend of another class.
 * ╚══════════════════════════════════════════════════════════╝
 */

#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

/* ══════════════════════════════════════════════════════════
   1. FUNCTION OVERLOADING — Compile-Time Polymorphism
   ══════════════════════════════════════════════════════════

   ╔══════════════════════════════════════════════════════════╗
    INTERVIEW TIP:
    Function Overloading resolution is done at COMPILE TIME
    based on the number and types of arguments (signature).
    Return type alone does NOT differentiate overloaded functions.
   ╚══════════════════════════════════════════════════════════╝
*/

class Printer
{
public:
    /* Same name, different parameter types */
    void print(int x) const { cout << "int: " << x << "\n"; }
    void print(double x) const { cout << "double: " << x << "\n"; }
    void print(string s) const { cout << "string: " << s << "\n"; }
    void print(int x, int y) const
    {
        cout << "int pair: " << x << ", " << y << "\n";
    }
};

/* ══════════════════════════════════════════════════════════
   2. FUNCTION OVERRIDING — Runtime Polymorphism basis
   ══════════════════════════════════════════════════════════

   ╔══════════════════════════════════════════════════════════╗
    INTERVIEW MUST-KNOW:
    Overloading vs Overriding:
    ┌───────────────┬──────────────┬────────────────────────┐
    │               │ Overloading  │ Overriding             │
    ├───────────────┼──────────────┼────────────────────────┤
    │ Where         │ Same class   │ Base + Derived class   │
    │ Signature     │ DIFFERENT    │ SAME (must match)      │
    │ When resolved │ Compile-time │ Runtime (if virtual)   │
    │ Keyword       │ none         │ virtual + override      │
    └───────────────┴──────────────┴────────────────────────┘
    'override' keyword (C++11): tells compiler to verify that
    the function is actually overriding a virtual — prevents
    silent bugs from mismatched signatures.
   ╚══════════════════════════════════════════════════════════╝
*/

class Employee
{
protected:
    string name;
    double baseSalary;

public:
    Employee(string n, double s) : name(n), baseSalary(s) {}

    /* virtual: resolved at runtime based on actual object type */
    virtual double calculateSalary() const
    {
        return baseSalary;
    }

    virtual void display() const
    {
        cout << "Employee: " << name
             << " | Salary: " << calculateSalary() << "\n";
    }

    /* Virtual destructor: MUST have in base class when using
     * base pointers. Without it, deleting via base pointer won't
     * call derived destructor → resource leak!
     *
     * ╔══════════════════════════════════════════════════╗
     *  INTERVIEW MUST-KNOW: Always make base class
     *  destructor virtual when using polymorphism.
     * ╚══════════════════════════════════════════════════╝
     */
    virtual ~Employee() { cout << "[Employee Destructor]\n"; }
};

class Manager : public Employee
{
private:
    double bonus;

public:
    Manager(string n, double s, double b)
        : Employee(n, s), bonus(b) {}

    double calculateSalary() const override
    {
        return baseSalary + bonus; // managers get bonus
    }

    void display() const override
    {
        cout << "Manager: " << name
             << " | Base: " << baseSalary
             << " | Bonus: " << bonus
             << " | Total: " << calculateSalary() << "\n";
    }

    ~Manager() override { cout << "[Manager Destructor]\n"; }
};

class Intern : public Employee
{
private:
    int months;

public:
    Intern(string n, double monthlyStipend, int m)
        : Employee(n, monthlyStipend), months(m) {}

    double calculateSalary() const override
    {
        return baseSalary * months; // stipend * months
    }

    void display() const override
    {
        cout << "Intern: " << name
             << " | Monthly: " << baseSalary
             << " | Months: " << months
             << " | Total: " << calculateSalary() << "\n";
    }

    ~Intern() override { cout << "[Intern Destructor]\n"; }
};

/* ══════════════════════════════════════════════════════════
   3. PURE VIRTUAL FUNCTIONS & ABSTRACT CLASS
   ══════════════════════════════════════════════════════════

   ╔══════════════════════════════════════════════════════════╗
    INTERVIEW MUST-KNOW: Pure Virtual Function
    Syntax: virtual void func() = 0;
    - A class with at least one pure virtual function is
      an ABSTRACT CLASS.
    - Abstract class CANNOT be instantiated (no objects).
    - Abstract class CAN have a pointer (for polymorphism).
    - Derived class MUST override ALL pure virtual functions,
      otherwise it also becomes abstract.
    - Purpose: define an INTERFACE — mandate derived classes
      to provide specific implementations.
   ╚══════════════════════════════════════════════════════════╝
*/

/* Abstract base class — defines the INTERFACE */
class Shape
{
protected:
    string color;

public:
    Shape(string c = "white") : color(c) {}

    /* Pure virtual — subclasses MUST implement */
    virtual double area() const = 0;
    virtual double perimeter() const = 0;
    virtual string name() const = 0;

    /* Concrete method in abstract class (allowed!) */
    virtual void describe() const
    {
        cout << name() << " [" << color << "]"
             << " Area=" << area()
             << " Perimeter=" << perimeter() << "\n";
    }

    virtual ~Shape() {}
};

class Circle : public Shape
{
private:
    double radius;
    static constexpr double PI = 3.14159265358979;

public:
    Circle(double r, string c = "red") : Shape(c), radius(r) {}
    double area() const override { return PI * radius * radius; }
    double perimeter() const override { return 2 * PI * radius; }
    string name() const override { return "Circle"; }
};

class Rectangle : public Shape
{
private:
    double len, wid;

public:
    Rectangle(double l, double w, string c = "blue")
        : Shape(c), len(l), wid(w) {}
    double area() const override { return len * wid; }
    double perimeter() const override { return 2 * (len + wid); }
    string name() const override { return "Rectangle"; }
};

class Triangle : public Shape
{
private:
    double a, b, c;

public:
    Triangle(double a, double b, double c, string col = "green")
        : Shape(col), a(a), b(b), c(c) {}
    double perimeter() const override { return a + b + c; }
    double area() const override
    {
        double s = perimeter() / 2.0;
        return sqrt(s * (s - a) * (s - b) * (s - c)); // Heron's formula
    }
    string name() const override { return "Triangle"; }
};

/* ══════════════════════════════════════════════════════════
   4. RUNTIME POLYMORPHISM — Base pointer container
   ══════════════════════════════════════════════════════════ */

void printPayroll(const vector<Employee *> &staff)
{
    cout << "\n--- Payroll (Runtime Polymorphism) ---\n";
    double total = 0;
    for (const auto *e : staff)
    {
        e->display(); // calls correct override at runtime
        total += e->calculateSalary();
    }
    cout << "Total payroll: " << total << "\n";
}

void printShapes(const vector<Shape *> &shapes)
{
    cout << "\n--- Shapes (Abstract Class Polymorphism) ---\n";
    for (const auto *s : shapes)
    {
        s->describe(); // runtime dispatch via vtable
    }
}

/* ══════════════════════════════════════════════════════════
   MAIN
   ══════════════════════════════════════════════════════════ */
int main()
{
    cout << "===== Polymorphism in C++ =====\n\n";

    /* --- Compile-Time Polymorphism (Function Overloading) --- */
    cout << "--- 1. Compile-Time (Function Overloading) ---\n";
    Printer p;
    p.print(42);
    p.print(3.14);
    p.print("Hello OOP");
    p.print(10, 20);

    /* --- Runtime Polymorphism --- */
    cout << "\n--- 2. Runtime Polymorphism (Virtual Functions) ---\n";

    /*
     * All pointers are of type Employee* (base),
     * but actual objects are different types.
     * Correct calculateSalary() is called at RUNTIME.
     */
    vector<Employee *> staff = {
        new Employee("Alice", 50000),
        new Manager("Bob", 60000, 15000),
        new Intern("Charlie", 5000, 6)};

    printPayroll(staff);

    /* Cleanup — virtual destructor ensures correct chain */
    for (auto *e : staff)
        delete e;

    /* --- Abstract Class --- */
    cout << "\n--- 3. Abstract Class + Pure Virtual Functions ---\n";

    // Shape s;   // COMPILE ERROR: cannot instantiate abstract class
    Shape *sp = new Circle(5.0); // VALID: pointer of abstract class

    vector<Shape *> shapes = {
        new Circle(5.0, "red"),
        new Rectangle(4.0, 6.0, "blue"),
        new Triangle(3.0, 4.0, 5.0, "green")};

    printShapes(shapes);

    for (auto *s : shapes)
        delete s;
    delete sp;

    cout << "\n--- Destructors called ---\n";
    return 0;
}
