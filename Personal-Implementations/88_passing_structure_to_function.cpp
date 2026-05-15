// 88. Program for passing structure to function
#include <bits/stdc++.h>
using namespace std;

struct address {
    string city;
    int pin;
    string phone;
};

struct employee {
    string name;
    address add;
};

void display(employee emp) {
    cout << "Printing the details....\n";
    cout << emp.name << " " << emp.add.city << " " << emp.add.pin << " " << emp.add.phone << "\n";
}

int main() {
    employee emp;
    
    cout << "Enter employee information?\n";
    cin >> emp.name >> emp.add.city >> emp.add.pin >> emp.add.phone;
    
    display(emp);
    return 0;
}
/*
TC: O(1) constant time
SC: O(1) constant space
*/
