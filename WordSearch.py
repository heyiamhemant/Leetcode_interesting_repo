"""79. Word Search
Medium
Topics
Companies
Given an m x n grid of characters board and a string word, return true if word exists in the grid.

The word can be constructed from letters of sequentially adjacent cells, where adjacent cells are horizontally or vertically neighboring. The same letter cell may not be used more than once.

 

Example 1:


Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
Output: true
Example 2:


Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "SEE"
Output: true
Example 3:


Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCB"
Output: false
 

Constraints:

m == board.length
n = board[i].length
1 <= m, n <= 6
1 <= word.length <= 15
board and word consists of only lowercase and uppercase English letters.
 """


# brute force approach:
class Solution:
    def exist(self, board, word) -> bool:
        pos = 0
        target = word[0]
        # find the first char of the targetword
        for i, x in enumerate(board):
            for j, y in enumerate(x):
                if y == target:
                    p, q = i, j
                    if dfs(board, p, q, word, pos):  # all characters were found
                        return True
                    # prepare targetWord for next attempt
                    # print("second attempt")
                    pos = 0
        return False


def dfs(board, p, q, targetWord, pos):
    # print(f"call({p},{q})")
    if (
        p < 0
        or q < 0
        or p >= len(board)
        or q >= len(board[0])
        or pos == len(targetWord)
    ):
        return False
    # print(board[p][q])
    targetc = targetWord[pos]
    if targetc == board[p][q]:
        temp = board[p][q]
        board[p][q] = "#"
        # print(targetc, p, q, pos)
        # print(board)
        pos += 1
        if (
            pos == len(targetWord)
            or dfs(board, p + 1, q, targetWord, pos)
            or dfs(board, p, q + 1, targetWord, pos)
            or dfs(board, p - 1, q, targetWord, pos)
            or dfs(board, p, q - 1, targetWord, pos)
        ):
            return True
        board[p][q] = temp

    return False


sol = Solution()
board = [["A", "B", "C", "E"], ["S", "F", "C", "S"], ["A", "D", "E", "E"]]
board = [["A", "B", "C", "E"], ["S", "F", "C", "S"], ["A", "D", "E", "E"]]
board = [["C", "A", "A"], ["A", "A", "A"], ["B", "C", "D"]]
word = "ABCCED"
# word = "AAB"
print(sol.exist(board, word))
