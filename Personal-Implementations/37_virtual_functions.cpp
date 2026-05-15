/*
    QUESTION:
    Write a C++ program demonstrating VIRTUAL FUNCTIONS and RUNTIME POLYMORPHISM.
    Base class has: virtual show() and non-virtual display().
    Derived class overrides both show() and display().
    Use a Base pointer to point to both Base and Derived objects.
    Observe which version of each function gets called.
    Output: Shows virtual (runtime) vs non-virtual (compile-time) dispatch
*/

#include <bits/stdc++.h>
using namespace std;

class Base
{
public:
    virtual void show()    { cout << "Base show" << endl; }
    void display()         { cout << "Base display" << endl; }
};

class Drive : public Base
{
public:
    void display() { cout << "Drive display" << endl; }
    void show()    { cout << "Drive show" << endl; }
};

int main()
{
    Base obj1;
    Base *p;

    cout << "--- P points to Base: ---" << endl;
    p = &obj1;
    p->display();   // Base::display (non-virtual → compile-time)
    p->show();      // Base::show    (virtual → runtime → Base)

    cout << "\n--- P points to Drive: ---" << endl;
    Drive obj2;
    p = &obj2;
    p->display();   // Base::display (non-virtual → compile-time → Base)
    p->show();      // Drive::show   (virtual → runtime → Drive)

    return 0;
}

/*
    INTUITION:
    - VIRTUAL FUNCTIONS enable RUNTIME POLYMORPHISM (dynamic dispatch).
    - When a function is virtual and called via a BASE POINTER/REFERENCE,
      C++ looks at the ACTUAL OBJECT TYPE at runtime to decide which version to call.
    - NON-VIRTUAL functions use STATIC DISPATCH: the function called depends on
      the POINTER TYPE (Base*), not the actual object type.
    - Comparison:
        p = &obj2 (Drive object, Base pointer):
        p->display() → Base::display  (non-virtual: uses pointer type = Base)
        p->show()    → Drive::show    (virtual: uses object type = Drive)
    - This is the core of OOP polymorphism — "one interface, many implementations."
    - Virtual functions work through the VTABLE (virtual function table):
      each object with virtual functions has a hidden pointer to a vtable.

    TIME COMPLEXITY:  O(1) — constant function calls.
    SPACE COMPLEXITY: O(1) — vtable overhead (hidden pointer per object).
*/
