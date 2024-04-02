"""994. Rotting Oranges
Medium

You are given an m x n grid where each cell can have one of three values:

0 representing an empty cell,
1 representing a fresh orange, or
2 representing a rotten orange.
Every minute, any fresh orange that is 4-directionally adjacent to a rotten orange becomes rotten.

Return the minimum number of minutes that must elapse until no cell has a fresh orange. If this is impossible, return -1.

 

Example 1:


Input: grid = [[2,1,1],[1,1,0],[0,1,1]]
Output: 4
Example 2:

Input: grid = [[2,1,1],[0,1,1],[1,0,1]]
Output: -1
Explanation: The orange in the bottom left corner (row 2, column 0) is never rotten, because rotting only happens 4-directionally.
Example 3:

Input: grid = [[0,2]]
Output: 0
Explanation: Since there are already no fresh oranges at minute 0, the answer is just 0.
 

Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 10
grid[i][j] is 0, 1, or 2."""

# second attempt on 15 Marhc 2024

import collections as C


class Solution(object):
    def orangesRotting(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        # 0 -> is empty
        # 1 -> fresh orange
        # 3 -> rotten orange
        # we use a dfs method where we mark every visited node to 1.
        # traverse through every fresh orange to determine whether it is rotten----> brute force
        # optimal : go throught every node and perform a dfs, marking every fresh to rotten

        if len(grid) == 0:
            return -1

        q  = C.deque()
        for row in range(len(grid)):
            for col in range(len(grid[row])):
                if grid[row][col] == 2:
                    q.append((row,col))
        # for row in grid:
        # print(row)
        count = orangeBfs(grid, q)
        for row in grid:
            for ele in row:
                if ele == 1:
                    return -1

        return count


def orangeBfs(grid, q):
    visited = set()
    rowSize = len(grid)
    colSize = len(grid[0])
    # print(q)
    count = -1
    while q:
        for k in range(len(q)):
            i, j = q.popleft()
            visited.add((i, j))
            if grid[i][j] != 2:
                # print(f"rot {i}, {j}")
                grid[i][j] = 2
            # print(f"visited ({i}, {j})")
            pos = [[0, 1], [1, 0], [0, -1], [-1, 0]]
            for pos_x, pos_y in pos:
                x, y = i + pos_x, j + pos_y
                # print(f"pos ({x} , {y})")
                if x >= 0 and x < rowSize and y >= 0 and y < colSize:
                    if (x, y) not in visited and grid[x][y] == 1:
                        print(f"for {i},{j} adj is {x},{y}")
                        # print(visited)
                        # print(f"added neigh {x}, {y}")
                        q.append((x, y))


        for row in grid:
            print(row)
        count += 1
        print(f"increasing count to {count}")
    return count


sol = Solution()
grid = [[2, 1, 1], [1, 1, 0], [0, 1, 1]]
grid = [
    [2, 0, 1, 1, 1, 1, 1, 1, 1, 1],
    [1, 0, 1, 0, 0, 0, 0, 0, 0, 1],
    [1, 0, 1, 0, 1, 1, 1, 1, 0, 1],
    [1, 0, 1, 0, 1, 0, 0, 1, 0, 1],
    [1, 0, 1, 0, 1, 0, 0, 1, 0, 1],
    [1, 0, 1, 0, 1, 1, 0, 1, 0, 1],
    [1, 0, 1, 0, 0, 0, 0, 1, 0, 1],
    [1, 0, 1, 1, 1, 1, 1, 1, 0, 1],
    [1, 0, 0, 0, 0, 0, 0, 0, 0, 1],
    [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],
]

"""grid = [[0,1,1,1],
        [2,0,0,1],
        [1,0,0,1],
        [1,1,1,1]]"""
grid = [[2, 1, 1], [1, 1, 1], [0, 1, 2]]
grid = [[2, 2], [1, 1], [0, 0], [2, 0]]
# print()
print(sol.orangesRotting(grid))
