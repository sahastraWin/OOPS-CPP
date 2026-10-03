#include <bits/stdc++.h>
using namespace std;

class My {
private:
    int x;
protected:
    int y;
public:
    int z;
    friend class Your;              // every member of Your can access My's private data
};

class Your {
public:
    My m;
    void Fun() {
        m.x = 10;
        m.y = 20;
        m.z = 30;
        cout << "X = " << m.x << endl;
        cout << "Y = " << m.y << endl;
        cout << "Z = " << m.z << endl;
    }
};

int main() {
    Your obj;
    obj.Fun();
    return 0;
}

/*
Output:
X = 10
Y = 20
Z = 30
*/
