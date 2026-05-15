/*
 * ============================================================
 *  TOPIC: Constructors in C++
 * ============================================================
 *
 * A constructor is a special member function that is:
 *   - Automatically called when an object is created.
 *   - Has the SAME name as the class.
 *   - Has NO return type (not even void).
 *
 * Types covered:
 *   1. Default (Non-Parameterised) Constructor
 *   2. Parameterised Constructor
 *   3. Copy Constructor  (Shallow Copy)
 *   4. Deep Copy Constructor
 *   5. Destructor basics
 *   6. Constructor Initialiser List
 *
 * ╔══════════════════════════════════════════════════════════╗
 *  INTERVIEW MUST-KNOW:
 *  - If you do NOT define any constructor, compiler provides
 *    a default one (does nothing for primitives).
 *  - If you define ANY constructor, compiler does NOT provide
 *    the default constructor automatically.
 *  - Constructor CANNOT be virtual.
 *  - Destructor CAN be virtual (and often should be in base class).
 *  - Constructor CANNOT have a return type.
 *  - Constructors CAN be overloaded.
 *  - Destructors CANNOT be overloaded (only one destructor per class).
 * ╚══════════════════════════════════════════════════════════╝
 */

#include <iostream>
#include <cstring> // for strcpy, strlen
#include <string>
using namespace std;

/* ══════════════════════════════════════════════════════════
   1. DEFAULT (NON-PARAMETERISED) CONSTRUCTOR
   ══════════════════════════════════════════════════════════ */

class Box
{
private:
    double length, width, height;

public:
    /*
     * Default constructor — no arguments.
     * Compiler auto-provides one IF no constructor is declared.
     * Here we define it explicitly and give sensible defaults.
     */
    Box() : length(1.0), width(1.0), height(1.0)
    {
        cout << "[Box Default Constructor called]\n";
    }

    double volume() const { return length * width * height; }
    void display() const
    {
        cout << "Box(" << length << " x " << width << " x " << height
             << ") Volume=" << volume() << "\n";
    }
};

/* ══════════════════════════════════════════════════════════
   2. PARAMETERISED CONSTRUCTOR
   ══════════════════════════════════════════════════════════

   ╔══════════════════════════════════════════════════════════╗
    INTERVIEW TIP:
    Use an INITIALISER LIST (colon syntax) instead of
    assignment in the body — it is MORE EFFICIENT because:
    - For const members and references, initialiser list is
      the ONLY way to initialise them.
    - For member objects, it calls their constructor directly
      (avoids double initialisation).
    Order of initialisation = ORDER OF DECLARATION in class,
    NOT the order in the initialiser list.
   ╚══════════════════════════════════════════════════════════╝
*/

class Person
{
private:
    string name;
    int age;
    const int id; // const member MUST use initialiser list

public:
    /* Parameterised constructor with initialiser list */
    Person(string n, int a, int i) : name(n), age(a), id(i)
    {
        cout << "[Person Parameterised Constructor] " << name << " created.\n";
    }

    void display() const
    {
        cout << "Person(id=" << id << ", name=" << name
             << ", age=" << age << ")\n";
    }
};

/* ══════════════════════════════════════════════════════════
   3. COPY CONSTRUCTOR — SHALLOW COPY
   ══════════════════════════════════════════════════════════

   ╔══════════════════════════════════════════════════════════╗
    INTERVIEW MUST-KNOW:
    Signature of Copy Constructor:
        ClassName(const ClassName& other);
    - Takes a CONST REFERENCE to another object of the same class.
    - If you DON'T define one, compiler provides a DEFAULT copy
      constructor that does a MEMBER-WISE (shallow) copy.
    - Shallow copy copies pointer VALUES, not the data pointed to.
      Both objects then share the same heap memory → DANGER!
      (double free, dangling pointer on destruction)
    - When copy constructor is invoked:
        * Object passed by value to a function
        * Object returned by value from a function
        * Object initialised from another: T b = a;
   ╚══════════════════════════════════════════════════════════╝
*/

class ShallowExample
{
public:
    int *data;
    int size;

    ShallowExample(int sz) : size(sz)
    {
        data = new int[sz];
        for (int i = 0; i < sz; i++)
            data[i] = i * 10;
        cout << "[ShallowExample Constructor] allocated at " << data << "\n";
    }

    /*
     * Compiler-generated copy constructor does this:
     * ShallowExample(const ShallowExample& other) {
     *     data = other.data;   // copies the POINTER, NOT the data!
     *     size = other.size;
     * }
     * PROBLEM: both objects point to the SAME heap block.
     * When one destructs → deletes memory → other has dangling ptr.
     */

    ~ShallowExample()
    {
        cout << "[ShallowExample Destructor] freeing " << data << "\n";
        delete[] data;
    }
};

