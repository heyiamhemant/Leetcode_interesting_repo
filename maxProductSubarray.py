# few things to note
# 1. take care of the zeroes
# 2. minuses can cause odd parity or even parity
import sys

INT_MIN = -sys.maxsize - 1


class Solution:
    def maxProduct(self, nums) -> int:
        n = len(nums)
        dpf = [0 for i in range(n)]
        Max = INT_MIN
        prodf = 1
        prodb = 1
        for i in range(0, n):
            if nums[i] != 0:
                prodf = prodf * nums[i]
                Max = max(Max, prodf)
            else:
                prodf = 1
                if Max < 0:
                    Max = 0
            dpf[i] = prodf
        for i in range(n - 1, -1, -1):
            if nums[i] != 0:
                prodb *= nums[i]
                Max = max(Max, prodb)
            else:
                prodb = 1
                if Max < 0:
                    Max = 0
            dpf[i] = prodb
        return Max
