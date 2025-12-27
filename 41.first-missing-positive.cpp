/*
 * @lc app=leetcode id=41 lang=cpp
 *
 * [41] First Missing Positive
 *
 * https://leetcode.com/problems/first-missing-positive/description/
 *
 * algorithms
 * Hard (40.10%)
 * Likes:    18093
 * Dislikes: 1968
 * Total Accepted:    1.6M
 * Total Submissions: 3.9M
 * Testcase Example:  '[1,2,0]'
 *
 * Given an unsorted integer array nums. Return the smallest positive integer
 * that is not present in nums.
 * 
 * You must implement an algorithm that runs in O(n) time and uses O(1)
 * auxiliary space.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,2,0]
 * Output: 3
 * Explanation: The numbers in the range [1,2] are all in the array.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [3,4,-1,1]
 * Output: 2
 * Explanation: 1 is in the array but 2 is missing.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: nums = [7,8,9,11,12]
 * Output: 1
 * Explanation: The smallest positive integer 1 is missing.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 10^5
 * -2^31 <= nums[i] <= 2^31 - 1
 * 
 * 
 */
#include<iostream>
using namespace std;
// @lc code=start
class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        // number can be between 1 and n+1 for array for size n {1,2,3,.. n} in worst case --> no negatives
        int result = -1;
        int n = nums.size();
        // remove all the 0 and negatives beforehand
        for(int i = 0; i < n; i++)
            if(nums[i] <= 0)
                nums[i] = n + 1;

        for(int i = 0; i < nums.size() ; i++) {

            // dont care about negative, dont care about numbers greater than n in the array
            int ele = abs(nums[i]);
            if(ele > 0  && ele < n+1 && nums[ele-1] > 0) {
                nums[ele-1] *= -1;
            }
 
        }

        for(int i = 0 ; i < nums.size(); i++) {
            if(nums[i] > 0)
                return i + 1;
        }

        return n+1; // for n+1 nothing will be marked

    }
};
// @lc code=end

