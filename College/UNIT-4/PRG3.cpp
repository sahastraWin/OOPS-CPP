// Program in C++ to overload + operator using member function to add two complex numbers
#include <iostream>
using namespace std;

class Complex
{
private:
    float real;
    float imag;

public:
    // constructor to intialize the complex number
    Complex(float r = 0, float i = 0) : real(r), imag(i) {}

    // overloading the + operator using a member function
    Complex operator+(const Complex &obj)
    {
        Complex temp;
        temp.real = real + obj.real;
        temp.imag = imag + obj.imag;
        return temp;
    }
    // function to display the complex number
    void display()
    {
        cout << real << "+" << imag << "i" << endl;
    }
};
int main()
{
    Complex c1(3.5, 2.5), c2(1.5, 4.5);
    Complex c3 = c1 + c2; // adding two complex numbers using overloaded operator
    c3.display();
    return 0;
}
