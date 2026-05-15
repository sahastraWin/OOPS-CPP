/*
 * ============================================================
 *  TOPIC: C++11 (and beyond) Features
 * ============================================================
 *
 * Covered here:
 *   1. auto keyword
 *   2. decltype
 *   3. final keyword (restrict inheritance / overriding)
 *   4. Lambda Expressions
 *   5. In-Class Member Initialisers
 *   6. Constructor Delegation
 *   7. Ellipsis / Variadic Functions (va_list)
 *   8. Range-based for loop
 *   9. nullptr
 *  10. Initialiser List (std::initializer_list)
 *  11. Move Semantics (move constructor + move assignment)
 *
 * ╔══════════════════════════════════════════════════════════╗
 *  INTERVIEW MUST-KNOW: C++11 is a watershed release.
 *  Almost everything listed here is now expected knowledge
 *  for any modern C++ role.
 * ╚══════════════════════════════════════════════════════════╝
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstdarg> // va_list, va_start, va_arg, va_end
#include <initializer_list>
#include <utility> // move, forward
using namespace std;

/* ══════════════════════════════════════════════════════════
   1. auto KEYWORD
   ══════════════════════════════════════════════════════════

   ╔══════════════════════════════════════════════════════════╗
    INTERVIEW MUST-KNOW:
    'auto' deduces the TYPE from the initialiser at compile time.
    - Makes code more readable for complex types (iterators, etc.)
    - Does NOT mean dynamic typing — type is fixed at compile time.
    - auto drops const/reference by default; use auto& or const auto&
      to preserve them.
    - Trailing return type syntax: auto func() -> ReturnType { }
   ╚══════════════════════════════════════════════════════════╝
*/

auto add(int a, int b) -> int
{ // trailing return type
    return a + b;
}

void autoDemo()
{
    cout << "--- 1. auto Keyword ---\n";

    auto x = 42;      // int
    auto y = 3.14;    // double
    auto z = "hello"; // const char*
    auto flag = true; // bool

    cout << "auto x=" << x << " y=" << y << " z=" << z << " flag=" << flag << "\n";

    /* auto with containers */
    vector<int> nums = {1, 2, 3, 4, 5};
    auto it = nums.begin(); // vector<int>::iterator — verbose without auto
    cout << "First element via auto iterator: " << *it << "\n";

    /* auto & for references */
    auto &ref = x;
    ref = 100;
    cout << "x after ref=100: " << x << "\n";

    /* const auto& for read-only references */
    const auto &cref = y;
    cout << "const auto& y = " << cref << "\n";

    /* auto in range-based for */
    cout << "Vector: ";
    for (const auto &val : nums)
        cout << val << " ";
    cout << "\n";
}

/* ══════════════════════════════════════════════════════════
   2. decltype
   ══════════════════════════════════════════════════════════

   ╔══════════════════════════════════════════════════════════╗
    INTERVIEW TIP:
    decltype(expr) deduces the type of an expression WITHOUT
    evaluating it. Useful in templates and trailing return types.
    Difference from auto:
      auto  : deduces from the VALUE
      decltype: deduces from the EXPRESSION TYPE exactly
                (preserves references and const)
   ╚══════════════════════════════════════════════════════════╝
*/

void decltypeDemo()
{
    cout << "\n--- 2. decltype ---\n";

    int a = 5;
    double b = 3.14;

    decltype(a) x = 10;      // int
    decltype(b) y = 2.71;    // double
    decltype(a + b) z = 7.5; // double (int + double → double)

    cout << "decltype(a)   x=" << x << "\n";
    cout << "decltype(b)   y=" << y << "\n";
    cout << "decltype(a+b) z=" << z << "\n";

    /* decltype for function return type deduction */
    auto multiply = [](auto x, auto y) -> decltype(x * y)
    {
        return x * y;
    };
    cout << "multiply(3, 4.5) = " << multiply(3, 4.5) << "\n";
}

