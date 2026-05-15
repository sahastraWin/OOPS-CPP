// WRITE A PROGRAM TO IMPLEMENT MULTIPLE INHERITANCE
#include <iostream>
using namespace std;

// base class 1;
class Engine
{
public:
    void startEngine()
    {
        cout << "Engine Started. " << endl;
    }
    void stopEngine()
    {
        cout << "Engine Stopped. " << endl;
    }
};

// base class 2
class Body
{
public:
    void designBody()
    {
        cout << "Body Designed. " << endl;
    }
    void paintBody()
    {
        cout << "Body Painted. " << endl;
    }
};

// derived class that inherits both from base Class1 nad base Class 2
class Car : public Engine, public Body
{
public:
    void carDetails()
    {
        cout << "Car is ready with Engine and Body designed. " << endl;
    }
};
int main()
{

    // Create an object of the derived class
    Car myCar;

    // Accessing methods from both base classes using the derived class object
    myCar.startEngine();
    myCar.designBody();
    myCar.paintBody();
    myCar.carDetails();
    myCar.stopEngine();

    return 0;
}
