/*
 * ============================================================
 *  TOPIC: Constants and Pointers in C++
 * ============================================================
 *
 * Covered here:
 *   1. const variables
 *   2. #define vs const
 *   3. const Pointers (3 variants)
 *   4. const Member Functions
 *   5. const Parameters
 *   6. constexpr (C++11)
 *
 * ╔══════════════════════════════════════════════════════════╗
 *  INTERVIEW MUST-KNOW: The 3 Types of const Pointers
 *
 *  Reading tip: read RIGHT TO LEFT from the variable name.
 *
 *  1. Pointer to const data (data is read-only):
 *        const int* ptr = &x;
 *        int const* ptr = &x;   // same thing
 *     → *ptr = 5   is ILLEGAL   (cannot modify data)
 *     → ptr = &y   is LEGAL     (can point elsewhere)
 *
 *  2. Const pointer (pointer itself is read-only):
 *        int* const ptr = &x;
 *     → *ptr = 5   is LEGAL     (can modify data)
 *     → ptr = &y   is ILLEGAL   (pointer is fixed)
 *
 *  3. Const pointer to const data (both read-only):
 *        const int* const ptr = &x;
 *     → *ptr = 5   is ILLEGAL   (cannot modify data)
 *     → ptr = &y   is ILLEGAL   (pointer is fixed)
 *
 *  MEMORY TRICK: "const" applies to what is IMMEDIATELY TO ITS LEFT.
 *  If nothing is to its left (it's first), it applies to what's RIGHT.
 * ╚══════════════════════════════════════════════════════════╝
 */

#include <iostream>
#include <string>
using namespace std;

/* ══════════════════════════════════════════════════════════
   1. const VARIABLES
   ══════════════════════════════════════════════════════════ */

/* Two ways to define constants */
#define MAX_SIZE_MACRO 100      // preprocessor — no type, no scope, no memory
const int MAX_SIZE_CONST = 100; // true constant — typed, scoped, may use memory

/*
 * ╔══════════════════════════════════════════════════════════╗
 *  INTERVIEW MUST-KNOW: #define vs const
 *  ┌────────────────┬──────────────────────────────────────┐
 *  │ #define        │ const                                │
 *  ├────────────────┼──────────────────────────────────────┤
 *  │ Preprocessor   │ Compiler-level                       │
 *  │ No type        │ Has type (type-safe)                 │
 *  │ No memory      │ Occupies memory (usually)            │
 *  │ No scope       │ Respects scope                       │
 *  │ Hard to debug  │ Appears in debugger                  │
 *  │ Cannot be ptr  │ Can take address of const var        │
 *  └────────────────┴──────────────────────────────────────┘
 *  PREFER 'const' (or constexpr) over #define in modern C++.
 * ╚══════════════════════════════════════════════════════════╝
 */

/* ══════════════════════════════════════════════════════════
   2. const POINTERS — All 3 Variants
   ══════════════════════════════════════════════════════════ */

void constPointerDemo()
{
    cout << "--- const Pointer Variants ---\n";

    int x = 10, y = 30;

    /* Variant 1: Pointer to const data — data protected */
    const int *ptr1 = &x;
    cout << "Variant 1 (ptr to const): *ptr1 = " << *ptr1 << "\n";
    ptr1 = &y; // OK: pointer can move
    cout << "After ptr1 = &y: *ptr1 = " << *ptr1 << "\n";
    // *ptr1 = 50;      // ERROR: cannot modify data through ptr1

    /* Variant 2: Const pointer — pointer fixed, data mutable */
    int *const ptr2 = &x;
    *ptr2 = 99; // OK: can modify the data
    cout << "Variant 2 (const ptr): *ptr2 = " << *ptr2 << " x=" << x << "\n";
    // ptr2 = &y;       // ERROR: cannot change what ptr2 points to

    /* Variant 3: Const pointer to const data — fully read-only */
    const int *const ptr3 = &x;
    cout << "Variant 3 (const ptr to const): *ptr3 = " << *ptr3 << "\n";
    // *ptr3 = 5;       // ERROR
    // ptr3 = &y;       // ERROR

    /* Variant 2 analogy: pointer is a pin in a map — fixed location */
    cout << "\nSummary:\n";
    cout << "  const int* ptr   → ptr movable, data read-only\n";
    cout << "  int* const ptr   → ptr fixed, data modifiable\n";
    cout << "  const int* const → both fixed and read-only\n";
}

/* ══════════════════════════════════════════════════════════
   3. const MEMBER FUNCTIONS
   ══════════════════════════════════════════════════════════

   ╔══════════════════════════════════════════════════════════╗
    INTERVIEW MUST-KNOW: const member functions
    - Declared with 'const' AFTER the parameter list.
    - CANNOT modify any non-mutable member of the class.
    - Can be called on CONST objects (only const functions can).
    - 'mutable' keyword overrides const for specific members.
    - Overloading: you can have const and non-const versions
      of the same function (they are different overloads).
   ╚══════════════════════════════════════════════════════════╝
*/

class Temperature
{
private:
    double celsius;
    mutable int accessCount; // mutable: can be modified even in const func

public:
    Temperature(double c) : celsius(c), accessCount(0) {}

    /* const member function — cannot modify celsius */
    double getCelsius() const
    {
        ++accessCount; // OK: mutable member
        return celsius;
    }

