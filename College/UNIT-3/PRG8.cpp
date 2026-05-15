// PROGRAM TO IMPLEMENT COMPOSITION
#include <iostream>
using namespace std;
class Engine
{
public:
    void start()
    {
        cout << "Engine has started\n";
    }
};
class Car
{
private:
    Engine engine; // Composition: car owns the engine
public:
    void startCar()
    {
        engine.start(); // using the engine object within the car object
        cout << "Car has started\n";
    }
};
int main()
{
    Car myCar;
    myCar.startCar(); // starting the car which internally starts the engine
    return 0;
}