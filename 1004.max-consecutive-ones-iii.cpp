/*
 * @lc app=leetcode id=1004 lang=cpp
 *
 * [1004] Max Consecutive Ones III
 *
 * https://leetcode.com/problems/max-consecutive-ones-iii/description/
 *
 * algorithms
 * Medium (64.38%)
 * Likes:    9004
 * Dislikes: 152
 * Total Accepted:    793.9K
 * Total Submissions: 1.2M
 * Testcase Example:  '[1,1,1,0,0,0,1,1,1,1,0]\n2'
 *
 * Given a binary array nums and an integer k, return the maximum number of
 * consecutive 1's in the array if you can flip at most k 0's.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,1,1,0,0,0,1,1,1,1,0], k = 2
 * Output: 6
 * Explanation: [1,1,1,0,0,1,1,1,1,1,1]
 * Bolded numbers were flipped from 0 to 1. The longest subarray is
 * underlined.
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1], k = 3
 * Output: 10
 * Explanation: [0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,1]
 * Bolded numbers were flipped from 0 to 1. The longest subarray is
 * underlined.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 10^5
 * nums[i] is either 0 or 1.
 * 0 <= k <= nums.length
 * 
 * 
 */

#include<iostream>
#include<set>
using namespace std;
// @lc code=start
class Solution {
public:
/*************  ✨ Codeium Command ⭐  *************/
/**
 * This function computes the maximum number of consecutive 1's in a binary array `nums`
 * by flipping at most `k` 0's to 1's. It uses a sliding window approach, where two pointers
 * `left` and `right` maintain a window of elements under consideration. The function iteratively
 * expands the window by incrementing `right` and adjusts the window by moving `left` when necessary.
 * The `flipCount` variable tracks how many 0's have been flipped, and the `flipped` set stores the indices 
 * of flipped 0's. The function returns the maximum length of consecutive 1's obtained by performing 
 * at most `k` flips.
 *
 * @param nums A vector of integers representing the binary array.
 * @param k An integer representing the maximum number of 0's that can be flipped to 1's.
 * @return The maximum number of consecutive 1's that can be obtained by flipping at most `k` 0's.
 */

/******  d4b26fc9-05bf-4fd2-b619-3c02bba62d5a  *******/
    int longestOnesMySolution(vector<int>& nums, int k) {
        int left = 0, right = 0, count = 0, flipCount = 0, maxOnes = 0;
        set<int> flipped;
        int n = nums.size();
        while(right < n) {
            if (nums[right] == 1) {
                count++;
            } else if(nums[right] == 0 and flipCount < k) {
                // encounter a 0 and flip it
                flipCount++;
                count++;
                nums[right]= 1;
                flipped.insert(right);
            } else {
                // encounter 0 and no flips left
                // shift left pointer
                maxOnes = max(maxOnes, count);
                while (left <= right)
                {
                    if (flipped.find(left) != flipped.end()) {
                        flipped.erase(left);
                        flipped.insert(right); // get back one flip and flip the zero
                        left++;
                        break;
                    }
                    left++;
                    if(count > 0) // handle negative flips
                        count--;
                }
            }
            right++;
        }
        return max(maxOnes, count);
    }
};
// @lc code=end

