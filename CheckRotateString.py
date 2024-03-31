"""Easy

Topics
Companies
Given two strings s and goal, return true if and only if s can become goal after some number of shifts on s.

A shift on s consists of moving the leftmost character of s to the rightmost position.

For example, if s = "abcde", then it will be "bcdea" after one shift.
 

Example 1:

Input: s = "abcde", goal = "cdeab"
Output: true
Example 2:

Input: s = "abcde", goal = "abced"
Output: false"""
class Solution:
    def rotateString(self, s: str, goal: str) -> bool:
        # approach : search for a string in the other string, if the goal string reached end, go to beginning
        i = 0
        m = len(s)
        n = len(goal)
        if n < m:
            return False
        while i < n:
            j = 0
            k = i
            # print(s , i , j , goal[k:])
            # check if this starting point i, we find the substring
            while j < m:
                if s[j] == goal[k]:
                    if k == n - 1 and j < m - 1:
                        k = 0
                    else:
                        k += 1
                    j += 1

                else:
                    break

            if j == m:
                return True
            i += 1

        return False
