#include <bits/stdc++.h>
using namespace std;

class Test {
public:
    Test() { cout << "   Test Created" << endl; }
    ~Test() { cout << "   Test Destroyed" << endl; }
};

void fun() {
    Test t;                                      // local object
    cout << "   Inside fun()" << endl;
}                                                // destroyed automatically here

int main() {
    cout << "1) Local object in a function:" << endl;
    fun();

    cout << "2) Heap object (new / delete):" << endl;
    Test *obj = new Test();
    delete obj;                                  // YOU must call delete

    cout << "3) Object inside a block:" << endl;
    {
        Test b;
    }                                            // destroyed at the closing brace
    return 0;
}

/*
Output:
1) Local object in a function:
   Test Created
   Inside fun()
   Test Destroyed
2) Heap object (new / delete):
   Test Created
   Test Destroyed
3) Object inside a block:
   Test Created
   Test Destroyed
*/
