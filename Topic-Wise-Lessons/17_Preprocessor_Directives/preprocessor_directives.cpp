/*
 * ============================================================
 *  TOPIC: Preprocessor Directives (Macros) in C++
 * ============================================================
 *
 * Preprocessor directives are processed BEFORE compilation.
 * They start with '#' and are NOT C++ statements.
 *
 * Covered here:
 *   1. #define — object-like macros
 *   2. #define — function-like macros
 *   3. #undef
 *   4. #ifdef / #ifndef / #endif — conditional compilation
 *   5. #if / #elif / #else
 *   6. Stringification (#) and token pasting (##)
 *   7. Predefined macros
 *   8. Include guards
 *
 * ╔══════════════════════════════════════════════════════════╗
 *  INTERVIEW MUST-KNOW:
 *  - Preprocessor runs BEFORE the compiler.
 *  - #define does TEXT SUBSTITUTION — no type checking!
 *  - Macros have NO scope (unlike functions/variables).
 *  - Prefer 'const' and 'constexpr' over #define for constants.
 *  - Prefer inline functions over function-like macros.
 *  - But macros are still essential for:
 *      → Include guards (#ifndef HEADER_H)
 *      → Conditional compilation (#ifdef DEBUG)
 *      → Platform-specific code
 *      → Stringification and token pasting
 * ╚══════════════════════════════════════════════════════════╝
 */

#include <iostream>
#include <string>
using namespace std;

/* ══════════════════════════════════════════════════════════
   1. OBJECT-LIKE MACROS (#define constant)
   ══════════════════════════════════════════════════════════ */

#define PI 3.14159265358979
#define MAX_USERS 100
#define APP_NAME "MyApplication"
#define NEWLINE '\n'

/*
 * ╔══════════════════════════════════════════════════════════╗
 *  INTERVIEW TIP: Problems with #define constants
 *  - No type safety: PI could be used as any type
 *  - No scope: visible everywhere after the #define
 *  - No debugger symbol: shows as raw value in debugger
 *  - Replacement is blind text substitution before compilation
 *  PREFER: constexpr double PI = 3.14159...;
 * ╚══════════════════════════════════════════════════════════╝
 */

/* ══════════════════════════════════════════════════════════
   2. FUNCTION-LIKE MACROS
   ══════════════════════════════════════════════════════════

   ╔══════════════════════════════════════════════════════════╗
    INTERVIEW MUST-KNOW: Macro pitfalls
    SQUARE(x+1) expands to: (x+1)*(x+1) — OK with parentheses
    Without parentheses: x+1*x+1 = 2x+1 — WRONG!
    Always parenthesize EVERY argument and the whole expression.
    Also: macro side effects with ++ are dangerous:
    MAX(a++, b++) may increment twice — undefined behavior.
    PREFER: inline functions or constexpr functions.
   ╚══════════════════════════════════════════════════════════╝
*/

/* Safe macro: parentheses around args AND whole expression */
#define SQUARE(x) ((x) * (x))
#define CUBE(x) ((x) * (x) * (x))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define ABS(x) ((x) < 0 ? -(x) : (x))
#define CLAMP(x, lo, hi) ((x) < (lo) ? (lo) : ((x) > (hi) ? (hi) : (x)))

/* ══════════════════════════════════════════════════════════
   3. STRINGIFICATION (#) and TOKEN PASTING (##)
   ══════════════════════════════════════════════════════════

   ╔══════════════════════════════════════════════════════════╗
    INTERVIEW TIP:
    #  in a macro converts the argument to a string literal.
    ## in a macro concatenates two tokens.
    These are powerful for generating code and debug macros.
   ╚══════════════════════════════════════════════════════════╝
*/

/* # turns argument into a string */
#define STRINGIFY(x) #x
#define TO_STRING(x) STRINGIFY(x)

/* ## concatenates tokens */
#define CONCAT(a, b) a##b

/* Debug macro: print variable name and value */
#define DEBUG_VAR(var) \
    cout << "[DEBUG] " << #var << " = " << (var) << "\n"

/* Assert-like macro */
#define MY_ASSERT(cond)                                        \
    if (!(cond))                                               \
    {                                                          \
        cerr << "ASSERTION FAILED: " << #cond                  \
             << " at " << __FILE__ << ":" << __LINE__ << "\n"; \
    }

/* Logging macro with file + line info */
#define LOG(msg) \
    cout << "[LOG " << __FILE__ << ":" << __LINE__ << "] " << msg << "\n"

/* ══════════════════════════════════════════════════════════
   4. CONDITIONAL COMPILATION (#ifdef / #ifndef)
   ══════════════════════════════════════════════════════════

   ╔══════════════════════════════════════════════════════════╗
    INTERVIEW MUST-KNOW:
    Conditional compilation lets you include/exclude code
    based on defined macros. Common uses:
    - Debug vs Release builds
    - Platform-specific code (Windows vs Linux)
    - Feature flags
    - Include guards (prevent double inclusion of headers)
   ╚══════════════════════════════════════════════════════════╝
*/

/* Toggle this to switch between debug and release behaviour */
#define DEBUG_MODE /* Comment this out for release build */

#ifdef DEBUG_MODE
#define DLOG(msg) cout << "[DEBUG] " << msg << "\n"
#else
#define DLOG(msg) /* empty — stripped out in release */
#endif

