/*
 * @lc app=leetcode id=994 lang=cpp
 *
 * [994] Rotting Oranges
 *
 * https://leetcode.com/problems/rotting-oranges/description/
 *
 * algorithms
 * Medium (58.20%)
 * Likes:    15237
 * Dislikes: 477
 * Total Accepted:    1.7M
 * Total Submissions: 2.9M
 * Testcase Example:  '[[2,1,1],[1,1,0],[0,1,1]]'
 *
 * You are given an m x n grid where each cell can have one of three
 * values:
 * 
 * 
 * 0 representing an empty cell,
 * 1 representing a fresh orange, or
 * 2 representing a rotten orange.
 * 
 * 
 * Every minute, any fresh orange that is 4-directionally adjacent to a rotten
 * orange becomes rotten.
 * 
 * Return the minimum number of minutes that must elapse until no cell has a
 * fresh orange. If this is impossible, return -1.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: grid = [[2,1,1],[1,1,0],[0,1,1]]
 * Output: 4
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: grid = [[2,1,1],[0,1,1],[1,0,1]]
 * Output: -1
 * Explanation: The orange in the bottom left corner (row 2, column 0) is never
 * rotten, because rotting only happens 4-directionally.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: grid = [[0,2]]
 * Output: 0
 * Explanation: Since there are already no fresh oranges at minute 0, the
 * answer is just 0.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * m == grid.length
 * n == grid[i].length
 * 1 <= m, n <= 10
 * grid[i][j] is 0, 1, or 2.
 * 
 * 
 */
#include<iostream>
#include<vector>
using namespace std;

// @lc code=start
class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        // Fast I/O optimization
        ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        queue<std::pair<int,int>> Q;
        int count = 0;
        int m = grid.size(), n = grid[0].size();
        int freshOranges = 0;
        for(int i = 0 ¯; i < m; i++) {
            for(int j = 0 ; j < n ; j++) {
                if(grid[i][j] == 2) Q.push({i,j});
                else if(grid[i][j] == 1) freshOranges++;
            }
        }
        vector<int> dRow = {1,0,-1,0};
        vector<int> dCol = {0,1,0,-1};
        while(!Q.empty()) {
            int size = Q.size();
            int rot = false;
            for(int o = 0 ; o < size; o++) {
                std::pair p = Q.front();
                Q.pop();
                int i = p.first;
                int j = p.second;
                grid[i][j] = 0;

                for(int d = 0 ; d < 4; d++) {
                    int x = i + dRow[d];
                    int y = j + dCol[d];
                    if( x >= 0 && 
                    y >= 0 && 
                    x < m && 
                    y < n && 
                    grid[x][y] == 1) {
                        grid[x][y] = 2;
                        Q.push({x,y});
                        freshOranges--;
                        rot = true;
                    }
                }
            }
            if(rot)
                count++;
        }
        if(freshOranges) return -1;
        return count;
    }
};
// @lc code=end

