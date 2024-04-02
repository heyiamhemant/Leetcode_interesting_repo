"""127. Word Ladder
Hard

Topics
Companies
A transformation sequence from word beginWord to word endWord using a dictionary wordList is a sequence of words beginWord -> s1 -> s2 -> ... -> sk such that:

Every adjacent pair of words differs by a single letter.
Every si for 1 <= i <= k is in wordList. Note that beginWord does not need to be in wordList.
sk == endWord
Given two words, beginWord and endWord, and a dictionary wordList, return the number of words in the shortest transformation sequence from beginWord to endWord, or 0 if no such sequence exists.

 

Example 1:

Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
Output: 5
Explanation: One shortest transformation sequence is "hit" -> "hot" -> "dot" -> "dog" -> cog", which is 5 words long.
Example 2:

Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log"]
Output: 0
Explanation: The endWord "cog" is not in wordList, therefore there is no valid transformation sequence.
 

Constraints:

1 <= beginWord.length <= 10
endWord.length == beginWord.length
1 <= wordList.length <= 5000
wordList[i].length == beginWord.length
beginWord, endWord, and wordList[i] consist of lowercase English letters.
beginWord != endWord
All the words in wordList are unique."""
import collections as c


class Solution(object):
    def ladderLength(self, beginWord, endWord, wordList):
        """
        :type beginWord: str
        :type endWord: str
        :type wordList: List[str]
        :rtype: int
        """
        # Simple dfs problem, if we are able to construct the adjacency list
        # hot -> *ot, h*t, ho*  is adjacent to dot -> *ot, d*t, do*. Because of the common regular expression.
        # How to find if two word are adjacent?
        # Create a map {regex like *ot -> words like hot, dot}

        # base case

        if endWord not in wordList:
            return 0
        # adjacency list
        neigh = c.defaultdict(list)
        wordList.append(
            beginWord
        )  # since it can also be a neightbour, and it's not present in the wordList

        # construct the ajacency list
        for word in wordList:
            for j in range(len(word)):
                pattern = word[:j] + "*" + word[j + 1 :]  # create all possible patterns
                neigh[pattern].append(
                    word
                )  # add the word to the list of all possible patterns

        # perform bfs to get shortest path
        q = c.deque([beginWord])
        visited = set()
        distance = 1
        while q:
            for i in range(len(q)):
                word = q.popleft()
                visited.add(word)
                print(word)
                if word == endWord:
                    return distance

                for j in range(len(word)):
                    pattern = word[:j] + "*" + word[j + 1 :]
                    for neighbour in neigh[pattern]:
                        if neighbour not in visited:
                            q.append(neighbour)

            distance += 1

        return 0


sol = Solution()
beginWord, endWord = "hot", "dog"
wordList = ["hot", "dog"]
print(sol.ladderLength(beginWord, endWord, wordList))
