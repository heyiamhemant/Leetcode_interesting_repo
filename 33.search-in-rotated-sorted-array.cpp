/*
 * @lc app=leetcode id=33 lang=cpp
 *
 * [33] Search in Rotated Sorted Array
 *
 * https://leetcode.com/problems/search-in-rotated-sorted-array/description/
 *
 * algorithms
 * Medium (41.74%)
 * Likes:    28427
 * Dislikes: 1726
 * Total Accepted:    3.7M
 * Total Submissions: 8.7M
 * Testcase Example:  '[4,5,6,7,0,1,2]\n0'
 *
 * There is an integer array nums sorted in ascending order (with distinct
 * values).
 * 
 * Prior to being passed to your function, nums is possibly rotated at an
 * unknown pivot index k (1 <= k < nums.length) such that the resulting array
 * is [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]]
 * (0-indexed). For example, [0,1,2,4,5,6,7] might be rotated at pivot index 3
 * and become [4,5,6,7,0,1,2].
 * 
 * Given the array nums after the possible rotation and an integer target,
 * return the index of target if it is in nums, or -1 if it is not in nums.
 * 
 * You must write an algorithm with O(log n) runtime complexity.
 * 
 * 
 * Example 1:
 * Input: nums = [4,5,6,7,0,1,2], target = 0
 * Output: 4
 * Example 2:
 * Input: nums = [4,5,6,7,0,1,2], target = 3
 * Output: -1
 * Example 3:
 * Input: nums = [1], target = 0
 * Output: -1
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 5000
 * -10^4 <= nums[i] <= 10^4
 * All values of nums are unique.
 * nums is an ascending array that is possibly rotated.
 * -10^4 <= target <= 10^4
 * 
 * 
 */
#include<iostream>
using namespace std;
// @lc code=start
class Solution {
    public:
    
        int search(vector<int>& nums, int target) {
            int low = 0 ;
            int high = nums.size() - 1;
            while(low <=  high) {
                int mid = (low + high) / 2;
                cout << "low : " << low << ", high : " << high << ", mid : " << mid <<endl;
                if(nums[mid] == target)
                    return mid;
                // decide if its in the first half or second half
                else if (nums[mid] >= nums[low]) {
                    if(target >= nums[low] && target <= nums[mid])  // sorted left
                        high = mid - 1;
                    else // target in unsorted right
                        low = mid + 1;
                } else if(nums[high] >= nums[mid]) {
                    if(target <= nums[high] && target >= nums[mid]) // sorted right
                        low = mid + 1;
                    else // target in unsorted left
                        high = mid - 1;
                } 
            }
            return -1;
        }
    };
// @lc code=end

