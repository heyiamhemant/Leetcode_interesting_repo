/*
 * @lc app=leetcode id=15 lang=cpp
 *
 * [15] 3Sum
 *
 * https://leetcode.com/problems/3sum/description/
 *
 * algorithms
 * Medium (35.63%)
 * Likes:    31817
 * Dislikes: 2989
 * Total Accepted:    4.2M
 * Total Submissions: 11.6M
 * Testcase Example:  '[-1,0,1,2,-1,-4]'
 *
 * Given an integer array nums, return all the triplets [nums[i], nums[j],
 * nums[k]] such that i != j, i != k, and j != k, and nums[i] + nums[j] +
 * nums[k] == 0.
 * 
 * Notice that the solution set must not contain duplicate triplets.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [-1,0,1,2,-1,-4]
 * Output: [[-1,-1,2],[-1,0,1]]
 * Explanation: 
 * nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0.
 * nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0.
 * nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0.
 * The distinct triplets are [-1,0,1] and [-1,-1,2].
 * Notice that the order of the output and the order of the triplets does not
 * matter.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [0,1,1]
 * Output: []
 * Explanation: The only possible triplet does not sum up to 0.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: nums = [0,0,0]
 * Output: [[0,0,0]]
 * Explanation: The only possible triplet sums up to 0.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 3 <= nums.length <= 3000
 * -10^5 <= nums[i] <= 10^5
 * 
 * 
 */

// @lc code=start
#include<iostream>
using namespace std;
class Solution
{
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        sort(nums.begin(), nums.end());
       
        for (int i = 0; i < nums.size(); i++)
        {
            // handle duplicate pairs, can also use set
            if(i > 0 and nums[i] == nums[i-1])
                continue;
            int low = i + 1;
            int high = nums.size() - 1;
            while(low < high) {
                int sum = nums[i] + nums[low] + nums[high];
                if (sum < 0)
                    low++;
                else if(sum > 0)
                     high--;
                else {
                    result.push_back({nums[i], nums[low], nums[high]});
                    low++;
                    // handle duplicate pairs, can also use set
                    while(nums[low] == nums[low-1] and low < high)
                        low++;

                    high--;
                }
            }
        }
        return result;
    }
};
// @lc code=end

