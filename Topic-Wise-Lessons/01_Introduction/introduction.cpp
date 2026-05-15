/*
 * ============================================================
 *  TOPIC: Introduction to Object-Oriented Programming (OOP)
 * ============================================================
 *
 * OOP is a programming PARADIGM that revolves around OBJECTS.
 *
 * KEY TERMS:
 *   - Object  : Instance of a class. Occupies memory, has state & behavior.
 *   - Class   : Blueprint / template for objects. No memory consumed by itself.
 *   - Simula  : First OOP language ever created.
 *
 * OOP vs Procedural:
 *   - OOP      -> Bottom-up approach
 *   - Procedural -> Top-down approach
 *
 * ╔══════════════════════════════════════════════════════════╗
 *  INTERVIEW MUST-KNOW: The 4 Pillars of OOP
 *   1. Encapsulation  - Binding data + functions together; data hiding
 *   2. Abstraction    - Hiding internal details, showing only essential info
 *   3. Inheritance    - Deriving new class from existing class (reusability)
 *   4. Polymorphism   - One interface, many forms
 * ╚══════════════════════════════════════════════════════════╝
 *
 * PROGRAMMING PARADIGMS:
 *   Imperative:
 *     a) Procedural   - step-by-step, top-down (C, Pascal)
 *     b) OOP          - object-centric, bottom-up (C++, Java, Python)
 *     c) Parallel     - tasks run simultaneously
 *   Declarative:
 *     a) Logical      - rule-based (Prolog)
 *     b) Functional   - compose functions (Haskell, Erlang)
 *     c) Database     - data manipulation (SQL)
 */

#include <iostream>
#include <string>
using namespace std;

/* ──────────────────────────────────────────────────────────
   A minimal class to demonstrate the OOP idea.
   The class is a BLUEPRINT; the object is the REAL ENTITY.
   ────────────────────────────────────────────────────────── */
class Car
{
private:
    /*
     * ╔══════════════════════════════════════════╗
     *  ENCAPSULATION: data is private by default
     *  in a class (unlike struct where it's public)
     * ╚══════════════════════════════════════════╝
     */
    string brand;
    int year;
    double speed; // km/h

public:
    /* Constructor - initialises the object at creation time */
    Car(string b, int y, double s) : brand(b), year(y), speed(s)
    {
        cout << "[Constructor] " << brand << " created.\n";
    }

    /* ABSTRACTION: user only knows what the car can DO,
       not HOW the engine works internally */
    void accelerate(double delta)
    {
        speed += delta;
        cout << brand << " accelerated to " << speed << " km/h\n";
    }

    void displayInfo() const
    {
        cout << "Brand: " << brand
             << " | Year: " << year
             << " | Speed: " << speed << " km/h\n";
    }

    /* Destructor */
    ~Car()
    {
        cout << "[Destructor] " << brand << " destroyed.\n";
    }
};

/* ──────────────────────────────────────────────────────────
   Demonstrating OOP vs Procedural thinking
   ────────────────────────────────────────────────────────── */
// Procedural way (just functions + data, no cohesion)
void showCarProcedural(string brand, int year)
{
    cout << "[Procedural] Brand: " << brand << ", Year: " << year << "\n";
}

int main()
{
    cout << "===== Introduction to OOP in C++ =====\n\n";

    /* ----- Procedural style ----- */
    cout << "--- Procedural Style ---\n";
    showCarProcedural("Toyota", 2020);

    /* ----- OOP style ----- */
    cout << "\n--- OOP Style ---\n";

    /*
     * ╔══════════════════════════════════════════════════════╗
     *  INTERVIEW TIP:
     *  Objects are created on STACK (automatic storage) here.
     *  Stack memory is automatically reclaimed when scope ends.
     *  For heap allocation use: Car* c = new Car(...); delete c;
     * ╚══════════════════════════════════════════════════════╝
     */
    Car myCar("Tesla Model 3", 2023, 0.0);
    myCar.displayInfo();
    myCar.accelerate(60.0);
    myCar.accelerate(40.0);
    myCar.displayInfo();

    cout << "\n--- Multiple Objects (each has its OWN state) ---\n";
    Car bmw("BMW X5", 2022, 0.0);
    Car honda("Honda Civic", 2021, 0.0);
    bmw.accelerate(80.0);
    honda.accelerate(50.0);

    /*
     * ╔══════════════════════════════════════════════════════╗
     *  INTERVIEW TIP:
     *  sizeof(class) = sum of non-static data member sizes
     *                  (+ padding/alignment by compiler).
     *  Static members are NOT counted in sizeof(object).
     * ╚══════════════════════════════════════════════════════╝
     */
    cout << "\nSize of Car object: " << sizeof(Car) << " bytes\n";

    cout << "\n--- OOP Benefits demonstrated ---\n";
    cout << "Modularity   : Car is a self-contained unit\n";
    cout << "Reusability  : Car class can create any number of objects\n";
    cout << "Extensibility: Can subclass Car -> ElectricCar, SportsCar\n";
    cout << "Maintainability: Fix once inside class, affects all objects\n";

    return 0;
    // Destructors called automatically when stack objects go out of scope
}
