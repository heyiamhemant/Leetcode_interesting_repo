class Solution:
    def numIslands(self, grid) -> int:
        m = len(grid)
        n = len(grid[0])
        visited = [[0 for i in range(n)] for j in range(m)]

        def modDfs(i, j):
            visited[i][j] = 1
            if (
                i < m - 1 and visited[i + 1][j] == 0 and grid[i + 1][j] == "1"
            ):  # move down
                modDfs(i + 1, j)
            if (
                j < n - 1 and visited[i][j + 1] == 0 and grid[i][j + 1] == "1"
            ):  # move right
                modDfs(i, j + 1)
            if i > 0 and visited[i - 1][j] == 0 and grid[i - 1][j] == "1":
                modDfs(i - 1, j)
            if j > 0 and visited[i][j - 1] == 0 and grid[i][j - 1] == "1":
                modDfs(i, j - 1)

        count = 0
        for i in range(m):
            for j in range(n):
                if visited[i][j] == 0 and grid[i][j] == "1":
                    modDfs(i, j)
                    count += 1
        return count
