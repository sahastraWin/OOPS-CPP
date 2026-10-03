#include <bits/stdc++.h>
using namespace std;

class Person {
public:
    Person(int x) { cout << "Person::Person(int) called" << endl; }
};
class Father : public Person {
public:
    Father(int x) : Person(x) { cout << "Father::Father(int) called" << endl; }
};
class Mother : public Person {
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
Constructors run in the ORDER OF DECLARATION (Father, Mother), not the order
you write in the initializer list. Child ends up with two Person copies.

Output:
Person::Person(int) called
Father::Father(int) called
Person::Person(int) called
Mother::Mother(int) called
Child::Child(int) called
*/
