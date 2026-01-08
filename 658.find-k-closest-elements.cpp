/*
 * @lc app=leetcode id=658 lang=cpp
 *
 * [658] Find K Closest Elements
 *
 * https://leetcode.com/problems/find-k-closest-elements/description/
 *
 * algorithms
 * Medium (47.96%)
 * Likes:    8939
 * Dislikes: 887
 * Total Accepted:    778K
 * Total Submissions: 1.6M
 * Testcase Example:  '[1,2,3,4,5]\n4\n3'
 *
 * Given a sorted integer array arr, two integers k and x, return the k closest
 * integers to x in the array. The result should also be sorted in ascending
 * order.
 * 
 * An integer a is closer to x than an integer b if:
 * 
 * 
 * |a - x| < |b - x|, or
 * |a - x| == |b - x| and a < b
 * 
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: arr = [1,2,3,4,5], k = 4, x = 3
 * 
 * Output: [1,2,3,4]
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: arr = [1,1,2,3,4,5], k = 4, x = -1
 * 
 * Output: [1,1,2,3]
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= k <= arr.length
 * 1 <= arr.length <= 10^4
 * arr is sorted in ascending order.
 * -10^4 <= arr[i], x <= 10^4
 * 
 * 
 */
#include<iostream>
using namespace std;
// @lc code=start
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int n = arr.size();
        
        // Binary search to find the insertion point of x (closest position)
        int right = lower_bound(arr.begin(), arr.end(), x) - arr.begin();
        int left = right - 1;  // One step left for potential closer element
        
        // Expand/shrink window to exactly k elements
        while (k--) {
            if (left < 0) {
                ++right;
            } else if (right >= n) {
                --left;
            } else if (abs(arr[left] - x) <= abs(arr[right] - x)) {
                --left;  // Left is closer or equal → discard right
            } else {
                ++right; // Right is closer → discard left
            }
        }
        
        // Window is now from left+1 to right-1 (size k)
        return vector<int>(arr.begin() + left + 1, arr.begin() + right);
    }
};
// @lc code=end

