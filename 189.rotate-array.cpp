/*
 * @lc app=leetcode id=189 lang=cpp
 *
 * [189] Rotate Array
 *
 * https://leetcode.com/problems/rotate-array/description/
 *
 * algorithms
 * Medium (41.80%)
 * Likes:    20516
 * Dislikes: 2162
 * Total Accepted:    3.6M
 * Total Submissions: 8.3M
 * Testcase Example:  '[1,2,3,4,5,6,7]\n3'
 *
 * Given an integer array nums, rotate the array to the right by k steps, where
 * k is non-negative.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,2,3,4,5,6,7], k = 3
 * Output: [5,6,7,1,2,3,4]
 * Explanation:
 * rotate 1 steps to the right: [7,1,2,3,4,5,6]
 * rotate 2 steps to the right: [6,7,1,2,3,4,5]
 * rotate 3 steps to the right: [5,6,7,1,2,3,4]
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [-1,-100,3,99], k = 2
 * Output: [3,99,-1,-100]
 * Explanation: 
 * rotate 1 steps to the right: [99,-1,-100,3]
 * rotate 2 steps to the right: [3,99,-1,-100]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 10^5
 * -2^31 <= nums[i] <= 2^31 - 1
 * 0 <= k <= 10^5
 * 
 * 
 * 
 * Follow up:
 * 
 * 
 * Try to come up with as many solutions as you can. There are at least three
 * different ways to solve this problem.
 * Could you do it in-place with O(1) extra space?
 * 
 * 
 */
#include<iostream>
using namespace std;
// @lc code=start
class Solution {
public:
    void rotate(vector<int>& nums, int k) {

        int n = nums.size();
        k%=n;
        // make partition on n - k and reverse each part
        int start = 0 ;
        int end = n - k - 1;
        while(start < end){
            swap(nums[start++],nums[end--]);
        }
        start = n - k;
        end = n-1;
        while(start < end) {
            swap(nums[start++],nums[end--]);
        }
        start = 0 ;
        end = n -1 ;
        // reverse the array
        while(start < end){
            swap(nums[start++],nums[end--]);
        }
    }
};
// @lc code=end

