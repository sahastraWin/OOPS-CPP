// Program to implement abstraction
#include <bits/stdc++.h>
using namespace std;
class Shape
{
public:
    virtual void draw() = 0;
};
class Circle : public Shape
{
public:
    void draw()override
    {
        cout << "Drawing Circle\n";
    }
};

int main()
{

    Circle c;
    c.draw();
    return 0;
}
