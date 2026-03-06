
/*
 * @lc app=leetcode id=problem_id lang=cpp
 *
 * [problem_id] Problem Name
 *
 * https://leetcode.com/problems/problem-slug/description/
 *
 * algorithms
 * Easy (acceptance_rate%)
 *
 * Problem description
 *
 * Example:
 * Input: example_input
 * Output: example_output
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
using namespace std;

// @lc code=start
class Solution {
public:
    return_type function_name(parameters) {
        
    }
};
// @lc code=end

// ============================================================================
// Test Cases
// ============================================================================

int main() {
    Solution sol;
    
    // Test Case 1
    {
        cout << "Test Case 1:" << endl;
        // Add test code here
        cout << "✓ Passed" << endl << endl;
    }
    
    // Test Case 2
    {
        cout << "Test Case 2:" << endl;
        // Add test code here
        cout << "✓ Passed" << endl << endl;
    }
    
    return 0;
}
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