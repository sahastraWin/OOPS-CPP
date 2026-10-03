#include <bits/stdc++.h>
using namespace std;

class Shape {                                    // ABSTRACT: has pure virtual functions
public:
    virtual float Area() = 0;                    // = 0 means "children MUST implement this"
    virtual float Perimeter() = 0;
    virtual ~Shape() {}
};

class Rectangle : public Shape {
private:
    float length, breadth;
public:
    Rectangle(float l = 1, float b = 1) {
        length = l;
        breadth = b;
    }
    float Area() override { return length * breadth; }
    float Perimeter() override { return 2 * (length + breadth); }
};

class Circle : public Shape {
private:
    float radius;
public:
    Circle(float r) { radius = r; }
    float Area() override { return 3.1425 * radius * radius; }
    float Perimeter() override { return 2 * 3.1425 * radius; }
};

int main() {
    /* Shape s;   ❌ ERROR: cannot create an object of an abstract class */
    Shape *s = new Rectangle(10, 5);
    cout << "Area of Rectangle " << s->Area() << endl;
    cout << "Perimeter of Rectangle " << s->Perimeter() << endl;
    delete s;

    s = new Circle(10);
    cout << "Area of Circle " << s->Area() << endl;
    cout << "Perimeter of Circle " << s->Perimeter() << endl;
    delete s;
    return 0;
}

/*
Output:
Area of Rectangle 50
Perimeter of Rectangle 30
Area of Circle 314.25
Perimeter of Circle 62.85
*/
