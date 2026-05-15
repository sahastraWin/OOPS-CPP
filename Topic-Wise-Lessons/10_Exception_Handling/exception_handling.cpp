/*
 * ============================================================
 *  TOPIC: Exception Handling in C++
 * ============================================================
 *
 * 3 Types of Errors:
 *   1. Syntax Error    — caught by compiler
 *   2. Logical Error   — caught by debugger / testing
 *   3. Runtime Error   — exceptions, handled at runtime
 *
 * Keywords: try | catch | throw
 *
 * ╔══════════════════════════════════════════════════════════╗
 *  INTERVIEW MUST-KNOW:
 *  - try block  : code that might throw an exception.
 *  - throw      : sends an exception to the nearest catch.
 *  - catch block: handles a specific type of exception.
 *  - Execution jumps from throw to matching catch — code
 *    between throw and catch is NOT executed (stack unwinds).
 *  - Catch blocks are checked TOP TO BOTTOM — put MOST SPECIFIC
 *    (derived) exceptions FIRST, LEAST specific LAST.
 *  - catch(...) catches ALL exceptions — must be LAST catch.
 *  - C++ does NOT require a 'finally' block (use RAII instead).
 *  - Constructors CAN throw (since no return type to signal error).
 *  - Destructors should NOT throw (undefined behaviour if they
 *    throw while another exception is active).
 * ╚══════════════════════════════════════════════════════════╝
 */

#include <iostream>
#include <string>
#include <stdexcept> // standard exception hierarchy
#include <cmath>
using namespace std;

/* ══════════════════════════════════════════════════════════
   1. BASIC try / catch / throw
   ══════════════════════════════════════════════════════════ */

void divide(double a, double b)
{
    if (b == 0)
    {
        /*
         * ╔══════════════════════════════════════════════╗
         *  throw: transfers control to nearest catch.
         *  You can throw any type: int, string, object.
         *  Prefer throwing exception objects (derived from
         *  std::exception) for consistency.
         * ╚══════════════════════════════════════════════╝
         */
        throw runtime_error("Division by zero!");
    }
    cout << a << " / " << b << " = " << a / b << "\n";
}

/* ══════════════════════════════════════════════════════════
   2. MULTIPLE CATCH BLOCKS
   ══════════════════════════════════════════════════════════

   ╔══════════════════════════════════════════════════════════╗
    INTERVIEW TIP:
    Standard exception hierarchy (std):
         exception
         ├── logic_error
         │   ├── invalid_argument
         │   ├── domain_error
         │   ├── length_error
         │   └── out_of_range
         └── runtime_error
             ├── range_error
             ├── overflow_error
             └── underflow_error
    Catch derived BEFORE base class exceptions.
   ╚══════════════════════════════════════════════════════════╝
*/

void testMultipleCatch(int choice)
{
    try
    {
        switch (choice)
        {
        case 1:
            throw invalid_argument("Invalid argument given");
        case 2:
            throw out_of_range("Index out of range");
        case 3:
            throw runtime_error("Runtime failure");
        case 4:
            throw 42; // throwing a primitive int
        case 5:
            throw string("oops"); // throwing a string
        default:
            cout << "No exception\n";
        }
    }
    catch (const invalid_argument &e)
    { // most specific first
        cout << "[invalid_argument] " << e.what() << "\n";
    }
    catch (const out_of_range &e)
    {
        cout << "[out_of_range] " << e.what() << "\n";
    }
    catch (const logic_error &e)
    { // catches all logic_errors
        cout << "[logic_error] " << e.what() << "\n";
    }
    catch (const exception &e)
    { // catches all std exceptions
        cout << "[exception] " << e.what() << "\n";
    }
    catch (int code)
    { // catches int throws
        cout << "[int exception] code=" << code << "\n";
    }
    catch (const string &s)
    { // catches string throws
        cout << "[string exception] " << s << "\n";
    }
    catch (...)
    { // catch-all — MUST be last
        cout << "[unknown exception]\n";
    }
}

/* ══════════════════════════════════════════════════════════
   3. CUSTOM EXCEPTION CLASSES
   ══════════════════════════════════════════════════════════

   ╔══════════════════════════════════════════════════════════╗
    INTERVIEW BEST PRACTICE:
    - Inherit from std::exception (or its derivatives).
    - Override the what() method to return a meaningful message.
    - what() is declared: virtual const char* what() const noexcept
    - 'noexcept' means this function will NEVER throw.
   ╚══════════════════════════════════════════════════════════╝
*/

class AppException : public exception
{
protected:
    string message;
    int errorCode;

public:
    AppException(string msg, int code)
        : message(msg), errorCode(code) {}

    /* Override what() to return error description */
    const char *what() const noexcept override
    {
        return message.c_str();
    }

    int getCode() const { return errorCode; }
};

class DatabaseException : public AppException
{
private:
    string query;

public:
    DatabaseException(string msg, int code, string q)
        : AppException(msg, code), query(q) {}

    const char *what() const noexcept override
    {
        /* Build a rich message */
        static string fullMsg;
        fullMsg = "DBError[" + to_string(errorCode) + "]: " + message + " | Query: " + query;
        return fullMsg.c_str();
    }

    string getQuery() const { return query; }
};

class NetworkException : public AppException
{
private:
    string host;
    int port;

public:
    NetworkException(string msg, int code, string h, int p)
        : AppException(msg, code), host(h), port(p) {}

    const char *what() const noexcept override
    {
        static string fullMsg;
        fullMsg = "NetError[" + to_string(errorCode) + "]: " + message + " | " + host + ":" + to_string(port);
        return fullMsg.c_str();
    }
};

