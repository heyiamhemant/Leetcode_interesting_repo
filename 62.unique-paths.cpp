/*
 * @lc app=leetcode id=62 lang=cpp
 *
 * [62] Unique Paths
 *
 * https://leetcode.com/problems/unique-paths/description/
 *
 * algorithms
 * Medium (64.96%)
 * Likes:    17526
 * Dislikes: 470
 * Total Accepted:    2.3M
 * Total Submissions: 3.6M
 * Testcase Example:  '3\n7'
 *
 * There is a robot on an m x n grid. The robot is initially located at the
 * top-left corner (i.e., grid[0][0]). The robot tries to move to the
 * bottom-right corner (i.e., grid[m - 1][n - 1]). The robot can only move
 * either down or right at any point in time.
 * 
 * Given the two integers m and n, return the number of possible unique paths
 * that the robot can take to reach the bottom-right corner.
 * 
 * The test cases are generated so that the answer will be less than or equal
 * to 2 * 10^9.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: m = 3, n = 7
 * Output: 28
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: m = 3, n = 2
 * Output: 3
 * Explanation: From the top-left corner, there are a total of 3 ways to reach
 * the bottom-right corner:
 * 1. Right -> Down -> Down
 * 2. Down -> Down -> Right
 * 3. Down -> Right -> Down
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= m, n <= 100
 * 
 * 
 */
#include<iostream>
using namespace std;
// @lc code=start
class Solution {
public:
int uniquePaths(int m, int n) {
    vector<vector<int>> dp(m , vector<int>(n, 0));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                // only one way to get here
                if(i == 0 || j == 0)
                    dp[i][j] = 1;
                else
                    // ways to get here is ways to be left block + above block
                    dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
            
        }
        return dp[m - 1][n - 1];
    }
};
// @lc code=end

