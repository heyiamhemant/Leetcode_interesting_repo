/*
 * @lc app=leetcode id=42 lang=cpp
 *
 * [42] Trapping Rain Water
 *
 * https://leetcode.com/problems/trapping-rain-water/description/
 *
 * algorithms
 * Hard (63.40%)
 * Likes:    32974
 * Dislikes: 558
 * Total Accepted:    2.5M
 * Total Submissions: 3.9M
 * Testcase Example:  '[0,1,0,2,1,0,1,3,2,1,2,1]'
 *
 * Given n non-negative integers representing an elevation map where the width
 * of each bar is 1, compute how much water it can trap after raining.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
 * Output: 6
 * Explanation: The above elevation map (black section) is represented by array
 * [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue
 * section) are being trapped.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: height = [4,2,0,3,2,5]
 * Output: 9
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * n == height.length
 * 1 <= n <= 2 * 10^4
 * 0 <= height[i] <= 10^5
 * 
 * 
 */

// @lc code=start
#include<iostream>
using namespace std;
class Solution
{
public:
    int trap(vector<int>& height) {
        int low = 0;
        int high = height.size() - 1;
        int water = 0;
        while (low < high)
        {
            int minH = min(height[low], height[high]);
            if(height[low] < height[high]) {
                while(low < high && height[low] <= minH) {
                    water += (minH - height[low]);
                    low++;
                }
            } else {
                while(high >= low && height[high] <= minH) {
                    water += (minH - height[high]);
                    high--;
                }
            }
        }
        return water;
    }
};
// @lc code=end

