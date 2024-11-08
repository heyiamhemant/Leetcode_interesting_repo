/*
 * @lc app=leetcode id=141 lang=cpp
 *
 * [141] Linked List Cycle
 *
 * https://leetcode.com/problems/linked-list-cycle/description/
 *
 * algorithms
 * Easy (51.31%)
 * Likes:    15842
 * Dislikes: 1424
 * Total Accepted:    3.4M
 * Total Submissions: 6.6M
 * Testcase Example:  '[3,2,0,-4]\n1'
 *
 * Given head, the head of a linked list, determine if the linked list has a
 * cycle in it.
 * 
 * There is a cycle in a linked list if there is some node in the list that can
 * be reached again by continuously following the next pointer. Internally, pos
 * is used to denote the index of the node that tail's next pointer is
 * connected to. Note that pos is not passed as a parameter.
 * 
 * Return true if there is a cycle in the linked list. Otherwise, return
 * false.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: head = [3,2,0,-4], pos = 1
 * Output: true
 * Explanation: There is a cycle in the linked list, where the tail connects to
 * the 1st node (0-indexed).
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: head = [1,2], pos = 0
 * Output: true
 * Explanation: There is a cycle in the linked list, where the tail connects to
 * the 0th node.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: head = [1], pos = -1
 * Output: false
 * Explanation: There is no cycle in the linked list.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * The number of the nodes in the list is in the range [0, 10^4].
 * -10^5 <= Node.val <= 10^5
 * pos is -1 or a valid index in the linked-list.
 * 
 * 
 * 
 * Follow up: Can you solve it using O(1) (i.e. constant) memory?
 * 
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    /**
     * Given head, the head of a linked list, determine if the linked list
     * has a cycle in it. A cycle is defined as a node pointing back to a
     * previously traversed node.
     * 
     * This function uses the Floyd's cycle-finding algorithm, also known as
     * the "tortoise and the hare" algorithm. The algorithm works by having
     * two pointers, one that increments one step at a time and one that
     * increments two steps at a time. If there is a cycle, the two pointers
     * will eventually meet at the same node.
     * 
     * @param head the head of the linked list
     * @return true if there is a cycle, false if not
     */
    bool hasCycle(ListNode *head) {
        ListNode *slow = head;
        ListNode *fast = head;
        if(head == NULL  ||head->next == NULL)
            return false;
        while (fast && fast->next) { 
            slow = slow->next;
            fast = fast->next->next;
            if(fast == slow)
                return true;
        }
        return false;
    }
};
// @lc code=end

