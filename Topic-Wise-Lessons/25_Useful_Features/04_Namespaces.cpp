#include <bits/stdc++.h>
using namespace std;

namespace First {
    void fun() { cout << "First" << endl; }
}
namespace Second {
    void fun() { cout << "Second" << endl; }
}

int main() {
    First::fun();                    // always works: name the namespace
    Second::fun();

    {
        using namespace First;       // inside THIS block only
        fun();                       // now fun() means First::fun()
        Second::fun();               // other namespaces still need ::
    }
    return 0;
}

/*
Output:
First
Second
First
Second
*/
