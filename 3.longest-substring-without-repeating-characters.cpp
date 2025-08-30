/*
 * @lc app=leetcode id=3 lang=cpp
 *
 * [3] Longest Substring Without Repeating Characters
 *
 * https://leetcode.com/problems/longest-substring-without-repeating-characters/description/
 *
 * algorithms
 * Medium (35.66%)
 * Likes:    40851
 * Dislikes: 1971
 * Total Accepted:    6.7M
 * Total Submissions: 18.7M
 * Testcase Example:  '"abcabcbb"'
 *
 * Given a string s, find the length of the longest substring without repeating
 * characters.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "abcabcbb"
 * Output: 3
 * Explanation: The answer is "abc", with the length of 3.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "bbbbb"
 * Output: 1
 * Explanation: The answer is "b", with the length of 1.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: s = "pwwkew"
 * Output: 3
 * Explanation: The answer is "wke", with the length of 3.
 * Notice that the answer must be a substring, "pwke" is a subsequence and not
 * a substring.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 0 <= s.length <= 5 * 10^4
 * s consists of English letters, digits, symbols and spaces.
 * 
 * 
 */
#include<iostream>
#include<map>
using namespace std;
// @lc code=start
class Solution {
public:
/**
 * Finds the length of the longest substring without repeating characters in the given string.
 * 
 * This function uses a sliding window approach to traverse the string, maintaining a map of
 * characters and their most recent positions to ensure no duplicates exist in the current
 * substring. The window expands by moving the right pointer, and contracts when a duplicate
 * character is encountered by moving the left pointer to the position after the first duplicate.
 * 
 * @param s The input string to search for the longest substring without repeating characters.
 * @return The length of the longest substring without repeating characters.
 */

    int lengthOfLongestSubstring(string s) {
        int maxLen = 0;
        int count = 0;
        map<char, int> characters;
        // new substring
        int right = 0;
        int left = 0;
        while (right < s.size()) {
            if (characters.find(s[right]) == characters.end()) {
                characters[s[right]] = right;
                count++;
                maxLen = max(maxLen, count);
            } else {
                // bring left pointer to after the position of first dup char,
                // so new substring is not containing duplicate
                int dupPos = characters[s[right]];
                while (left < dupPos) {
                    characters.erase(s[left++]);
                    count--;
                }
                left = dupPos + 1;
                characters[s[right]] = right;
            }
            right++;
        }
        return maxLen;
    }
};

// wnd attempt

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int winStart = 0; 
        int maxCount = 0;
        int winEnd = 0; 
        set<char> map; 
        while(winEnd < s.size()) { 
            char cur = s[winEnd]; 
            while(map.find(cur) != map.end())
                map.erase(s[winStart++]); 
            map.insert(cur);
            maxCount = max(maxCount , winEnd - winStart + 1);
            winEnd++; 
        } 
        return maxCount;

    }
};
// @lc code=end

