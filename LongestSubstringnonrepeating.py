"""3. Longest Substring Without Repeating Characters
Solved
Medium

Topics
Companies

Hint
Given a string s, find the length of the longest 
substring
 without repeating characters.

 

Example 1:

Input: s = "abcabcbb"
Output: 3
Explanation: The answer is "abc", with the length of 3.
Example 2:

Input: s = "bbbbb"
Output: 1
Explanation: The answer is "b", with the length of 1.
Example 3:

Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.
 

Constraints:

0 <= s.length <= 5 * 104
s consists of English letters, digits, symbols and spaces.
"""

class Solution:
    # solved completely on my own
    def lengthOfLongestSubstring(self, s: str) -> int:
        left, right = 0, 0
        n = len(s)
        # map to keep the set of characters encountered
        trackC = {}

        maxs = 0
        # sliding window
        while right < n:
            duplicate = False

            # adjust the right pointer, and mark the duplicate flag upon encountering a character twice
            if s[right] not in trackC:
                trackC[s[right]] = 1
            elif trackC[s[right]] == 0:
                trackC[s[right]] += 1
            else:
                trackC[s[right]] += 1
                duplicate = True
            # print(trackC, right , left, right - left + 1)
            if duplicate:
                # adjust left pointer to correct until the duplicate character is removed
                # print(s[right], s[left])
                while left <= right:
                    if trackC[s[left]] > 1:
                        trackC[s[left]] -= 1
                        left += 1
                        break
                    else:
                        trackC[s[left]] -= 1
                    left += 1
            # the duplicate is removed and we have the new non repeating sub - string
            maxs = max(right - left + 1, maxs)
            right += 1

        return maxs
