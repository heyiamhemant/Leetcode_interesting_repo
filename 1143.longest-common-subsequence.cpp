/*
 * @lc app=leetcode id=1143 lang=cpp
 *
 * [1143] Longest Common Subsequence
 *
 * https://leetcode.com/problems/longest-common-subsequence/description/
 *
 * algorithms
 * Medium (57.79%)
 * Likes:    14391
 * Dislikes: 225
 * Total Accepted:    1.5M
 * Total Submissions: 2.6M
 * Testcase Example:  '"abcde"\n"ace"'
 *
 * Given two strings text1 and text2, return the length of their longest common
 * subsequence. If there is no common subsequence, return 0.
 * 
 * A subsequence of a string is a new string generated from the original string
 * with some characters (can be none) deleted without changing the relative
 * order of the remaining characters.
 * 
 * 
 * For example, "ace" is a subsequence of "abcde".
 * 
 * 
 * A common subsequence of two strings is a subsequence that is common to both
 * strings.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: text1 = "abcde", text2 = "ace" 
 * Output: 3  
 * Explanation: The longest common subsequence is "ace" and its length is 3.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: text1 = "abc", text2 = "abc"
 * Output: 3
 * Explanation: The longest common subsequence is "abc" and its length is 3.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: text1 = "abc", text2 = "def"
 * Output: 0
 * Explanation: There is no such common subsequence, so the result is 0.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= text1.length, text2.length <= 1000
 * text1 and text2 consist of only lowercase English characters.
 * 
 * 
 */
#include<iostream>
#include<unordered_set>
using namespace std;
// @lc code=start
class Solution {
    public:
        int longestCommonSubsequence(string text1, string text2) {
            int m = text1.size();
            int n = text2.size();

            // why not dp[m][n]?
            // Because we need to consider the case where we have an empty string
            // So we create a dp array of size (m+1) x (n+1)
            // This allows us to handle the base case where one of the strings is empty
            // dp[i][j] will hold the length of the longest common subsequence of text
            int dp[m+1][n+1];
            memset(dp, 0, sizeof(dp));
            for(int i = 1; i <= m; i++) {
                for(int j = 1; j <= n; j++) {
                    // If characters match, increment the count from the previous indices
                    // Otherwise, take the maximum from either excluding the current character of text1 or text2
                    // This ensures we are considering the longest subsequence found so far
                    // dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                    if(text1[i-1] == text2[j-1]) 
                        dp[i][j] = 1 + dp[i-1][j-1];
                    else
                    // If characters do not match, take the maximum of the two possible subsequences
                        dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
            return dp[m][n];
        }
};