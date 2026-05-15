// Program to calculate the area of rectangle, square and circle using constructor overloading that accepts input from the user and then shows the desired result.
#include <iostream>
#include <cmath>
using namespace std;
class Shape
{
public:
    double area;

    // constructor for rectangle:
    Shape(double l, double w)
    {
        area = l * w;
    }

    // constructor for square:
    Shape(double s)
    {
        area = s * s;
    }

    // constructor for circle:
    Shape(double radius, bool isCircle)
    {
        if (isCircle)
            area = M_PI * radius * radius;
    }
    void display()
    {
        cout << "Area :" << area << " units " << endl;
        }
};
int main()
{
    double l, w, radius, s;
    int choice;
    cout << "Calculate the area of \n";
    cout << "1. Rectangle \n"
         << "2. Square\n"
         << "3. Circle\n";
    cout << "Enter your choice\n";
    cin >> choice;

    if (choice == 1)
    {
        cout << "Enter length and width\n";
        cin >> l >> w;
        Shape rectangle(l, w);
        rectangle.display();
    }
    else if (choice == 2)
    {
        cout << "Enter side\n";
        cin >> s;
        Shape square(s);
        square.display();
    }
    else if (choice == 3)
    {
        cout << "Enter radius\n";
        cin >> radius;
        Shape circle(radius, true);
        circle.display();
    }
    else
    {
        cout << "Invalid Choice";
    }
    return 0;
}