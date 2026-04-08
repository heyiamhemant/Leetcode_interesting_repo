/*
 * @lc app=leetcode id=875 lang=cpp
 *
 * [875] Koko Eating Bananas
 *
 * https://leetcode.com/problems/koko-eating-bananas/description/
 *
 * algorithms
 * Medium (49.75%)
 * Likes:    13692
 * Dislikes: 917
 * Total Accepted:    1.5M
 * Total Submissions: 3.1M
 * Testcase Example:  '[3,6,7,11]\n8'
 *
 * Koko loves to eat bananas. There are n piles of bananas, the i^th pile has
 * piles[i] bananas. The guards have gone and will come back in h hours.
 * 
 * Koko can decide her bananas-per-hour eating speed of k. Each hour, she
 * chooses some pile of bananas and eats k bananas from that pile. If the pile
 * has less than k bananas, she eats all of them instead and will not eat any
 * more bananas during this hour.
 * 
 * Koko likes to eat slowly but still wants to finish eating all the bananas
 * before the guards return.
 * 
 * Return the minimum integer k such that she can eat all the bananas within h
 * hours.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: piles = [3,6,7,11], h = 8
 * Output: 4
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: piles = [30,11,23,4,20], h = 5
 * Output: 30
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: piles = [30,11,23,4,20], h = 6
 * Output: 23
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= piles.length <= 10^4
 * piles.length <= h <= 10^9
 * 1 <= piles[i] <= 10^9
 * 
 * 
 */
#include<iostream>
#include<vector>
using namespace std;
// @lc code=start
class Solution {
public:
    long long calculatehours(vector<int> &piles, int s) {
        long long hours = 0;
        for(int p : piles) {
            if(p%s == 0)
                hours+=(p/s);
            else hours+=(p/s + 1);
        }
        return hours;
    }
    int minEatingSpeed(vector<int>& piles, int h) {
        // if h is less than number of piles -> cannot eat
        if ( h < piles.size()) return -1;

        // time is between piles.size() and h
        // speed is between  1 and max(piles)
        // binary search rate between 1 -> max(piles)

        int low = 1;
        int high = *max_element(piles.begin(), piles.end());
        int mid = -1;
        long long hours = 0;
        while(low <= high) {
            mid = low + (high - low)/2;
            hours = calculatehours(piles,mid);
            //cout << "mid : " << mid << " hours : " <<hours <<endl;
            if(hours <= h) high = mid - 1; // is slower possible to get even lower speed
            else if(hours > h) low = mid + 1;
        }
        return low; // low will be always satisfy
    }
};

// @lc code=end

