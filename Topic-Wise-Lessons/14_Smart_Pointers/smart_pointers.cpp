/*
 * ============================================================
 *  TOPIC: Smart Pointers & Pointer Pitfalls in C++
 * ============================================================
 *
 * Raw pointer problems:
 *   1. Uninitialized Pointers  — pointer holds garbage address
 *   2. Memory Leaks            — heap memory never freed
 *   3. Dangling Pointers       — pointer to freed memory
 *
 * Smart Pointers (C++11 — <memory> header) solve these automatically.
 * They wrap raw pointers and auto-delete on scope exit.
 *
 * Types:
 *   unique_ptr — exclusive ownership; one pointer per object
 *   shared_ptr — shared ownership; reference-counted
 *   weak_ptr   — non-owning observer; breaks circular references
 *
 * ╔══════════════════════════════════════════════════════════╗
 *  INTERVIEW MUST-KNOW:
 *  Smart pointers implement RAII — resource released when the
 *  pointer object goes out of scope.
 *  Prefer smart pointers over raw new/delete in modern C++.
 *
 *  unique_ptr: move-only (cannot be copied, only moved)
 *  shared_ptr: copies increment ref_count; dtor decrements.
 *              Object deleted when ref_count reaches 0.
 *  weak_ptr:   does NOT increment ref_count; use .lock() to
 *              get a temporary shared_ptr to access the object.
 * ╚══════════════════════════════════════════════════════════╝
 */

#include <iostream>
#include <memory> // unique_ptr, shared_ptr, weak_ptr
#include <string>
#include <vector>
using namespace std;

/* ══════════════════════════════════════════════════════════
   Helper class to visualise construction/destruction
   ══════════════════════════════════════════════════════════ */
class Resource
{
private:
    string label;
    int value;

public:
    Resource(string l, int v) : label(l), value(v)
    {
        cout << "[Resource CTOR] '" << label << "' value=" << value << "\n";
    }

    ~Resource()
    {
        cout << "[Resource DTOR] '" << label << "' cleaned up\n";
    }

    void use() const
    {
        cout << "Using resource '" << label << "' value=" << value << "\n";
    }

    int getValue() const { return value; }
};

/* ══════════════════════════════════════════════════════════
   1. RAW POINTER PITFALLS (demonstrated for understanding)
   ══════════════════════════════════════════════════════════ */

void rawPointerProblems()
{
    cout << "--- Raw Pointer Pitfalls ---\n";

    /* Problem 1: Uninitialized pointer */
    /*
     * int* p;
     * *p = 42;   // UNDEFINED BEHAVIOR — p points to garbage address
     */
    cout << "1. Uninitialized pointer: NEVER use before initializing.\n";
    int x = 10;
    int *p = &x; // safe: initialized to address of x
    cout << "   Safe init: *p = " << *p << "\n";

    /* Problem 2: Memory Leak */
    /*
     * int* q = new int[100];
     * q = nullptr;   // LEAK: heap block never freed!
     * // Should do: delete[] q; q = nullptr;
     */
    cout << "2. Memory Leak: always delete before nulling pointer.\n";
    int *q = new int[5];
    delete[] q; // proper cleanup
    q = nullptr;
    cout << "   Proper cleanup done.\n";

    /* Problem 3: Dangling Pointer */
    int *r = new int(99);
    cout << "3. Dangling pointer demo:\n";
    cout << "   Before delete: *r = " << *r << "\n";
    delete r;
    r = nullptr; // set to nullptr immediately after delete!
    /*
     * cout << *r;  // UNDEFINED BEHAVIOR if r not set to nullptr
     *              // With nullptr: at least you get a null-deref
     *              // signal, not silent corruption.
     */
    cout << "   After delete+nullptr: safe to check if(r) before use\n";
}

