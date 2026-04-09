/*
 * @lc app=leetcode id=1011 lang=cpp
 *
 * [1011] Capacity To Ship Packages Within D Days
 *
 * https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/description/
 *
 * algorithms
 * Medium (73.55%)
 * Likes:    11000
 * Dislikes: 289
 * Total Accepted:    756.9K
 * Total Submissions: 1M
 * Testcase Example:  '[1,2,3,4,5,6,7,8,9,10]\n5'
 *
 * A conveyor belt has packages that must be shipped from one port to another
 * within days days.
 * 
 * The i^th package on the conveyor belt has a weight of weights[i]. Each day,
 * we load the ship with packages on the conveyor belt (in the order given by
 * weights). We may not load more weight than the maximum weight capacity of
 * the ship.
 * 
 * Return the least weight capacity of the ship that will result in all the
 * packages on the conveyor belt being shipped within days days.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: weights = [1,2,3,4,5,6,7,8,9,10], days = 5
 * Output: 15
 * Explanation: A ship capacity of 15 is the minimum to ship all the packages
 * in 5 days like this:
 * 1st day: 1, 2, 3, 4, 5
 * 2nd day: 6, 7
 * 3rd day: 8
 * 4th day: 9
 * 5th day: 10
 * 
 * Note that the cargo must be shipped in the order given, so using a ship of
 * capacity 14 and splitting the packages into parts like (2, 3, 4, 5), (1, 6,
 * 7), (8), (9), (10) is not allowed.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: weights = [3,2,2,4,1,4], days = 3
 * Output: 6
 * Explanation: A ship capacity of 6 is the minimum to ship all the packages in
 * 3 days like this:
 * 1st day: 3, 2
 * 2nd day: 2, 4
 * 3rd day: 1, 4
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: weights = [1,2,3,1,1], days = 4
 * Output: 3
 * Explanation:
 * 1st day: 1
 * 2nd day: 2
 * 3rd day: 3
 * 4th day: 1, 1
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= days <= weights.length <= 5 * 10^4
 * 1 <= weights[i] <= 500
 * 
 * 
 */
#include<iostream>
#include<vector>
using namespace std;
// @lc code=start
using ll = long long;
class Solution {
public:
    int calculateDays(vector<int> &weights, ll capacity) {
        int days = 1; // Start with the first day
        ll currentLoad = 0;
        
        for(int w : weights) {
            if (currentLoad + w > capacity) {
                // This package won't fit today, move to next day
                days++;
                currentLoad = w;
            } else {
                currentLoad += w;
            }
        }
        return days;
    }

    int shipWithinDays(vector<int>& weights, int days) {
        if(days < 1) return -1;
        // min weight capacity required will be min(weights)
        ll total_weight = 0;
        for(int w : weights)
            total_weight += w;

        ll low = max((ll)*max_element(weights.begin(), weights.end()), total_weight /days);
         //max capacity would be sum of all weights -> 1 day everything ships
        ll high = total_weight;
        ll mid = 0;
        int ans =0 ;
        while(low <= high) {
            mid = low + (high - low)/2;
            int d = calculateDays(weights, mid);
            //cout << "low : " << low << " high : " << high << " mid : " <<mid <<" d :" << d << endl;
            if(d <= days) {
                high = mid - 1;
                ans = mid;
            }
            else if(d > days) low = mid + 1;
        }
        return ans;
        
    }
};
// @lc code=end

