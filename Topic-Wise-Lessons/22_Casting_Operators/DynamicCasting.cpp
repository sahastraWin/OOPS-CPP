#include <iostream>
using namespace std;

/* IMPORTANT:
   - dynamic_cast only works with polymorphic classes (must have a virtual function).
   - It returns NULL if the cast is invalid, preventing crashes.
*/
class Base
{
    virtual void func() {} // Makes class polymorphic
};

class Derived : public Base
{
public:
    void derivedOnly() { cout << "Accessing Derived logic!" << endl; }
};

int main()
{
    Base *bp = new Derived();
    Base *bp2 = new Base();

    // Successful cast
    Derived *dp = dynamic_cast<Derived *>(bp);
    if (dp)
        dp->derivedOnly();

    // Failed cast
    Derived *dp2 = dynamic_cast<Derived *>(bp2);
    if (dp2 == NULL)
        cout << "Safe: Cast failed for incompatible type." << endl;

    delete bp;
    delete bp2;
    return 0;
}