/*
 * @lc app=leetcode id=67 lang=cpp
 *
 * [67] Add Binary
 *
 * https://leetcode.com/problems/add-binary/description/
 *
 * algorithms
 * Easy (57.69%)
 * Likes:    10787
 * Dislikes: 1116
 * Total Accepted:    2.3M
 * Total Submissions: 4M
 * Testcase Example:  '"11"\n"1"'
 *
 * Given two binary strings a and b, return their sum as a binary string.
 * 
 * 
 * Example 1:
 * Input: a = "11", b = "1"
 * Output: "100"
 * Example 2:
 * Input: a = "1010", b = "1011"
 * Output: "10101"
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= a.length, b.length <= 10^4
 * a and b consist only of '0' or '1' characters.
 * Each string does not contain leading zeros except for the zero itself.
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    string addBinary(string a, string b) {
        int i = a.size() - 1;
        int j = b.size() - 1;
        int carry = 0;
        string res ;
        while(i >= 0 || j >= 0 || carry) {
            int sum = 0 ;
            int numa = 0; 
            int numb = 0;
            if(i >= 0) numa = a[i] - '0';
            if(j >= 0) numb = b[j] - '0';
            sum = numa + numb + carry;
            carry = sum / 2;
            res +=((sum%2) + '0');
            i--;
            j--;
        }
        reverse(res.begin(), res.end());
        return res;
    }
};
// @lc code=end

