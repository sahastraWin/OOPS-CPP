/*
 * ============================================================
 *  TOPIC: Destructors in C++
 * ============================================================
 *
 * A destructor is a special member function that:
 *   - Is automatically called when an object goes out of scope
 *     or is explicitly deleted.
 *   - Has the SAME name as the class preceded by tilde (~).
 *   - Has NO return type and NO parameters.
 *   - CANNOT be overloaded (only one destructor per class).
 *   - CAN be virtual.
 *
 * Covered here:
 *   1. Basic Destructor
 *   2. Destructor in Inheritance (order of calls)
 *   3. Virtual Destructor (CRITICAL for polymorphism)
 *   4. Pure Virtual Destructor
 *   5. RAII pattern (Resource Acquisition Is Initialisation)
 *   6. Static vs Dynamic object destruction
 *
 * ╔══════════════════════════════════════════════════════════╗
 *  INTERVIEW MUST-KNOW:
 *  Constructor order : Base → Derived (top-down)
 *  Destructor order  : Derived → Base (bottom-up) — REVERSE!
 *
 *  WHEN is destructor called?
 *    1. Local object goes out of scope
 *    2. delete ptr  (dynamically allocated object)
 *    3. Temporary object lifetime ends
 *    4. Program ends (global/static objects)
 *    5. Explicitly called: obj.~ClassName()  (rare)
 *
 *  Rules:
 *    - No arguments, no return type, no overloading.
 *    - Destructor of a class with virtual functions should be virtual.
 *    - Destructors should NOT throw exceptions.
 *    - If not defined, compiler provides a default one.
 *
 *  When do you NEED to define a destructor?
 *    When the class manages EXTERNAL resources:
 *      - Heap memory (new/delete)
 *      - File handles
 *      - Network connections
 *      - Mutex locks
 * ╚══════════════════════════════════════════════════════════╝
 */

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

/* ══════════════════════════════════════════════════════════
   1. BASIC DESTRUCTOR
   ══════════════════════════════════════════════════════════ */

class ResourceHolder
{
private:
    int *buffer;
    int size;
    string name;

public:
    ResourceHolder(string n, int sz) : name(n), size(sz)
    {
        buffer = new int[sz];
        for (int i = 0; i < sz; i++)
            buffer[i] = i;
        cout << "[ResourceHolder] '" << name << "' allocated " << sz << " ints\n";
    }

    /*
     * ╔══════════════════════════════════════════════════╗
     *  DESTRUCTOR releases heap memory.
     *  Without this: MEMORY LEAK (buffer is never freed).
     *  Rule of Three: if you need a destructor, you probably
     *  also need a copy constructor and copy assignment operator.
     * ╚══════════════════════════════════════════════════╝
     */
    ~ResourceHolder()
    {
        delete[] buffer;
        cout << "[~ResourceHolder] '" << name << "' memory freed\n";
    }

    void display() const
    {
        cout << "ResourceHolder('" << name << "'): ";
        for (int i = 0; i < size; i++)
            cout << buffer[i] << " ";
        cout << "\n";
    }
};

/* ══════════════════════════════════════════════════════════
   2. DESTRUCTOR CALL ORDER IN INHERITANCE
   ══════════════════════════════════════════════════════════ */

class GrandParent
{
public:
    GrandParent() { cout << "[GrandParent Constructor]\n"; }
    ~GrandParent() { cout << "[GrandParent Destructor]\n"; }
};

class Parent : public GrandParent
{
public:
    Parent() { cout << "[Parent Constructor]\n"; }
    ~Parent() { cout << "[Parent Destructor]\n"; }
};

class Child : public Parent
{
public:
    Child() { cout << "[Child Constructor]\n"; }
    ~Child() { cout << "[Child Destructor]\n"; }
};

