#include <bits/stdc++.h>
using namespace std;

class Person {
public:
    Person() { cout << "Person::Person() called" << endl; }
    Person(int x) { cout << "Person::Person(int) called" << endl; }
};
class Father : virtual public Person {
public:
    Father(int x) : Person(x) { cout << "Father::Father(int) called" << endl; }
};
class Mother : virtual public Person {
public:
    Mother(int x) : Person(x) { cout << "Mother::Mother(int) called" << endl; }
};
class Child : public Father, public Mother {
public:
    Child(int x) : Mother(x), Father(x) { cout << "Child::Child(int) called" << endl; }
};

int main() {
    Child child(30);
    return 0;
}

/*
With virtual inheritance the MOST-DERIVED class (Child) constructs Person.
Child did not mention Person(x), so Person's DEFAULT constructor runs.
(To use Person(int), write  Child(int x) : Person(x), Father(x), Mother(x).)

Output:
Person::Person() called
Father::Father(int) called
Mother::Mother(int) called
Child::Child(int) called
*/
