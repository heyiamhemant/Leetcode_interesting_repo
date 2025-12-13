//solved https://leetcode.com/problems/score-of-a-string/
class Solution {
public:
    int scoreOfString(string s) {
        int res = 0;
        for(int i = 1 ; i < s.size() ; i++) {
            int score = abs( s[i] - s[i-1]);
            res+=score;
        }
        return res;
    }
};