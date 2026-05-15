// 89. Program for union
#include <bits/stdc++.h>
using namespace std;

union test1 {
    int x;
    int y;
} Test1;

union test2 {
    int x;
    char y;
} Test2;

union test3 {
    int arr[10];
    char y;
} Test3;

int main() {
    cout << "sizeof(test1) = " << sizeof(Test1) 
         << ", sizeof(test2) = " << sizeof(Test2) 
         << ", sizeof(test3) = " << sizeof(Test3) << "\n";
    
    return 0;
}
/*
TC: O(1) constant time
SC: O(1) constant space
*/
