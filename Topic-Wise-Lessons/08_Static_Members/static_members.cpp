/*
 * ============================================================
 *  TOPIC: Static Data Members and Static Member Functions
 * ============================================================
 *
 * ╔══════════════════════════════════════════════════════════╗
 *  INTERVIEW MUST-KNOW: Static Members
 *
 *  Static Data Members:
 *  - Belong to the CLASS, not to any specific object.
 *  - ONE copy shared across ALL objects of the class.
 *  - Exist even BEFORE any object is created.
 *  - Must be DEFINED (not just declared) outside the class
 *    (exception: constexpr static can be defined inline in C++17).
 *  - Initialised before main() starts.
 *  - Access: ClassName::member  OR  object.member (not recommended).
 *
 *  Static Member Functions:
 *  - Belong to the CLASS, not to any object.
 *  - Can be called WITHOUT creating an object: ClassName::func()
 *  - Do NOT have a 'this' pointer.
 *  - Can access ONLY static data members and other static functions.
 *  - Cannot be const, volatile (no object context to be const of).
 *  - Cannot be virtual (no vtable for class-level functions).
 * ╚══════════════════════════════════════════════════════════╝
 */

#include <iostream>
#include <string>
using namespace std;

/* ══════════════════════════════════════════════════════════
   1. STATIC DATA MEMBER — Object Counter
   ══════════════════════════════════════════════════════════ */

class Employee
{
private:
    string name;
    int id;

    /*
     * ╔══════════════════════════════════════════════════╗
     *  'count' is a static member:
     *  - Declared inside the class.
     *  - Must be DEFINED outside the class body.
     *  - Shared by all Employee objects.
     * ╚══════════════════════════════════════════════════╝
     */
    static int count; // declaration only

public:
    Employee(string n) : name(n)
    {
        id = ++count; // auto-assign unique ID
        cout << "[Employee] Created: " << name << " (id=" << id << ")\n";
    }

    ~Employee()
    {
        --count;
        cout << "[Employee] Destroyed: " << name << "\n";
    }

    /* Static member function — can access 'count' (static) */
    static int getCount() { return count; }

    void display() const
    {
        cout << "Employee(id=" << id << ", name=" << name
             << ", total_employees=" << count << ")\n";
    }
};

/* DEFINITION of static member — exactly once, outside class */
int Employee::count = 0;

/* ══════════════════════════════════════════════════════════
   2. STATIC MEMBER — Singleton Pattern
   ══════════════════════════════════════════════════════════

   ╔══════════════════════════════════════════════════════════╗
    INTERVIEW MUST-KNOW: Singleton uses static member to
    ensure only ONE instance of a class exists.
    Common use cases: Logger, Config, Database connection pool.
   ╚══════════════════════════════════════════════════════════╝
*/

class Logger
{
private:
    static Logger *instance; // single instance pointer
    string logFile;
    int logCount;

    /* Private constructor prevents external instantiation */
    Logger(string file) : logFile(file), logCount(0)
    {
        cout << "[Logger] Initialised with file: " << file << "\n";
    }

public:
    /* Prevent copy and assignment */
    Logger(const Logger &) = delete;
    Logger &operator=(const Logger &) = delete;

    /* Static factory method */
    static Logger *getInstance(string file = "app.log")
    {
        if (instance == nullptr)
        {
            instance = new Logger(file); // created only once
        }
        return instance;
    }

    void log(const string &msg)
    {
        ++logCount;
        cout << "[LOG #" << logCount << "] " << msg << "\n";
    }

    static void destroyInstance()
    {
        delete instance;
        instance = nullptr;
        cout << "[Logger] Instance destroyed.\n";
    }
};

Logger *Logger::instance = nullptr; // definition outside class

/* ══════════════════════════════════════════════════════════
   3. STATIC MEMBER — Class-level constant / shared config
   ══════════════════════════════════════════════════════════ */

