/*
 * ============================================================
 *  TOPIC: Inheritance in C++
 * ============================================================
 *
 * Covered here:
 *   1. Single Inheritance
 *   2. Multilevel Inheritance
 *   3. Multiple Inheritance
 *   4. Hierarchical Inheritance
 *   5. Hybrid Inheritance
 *   6. Access Specifiers in Inheritance
 *   7. Constructors in Inheritance
 *   8. Diamond Problem + Virtual Base Class
 *   9. Base class pointer → Derived class object
 *  10. Available vs Accessible
 *
 * ╔══════════════════════════════════════════════════════════╗
 *  INTERVIEW MUST-KNOW:
 *  Syntax: class Derived : <access_specifier> Base {}
 *
 *  Access specifier in inheritance changes the MAX access level
 *  of inherited members in the derived class:
 *  ┌──────────┬───────────────────────────────────────────┐
 *  │ Base     │ public  │ protected │ private              │
 *  ├──────────┼─────────┼───────────┼──────────────────────┤
 *  │ public   │ public  │ protected │ private (inaccessible)│
 *  │ protected│protected│ protected │ private (inaccessible)│
 *  │ private  │ private │ private   │ private (inaccessible)│
 *  └──────────┴─────────┴───────────┴──────────────────────┘
 *  (row = base member access, column = inheritance mode,
 *   cell = access level in derived)
 *
 *  AVAILABLE vs ACCESSIBLE:
 *  - Everything from base is AVAILABLE in derived (memory-wise).
 *  - Private base members are NOT ACCESSIBLE from derived.
 *  - Analogy: Father's bank balance is AVAILABLE (inherited)
 *    but NOT ACCESSIBLE — son can't directly touch it.
 * ╚══════════════════════════════════════════════════════════╝
 */

#include <iostream>
#include <string>
using namespace std;

/* ══════════════════════════════════════════════════════════
   1. SINGLE INHERITANCE
   ══════════════════════════════════════════════════════════ */

class Animal
{
protected:
    string name;
    int age;

public:
    Animal(string n, int a) : name(n), age(a)
    {
        cout << "[Animal Constructor] " << name << "\n";
    }

    void eat() const { cout << name << " is eating.\n"; }
    void sleep() const { cout << name << " is sleeping.\n"; }

    virtual void speak() const
    { // virtual for polymorphism later
        cout << name << " makes a sound.\n";
    }

    ~Animal() { cout << "[Animal Destructor] " << name << "\n"; }
};

class Dog : public Animal
{
private:
    string breed;

public:
    /*
     * ╔══════════════════════════════════════════════════════╗
     *  INTERVIEW MUST-KNOW: Constructors in Inheritance
     *  - Base class constructor is called FIRST.
     *  - By default, the DEFAULT (non-parameterised) base
     *    constructor is called.
     *  - To call a PARAMETERISED base constructor, use
     *    initialiser list: Derived(...) : Base(args) {}
     * ╚══════════════════════════════════════════════════════╝
     */
    Dog(string n, int a, string b)
        : Animal(n, a), breed(b)
    {
        cout << "[Dog Constructor] " << name << " (" << breed << ")\n";
    }

    void speak() const override
    { // override base class virtual
        cout << name << " says: Woof!\n";
    }

    void fetch() const { cout << name << " is fetching the ball!\n"; }

    ~Dog() { cout << "[Dog Destructor] " << name << "\n"; }
};

/* ══════════════════════════════════════════════════════════
   2. MULTILEVEL INHERITANCE
   A → B → C  (chain)
   ══════════════════════════════════════════════════════════ */

class Vehicle
{
protected:
    string brand;
    int year;

public:
    Vehicle(string b, int y) : brand(b), year(y) {}
    void showBasic() const
    {
        cout << "Vehicle: " << brand << " (" << year << ")\n";
    }
};

class Car : public Vehicle
{
protected:
    int doors;

public:
    Car(string b, int y, int d) : Vehicle(b, y), doors(d) {}
    void showCar() const
    {
        cout << "Car: " << brand << " | Doors: " << doors << "\n";
    }
};

class ElectricCar : public Car
{
private:
    int batteryKWh;

public:
    ElectricCar(string b, int y, int d, int bat)
        : Car(b, y, d), batteryKWh(bat) {}
    void showElectric() const
    {
        cout << "ElectricCar: " << brand
             << " | Battery: " << batteryKWh << " kWh\n";
    }
};

/* ══════════════════════════════════════════════════════════
   3. MULTIPLE INHERITANCE
   Derived inherits from two or more base classes.
   ══════════════════════════════════════════════════════════

   ╔══════════════════════════════════════════════════════════╗
    INTERVIEW TIP: Multiple inheritance can lead to the
    Diamond Problem (see section 8 below).
    Real-world example: child inherits from both parents.
   ╚══════════════════════════════════════════════════════════╝
*/

class FlyingAbility
{
public:
    void fly() const { cout << "Flying high!\n"; }
};

class SwimmingAbility
{
public:
    void swim() const { cout << "Swimming fast!\n"; }
};

/* Duck inherits BOTH abilities */
class Duck : public Animal, public FlyingAbility, public SwimmingAbility
{
public:
    Duck(string n, int a) : Animal(n, a) {}
    void speak() const override
    {
        cout << name << " says: Quack!\n";
    }
};

/* ══════════════════════════════════════════════════════════
   4. HIERARCHICAL INHERITANCE
   Multiple derived classes from ONE base class.
   ══════════════════════════════════════════════════════════ */

