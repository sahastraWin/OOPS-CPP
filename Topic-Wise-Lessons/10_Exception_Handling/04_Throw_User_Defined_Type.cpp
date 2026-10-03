#include <bits/stdc++.h>
using namespace std;

class myExp {
    // empty class: its TYPE is the message
};

void check(int num) {
    try {
        if (num == 1) throw 1;
        else if (num == 2) throw myExp();        // throw an object
        else if (num == 3) throw "Unknown Exception";
        else cout << "Value " << num << endl;
    }
    catch (int ex) {
        cout << "Integer Exception" << endl;
    }
    catch (myExp &e) {
        cout << "myExp Exception" << endl;
    }
    catch (...) {
        cout << "Unknown Exception" << endl;
    }
}

int main() {
    for (int i = 1; i <= 4; i++) check(i);
    return 0;
}

/*
Output:
Integer Exception
myExp Exception
Unknown Exception
Value 4
*/
