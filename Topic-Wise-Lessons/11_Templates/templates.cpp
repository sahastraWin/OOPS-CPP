/*
 * ============================================================
 *  TOPIC: Templates in C++ (Generic Programming)
 * ============================================================
 *
 * Templates allow writing code that works with ANY data type.
 * They are resolved at COMPILE TIME (zero runtime overhead).
 *
 * Types:
 *   1. Function Templates
 *   2. Class Templates
 *   3. Template Specialisation
 *   4. Variadic Templates (C++11)
 *
 * ╔══════════════════════════════════════════════════════════╗
 *  INTERVIEW MUST-KNOW:
 *  - Templates are COMPILE-TIME polymorphism (unlike virtual
 *    functions which are RUNTIME polymorphism).
 *  - The compiler generates a SEPARATE concrete version of the
 *    function/class for each type used — called INSTANTIATION.
 *  - Template code is usually placed in HEADER files because
 *    the compiler needs the full definition at instantiation.
 *  - STL (Standard Template Library) is entirely built on templates:
 *    vector<T>, map<K,V>, pair<A,B>, etc.
 *  - Template type parameter: typename T  (same as class T)
 * ╚══════════════════════════════════════════════════════════╝
 */

#include <iostream>
#include <string>
#include <stdexcept>
#include <algorithm>
using namespace std;

/* ══════════════════════════════════════════════════════════
   1. FUNCTION TEMPLATES
   ══════════════════════════════════════════════════════════ */

/* Generic swap — works for ANY type T */
template <typename T>
void mySwap(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}

/* Generic max — returns larger of two values */
template <typename T>
T myMax(T a, T b)
{
    return (a > b) ? a : b;
}

/* Multiple template parameters */
template <typename T, typename U>
void printPair(T first, U second)
{
    cout << "(" << first << ", " << second << ")\n";
}

/* Function template with non-type parameter */
template <typename T, int SIZE>
T arraySum(T (&arr)[SIZE])
{
    T sum = T(); // zero-initialise
    for (int i = 0; i < SIZE; i++)
        sum += arr[i];
    return sum;
}

/* Generic binary search */
template <typename T>
int binarySearch(T arr[], int size, T target)
{
    int lo = 0, hi = size - 1;
    while (lo <= hi)
    {
        int mid = lo + (hi - lo) / 2;
        if (arr[mid] == target)
            return mid;
        else if (arr[mid] < target)
            lo = mid + 1;
        else
            hi = mid - 1;
    }
    return -1;
}

/* ══════════════════════════════════════════════════════════
   2. CLASS TEMPLATES
   ══════════════════════════════════════════════════════════

   ╔══════════════════════════════════════════════════════════╗
    INTERVIEW TIP:
    When defining template class member functions OUTSIDE
    the class, repeat the template header each time:
        template <typename T>
        T Stack<T>::top() const { ... }
   ╚══════════════════════════════════════════════════════════╝
*/

template <typename T>
class Stack
{
private:
    T *data;
    int capacity;
    int topIndex;

public:
    Stack(int cap = 10) : capacity(cap), topIndex(-1)
    {
        data = new T[capacity];
    }

    /* Copy constructor */
    Stack(const Stack &other) : capacity(other.capacity), topIndex(other.topIndex)
    {
        data = new T[capacity];
        for (int i = 0; i <= topIndex; i++)
            data[i] = other.data[i];
    }

    ~Stack() { delete[] data; }

    void push(const T &val)
    {
        if (topIndex == capacity - 1)
            throw overflow_error("Stack overflow");
        data[++topIndex] = val;
    }

    T pop()
    {
        if (isEmpty())
            throw underflow_error("Stack underflow");
        return data[topIndex--];
    }

    T top() const
    {
        if (isEmpty())
            throw underflow_error("Stack is empty");
        return data[topIndex];
    }

    bool isEmpty() const { return topIndex == -1; }
    int size() const { return topIndex + 1; }

    void display() const
    {
        cout << "Stack [top→bottom]: ";
        for (int i = topIndex; i >= 0; i--)
            cout << data[i] << " ";
        cout << "\n";
    }
};

/* ══════════════════════════════════════════════════════════
   3. CLASS TEMPLATE with multiple parameters
   ══════════════════════════════════════════════════════════ */

template <typename K, typename V>
class Pair
{
public:
    K key;
    V value;

    Pair(K k, V v) : key(k), value(v) {}

    void display() const
    {
        cout << key << " => " << value << "\n";
    }

    /* Comparison based on key */
    bool operator<(const Pair<K, V> &other) const
    {
        return key < other.key;
    }
};

