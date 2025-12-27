/*
 * @lc app=leetcode id=229 lang=cpp
 *
 * [229] Majority Element II
 *
 * https://leetcode.com/problems/majority-element-ii/description/
 *
 * algorithms
 * Medium (52.90%)
 * Likes:    10807
 * Dislikes: 484
 * Total Accepted:    1.2M
 * Total Submissions: 2.1M
 * Testcase Example:  '[3,2,3]'
 *
 * Given an integer array of size n, find all elements that appear more than ⌊
 * n/3 ⌋ times.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [3,2,3]
 * Output: [3]
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [1]
 * Output: [1]
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: nums = [1,2]
 * Output: [1,2]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 5 * 10^4
 * -10^9 <= nums[i] <= 10^9
 * 
 * 
 * 
 * Follow up: Could you solve the problem in linear time and in O(1) space?
 * 
 */
#include<iostream>
using namespace std;
// @lc code=start
class Solution {
public:
    vector<int> majorityElement(vector<int>& nums) {
        vector<int> result;
        int candidate1 = nums[0];
        int candidate2 = nums[0];

        int count1 = 0;
        int count2 = 0;
        int n = nums.size();
        // find candidates
        for (int i = 0; i < nums.size(); i++)
        {   
            if(nums[i] == candidate1)
                count1++;
            else if(nums[i] == candidate2)
                count2++;
            else if (count1 == 0) {
                candidate1 = nums[i];
                count1 = 1;
            }
            else if (count2 == 0)
            {
                candidate2 = nums[i];
                count2 = 1;
            }
            else
            {
                count1--;
                count2--;
            }
        }
        // verify
        count1 = 0;
        count2 = 0;
        for (int i : nums)
        {
            if( i == candidate1)
                count1++;
            else if(i == candidate2)
                count2++;
            else if(count1 == 0)
                candidate1 = nums[i];
                
            if(count1 > n/3) 
                result.push_back(candidate1);
            
            if(count2 > n/3)
                result.push_back(candidate2);
        }


        return result;
    }
};
// @lc code=end

