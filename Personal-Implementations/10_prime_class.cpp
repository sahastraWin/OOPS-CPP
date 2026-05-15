/*
    QUESTION:
    Write a C++ program using OOP to check if a number is prime.
    Create a class 'Prime' with:
    - Constructor that takes an integer and checks if it's prime
    - show() method that displays the result
    A number is prime if it has no divisors other than 1 and itself.
    Input: An integer
    Output: "<n> is Prime Number." or "<n> is Not Prime Number."
*/

#include <bits/stdc++.h>
using namespace std;

class Prime
{
    int a, k;

public:
    Prime(int x)
    {
        a = x;
        k = 1; // assume prime

        if (a <= 1)
        {
            k = 0; // 0 and 1 are not prime
            return;
        }

        for (int i = 2; i * i <= a; i++)
        {
            if (a % i == 0)
            {
                k = 0; // found a factor → not prime
                break;
            }
        }
    }

    void show()
    {
        if (k == 1)
            cout << a << " is Prime Number." << endl;
        else
            cout << a << " is Not Prime Number." << endl;
    }
};

int main()
{
    int a;
    cout << "Enter the Number: ";
    cin >> a;

    Prime obj(a);
    obj.show();

    return 0;
}

/*
    INTUITION:
    - Encapsulate the prime-checking logic inside a class.
    - The constructor does the computation: flag k=1 means prime, k=0 means not.
    - OPTIMIZATION: check divisors only up to sqrt(a) using i*i <= a.
      If a has a factor d > sqrt(a), then a/d < sqrt(a) is also a factor
      and would have been found already.
    - k is a member variable so show() can access it without re-computing.
    - Special case: a <= 1 → not prime by definition.
    - OOP advantage: the Prime class encapsulates both data and logic together.

    TIME COMPLEXITY:  O(sqrt(n)) — loop runs up to sqrt(a) iterations.
    SPACE COMPLEXITY: O(1) — only two member variables (a, k).
*/