class Circle
{
private:
    double radius;

public:
    /*
     * ╔══════════════════════════════════════════════════╗
     *  C++17: constexpr static can be defined INLINE.
     *  Prior to C++17: must define outside: double Circle::PI = 3.14159;
     * ╚══════════════════════════════════════════════════╝
     */
    static constexpr double PI = 3.14159265358979;

    Circle(double r) : radius(r) {}

    double area() const { return PI * radius * radius; }
    double circumference() const { return 2 * PI * radius; }

    /* Static utility — doesn't need any object */
    static double areaFromRadius(double r) { return PI * r * r; }
};

/* ══════════════════════════════════════════════════════════
   4. STATIC vs NON-STATIC member function summary demo
   ══════════════════════════════════════════════════════════ */

class BankAccount
{
private:
    double balance;
    static double interestRate; // same rate for all accounts
    static int totalAccounts;

public:
    BankAccount(double initialBalance) : balance(initialBalance)
    {
        ++totalAccounts;
    }

    ~BankAccount() { --totalAccounts; }

    /* Non-static: operates on a specific object */
    void applyInterest()
    {
        balance += balance * interestRate;
    }

    double getBalance() const { return balance; }

    /* Static: class-level operation */
    static void setInterestRate(double rate)
    {
        interestRate = rate; // changes for ALL accounts
    }

    static double getInterestRate() { return interestRate; }
    static int getTotalAccounts() { return totalAccounts; }

    /*
     * ╔══════════════════════════════════════════════════╗
     *  INTERVIEW TIP:
     *  Static function CANNOT use 'this':
     *      void foo() { this->balance = 0; }  // OK if non-static
     *      static void bar() { this->balance; } // COMPILE ERROR
     * ╚══════════════════════════════════════════════════╝
     */
};

double BankAccount::interestRate = 0.05; // 5% default
int BankAccount::totalAccounts = 0;

/* ══════════════════════════════════════════════════════════
   MAIN
   ══════════════════════════════════════════════════════════ */
int main()
{
    cout << "===== Static Members in C++ =====\n\n";

    /* --- Object Counter --- */
    cout << "--- 1. Static Object Counter ---\n";
    cout << "Employees before creation: " << Employee::getCount() << "\n";
    {
        Employee e1("Alice");
        Employee e2("Bob");
        Employee e3("Charlie");
        cout << "Employees in scope: " << Employee::getCount() << "\n";
        e1.display();
    } // e1, e2, e3 destroyed here
    cout << "Employees after scope: " << Employee::getCount() << "\n";

    /* --- Singleton --- */
    cout << "\n--- 2. Singleton Logger ---\n";
    Logger *log1 = Logger::getInstance("debug.log");
    Logger *log2 = Logger::getInstance(); // returns SAME instance

    cout << "Same instance? " << (log1 == log2 ? "YES" : "NO") << "\n";
    log1->log("Application started");
    log2->log("User logged in");
    Logger::destroyInstance();

    /* --- Static Constant --- */
    cout << "\n--- 3. Static Constant (Circle::PI) ---\n";
    Circle c(5.0);
    cout << "PI = " << Circle::PI << "\n";
    cout << "Circle area = " << c.area() << "\n";
    cout << "Static utility area(7) = " << Circle::areaFromRadius(7.0) << "\n";

    /* --- Bank Account --- */
    cout << "\n--- 4. Static Interest Rate (shared) ---\n";
    BankAccount a1(1000), a2(2000), a3(5000);
    cout << "Total accounts: " << BankAccount::getTotalAccounts() << "\n";
    cout << "Interest rate: " << BankAccount::getInterestRate() << "\n";

    a1.applyInterest();
    a2.applyInterest();
    cout << "a1 balance after interest: " << a1.getBalance() << "\n";
    cout << "a2 balance after interest: " << a2.getBalance() << "\n";

    BankAccount::setInterestRate(0.08); // 8% now for ALL accounts
    cout << "\nChanged rate to 8%\n";
    a3.applyInterest();
    cout << "a3 balance after 8% interest: " << a3.getBalance() << "\n";

    return 0;
}
