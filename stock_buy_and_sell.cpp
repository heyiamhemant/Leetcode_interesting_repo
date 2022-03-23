/*https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
 You are given an array prices where prices[i] is the price of a given stock on the ith day.

You want to maximize your profit by choosing a single day to buy one stock and choosing a different day in the future to sell that stock.

Return the maximum profit you can achieve from this transaction. If you cannot achieve any profit, return 0.*/
#include <bits/stdc++.h>
#define db1(x) cerr << #x << "=" << x << '\n'
#define db2(x, y) cerr << #x << "=" << x << "," << #y << "=" << y << '\n'
#define db3(x, y, z) cerr << #x << "=" << x << "," << #y << "=" << y << "," << #z << "=" << z << '\n'
#define rep(i, n) for (ll i = 0; i < (n); ++i)
#define repA(i, a, n) for (ll i = a; i <= (n); ++i)
#define repD(i, a, n) for (ll i = a; i >= (n); --i)
#define mp make_pair
#define sp << ' ' <<
#define pb push_back
#define FastIO               \
    ios::sync_with_stdio(0); \
    cin.tie(0);              \
    cout.tie(0);
using namespace std;
using ll = long long;
int stock_buy_and_sell(vector<int> &A)
{
    int MAX_PROFIT = 0;
    int min_till_now = INT_MAX;
    for (int i = 0; i < A.size(); i++)
    {
        min_till_now = min(min_till_now, A[i]);
        MAX_PROFIT = max(A[i] - min_till_now, MAX_PROFIT);
    }
    return MAX_PROFIT;
}
int main()
{
    FastIO
        ll t;
    cin >> t;
    while (t--)
    {
        ll n;
        cin >> n;
        vector<int> v(n);
        rep(i, n) cin >> v[i];
        cout << stock_buy_and_sell(v) << endl;
        /*rep(i, res.size())
        {
            rep(j, res[0].size()) cout << res[i][j] << " ";
            cout << endl;
        }*/
        cout << '\n';
    }
    return 0;
}