/* ══════════════════════════════════════════════════════════
   3. VIRTUAL DESTRUCTOR — CRITICAL for polymorphism
   ══════════════════════════════════════════════════════════

   ╔══════════════════════════════════════════════════════════╗
    INTERVIEW MUST-KNOW: The most important destructor rule!

    Scenario:
        Base* ptr = new Derived();
        delete ptr;

    Without virtual destructor in Base:
        Only Base destructor is called → Derived resources LEAKED!

    With virtual destructor in Base:
        Derived destructor called FIRST, then Base destructor.
        All resources properly released.

    RULE: If a class has ANY virtual function, make its
    destructor virtual. This is almost always the right thing
    to do for base classes meant for polymorphic use.
   ╚══════════════════════════════════════════════════════════╝
*/

class Animal
{
public:
    string name;

    Animal(string n) : name(n)
    {
        cout << "[Animal Constructor] " << name << "\n";
    }

    /*
     * WITHOUT 'virtual': only Animal destructor called for base ptr.
     * WITH    'virtual': Dog destructor called first, then Animal.
     */
    virtual ~Animal()
    {
        cout << "[Animal Virtual Destructor] " << name << "\n";
    }

    virtual void speak() const = 0; // pure virtual
};

class Dog : public Animal
{
private:
    string *tricks; // heap resource
    int numTricks;

public:
    Dog(string n, int t) : Animal(n), numTricks(t)
    {
        tricks = new string[t];
        for (int i = 0; i < t; i++)
            tricks[i] = "trick_" + to_string(i);
        cout << "[Dog Constructor] " << name << " with " << t << " tricks\n";
    }

    ~Dog() override
    {
        delete[] tricks; // WITHOUT virtual base destructor, this never runs!
        cout << "[Dog Destructor] " << name << " tricks freed\n";
    }

    void speak() const override
    {
        cout << name << " says: Woof!\n";
    }
};

class Cat : public Animal
{
private:
    int *scratchCount; // heap resource

public:
    Cat(string n) : Animal(n)
    {
        scratchCount = new int(0);
        cout << "[Cat Constructor] " << name << "\n";
    }

    ~Cat() override
    {
        delete scratchCount;
        cout << "[Cat Destructor] " << name << " scratchCount freed\n";
    }

    void speak() const override
    {
        cout << name << " says: Meow!\n";
    }
};

/* ══════════════════════════════════════════════════════════
   4. PURE VIRTUAL DESTRUCTOR
   ══════════════════════════════════════════════════════════

   ╔══════════════════════════════════════════════════════════╗
    INTERVIEW TIP:
    You CAN declare a destructor as pure virtual:
        virtual ~AbstractBase() = 0;
    But you MUST still PROVIDE A DEFINITION (even pure virtual
    destructors must have a body, called during stack unwinding).
    This makes the class ABSTRACT without any other pure virtuals.
   ╚══════════════════════════════════════════════════════════╝
*/

class AbstractShape
{
public:
    virtual double area() const = 0;
    virtual ~AbstractShape() = 0; // pure virtual destructor
};

/* MUST define even though it's pure virtual */
AbstractShape::~AbstractShape()
{
    cout << "[AbstractShape Pure Virtual Destructor]\n";
}

class ConcreteCircle : public AbstractShape
{
private:
    double radius;

public:
    ConcreteCircle(double r) : radius(r) {}
    double area() const override { return 3.14159 * radius * radius; }
    ~ConcreteCircle() override
    {
        cout << "[ConcreteCircle Destructor]\n";
    }
};

/* ══════════════════════════════════════════════════════════
   5. RAII — Resource Acquisition Is Initialisation
   ══════════════════════════════════════════════════════════

   ╔══════════════════════════════════════════════════════════╗
    INTERVIEW MUST-KNOW: RAII Pattern
    - Resources are tied to object LIFETIME.
    - Acquired in the CONSTRUCTOR.
    - Released in the DESTRUCTOR (automatically, even on exceptions).
    - This is the foundation of smart pointers, std::lock_guard, etc.
    - Makes code EXCEPTION-SAFE without try/finally blocks.
   ╚══════════════════════════════════════════════════════════╝
*/

