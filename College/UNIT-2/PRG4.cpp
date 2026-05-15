// Program to implement destructor
#include <iostream>
using namespace std;
class Book
{
public:
    int bookId;
    string title;
    // parameterized constructor
    Book(int id, string t) : bookId(id), title(t)
    {
        cout << "Constructor called for Book : " << title << endl;
    }
    ~Book()
    {
        cout << "Destructor called for Book : " << title << endl;
    }
    void display()
    {
        cout << "Book Id: " << bookId << endl;
        cout << "Book Title: " << title << endl;
    }
};
/*
This demonstrates the order in which constructors and destructors are called in your program.
The constructors are called in the order of object creation, while the destructors are called in the reverse order of object destruction.
*/
int main()
{
    Book b1(1, "The Alchemist"); // parameterized constructor is called
    b1.display();
    Book b2(2, "The Dark Side"); // parameterized constructor is called
    b1.display();
    return 0;
}
