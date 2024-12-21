/*
 * @lc app=leetcode id=347 lang=cpp
 *
 * [347] Top K Frequent Elements
 *
 * https://leetcode.com/problems/top-k-frequent-elements/description/
 *
 * algorithms
 * Medium (63.49%)
 * Likes:    17777
 * Dislikes: 686
 * Total Accepted:    2.5M
 * Total Submissions: 3.9M
 * Testcase Example:  '[1,1,1,2,2,3]\n2'
 *
 * Given an integer array nums and an integer k, return the k most frequent
 * elements. You may return the answer in any order.
 * 
 * 
 * Example 1:
 * Input: nums = [1,1,1,2,2,3], k = 2
 * Output: [1,2]
 * Example 2:
 * Input: nums = [1], k = 1
 * Output: [1]
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= nums.length <= 10^5
 * -10^4 <= nums[i] <= 10^4
 * k is in the range [1, the number of unique elements in the array].
 * It is guaranteed that the answer is unique.
 * 
 * 
 * 
 * Follow up: Your algorithm's time complexity must be better than O(n log n),
 * where n is the array's size. 
 * 
 */
#include<iostream>                          
#include<vector>
using namespace std;
// @lc code=start
class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        vector<int, int> freqMap;
        vector<vector<int>> bucket(nums.size());
        vector<int> result;
        for (int i = 0; i < nums.size(); i++)
        {
            freqMap[nums[i]]++;
        }
        for (auto it : freqMap){
            int num = it.first;
            int freq = it.second;
            bucket[freq].push_back(num);
        }
        // get top k most frequent
        int i = nums.size();
        int count = 0;
        while (i > 0 && count <= k)
        {    
            for (int j : bucket[k]) {
                result.push_back(j);
                count++;
            }
        }
    }
};
// @lc code=end

