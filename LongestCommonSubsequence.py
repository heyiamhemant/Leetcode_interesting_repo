import os


# Recursive solution


def lcs(str1, str2, n1, n2):
    if n1 < 0 or n2 < 0:
        return 0
    if str1[n1] == str2[n2]:
        print(str1[n1], str2[n2])
        return 1 + lcs(str1, str2, n1 - 1, n2 - 1)
    return max(lcs(str1, str2, n1 - 1, n2), lcs(str1, str2, n1, n2 - 1))


def longestCommonSubsequence(str1, str2):
    # Rules for getting a recursion - Striver
    # 1. Think everything in terms of index.
    # 2. Think about all the possibilities.
    # 3. Pick the best possible among them.
    # so in this question to find lcs, we can say
    # lcs[a = str1.length-1,b = str2.length-1] = lcs ( str1[0.. str1.length-1] and str2 [0 .. str2.length-1])

    # First Recursive soln:

    # memoization
    n1 = len(str1)
    n2 = len(str2)

    dp = [[0 for j in range(n2 + 1)] for i in range(n1 + 1)]
    for i in range(1, n1 + 1):
        for j in range(1, n2 + 1):
            if str1[i - 1] == str2[j - 1]:
                print(str1[i - 1], str2[j - 1])
                dp[i][j] = dp[i - 1][j - 1] + 1
            else:
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])
    return dp[n1][n2]


# driver

print(longestCommonSubsequence("abcde", "ace"))
