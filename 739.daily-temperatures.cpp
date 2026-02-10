/*
 * @lc app=leetcode id=739 lang=cpp
 *
 * [739] Daily Temperatures
 *
 * https://leetcode.com/problems/daily-temperatures/description/
 *
 * algorithms
 * Medium (66.51%)
 * Likes:    14517
 * Dislikes: 371
 * Total Accepted:    1.6M
 * Total Submissions: 2.3M
 * Testcase Example:  '[73,74,75,71,69,72,76,73]'
 *
 * Given an array of integers temperatures represents the daily temperatures,
 * return an array answer such that answer[i] is the number of days you have to
 * wait after the i^th day to get a warmer temperature. If there is no future
 * day for which this is possible, keep answer[i] == 0 instead.
 * 
 * 
 * Example 1:
 * Input: temperatures = [73,74,75,71,69,72,76,73]
 * Output: [1,1,4,2,1,1,0,0]
 * Example 2:
 * Input: temperatures = [30,40,50,60]
 * Output: [1,1,1,0]
 * Example 3:
 * Input: temperatures = [30,60,90]
 * Output: [1,1,0]
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= temperatures.length <= 10^5
 * 30 <= temperatures[i] <= 100
 * 
 * 
 */
#include<iostream>
using namespace std;
// @lc code=start
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        stack<int> S;
        vector<int> answer(temperatures.size(), 0);
        for(int i =0 ; i < temperatures.size() ; i++) {
            while(!S.empty() && temperatures[i] > temperatures[S.top()]) {
                // pop the temperatures waiting for a larger temperature
                answer[S.top()] = i - S.top();
                S.pop();
            }
            S.push(i); // put temperatures to wait for a larger temperature to pop them
        }
        return answer;
    }
};
// @lc code=end

