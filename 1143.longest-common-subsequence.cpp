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

// @lc code=start
class Solution {
    public:
        int longestConsecutive(vector<int>& nums) {
             // hash set
             unordered_set<int> numbers(nums.begin(), nums.end());
             int maxCount =0 ;
             for(int num : nums) {
                numbers.insert(num);
             }
             for(int num : nums) {
                int count  = 1;
                //avoid start sequence with numbers in the middle of a sequence
                if(numbers.find(num-1) == numbers.end()) {
                    int curNum = num;
                    while(numbers.find(curNum + 1) != numbers.end()) {
                        count++;
                        curNum++;
                    }
                    maxCount = max(maxCount, count);
                }
            }
             return maxCount;
        }
    };
// @lc code=end

