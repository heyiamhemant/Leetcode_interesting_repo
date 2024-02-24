# https://codeforces.com/problemset/problem/1343/C


# find the maximum sum of the longest alternating subsequence -> [+,-,+,-] subsequence
import sys
def alternatingSubsequence(nums):
    # start with positive
    INT_MIN = -sys.maxsize - 1
    i = 0
    j = 0
    sum = 0
    while i < len(nums) and j < len(nums):
        nMax = INT_MIN
        Max = -1
        while i < len(nums) and nums[i] < 0:
            nMax = max(nMax, nums[i])
            i += 1
        if nMax != INT_MIN:
            sum += nMax
        j = i
        while j < len(nums) and nums[j] >= 0:
            Max = max(Max, nums[j])
            j += 1
        print(nMax, Max, end=" ")
        if Max > 0:
            sum += Max
        i = j
    return sum


# driver
T = int(input())
for i in range(T):
    n = int(input())
    nums = [[] for j in range(n)]
    for j in range(n):
        nums[j] = list(map(int, input().split()))
    print(alternatingSubsequence(nums))
# nums = int(input()).split()
