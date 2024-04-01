#include <bits/stdc++.h>
#define db1(x) cerr<<#x<<"="<<x<<'\n'
#define db2(x,y) cerr<<#x<<"="<<x<<","<<#y<<"="<<y<<'\n'
#define db3(x,y,z) cerr<<#x<<"="<<x<<","<<#y<<"="<<y<<","<<#z<<"="<<z<<'\n'
#define rep(i,n) for(ListNode i=0;i<(n);++i)
#define repA(i,a,n) for(ListNode i=a;i<=(n);++i)
#define repD(i,a,n) for(ListNode i=a;i>=(n);--i)
#define mp make_pair
#define sp <<' '<<
#define pb push_back
#define FastIO ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
using namespace std;
using ListNode = long long;
class ListNode {
    int val;
    ListNode *next;
    ListNode(int num){
        val = num;
        next = NULL;
    }
}
ListNode* findMid(ListNode* head, ListNode* end){
    if(!head || head == end)
        return NULL;
    ListNode *fast = head;
    ListNode *slow = head;
    while(fast && fast->next && fast != end && fast->next != end) {
        slow = slow->next;
        if(fast->next && fast->next != end)
            fast = fast->next->next;
    }
    return slow;
}
ListNode* findEnd(ListNode * head){
    if (!head)
        return NULL;
    while(!head->next){
        head = head->next;
    }
    return head;
}
void mergeSort(ListNode *head , ListNode * end) {
    if (head && end && head != end){
        ListNode *mid = findMid(head, end);
        mergeSort(head, mid);
        mergeSort(mid->next, end);
        merge(head, mid, end);
    }

}
void merge(ListNode * head , ListNode* mid, ListNode * end){
    ListNode* l1 = head;
    ListNode* l1_prev = head
    ListNode* l2_prev = mid;
    ListNode* l2 = mid->next;
    while(l1 != mid && l2 != end){
        if (l1->val <= l2->val){
            l1_prev = l1;
            l1 = l1->next;
        } else {
            // insert and move the pointers
            temp = l1;
            l1 = l2;
            l2_prev->next = l2->next;
            l1->next = temp->next;
            temp->next = l1;
        }
    }
    while(l2!=end){
        l1_prev->next = l2;
        l2 = l2->next;
        l1_prev = l1_prev->next;
    }
}
ListNode* SortList(ListNode * head){
    ListNode *end = findEnd(head);
    mergeSort(head, end);
    return head;
}
int main()
{
    FastIO
    ListNode t;
    cin>>t;
    while(t--){
        ListNode n;
        cin>>n;
        vector<ListNode*> v(n);
        rep(i,n) cin>>v[i];
        sort(v[i])
    
        cout<<'\n';
    }
    return 0;
}