class Solution:
    def convertToTitle(self, columnNumber: int) -> str:
        num = columnNumber
        res = ""
        while num :
            rem = num % 26
            if rem:
                res += chr(rem + 64)
            num = num // 26
            print(res, rem, num)
        return res[::-1]

sol = Solution()
print(sol.convertToTitle(701))