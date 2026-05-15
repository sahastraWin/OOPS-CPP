#include <iostream>
#include <string>
using namespace std;

/* IMPORTANT:
   - Composition ("Has-a"): The Car HAS an Engine.
   - Decouples classes: You can change the Engine without breaking the Car's hierarchy.
*/
class Engine
{
public:
    void start() { cout << "Engine vrooming..." << endl; }
};

class Car
{
private:
    Engine e; // Composition
    string model;

public:
    Car(string m) : model(m) {}
    void startCar()
    {
        cout << model << " is ready." << endl;
        e.start();
    }
};

int main()
{
    Car myCar("Tesla");
    myCar.startCar();
    return 0;
}