// Program to implement static data member and member functions
#include <iostream>
using namespace std;
class Counter
{
private:
    static int count; // static data member to keep track of count
public:
    Counter()
    {
        count++; // incrementing count each time when an object is created
    }
    static void displayCount()
    {
        cout << "Count :" << count << endl;
    }
};
int Counter::count = 0;
int main()
{
    Counter c1, c2, c3;
    Counter::displayCount();
    return 0;
}