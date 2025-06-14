/*
 * @lc app=leetcode id=125 lang=cpp
 *
 * [125] Valid Palindrome
 *
 * https://leetcode.com/problems/valid-palindrome/description/
 *
 * algorithms
 * Easy (49.08%)
 * Likes:    10394
 * Dislikes: 8550
 * Total Accepted:    4.3M
 * Total Submissions: 8.4M
 * Testcase Example:  '"A man, a plan, a canal: Panama"'
 *
 * A phrase is a palindrome if, after converting all uppercase letters into
 * lowercase letters and removing all non-alphanumeric characters, it reads the
 * same forward and backward. Alphanumeric characters include letters and
 * numbers.
 * 
 * Given a string s, return true if it is a palindrome, or false otherwise.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "A man, a plan, a canal: Panama"
 * Output: true
 * Explanation: "amanaplanacanalpanama" is a palindrome.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "race a car"
 * Output: false
 * Explanation: "raceacar" is not a palindrome.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: s = " "
 * Output: true
 * Explanation: s is an empty string "" after removing non-alphanumeric
 * characters.
 * Since an empty string reads the same forward and backward, it is a
 * palindrome.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s.length <= 2 * 10^5
 * s consists only of printable ASCII characters.
 * 
 * 
 */
#include<iostream>
using namespace std;
// @lc code=start
class Solution {
    public:
        bool isPalindrome(string s) {
            int i = 0 , j= s.size() - 1;
            for(char &c : s)
                c = tolower(c);
            while ( i  < j ) {
                while(i < s.size() && !isalnum(s[i]))
                    i++;
                while(j < s.size() && !isalnum(s[j]))
                    j--;
    
                
                if(i < s.size() && j < s.size() && s[i] != s[j])
                    return false;
                i++;
                j--;
                
            } 
            return true;
        }
    };
// @lc code=end

