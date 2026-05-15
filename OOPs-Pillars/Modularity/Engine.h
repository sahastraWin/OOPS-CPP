#ifndef ENGINE_H
#define ENGINE_H

#include <iostream>
using namespace std;

class Engine
{
private:
    bool isRunning;

public:
    Engine() : isRunning(false) {}

    void start()
    {
        if (!isRunning)
        {
            isRunning = true;
            cout << "Engine: Ignition system engaged." << endl;
        }
    }

    void stop()
    {
        if (isRunning)
        {
            isRunning = false;
            cout << "Engine: Fuel supply cut." << endl;
        }
    }

    bool getStatus() { return isRunning; }
};

#endif