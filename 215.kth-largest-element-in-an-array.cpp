/*
 * @lc app=leetcode id=215 lang=cpp
 *
 * [215] Kth Largest Element in an Array
 *
 * https://leetcode.com/problems/kth-largest-element-in-an-array/description/
 *
 * algorithms
 * Medium (67.22%)
 * Likes:    18178
 * Dislikes: 952
 * Total Accepted:    3.2M
 * Total Submissions: 4.7M
 * Testcase Example:  '[3,2,1,5,6,4]\n2'
 *
 * Given an integer array nums and an integer k, return the k^th largest
 * element in the array.
 * 
 * Note that it is the k^th largest element in the sorted order, not the k^th
 * distinct element.
 * 
 * Can you solve it without sorting?
 * 
 * 
 * Example 1:
 * Input: nums = [3,2,1,5,6,4], k = 2
 * Output: 5
 * Example 2:
 * Input: nums = [3,2,3,1,2,4,5,5,6], k = 4
 * Output: 4
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= k <= nums.length <= 10^5
 * -10^4 <= nums[i] <= 10^4
 * 
 * 
 */
#include <vector>
using namespace std;
// @lc code=start
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        vector<int> Heap;
        for (int i = 0; i < k; i++)
            Heap.push_back(nums[i]);
        // MIN HEAP
        make_heap(Heap.begin(), Heap.end(), greater<int>());
        for (int i = k; i < nums.size(); i++){
            if(nums[i] > Heap.front()) {
                // it can be among k largest elements
                Heap.push_back(nums[i]);
                push_heap(Heap.begin(), Heap.end(), greater<int>());
                pop_heap(Heap.begin(), Heap.end(), greater<int>());
                Heap.pop_back(); // remove smallest
            }
        }
        return Heap.front();
    }
};
// @lc code=end

