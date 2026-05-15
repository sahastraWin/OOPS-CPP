// Program to implement default constructor
#include <iostream>
using namespace std;
class Book
{
public:
    int bookId;
    string title;
    // Default constructor
    Book()
    {
        bookId = 0;
        title = "Unknown";
    }
    void display()
    {
        cout << "Book Id: " << bookId << endl;
        cout << "Book Title: " << title << endl;
    }
};
int main()
{
    Book b1; //Default constructor is called
    b1.display();
    return 0;
}
