#include <iostream>
using namespace std;

/* IMPORTANT:
   - Shape is an Abstract Class because it has a Pure Virtual Function.
   - You cannot create an object of Shape: Shape s; // This would throw an error.
   - Derived classes MUST implement draw() to be instantiable.
*/
class Shape
{
public:
    virtual void draw() = 0; // Pure Virtual Function

    void commonFunction()
    {
        cout << "Calculating area for: " << endl;
    }
};

class Circle : public Shape
{
public:
    void draw() override
    {
        cout << "Drawing a Circle ◯" << endl;
    }
};

int main()
{
    Circle c;
    c.commonFunction();
    c.draw();
    return 0;
}