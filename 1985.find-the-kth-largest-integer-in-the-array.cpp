/*
 * @lc app=leetcode id=1985 lang=cpp
 *
 * [1985] Find the Kth Largest Integer in the Array
 *
 * https://leetcode.com/problems/find-the-kth-largest-integer-in-the-array/description/
 *
 * algorithms
 * Medium (47.64%)
 * Likes:    1378
 * Dislikes: 160
 * Total Accepted:    103.4K
 * Total Submissions: 216K
 * Testcase Example:  '["3","6","7","10"]\n4'
 *
 * You are given an array of strings nums and an integer k. Each string in nums
 * represents an integer without leading zeros.
 * 
 * Return the string that represents the k^th largest integer in nums.
 * 
 * Note: Duplicate numbers should be counted distinctly. For example, if nums
 * is ["1","2","2"], "2" is the first largest integer, "2" is the
 * second-largest integer, and "1" is the third-largest integer.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = ["3","6","7","10"], k = 4
 * Output: "3"
 * Explanation:
 * The numbers in nums sorted in non-decreasing order are ["3","6","7","10"].
 * The 4^th largest integer in nums is "3".
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = ["2","21","12","1"], k = 3
 * Output: "2"
 * Explanation:
 * The numbers in nums sorted in non-decreasing order are ["1","2","12","21"].
 * The 3^rd largest integer in nums is "2".
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: nums = ["0","0"], k = 2
 * Output: "0"
 * Explanation:
 * The numbers in nums sorted in non-decreasing order are ["0","0"].
 * The 2^nd largest integer in nums is "0".
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= k <= nums.length <= 10^4
 * 1 <= nums[i].length <= 100
 * nums[i] consists of only digits.
 * nums[i] will not have any leading zeros.
 * 
 * 
 */
#include<vector>
#include<string>
#include<algorithm>
using namespace std;
// @lc code=start
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        make_heap(nums.begin() , nums.begin() + k , std::greater<int>());
        for(int i = k  ; i < nums.size() ; i++) {
            if(nums[i] > nums.front()) {
                pop_heap(nums.begin(), nums.begin() + k , std::greater<int>());
                nums[k-1] = nums[i];
                push_heap(nums.begin(), nums.begin() + k , std::greater<int>());
            }

        }
        return nums[0];
    }
};
// @lc code=end

