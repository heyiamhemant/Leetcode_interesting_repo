"""646. Maximum Length of Pair Chain
Solved
Medium

Topics
Companies
You are given an array of n pairs pairs where pairs[i] = [lefti, righti] and lefti < righti.

A pair p2 = [c, d] follows a pair p1 = [a, b] if b < c. A chain of pairs can be formed in this fashion.

Return the length longest chain which can be formed.

You do not need to use up all the given intervals. You can select pairs in any order."""


class Solution:
    def findLongestChain(self, pairs: list[list[int]]) -> int:
        pairs.sort(key=lambda x: x[1])
        prevb = -1001
        chain = 0
        for a, b in pairs:
            if a > prevb:
                chain += 1
                prevb = b
        return chain
