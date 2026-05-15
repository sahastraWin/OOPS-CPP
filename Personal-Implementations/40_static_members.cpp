/*
    QUESTION:
    Write a C++ program demonstrating STATIC MEMBERS of a class.
    Class 'Stat' has a static member 'count' that tracks how many objects
    have been created. Each new object increments count and stores its code.
    Static members are SHARED across all instances.
    Output: Object codes and count after creating two objects
*/

#include <bits/stdc++.h>
using namespace std;

class Stat
{
    int code;
    static int count;  // shared across ALL Stat objects

public:
    Stat()
    {
        code = ++count;  // each new object gets next sequential code
    }

    void showcode()
    {
        cout << "Object code: " << code << endl;
    }

    static void showcount()
    {
        cout << "Total objects created: " << count << endl;
    }
};

int Stat::count = 0;  // initialize static member outside the class

int main()
{
    Stat obj1, obj2;

    obj1.showcount();  // static method: shows count = 2
    obj1.showcode();   // instance method: shows code = 1

    obj2.showcount();  // static method: shows count = 2
    obj2.showcode();   // instance method: shows code = 2

    // Can also call static method via class name:
    Stat::showcount();

    return 0;
}

/*
    INTUITION:
    - STATIC MEMBER VARIABLE: shared by ALL objects of the class — there is
      only ONE copy in memory, not one per object.
    - int Stat::count = 0 initializes it ONCE outside the class definition.
    - Each constructor call: code = ++count increments the shared count first,
      then assigns the new value as this object's unique code.
    - STATIC MEMBER FUNCTION: can be called without an object (Stat::showcount()).
      It can ONLY access static members (no 'this' pointer — no specific object).
    - Use cases for static members:
        - Object counter (like here).
        - Shared configuration values (e.g., max allowed instances).
        - Singleton pattern.

    TIME COMPLEXITY:  O(1) — constructor and methods are constant time.
    SPACE COMPLEXITY: O(1) per object for 'code'; O(1) total for static 'count'.
*/
