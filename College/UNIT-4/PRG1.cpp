// POLYMORPHISM: compile-time
#include <iostream>
using namespace std;

class Print
{
public:
    void show(int i)
    {
        cout << "Integer : " << i << endl;
    }
    void show(double i)
    {
        cout << "Double  : " << i << endl;
    }
    void show(const ::string &str)
    /*
    The display(const ::string &str) method allows you to pass a string (from the global string type, which is uncommon) to the function,
    where it will be printed, but it will not be modified.
    */
    {
        cout << "String  : " << str << endl;
    }
};
int main()
{
    Print obj;
    obj.show(5);
    obj.show(5.1);
    obj.show("Hello");
    return 0;
}