/* ══════════════════════════════════════════════════════════
   3. final KEYWORD
   ══════════════════════════════════════════════════════════

   ╔══════════════════════════════════════════════════════════╗
    INTERVIEW MUST-KNOW: 'final' keyword (C++11)
    Two uses:
    1. On a CLASS: prevents any further inheritance.
       class Sealed final { ... };   // cannot be subclassed
    2. On a VIRTUAL FUNCTION: prevents further overriding.
       void foo() override final { }  // no derived class can override
    Compiler error if violated — better than runtime surprise.
   ╚══════════════════════════════════════════════════════════╝
*/

class Base
{
public:
    virtual void greet() const { cout << "Hello from Base\n"; }
    virtual void compute() const { cout << "Base compute\n"; }
    virtual ~Base() {}
};

class Middle : public Base
{
public:
    void greet() const override final
    { // 'final' here: no further override
        cout << "Hello from Middle\n";
    }
    void compute() const override { cout << "Middle compute\n"; }
};

class Leaf final : public Middle
{ // 'final' class: cannot inherit from Leaf
public:
    /* void greet() override { }   // ERROR: greet is final in Middle */
    void compute() const override { cout << "Leaf compute\n"; }
};

/* class TryInherit : public Leaf { };   // ERROR: Leaf is final */

/* ══════════════════════════════════════════════════════════
   4. LAMBDA EXPRESSIONS
   ══════════════════════════════════════════════════════════

   ╔══════════════════════════════════════════════════════════╗
    INTERVIEW MUST-KNOW: Lambda Syntax
    [capture](params) mutable -> ReturnType { body }

    Capture modes:
      []        — capture nothing
      [x]       — capture x by value
      [&x]      — capture x by reference
      [=]       — capture all locals by value
      [&]       — capture all locals by reference
      [=, &x]   — all by value except x by reference
      [this]    — capture this pointer (class context)

    'mutable': allows modifying captured-by-value copies.
    Lambda type: unique unnamed type (use auto or std::function).
   ╚══════════════════════════════════════════════════════════╝
*/

void lambdaDemo()
{
    cout << "\n--- 4. Lambda Expressions ---\n";

    /* Basic lambda */
    auto greet = []()
    { cout << "Hello from lambda!\n"; };
    greet();

    /* Lambda with parameters and return type */
    auto add = [](int a, int b) -> int
    { return a + b; };
    cout << "add(3, 4) = " << add(3, 4) << "\n";

    /* Capture by value */
    int base = 10;
    auto addBase = [base](int x)
    { return base + x; }; // base is captured
    cout << "addBase(5) = " << addBase(5) << "\n";
    base = 999; // changing base doesn't affect lambda's copy
    cout << "addBase(5) after base=999 (still 10+5): " << addBase(5) << "\n";

    /* Capture by reference */
    int counter = 0;
    auto increment = [&counter]()
    { ++counter; };
    increment();
    increment();
    increment();
    cout << "counter after 3 increments: " << counter << "\n";

    /* mutable lambda (modify captured-by-value copy) */
    int val = 5;
    auto mutLambda = [val]() mutable
    {
        val += 10; // modifies LOCAL COPY, not original val
        return val;
    };
    cout << "mutLambda() = " << mutLambda() << " (val still: " << val << ")\n";

    /* Lambda stored in std::function */
    function<double(double, double)> power = [](double base, double exp)
    {
        double result = 1;
        for (int i = 0; i < (int)exp; i++)
            result *= base;
        return result;
    };
    cout << "power(2, 10) = " << power(2, 10) << "\n";

    /* Lambda with STL algorithms */
    vector<int> nums = {5, 3, 8, 1, 9, 2, 7};
    sort(nums.begin(), nums.end(), [](int a, int b)
         { return a < b; });
    cout << "Sorted: ";
    for (const auto &n : nums)
        cout << n << " ";
    cout << "\n";

    /* Filter with lambda */
    vector<int> evens;
    for_each(nums.begin(), nums.end(), [&evens](int n)
             {
        if (n % 2 == 0) evens.push_back(n); });
    cout << "Even numbers: ";
    for (const auto &n : evens)
        cout << n << " ";
    cout << "\n";

    /* Immediately invoked lambda */
    int result = [](int x, int y)
    { return x * y; }(6, 7);
    cout << "Immediately invoked 6*7 = " << result << "\n";
}

