/*
 * @lc app=leetcode id=424 lang=cpp
 *
 * [424] Longest Repeating Character Replacement
 *
 * https://leetcode.com/problems/longest-repeating-character-replacement/description/
 *
 * algorithms
 * Medium (55.58%)
 * Likes:    11205
 * Dislikes: 598
 * Total Accepted:    949.4K
 * Total Submissions: 1.7M
 * Testcase Example:  '"ABAB"\n2'
 *
 * You are given a string s and an integer k. You can choose any character of
 * the string and change it to any other uppercase English character. You can
 * perform this operation at most k times.
 * 
 * Return the length of the longest substring containing the same letter you
 * can get after performing the above operations.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "ABAB", k = 2
 * Output: 4
 * Explanation: Replace the two 'A's with two 'B's or vice versa.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "AABABBA", k = 1
 * Output: 4
 * Explanation: Replace the one 'A' in the middle with 'B' and form "AABBBBA".
 * The substring "BBBB" has the longest repeating letters, which is 4.
 * There may exists other ways to achieve this answer too.
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s.length <= 10^5
 * s consists of only uppercase English letters.
 * 0 <= k <= s.length
 * 
 * 
 */
#include<iostream>
#include<map>
using namespace std;
// @lc code=start
class Solution {
public:
    int characterReplacement(string s, int k) {
        int right = 0;
        int left = 0;
        unordered_map<char, int> cMap;
        char maxFreqC;
        int maxFreq = 0;
        while (right < s.size())
        {
            char c = s[right];
            if (cMap.find(c) == cMap.end())
            {
                cMap[c] = 0;
            } else {
                if(c != maxFreqC)
                    k--;

                int freq = ++cMap[c];
                if (freq > maxFreq) {
                    maxFreqC = c;
                    maxFreq = freq;
                }
            }

            while(k <0 && left < right && s[left] != maxFreqC) {
                k++;
                if(cMap[c] > 0)
                    cMap[c]--;
                else
                    return 0;
            }
            right++;
        }
        return right - left;
    }
};
// @lc code=end

