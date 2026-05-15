// PROGRAM TO DEMONSTRATE STATIC AND DYNAMIC VARIABLES
#include <iostream>
using namespace std;

int main()
{
    // static object
    int staticVar;
    cout << "Static variable address\n";
    cout << &staticVar << "\n";
    int *dynamicVar = new int;
    cout << "Dynamic variable address\n";
    cout << dynamicVar;
    return 0;
}