/* ══════════════════════════════════════════════════════════
   5. IN-CLASS MEMBER INITIALISERS & CONSTRUCTOR DELEGATION
   ══════════════════════════════════════════════════════════

   ╔══════════════════════════════════════════════════════════╗
    INTERVIEW TIP: In-class initialisers (C++11)
    - Can provide default values for members directly in
      the class definition.
    - Constructors that don't initialise those members will
      use these defaults — reduces boilerplate.
    - Constructor delegation: one constructor calls another
      of the SAME class to avoid code duplication.
   ╚══════════════════════════════════════════════════════════╝
*/

class ServerConfig
{
public:
    string host = "localhost"; // in-class initialiser
    int port = 8080;           // in-class initialiser
    bool ssl = false;          // in-class initialiser
    int timeout = 30;          // in-class initialiser
    string name;

    /* Delegation: all route through the fully-parameterised constructor */
    ServerConfig(string n, string h, int p, bool s, int t)
        : name(n), host(h), port(p), ssl(s), timeout(t) {}

    ServerConfig(string n, int p)
        : ServerConfig(n, "localhost", p, false, 30) {} // delegate

    ServerConfig(string n)
        : ServerConfig(n, 8080) {} // delegate

    ServerConfig()
        : ServerConfig("default") {} // delegate

    void display() const
    {
        cout << name << ": " << (ssl ? "https" : "http") << "://"
             << host << ":" << port
             << " timeout=" << timeout << "s\n";
    }
};

/* ══════════════════════════════════════════════════════════
   6. VARIADIC FUNCTIONS (Ellipsis / va_list)
   ══════════════════════════════════════════════════════════

   ╔══════════════════════════════════════════════════════════╗
    INTERVIEW TIP:
    va_list is the C-style way of handling variable arguments.
    Steps:
    1. va_list args;
    2. va_start(args, lastFixed);   — init after last named param
    3. va_arg(args, Type);          — get next argument
    4. va_end(args);                — cleanup
    MODERN C++: Prefer variadic templates (safer, type-safe).
   ╚══════════════════════════════════════════════════════════╝
*/

int variadicSum(int count, ...)
{
    va_list args;
    va_start(args, count); // initialise after 'count'
    int sum = 0;
    for (int i = 0; i < count; i++)
    {
        sum += va_arg(args, int); // fetch one int at a time
    }
    va_end(args); // cleanup
    return sum;
}

void variadicDemo()
{
    cout << "\n--- 7. Variadic Functions (Ellipsis) ---\n";
    cout << "variadicSum(3, 10, 20, 30)     = " << variadicSum(3, 10, 20, 30) << "\n";
    cout << "variadicSum(5, 1, 2, 3, 4, 5) = " << variadicSum(5, 1, 2, 3, 4, 5) << "\n";
}

/* ══════════════════════════════════════════════════════════
   7. MOVE SEMANTICS — Move Constructor + Move Assignment
   ══════════════════════════════════════════════════════════

   ╔══════════════════════════════════════════════════════════╗
    INTERVIEW MUST-KNOW: Move Semantics (C++11)
    Problem: copying large objects (e.g., with heap data) is
    expensive — allocate + copy + deallocate old.
    Solution: MOVE transfers ownership of resources (no copy).
    The moved-from object is left in a valid-but-unspecified state.

    Move constructor:    ClassName(ClassName&& other)
    Move assignment:     ClassName& operator=(ClassName&& other)

    '&&' = rvalue reference — binds to temporaries and
    objects explicitly moved with std::move().

    Rule of Five: if you define any of ctor, dtor, copy ctor,
    copy assign → also define move ctor + move assign.
   ╚══════════════════════════════════════════════════════════╝
*/

class Buffer
{
private:
    int *data;
    size_t size;
    string label;

public:
    /* Constructor */
    Buffer(string lbl, size_t sz) : label(lbl), size(sz)
    {
        data = new int[sz];
        for (size_t i = 0; i < sz; i++)
            data[i] = (int)i;
        cout << "[Buffer CTOR] '" << label << "' size=" << sz << "\n";
    }

    /* Copy constructor — deep copy */
    Buffer(const Buffer &other) : label(other.label + "_copy"), size(other.size)
    {
        data = new int[size];
        for (size_t i = 0; i < size; i++)
            data[i] = other.data[i];
        cout << "[Buffer COPY] '" << label << "'\n";
    }

