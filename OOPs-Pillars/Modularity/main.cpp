#include <iostream>
#include <string>

using namespace std;

/*
Modularity -->
1. Modularity means breaking down a large program into smaller, independent, and manageable modules.
2. Each module handles one specific functionality, making the code easier to maintain, test, and debug.
3. Modules can be developed, modified, and reused independently without affecting other parts of the program.

4. In real-world terms, think of a company where different departments (HR, Sales, Development, Accounts)
   work on their own tasks. Each department is independent but together they form the complete organization.
5. In programming, we can achieve modularity by dividing the code into separate classes/functions
   based on responsibilities.
6. The main function then acts as the "manager" that uses all the modules together to perform the overall task.
*/

/*
Module 1: EngineModule
Handles all operations related to the car's engine.
*/
class EngineModule
{
private:
    bool isEngineOn;

public:
    EngineModule() : isEngineOn(false) {}

    void startEngine()
    {
        isEngineOn = true;
        cout << "[Engine Module] Engine started successfully!" << endl;
    }

    void stopEngine()
    {
        isEngineOn = false;
        cout << "[Engine Module] Engine stopped successfully!" << endl;
    }

    bool engineStatus() const
    {
        return isEngineOn;
    }
};

/*
Module 2: GearModule
Handles gear shifting operations.
*/
class GearModule
{
private:
    int currentGear;

public:
    GearModule() : currentGear(0) {}

    void shiftGear(int gear)
    {
        currentGear = gear;
        cout << "[Gear Module] Shifted to gear " << currentGear << endl;
    }

    int getCurrentGear() const
    {
        return currentGear;
    }
};

/*
Module 3: SpeedModule
Handles acceleration and braking.
*/
class SpeedModule
{
private:
    int currentSpeed;

public:
    SpeedModule() : currentSpeed(0) {}

    void accelerate()
    {
        currentSpeed += 20;
        cout << "[Speed Module] Accelerated to " << currentSpeed << " km/h" << endl;
    }

    void brake()
    {
        currentSpeed -= 20;
        if (currentSpeed < 0)
            currentSpeed = 0;
        cout << "[Speed Module] Braked to " << currentSpeed << " km/h" << endl;
    }

    int getCurrentSpeed() const
    {
        return currentSpeed;
    }
};

/*
Main CarSystem:
1. Uses EngineModule, GearModule, and SpeedModule together.
2. Demonstrates modularity where each module has its own responsibility.
*/
class CarSystem
{
private:
    EngineModule engine;
    GearModule gear;
    SpeedModule speed;

public:
    void startCar()
    {
        engine.startEngine();
    }

    void shiftCarGear(int g)
    {
        if (!engine.engineStatus())
        {
            cout << "[Car System] Cannot shift gear. Engine is OFF." << endl;
            return;
        }
        gear.shiftGear(g);
    }

    void accelerateCar()
    {
        if (!engine.engineStatus())
        {
            cout << "[Car System] Cannot accelerate. Engine is OFF." << endl;
            return;
        }
        speed.accelerate();
    }

    void brakeCar()
    {
        speed.brake();
    }

    void stopCar()
    {
        engine.stopEngine();
    }
};

// Main Function
int main()
{
    /*
    This main function demonstrates modularity:
    - Each module (EngineModule, GearModule, SpeedModule) handles its own job.
    - CarSystem uses these modules to operate the complete car.
    - If we need to change how acceleration works, we only modify SpeedModule,
      not the entire program.
    */
    CarSystem myCar;

    myCar.startCar();
    myCar.shiftCarGear(1);
    myCar.accelerateCar();
    myCar.shiftCarGear(2);
    myCar.accelerateCar();
    myCar.brakeCar();
    myCar.stopCar();

    return 0;
}
#include "Car.h"

int main()
{
    ModularCar myCar("Tesla");

    myCar.startCar();
    myCar.stopCar();

    return 0;
}