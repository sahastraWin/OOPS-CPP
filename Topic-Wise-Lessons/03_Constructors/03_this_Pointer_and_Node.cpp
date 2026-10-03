#include <bits/stdc++.h>
using namespace std;

class Node {
private:
    int data;
    Node *next;
public:
    Node(int data) {
        this->data = data;          // this->data is the member, data is the parameter
        this->next = nullptr;
    }
    int getData() { return data; }
    Node* getNext() { return next; }
    void setNext(Node *n) { next = n; }
};

int main() {
    Node *first = new Node(5);
    Node *second = new Node(10);
    first->setNext(second);         // link: 5 -> 10

    cout << first->getData() << " -> " << first->getNext()->getData() << endl;

    delete second;
    delete first;
    return 0;
}

/*
Output:
5 -> 10
*/
