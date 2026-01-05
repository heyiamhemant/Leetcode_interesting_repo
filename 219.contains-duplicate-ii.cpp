/*
 * @lc app=leetcode id=219 lang=cpp
 *
 * [219] Contains Duplicate II
 *
 * https://leetcode.com/problems/contains-duplicate-ii/description/
 *
 * algorithms
 * Easy (46.85%)
 * Likes:    7243
 * Dislikes: 3295
 * Total Accepted:    1.6M
 * Total Submissions: 3.2M
 * Testcase Example:  '[1,2,3,1]\n3'
 *
 * Given an integer array nums and an integer k, return true if there are two
 * distinct indices i and j in the array such that nums[i] == nums[j] and abs(i
 * - j) <= k.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,2,3,1], k = 3
 * Output: true
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [1,0,1,1], k = 1
 * Output: true
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: nums = [1,2,3,1,2,3], k = 2
 * Output: false
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 10^5
 * -10^9 <= nums[i] <= 10^9
 * 0 <= k <= 10^5
 * 
 * 
 */
#include<iostream>
#include<unordered_set>
using namespace std;
// @lc code=start
class Solution {
public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        int i = 0;
        int j = 0;
        unordered_set<int> Set;
        while(j < k && j < nums.size()) {
            if(Set.find(nums[j]) == Set.end())
                Set.insert(nums[j++]);
            else return true;
        }

        while(j < nums.size()) {
            if(Set.find(nums[j]) == Set.end()) {
                Set.insert(nums[j++]);
                Set.erase(nums[i++]);
            } else return true;
        }
        return false;

    }
};
// @lc code=end

