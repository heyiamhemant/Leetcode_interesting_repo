"""686. Repeated String Match
Medium
Topics
Companies
Given two strings a and b, return the minimum number of times you should repeat string a so that string b is a substring of it. If it is impossible for b​​​​​​ to be a substring of a after repeating it, return -1.

Notice: string "abc" repeated 0 times is "", repeated 1 time is "abc" and repeated 2 times is "abcabc".

 

Example 1:

Input: a = "abcd", b = "cdabcdab"
Output: 3
Explanation: We return 3 because by repeating a three times "abcdabcdabcd", b is a substring of it.
Example 2:

Input: a = "a", b = "aa"
Output: 2
 

Constraints:

1 <= a.length, b.length <= 104
a and b consist of lowercase English letters.
"""


class Solution(object):

    def repeatedStringMatch(self, a, b):
        """
        :type a : str
        :type b : str
        :rtype:int
        """
        # i pointer on a , j pointer on b
        # my idea : calculate hash function of substring as a multiple of different char-codes.
        # if the hash function of
        if a == b:
            return 1

        x = len(a) // len(b)
        for i in range(x):
            a += a
        if RabinKarp(
            a, b
        ):  # minimum repetition to have a substring of len(b) length possible
            return x + 1
        if RabinKarp(a + a, b):  # worst case repetition to have substring in the string
            return x + 2
        return -1


def RabinKarp(str, substr):

    # print(f"str = {str}, substr = {substr}")
    substrHashCode = 0
    for i, c in enumerate(substr):
        substrHashCode += Hash(c) * (10 ** (len(substr) - i - 1))

    ws = len(substr)
    strHashCode = 0
    for i in range(ws):
        c = Hash(str[i])
        strHashCode += c * (10 ** (ws - i - 1))
    print(strHashCode, substrHashCode)
    if strHashCode == substrHashCode:
        return 1
    for i in range(ws, len(str)):
        strHashCode -= Hash(str[i - ws]) * 10 ** (ws - 1)
        strHashCode *= 10
        strHashCode += Hash(str[i])
        print(f"substrHashCode= {substrHashCode}, strHashCode = {strHashCode}")
        if strHashCode == substrHashCode:
            return matchstr(str, substr, i, ws)
    return 0


def Hash(char):
    return ord(char) - ord("a") + 1


def matchstr(str, substr, i, ws):
    print(str[i - ws + 1 : i + 1], substr)
    if str[i - ws + 1 : i + 1] == substr:
        return 1
    return 0


sol = Solution()
print(sol.repeatedStringMatch("aa", "a"))
