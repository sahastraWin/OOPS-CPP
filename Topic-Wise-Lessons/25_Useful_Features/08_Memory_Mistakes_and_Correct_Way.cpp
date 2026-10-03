#include <bits/stdc++.h>
using namespace std;

class Rectangle {
private:
    int Length, Breadth;
public:
    Rectangle(int l, int b) { Length = l; Breadth = b; }
    int Area() { return Length * Breadth; }
};

/* ✅ Correct: every new has a matching delete, so no memory leak */
int Fun(int l, int b) {
    Rectangle *p = new Rectangle(l, b);
    int area = p->Area();
    delete p;
    return area;
}

int main() {
    /* Calling Fun() many times is safe because it frees its memory each time.
       (If delete p were missing, a long while(1) loop would eat all your RAM.) */
    for (int i = 0; i < 3; i++) {
        cout << "Result: " << Fun(10, 20) << endl;
    }

    /* ✅ Safe pointer handling */
    int *ptr1 = new int(10);
    int *ptr2 = ptr1;                            // both point to the same memory
    delete ptr2;                                 // single object -> plain delete
    ptr1 = nullptr;                              // never use a pointer after delete
    ptr2 = nullptr;
    if (ptr1 == nullptr)
        cout << "Pointers reset safely" << endl;
    return 0;
}

/*
❌ Common mistakes:
1) delete[] on memory from  new int(10)   -> new pairs with delete, new[] with delete[]
2) cout << *ptr1; after the memory was deleted -> "dangling pointer" (undefined behaviour)
3) Forgetting delete -> memory leak
💡 Best fix: use smart pointers (Topic 50).

Output:
Result: 200
Result: 200
Result: 200
Pointers reset safely
*/
