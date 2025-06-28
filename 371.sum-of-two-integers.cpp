/*
 * @lc app=leetcode id=371 lang=cpp
 *
 * [371] Sum of Two Integers
 *
 * https://leetcode.com/problems/sum-of-two-integers/description/
 *
 * algorithms
 * Medium (52.70%)
 * Likes:    4475
 * Dislikes: 5719
 * Total Accepted:    596.1K
 * Total Submissions: 1.1M
 * Testcase Example:  '1\n2'
 *
 * Given two integers a and b, return the sum of the two integers without using
 * the operators + and -.
 * 
 * 
 * Example 1:
 * Input: a = 1, b = 2
 * Output: 3
 * Example 2:
 * Input: a = 2, b = 3
 * Output: 5
 * 
 * 
 * Constraints:
 * 
 * 
 * -1000 <= a, b <= 1000
 * 
 * 
 */

// @lc code=start
class Solution {
    public:
        /**
         * This function takes two integers and returns their sum
         * without using the operators + or -. It does this by
         * performing a binary addition, keeping track of carry
         * and adding each digit to the total sum.
         */
        int getSum(int a, int b) {
            int carry = 0;
            int totalSum = 0;
            int tenPower = 1;
            while(a || b) {
                int sum = a % 10 + b % 10 + carry;
                carry = sum / 10;
                totalSum+=((sum % 10) * tenPower) ;
                a/=10;
                b/=10;
                tenPower*=10; 
            }
            return totalSum + (carry * tenPower); 
        }
};
// @lc code=end

