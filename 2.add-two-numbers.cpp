/*
 * @lc app=leetcode id=2 lang=cpp
 *
 * [2] Add Two Numbers
 *
 * https://leetcode.com/problems/add-two-numbers/description/
 *
 * algorithms
 * Medium (44.32%)
 * Likes:    31852
 * Dislikes: 6393
 * Total Accepted:    5.1M
 * Total Submissions: 11.4M
 * Testcase Example:  '[2,4,3]\n[5,6,4]'
 *
 * You are given two non-empty linked lists representing two non-negative
 * integers. The digits are stored in reverse order, and each of their nodes
 * contains a single digit. Add the two numbers and return the sum as a linked
 * list.
 * 
 * You may assume the two numbers do not contain any leading zero, except the
 * number 0 itself.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: l1 = [2,4,3], l2 = [5,6,4]
 * Output: [7,0,8]
 * Explanation: 342 + 465 = 807.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: l1 = [0], l2 = [0]
 * Output: [0]
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: l1 = [9,9,9,9,9,9,9], l2 = [9,9,9,9]
 * Output: [8,9,9,9,0,0,0,1]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * The number of nodes in each linked list is in the range [1, 100].
 * 0 <= Node.val <= 9
 * It is guaranteed that the list represents a number that does not have
 * leading zeros.
 * 
 * 
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int sum = 0;
        int carry = 0;
        ListNode *head = l1;
        ListNode *h1 = l1;
        ListNode *prev = nullptr;
        ListNode *h2 = l2;
        while (h1 && h2) {
            sum = h1->val + h2->val + carry;
            carry = sum / 10;
            sum = sum % 10;
            cout << sum << " " << carry << endl;
            h1->val = sum;
            prev = h1;
            h1 = h1->next;
            h2 = h2->next;
        }
        while(h2) {
            sum = h2->val + carry;
            carry = sum / 10;
            sum = sum % 10;
            cout << sum << " " << carry << endl;
            prev->next = new ListNode(sum);
            prev = prev->next;
            h2 = h2->next;
        }
        while(h1) {
            sum = h1->val + carry;
            carry = sum / 10;
            sum = sum % 10;
            h1->val = sum;
            prev = h1;
            h1 = h1->next;
        }
        if(carry && prev)
            prev->next = new ListNode(carry);
        return head;
    }
};
// @lc code=end

