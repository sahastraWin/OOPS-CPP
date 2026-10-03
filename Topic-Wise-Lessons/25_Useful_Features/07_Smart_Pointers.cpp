#include <bits/stdc++.h>
using namespace std;

class Rectangle {
private:
    int Length, Breadth;
public:
    Rectangle(int l, int b) { Length = l; Breadth = b; }
    int Area() { return Length * Breadth; }
};

int main() {
    /* 🔹 unique_ptr: ONE owner only, deletes the object automatically */
    cout << "--- unique_ptr ---" << endl;
    unique_ptr<Rectangle> ptr1(new Rectangle(10, 5));
    cout << ptr1->Area() << endl;

    unique_ptr<Rectangle> ptr2;
    ptr2 = move(ptr1);                           // ownership moves; ptr1 becomes empty
    if (ptr1 == nullptr)
        cout << "ptr1 is empty now" << endl;
    cout << ptr2->Area() << endl;

    /* 🔹 shared_ptr: MANY owners, a reference counter tracks them */
    cout << "--- shared_ptr ---" << endl;
    shared_ptr<Rectangle> sp1(new Rectangle(10, 5));
    shared_ptr<Rectangle> sp2 = sp1;             // both point to the same object
    cout << "sp1 area " << sp1->Area() << endl;
    cout << "sp2 area " << sp2->Area() << endl;
    cout << "use_count = " << sp1.use_count() << endl;
    sp2.reset();                                 // sp2 lets go
    cout << "use_count = " << sp1.use_count() << endl;
    return 0;                                    // memory freed automatically, no delete needed
}

/*
Output:
--- unique_ptr ---
50
ptr1 is empty now
50
--- shared_ptr ---
sp1 area 50
sp2 area 50
use_count = 2
use_count = 1
*/
