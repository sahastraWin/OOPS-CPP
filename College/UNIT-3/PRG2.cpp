// WRITE A PROGRAM TO IMPLEMENT MANY TO ONE ASSOCIATION
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// course class (one side)
class Course
{
public:
    string courseName;

    // constructor to intialize courseName
    Course(string name) : courseName(name) {}

    void display()
    {
        cout << "Course :" << courseName << endl;
    }
};

// student class(many side)
class Student
{
public:
    string studentName;
    Course *course; // pointer to the Course class(many students to one course)

    // constructor to intialize studentName and associated course
    Student(string name, Course *c) : studentName(name), course(c) {} // what  is this ???
    void display()
    {
        cout << "Student : " << studentName << " is enrolled in ";
        course->display(); 
    }
};
int main()
{
    // create a Course object
    Course course1("Computer Science");

    // create student objects associated with the course
    Student student1("Sahastrajeet", &course1); 
    Student student2("Vedraj", &course1);
    Student student3("Jeet", &course1);

    // Display students and their course
    student1.display();
    cout << endl;
    student2.display();
    cout << endl;
    student3.display();

    return 0;
}