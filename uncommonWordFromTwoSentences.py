"""884. Uncommon Words from Two Sentences

Companies
A sentence is a string of single-space separated words where each word consists only of lowercase letters.

A word is uncommon if it appears exactly once in one of the sentences, and does not appear in the other sentence.

Given two sentences s1 and s2, return a list of all the uncommon words. You may return the answer in any order.

 

Example 1:

Input: s1 = "this apple is sweet", s2 = "this apple is sour"
Output: ["sweet","sour"]
Example 2:

Input: s1 = "apple apple", s2 = "banana"
Output: ["banana"]"""


class Solution(object):
    def convertSentenceToList(self, s1):
        wordsList = {}
        word = ""
        for i in range(0, len(s1) + 1):
            if i < len(s1):
                char = s1[i]
            if char == " " or i == len(s1):
                if word in wordsList and wordsList[word] == 1:
                    wordsList[word] = 0
                else:
                    wordsList[word] = 1
                word = ""
            else:
                word += char
        return wordsList

    def uncommonFromSentences(self, s1, s2):
        """
        :type s1: str
        :type s2: str
        :rtype: List[str]
        """
        # convert sentences to list of words
        wordsList1 = self.convertSentenceToList(s1)
        wordsList2 = self.convertSentenceToList(s2)

        print(wordsList1)
        print(wordsList2)
        for key in wordsList1:
            if key in wordsList2 and wordsList2[key] == 1:
                wordsList1[key] = 0
                wordsList2[key] = 0

        result = []
        for key, value in wordsList1.items():
            if value == 1:
                result.append(key)
        for key, value in wordsList2.items():
            if value == 1:
                result.append(key)
        return result