class FileRAII
{
private:
    FILE *file;
    string filename;

public:
    FileRAII(const string &fname, const string &mode)
        : filename(fname)
    {
        file = fopen(fname.c_str(), mode.c_str());
        if (!file)
            throw runtime_error("Cannot open file: " + fname);
        cout << "[FileRAII] Opened: " << filename << "\n";
    }

    ~FileRAII()
    {
        if (file)
        {
            fclose(file);
            cout << "[FileRAII] Closed: " << filename << "\n";
        }
    }

    void write(const string &data)
    {
        if (file)
            fputs(data.c_str(), file);
    }

    /* Prevent copy — file handles should not be shared */
    FileRAII(const FileRAII &) = delete;
    FileRAII &operator=(const FileRAII &) = delete;
};

class MutexRAII
{
private:
    string mutexName;
    bool locked;

public:
    MutexRAII(const string &name) : mutexName(name), locked(false)
    {
        locked = true;
        cout << "[MutexRAII] Locked: " << mutexName << "\n";
    }

    ~MutexRAII()
    {
        if (locked)
        {
            locked = false;
            cout << "[MutexRAII] Unlocked: " << mutexName << " (auto on scope exit)\n";
        }
    }
};

/* ══════════════════════════════════════════════════════════
   6. STATIC vs DYNAMIC object destruction
   ══════════════════════════════════════════════════════════ */

class Tracer
{
private:
    string tag;

public:
    Tracer(string t) : tag(t) { cout << "[Tracer CTOR] " << tag << "\n"; }
    ~Tracer() { cout << "[Tracer DTOR] " << tag << "\n"; }
};

static Tracer globalTracer("GLOBAL"); // ctor before main, dtor after main

/* ══════════════════════════════════════════════════════════
   MAIN
   ══════════════════════════════════════════════════════════ */
int main()
{
    cout << "===== Destructors in C++ =====\n\n";

    /* --- Basic Destructor --- */
    cout << "--- 1. Basic Destructor (heap resource) ---\n";
    {
        ResourceHolder rh("buffer_A", 5);
        rh.display();
    } // <-- destructor called here as rh goes out of scope
    cout << "(rh destroyed)\n";

    /* Dynamic allocation */
    cout << "\nDynamic object:\n";
    ResourceHolder *rp = new ResourceHolder("buffer_B", 3);
    rp->display();
    delete rp; // destructor called here

    /* --- Constructor / Destructor order --- */
    cout << "\n--- 2. Inheritance Constructor/Destructor Order ---\n";
    {
        Child c;
        cout << "(Child object in scope)\n";
    } // Destructor called: Child → Parent → GrandParent

    /* --- Virtual Destructor --- */
    cout << "\n--- 3. Virtual Destructor (Polymorphic Delete) ---\n";
    Animal *animals[2];
    animals[0] = new Dog("Rex", 3);
    animals[1] = new Cat("Whiskers");

    for (auto &a : animals)
        a->speak();

    cout << "\nDeleting via base pointer (virtual destructor):\n";
    for (auto &a : animals)
        delete a; // correct: virtual dispatches Dog/Cat dtor first

    /* --- Pure Virtual Destructor --- */
    cout << "\n--- 4. Pure Virtual Destructor ---\n";
    AbstractShape *shape = new ConcreteCircle(5.0);
    cout << "Area = " << shape->area() << "\n";
    delete shape; // ConcreteCircle dtor, then AbstractShape dtor

    /* --- RAII --- */
    cout << "\n--- 5. RAII (auto resource release) ---\n";
    try
    {
        FileRAII f("test_raii.txt", "w");
        f.write("Hello from RAII!\n");
        // file automatically closed when f goes out of scope
    }
    catch (const runtime_error &e)
    {
        cout << "File error: " << e.what() << "\n";
    }

    {
        MutexRAII lock("db_mutex");
        cout << "  (critical section — db operations here)\n";
    } // lock automatically released here

    cout << "\n(main ending — global Tracer will be destroyed after main)\n";
    return 0;
}
