"""72. Edit Distance
Medium
Topics
Companies
Given two strings word1 and word2, return the minimum number of operations required to convert word1 to word2.

You have the following three operations permitted on a word:

Insert a character
Delete a character
Replace a character
 

Example 1:

Input: word1 = "horse", word2 = "ros"
Output: 3
Explanation: 
horse -> rorse (replace 'h' with 'r')
rorse -> rose (remove 'r')
rose -> ros (remove 'e')
Example 2:

Input: word1 = "intention", word2 = "execution"
Output: 5
Explanation: 
intention -> inention (remove 't')
inention -> enention (replace 'i' with 'e')
enention -> exention (replace 'n' with 'x')
exention -> exection (replace 'n' with 'c')
exection -> execution (insert 'u')
 

Constraints:

0 <= word1.length, word2.length <= 500
word1 and word2 consist of lowercase English letters."""


class Solution(object):
    def minDistance(self, word1, word2):
        """
        :type word1: str
        :type word2: str
        :rtype: int
        """

        # in brute force we can see
        # if the pointers of i on first string, and j on second string used
        # i = m-1 , j = n -1
        # if a[i] == a[j], then i-=1, j-=1
        # Replace : we force them to be equal. i-=1 and j-=1
        # Insert : e.g. abc , abcd , i on c and j on d , insert d into abc----> i and j-=1
        # Delete : e.g. abcd , abc , i on d and j on c , move on from d to c, deleting d------> i-=1 and j
        m = len(word1)
        n = len(word2)
        dp = [[0 for j in range(n + 1)] for i in range(m + 1) ]
        for i in range(m + 1):
            for j in range(n+ 1):
                if i == 0:
                    dp[i][j] = j
                elif j == 0:
                    dp[i][j] = i
                else:
                    if word1[i - 1] == word2[j - 1]:
                        dp[i][j] = dp[i-1][j-1]
                    else :
                        dp[i][j] = 1 +  min(dp[i-1][j], dp[i-1][j-1], dp[i][j-1])
        return dp[m][n] 


sol = Solution()
print(sol.minDistance("abcd", "abc"))
