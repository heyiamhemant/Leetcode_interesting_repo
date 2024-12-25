/*
 * @lc app=leetcode id=121 lang=cpp
 *
 * [121] Best Time to Buy and Sell Stock
 *
 * https://leetcode.com/problems/best-time-to-buy-and-sell-stock/description/
 *
 * algorithms
 * Easy (54.29%)
 * Likes:    32080
 * Dislikes: 1225
 * Total Accepted:    5.6M
 * Total Submissions: 10.4M
 * Testcase Example:  '[7,1,5,3,6,4]'
 *
 * You are given an array prices where prices[i] is the price of a given stock
 * on the i^th day.
 * 
 * You want to maximize your profit by choosing a single day to buy one stock
 * and choosing a different day in the future to sell that stock.
 * 
 * Return the maximum profit you can achieve from this transaction. If you
 * cannot achieve any profit, return 0.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: prices = [7,1,5,3,6,4]
 * Output: 5
 * Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit
 * = 6-1 = 5.
 * Note that buying on day 2 and selling on day 1 is not allowed because you
 * must buy before you sell.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: prices = [7,6,4,3,1]
 * Output: 0
 * Explanation: In this case, no transactions are done and the max profit =
 * 0.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= prices.length <= 10^5
 * 0 <= prices[i] <= 10^4
 * 
 * 
 */
#include<iostream>
using namespace std;
// @lc code=start
class Solution {
public:
    /**
     * Returns the maximum profit from buying and selling stocks.
     * 
     * We keep track of the minimum price we have seen so far and the maximum
     * profit we can make. We loop through the array and update these two
     * variables according to the current price. At the end of the loop, the
     * maximum profit we can make is stored in maxProfit.
     */
    int maxProfit(vector<int>& prices) {
        int minTillNow = INT_MAX;
        int maxProfit = 0;
        for (int price : prices)
        {
            minTillNow = min(minTillNow, price);
            maxProfit = max(maxProfit, price - minTillNow);
        }
        return maxProfit;
    }
};
// @lc code=end

