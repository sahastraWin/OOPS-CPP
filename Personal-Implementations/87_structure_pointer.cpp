// 87. Program for structure pointer
#include <bits/stdc++.h>
using namespace std;

struct item {
    string itemName;
    int qty;
    float price;
    float amount;
};

int main() {
    item itm;
    item *pItem = &itm;
    
    cout << "Enter product name: ";
    getline(cin, pItem->itemName);
    
    cout << "Enter price: ";
    cin >> pItem->price;
    
    cout << "Enter quantity: ";
    cin >> pItem->qty;
    
    pItem->amount = (float)pItem->qty * pItem->price;
    
    cout << "\nName: " << pItem->itemName << "\n";
    cout << "Price: " << pItem->price << "\n";
    cout << "Quantity: " << pItem->qty << "\n";
    cout << "Total Amount: " << pItem->amount << "\n";
    
    return 0;
}
/*
TC: O(1) constant time
SC: O(1) constant space
*/
