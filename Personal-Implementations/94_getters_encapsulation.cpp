/*
    QUESTION:
    Write a C++ program demonstrating a class with GETTER METHODS for ENCAPSULATION.
    Create class 'Point' with private coordinates x and y.
    Use a parameterized constructor to set the values.
    Use getX() and getY() getter methods to access private data from outside.
    Input: Hardcoded point (10, 15)
    Output: x and y coordinates via getters
*/

#include <bits/stdc++.h>
using namespace std;

class Point
{
    int x, y;

public:
    Point(int x1, int y1)
    {
        x = x1;
        y = y1;
    }

    int getX() { return x; }
    int getY() { return y; }
};

int main()
{
    Point p(10, 15);
    cout << "x = " << p.getX() << endl;
    cout << "y = " << p.getY() << endl;

    return 0;
}

/*
    INTUITION:
    - ENCAPSULATION with GETTERS: private data cannot be accessed directly,
      but public getter methods provide READ-ONLY access.
    - p.x would be a compile error (x is private).
    - p.getX() works (getX is public), returns the value of x.
    - WHY use getters instead of public members?
        1. CONTROL: You can add validation, logging, or computation in a getter.
        2. READ-ONLY: Expose data for reading without allowing modification.
        3. FUTURE-PROOFING: Change internal representation without breaking interface.
    - The parameterized constructor initializes x and y in one step at object creation.
    - In modern C++, prefer initialization list: Point(int x1, int y1) : x(x1), y(y1) {}

    TIME COMPLEXITY:  O(1) — constructor and getters are constant time.
    SPACE COMPLEXITY: O(1) — two int members.
*/
