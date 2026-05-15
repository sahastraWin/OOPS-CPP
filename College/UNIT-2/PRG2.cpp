// Program to implement parameterized constructor
#include <iostream>
using namespace std;
class Book
{
public:
    int bookId;
    string title;
    // parameterized constructor
    Book(int id, string t)
    {
        bookId = id;
        title = t;
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
    b1.display();
    return 0;
}
