/*
 * ============================================================
 *  TOPIC: Inner (Nested) Classes in C++
 * ============================================================
 *
 * An inner class is a class defined INSIDE another class.
 * It is useful when the inner class is ONLY relevant to the
 * outer class and shouldn't be exposed globally.
 *
 * ╔══════════════════════════════════════════════════════════╗
 *  INTERVIEW MUST-KNOW:
 *  - Inner class can access STATIC members of outer class.
 *  - Inner class CANNOT directly access non-static members
 *    of outer class (needs an object reference).
 *  - Outer class CAN create objects of inner class.
 *  - Outer class can access only PUBLIC members of inner class.
 *  - Inner class acts as a separate class — has its own access
 *    specifiers, constructors, destructors, etc.
 *  - Object of inner class must be created AFTER its definition.
 *
 *  Common real-world uses:
 *    - Node class inside LinkedList
 *    - Iterator class inside a container
 *    - Builder pattern (inner Builder class)
 * ╚══════════════════════════════════════════════════════════╝
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

/* ══════════════════════════════════════════════════════════
   1. BASIC INNER CLASS
   ══════════════════════════════════════════════════════════ */

class Outer
{
private:
    int outerData;
    static int sharedCounter; // static — accessible by Inner

public:
    Outer(int d) : outerData(d) { ++sharedCounter; }

    /* Inner class defined inside Outer */
    class Inner
    {
    private:
        int innerData;

    public:
        Inner(int d) : innerData(d) {}

        void display() const
        {
            cout << "Inner data: " << innerData << "\n";
            /* Can access Outer's STATIC members */
            cout << "Outer shared counter: " << sharedCounter << "\n";
            /* Cannot directly access outerData (non-static) */
        }

        /* Access outer data via a passed reference */
        void displayWithOuter(const Outer &o) const
        {
            cout << "Inner=" << innerData
                 << " Outer=" << o.outerData << "\n";
        }
    };

    void useInner() const
    {
        Inner innerObj(42); // outer can create inner object
        innerObj.display();
        innerObj.displayWithOuter(*this);
    }

    static int getCounter() { return sharedCounter; }
};

int Outer::sharedCounter = 0;

/* ══════════════════════════════════════════════════════════
   2. PRACTICAL USE: Linked List with Inner Node class
   ══════════════════════════════════════════════════════════

   ╔══════════════════════════════════════════════════════════╗
    INTERVIEW TIP:
    Defining Node inside LinkedList keeps the implementation
    clean — users of LinkedList don't need to know about Node.
    It's a classic encapsulation of implementation detail.
   ╚══════════════════════════════════════════════════════════╝
*/

class LinkedList
{
private:
    /* Node is an inner class — implementation detail */
    struct Node
    {
        int data;
        Node *next;
        Node(int d) : data(d), next(nullptr) {}
    };

    Node *head;
    int size;

public:
    LinkedList() : head(nullptr), size(0) {}

    void pushFront(int val)
    {
        Node *newNode = new Node(val);
        newNode->next = head;
        head = newNode;
        ++size;
    }

    void pushBack(int val)
    {
        Node *newNode = new Node(val);
        if (!head)
        {
            head = newNode;
        }
        else
        {
            Node *cur = head;
            while (cur->next)
                cur = cur->next;
            cur->next = newNode;
        }
        ++size;
    }

    bool remove(int val)
    {
        if (!head)
            return false;
        if (head->data == val)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
            --size;
            return true;
        }
        Node *cur = head;
        while (cur->next && cur->next->data != val)
            cur = cur->next;
        if (!cur->next)
            return false;
        Node *temp = cur->next;
        cur->next = temp->next;
        delete temp;
        --size;
        return true;
    }

    void display() const
    {
        cout << "List[" << size << "]: ";
        Node *cur = head;
        while (cur)
        {
            cout << cur->data;
            if (cur->next)
                cout << " -> ";
            cur = cur->next;
        }
        cout << "\n";
    }

    int getSize() const { return size; }

    ~LinkedList()
    {
        Node *cur = head;
        while (cur)
        {
            Node *next = cur->next;
            delete cur;
            cur = next;
        }
    }
};

/* ══════════════════════════════════════════════════════════
   3. INNER CLASS — Builder Pattern
   ══════════════════════════════════════════════════════════

   ╔══════════════════════════════════════════════════════════╗
    INTERVIEW TIP: Builder Pattern is very common in interviews.
    - Used when an object has many optional parameters.
    - Avoids "telescoping constructor" anti-pattern.
    - Inner Builder class constructs the outer Product object.
    - Popular in Java, but applicable in C++ too.
   ╚══════════════════════════════════════════════════════════╝
*/

class HTTPRequest
{
private:
    string method;
    string url;
    string body;
    int timeout;
    bool ssl;

    /* Private constructor — only Builder can create */
    HTTPRequest(string m, string u, string b, int t, bool s)
        : method(m), url(u), body(b), timeout(t), ssl(s) {}

public:
    void display() const
    {
        cout << (ssl ? "https" : "http") << "://"
             << url << " [" << method << "]"
             << " timeout=" << timeout << "s"
             << " body=" << (body.empty() ? "(none)" : body) << "\n";
    }

    /* Inner Builder class */
    class Builder
    {
    private:
        string method = "GET";
        string url = "";
        string body = "";
        int timeout = 30;
        bool ssl = true;

    public:
        Builder &setMethod(string m)
        {
            method = m;
            return *this;
        }
        Builder &setURL(string u)
        {
            url = u;
            return *this;
        }
        Builder &setBody(string b)
        {
            body = b;
            return *this;
        }
        Builder &setTimeout(int t)
        {
            timeout = t;
            return *this;
        }
        Builder &setSSL(bool s)
        {
            ssl = s;
            return *this;
        }

        /* Build returns the outer class object */
        HTTPRequest build() const
        {
            return HTTPRequest(method, url, body, timeout, ssl);
        }
    };
};

/* ══════════════════════════════════════════════════════════
   MAIN
   ══════════════════════════════════════════════════════════ */
int main()
{
    cout << "===== Inner (Nested) Classes =====\n\n";

    /* --- Basic Inner Class --- */
    cout << "--- 1. Basic Inner Class ---\n";
    Outer o1(10), o2(20);
    cout << "Outer counter: " << Outer::getCounter() << "\n";
    o1.useInner();

    /* Using inner class from outside */
    Outer::Inner inner(99);
    inner.display();
    inner.displayWithOuter(o2);

    /* --- Linked List (Node inner class hidden) --- */
    cout << "\n--- 2. Linked List with Inner Node ---\n";
    LinkedList list;
    list.pushBack(10);
    list.pushBack(20);
    list.pushBack(30);
    list.pushFront(5);
    list.display();

    list.remove(20);
    list.display();

    list.remove(5);
    list.display();

    /* --- Builder Pattern --- */
    cout << "\n--- 3. Builder Pattern (Inner Builder) ---\n";
    HTTPRequest req = HTTPRequest::Builder()
                          .setMethod("POST")
                          .setURL("api.example.com/users")
                          .setBody("{\"name\":\"Alice\"}")
                          .setTimeout(10)
                          .setSSL(true)
                          .build();
    req.display();

    HTTPRequest getReq = HTTPRequest::Builder()
                             .setURL("api.example.com/users/1")
                             .build();
    getReq.display();

    return 0;
}
