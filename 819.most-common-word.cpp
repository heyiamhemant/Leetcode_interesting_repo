/*
 * @lc app=leetcode id=819 lang=cpp
 *
 * [819] Most Common Word
 *
 * https://leetcode.com/problems/most-common-word/description/
 *
 * algorithms
 * Easy (44.38%)
 * Likes:    1726
 * Dislikes: 3073
 * Total Accepted:    380.3K
 * Total Submissions: 856.7K
 * Testcase Example:  '"Bob hit a ball, the hit BALL flew far after it was hit."\n["hit"]'
 *
 * Given a string paragraph and a string array of the banned words banned,
 * return the most frequent word that is not banned. It is guaranteed there is
 * at least one word that is not banned, and that the answer is unique.
 * 
 * The words in paragraph are case-insensitive and the answer should be
 * returned in lowercase.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: paragraph = "Bob hit a ball, the hit BALL flew far after it was
 * hit.", banned = ["hit"]
 * Output: "ball"
 * Explanation: 
 * "hit" occurs 3 times, but it is a banned word.
 * "ball" occurs twice (and no other word does), so it is the most frequent
 * non-banned word in the paragraph. 
 * Note that words in the paragraph are not case sensitive,
 * that punctuation is ignored (even if adjacent to words, such as "ball,"), 
 * and that "hit" isn't the answer even though it occurs more because it is
 * banned.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: paragraph = "a.", banned = []
 * Output: "a"
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= paragraph.length <= 1000
 * paragraph consists of English letters, space ' ', or one of the symbols:
 * "!?',;.".
 * 0 <= banned.length <= 100
 * 1 <= banned[i].length <= 10
 * banned[i] consists of only lowercase English letters.
 * 
 * 
 */

// @lc code=start
class Solution {
public:
    string mostCommonWord(string paragraph, vector<string>& banned) {
        map<string, int> wordsMap;
        string parseWord;
        string maxFreqWord;
        string secondFreqWord;
        int maxFreq = 0;
        int secondFreq = 0;
        for (int i = 0; i < paragraph.size(); i++)
        {
            if ( parseWord.size() > 0 && paragraph[i] == ' ' || paragraph[i] == ',' || paragraph[i] == '.' || paragraph[i] == '!' || paragraph[i] == '?' || paragraph[i] == ';')
            {
                int wordFreq = ++wordsMap[parseWord];
                if(wordFreq > maxFreq) {
                    secondFreq = maxFreq;
                    maxFreq = wordFreq;
                    secondFreqWord = maxFreqWord;
                    maxFreqWord = parseWord;
                }
                parseWord = "";
            } else {
                parseWord += tolower(paragraph[i]);
            }
        }
        cout << maxFreq << maxFreqWord <<secondFreq << secondFreqWord << endl;
        for (string bannedWord : banned)
        {
            if (bannedWord == maxFreqWord)
            {
                maxFreqWord = secondFreqWord;
            }
        }

        return maxFreqWord;
    }
};
// @lc code=end

