/*
 * ======================================================================================
 * DIFFERENCE BETWEEN CLASS, STRUCT, AND UNION
 * ======================================================================================
 *
 * 1. CLASS:
 *    - Members are PRIVATE by default.
 *    - Used primarily for Encapsulation (Object-Oriented Programming).
 *    - Each member has its own dedicated memory location.
 *
 * 2. STRUCT:
 *    - Members are PUBLIC by default.
 *    - Historically used for plain data grouping (POD - Plain Old Data),
 *      though in C++, they can have methods and constructors just like classes.
 *    - Each member has its own dedicated memory location.
 *
 * 3. UNION:
 *    - Members are PUBLIC by default.
 *    - All members SHARE the same memory location.
 *    - The size of the union is the size of its largest member.
 *    - You can only store one value at a time; modifying one member overwrites others.
 * ======================================================================================
 */

#include <iostream>

// CLASS example
class Player
{
    int id; // Private by default
public:
    int level;
};

// STRUCT example
struct Point
{
    int x; // Public by default
    int y;
};

// UNION example
union Data
{
    int integer;    // 4 bytes
    char character; // 1 byte
    float decimal;  // 4 bytes
    // Total size will be 4 bytes (size of largest member)
};

int main()
{
    /*
     * --- CLASS & STRUCT BEHAVIOR ---
     * Both allocate memory for all members simultaneously.
     */
    Point p = {10, 20};

    using namespace std; // Using directive used here only to avoid prefixing

    cout << "--- Struct / Class ---" << endl;
    cout << "Point X: " << p.x << ", Y: " << p.y << endl;
    cout << "Size of Point struct: " << sizeof(p) << " bytes" << endl
         << endl;

    /*
     * --- UNION BEHAVIOR ---
     * Changing 'decimal' will corrupt 'integer' because they overlap in memory.
     */
    Data d;
    cout << "--- Union ---" << endl;
    cout << "Size of Data union: " << sizeof(d) << " bytes" << endl;

    d.integer = 65;
    cout << "Stored 65 in d.integer." << endl;
    cout << "d.integer: " << d.integer << endl;
    cout << "d.character (interpreted 65 as ASCII): " << d.character << endl;

    d.decimal = 10.5f;
    cout << "Stored 10.5 in d.decimal." << endl;
    cout << "d.decimal: " << d.decimal << endl;
    cout << "d.integer (now corrupted/overwritten): " << d.integer << endl;

    return 0;
}