/* ══════════════════════════════════════════════════════════
   4. DEEP COPY CONSTRUCTOR
   ══════════════════════════════════════════════════════════

   ╔══════════════════════════════════════════════════════════╗
    INTERVIEW MUST-KNOW: The Rule of Three (C++03)
    If a class defines ANY of:
      1. Destructor
      2. Copy Constructor
      3. Copy Assignment Operator
    then it almost certainly needs to define all THREE.

    Rule of Five (C++11 adds):
      4. Move Constructor
      5. Move Assignment Operator

    Rule of Zero: Prefer classes that need NONE of these
    (use RAII wrappers like smart pointers / std::string).
   ╚══════════════════════════════════════════════════════════╝
*/

class DeepArray
{
private:
    int *data;
    int size;

public:
    /* Constructor */
    DeepArray(int sz) : size(sz)
    {
        data = new int[sz];
        for (int i = 0; i < sz; i++)
            data[i] = i + 1;
        cout << "[DeepArray Constructor] allocated at " << (void *)data << "\n";
    }

    /* DEEP Copy Constructor — allocates NEW memory and copies VALUES */
    DeepArray(const DeepArray &other) : size(other.size)
    {
        data = new int[size]; // NEW allocation
        for (int i = 0; i < size; i++)
            data[i] = other.data[i]; // copy values
        cout << "[DeepArray DEEP Copy Constructor] new allocation at "
             << (void *)data << "\n";
    }

    /* Copy Assignment Operator (for completeness — Rule of Three) */
    DeepArray &operator=(const DeepArray &other)
    {
        if (this == &other)
            return *this; // self-assignment guard
        delete[] data;    // free old memory
        size = other.size;
        data = new int[size];
        for (int i = 0; i < size; i++)
            data[i] = other.data[i];
        cout << "[DeepArray Copy Assignment] new allocation at "
             << (void *)data << "\n";
        return *this;
    }

    void display() const
    {
        cout << "DeepArray[" << (void *)data << "]: ";
        for (int i = 0; i < size; i++)
            cout << data[i] << " ";
        cout << "\n";
    }

    /* Destructor */
    ~DeepArray()
    {
        cout << "[DeepArray Destructor] freeing " << (void *)data << "\n";
        delete[] data;
    }
};

/* ══════════════════════════════════════════════════════════
   5. CONSTRUCTOR DELEGATION (C++11)
   ══════════════════════════════════════════════════════════

   ╔══════════════════════════════════════════════════════════╗
    INTERVIEW TIP:
    One constructor can call another constructor of the SAME
    class in its initialiser list. This avoids code duplication.
   ╚══════════════════════════════════════════════════════════╝
*/

class Config
{
private:
    string host;
    int port;
    bool ssl;

public:
    /* Primary constructor */
    Config(string h, int p, bool s) : host(h), port(p), ssl(s)
    {
        cout << "[Config] " << host << ":" << port
             << (ssl ? " (SSL)" : "") << "\n";
    }

    /* Delegating constructors — call the primary one */
    Config(string h, int p) : Config(h, p, false) {} // no SSL default
    Config() : Config("localhost", 8080) {}          // full default

    void display() const
    {
        cout << "Host=" << host << " Port=" << port
             << " SSL=" << ssl << "\n";
    }
};

/* ══════════════════════════════════════════════════════════
   MAIN
   ══════════════════════════════════════════════════════════ */
int main()
{
    cout << "===== Constructors in C++ =====\n\n";

    /* --- Default Constructor --- */
    cout << "--- 1. Default Constructor ---\n";
    Box b1;
    b1.display();

    /* --- Parameterised Constructor --- */
    cout << "\n--- 2. Parameterised Constructor ---\n";
    Person p1("Alice", 22, 1001);
    p1.display();
    Person p2("Bob", 25, 1002);
    p2.display();

    /* --- Deep Copy Constructor --- */
    cout << "\n--- 3. Deep Copy Constructor ---\n";
    DeepArray arr1(5);
    arr1.display();

    DeepArray arr2(arr1); // invokes deep copy constructor
    arr2.display();

    cout << "Modifying arr1's first element to 999...\n";
    arr1.data[0] = 999; // should NOT affect arr2

    cout << "arr1: ";
    arr1.display();
    cout << "arr2: ";
    arr2.display(); // arr2 is independent

    /* --- Copy Assignment --- */
    cout << "\n--- Copy Assignment Operator ---\n";
    DeepArray arr3(3);
    arr3 = arr1; // copy assignment
    cout << "arr3 after assignment: ";
    arr3.display();

    /* --- Delegating Constructors --- */
    cout << "\n--- Delegating Constructors (C++11) ---\n";
    Config c1;
    Config c2("api.example.com", 443);
    Config c3("db.internal", 5432, true);
    c1.display();
    c2.display();
    c3.display();

    cout << "\n--- Destructors called as objects go out of scope ---\n";
    return 0;
}
