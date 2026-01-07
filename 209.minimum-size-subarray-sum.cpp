/*
 * @lc app=leetcode id=209 lang=cpp
 *
 * [209] Minimum Size Subarray Sum
 *
 * https://leetcode.com/problems/minimum-size-subarray-sum/description/
 *
 * algorithms
 * Medium (48.04%)
 * Likes:    14060
 * Dislikes: 527
 * Total Accepted:    1.7M
 * Total Submissions: 3.4M
 * Testcase Example:  '7\n[2,3,1,2,4,3]'
 *
 * Given an array of positive integers nums and a positive integer target,
 * return the minimal length of a subarray whose sum is greater than or equal
 * to target. If there is no such subarray, return 0 instead.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: target = 7, nums = [2,3,1,2,4,3]
 * Output: 2
 * Explanation: The subarray [4,3] has the minimal length under the problem
 * constraint.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: target = 4, nums = [1,4,4]
 * Output: 1
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: target = 11, nums = [1,1,1,1,1,1,1,1]
 * Output: 0
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= target <= 10^9
 * 1 <= nums.length <= 10^5
 * 1 <= nums[i] <= 10^4
 * 
 * 
 * 
 * Follow up: If you have figured out the O(n) solution, try coding another
 * solution of which the time complexity is O(n log(n)).
 */
#include<iostream>
using namespace std;
// @lc code=start
class Solution {
public: 
    int minSubArrayLen(int target, vector<int>& nums) {
        int n = nums.size();
        int res = n + 1;  // Sentinel
        int currSum = 0;
        int left = 0;

        for (int right = 0; right < n; ++right) {
            currSum += nums[right];

            while (currSum >= target && left <= right) {
                res = min(res, right - left + 1);
                currSum -= nums[left++];
            }
        }

        return res == n + 1 ? 0 : res;
    }
};
// @lc code=end

