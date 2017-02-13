/*
Write a program to find the node at which the intersection of two singly linked lists begins.


For example, the following two linked lists:

A:          a1 → a2
                   ↘
                     c1 → c2 → c3
                   ↗            
B:     b1 → b2 → b3
begin to intersect at node c1.


Notes:

If the two linked lists have no intersection at all, return null.
The linked lists must retain their original structure after the function returns.
You may assume there are no cycles anywhere in the entire linked structure.
Your code should preferably run in O(n) time and use only O(1) memory.

*/

//ListNode *getIntersectionNode(ListNode *headA, ListNode *headB);

ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    if (headA == nullptr || headB == nullptr) { return nullptr; }

    int lenA = 0, lenB = 0;
    auto temp = headA;
    while (temp) {
        temp = temp->next;
        lenA++;
    }
    
    temp = headB;
    while (temp) {
        temp = temp->next;
        lenB++;
    }

    int offset = (lenA - lenB);
    if (lenA < lenB) {
        offset = lenB - lenA;
        temp = headB;
        while (offset) {
            temp = temp->next;
            offset--;
        }
        headB = temp;
    } else {
        temp = headA;
        while (offset) {
            temp = temp->next;
            offset--;
        }
        headA = temp;
    }

    while (headA && headB && headA->val != headB->val) {
        headA = headA->next;
        headB = headB->next;
    }
    return headA;
}

