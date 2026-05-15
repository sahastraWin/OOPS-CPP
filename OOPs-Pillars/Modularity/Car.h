#ifndef CAR_H
#define CAR_H

#include "Engine.h" // Including the Engine module
#include <string>

class ModularCar
{
private:
    string brand;
    Engine engine; // Composition: Car "has-a" module

public:
    ModularCar(string b) : brand(b) {}

    void startCar()
    {
        engine.start();
        cout << brand << " is ready to drive!" << endl;
    }

    void stopCar()
    {
        engine.stop();
        cout << brand << " is shut down." << endl;
    }
};

#endif