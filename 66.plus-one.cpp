/*
 * @lc app=leetcode id=66 lang=cpp
 *
 * [66] Plus One
 */

// @lc code=start
class Solution {
    public:
        vector<int> plusOne(vector<int>& digits) {
            int n = digits.size();
            int sum = digits[n-1] + 1;
            digits[n-1] = sum % 10;
            int carry = sum / 10;
            int pos = n-2;
            while(carry && pos >= 0) {
                sum = digits[pos] + 1 ;
                digits[pos] = sum % 10;
                carry = sum / 10;
                pos--;
            }
            if(carry)
                digits.insert(digits.begin() , 1);
        
            return digits;
        }
    };
// @lc code=end

