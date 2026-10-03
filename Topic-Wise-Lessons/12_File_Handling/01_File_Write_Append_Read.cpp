#include <bits/stdc++.h>
using namespace std;

int main() {
    /* ✍️ ios::trunc : erase old content, then write */
    ofstream outfile("My.txt", ios::trunc);
    outfile << "I Love :- " << endl;
    outfile << "Dynamic Programming and Recursion." << endl;
    outfile.close();

    /* ➕ ios::app : keep old content, add at the END */
    ofstream appendfile("My.txt", ios::app);
    appendfile << "And Competitive Programming As well" << endl;
    appendfile.close();

    /* 📖 Read the whole file line by line */
    ifstream infile("My.txt");
    if (!infile) {
        cout << "File Cannot be opened";
        return 0;
    }
    string line;
    while (getline(infile, line)) {
        cout << line << endl;
    }
    infile.close();
    return 0;
}

/*
Output:
I Love :-
Dynamic Programming and Recursion.
And Competitive Programming As well
*/
