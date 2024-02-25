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
        orig = a
        x = 1
        while len(a) < len(b):
            a+=orig
            x+=1
        if a == b :
            return x 
        if RabinKarp(
            a, b
        ):  # minimum repetition to have a substring of len(b) length possible)
            return x
        if a+orig == b:
            return x+1
        if RabinKarp(a + orig, b):  # worst case repetition to have substring in the string
            return x + 1
        return -1


def RabinKarp(str, substr):

    #print(f"str = {str}, substr = {substr}")
    ws = len(substr)
    substrHashCode = 0
    substrHashCode = sum( (Hash(c) * (10 ** (ws-i -1)) % (10**6)) for i,c in enumerate(substr))
    #print(f"substrHashCode = {substrHashCode}")

    #print(len(str) - ws)
    for i in range(len(str)-ws + 1):
        j = i
        strHashCode = sum((Hash(str[j]) * (10 **(ws-(j-i)-1)) % (10**6))  for j in range(j, j+ws)) 
        #print(str[i:i+ws],strHashCode, substr )
        if strHashCode == substrHashCode and  matchstr(str[i:i+ws], substr):
            return 1
    #print(strHashCode, substrHashCode)
    return 0


def Hash(char):
    return ord(char) - ord("a") + 1


def matchstr(str, substr):
    if str == substr:
        return 1
    return 0


sol = Solution()
print(sol.repeatedStringMatch("abcde", "deabcdeabc"))
print(sol.repeatedStringMatch("aa", "a"))
print(sol.repeatedStringMatch("abcd", "cdabcdab"))
print(sol.repeatedStringMatch("a", "aa"))
