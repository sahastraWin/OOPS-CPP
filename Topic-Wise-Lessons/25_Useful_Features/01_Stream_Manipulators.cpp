#include <bits/stdc++.h>
using namespace std;

int main() {
    cout << "Hex 163: " << hex << 163 << "\n";
    cout << "Oct 163: " << oct << 163 << "\n";
    cout << "Dec 163: " << dec << 163 << "\n";
    cout << "Fixed Manipulator: " << fixed << 162.6454 << endl;
    cout << "Scientific Manipulator: " << scientific << 162.6454 << "\n";
    cout << setw(10) << "World" << endl;    // right-align in a field of width 10
    return 0;
}

/*
Output (Linux / Mac):
Hex 163: a3
Oct 163: 243
Dec 163: 163
Fixed Manipulator: 162.645400
Scientific Manipulator: 1.626454e+02
     World
(Windows shows e+002 instead of e+02.)
*/
