// Program to illustrate inline function
#include <bits/stdc++.h>
using namespace std;
inline int max(int a, int b)
{
    return (a > b) ? a : b;
}
int main()
{
    int x, y;
    x = 5;
    y = 10;
    int result = max(x, y); // inline expansion
    cout<<result;
    return 0;
}