class Shape
{
protected:
    string color;

public:
    Shape(string c) : color(c) {}
    virtual double area() const = 0; // pure virtual → abstract
    virtual void display() const
    {
        cout << "Shape [" << color << "] area=" << area() << "\n";
    }
};

class Triangle : public Shape
{
private:
    double base, height;

public:
    Triangle(string c, double b, double h)
        : Shape(c), base(b), height(h) {}
    double area() const override { return 0.5 * base * height; }
};

class Square : public Shape
{
private:
    double side;

public:
    Square(string c, double s) : Shape(c), side(s) {}
    double area() const override { return side * side; }
};

/* ══════════════════════════════════════════════════════════
   5. DIAMOND PROBLEM + VIRTUAL BASE CLASS
   ══════════════════════════════════════════════════════════

   ╔══════════════════════════════════════════════════════════╗
    INTERVIEW MUST-KNOW: The Diamond Problem
    Occurs in multiple inheritance when two parent classes
    share the same grandparent:
             Person
            /      \
         Father   Mother
            \      /
             Child
    Without virtual: Child gets TWO copies of Person.
    With 'virtual' keyword on Father and Mother: only ONE copy.

    Syntax: class Father : virtual public Person {}
            class Mother : virtual public Person {}
            class Child  : public Father, public Mother {}
   ╚══════════════════════════════════════════════════════════╝
*/

class Person
{
public:
    string name;
    Person(string n) : name(n)
    {
        cout << "[Person Constructor] " << name << "\n";
    }
    void introduce() const { cout << "Hi, I am " << name << "\n"; }
};

class Father : virtual public Person
{
public:
    Father(string n) : Person(n)
    {
        cout << "[Father Constructor]\n";
    }
    void fatherSkill() const { cout << "Father: coding expertise\n"; }
};

class Mother : virtual public Person
{
public:
    Mother(string n) : Person(n)
    {
        cout << "[Mother Constructor]\n";
    }
    void motherSkill() const { cout << "Mother: artistic talent\n"; }
};

/*
 * ╔══════════════════════════════════════════════════════════╗
 *  With virtual inheritance, Child must call the
 *  Person constructor DIRECTLY in its initialiser list.
 *  The virtual base class constructor is called FIRST.
 * ╚══════════════════════════════════════════════════════════╝
 */
class Child : public Father, public Mother
{
public:
    Child(string n) : Person(n), Father(n), Mother(n)
    {
        cout << "[Child Constructor]\n";
    }
    void show() const
    {
        introduce();
        fatherSkill();
        motherSkill();
    }
};

/* ══════════════════════════════════════════════════════════
   6. BASE CLASS POINTER → DERIVED CLASS OBJECT
   ══════════════════════════════════════════════════════════

   ╔══════════════════════════════════════════════════════════╗
    INTERVIEW MUST-KNOW:
    Base* ptr = new Derived();  ← VALID (upcasting)
    Derived* ptr = new Base();  ← INVALID (downcasting without cast)

    Why valid? A Derived object IS-A Base object.
    Why invalid? Base object is NOT necessarily a Derived object
    (derived may have extra members Base doesn't have).

    Using Base pointer → can only call BASE class methods
    (unless they are virtual — then derived version is called).
   ╚══════════════════════════════════════════════════════════╝
*/

class BasicCar
{
public:
    virtual void start() const { cout << "BasicCar: key ignition\n"; }
    void brake() const { cout << "BasicCar: brakes applied\n"; }
    virtual ~BasicCar() {}
};

class AdvancedCar : public BasicCar
{
public:
    void start() const override { cout << "AdvancedCar: push-button start + AC + GPS\n"; }
    void moonroof() const { cout << "AdvancedCar: moonroof opened\n"; }
};

/* ══════════════════════════════════════════════════════════
   MAIN
   ══════════════════════════════════════════════════════════ */
int main()
{
    cout << "===== Inheritance in C++ =====\n\n";

    /* --- Single Inheritance --- */
    cout << "--- 1. Single Inheritance ---\n";
    Dog d("Buddy", 3, "Labrador");
    d.eat();
    d.speak();
    d.fetch();

    /* --- Multilevel Inheritance --- */
    cout << "\n--- 2. Multilevel Inheritance ---\n";
    ElectricCar tesla("Tesla", 2024, 4, 100);
    tesla.showBasic();
    tesla.showCar();
    tesla.showElectric();

    /* --- Multiple Inheritance --- */
    cout << "\n--- 3. Multiple Inheritance ---\n";
    Duck duck("Donald", 2);
    duck.speak();
    duck.fly();
    duck.swim();

    /* --- Hierarchical Inheritance --- */
    cout << "\n--- 4. Hierarchical Inheritance ---\n";
    Triangle tri("red", 6.0, 4.0);
    Square sq("blue", 5.0);
    tri.display();
    sq.display();

    /* --- Diamond Problem + Virtual Base Class --- */
    cout << "\n--- 5. Diamond Problem + Virtual Base Class ---\n";
    Child child("Alex");
    child.show();

    /* --- Base Pointer → Derived Object --- */
    cout << "\n--- 6. Base Pointer → Derived Object ---\n";
    BasicCar *ptr = new AdvancedCar(); // VALID: upcasting
    ptr->start();                      // calls AdvancedCar::start() because virtual
    ptr->brake();                      // calls BasicCar::brake() (not virtual)
    // ptr->moonroof();  // COMPILE ERROR — BasicCar doesn't know moonroof

    delete ptr; // calls correct destructor (virtual ~BasicCar)

    cout << "\n--- Objects destroyed (destructor order: derived → base) ---\n";
    return 0;
}
