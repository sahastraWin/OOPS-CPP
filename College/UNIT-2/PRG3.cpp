// Program to implement copy constructor
#include <iostream>
using namespace std;
class Book
{
public:
    int bookId;
    string title;
    // paramterized constructor
    Book(int id, string t)
    {
        bookId = id;
        title = t;
    }
    Book(const Book &b)
    /*
    This constructor takes a reference to a constant object of the same class (const Book &b) 
    and initializes the new object's bookId and title members with the values from the existing object b.
    */
    {
        bookId = b.bookId;
        title = b.title;
    }
    void display()
    {
        cout << "Book Id: " << bookId << endl;
        cout << "Book Title: " << title << endl;
    }
};
int main()
{
    Book b1(1, "The Alchemist"); // parameterized constructor is called
    Book b2 = b1;                // copy constructor  is called
    b2.display();
    return 0;
}
