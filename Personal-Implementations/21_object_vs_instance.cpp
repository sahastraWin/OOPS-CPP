/*
   Example demonstrating object size and
   the difference between class and object.
*/

#include <iostream>

using namespace std;
/*
   Updated to 'std' to resolve the error shown in
   Screenshot 2026-05-14 123009.png
*/

class Player
{
private:
    int health; // 4 bytes
    char level; // 1 byte (plus potential padding)
public:
    void display()
    {
        /* Method logic here */
    }
};

int main()
{
    Player p1;

    /*
        sizeof(p1) tells us how much memory
        the specific object 'p1' occupies.
    */
    cout << "Size of object: " << sizeof(p1) << " bytes" << endl;

    return 0;
}

/*
WHY "OBJECT-ORIENTED" AND NOT "CLASS-ORIENTED"?

While classes are the blueprints we write in our code, the Object is the
living entity that actually occupies memory and performs actions.

Execution vs. Definition: A class is a static description. It does
nothing until it is instantiated. The "Oriented" part refers to the
fact that the system's logic is driven by the interaction between
objects.

State: Only objects have "state" (actual values). A class defines that
a Car has a speed, but only an object 'myCar' is actually going 60 mph.

Focus: The philosophy of OOP is to model the world as a collection of
interacting entities (objects) rather than a list of instructions
or templates.

CLASS VS. OBJECT VS. INSTANCE

These terms are often used interchangeably, but there are technical nuances.

Class:    A user-defined data type; the blueprint (e.g., House Blueprint).

Object:   A real-world entity created from the class (e.g., The Physical House).

Instance: The specific "realization" of an object in memory. "Instance"
emphasizes the relationship: the house is an instance of
that blueprint.

Note: An Object is the thing itself, while an Instance refers to its
origin. You "instantiate" a class to create an "object."

DATA HIDING: ABSTRACTION OR ENCAPSULATION?

Data hiding is technically a result of Encapsulation, but it serves the
goal of Abstraction.

Encapsulation: The mechanism. It is the act of bundling data and
methods into a single unit (the class) and using access specifiers
(private, protected) to restrict access. This is where data hiding
"belongs" physically.

Abstraction: The concept. It is the act of showing only essential
features and hiding the complex background details.

Verdict: Data hiding is a core part of Encapsulation.

FACTORS AFFECTING OBJECT SIZE (MEMORY)

To find the size of an object in C++, use the 'sizeof' operator.

Member Variables: The sum of the sizes of all non-static data members.

Padding/Alignment: The compiler may add "empty" bytes to align data
for faster CPU access.

Virtual Functions: If the class has virtual functions, the object
contains a hidden pointer (vptr), usually adding 8 bytes on a
64-bit system.

Empty Classes: An empty class object still occupies 1 byte to ensure
it has a unique memory address.
*/