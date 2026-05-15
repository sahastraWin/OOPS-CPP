/*
    QUESTION:
    Write a C++ program demonstrating SINGLE INHERITANCE for salary calculation.
    Base class 'Emp' has: employee number, name, designation.
    Derived class 'Salary' inherits Emp and adds: basic pay, HRA, DA, PF.
    calculate() computes net pay = BP + HRA + DA - PF.
    display() shows the formatted result.
    Input: Employee details and salary components
    Output: Employee number, name, and net pay
*/

#include <bits/stdc++.h>
using namespace std;

class Emp
{
public:
    int eno;
    char name[30];
    char des[30];

    void get()
    {
        cout << "Enter Employee No, Name, Designation: ";
        cin >> eno >> name >> des;
    }
};

class Salary : public Emp
{
    float bp, hra, da, pf, np;

public:
    void get1()
    {
        cout << "Enter Basic Pay, HRA, DA, PF: ";
        cin >> bp >> hra >> da >> pf;
    }

    void calculate()
    {
        np = bp + hra + da - pf;
    }

    void display()
    {
        cout << "\nE_No\tName\t\tNet Pay" << endl;
        cout << eno << "\t" << name << "\t\t" << np << endl;
    }
};

int main()
{
    Salary s;
    s.get();
    s.get1();
    s.calculate();
    s.display();
    return 0;
}

/*
    INTUITION:
    - SINGLE INHERITANCE: Salary class inherits from ONE base class (Emp).
    - class Salary : public Emp → Salary gets ALL public/protected members of Emp.
    - 'public' inheritance preserves access levels: public remains public.
    - The derived class EXTENDS the base: Salary adds salary fields to Employee data.
    - IS-A relationship: A Salary object IS AN Emp object (plus more).
    - Calling s.get() works because Salary inherited get() from Emp.
    - calculate() can use bp, hra, da, pf (Salary's own members).
    - Separation: Emp handles identity data; Salary handles financial data.

    TIME COMPLEXITY:  O(1) — arithmetic operations, constant time.
    SPACE COMPLEXITY: O(1) — fixed number of member variables.
*/
