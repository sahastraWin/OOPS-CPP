// EXCEPTION HANDLING :
#include <iostream>
#include <stdexcept> // For runtime_error
using namespace std;

int main()
{
    try
    {
        int num = 10;
        int den = 0;
        int res;

        if (den == 0)
        {
            throw runtime_error("Division by zero not allowed");
        }

        res = num / den; // This line will not be executed due to the exception above
        cout << res;
    }
    catch (const exception &e) // Catch exception by reference
    {
        cout << e.what(); // Print the error message
    }
    return 0;
}
