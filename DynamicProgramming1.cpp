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