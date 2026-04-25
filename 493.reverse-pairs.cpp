/*
 * @lc app=leetcode id=493 lang=cpp
 *
 * [493] Reverse Pairs
 *
 * https://leetcode.com/problems/reverse-pairs/description/
 *
 * algorithms
 * Hard (33.76%)
 * Likes:    7026
 * Dislikes: 300
 * Total Accepted:    359.8K
 * Total Submissions: 1.1M
 * Testcase Example:  '[1,3,2,3,1]'
 *
 * Given an integer array nums, return the number of reverse pairs in the
 * array.
 * 
 * A reverse pair is a pair (i, j) where:
 * 
 * 
 * 0 <= i < j < nums.length and
 * nums[i] > 2 * nums[j].
 * 
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: nums = [1,3,2,3,1]
 * Output: 2
 * Explanation: The reverse pairs are:
 * (1, 4) --> nums[1] = 3, nums[4] = 1, 3 > 2 * 1
 * (3, 4) --> nums[3] = 3, nums[4] = 1, 3 > 2 * 1
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: nums = [2,4,3,5,1]
 * Output: 3
 * Explanation: The reverse pairs are:
 * (1, 4) --> nums[1] = 4, nums[4] = 1, 4 > 2 * 1
 * (2, 4) --> nums[2] = 3, nums[4] = 1, 3 > 2 * 1
 * (3, 4) --> nums[3] = 5, nums[4] = 1, 5 > 2 * 1
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 5 * 10^4
 * -2^31 <= nums[i] <= 2^31 - 1
 * 
 * 
 */

// @lc code=start
#include <vector>
using ll = long long;
class Solution {
public:
    void merge(vector<int>&nums, int low , int mid, int high, int &result)  {
        // two sorted halves i < j is satisfied for i in 1st array and j in second array
        vector<int> res;
        int i = low, j = mid + 1;
        for (; i <= mid; i++) {
            // While nums[i] > 2 * nums[j], all elements from mid+1 to j-1 satisfy the condition
            while (j <= high && (long long)nums[i] > 2LL * nums[j]) {
                j++;
            }
            result += (j - (mid + 1));
        }
        i = low, j = mid + 1;
        while(i <= mid && j <= high) {
            if(nums[i] <= nums[j]) res.push_back(nums[i++]);
            else res.push_back(nums[j++]);
        }
        while(i <= mid) res.push_back(nums[i++]);
        while(j <= high) res.push_back(nums[j++]);

        for(int i = low, k = 0 ; i <= high && k < res.size() ; i++, k++) {
            nums[i] = res[k];
        }
    }
    void mergeSort(vector<int> & nums, int low , int high, int &result) {
        if(low >= high) return;
        int mid = low + (high - low)/2;
        mergeSort(nums,low, mid, result);
        mergeSort(nums,mid + 1, high ,result);
        merge(nums,low, mid , high, result);

    }
    int reversePairs(vector<int>& nums) {
        int result = 0;
        mergeSort(nums, 0 , nums.size()-1, result);
        return result;
    }
};
// @lc code=end

