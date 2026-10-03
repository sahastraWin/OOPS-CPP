#include <bits/stdc++.h>
using namespace std;

template <class T>
class Stack {
private:
    T *stk;
    int top, maxSize;
public:
    Stack(int sz) {
        maxSize = sz;
        top = -1;
        stk = new T[maxSize];
    }
    ~Stack() { delete[] stk; }
    void Push(T x);
    T Pop();
};

/* Member functions defined outside need the template line again */
template <class T>
void Stack<T>::Push(T x) {
    if (top == maxSize - 1)
        cout << "Stack is Full" << endl;
    else {
        top++;
        stk[top] = x;
        cout << x << " Added to Stack" << endl;
    }
}

template <class T>
T Stack<T>::Pop() {
    T x = 0;
    if (top == -1)
        cout << "Stack is Empty" << endl;
    else {
        x = stk[top];
        top--;
        cout << x << " Removed from Stack" << endl;
    }
    return x;
}

int main() {
    cout << "--- Stack of int ---" << endl;
    Stack<int> stack1(10);
    stack1.Push(10);
    stack1.Push(23);
    stack1.Push(33);
    stack1.Pop();

    cout << "--- Stack of double ---" << endl;
    Stack<double> stack2(10);
    stack2.Push(10.5);
    stack2.Push(23.7);
    stack2.Push(33.8);
    stack2.Pop();
    return 0;
}

/*
Output:
--- Stack of int ---
10 Added to Stack
23 Added to Stack
33 Added to Stack
33 Removed from Stack
--- Stack of double ---
10.5 Added to Stack
23.7 Added to Stack
33.8 Added to Stack
33.8 Removed from Stack
*/
