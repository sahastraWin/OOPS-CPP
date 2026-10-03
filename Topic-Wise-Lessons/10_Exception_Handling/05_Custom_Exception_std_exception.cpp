#include <bits/stdc++.h>
using namespace std;

class MyException : public exception {
public:
    /* what() is the standard way to describe the error */
    const char* what() const noexcept override {
        return "My Custom Exception";
    }
};

int Division(int a, int b) {
    if (b == 0) throw 1;
    if (b == 1) throw MyException();
    return a / b;
}

int main() {
    int tests[] = {5, 1, 0};

    for (int y : tests) {
        try {
            int z = Division(10, y);             // compute FIRST, print AFTER
            cout << "10 / " << y << " = " << z << endl;
        }
        catch (int x) {
            cout << "Division By Zero Error" << endl;
        }
        catch (MyException &ME) {
            cout << "Division By One Error" << endl;
            cout << ME.what() << endl;
        }
    }
    cout << "End of the Program" << endl;
    return 0;
}

/*
📝 Old style  int f() throw(int)  (exception specifications) was REMOVED in C++17.
Do not write it in new code.

Output:
10 / 5 = 2
Division By One Error
My Custom Exception
Division By Zero Error
End of the Program
*/
