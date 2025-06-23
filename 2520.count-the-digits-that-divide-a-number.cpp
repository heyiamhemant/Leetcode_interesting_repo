/*
 * @lc app=leetcode id=2520 lang=cpp
 *
 * [2520] Count the Digits That Divide a Number
 *
 * https://leetcode.com/problems/count-the-digits-that-divide-a-number/description/
 *
 * algorithms
 * Easy (85.13%)
 * Likes:    585
 * Dislikes: 37
 * Total Accepted:    120.6K
 * Total Submissions: 140.5K
 * Testcase Example:  '7'
 *
 * Given an integer num, return the number of digits in num that divide num.
 * 
 * An integer val divides nums if nums % val == 0.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: num = 7
 * Output: 1
 * Explanation: 7 divides itself, hence the answer is 1.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: num = 121
 * Output: 2
 * Explanation: 121 is divisible by 1, but not 2. Since 1 occurs twice as a
 * digit, we return 2.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: num = 1248
 * Output: 4
 * Explanation: 1248 is divisible by all of its digits, hence the answer is
 * 4.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= num <= 10^9
 * num does not contain 0 as one of its digits.
 * 
 * 
 */

// @lc code=start
class Solution {
    public:
        int countDigits(int num) {
            int result = 0;
            int orig = num;
            while(num) {
                int dig = num%10;
                if(orig % dig == 0)
                    result++;
                num/=10;
                
            }
            return result;
    
        }
    };
// @lc code=end