/* ══════════════════════════════════════════════════════════
   2. unique_ptr — exclusive ownership
   ══════════════════════════════════════════════════════════

   ╔══════════════════════════════════════════════════════════╗
    INTERVIEW MUST-KNOW: unique_ptr
    - Only ONE unique_ptr can own an object at a time.
    - CANNOT be copied (copy constructor/assignment deleted).
    - CAN be MOVED (ownership transferred).
    - When unique_ptr goes out of scope → object destroyed.
    - Use make_unique<T>() (C++14) — safer than new.
   ╚══════════════════════════════════════════════════════════╝
*/

void uniquePtrDemo()
{
    cout << "\n--- 2. unique_ptr ---\n";

    /* Creation */
    unique_ptr<Resource> p1 = make_unique<Resource>("Alpha", 10);
    p1->use();

    /* Transfer ownership via move */
    unique_ptr<Resource> p2 = move(p1); // p1 becomes nullptr
    cout << "p1 after move: " << (p1 ? "valid" : "null") << "\n";
    p2->use();

    /* unique_ptr with array */
    unique_ptr<int[]> arr = make_unique<int[]>(5);
    for (int i = 0; i < 5; i++)
        arr[i] = i * i;
    cout << "Array: ";
    for (int i = 0; i < 5; i++)
        cout << arr[i] << " ";
    cout << "\n";

    /* Custom deleter */
    auto customDeleter = [](Resource *r)
    {
        cout << "[Custom Deleter] freeing resource\n";
        delete r;
    };
    unique_ptr<Resource, decltype(customDeleter)>
        p3(new Resource("Beta", 20), customDeleter);
    p3->use();

    cout << "(p2 and p3 destroyed at end of scope)\n";
} // p2, p3 auto-destroyed here

/* ══════════════════════════════════════════════════════════
   3. shared_ptr — shared ownership with reference counting
   ══════════════════════════════════════════════════════════

   ╔══════════════════════════════════════════════════════════╗
    INTERVIEW MUST-KNOW: shared_ptr
    - Multiple shared_ptrs can point to the SAME object.
    - Maintains a REFERENCE COUNT (use_count()).
    - Object deleted when ref_count drops to 0.
    - Slightly more overhead than unique_ptr (atomic ref count).
    - Use make_shared<T>() — single allocation for object + control block.
   ╚══════════════════════════════════════════════════════════╝
*/

void sharedPtrDemo()
{
    cout << "\n--- 3. shared_ptr ---\n";

    shared_ptr<Resource> sp1 = make_shared<Resource>("Gamma", 30);
    cout << "sp1 use_count: " << sp1.use_count() << "\n";

    {
        shared_ptr<Resource> sp2 = sp1; // copies → ref_count = 2
        cout << "sp1 use_count after sp2 copy: " << sp1.use_count() << "\n";
        sp1->use();
        sp2->use();

        shared_ptr<Resource> sp3 = sp2; // ref_count = 3
        cout << "sp1 use_count after sp3 copy: " << sp1.use_count() << "\n";
    } // sp2, sp3 out of scope → ref_count = 1

    cout << "sp1 use_count after sp2,sp3 destroyed: " << sp1.use_count() << "\n";

    /* Storing in container */
    vector<shared_ptr<Resource>> resources;
    resources.push_back(make_shared<Resource>("Delta", 40));
    resources.push_back(sp1); // sp1 shared with vector
    cout << "sp1 use_count in vector: " << sp1.use_count() << "\n";
    resources.clear(); // vector releases shares
    cout << "sp1 use_count after vector clear: " << sp1.use_count() << "\n";

    cout << "(sp1 destroyed at end of scope)\n";
} // ref_count = 0 → Resource deleted

