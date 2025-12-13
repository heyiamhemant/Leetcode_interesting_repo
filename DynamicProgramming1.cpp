#include<iostream>
#include<bits/stdc++>
using namespace std;

int climbingStairs(int n)
{
    if(n == 0 || n == 1)
        return 1;
    int prev1 = 1;
    int prev = 1;
    int result;
    for (int i = 2; i <= n; i++)
    {
        result = prev + prev1;
        prev1 = prev;
        prev = result;


    }
    return result;
}

int coinChange(vector<int> coins, int amount) {
    if (amount < 0)
        return -1
    vector<int> dp(amount + 1, INT_MAX); // every coin is made using infinite coins, we try to minimize it.
    dp[0] = 0;
    for (int i = 1; i <= amount; i++) {
        // find the min {dp[i - coins[j]]}
        for(int coin : coins) {
            if(i >= coin && dp[i-coin] != INT_MAX)
                dp[i] = min(dp[i], 1 + dp[i - coin]);
        }
    }
    if(dp[amount] == INT_MAX)
        return -1;
    else
        return dp[amount];
}

int longestCommonSubsequence(string a , string b ) {
    int m = a.size();
    int n = b.size();
    int dp[m+1][n+1];
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++) {
            if(a[i-1] == b[j-1])
                dp[i][j] = 1 + dp[i - 1][j - 1];
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    return dp[m][n];
}

int dpKnapsack(vector<vector<int>>& bag, int capacity) {
    int dp[bag.size()];
    int maxProfit = INT_MIN;
    int remaining = capacity;
    for (int i = 0; i < bag.size(); i++)
    {
        if(i == 0) {
            maxProfit = bag[0][1]; // profit
            dp[0] = capacity - bag[0][0]; // weight
        }

        int take = bag[i][1] /*profit*/ + dp[i - 1] /*maxprofit of capacity - 1*/;
        int nottake = dp[i - 1];
        if (remaining < bag[i][0])
        {
            maxProfit = max(take, nottake);
            remaining = 
        }
    }
    return maxProfit;
}
