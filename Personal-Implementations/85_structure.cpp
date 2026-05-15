// 85. Program for structure in C++
#include <bits/stdc++.h>
using namespace std;

struct employee {
    string name;
    int empId;
    float salary;
};

int main() {
    employee emp = {"Mike", 1120, 76909.00f};
    
    cout << "\nName: " << emp.name << "\n";
    cout << "Id: " << emp.empId << "\n";
    cout << "Salary: " << emp.salary << "\n";
    
    return 0;
}
/*
TC: O(1) constant time
SC: O(1) constant space
*/
