/*
Given a list, rotate the list to the right by k places, where k is non-negative.
For example:
Given 1->2->3->4->5->NULL and k = 2,
return 4->5->1->2->3->NULL.

    ListNode* rotateRight(ListNode* head, int k);
*/

#include <iostream>

typedef struct ListNode {
    int val;
    struct ListNode *next;
}ListNode;

ListNode* rotateRight(ListNode* head, int k) {

    if (head == nullptr) {
        return head;
    }

    ListNode *oldHead, *newHead;
    oldHead = newHead = head;

    int tempk = k;

    auto temp = head;
    while (temp && k > 0) {
        temp = temp->next;
        k--;
    }

    // that means k is > len of list.
    if (temp == nullptr) {
        if (k == 0) { return oldHead; }
        k = tempk % (tempk - k);
        temp = oldHead = newHead = head;
        while (temp && k > 0) {
            temp = temp->next;
            k--;
        }
    }

    while (temp && temp->next != nullptr) {
        newHead = newHead->next;
        temp = temp->next;
    }

    auto toReturn = newHead->next;
    newHead->next = nullptr;
    temp->next = oldHead;
    return toReturn;
}


int main() {

    return 0;
}
