"""Capture Regions on Board
Programming
Graph Data Structure & Algorithms
Hard
33.1% Success

264

19

Bookmark
Asked In:
Problem Description

Given a 2D character matrix A of size N x M, containing 'X' and 'O', capture all regions surrounded by 'X'.

A region is captured by flipping all 'O's into 'X's in that surrounded region.

"""


class Solution:
    def dfs(self, A, i, j):
        if i < 0 or i >= len(A) or j >= len(A[0]) or j < 0 or A[i][j] != "0":
            return
        # else start capture
        A[i][j] = "#"

        self.dfs(A, i + 1, j)
        self.dfs(A, i, j + 1)
        self.dfs(A, i - 1, j)
        self.dfs(A, i, j - 1)

    # @param A : list of list of chars
    def solve(self, A):
        # visited = set()
        M = len(A)
        N = len(A[0])
        for j in range(N):
            if A[0][j] == "0":
                self.dfs(A, 0, j)
            if A[M - 1][j] == "0":
                self.dfs(A, M - 1, j)
        for i in range(M):
            if A[i][0] == "0":
                self.dfs(A, i, 0)
            if A[i][N - 1] == "0":
                self.dfs(A, i, N - 1)
        for i in range(M):
            for j in range(N):
                if A[i][j] == "0":
                    A[i][j] = "X"
                if A[i][j] == "#":
                    A[i][j] = "0"


obj = Solution()
"""A = [
    ["X", "0", "0", "0", "0", "0", "0", "X"],
    ["X", "X", "0", "0", "X", "0", "0", "X"],
    ["0", "X", "X", "0", "X", "0", "X", "X"],
]"""
A = [["X", "X", "X", "X"], ["X", "0", "X", "X"], ["X", "X", "X", "X"]]
obj.solve(A)
print(A)
