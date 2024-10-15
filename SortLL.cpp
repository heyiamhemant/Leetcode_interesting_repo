#include<iostream>

using namespace std;

class ListNode {
    public:
    int val;
    ListNode* next;
    ListNode(int val) {
        this->val = val;
        this->next = NULL;
    }
};

class Solution
{
    public : 
    void merge(ListNode* head1, ListNode* head2) {
        ListNode* h1 = head1;
        ListNode* h2 = head2;
        while(h1 && h2) {
            if (h1->val <= h2->val){
                h1 = h1->next;
            } else {
                // place h2 before h1
                ListNode* temp = h2->next;
                h2->next = h1;
                h2 = temp;
            }
        }
        // add remaining nodes of h2
        while(h2){
            ListNode* temp = h2->next;
            h1->next = h2;
            h1 = h1->next;
            h2 = temp;
        }
    }
    ListNode* findMid(ListNode* head) {
        ListNode* slow = head;.
        ListNode* fast = head;
        while(fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }
    void sortList(ListNode* head) {
        ListNode* mid = findMid(head);
        ListNode* head2 = mid->next;
        mid->next = NULL;
        sortList(head);
        sortList(head2);
        merge(head,head2);


        // find the mid of the linked list
        
        
    }
};