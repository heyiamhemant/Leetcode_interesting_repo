//solved https://leetcode.com/problems/score-of-a-string/
int scoreOfString(string s) {
    int res = 0;
    for(int i = 1 ; i < s.size() ; i++) {
        int score = abs( s[i] - s[i-1]);
        res+=score;
    }
    return res;
}



//https://leetcode.com/problems/longest-common-prefix/
string longestCommonPrefix(vector<string>& strs) {
    bool commonPrefix = true;
    string res;
    int i = 0;
    while(commonPrefix && i < strs[0].size()) {
        char common = strs[0][i];
        for(int j = 1 ; j < strs.size() ; j++) {
            char newCommon = strs[j][i];
            if(common != newCommon)
                commonPrefix = false;
        }
        if(commonPrefix)
            res+=common;

        i++;
    }
    return res;
}