/* ══════════════════════════════════════════════════════════
   4. TEMPLATE SPECIALISATION
   ══════════════════════════════════════════════════════════

   ╔══════════════════════════════════════════════════════════╗
    INTERVIEW TIP:
    Full Specialisation: override template for a SPECIFIC type.
    Partial Specialisation: override for a subset of types
    (e.g., pointer types, const types). Only valid for classes.
   ╚══════════════════════════════════════════════════════════╝
*/

/* Generic print */
template <typename T>
void smartPrint(T val)
{
    cout << "Value: " << val << "\n";
}

/* Full specialisation for bool — print true/false, not 1/0 */
template <>
void smartPrint<bool>(bool val)
{
    cout << "Bool: " << (val ? "true" : "false") << "\n";
}

/* Full specialisation for const char* — add quotes */
template <>
void smartPrint<const char *>(const char *val)
{
    cout << "String: \"" << val << "\"\n";
}

/* ══════════════════════════════════════════════════════════
   5. VARIADIC TEMPLATE (C++11) — variable number of args
   ══════════════════════════════════════════════════════════

   ╔══════════════════════════════════════════════════════════╗
    INTERVIEW TIP:
    Variadic templates use parameter PACKS (typename... Args).
    Recursion peels off one argument at a time.
    Base case (no args) stops recursion.
    Used internally by std::tuple, std::make_shared, etc.
   ╚══════════════════════════════════════════════════════════╝
*/

/* Base case: no arguments left */
void printAll() { cout << "\n"; }

/* Recursive case: print first arg, recurse on rest */
template <typename First, typename... Rest>
void printAll(First first, Rest... rest)
{
    cout << first << " ";
    printAll(rest...); // expand the pack
}

/* Variadic sum */
template <typename T>
T varSum(T val) { return val; }

template <typename T, typename... Args>
T varSum(T first, Args... args)
{
    return first + varSum(args...);
}

/* ══════════════════════════════════════════════════════════
   MAIN
   ══════════════════════════════════════════════════════════ */
int main()
{
    cout << "===== Templates in C++ =====\n\n";

    /* --- Function Templates --- */
    cout << "--- 1. Function Templates ---\n";
    int a = 3, b = 7;
    cout << "Before swap: a=" << a << " b=" << b << "\n";
    mySwap(a, b);
    cout << "After swap:  a=" << a << " b=" << b << "\n";

    string s1 = "apple", s2 = "mango";
    mySwap(s1, s2);
    cout << "Swapped strings: " << s1 << ", " << s2 << "\n";

    cout << "myMax(3,7)       = " << myMax(3, 7) << "\n";
    cout << "myMax(3.14, 2.7) = " << myMax(3.14, 2.7) << "\n";
    cout << "myMax('a','z')   = " << myMax('a', 'z') << "\n";

    printPair(1, "hello");
    printPair(3.14, true);

    int intArr[] = {1, 2, 3, 4, 5};
    double dblArr[] = {1.1, 2.2, 3.3};
    cout << "Sum of intArr  = " << arraySum(intArr) << "\n";
    cout << "Sum of dblArr  = " << arraySum(dblArr) << "\n";

    /* --- Class Templates (Stack) --- */
    cout << "\n--- 2. Class Template (Stack) ---\n";
    Stack<int> intStack(5);
    intStack.push(10);
    intStack.push(20);
    intStack.push(30);
    intStack.display();
    cout << "Pop: " << intStack.pop() << "\n";
    intStack.display();

    Stack<string> strStack(3);
    strStack.push("first");
    strStack.push("second");
    strStack.push("third");
    strStack.display();

    try
    {
        strStack.push("overflow"); // should throw
    }
    catch (const overflow_error &e)
    {
        cout << "Caught: " << e.what() << "\n";
    }

    /* --- Multiple Template Params --- */
    cout << "\n--- 3. Multiple Template Parameters ---\n";
    Pair<string, int> p1("age", 25);
    Pair<string, double> p2("gpa", 9.5);
    Pair<int, string> p3(1001, "Alice");
    p1.display();
    p2.display();
    p3.display();

    /* --- Template Specialisation --- */
    cout << "\n--- 4. Template Specialisation ---\n";
    smartPrint(42);
    smartPrint(3.14);
    smartPrint(true);          // uses bool specialisation
    smartPrint("hello world"); // uses const char* specialisation

    /* --- Variadic Templates --- */
    cout << "\n--- 5. Variadic Templates ---\n";
    cout << "printAll: ";
    printAll(1, 2.5, "three", 'x', true);

    cout << "varSum(1,2,3,4,5)     = " << varSum(1, 2, 3, 4, 5) << "\n";
    cout << "varSum(1.1, 2.2, 3.3) = " << varSum(1.1, 2.2, 3.3) << "\n";

    return 0;
}
