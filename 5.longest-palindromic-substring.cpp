/*
 * @lc app=leetcode id=5 lang=cpp
 *
 * [5] Longest Palindromic Substring
 *
 * https://leetcode.com/problems/longest-palindromic-substring/description/
 *
 * algorithms
 * Medium (34.57%)
 * Likes:    29776
 * Dislikes: 1824
 * Total Accepted:    3.4M
 * Total Submissions: 9.7M
 * Testcase Example:  '"babad"'
 *
 * Given a string s, return the longest palindromic substring in s.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "babad"
 * Output: "bab"
 * Explanation: "aba" is also a valid answer.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "cbbd"
 * Output: "bb"
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s.length <= 1000
 * s consist of only digits and English letters.
 * 
 * 
 */
#include<iostream>
using namespace std;

// @lc code=start
class Solution {
public:
    //string longestPalindrome(string s) {
        
    //}
    // brute force
    string longestPalidrome(string s) {
        string longestPal;
        for (int i = 0; i < s.size(); i++)
        {

            int p = i + 1, q = i - 1;
            string pal = toString(s[i]);
            while (p > i && p < s.size() && q < i && q > 0 && s[p] == s[q])
            {
                    pal = s[p++] + pal + s[q--];
            }
            if (pal.size() > longestPal.size())
                longestPal = pal;
        }
        return longestPal;
    }
};
// @lc code=end

