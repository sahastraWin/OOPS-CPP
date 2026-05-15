/*
    QUESTION:
    Write a C++ program demonstrating a class with ALL PUBLIC members.
    Create a class 'Person' with public data members: name (string) and number (int).
    Read values directly from the user into the object's public members.
    Input: Name and number
    Output: "<name>: <number>"
*/

#include <bits/stdc++.h>
using namespace std;

class Person
{
public:
    string name;
    int number;
};

int main()
{
    Person obj;

    cout << "Enter the Name: ";
    cin >> obj.name;

    cout << "Enter the Number: ";
    cin >> obj.number;

    cout << obj.name << ": " << obj.number << endl;

    return 0;
}

/*
    INTUITION:
    - When members are PUBLIC, they can be directly accessed using the dot (.)
      operator from outside the class: obj.name, obj.number.
    - This is the simplest form of a class — essentially a struct with a class keyword.
    - In C++, struct members are public by default; class members are private by default.
    - Public access trades encapsulation for simplicity — fine for plain data holders.
    - Real-world: this pattern is used for simple data transfer objects (DTOs)
      where the class is just a container for grouped data.
    - No constructor needed here — the default constructor (auto-generated) handles
      object creation, and we assign values later via direct member access.

    TIME COMPLEXITY:  O(1) — read and print are constant time operations.
    SPACE COMPLEXITY: O(n) — where n = length of the name string.
*/
