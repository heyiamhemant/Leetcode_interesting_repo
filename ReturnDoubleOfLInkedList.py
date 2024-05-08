"""2816. Double a Number Represented as a Linked List
Solved
Medium

Topics
Companies

Hint
You are given the head of a non-empty linked list representing a non-negative integer without leading zeroes.

Return the head of the linked list after doubling it.

 

Example 1:


Input: head = [1,8,9]
Output: [3,7,8]
Explanation: The figure above corresponds to the given linked list which represents the number 189. Hence, the returned linked list represents the number 189 * 2 = 378.
Example 2:


Input: head = [9,9,9]
Output: [1,9,9,8]
Explanation: The figure above corresponds to the given linked list which represents the number 999. Hence, the returned linked list reprersents the number 999 * 2 = 1998. 
 

Constraints:

The number of nodes in the list is in the range [1, 104]
0 <= Node.val <= 9
The input is generated such that the list represents a number that does not have leading zeros, except the number 0 itself."""


# Definition for singly-linked list.
# class ListNode:
#     def __init__(self, val=0, next=None):
#         self.val = val
#         self.next = next
class Solution:
    def doubleIt(self, head: Optional[ListNode]) -> Optional[ListNode]:
        node = head
        stack = []
        while node:
            stack.append(node)
            node = node.next

        carry = 0
        prevNode = None
        while stack:
            node = stack.pop()
            sum = node.val * 2 + carry
            # print(node.val ,sum, carry)
            if sum > 9:
                carry = sum // 10
                sum %= 10
            else:
                carry = 0
            node.val = sum
            node.next = prevNode
            prevNode = node

        if carry > 0:
            node = ListNode(carry)
            node.next = prevNode

        return node
