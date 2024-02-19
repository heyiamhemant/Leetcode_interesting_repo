"""B Search A
Programming
Graph Data Structure & Algorithms
Hard
26.6% Success

255

40

Bookmark
Asked In:
Given a 2D A and a B, find if the B exists in the grid.

The B can be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The cell itself does not count as an adjacent cell. 

The same letter cell may be used more than once.

Example :

Given A =

[
  ["ABCE"],
  ["SFCS"],
  ["ADEE"]
]
B = "ABCCED", -> returns 1,
B = "SEE", -> returns 1,
B = "ABCB", -> returns 1,
B = "ABFSAB" -> returns 1
B = "ABCD" -> returns 0
Note that 1 corresponds to true, and 0 corresponds to false."""


def dfs(i, j, A, B, k):
    if k == len(B):
        return True
    if i >= len(A) or j >= len(A[0]) or i < 0 or j < 0 or k >= len(B):
        return False
    if B[k] != A[i][j]:
        return False
    print(A[i][j], i, j, B[k])
    # we dont care about visited because cells might repeat
    if (
        dfs(i + 1, j, A, B, k + 1)
        or dfs(i, j + 1, A, B, k + 1)
        or dfs(i - 1, j, A, B, k + 1)
        or dfs(i, j - 1, A, B, k + 1)
    ):
        return True

    return False


def exist(A, B):
    for i in range(len(A)):
        for j in range(len(A[0])):
            if dfs(i, j, A, B, 0):
                return True
    return False


A = [
    "AEEABC",
    "ABGDCD",
    "DFCFBG",
    "FFEGFD",
    "CBFEDD",
    "DFACFE",
    "DGCDAA",
    "FBFDFB",
    "GFFGFA",
]
B = "FCDDDE"
print(exist(A, B))
