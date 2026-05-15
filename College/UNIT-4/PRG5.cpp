// Program to calculate the area of rectangle, square and circle using constructor overloading that accepts input from the user and then shows the desired result.
#include <iostream>
#include <cmath>
using namespace std;

class Shape
{
public:
    double area;
    // constructor for rectangle:
    Shape(double length, double width)
    {
        area = length * width;
    }
    // constructor for square:

    Shape(double side)
    {
        area = side * side;
    }
    // constructor for circle:

    Shape(double radius, bool isCircle)
    {
        if (isCircle)
        {
            area = M_PI * radius * radius;
        }
    }

    // Function to display the result
    void displayArea()
    {
        cout << "Area : " << area << " units" << endl;
    }
};

int main()
{
    double length, width, radius, side;
    int choice;

    cout << "Calculate the area of :\n";
    cout << "1. Rectangle \n2. Square \n3. Circle \n4. Exit\n";
    cout << "Enter your choice\n";
    cin >> choice;

    if (choice == 1)
    {
        cout << "Enter the length and width" << endl;
        cin >> length >> width;
        Shape rectangle(length, width);
        rectangle.displayArea();
    }
    else if (choice == 2)
    {
        cout << "Enter the side" << endl;
        cin >> side;
        Shape square(side);
        square.displayArea();
    }

    else if (choice == 3)
    {
        cout << "Enter the radius" << endl;
        cin >> radius;
        Shape circle(radius, true);
        circle.displayArea();
    }
    else if (choice == 4)
    {
        exit(0);
    }
    else
    {
        cout << "INVLAID CHOICE  !! " << endl;
    }
    return 0;
}
