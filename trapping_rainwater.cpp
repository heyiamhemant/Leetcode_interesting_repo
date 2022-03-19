// https://leetcode.com/problems/trapping-rain-water/
/*Given n non-negative integers representing an elevation map where the width of each bar is 1,
compute how much water it can trap after raining.*/
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

int trap(vector<int> &height)
{
    int i = 0, n = height.size(), j = n - 1, sum = 0;
    int Min = 0, total = 0, bs = 0, bi = 0;
    while (i < j)
    {
        bi = i;
        bs = sum;
        Min = height[i++];
        while (i < j && height[i] < Min)
        {
            sum += (Min - height[i++]);
        }
        if (i == n)
        {
            sum = bs;
            i = bi;
        }

        bi = j;
        bs = sum;
        Min = height[j--];
        while (i < j && height[j] < Min)
        {
            sum += (Min - height[j--]);
        }
        if (j < 0)
        {
            sum = bs;
            j = bi;
        }
        db2(i, j);
    }
    return sum;
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
        cout << "\n";
        cout << trap(v);
        cout << '\n';
    }
    return 0;
}