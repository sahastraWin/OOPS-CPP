#include <bits/stdc++.h>
using namespace std;

class Marker {
private:
    string color;
    string nature;
public:
    /* 🔹 Default constructor: takes no arguments */
    Marker() {
        color = "Red";
        nature = "Temporary";
    }

    /* 🔹 Parameterized constructor: takes values from the user */
    Marker(string color, string nature) {
        this->color = color;     // this-> separates member from parameter
        this->nature = nature;
    }

    /* 🔹 Copy constructor: builds a new object from an existing one */
    Marker(const Marker &m) {
        color = m.color;
        nature = m.nature;
    }

    /* 🔹 Accessor (getter): only READS private data */
    pair<string, string> getter() {
        return {color, nature};
    }

    /* 🔹 Mutator (setter): CHANGES private data */
    void setter(string c, string n) {
        color = c;
        nature = n;
    }
};

int main() {
    Marker m0;                                      // default
    Marker m1("Blue", "Temporary"), m2("Black", "Permanent");
    Marker m3(m2);                                  // copy of m2
    m3.setter("Green", "Permanent");                // change only m3

    cout << "Marker M0 - Color " << m0.getter().first << " Nature " << m0.getter().second << endl;
    cout << "Marker M1 - Color " << m1.getter().first << " Nature " << m1.getter().second << endl;
    cout << "Marker M2 - Color " << m2.getter().first << " Nature " << m2.getter().second << endl;
    cout << "Marker M3 - Color " << m3.getter().first << " Nature " << m3.getter().second << endl;
    return 0;
}

/*
⚠️ Ambiguity warning:
If you write BOTH   Marker()   AND   Marker(string c = "Red", string n = "Temporary")
then   Marker m;   gives the error: call of overloaded 'Marker()' is ambiguous.
Fix: keep only one of them.

Output:
Marker M0 - Color Red Nature Temporary
Marker M1 - Color Blue Nature Temporary
Marker M2 - Color Black Nature Permanent
Marker M3 - Color Green Nature Permanent
*/
