/*
 * @lc app=leetcode id=859 lang=cpp
 *
 * [859] Buddy Strings
 *
 * https://leetcode.com/problems/buddy-strings/description/
 *
 * algorithms
 * Easy (33.93%)
 * Likes:    3361
 * Dislikes: 1849
 * Total Accepted:    295.2K
 * Total Submissions: 868.1K
 * Testcase Example:  '"ab"\n"ba"'
 *
 * Given two strings s and goal, return true if you can swap two letters in s
 * so the result is equal to goal, otherwise, return false.
 * 
 * Swapping letters is defined as taking two indices i and j (0-indexed) such
 * that i != j and swapping the characters at s[i] and s[j].
 * 
 * 
 * For example, swapping at indices 0 and 2 in "abcd" results in "cbad".
 * 
 * 
 * 
 * Example 1:
 * 
 * 
 * Input: s = "ab", goal = "ba"
 * Output: true
 * Explanation: You can swap s[0] = 'a' and s[1] = 'b' to get "ba", which is
 * equal to goal.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "ab", goal = "ab"
 * Output: false
 * Explanation: The only letters you can swap are s[0] = 'a' and s[1] = 'b',
 * which results in "ba" != goal.
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: s = "aa", goal = "aa"
 * Output: true
 * Explanation: You can swap s[0] = 'a' and s[1] = 'a' to get "aa", which is
 * equal to goal.
 * 
 * 
 * 
 * Constraints:
 * 
 * 
 * 1 <= s.length, goal.length <= 2 * 10^4
 * s and goal consist of lowercase letters.
 * 
 * 
 */

 #include<string>
    using namespace std;


// @lc code=start
    bool buddyStrings1(string s, string goal) {
        int arr[26];
        memset(arr, 0 , sizeof(arr));
        if(s == goal) {
            for(char &c : s) {
                if(++arr[c-'a'] == 2) return true;
            }
            
            return false;
            
        }
        // spot the difference
        int pos1 = -1, pos2 = -1;
        for(int i = 0; i < s.size(); i++) {

            if(pos1 == -1 && s[i] != goal[i]) pos1 = i;
            else if(pos2 == -1 && s[i] != goal[i]) pos2 = i;
            else if(s[i] != goal[i]) return false;
        }

        if(pos1 == -1 || pos2 == -1) return false;

        swap(s[pos1], s[pos2]);
        if(s == goal) return true;
        return false;
    }
class Solution {
public:
    bool buddyStringsBitMask(string s, string goal) {
        if(s.size() != goal.size()) return false;
        int mask = 0;
        if(s == goal) {
            for(char &c : s) {
                if((mask >> (c - 'a')) & 1) return true;
                // 01 or 01 is not 10
                else mask |= (1 << (c - 'a'));
            }
            return false;
        }
        // spot the difference
        int pos1 = -1, pos2 = -1;
        for(int i = 0; i < s.size(); i++) {
            if(pos1 == -1 && s[i] != goal[i]) pos1 = i;
            else if(pos2 == -1 && s[i] != goal[i]) pos2 = i;
            else if(s[i] != goal[i]) return false;
        }
        if(pos1 == -1 || pos2 == -1) return false;
        return(s[pos1] == goal[pos2] && s[pos2] == goal[pos1]);
    }
};
// @lc code=end

