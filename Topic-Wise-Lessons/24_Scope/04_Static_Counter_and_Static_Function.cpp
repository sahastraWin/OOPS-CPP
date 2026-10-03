#include <bits/stdc++.h>
using namespace std;

class Test {
public:
    int a;
    static int count;               // ONE copy shared by all objects
    Test() {
        a = 10;
        count++;                    // every new object increases it
    }
    static int getCount() {         // static function: can use only static members
        return count;
    }
};

int Test::count = 0;

int main() {
    cout << "Calling count without object : " << Test::count << endl;
    cout << "Calling getCount without object : " << Test::getCount() << endl;

    Test t1;
    cout << "After t1 -> count : " << t1.count << endl;

    Test t2, t3;
    cout << "After t2 and t3 -> getCount : " << Test::getCount() << endl;
    return 0;
}

/*
Output:
Calling count without object : 0
Calling getCount without object : 0
After t1 -> count : 1
After t2 and t3 -> getCount : 3
*/
