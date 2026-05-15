#include <iostream>
using namespace std;

/* IMPORTANT:
   1. Destructor: To free allocated memory.
   2. Copy Constructor: To create a new memory block for the copy.
   3. Copy Assignment Operator: To handle 'obj1 = obj2' safely.
*/
class Box
{
    int *data;

public:
    Box(int val)
    {
        data = new int(val);
    }

    // 1. Destructor
    ~Box() { delete data; }

    // 2. Copy Constructor (Deep Copy)
    Box(const Box &other)
    {
        data = new int(*other.data);
    }

    // 3. Copy Assignment Operator
    Box &operator=(const Box &other)
    {
        if (this != &other)
        {
            delete data; // Free old memory
            data = new int(*other.data);
        }
        return *this;
    }

    void display() { cout << "Value: " << *data << endl; }
};

int main()
{
    Box b1(50);
    Box b2 = b1; // Calls Copy Constructor
    b2.display();
    return 0;
}