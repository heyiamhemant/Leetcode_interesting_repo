/*
 * @lc app=leetcode id=881 lang=cpp
 *
 * [881] Boats to Save People
 *
 * https://leetcode.com/problems/boats-to-save-people/description/
 *
 * algorithms
 * Medium (59.66%)
 * Likes:    6817
 * Dislikes: 176
 * Total Accepted:    529K
 * Total Submissions: 865.9K
 * Testcase Example:  '[1,2]\n3'
 *
 * You are given an array people where people[i] is the weight of the i^th
 * person, and an infinite number of boats where each boat can carry a maximum
 * weight of limit. Each boat carries at most two people at the same time,
 * provided the sum of the weight of those people is at most limit.
 * 
 * Return the minimum number of boats to carry every given person.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: people = [1,2], limit = 3
 * Output: 1
 * Explanation: 1 boat (1, 2)
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: people = [3,2,2,1], limit = 3
 * Output: 3
 * Explanation: 3 boats (1, 2), (2) and (3)
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: people = [3,5,3,4], limit = 5
 * Output: 4
 * Explanation: 4 boats (3), (3), (4), (5)
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= people.length <= 5 * 10^4
 * 1 <= people[i] <= limit <= 3 * 10^4
 * 
 * 
 */
#include<iostream>
using namespace std;
// @lc code=start
class Solution {
public:
    int numRescueBoats(vector<int>& people, int limit) {
        int count = 0;
        sort(people.begin(), people.end());
        int start = 0 ;
        int end = people.size()  - 1;
        while(start < end) {
            int pairSum = people[start] + people[end] ;
            if(pairSum <= limit) {
                start++;
                end--;
            } else 
                end--;
            count++;
        }
        
        if(start == end && people[start] <= limit)
            count++;

        return count;
    }
};
// @lc code=end

