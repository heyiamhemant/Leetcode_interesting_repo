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

int longestCommonSubsequence(string text1, string text2) {
        int m = text1.size();
        int n = text2.size();
        int dp[m+1][n+1];
        memset(dp, 0 , sizeof(dp));
        for(int i = 1 ; i <= m ; i++){
            for(int j = 1 ; j <= n ; j++) {
                int pos1 = i-1;
                int pos2 = j-1;
                if(text1[pos1] == text2[pos2])
                    dp[i][j] = 1 + dp[i-1][j-1]; // select both char
                else 
                    dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
            }
        }
        return dp[m][n];
}