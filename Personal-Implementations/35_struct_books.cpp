/*
    QUESTION:
    Write a C++ program demonstrating STRUCTURES (struct) for a book catalog.
    Define a struct 'Books' with name and author fields.
    Read n books from the user into an array of structs and display them in a table.
    Input: Number of books n, then name and author for each
    Output: Formatted table of S.No, Book, Author
*/

#include <bits/stdc++.h>
using namespace std;

struct Books
{
    char name[50];
    char author[50];
};

int main()
{
    Books a[50];
    int n;

    cout << "No Of Books: ";
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        cout << "Book " << (i + 1) << " - Name: ";
        cin >> a[i].name;
        cout << "Book " << (i + 1) << " - Author: ";
        cin >> a[i].author;
    }

    cout << "\nS.No\tBook\t\tAuthor" << endl;
    cout << "----\t----\t\t------" << endl;

    for (int i = 0; i < n; i++)
        cout << (i + 1) << "\t" << a[i].name << "\t\t" << a[i].author << endl;

    return 0;
}

/*
    INTUITION:
    - A STRUCT groups related data of different types under one name.
    - struct Books bundles 'name' and 'author' — two pieces of data that
      logically belong together for each book.
    - An ARRAY OF STRUCTS: Books a[50] stores up to 50 book records.
    - Access members via dot notation: a[i].name, a[i].author.
    - Loop 1 (i from 0 to n-1): reads each book's data.
    - Loop 2 (i from 0 to n-1): displays in tabular format.
    - 0-based indexing internally; display shows i+1 for user-friendly numbering.
    - struct vs class in C++: struct members are PUBLIC by default; class members
      are PRIVATE by default. Otherwise identical.

    TIME COMPLEXITY:  O(n) — two linear loops (read and display).
    SPACE COMPLEXITY: O(n) — array of n Book structs.
*/
