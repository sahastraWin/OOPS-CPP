/*
 * ============================================================
 *  TOPIC: Namespaces in C++
 * ============================================================
 *
 * Namespaces provide a way to AVOID NAME CONFLICTS when the
 * same identifier is defined in multiple places.
 *
 * Covered here:
 *   1. Defining and using namespaces
 *   2. Nested namespaces
 *   3. 'using' directive and 'using' declaration
 *   4. Anonymous (unnamed) namespace
 *   5. Namespace alias
 *   6. Inline namespace (C++11)
 *   7. Why 'using namespace std;' in global scope is bad practice
 *
 * ╔══════════════════════════════════════════════════════════╗
 *  INTERVIEW MUST-KNOW:
 *  - std is a namespace: cout, cin, endl, string, etc. all live in std.
 *  - 'using namespace std;' pulls ALL of std into global scope
 *    → risks name collision in large projects.
 *  - Prefer 'using std::cout;' (specific declaration) in headers.
 *  - Anonymous namespace = internal linkage (like static at file scope).
 *    Symbols only visible within that translation unit.
 *  - Namespace can be REOPENED across multiple files/locations.
 * ╚══════════════════════════════════════════════════════════╝
 */

#include <iostream>
#include <string>

/* Note: NOT using 'using namespace std;' globally — deliberate */

/* ══════════════════════════════════════════════════════════
   1. DEFINING A NAMESPACE
   ══════════════════════════════════════════════════════════ */

namespace Geometry
{
    const double PI = 3.14159265358979;

    double circleArea(double r) { return PI * r * r; }
    double circlePerim(double r) { return 2 * PI * r; }
    double rectArea(double l, double w) { return l * w; }

    class Point
    {
    public:
        double x, y;
        Point(double a, double b) : x(a), y(b) {}
        void display() const
        {
            std::cout << "Point(" << x << ", " << y << ")\n";
        }
    };
}

/* ══════════════════════════════════════════════════════════
   2. SAME NAME, DIFFERENT NAMESPACE — no conflict
   ══════════════════════════════════════════════════════════ */

namespace Physics
{
    /* PI here is a different entity from Geometry::PI */
    const double PI = 3.14159265358979;

    double kineticEnergy(double mass, double vel)
    {
        return 0.5 * mass * vel * vel;
    }

    double gravitationalPE(double mass, double height)
    {
        return mass * 9.8 * height;
    }

    void fun() { std::cout << "[Physics::fun]\n"; }
}

namespace Math
{
    void fun() { std::cout << "[Math::fun]\n"; }
    int square(int x) { return x * x; }
    int cube(int x) { return x * x * x; }
}

/* ══════════════════════════════════════════════════════════
   3. NAMESPACE CAN BE REOPENED (split across code)
   ══════════════════════════════════════════════════════════

   ╔══════════════════════════════════════════════════════════╗
    INTERVIEW TIP:
    This is how std namespace is defined across many headers.
    Each header adds to the std namespace.
   ╚══════════════════════════════════════════════════════════╝
*/

namespace Geometry
{
    /* Adding more functions to Geometry namespace */
    double triangleArea(double b, double h) { return 0.5 * b * h; }

    class Circle
    {
    private:
        double radius;

    public:
        Circle(double r) : radius(r) {}
        double area() const { return PI * radius * radius; }
        double perimeter() const { return 2 * PI * radius; }
        void display() const
        {
            std::cout << "Circle(r=" << radius
                      << " area=" << area() << ")\n";
        }
    };
}

/* ══════════════════════════════════════════════════════════
   4. NESTED NAMESPACES (C++17: namespace A::B::C {})
   ══════════════════════════════════════════════════════════ */

namespace Company
{
    namespace Engineering
    {
        namespace Backend
        {
            void deploy()
            {
                std::cout << "Company::Engineering::Backend::deploy()\n";
            }
            class API
            {
            public:
                void serve()
                {
                    std::cout << "Backend API serving request\n";
                }
            };
        }
        namespace Frontend
        {
            void render()
            {
                std::cout << "Company::Engineering::Frontend::render()\n";
            }
        }
    }
    namespace HR
    {
        void hire() { std::cout << "Company::HR::hire()\n"; }
    }
}

