// PROGRAM TO RESOLVE AMBIGUITY IN MULTIPLE INHERITANCE
#include <iostream>
using namespace std;
class Base1
{
public:
    void display()
    {
        cout << "Display from base1 class\n";
    }
};
class Base2
{
public:
    void display()
    {
        cout << "Display from base2 class";
    }
};
class Derived : public Base1, public Base2
{
public:
    void show()
    {
        Base1::display();
        Base2::display();
    }
};
int main()
{
    Derived obj;
    obj.show();
    return 0;
}