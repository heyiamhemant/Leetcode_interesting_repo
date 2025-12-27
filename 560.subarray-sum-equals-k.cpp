/*
 * @lc app=leetcode id=560 lang=cpp
 *
 * [560] Subarray Sum Equals K
 *
 * https://leetcode.com/problems/subarray-sum-equals-k/description/
 *
 * algorithms
 * Medium (44.30%)
 * Likes:    24400
 * Dislikes: 817
 * Total Accepted:    2.2M
 * Total Submissions: 4.6M
 * Testcase Example:  '[1,1,1]\n2'
 *
 * Given an array of integers nums and an integer k, return the total number of
 * subarrays whose sum equals to k.
 * 
 * A subarray is a contiguous non-empty sequence of elements within an
 * array.
 * 
 * 
 * Example 1:
 * Input: nums = [1,1,1
 * ], k = 2
 * Output: 2
 * Example 2:
 * Input: nums = [1,2,3], k = 3
 * Output: 2
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 2 * 10^4
 * -1000 <= nums[i] <= 1000
 * -10^7 <= k <= 10^7
 * 
 * 
 */
#include<iostream>
using namespace std;
// @lc code=start
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        unordered_map<int, int> prefixCount;  // prefix sum -> frequency
        prefixCount[0] = 1;  // Empty subarray has sum 0

        int prefix = 0;
        int result = 0;

        for (int num : nums) {
            prefix += num;

            // How many previous prefixes == prefix - k?
            if (prefixCount.count(prefix - k)) {
                result += prefixCount[prefix - k];
            }

            // Add current prefix
            prefixCount[prefix]++;
        }

        return result;
    }
};
// @lc code=end