/* ══════════════════════════════════════════════════════════
   4. weak_ptr — non-owning observer
   ══════════════════════════════════════════════════════════

   ╔══════════════════════════════════════════════════════════╗
    INTERVIEW MUST-KNOW: weak_ptr
    - Does NOT increment reference count.
    - Does NOT prevent object from being deleted.
    - Used to BREAK CIRCULAR REFERENCES (which cause memory leaks
      even with shared_ptr because ref_count never reaches 0).
    - To access the object: call .lock() which returns a
      shared_ptr (empty if object already deleted).
    - Check if still valid: .expired() returns true if deleted.

    CIRCULAR REFERENCE EXAMPLE:
    If A holds shared_ptr<B> and B holds shared_ptr<A>:
      → ref_count of A and B never reach 0 → MEMORY LEAK.
    Fix: make one of them weak_ptr.
   ╚══════════════════════════════════════════════════════════╝
*/

struct Node
{
    int value;
    shared_ptr<Node> next; // OK for forward references
    weak_ptr<Node> prev;   // weak to avoid circular ref in doubly-linked

    Node(int v) : value(v)
    {
        cout << "[Node CTOR] value=" << v << "\n";
    }
    ~Node()
    {
        cout << "[Node DTOR] value=" << value << "\n";
    }
};

void weakPtrDemo()
{
    cout << "\n--- 4. weak_ptr ---\n";

    /* Basic weak_ptr usage */
    shared_ptr<Resource> sp = make_shared<Resource>("Epsilon", 50);
    weak_ptr<Resource> wp = sp; // does NOT increase ref_count

    cout << "sp use_count: " << sp.use_count() << " (wp doesn't add)\n";
    cout << "wp expired?   " << (wp.expired() ? "Yes" : "No") << "\n";

    /* Access via lock() */
    if (auto locked = wp.lock())
    { // lock() returns shared_ptr
        locked->use();
        cout << "Accessed via weak_ptr.lock()\n";
    }

    sp.reset(); // release ownership → Resource destroyed
    cout << "After sp.reset(), wp expired? " << (wp.expired() ? "Yes" : "No") << "\n";

    if (auto locked = wp.lock())
    {
        locked->use(); // this block won't run
    }
    else
    {
        cout << "Resource already gone — weak_ptr correctly reports expired\n";
    }

    /* Doubly-linked list with weak_ptr (no memory leak) */
    cout << "\n-- Doubly-linked list (weak_ptr for prev) --\n";
    auto n1 = make_shared<Node>(1);
    auto n2 = make_shared<Node>(2);
    auto n3 = make_shared<Node>(3);

    n1->next = n2;
    n2->prev = n1; // prev is weak
    n2->next = n3;
    n3->prev = n2;

    cout << "n1 use_count: " << n1.use_count() << "\n";
    cout << "n2 use_count: " << n2.use_count() << "\n";
    cout << "(nodes will be properly cleaned up)\n";
} // n1, n2, n3 properly destroyed — no circular reference issue

/* ══════════════════════════════════════════════════════════
   5. COMPARISON TABLE (printed as commentary)
   ══════════════════════════════════════════════════════════ */

void printComparison()
{
    cout << "\n--- Smart Pointer Comparison ---\n";
    cout << "+----------------+---------------+----------------+------------+\n";
    cout << "| Feature        | unique_ptr    | shared_ptr     | weak_ptr   |\n";
    cout << "+----------------+---------------+----------------+------------+\n";
    cout << "| Ownership      | Exclusive     | Shared         | None       |\n";
    cout << "| Ref Count      | No            | Yes            | No         |\n";
    cout << "| Copyable       | No (move only)| Yes            | Yes        |\n";
    cout << "| Overhead       | Minimal       | Ref count      | Minimal    |\n";
    cout << "| When to use    | Single owner  | Shared owner   | Observer   |\n";
    cout << "+----------------+---------------+----------------+------------+\n";
}

/* ══════════════════════════════════════════════════════════
   MAIN
   ══════════════════════════════════════════════════════════ */
int main()
{
    cout << "===== Smart Pointers & Pointer Pitfalls =====\n\n";

    rawPointerProblems();
    uniquePtrDemo();
    sharedPtrDemo();
    weakPtrDemo();
    printComparison();

    return 0;
}
