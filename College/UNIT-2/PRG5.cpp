// Program to implement message passing
#include <iostream>
using namespace std;
class Book
{
public:
    void displayDetails()
    {
        cout << "This is a book." << endl;
    }
};
class Library
{
public:
    void showBookDetails(Book &book)
    {
        book.displayDetails();
    }
};
int main()
{
    Book myBook;
    Library myLibrary;
    myLibrary.showBookDetails(myBook);
    return 0;
}