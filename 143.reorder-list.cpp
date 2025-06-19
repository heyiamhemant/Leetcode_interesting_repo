/*
 * @lc app=leetcode id=143 lang=cpp
 *
 * [143] Reorder List
 *
 * https://leetcode.com/problems/reorder-list/description/
 *
 * algorithms
 * Medium (60.50%)
 * Likes:    11806
 * Dislikes: 460
 * Total Accepted:    1.3M
 * Total Submissions: 2M
 * Testcase Example:  '[1,2,3,4]'
 *
 * You are given the head of a singly linked-list. The list can be represented
 * as:
 * 
 * 
 * L0 → L1 → … → Ln - 1 → Ln
 * 
 * 
 * Reorder the list to be on the following form:
 * 
 * 
 * L0 → Ln → L1 → Ln - 1 → L2 → Ln - 2 → …
 * 
 * 
 * You may not modify the values in the list's nodes. Only nodes themselves may
 * be changed.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: head = [1,2,3,4]
 * Output: [1,4,2,3]
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: head = [1,2,3,4,5]
 * Output: [1,5,2,4,3]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * The number of nodes in the list is in the range [1, 5 * 10^4].
 * 1 <= Node.val <= 1000
 * 
 * 
 */

// @lc code=start
/**
 * Definition for singly-linked list.

 */
#include<iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
class Solution
{
public:
    /**
 * Definition for singly-linked list.*/
struct ListNode
     int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}
};
#include<iostream>
    using namespace std;
    class Solution
    {
    public:
        void reorderList(ListNode* head) {
            // Handle edge cases: empty list or single node
            if (!head || !head->next) return;
            
            // Step 1: Find the middle of the list using slow and fast pointers
            ListNode *slow = head, *fast = head, *prev = NULL;
            while (fast && fast->next) {
                fast = fast->next->next;
                prev = slow;
                slow = slow->next;
            }
            
            // Step 2: Split the list into two halves
            if (prev) prev->next = NULL; // Ensure prev is not null
            
            // Step 3: Reverse the second half
            ListNode *list2 = slow, *Next = NULL;
            prev = NULL;
            while (list2) {
                Next = list2->next;
                list2->next = prev;
                prev = list2;
                list2 = Next;
            }
            ListNode *head2 = prev; // Head of the reversed second half
            
            ListNode *curr = head; // Keep track of current node for appending
            while (head && head2) {
                ListNode *Next = head->next;   // Save next node of first list
                ListNode *Next2 = head2->next; // Save next node of second list
                head->next = head2;            // Link first list node to second list node
                head2->next = Next;            // Link second list node back to first list
                curr = head2;                  // Update curr to the last merged node
                head = Next;                   // Move to next node in first list
                head2 = Next2;                 // Move to next node in second list
            }
            
            // Step 5: Append any remaining nodes from head2
            if (head2) curr->next = head2;
        }
    };
// @lc code=end

