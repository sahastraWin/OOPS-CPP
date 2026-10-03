#include <bits/stdc++.h>
using namespace std;

int main() {
    /* Prepare a file so this program runs on its own */
    ofstream out("my.txt");
    out << "Aman_Babu" << endl << 2019017 << endl << "CSE" << endl;
    out.close();

    ifstream ifs;
    ifs.open("my.txt");
    if (ifs.is_open())
        cout << "File is Opened" << endl;

    string name, branch;
    int roll;
    ifs >> name >> roll >> branch;               // >> stops at whitespace

    cout << "Name: " << name << endl;
    cout << "Roll: " << roll << endl;
    cout << "Branch: " << branch << endl;

    string extra;
    ifs >> extra;                                // try to read past the end
    if (ifs.eof())
        cout << "End of File Reached" << endl;

    ifs.close();
    return 0;
}

/*
🧠 eof() becomes true only AFTER a read attempt hits the end of the file.

Output:
File is Opened
Name: Aman_Babu
Roll: 2019017
Branch: CSE
End of File Reached
*/