    /* Move constructor — steal resources, no allocation! */
    Buffer(Buffer &&other) noexcept
        : data(other.data), size(other.size), label(move(other.label))
    {
        other.data = nullptr; // CRUCIAL: null the source pointer
        other.size = 0;
        cout << "[Buffer MOVE] '" << label << "' (no allocation)\n";
    }

    /* Copy assignment */
    Buffer &operator=(const Buffer &other)
    {
        if (this == &other)
            return *this;
        delete[] data;
        size = other.size;
        label = other.label + "_copy";
        data = new int[size];
        for (size_t i = 0; i < size; i++)
            data[i] = other.data[i];
        cout << "[Buffer COPY=] '" << label << "'\n";
        return *this;
    }

    /* Move assignment — steal resources */
    Buffer &operator=(Buffer &&other) noexcept
    {
        if (this == &other)
            return *this;
        delete[] data; // free our old data
        data = other.data;
        size = other.size;
        label = move(other.label);
        other.data = nullptr; // null the source
        other.size = 0;
        cout << "[Buffer MOVE=] '" << label << "'\n";
        return *this;
    }

    ~Buffer()
    {
        if (data)
            delete[] data;
        cout << "[Buffer DTOR] '" << label << "'\n";
    }

    void display() const
    {
        cout << "Buffer('" << label << "' size=" << size << "): ";
        if (data)
            for (size_t i = 0; i < size && i < 5; i++)
                cout << data[i] << " ";
        else
            cout << "(empty/moved)";
        cout << "\n";
    }
};

/* ══════════════════════════════════════════════════════════
   8. nullptr
   ══════════════════════════════════════════════════════════

   ╔══════════════════════════════════════════════════════════╗
    INTERVIEW TIP:
    nullptr (C++11) is the type-safe null pointer constant.
    - Type: std::nullptr_t
    - Replaces NULL (which is just 0 or ((void*)0))
    - Avoids ambiguity: func(NULL) → func(int) or func(int*)?
      func(nullptr) → always resolves to pointer overload.
   ╚══════════════════════════════════════════════════════════╝
*/

void handlePtr(int *p) { cout << "int* overload called\n"; }
void handlePtr(int n) { cout << "int  overload called\n"; }

void nullptrDemo()
{
    cout << "\n--- 9. nullptr ---\n";
    /* handlePtr(NULL);    // AMBIGUOUS: could be int or int* */
    handlePtr(nullptr); // unambiguously int*
    handlePtr(0);       // int overload
    int *p = nullptr;
    if (!p)
        cout << "Pointer is null (safe check)\n";
}

/* ══════════════════════════════════════════════════════════
   MAIN
   ══════════════════════════════════════════════════════════ */
int main()
{
    cout << "===== C++11 and Modern C++ Features =====\n\n";

    autoDemo();
    decltypeDemo();

    cout << "\n--- 3. final Keyword ---\n";
    Leaf leaf;
    leaf.greet();
    leaf.compute();
    Base *bp = new Leaf();
    bp->greet();   // calls Middle::greet (final)
    bp->compute(); // calls Leaf::compute
    delete bp;

    lambdaDemo();

    cout << "\n--- 5. In-Class Initialisers & Delegation ---\n";
    ServerConfig c1;
    ServerConfig c2("api-server");
    ServerConfig c3("prod", 443);
    ServerConfig c4("custom", "10.0.0.1", 9090, true, 60);
    c1.display();
    c2.display();
    c3.display();
    c4.display();

    variadicDemo();

    cout << "\n--- 8. Move Semantics ---\n";
    Buffer b1("original", 5);
    b1.display();

    Buffer b2 = b1; // copy
    b2.display();

    Buffer b3 = move(b1); // move — b1 is emptied
    cout << "b1 after move: ";
    b1.display();
    cout << "b3 (moved):    ";
    b3.display();

    Buffer b4("temp", 3);
    b3 = move(b4); // move assignment
    b3.display();

    nullptrDemo();

    cout << "\n--- Cleanup (destructors) ---\n";
    return 0;
}
