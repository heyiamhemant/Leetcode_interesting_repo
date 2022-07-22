"""859. Buddy Strings
Easy

Given two strings s and goal, return true if you can swap two letters in s so the result is equal to goal, otherwise, return false.

Swapping letters is defined as taking two indices i and j (0-indexed) such that i != j and swapping the characters at s[i] and s[j].

For example, swapping at indices 0 and 2 in "abcd" results in "cbad".
 

Example 1:

Input: s = "ab", goal = "ba"
Output: true
Explanation: You can swap s[0] = 'a' and s[1] = 'b' to get "ba", which is equal to goal.
Example 2:

Input: s = "ab", goal = "ab"
Output: false
Explanation: The only letters you can swap are s[0] = 'a' and s[1] = 'b', which results in "ba" != goal.
Example 3:

Input: s = "aa", goal = "aa"
Output: true
Explanation: You can swap s[0] = 'a' and s[1] = 'a' to get "aa", which is equal to goal.
 

Constraints:

1 <= s.length, goal.length <= 2 * 104
s and goal consist of lowercase letters."""


class Solution(object):
    def buddyStrings(self, s, goal):
        """
        :type s: str
        :type goal: str
        :rtype: bool
        """
        map = {}
        duplicate = False
        if s == goal:
            for i in range(26):
                map[i] = 0
            for ele in s:
                map[ele - "a"] += 1
                if map[ele - "a"] == 2:
                    duplicate = True
                    break
            return duplicate

        first_s = ""
        second_s = ""
        first_goal = ""
        second_goal = ""
        for i in len(s):
            if s[i] != goal[i]:
                if first_s == "" and first_goal != "":
                    first_s = s[i]
                    first_goal = goal[i]
                else:
                    second_s = s[i]
                    second_goal = goal[i]

        if first_s == second_goal and second_s == first_goal:
            return True

        return False
