// program to implement pure virtual function
#include <iostream>
using namespace std;
class Shape
{
public:
    virtual void draw() = 0;
    virtual void area()
    {
        cout << "Area of shape\n";
    }
};
class Rectangle : public Shape
{
public:
    void draw() override
    {
        cout << "Draw a rectangle\n";
    }
    void area() override
    {
        cout << "Area of rectangle\n";
    }
};
class Circle : public Shape
{
public:
    void draw() override
    {
        cout << "Draw a circle\n";
    }
    void area() override
    {
        cout << "Area of circle\n";
    }
};

int main()
{
    Shape *shape1 = new Rectangle();
    Shape *shape2 = new Circle();
    shape1->draw();
    shape1->area();
    shape2->draw();
    shape2->area();
    delete shape1;
    delete shape2;
    return 0;
}