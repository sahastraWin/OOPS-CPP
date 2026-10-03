#include <bits/stdc++.h>
using namespace std;

class Student {
public:
    string name;
    int rollno;
    string branch;

    Student() {}                                 // default constructor is REQUIRED for loading
    Student(string n, int r, string b) {
        name = n;
        rollno = r;
        branch = b;
    }
    friend ofstream& operator<<(ofstream &ofs, const Student &s);
    friend ifstream& operator>>(ifstream &ifs, Student &s);
};

/* 💾 Save: write each field on its own line */
ofstream& operator<<(ofstream &ofs, const Student &s) {
    ofs << s.name << endl;
    ofs << s.rollno << endl;
    ofs << s.branch << endl;
    return ofs;
}

/* 📥 Load: read the fields back in the SAME order */
ifstream& operator>>(ifstream &ifs, Student &s) {
    ifs >> s.name >> s.rollno >> s.branch;
    return ifs;
}

int main() {
    Student s1("Aman_Babu", 2019017, "CSE");

    ofstream ofs("Student.txt", ios::trunc);
    ofs << s1;                                   // serialize
    ofs.close();

    Student s2;
    ifstream ifs("Student.txt");
    ifs >> s2;                                   // deserialize
    ifs.close();

    cout << s2.name << endl << s2.rollno << endl << s2.branch << endl;
    return 0;
}

/*
Output:
Aman_Babu
2019017
CSE
*/
