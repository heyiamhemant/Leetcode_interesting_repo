import sys


def queueGame(input: list, start, end):
    if start < 0 or end < 0 or start > end:
        return
    if start == end:
        res = 0
    if start >= 0 and end >= 0 and start <= n - 1 and end <= n - 1 and start < end:
        queueGame(input, start + 1, end)
        queueGame(input, start, end - 1)
        res = max(
            input[start] + dp[start + 1][end],
            input[end - 1] + dp[start][end - 1],
        )  # maximum from both choices possible
    dp[start][end] = res
    return dp[start][end]


# driver
n = int(input())
dp = [[0 for i in range(n)] for i in range(n)]
print(queueGame(0, n - 1))
