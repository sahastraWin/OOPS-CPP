#include <bits/stdc++.h>
using namespace std;

class Rectangle {
private:
    int length, breadth;
public:
    Rectangle() { length = 1; breadth = 1; }
    Rectangle(int l, int b) { length = l; breadth = b; }
    int getLength() { return length; }
    int getBreadth() { return breadth; }
    void setLength(int l) { length = l; }
    void setBreadth(int b) { breadth = b; }
    int area() { return length * breadth; }
    int perimeter() { return 2 * (length + breadth); }
    bool isSquare() { return length == breadth; }
    ~Rectangle() { cout << "Rectangle Destroyed" << endl; }
};

class Cuboid : public Rectangle {        // Cuboid IS-A Rectangle with height
private:
    int height;
public:
    Cuboid(int h) { height = h; }
    int getHeight() { return height; }
    void setHeight(int h) { height = h; }
    int volume() {
        /* length and breadth are private in Rectangle,
           so we use the public getters. */
        return getLength() * getBreadth() * height;
    }
};

int main() {
    Cuboid c(5);
    c.setLength(10);
    c.setBreadth(7);
    cout << "Volume is " << c.volume() << endl;
    return 0;
}

/*
Output:
Volume is 350
Rectangle Destroyed
*/
