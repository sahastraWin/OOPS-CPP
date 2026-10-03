#include <bits/stdc++.h>
using namespace std;

class Car {
public:
    virtual void Start() { cout << "Car Started" << endl; }
    virtual void Stop() { cout << "Car Stopped" << endl; }
    virtual ~Car() {}
};
class Innova : public Car {
public:
    void Start() override { cout << "Innova Started" << endl; }
    void Stop() override { cout << "Innova Stopped" << endl; }
};
class Swift : public Car {
public:
    void Start() override { cout << "Swift Started" << endl; }
    void Stop() override { cout << "Swift Stopped" << endl; }
};

int main() {
    Car *c = new Innova();
    c->Start();
    c->Stop();
    delete c;

    c = new Swift();                // same pointer, different object
    c->Start();
    c->Stop();
    delete c;
    return 0;
}

/*
🧠 Without 'virtual' in Car, all four lines would print "Car Started/Stopped".

Output:
Innova Started
Innova Stopped
Swift Started
Swift Stopped
*/
