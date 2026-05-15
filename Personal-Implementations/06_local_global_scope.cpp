/*
    Question:
    Explain and demonstrate:
    1. Local Variables — declared inside a function/block, limited scope
    2. Global Variables — declared outside all functions, accessible everywhere
    3. Parameters — variables passed into a function
    4. Scope — where a variable is accessible

    Intuition:
    Think of scope like physical rooms in a building:
    - Global variable = hallway (everyone can access it)
    - Local variable  = inside a room (only that room's occupants can use it)
    - Parameter       = something passed into a room (exists only while you're in that room)

    Key Rules:
    1. Local variables exist only within their {} block.
    2. Global variables exist for the entire program duration.
    3. If a local variable has the same name as a global, local takes priority inside that scope.
    4. Parameters behave like local variables — they are created on function entry, destroyed on exit.

    Time Complexity:  O(1) — all operations constant
    Space Complexity: O(1) — fixed variables
*/

#include <bits/stdc++.h>
using namespace std;

// -------------------------------------------------------
// GLOBAL VARIABLE — accessible anywhere in this file
// -------------------------------------------------------
int globalVar = 100;
int counter = 0; // global counter shared across functions

// -------------------------------------------------------
// Function to demonstrate parameter scope
// -------------------------------------------------------
void showParameterScope(int param)
{
    // param is a LOCAL copy — changes here don't affect caller
    cout << "Inside showParameterScope:" << endl;
    cout << "  param (local) = " << param << endl;
    param = param * 2; // modifying local copy
    cout << "  param after modification = " << param << endl;
    // param ceases to exist after this function returns
}

// -------------------------------------------------------
// Function to demonstrate local vs global
// -------------------------------------------------------
void demonstrateScope()
{
    int localVar = 50; // LOCAL — only accessible inside this function

    cout << "Inside demonstrateScope():" << endl;
    cout << "  localVar  (local)  = " << localVar << endl;
    cout << "  globalVar (global) = " << globalVar << endl;

    globalVar += 10; // modifying global — affects everywhere
    counter++;       // modifying global counter

    cout << "  globalVar after modification = " << globalVar << endl;
}

// -------------------------------------------------------
// Function showing block-level scope
// -------------------------------------------------------
void blockScope()
{
    int x = 1; // outer block
    cout << "Outer block x = " << x << endl;

    {
        int x = 99; // inner block — DIFFERENT x (shadows outer)
        cout << "Inner block x = " << x << endl;
        int y = 200; // y only exists inside this inner block
        cout << "Inner block y = " << y << endl;
    }
    // y is NOT accessible here — out of scope
    // inner x is NOT accessible here

    cout << "Back to outer block x = " << x << endl;
    // cout << y; // ERROR: y is out of scope here
}

// -------------------------------------------------------
// Function showing loop variable scope
// -------------------------------------------------------
void loopScope()
{
    for (int i = 0; i < 3; i++)
    {
        // i is scoped to the for loop
        int loopLocal = i * 10; // exists only in this iteration
        cout << "i = " << i << ", loopLocal = " << loopLocal << endl;
    }
    // cout << i; // ERROR: i is out of scope here
}

// -------------------------------------------------------
// MAIN
// -------------------------------------------------------
int main()
{

    cout << "=== Global Variable ===" << endl;
    cout << "globalVar (before any function) = " << globalVar << endl;
    cout << endl;

    cout << "=== Local Variables and Function Scope ===" << endl;
    demonstrateScope();
    cout << "globalVar (after demonstrateScope) = " << globalVar << endl;
    cout << "counter = " << counter << endl;
    cout << endl;

    cout << "=== Parameter Scope ===" << endl;
    int myValue = 42;
    cout << "myValue before function call = " << myValue << endl;
    showParameterScope(myValue);
    cout << "myValue after function call  = " << myValue << endl;
    cout << "→ myValue unchanged (pass by value creates local copy)" << endl;
    cout << endl;

    cout << "=== Block Scope ===" << endl;
    blockScope();
    cout << endl;

    cout << "=== Loop Variable Scope ===" << endl;
    loopScope();
    cout << endl;

    // Local variable in main — only accessible inside main
    int mainLocal = 77;
    cout << "=== Local Variable in main ===" << endl;
    cout << "mainLocal = " << mainLocal << " (only accessible in main)" << endl;

    return 0;
}

/*
    Time Complexity:  O(1) — constant time operations
    Space Complexity: O(1) — fixed number of variables, no dynamic allocation
*/
