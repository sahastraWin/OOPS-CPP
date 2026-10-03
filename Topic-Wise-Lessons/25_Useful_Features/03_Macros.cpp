#include <bits/stdc++.h>
using namespace std;

/* Function-like macro: ALWAYS wrap every argument and the whole body in ( ) */
#define MAX(x, y) ((x) > (y) ? (x) : (y))

/* Define PI only if nobody defined it before */
#ifndef PI
    #define PI 3.1425
#endif

int main() {
    cout << PI << endl;
    cout << MAX(121, 125) << endl;
    return 0;
}

/*
📝 I named it MAX (upper case) because lower-case max can clash with std::max.
⚠️ Macros are plain text replacement (no type checking). Prefer const / inline / templates.

Output:
3.1425
125
*/