/* C++17 shorthand for nested namespace definition */
namespace Company::Engineering::DevOps
{
    void provision()
    {
        std::cout << "Company::Engineering::DevOps::provision()\n";
    }
}

/* ══════════════════════════════════════════════════════════
   5. ANONYMOUS (UNNAMED) NAMESPACE
   ══════════════════════════════════════════════════════════

   ╔══════════════════════════════════════════════════════════╗
    INTERVIEW MUST-KNOW:
    Anonymous namespace = symbols have INTERNAL LINKAGE.
    Only visible in this translation unit (this .cpp file).
    Replaces 'static' at file scope in modern C++.
    Avoids ODR (One Definition Rule) violations.
   ╚══════════════════════════════════════════════════════════╝
*/

namespace
{
    int internalCounter = 0; // only visible in this file

    void internalHelper()
    {
        ++internalCounter;
        std::cout << "Internal helper called " << internalCounter << " time(s)\n";
    }
}

/* ══════════════════════════════════════════════════════════
   6. NAMESPACE ALIAS
   ══════════════════════════════════════════════════════════ */

namespace CEBak = Company::Engineering::Backend; // alias for long name

/* ══════════════════════════════════════════════════════════
   MAIN
   ══════════════════════════════════════════════════════════ */
int main()
{
    std::cout << "===== Namespaces in C++ =====\n\n";

    /* --- Using :: to access namespace members --- */
    std::cout << "--- 1. Scope Resolution to Access Namespace ---\n";
    std::cout << "PI (Geometry): " << Geometry::PI << "\n";
    std::cout << "Circle area r=5: " << Geometry::circleArea(5.0) << "\n";
    std::cout << "Rect area 4x3: " << Geometry::rectArea(4.0, 3.0) << "\n";

    Geometry::Point pt(3, 4);
    pt.display();

    Geometry::Circle c(7.0);
    c.display();

    /* --- Physics namespace --- */
    std::cout << "\n--- 2. Different Namespaces, Same-Named Entities ---\n";
    std::cout << "KE(mass=10, vel=5) = " << Physics::kineticEnergy(10, 5) << " J\n";
    std::cout << "PE(mass=10, h=20)  = " << Physics::gravitationalPE(10, 20) << " J\n";

    /* Same function name, different namespaces — no conflict */
    Physics::fun();
    Math::fun();

    /* --- using declaration (specific) --- */
    std::cout << "\n--- 3. 'using' Declaration (specific import) ---\n";
    using Math::cube;
    using Math::square;
    std::cout << "square(7) = " << square(7) << "\n";
    std::cout << "cube(4)   = " << cube(4) << "\n";

    /* --- using directive (entire namespace) --- */
    std::cout << "\n--- 4. 'using namespace' Directive ---\n";
    {
        /* Limit scope of 'using namespace' to this block */
        using namespace Geometry;
        std::cout << "Triangle area (base=6, h=4) = " << triangleArea(6, 4) << "\n";
        Point p2(1, 2);
        p2.display();
    } // Geometry pulled in only within this block

    /* --- Nested Namespace --- */
    std::cout << "\n--- 5. Nested Namespaces ---\n";
    Company::Engineering::Backend::deploy();
    Company::Engineering::Frontend::render();
    Company::HR::hire();
    Company::Engineering::DevOps::provision();

    Company::Engineering::Backend::API api;
    api.serve();

    /* --- Namespace alias --- */
    std::cout << "\n--- 6. Namespace Alias ---\n";
    CEBak::deploy(); // same as Company::Engineering::Backend::deploy()
    CEBak::API api2;
    api2.serve();

    /* --- Anonymous namespace --- */
    std::cout << "\n--- 7. Anonymous Namespace ---\n";
    internalHelper();
    internalHelper();
    internalHelper();

    /* --- why 'using namespace std' globally is risky --- */
    std::cout << "\n--- 8. Why Avoid 'using namespace std' Globally ---\n";
    std::cout << "If you write 'using namespace std' globally and also\n";
    std::cout << "define 'void swap(int,int)' → CONFLICT with std::swap!\n";
    std::cout << "Prefer: 'using std::cout;' in cpp files, never in headers.\n";

    return 0;
}
