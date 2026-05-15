// Program to implement how an object can be returned from a function
#include <iostream>
using namespace std;
class Point
{
private:
    int x, y;

public:
    // constructor to intialize the points
    Point(int a, int b) : x(a), y(b) {}
    // function to display the points coordinates
    void display()
    {
        cout << "Point (" << x << " , " << y << ")" << endl;
    }
    Point move(int dx, int dy)
    {
        return Point(x + dx, y + dy); // create and return new object
    }
};
int main()
{
    // Create a point object by value from the move function
    Point p1(2, 3);
    // Display the inital point
    cout << "Initial Point :\n";
    p1.display();

    // return a new point object by value from the move() function
    Point p2 = p1.move(5, -2);
    // Display the moved point
    cout << "Moved point :\n";
    p2.display();
    return 0;
}