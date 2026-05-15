// VIRTUAL FUNCTION
#include <iostream>
using namespace std;

class Base
{
public:
    virtual void show()
    {
        cout << "Base class show function" << endl;
    }
    void display()
    {
        cout << "Base class display function" << endl;
    }
};

class Derived : public Base
{
public:
    void show() override
    {
        cout << "Dervied class show function" << endl;
    }
    void display()
    {
        cout << "Dervied class display function" << endl;
    }
};

int main()
{
    Base *basePtr;
    Derived derivedObj;
    basePtr = &derivedObj;
    basePtr->show();    // Calls Derived class's show function
    basePtr->display(); // Calls Base class's display function

    return 0;
}
