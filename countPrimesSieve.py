"""Medium

Topics
Companies

Hint
Given an integer n, return the number of prime numbers that are strictly less than n.

 

Example 1:

Input: n = 10
Output: 4
Explanation: There are 4 prime numbers less than 10, they are 2, 3, 5, 7.
Example 2:

Input: n = 0
Output: 0
Example 3:

Input: n = 1
Output: 0
 

Constraints:

0 <= n <= 5 * 106"""


class Solution:
    # Sieve of Ero : basically go from 2 to n and mark any multiples you come across. Whatever we are left with are the prime factors.
    def countPrimes(self, n: int) -> int:
        mark = [0 for i in range(n)]
        for factor in range(2, n):
            if mark[factor] == 1:
                continue
            for i in range(2 * factor, n, factor):  # because 1 * factor is prime
                if i < n:
                    mark[i] = 1
        res = 0
        for i in range(2, n):
            if mark[i] == 0:
                print(i)
                res += 1
        return res
