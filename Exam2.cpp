#include <iostream>
using namespace std;
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};
Node* mergeSortedLists(Node* list1, Node* list2) {
    Node* dummy = new Node(0);
    Node* tail = dummy;
    while (list1 != nullptr && list2 != nullptr) {
        if (list1->data <= list2->data) {
            tail->next = list1;
            list1 = list1->next; 
        } else {
            tail->next = list2;
            list2 = list2->next;
        }
        tail = tail->next;
    }
    if (list1 != nullptr) {
        tail->next = list1;
    }
    if (list2 != nullptr) {
        tail->next = list2;
    }
    Node* mergedHead = dummy->next;
    delete dummy;
    return mergedHead;
}
void printL(Node* head) {
    while (head != nullptr) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}
Node* createNode(int data) {
    return new Node(data);
}

int main() {
    Node* list1 = createNode(1);
    list1->next = createNode(3);
    list1->next->next = createNode(5);
    Node* list2 = createNode(2);
    list2->next = createNode(4);
    list2->next->next = createNode(6);
    Node* mergedList = mergeSortedLists(list1, list2);
    cout << "Merged sorted linked list: ";
    printL(mergedList);

    return 0;
}
