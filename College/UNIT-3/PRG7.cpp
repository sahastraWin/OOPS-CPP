// PROGRAM TO IMPLEMENT AGGREGATION
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
public:
    Engine engine; // Aggregation: car has an engine
};
int main()
{
    Car myCar;
    myCar.engine.start();
    return 0;
}