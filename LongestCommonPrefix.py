"""Easy

Topics
Companies
Write a function to find the longest common prefix string amongst an array of strings.

If there is no common prefix, return an empty string "".

 

Example 1:

Input: strs = ["flower","flow","flight"]
Output: "fl"
Example 2:

Input: strs = ["dog","racecar","car"]
Output: ""
Explanation: There is no common prefix among the input strings.
 

Constraints:

1 <= strs.length <= 200
0 <= strs[i].length <= 200
strs[i] consists of only lowercase English letters."""


class Solution:
    def longestCommonPrefix(self, strs: list[str]) -> str:
        # brute force approach is to go through every string, and find a common character, and then move forward and traverse string again.
        prefix = strs[0]

        for str in strs:
            newPrefix = ""
            i = 0
            m = len(str)
            n = len(prefix)
            while i < m and i < n:
                if str[i] != prefix[i]:
                    break
                newPrefix += str[i]
                i += 1

            prefix = newPrefix

        return prefix
