#include <iostream>
using namespace std;

/* IMPORTANT:
   - Without 'virtual', Class D would get TWO copies of Class A.
   - 'virtual inheritance' ensures only one shared instance of A exists.
*/
class A
{
public:
    int data = 10;
};

class B : virtual public A
{
}; // Virtual inheritance
class C : virtual public A
{
}; // Virtual inheritance

class D : public B, public C
{
public:
    void show()
    {
        // Without 'virtual', this would be ambiguous: which 'data'?
        cout << "Value of data: " << data << endl;
    }
};

int main()
{
    D obj;
    obj.show();
    return 0;
}