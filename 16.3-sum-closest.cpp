/*
 * @lc app=leetcode id=16 lang=cpp
 *
 * [16] 3Sum Closest
 *
 * https://leetcode.com/problems/3sum-closest/description/
 *
 * algorithms
 * Medium (46.19%)
 * Likes:    11005
 * Dislikes: 595
 * Total Accepted:    1.5M
 * Total Submissions: 3.2M
 * Testcase Example:  '[-1,2,1,-4]\n1'
 *
 * Given an integer array nums of length n and an integer target, find three
 * integers in nums such that the sum is closest to target.
 * 
 * Return the sum of the three integers.
 * 
 * You may assume that each input would have exactly one solution.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [-1,2,1,-4], target = 1
 * Output: 2
 * Explanation: The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [0,0,0], target = 1
 * Output: 0
 * Explanation: The sum that is closest to the target is 0. (0 + 0 + 0 =
 * 0).
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 3 <= nums.length <= 500
 * -1000 <= nums[i] <= 1000
 * -10^4 <= target <= 10^4
 * 
 * 
 */

#include<iostream>
using namespace std;
// @lc code=start
class Solution {
    public:
        int threeSumClosest(vector<int>& nums, int target) {
            sort(nums.begin(), nums.end());
            int minDelta = INT_MAX;
            int result = 0;
            for(int i = 0 ; i < nums.size(); i++) {
                int j = i + 1;
                int k = nums.size() - 1;
            
                while(j < k) {
                    int sum = nums[i] + nums[j] + nums[k];
                    int delta = abs(target-sum);
                    if(delta < minDelta){ // getting closer
                        minDelta = delta;
                        result = sum;
                    } 
                    
                    if(sum < target) {
                        j++; //too small
                    }else if(sum > target) {
                        k--; // too big
                    } else {
                        return sum; // just right
                    }
                }
            }
            return result;
        }
    };
// @lc code=end

