"""242. Valid Anagram
Solved
Easy
Topics
Companies
Given two strings s and t, return true if t is an anagram of s, and false otherwise.

An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase, typically using all the original letters exactly once.

 

Example 1:

Input: s = "anagram", t = "nagaram"
Output: true
Example 2:

Input: s = "rat", t = "car"
Output: false
 

Constraints:

1 <= s.length, t.length <= 5 * 104
s and t consist of lowercase English letters.
 """

class Solution:
    def isAnagram(self, s: str, t: str) -> bool:
        Map = {}
        for c in s:
            asc = ord(c)
            if asc in Map.keys():
                Map[asc]+=1
            else:
                Map[asc] = 1


        for c in t:
            ascii = ord(c)
            if ascii in Map.keys():
                Map[ascii]-=1
            else:
                return False
        
        for key in Map.keys():
            if Map[key] != 0 :
                return False
        
        return True
