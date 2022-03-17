/*Given an integer array nums, find the contiguous subarray (containing at least one number)
 which has the largest sum and return its sum.*/

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
int maxSubArray(vector<int> &nums)
{
    int i = 0;
    int maxfh = 0, sum = 0;
    int maxtn = INT_MIN;
    for (int i : nums)
    {
        sum += i;
        maxtn = max(maxtn, sum);
        if (sum < 0)
        {
            sum = 0;
        }
    }
    return maxtn;
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
        rep(i, n) cout << v[i] << " ";
        cout << maxSubArray(v);

        cout << '\n';
    }
    return 0;
}