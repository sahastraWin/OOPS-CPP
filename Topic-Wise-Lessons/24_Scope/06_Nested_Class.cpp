#include <bits/stdc++.h>
using namespace std;

class Outside {
public:
    int x;
    class Inside {                  // class inside a class
    public:
        int x;
        static int y;
        int foo() { return x + y; }
    };
};

int Outside::Inside::y = 5;         // define the nested static member

int main() {
    Outside A;
    Outside::Inside B;              // use :: to reach the nested class
    A.x = 1;
    B.x = 2;
    cout << "Outside x = " << A.x << endl;
    cout << "Inside x = " << B.x << endl;
    cout << "Inside::y = " << Outside::Inside::y << endl;
    cout << "foo() = " << B.foo() << endl;
    return 0;
}

/*
Output:
Outside x = 1
Inside x = 2
Inside::y = 5
foo() = 7
*/
