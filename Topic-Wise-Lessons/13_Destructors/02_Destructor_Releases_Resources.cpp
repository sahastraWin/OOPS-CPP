#include <bits/stdc++.h>
using namespace std;

class Test {
private:
    int *p;
    ifstream fis;
public:
    Test() {
        p = new int[10];                         // acquire memory
        fis.open("my.txt");                      // acquire file
        cout << "Resources acquired" << endl;
    }
    ~Test() {
        delete[] p;                              // new[] pairs with delete[]
        fis.close();
        cout << "Resources released" << endl;
    }
};

int main() {
    Test t;
    return 0;
}

/*
🧠 Rule: whatever the constructor acquires, the destructor must release.

Output:
Resources acquired
Resources released
*/
