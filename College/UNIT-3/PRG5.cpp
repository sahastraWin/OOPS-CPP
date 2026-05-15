// WRITE A PROGRAM TO IMPLEMENT OF ABSTRACT CLASSES

#include <iostream>
using namespace std;

// abstract base class
class Shape
{
public:
    // pure virtual function

    virtual void draw() = 0; // making this class abstract

    // a regular function
    void display()
    {
        cout << "Displaying the shape" << endl;
    }
};

// derived class 1
class Circle : public Shape
{
public:
    // implementing the pure virtual from shape
    void draw() override
    {
        cout << "Drawing a Circle" << endl;
    }
};

// derived class 2
class Rectangle : public Shape
{
public:
    // implementing the pure virtual from shape
    void draw() override
    {
        cout << "Drawing a Rectangle" << endl;
    }
};
int main()
{
    // Shape shape ; //this will give a compile time error because Shape is abstract

    // creating objects of derived classes
    Circle circle;
    Rectangle rectangle;

    // using polymorphism to call the draw function
    Shape *shapePtr; // pointer to shape class

    shapePtr = &circle;
    shapePtr->draw();

    shapePtr = &rectangle;
    shapePtr->draw();

    return 0;
}