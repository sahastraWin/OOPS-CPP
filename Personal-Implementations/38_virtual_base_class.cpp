/*
    QUESTION:
    Write a C++ program demonstrating VIRTUAL BASE CLASS to solve the Diamond Problem.
    Hierarchy:
        Student (base)
        Test : virtual public Student
        Sports : virtual public Student
        Result : public Test, public Sports
    Without 'virtual', Result would have TWO copies of Student.
    With 'virtual', Result has exactly ONE shared copy of Student.
    Input: Roll number, marks (2), sports score
    Output: Complete result with total
*/

#include <bits/stdc++.h>
using namespace std;

class Student
{
    int rno;

public:
    void getnumber()
    {
        cout << "Enter Roll No: ";
        cin >> rno;
    }
    void putnumber() { cout << "Roll No:  " << rno << endl; }
};

class Test : virtual public Student
{
public:
    int part1, part2;

    void getmarks()
    {
        cout << "Enter Marks 1 & 2: ";
        cin >> part1 >> part2;
    }
    void putmarks() { cout << "Marks:    " << part1 << ", " << part2 << endl; }
};

class Sports : public virtual Student
{
public:
    int score;

    void getscore()
    {
        cout << "Enter Sports Score: ";
        cin >> score;
    }
    void putscore() { cout << "Score:    " << score << endl; }
};

class Result : public Test, public Sports
{
    int total;

public:
    void display()
    {
        total = part1 + part2 + score;
        putnumber();
        putmarks();
        putscore();
        cout << "Total:    " << total << endl;
    }
};

int main()
{
    Result obj;
    obj.getnumber();
    obj.getmarks();
    obj.getscore();
    obj.display();
    return 0;
}

/*
    INTUITION:
    - DIAMOND PROBLEM: Without virtual, Result inherits Student TWICE:
        Once through Test, once through Sports → ambiguity and duplicate data.
    - VIRTUAL INHERITANCE: Adding 'virtual' to base class declaration ensures
        only ONE shared copy of Student exists in Result.
    - class Test : virtual public Student   → Test marks Student as virtual base.
    - class Sports : public virtual Student → Sports marks Student as virtual base.
    - Result inherits both, but shares ONE Student subobject.
    - Now rno, getnumber(), putnumber() exist only once — no ambiguity.
    - The MOST DERIVED class (Result) is responsible for calling the virtual
      base class constructor.

    TIME COMPLEXITY:  O(1) — input and arithmetic, constant time.
    SPACE COMPLEXITY: O(1) — fixed member variables, no dynamic allocation.
*/