void simulateDB(bool fail)
{
    if (fail)
        throw DatabaseException("Connection timeout", 503,
                                "SELECT * FROM users");
    cout << "DB query succeeded.\n";
}

void simulateNetwork(bool fail)
{
    if (fail)
        throw NetworkException("Host unreachable", 504, "api.server.com", 443);
    cout << "Network request succeeded.\n";
}

/* ══════════════════════════════════════════════════════════
   4. EXCEPTION FROM CONSTRUCTOR
   ══════════════════════════════════════════════════════════

   ╔══════════════════════════════════════════════════════════╗
    INTERVIEW TIP:
    If constructor fails, throw an exception — it is the only
    way to signal construction failure (no return type).
    When a constructor throws:
    - Destructor of the partially-constructed object is NOT called.
    - Destructors of fully-constructed member objects ARE called.
    → Use RAII members (smart pointers) to avoid leaks.
   ╚══════════════════════════════════════════════════════════╝
*/

class FileProcessor
{
private:
    string filename;

public:
    FileProcessor(string fname) : filename(fname)
    {
        if (fname.empty())
            throw invalid_argument("Filename cannot be empty");
        if (fname.size() > 255)
            throw length_error("Filename too long");
        cout << "[FileProcessor] Ready to process: " << filename << "\n";
    }

    void process()
    {
        cout << "Processing " << filename << "...\n";
    }
};

/* ══════════════════════════════════════════════════════════
   5. NESTED TRY BLOCKS + RE-THROWING
   ══════════════════════════════════════════════════════════

   ╔══════════════════════════════════════════════════════════╗
    INTERVIEW TIP:
    'throw;' inside a catch block RE-THROWS the current exception
    to the outer try-catch, preserving the original exception object.
    Use when you want to log or partially handle an exception,
    then let the caller deal with it.
   ╚══════════════════════════════════════════════════════════╝
*/

void outerFunction()
{
    try
    {
        cout << "[Outer try]\n";
        try
        {
            cout << "[Inner try] — throwing\n";
            throw runtime_error("Inner error occurred");
        }
        catch (const runtime_error &e)
        {
            cout << "[Inner catch] Caught: " << e.what() << "\n";
            cout << "[Inner catch] Logging... then re-throwing\n";
            throw; // re-throw to outer catch
        }
    }
    catch (const exception &e)
    {
        cout << "[Outer catch] Re-caught: " << e.what() << "\n";
    }
}

/* ══════════════════════════════════════════════════════════
   6. FUNCTION EXCEPTION SPECIFICATION (noexcept)
   ══════════════════════════════════════════════════════════

   ╔══════════════════════════════════════════════════════════╗
    INTERVIEW MUST-KNOW:
    noexcept  → function guarantees it will NEVER throw.
    If it does throw, std::terminate() is called immediately.
    Use noexcept on:
      - Destructors (already noexcept by default in C++11)
      - Move constructors / move assignment operators
      - Leaf functions that can't logically fail
    Compilers can optimise noexcept functions better.
   ╚══════════════════════════════════════════════════════════╝
*/

double safeSquareRoot(double x) noexcept(false)
{
    if (x < 0)
        throw domain_error("Square root of negative number");
    return sqrt(x);
}

/* ══════════════════════════════════════════════════════════
   MAIN
   ══════════════════════════════════════════════════════════ */
int main()
{
    cout << "===== Exception Handling in C++ =====\n\n";

    /* --- Basic try/catch/throw --- */
    cout << "--- 1. Basic try / catch / throw ---\n";
    try
    {
        divide(10, 2);
    }
    catch (const exception &e)
    {
        cout << e.what();
    }
    try
    {
        divide(10, 0);
    }
    catch (const exception &e)
    {
        cout << "Error: " << e.what() << "\n";
    }

    /* --- Multiple catch blocks --- */
    cout << "\n--- 2. Multiple Catch Blocks ---\n";
    for (int i = 0; i <= 6; i++)
    {
        cout << "Choice " << i << ": ";
        testMultipleCatch(i);
    }

    /* --- Custom Exceptions --- */
    cout << "\n--- 3. Custom Exception Classes ---\n";
    try
    {
        simulateDB(false);
    }
    catch (const AppException &e)
    {
        cout << e.what() << "\n";
    }

    try
    {
        simulateDB(true);
    }
    catch (const DatabaseException &e)
    {
        cout << e.what() << "\n";
        cout << "Error code: " << e.getCode() << "\n";
    }

    try
    {
        simulateNetwork(true);
    }
    catch (const NetworkException &e)
    {
        cout << e.what() << "\n";
    }
    catch (const AppException &e)
    { // parent catches if specific not matched
        cout << "[AppException] " << e.what() << "\n";
    }

    /* --- Constructor throwing --- */
    cout << "\n--- 4. Exception from Constructor ---\n";
    try
    {
        FileProcessor fp("data.csv");
        fp.process();
    }
    catch (const exception &e)
    {
        cout << "Error: " << e.what() << "\n";
    }
    try
    {
        FileProcessor fp(""); // will throw
        fp.process();
    }
    catch (const exception &e)
    {
        cout << "Error: " << e.what() << "\n";
    }

    /* --- Nested try + re-throw --- */
    cout << "\n--- 5. Nested Try + Re-throw ---\n";
    outerFunction();

    /* --- noexcept function --- */
    cout << "\n--- 6. noexcept function ---\n";
    try
    {
        cout << "sqrt(16) = " << safeSquareRoot(16) << "\n";
        cout << "sqrt(-4) = " << safeSquareRoot(-4.0) << "\n";
    }
    catch (const domain_error &e)
    {
        cout << "Math error: " << e.what() << "\n";
    }

    return 0;
}
