/*
 * @lc app=leetcode id=680 lang=cpp
 *
 * [680] Valid Palindrome II
 *
 * https://leetcode.com/problems/valid-palindrome-ii/description/
 *
 * algorithms
 * Easy (41.63%)
 * Likes:    8837
 * Dislikes: 505
 * Total Accepted:    1.1M
 * Total Submissions: 2.5M
 * Testcase Example:  '"aba"'
 *
 * Given a string s, return true if the s can be palindrome after deleting at
 * most one character from it.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "aba"
 * Output: true
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "abca"
 * Output: true
 * Explanation: You could delete the character 'c'.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: s = "abc"
 * Output: false
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s.length <= 10^5
 * s consists of lowercase English letters.
 * 
 * 
 */
#include<iostream>
using namespace std;
// @lc code=start
class Solution {
public:
    bool validPalindrome(string s) {
        int left = 0;
        int right = s.size() - 1;
        while(left < right) {
            if(s[left] != s[right]) { // found inequality, check if removing one character from either pointers works
                return isPalindrome(s , left+1, right) || isPalindrome(s , left, right-1);
            }
            left++;
            right--;
        }
        return true;
    }
    bool isPalindrome(string & s, int left, int right) {
        while(left < right) {
            if(s[left++] != s[right--])
                return false;
        }
        return true;
    }
};
// @lc code=end

