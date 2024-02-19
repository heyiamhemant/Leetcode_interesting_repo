"""Stepping Numbers
Programming
Graph Data Structure & Algorithms
Medium
36.4% Success

291

21

Bookmark
Asked In:
Problem Description
 
 

Given A and B you have to find all stepping numbers in the range A to B (both inclusive).

The stepping number:

A number is called as a stepping number if the adjacent digits have a difference of 1.

For e.g. 123 is a stepping number, but 358 is not a stepping number

 



Problem Constraints
0 <= A <= 104
1 <= B <= 107
A <= B


Input Format
First argument is an integer A.

Second argument is an integer B.

 



Output Format
Return a integer array sorted in ascending order denoting the stepping numbers between A and B.



Example Input
Input 1:

 A = 10
 B = 20
 



Example Output
Output 1:

 [10, 12]
 



Example Explanation
Explanation 1:

 The stepping numbers in range [10, 20] are 10, and 12. """


class Solution:
    # @param A : integer
    # @param B : integer
    # @return a list of integers
    # time complexit : height of tree O(max ( log A, log B ) )
    def stepNumberCheckDfs(self, num, result, A, B):
        # base return case
        if num > B:
            return
        if num <= B and num >= A:
            print(num)
            result.append(num)
        digit = num % 10
        if digit != 9:  # no digit after 9
            self.stepNumberCheckDfs(num * 10 + digit + 1, result, A, B)
        if digit != 0:  # no digit prior to 0
            self.stepNumberCheckDfs(num * 10 + digit - 1, result, A, B)

    def stepNumber(self, A, B):
        result = []
        for i in range(1, 10):
            self.stepNumberCheckDfs(i, result, A, B)

        # 0 produces same results as 1
        if A == 0:
            result.append(0)
        result.sort()
        return result


obj = Solution()
result = obj.stepNumber(0, 86)
print(result)
