// 90. Program for union pointer
#include <bits/stdc++.h>
using namespace std;

union test {
    int x;
    char y;
};

int main() {
    test p1;
    p1.x = 65;
    
    test* p2 = &p1;
    
    cout << p2->x << " " << p2->y << "\n";
    return 0;
}
/*
TC: O(1) constant time
SC: O(1) constant space
*/
