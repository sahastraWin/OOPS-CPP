// Program to illustrate member and normal function and member function
#include <bits/stdc++.h>
using namespace std;
void greet(string name)
{
    cout << "Hello " << name << endl;
}
class Person
{
public:
    string name;
    // member function or method
    void introduce()
    {
        cout << "Hi my name is : " << name << endl;
    }
};

int main()
{
    // calling normal function
    greet("Sahastrajeet\n");

    // creating object
    Person p;
    p.name = "Jeet";
    // calling member using object
    p.introduce();
    return 0;
}