/* Platform detection */
#ifdef _WIN32
#define PLATFORM "Windows"
#elif defined(__APPLE__)
#define PLATFORM "macOS"
#elif defined(__linux__)
#define PLATFORM "Linux"
#else
#define PLATFORM "Unknown"
#endif

/* #ifndef — "if not defined" */
#ifndef MAX_BUFFER_SIZE
#define MAX_BUFFER_SIZE 1024 // default, only if not already defined
#endif

/* #undef — remove a macro definition */
#define TEMP_MACRO 42
// ... use TEMP_MACRO ...
#undef TEMP_MACRO
// TEMP_MACRO is now undefined

/* ══════════════════════════════════════════════════════════
   5. INCLUDE GUARD PATTERN
   (simulated here — normally in header files)
   ══════════════════════════════════════════════════════════

   ╔══════════════════════════════════════════════════════════╗
    INTERVIEW MUST-KNOW: Include Guards
    Every .h file should start with:
        #ifndef MY_HEADER_H
        #define MY_HEADER_H
        // ... header content ...
        #endif // MY_HEADER_H

    OR use the modern (non-standard but universally supported):
        #pragma once

    Purpose: Prevent multiple inclusion of the same header,
    which would cause "redefinition" compiler errors.
    'pragma once' is simpler; include guards are more portable.
   ╚══════════════════════════════════════════════════════════╝
*/

/* Simulated include guard effect */
#ifndef MYCLASS_DEFINED
#define MYCLASS_DEFINED

class MyClass
{
public:
    int value;
    MyClass(int v) : value(v) {}
    void display() const { cout << "MyClass(" << value << ")\n"; }
};

#endif // MYCLASS_DEFINED

/* ══════════════════════════════════════════════════════════
   6. PREDEFINED MACROS
   ══════════════════════════════════════════════════════════

   ╔══════════════════════════════════════════════════════════╗
    INTERVIEW TIP: Predefined macros (always available):
    __FILE__    → current source file name (string)
    __LINE__    → current line number (integer)
    __func__    → current function name (C99/C++11)
    __DATE__    → compilation date "Mmm dd yyyy"
    __TIME__    → compilation time "hh:mm:ss"
    __cplusplus → C++ version: 201103 (C++11), 201402 (C++14), etc.
   ╚══════════════════════════════════════════════════════════╝
*/

void showPredefinedMacros()
{
    cout << "--- Predefined Macros ---\n";
    cout << "__FILE__    : " << __FILE__ << "\n";
    cout << "__LINE__    : " << __LINE__ << "\n";
    cout << "__func__    : " << __func__ << "\n";
    cout << "__DATE__    : " << __DATE__ << "\n";
    cout << "__TIME__    : " << __TIME__ << "\n";
    cout << "__cplusplus : " << __cplusplus << "\n";
    cout << "PLATFORM    : " << PLATFORM << "\n";
}

/* ══════════════════════════════════════════════════════════
   MAIN
   ══════════════════════════════════════════════════════════ */
int main()
{
    cout << "===== Preprocessor Directives =====\n\n";

    /* --- Object-like macros --- */
    cout << "--- 1. Object-like Macros ---\n";
    cout << "PI         = " << PI << "\n";
    cout << "MAX_USERS  = " << MAX_USERS << "\n";
    cout << "APP_NAME   = " << APP_NAME << "\n";
    cout << "MAX_BUFFER = " << MAX_BUFFER_SIZE << "\n";

    /* --- Function-like macros --- */
    cout << "\n--- 2. Function-like Macros ---\n";
    int a = 5, b = 3;
    cout << "SQUARE(5)     = " << SQUARE(5) << "\n";
    cout << "SQUARE(a+1)   = " << SQUARE(a + 1) << "\n"; // safe: ((a+1)*(a+1))
    cout << "CUBE(3)       = " << CUBE(3) << "\n";
    cout << "MAX(5,3)      = " << MAX(5, 3) << "\n";
    cout << "MIN(5,3)      = " << MIN(5, 3) << "\n";
    cout << "ABS(-7)       = " << ABS(-7) << "\n";
    cout << "CLAMP(15,0,10)= " << CLAMP(15, 0, 10) << "\n";

    /* --- Stringification & Token Pasting --- */
    cout << "\n--- 3. Stringification and Token Pasting ---\n";
    cout << "STRINGIFY(hello)  = " << STRINGIFY(hello) << "\n";
    cout << "TO_STRING(PI)     = " << TO_STRING(PI) << "\n";

    int CONCAT(my, Var) = 42; // creates variable 'myVar'
    cout << "CONCAT(my, Var) = myVar = " << myVar << "\n";

    int temperature = -15;
    DEBUG_VAR(temperature);
    DEBUG_VAR(a + b);

    MY_ASSERT(a > b); // passes
    MY_ASSERT(a < b); // fails — prints error info

    LOG("Application starting up");

    /* --- Conditional Compilation --- */
    cout << "\n--- 4. Conditional Compilation ---\n";
    DLOG("This is a debug message"); // visible when DEBUG_MODE defined
    cout << "Build mode: " <<
#ifdef DEBUG_MODE
        "DEBUG"
#else
        "RELEASE"
#endif
         << "\n";

    /* --- MyClass (include guard demo) --- */
    cout << "\n--- 5. Include Guard (Prevents Redefinition) ---\n";
    MyClass mc(99);
    mc.display();

    /* --- Predefined Macros --- */
    cout << "\n";
    showPredefinedMacros();

    return 0;
}