    double getFahrenheit() const
    {
        ++accessCount;
        return celsius * 9.0 / 5.0 + 32;
    }

    double getKelvin() const
    {
        ++accessCount;
        return celsius + 273.15;
    }

    int getAccessCount() const { return accessCount; }

    /* Non-const function — can modify celsius */
    void setCelsius(double c) { celsius = c; }

    /* Const overload: returns const reference (for read) */
    const double &valueRef() const { return celsius; }

    /* Non-const overload: returns modifiable reference */
    double &valueRef() { return celsius; }
};

/* ══════════════════════════════════════════════════════════
   4. const PARAMETERS
   ══════════════════════════════════════════════════════════

   ╔══════════════════════════════════════════════════════════╗
    INTERVIEW TIP:
    Pass by const reference: const T& param
    - Avoids expensive copy (efficiency of pass-by-reference)
    - Prevents accidental modification (safety of pass-by-value)
    - This is the PREFERRED way to pass large objects in C++.
    - Primitives (int, double, char) can be passed by value —
      copy cost is trivial.
   ╚══════════════════════════════════════════════════════════╝
*/

double circleArea(const double &radius)
{
    // radius += 1;   // ERROR: cannot modify const parameter
    return 3.14159 * radius * radius;
}

void printTemp(const Temperature &t)
{
    /* t.setCelsius(0);   // ERROR: non-const function on const ref */
    cout << "Celsius=" << t.getCelsius() << " "
         << "Fahrenheit=" << t.getFahrenheit() << " "
         << "Kelvin=" << t.getKelvin() << "\n";
}

/* ══════════════════════════════════════════════════════════
   5. constexpr (C++11) — compile-time constants
   ══════════════════════════════════════════════════════════

   ╔══════════════════════════════════════════════════════════╗
    INTERVIEW MUST-KNOW: constexpr vs const
    const    : value fixed at runtime (could be runtime value)
    constexpr: value MUST be known at COMPILE TIME.
               Can be used in array sizes, template arguments, etc.
    constexpr functions: evaluated at compile time if all
               arguments are compile-time constants; otherwise
               fall back to runtime evaluation.
   ╚══════════════════════════════════════════════════════════╝
*/

constexpr int factorial(int n)
{
    return (n <= 1) ? 1 : n * factorial(n - 1);
}

constexpr double PI = 3.14159265358979;

constexpr double circleAreaCE(double r)
{
    return PI * r * r;
}

class FixedArray
{
private:
    static constexpr int SIZE = 10; // compile-time constant
    int data[SIZE];                 // array size must be compile-time

public:
    FixedArray()
    {
        for (int i = 0; i < SIZE; i++)
            data[i] = i;
    }

    static constexpr int size() { return SIZE; }

    int &operator[](int idx) { return data[idx]; }
};

/* ══════════════════════════════════════════════════════════
   6. const and POINTERS in function parameters
   ══════════════════════════════════════════════════════════ */

/* Array passed as const pointer — function cannot modify array */
int sumArray(const int *arr, int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += arr[i];
    // arr[0] = 999;   // ERROR: arr is const pointer to const int
    return sum;
}

/* String literal must always be assigned to const char* */
const char *getGreeting()
{
    return "Hello, World!"; // string literal is read-only
}

/* ══════════════════════════════════════════════════════════
   MAIN
   ══════════════════════════════════════════════════════════ */
int main()
{
    cout << "===== Constants and Pointers =====\n\n";

    /* --- const vs #define --- */
    cout << "--- 1. const vs #define ---\n";
    cout << "MAX_SIZE_MACRO = " << MAX_SIZE_MACRO << " (no type, no debug)\n";
    cout << "MAX_SIZE_CONST = " << MAX_SIZE_CONST << " (typed, debuggable)\n";

    /* --- const Pointer Variants --- */
    cout << "\n";
    constPointerDemo();

    /* --- const Member Functions --- */
    cout << "\n--- 3. const Member Functions ---\n";
    Temperature t(100.0);
    printTemp(t);
    cout << "Access count: " << t.getAccessCount() << "\n";

    const Temperature freezing(0.0);
    printTemp(freezing);
    /* freezing.setCelsius(10);  // ERROR: non-const on const object */

    /* Non-const overload */
    t.valueRef() = 200.0; // calls non-const valueRef()
    cout << "After modifying via valueRef(): " << t.getCelsius() << "\n";

    /* --- const Parameters --- */
    cout << "\n--- 4. const Parameters ---\n";
    double r = 5.0;
    cout << "Circle area(r=5) = " << circleArea(r) << "\n";

    int arr[] = {1, 2, 3, 4, 5};
    cout << "Sum of array = " << sumArray(arr, 5) << "\n";

    const char *msg = getGreeting();
    cout << "Greeting: " << msg << "\n";

    /* --- constexpr --- */
    cout << "\n--- 5. constexpr (Compile-Time Constants) ---\n";
    constexpr int fact5 = factorial(5); // computed at compile time!
    constexpr int fact10 = factorial(10);
    cout << "factorial(5)  = " << fact5 << "\n";
    cout << "factorial(10) = " << fact10 << "\n";
    cout << "PI = " << PI << "\n";
    cout << "circleAreaCE(3.0) = " << circleAreaCE(3.0) << "\n";

    FixedArray fa;
    cout << "FixedArray size = " << FixedArray::size() << "\n";
    cout << "fa[3] = " << fa[3] << "\n";

    return 0;
}
