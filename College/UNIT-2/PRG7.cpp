// Program to implement class and object
#include <iostream>
using namespace std;
class Car
{
private:
    string model;
    int year;

public:
    Car(string m, int y) : model(m), year(y) {}

    void displayDetails()
    {
        cout << "Model     : " << model << endl;
        ;
        cout << "Year      : " << year;
    }
};
int main()
{
    Car myCar("Toyota", 2005);
    myCar.displayDetails();
    return 0;
}