// WRITE A PROGRAM TO IMPLEMENT CLASS AND OBJECT
#include <iostream>
using namespace std;

// defining a class named 'Car'
class Car
{
private:
    string model;
    int year;

public:
    // constructor to intialize object
    Car(string m, int y) : model(m), year(y) {}
    /*
    {
        model = m;
        year = y;
    }
        */
    // member function to display the car details
    void displayDetails()
    {
        cout << "Model : " << model << endl;
        cout << "Year  : " << year << endl;
    }
};

int main()
{

    // creating an object of the 'Car' class
    Car myCar("Toyota", 2005);

    // calling the member function using the object 'myCar'
    myCar.displayDetails();
    return 0;
}

