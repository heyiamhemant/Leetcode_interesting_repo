/*
 * @lc app=leetcode id=567 lang=cpp
 *
 * [567] Permutation in String
 *
 * https://leetcode.com/problems/permutation-in-string/description/
 *
 * algorithms
 * Medium (46.43%)
 * Likes:    12053
 * Dislikes: 466
 * Total Accepted:    1.1M
 * Total Submissions: 2.4M
 * Testcase Example:  '"ab"\n"eidbaooo"'
 *
 * Given two strings s1 and s2, return true if s2 contains a permutation of s1,
 * or false otherwise.
 * 
 * In other words, return true if one of s1's permutations is the substring of
 * s2.
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s1 = "ab", s2 = "eidbaooo"
 * Output: true
 * Explanation: s2 contains one permutation of s1 ("ba").
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s1 = "ab", s2 = "eidboaoo"
 * Output: false
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s1.length, s2.length <= 10^4
 * s1 and s2 consist of lowercase English letters.
 * 
 * 
 */
#include<iostream>
using namespace std;

// @lc code=start
class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        int alphabetsa[26];
        int alphabetsb[26];
        bool result;
        int n1 = s1.size();
        int n2 = s2.size();
        if(n1 > n2)
            return false;
        int matched = 0;
        memset(alphabetsa, 0, sizeof(int));
        memset(alphabetsb, 0, sizeof(int));
        for (char c : s1) {
            alphabetsa[c - 'a']++;
        }

        // get first window
        for (int i = 0; i < n1; i++)
        {
            alphabetsb[s2[i] - 'a']++;
        }

        for (int i = 0; i < 26; i++){
            if(alphabetsa[i] == alphabetsb[i])
                matched++;
        }

        for (int i = n1; i < n2; i++){
            char c = s2[i];
            char p = s2[i - n1];
            alphabetsb[c]++;
            alphabetsb[p]--;
            if (alphabetsb[c] == alphabetsa[c])
                matched++;
            else
                matched--;

            if(alphabetsa[p] == alphabetsb[p])
                matched--;
            else
                matched++;
        }
        if(matched == 26)
            result = true;
        return result;
    }
    
    bool checkInclusion7Jan(string s1, string s2) {
        if (s1.size() > s2.size()) return false;

        array<int, 26> target = {0};
        array<int, 26> window = {0};

        // Count frequency of s1
        for (char c : s1) {
            target[c - 'a']++;
        }

        int len = s1.size();

        // Build initial window of size len in s2
        for (int i = 0; i < len; ++i) {
            window[s2[i] - 'a']++;
        }

        // Check first window
        if (target == window) return true;

        // Slide the window across s2
        for (int i = len; i < s2.size(); ++i) {
            // Add new char
            window[s2[i] - 'a']++;

            // Remove old char (the one leaving the window)
            window[s2[i - len] - 'a']--;

            // Check if current window matches
            if (target == window) return true;
        }

        return false;
    }
};
// @lc code=end

