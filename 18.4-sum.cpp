/*
 * @lc app=leetcode id=18 lang=cpp
 *
 * [18] 4Sum
 *
 * https://leetcode.com/problems/4sum/description/
 *
 * algorithms
 * Medium (36.92%)
 * Likes:    12634
 * Dislikes: 1522
 * Total Accepted:    1.5M
 * Total Submissions: 3.9M
 * Testcase Example:  '[1,0,-1,0,-2,2]\n0'
 *
 * Given an array nums of n integers, return an array of all the unique
 * quadruplets [nums[a], nums[b], nums[c], nums[d]] such that:
 * 
 * 
 * 0 <= a, b, c, d < n
 * a, b, c, and d are distinct.
 * nums[a] + nums[b] + nums[c] + nums[d] == target
 * 
 * 
 * You may return the answer in any order.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,0,-1,0,-2,2], target = 0
 * Output: [[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [2,2,2,2,2], target = 8
 * Output: [[2,2,2,2]]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 200
 * -10^9 <= nums[i] <= 10^9
 * -10^9 <= target <= 10^9
 * 
 * 
 */

// @lc code=start
#include<iostream>
using namespace std;
using ll = long long;
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> result;
        int n = nums.size();
        sort(nums.begin(), nums.end());

        for(int i = 0 ; i < n - 3; i++) { // j , left, right for 3

            if(i > 0 && nums[i] == nums[i-1])  // skip duplicates for i
                continue;
            for(int j = i + 1; j < n - 2 ; j++) { // left, right for 2
                if(j > i + 1 && nums[j] == nums[j-1]) // skip duplicates for j
                    continue;
                int left = j + 1;
                int right = n - 1;
        
                while(left < right ) {
                    ll sum = (ll)nums[i] + nums[j] + nums[left] + nums[right];
                    if(sum == target) {
                        result.push_back({nums[i],nums[j], nums[left], nums[right]});
                        while(left < right && nums[left] == nums[left + 1]) left++; // skip duplicates for left
                        while(left < right && nums[right] == nums[right - 1]) right--; // skip duplicates for right
                        left++;
                        right--;
                    } else if(sum > target)
                        right--;
                    else if(sum < target) 
                        left++;
                                        
                }
            }
        }



        return result;
    }
};
// @lc code=end

