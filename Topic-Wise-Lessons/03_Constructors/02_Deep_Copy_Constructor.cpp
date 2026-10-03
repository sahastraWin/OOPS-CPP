#include <bits/stdc++.h>
using namespace std;

class Test
{
private:
    int a;
    int *p; // pointer to dynamic memory
public:
    Test(int x)
    {
        a = x;
        p = new int[5];
        for (int i = 0; i < 5; i++)
            p[i] = i + 1;
    }

    /* 🔹 DEEP copy: creates NEW memory and copies the VALUES */
    Test(const Test &t)
    {
        a = t.a;
        p = new int[5];
        for (int i = 0; i < 5; i++)
            p[i] = t.p[i];
    }

    void setValue(int index, int value) { p[index] = value; }

    void display()
    {
        cout << "a = " << a << ", p = ";
        for (int i = 0; i < 5; i++)
            cout << p[i] << " ";
        cout << endl;
    }

    ~Test() { delete[] p; } // free the memory
};

int main()
{
    Test t1(10);
    Test t2(t1);        // deep copy
    t2.setValue(0, 99); // change ONLY t2

    t1.display();
    t2.display();
    return 0;
}

/*
🧠 Intuition:
SHALLOW copy:  this->p = t.p;   -> both objects share ONE array.
                                   Changing one changes the other, and
                                   both destructors delete the same memory (crash!).
DEEP copy:     this->p = new int[5]; -> each object owns its own array.

Output:
a = 10, p = 1 2 3 4 5
a = 10, p = 99 2 3 4 5
*/
