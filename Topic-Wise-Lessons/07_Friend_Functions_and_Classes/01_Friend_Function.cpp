#include <bits/stdc++.h>
using namespace std;

class Test {
private:
    int x;
protected:
    int y;
public:
    int z;
    friend void Fun();              // Fun() is allowed to touch private/protected data
};

void Fun() {
    Test t;
    t.x = 10;                       // private: allowed only because of friend
    t.y = 20;                       // protected: allowed
    t.z = 30;
    cout << "X : " << t.x << endl;
    cout << "Y : " << t.y << endl;
    cout << "Z : " << t.z << endl;
}

int main() {
    Fun();
    return 0;
}

/*
Output:
X : 10
Y : 20
Z : 30
*/
