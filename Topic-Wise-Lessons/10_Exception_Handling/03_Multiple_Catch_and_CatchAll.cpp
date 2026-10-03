#include <bits/stdc++.h>
using namespace std;

int main() {
    int arr[3] = {-1, 2, 5};

    for (int i = 0; i < 3; i++) {
        int num = arr[i];
        try {
            if (num == -1) throw 1;              // int
            else if (num == 2) throw 'a';        // char
            else throw "Generic";                // const char*
        }
        catch (int ex) {
            cout << "Integer Exception" << endl;
        }
        catch (char ex) {
            cout << "Character Exception" << endl;
        }
        catch (...) {                            // catches ANY other type
            cout << "Generic Exception" << endl;
        }
    }
    return 0;
}

/*
⚠️ catch(...) MUST be the LAST block. If you put it first, it swallows everything
and the blocks below it never run.

Output:
Integer Exception
Character Exception
Generic Exception
*/
