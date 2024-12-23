/*
 * @lc app=leetcode id=11 lang=cpp
 *
 * [11] Container With Most Water
 *
 * https://leetcode.com/problems/container-with-most-water/description/
 *
 * algorithms
 * Medium (56.42%)
 * Likes:    30156
 * Dislikes: 1894
 * Total Accepted:    3.6M
 * Total Submissions: 6.3M
 * Testcase Example:  '[1,8,6,2,5,4,8,3,7]'
 *
 * You are given an integer array height of length n. There are n vertical
 * lines drawn such that the two endpoints of the i^th line are (i, 0) and (i,
 * height[i]).
 * 
 * Find two lines that together with the x-axis form a container, such that the
 * container contains the most water.
 * 
 * Return the maximum amount of water a container can store.
 * 
 * Notice that you may not slant the container.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: height = [1,8,6,2,5,4,8,3,7]
 * Output: 49
 * Explanation: The above vertical lines are represented by array
 * [1,8,6,2,5,4,8,3,7]. In this case, the max area of water (blue section) the
 * container can contain is 49.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: height = [1,1]
 * Output: 1
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * n == height.length
 * 2 <= n <= 10^5
 * 0 <= height[i] <= 10^4
 * 
 * 
 */

// @lc code=start
#include<iostream>
using namespace std;
class Solution
{
public:
/**
 * Calculates the maximum amount of water that can be contained between two lines in a given height array.
 * 
 * The function uses a two-pointer approach to find the two lines that form the container with the maximum
 * water capacity. It starts with the leftmost and rightmost lines and iteratively adjusts the pointers to
 * maximize the area formed by the lines and the x-axis.
 * 
 * @param height A reference to a vector of integers representing the height of lines. The ith line has
 * endpoints (i, 0) and (i, height[i]).
 * @return An integer representing the maximum amount of water a container can store.
 */

    int maxArea(vector<int>& height) {
        int low = 0;
        int high = height.size() - 1;
        int maxWater = 0;

        while(low < high) {
            int minH = min(height[low], height[high]);
            maxWater = max(maxWater, minH * (high - low));
            if(height[low] <= height[high]) {
                while(low < high && height[low] <= minH)
                    low++;
            } else {
                while(high > low && height[high] <= minH)
                    high--;
            }

        }
        return maxWater;
    }
};
// @lc code=end

