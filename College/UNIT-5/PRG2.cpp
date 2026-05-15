// WAP  to read three numbers x,y and z to evaluate R given by R=z/(x-y)
#include <iostream>
#include <stdexcept>
using namespace std;
int main()
{
    try
    {
        int x, y, z, R;
        cout << "Enter the value of x\n";
        cin >> x;
        cout << "Enter the value of y\n";
        cin >> y;
        cout << "Enter the value of z\n";
        cin >> z;
        if ((x - y) == 0)
        {
            throw runtime_error("Divison by zero not allowed");
        }
        R = z / (x - y);
        cout << "Result : " << R;
    }
    catch (const exception &e)
    {
        cout << e.what();
    }
    return 0;
}